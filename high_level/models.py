from django.db import models


class TaskModel(models.Model):
    identifier = models.CharField(max_length=100)
    size = models.IntegerField()
    duration = models.FloatField(default=0.0)

    def __str__(self):
        return self.identifier

    def json(self):
        return {
            "id": self.id,
            "identifier": self.identifier,
            "size": self.size,
            "duration": self.duration,
        }
