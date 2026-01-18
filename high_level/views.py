from django.views.generic import DetailView
from django.http import JsonResponse
from .models import TaskModel


class TaskDetailView(DetailView):
    model = TaskModel

    def render_to_response(self, context, **response_kwargs):
        return JsonResponse(self.object.json())
