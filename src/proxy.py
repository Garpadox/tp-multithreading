from http.server import BaseHTTPRequestHandler, HTTPServer
import json
from QueueClient import QueueClient
from task import Task


class Proxy(BaseHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        self.client = QueueClient()
        super().__init__(*args, **kwargs)

    def do_GET(self):
        try:
            t = self.client.task_queue.get(timeout=2)
            json_payload = bytes(t.to_json(), "utf-8")
            self.send_response(200)
            self.send_header("Content-type", "application/json")
            self.end_headers()
            self.wfile.write(json_payload)

        except Exception as e:
            print(f"ERREUR PROXY: {e}")
            self.send_error(404, f"Error: {e}")

    def do_POST(self):
        length = int(self.headers.get("content-length"))
        data = json.loads(self.rfile.read(length))
        t_result = Task(identifier=data["identifier"], size=data["size"])
        t_result.time = data["time"]
        self.client.result_queue.put(t_result)
        self.send_response(200)
        self.end_headers()


def run():
    server = HTTPServer(("", 8000), Proxy)
    print("Proxy running on port 8000...")
    server.serve_forever()


if __name__ == "__main__":
    run()
