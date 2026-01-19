#include <cpr/cpr.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class Task {
private:
  std::string identifier;
  int size;
  float duration;

public:
  Task(std::string id, int s, float d) : identifier(id), size(s), duration(d) {}
  Task(json data) {
    std::cout << "Construction JSON" << std::endl;
    identifier = data["identifier"];
    size = data["size"];
    duration = data.value("duration", 0.0f);
  }
  Task(int id) {
    std::cout << "Construction ID (" << id << ")..." << std::endl;
    std::string url =
        "http://127.0.0.1:8000/api/task/" + std::to_string(id) + "/";

    cpr::Response r = cpr::Get(cpr::Url{url}, cpr::Timeout{5000});

    if (r.status_code != 200) {
      std::cerr << "Tache introuvable " << id << std::endl;
      std::cerr << "HTTP : " << r.status_code << std::endl;
      exit(EXIT_FAILURE);
    }
    try {
      json data = json::parse(r.text);
      identifier = data["identifier"];
      size = data["size"];
      duration = data.value("duration", 0.0f);
    } catch (json::parse_error &e) {
      std::cerr << "Erreur de parsing : " << e.what() << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  void display() const {
    std::cout << "=== Tache : " << identifier << " ===" << std::endl;
    std::cout << "Size     : " << size << std::endl;
    std::cout << "Duration : " << duration << "s" << std::endl;
    std::cout << "============================" << std::endl;
  }
};

int main() {
  std::cout << "Constructeurs Intelligents" << std::endl;
  std::cout << "\nDemande de la tache ID 1" << std::endl;
  Task t1(1);
  t1.display();
  std::cout << "\nCreation locale via JSON" << std::endl;
  json local_json = {
      {"identifier", "task_locale"}, {"size", 999}, {"duration", 12.5}};
  Task t2(local_json);
  t2.display();

  return 0;
}
