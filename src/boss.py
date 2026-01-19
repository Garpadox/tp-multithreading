# boss.py
from QueueClient import QueueClient
from task import Task


class Boss:
    def __init__(self, client):
        self.tasks_queue = client.task_queue
        self.results_queue = client.result_queue
        self.sent_tasks = {}

    def run_put_queue(self):
        print("--- Sending Tasks ---")
        for i in range(10):
            task = Task(identifier=i)
            self.sent_tasks[i] = task
            self.tasks_queue.put(task)
            print(f"Task {i} sent (Size: {task.size})")

    def run_comparison(self):
        print("\n--- Receiving & Comparing Results ---")
        for _ in range(10):
            cpp_result_task = self.results_queue.get()
            cpp_time = cpp_result_task.time
            id = cpp_result_task.identifier
            original_task = self.sent_tasks[id]
            print(f"Verifying Task {id} in Python...", end=" ")
            original_task.work()
            py_time = original_task.time
            diff = py_time - cpp_time
            winner = "C++" if diff > 0 else "Python"

            print("Done.")
            print(f"   [C++ Time]: {cpp_time:.5f}s")
            print(f"   [Py  Time]: {py_time:.5f}s")
            print(f"   -> Winner: {winner} (Diff: {abs(diff):.5f}s)")


if __name__ == "__main__":
    boss = Boss(QueueClient())
    boss.run_put_queue()
    boss.run_comparison()
