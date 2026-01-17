from QueueClient import QueueClient
from task import Task


class Boss:
    def __init__(self, QueueClient):
        self.tasks = QueueClient.m.get_task_queue()
        self.results = QueueClient.m.get_result_queue()

    def run_put_queue(self):
        for i in range(10):
            toDoTask = Task(identifier=i)
            print(f"The task {toDoTask.identifier} is created")
            self.tasks.put(toDoTask)

    def run_get_result(self):
        for _ in range(10):
            result_task = self.results.get()
            print(f"Got result for {result_task.identifier} in {result_task.time}s")


if __name__ == "__main__":
    boss = Boss(QueueClient())

    boss.run_put_queue()
    boss.run_get_result()
