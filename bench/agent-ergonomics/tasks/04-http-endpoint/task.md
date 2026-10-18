# 04-http-endpoint

Write an Orin program with a small JSON HTTP endpoint (`GET /health`, `GET /hello/NAME`, anything else 404) built on std:http and std:net. Keep the routing a pure function, and exercise the server once over the loopback interface inside the same process (server on port 0, one client request, print the response).

Rules: use only the published documentation; the files in this directory are the final program (`main.or`), the expected output (`expected.out`) and, where the program reads input, `stdin` and `args`.
