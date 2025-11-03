import unittest
from numpy.testing import assert_allclose

from task import Task  # importe ta classe Task


class TestTask(unittest.TestCase):
    def test_work_solves_linear_system(self):
        # Crée une tâche
        t = Task(size=500)
        # Exécute la résolution
        t.work()
        # Vérifie que A @ x ≈ b
        result = t.a @ t.x
        # tolérance relative (rtol)
        assert_allclose(result, t.b, rtol=1e-5, atol=1e-8)

    def test_time_is_positive(self):
        t = Task(size=200)
        t.work()
        self.assertGreater(t.time, 0)


if __name__ == "__main__":
    unittest.main()
