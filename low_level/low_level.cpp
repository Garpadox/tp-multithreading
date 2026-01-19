#include <cpr/cpr.h>
#include <iostream>
#include <nlohmann/json.hpp> // AJOUT : La librairie JSON
#include <string>
using json = nlohmann::json;

class Task {
private:
  std::string identifier;
  int size;
  float duration;

public:
  Task(std::string id, int s, float d) : identifier(id), size(s), duration(d) {}

  void display() const {
    std::cout << "=== Details de la Tache ===" << std::endl;
    std::cout << "Identifier : " << identifier << std::endl;
    std::cout << "Size       : " << size << std::endl;
    std::cout << "Duration   : " << duration << " s" << std::endl;
    std::cout << "===========================" << std::endl;
  }
};

int main() {
  std::cout << "Parsing JSON" << std::endl;

  std::string url = "http://127.0.0.1:8000/api/task/1/";
  cpr::Response r = cpr::Get(cpr::Url{url}, cpr::Timeout{5000});

  if (r.status_code == 200) {
    std::cout << "Donnees brutes recues." << std::endl;

    try {
      json task_data = json::parse(r.text);
      std::string id_recupere = task_data["identifier"];
      int size_recuperee = task_data["size"];

      float duration_recuperee = task_data.value("duration", 0.0f);

      std::cout << "\n--- Analyse reussie via JSON ---" << std::endl;
      std::cout << "Identifier: " << id_recupere << std::endl;
      std::cout << "Size: " << size_recuperee << std::endl;
      std::cout << "Duration: " << duration_recuperee << std::endl;

    } catch (json::parse_error &e) {
      std::cerr << "Erreur de parsing JSON : " << e.what() << std::endl;
    }

  } else {
    std::cerr << "Erreur HTTP : " << r.status_code << std::endl;
    std::cerr << "Message : " << r.text << std::endl;
  }

  return 0;
}
