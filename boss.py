# boss.py
from client import QueueClient
from task import Task
import time


class Boss(QueueClient):
    def __init__(self):
        super().__init__()

    def submit_tasks(self, num_tasks):
        print(f"Envoi de {num_tasks} tâches...")
        for i in range(num_tasks):
            t = Task(identifier=i, size=1000)  # Taille fixée pour l'exemple
            self.task_queue.put(t)
            print(f"Tâche {i} envoyée.")

    def wait_results(self, num_tasks):
        print("Attente des résultats...")
        start_total = time.perf_counter()

        for _ in range(num_tasks):
            result = self.result_queue.get()
            print(
                f"Reçu résultat tâche {result.identifier} (Calculé en {result.time:.4f}s)"
            )

        total_time = time.perf_counter() - start_total
        print(f"Toutes les tâches finies. Temps total d'attente : {total_time:.4f}s")


if __name__ == "__main__":
    boss = Boss()
    # On lance 10 tâches par exemple
    boss.submit_tasks(10)
    boss.wait_results(10)
