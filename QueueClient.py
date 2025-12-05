from multiprocessing.managers import BaseManager


class QueueManager(BaseManager):
    pass


# Il faut ré-enregistrer les noms pour que le client sache quelles méthodes appeler
QueueManager.register("get_task_queue")
QueueManager.register("get_result_queue")


class QueueClient:
    def __init__(self):
        self.manager = QueueManager(address=("localhost", 50000), authkey=b"abc")
        self.manager.connect()
        # Récupération des objets partagés (les proxies)
        self.task_queue = self.manager.get_task_queue()
        self.result_queue = self.manager.get_result_queue()
        print("Connected to server.")
