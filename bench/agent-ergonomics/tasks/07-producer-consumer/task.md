# 07-producer-consumer

Write an Orin program with two producer tasks and one consumer task joined by a bounded channel from std:task. The producers send ranges of integers; the consumer sums them and counts the items; the channel is closed when both producers are done. The output must be deterministic.

Rules: use only the published documentation; the files in this directory are the final program (`main.or`), the expected output (`expected.out`) and, where the program reads input, `stdin` and `args`.
