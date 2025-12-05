from multiprocessing.managers import BaseManager
from multiprocessing import Queue

# Les files doivent être définies globalement pour être "picklables" sur certains OS
task_queue = Queue()
result_queue = Queue()


class QueueManager(BaseManager):
    pass


def return_task_queue():
    return task_queue


def return_result_queue():
    return result_queue


if __name__ == "__main__":
    # Enregistrement des méthodes d'accès aux queues
    QueueManager.register("get_task_queue", callable=return_task_queue)
    QueueManager.register("get_result_queue", callable=return_result_queue)

    # Configuration du manager (port 50000, clé d'authentification obligatoire)
    manager = QueueManager(address=("", 50000), authkey=b"abc")

    server = manager.get_server()
    print("Server started on port 50000...")
    server.serve_forever()
