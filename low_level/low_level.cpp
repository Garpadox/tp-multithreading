#include <chrono>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

#include <Eigen/Dense>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std::chrono;

class Task {
private:
  std::string identifier;
  int size;
  float time;

  std::unique_ptr<Eigen::MatrixXf> A;
  std::unique_ptr<Eigen::VectorXf> b;
  std::optional<Eigen::VectorXf> x;

public:
  Task(int id) {
    std::cout << "Recuperation de la tache " << id << "..." << std::endl;
    std::string url =
        "http://127.0.0.1:8000/api/task/" + std::to_string(id) + "/";
    cpr::Response r = cpr::Get(cpr::Url{url}, cpr::Timeout{5000});

    if (r.status_code != 200) {
      std::cerr << "Erreur HTTP " << r.status_code << std::endl;
      exit(EXIT_FAILURE);
    }

    try {
      json data = json::parse(r.text);

      identifier = data["identifier"];
      size = data["size"];
      time = 0.0f;
      if (data.contains("a") && !data["a"].is_null()) {
        auto json_a = data["a"];
        auto json_b = data["b"];

        A = std::make_unique<Eigen::MatrixXf>(size, size);
        b = std::make_unique<Eigen::VectorXf>(size);

        for (int i = 0; i < size; ++i)
          for (int j = 0; j < size; ++j)
            (*A)(i, j) = json_a[i][j];

        for (int i = 0; i < size; ++i)
          (*b)(i) = json_b[i];

        std::cout << "Donnees chargees depuis le serveur." << std::endl;

      } else {
        std::cout << "WARNING: Matrices absentes du serveur." << std::endl;
        std::cout << "Generation aleatoire locale (Size: " << size << ")..."
                  << std::endl;

        A = std::make_unique<Eigen::MatrixXf>(
            Eigen::MatrixXf::Random(size, size));
        b = std::make_unique<Eigen::VectorXf>(Eigen::VectorXf::Random(size));
      }

    } catch (std::exception &e) {
      std::cerr << "Erreur parsing : " << e.what() << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  void work() {
    if (!A || !b)
      return;

    std::cout << "Calcul en cours (Resolution Ax=b)..." << std::endl;
    auto start = high_resolution_clock::now();
    Eigen::VectorXf result = A->colPivHouseholderQr().solve(*b);
    x = result;

    auto end = high_resolution_clock::now();
    time = duration<float>(end - start).count();

    std::cout << "Termine en " << time << " secondes." << std::endl;
  }

  void display_result() const {
    if (x.has_value()) {
      Eigen::VectorXf check = (*A) * (*x) - (*b);
      std::cout << "Erreur de precision : " << check.norm() << std::endl;
    }
  }
};

int main() {
  Task t(1);
  t.work();
  t.display_result();
  return 0;
}
