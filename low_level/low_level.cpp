#include <cpr/cpr.h>
#include <iostream>
#include <string>

class Task {
private:
  std::string identifier;
  int size;
  float duration;

public:
  Task(std::string id, int s, float d) : identifier(id), size(s), duration(d) {}

  // Méthode d'affichage
  void display() const {
    std::cout << "=== Details de la Tache ===" << std::endl;
    std::cout << "Identifier : " << identifier << std::endl;
    std::cout << "Size       : " << size << std::endl;
    std::cout << "Duration   : " << duration << " s" << std::endl;
    std::cout << "===========================" << std::endl;
  }
};

int main() {
  std::cout << "--- Test de connexion HTTP ---" << std::endl;
  std::string url = "http://127.0.0.1:8000/api/task/1/";

  std::cout << "Requete vers : " << url << " ..." << std::endl;
  cpr::Response r = cpr::Get(cpr::Url{url});

  // 3. Vérification du statut HTTP
  if (r.status_code == 200) {
    std::cout << "Succes ! Reponse recue :" << std::endl;
    std::cout << r.text << std::endl;
  } else {
    std::cerr << "Erreur HTTP : " << r.status_code << std::endl;
    std::cerr << "Message : " << r.text << std::endl;
  }

  return 0;
}
