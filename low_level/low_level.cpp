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
  std::cout << "Debut du client low_level" << std::endl;
  Task maTache("task_test_01", 500, 0.0f);

  // Affichage
  maTache.display();

  return 0;
}
