from django.urls import path
from .views import TaskDetailView

urlpatterns = [
    path("task/<int:pk>/", TaskDetailView.as_view(), name="task-detail"),
]
