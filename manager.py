# manager.py
from multiprocessing.managers import BaseManager
from multiprocessing import Queue

# Définition des files d'attente globales
task_queue = Queue()
result_queue = Queue()


# Fonctions d'accès pour que le Manager puisse exposer les files
def get_task_queue():
    return task_queue


def get_result_queue():
    return result_queue


class QueueManager(BaseManager):
    pass


if __name__ == "__main__":
    # Enregistrement des méthodes dans le réseau
    QueueManager.register("get_task_queue", callable=get_task_queue)
    QueueManager.register("get_result_queue", callable=get_result_queue)

    # Configuration du serveur (Port 50000, mot de passe 'abc')
    manager = QueueManager(address=("", 50000), authkey=b"abc")

    print("Serveur de files d'attente démarré sur le port 50000...")
    server = manager.get_server()
    server.serve_forever()
