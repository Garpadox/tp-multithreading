# minion.py
from client import QueueClient


class Minion(QueueClient):
    def __init__(self):
        super().__init__()

    def work(self):
        print("Minion prêt à travailler (Ctrl+C pour arrêter)...")
        while True:
            try:
                # Récupère une tâche (bloquant si vide)
                task = self.task_queue.get()

                print(
                    f"Traitement de la tâche {task.identifier} (taille {task.size})..."
                )

                # C'est ici que le calcul matriciel se fait
                task.work()

                # On renvoie la tâche complétée
                self.result_queue.put(task)
                print(f"Tâche {task.identifier} terminée et renvoyée.")

            except Exception as e:
                print(f"Erreur: {e}")


if __name__ == "__main__":
    m = Minion()
    m.work()
