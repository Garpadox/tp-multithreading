#include <chrono>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include <Eigen/Dense>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std::chrono;

class Task {
private:
  int identifier;
  int size;
  float time = 0.0;

  std::unique_ptr<Eigen::MatrixXf> A;
  std::unique_ptr<Eigen::VectorXf> b;
  std::optional<Eigen::VectorXf> x;

public:
  Task(int id) {
    std::cout << "Recuperation de la tache " << id << "..." << std::endl;
    std::string url = "http://127.0.0.1:8000/";

    try {
      cpr::Response r = cpr::Get(cpr::Url{url}, cpr::Timeout{30000});

      if (r.status_code == 0) {
        throw std::runtime_error(
            "Le serveur est injoignable (Connection Refused)");
      }
      if (r.status_code != 200) {
        throw std::runtime_error("Erreur HTTP: " +
                                 std::to_string(r.status_code));
      }

      json data = json::parse(r.text);

      if (data["identifier"].is_number()) {
        identifier = data["identifier"];
      } else {
        try {
          identifier = std::stoi(data["identifier"].get<std::string>());
        } catch (...) {
          identifier = 0;
        }
      }

      size = data["size"];
      if (data.contains("a") && data.contains("b")) {
        A = std::make_unique<Eigen::MatrixXf>(size, size);
        b = std::make_unique<Eigen::VectorXf>(size);

        auto json_a = data["a"];
        auto json_b = data["b"];

        for (int i = 0; i < size; ++i) {
          for (int j = 0; j < size; ++j) {
            (*A)(i, j) = json_a[i][j];
          }
        }

        for (int i = 0; i < size; ++i) {
          (*b)(i) = json_b[i];
        }
      } else {
        throw std::runtime_error("JSON incomplet : matrices manquantes");
      }

    } catch (const std::exception &e) {
      throw;
    }
  }

  void work() {
    if (!A || !b)
      return;

    std::cout << "Calcul en cours (Tache " << identifier << ", taille " << size
              << ")..." << std::endl;
    auto start = high_resolution_clock::now();

    Eigen::VectorXf result = A->colPivHouseholderQr().solve(*b);
    x = result;

    auto end = high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    time = elapsed.count();

    std::cout << "Termine en " << time << " secondes." << std::endl;
  }

  void post_result() {
    if (!x.has_value())
      return;

    std::cout << "Envoi des resultats au serveur..." << std::endl;
    json j;
    j["identifier"] = identifier;
    j["size"] = size;
    j["time"] = time;

    j["x"] = json::array();
    for (int i = 0; i < x->size(); ++i) {
      j["x"].push_back((*x)(i));
    }

    cpr::Response r =
        cpr::Post(cpr::Url{"http://127.0.0.1:8000/"}, cpr::Body{j.dump()},
                  cpr::Header{{"Content-Type", "application/json"}});

    if (r.status_code == 200) {
      std::cout << "Resultats envoyes avec succes !" << std::endl;
    } else {
      std::cerr << "Echec de l'envoi : " << r.status_code << std::endl;
    }
  }
};

int main() {
  while (true) {
    try {
      Task t(0);
      t.work();
      t.post_result();
    } catch (...) {
      std::cout << "Plus de taches ou arret du serveur." << std::endl;
      break;
    }
  }
  return 0;
}
