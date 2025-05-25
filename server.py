import http.server
import socketserver
import os

PORT = 8000
# Serve from the current directory (project root) instead of just build_wasm
# DIRECTORY = "build_wasm"


class Handler(http.server.SimpleHTTPRequestHandler):
    # Remove the custom __init__ that forces the directory
    # def __init__(self, *args, **kwargs):
    #     super().__init__(*args, directory=DIRECTORY, **kwargs)

    def end_headers(self):
        self.send_header("Cross-Origin-Opener-Policy", "same-origin")
        self.send_header("Cross-Origin-Embedder-Policy", "require-corp")
        super().end_headers()  # Use super() instead of calling the base class directly


# No need to change directory if serving from the root where server.py is
# os.chdir(os.path.dirname(__file__) or ".")

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print(f"Serving directory '.' at http://localhost:{PORT}")  # Update print message
    print("Adding COOP and COEP headers for SharedArrayBuffer support.")
    httpd.serve_forever()
