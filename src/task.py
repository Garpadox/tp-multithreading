import time
import numpy as np
import json


class Task:
    def __init__(self, identifier=0, size=None):
        self.identifier = identifier
        self.size = size or np.random.randint(300, 3_000)
        self.a = np.random.rand(self.size, self.size)
        self.b = np.random.rand(self.size)
        self.x = np.zeros((self.size))
        self.time = 0

    def work(self):
        start = time.perf_counter()
        self.x = np.linalg.solve(self.a, self.b)
        self.time = time.perf_counter() - start

    def to_json(self):
        data = {
            "identifier": self.identifier,
            "size": self.size,
            "time": self.time,
            "a": self.a.tolist(),
            "b": self.b.tolist(),
            "x": self.x.tolist(),
        }
        return json.dumps(data)

    @staticmethod
    def from_json(json_str: str):
        data = json.loads(json_str)
        task = Task(identifier=data["identifier"], size=data["size"])
        task.time = data["time"]
        task.a = np.array(data["a"])
        task.b = np.array(data["b"])
        task.x = np.array(data["x"])

        return task
