# 02-json-config

Write an Orin program with `decodeConfig` that reads a JSON configuration `{name: string, port: int 1..65535, debug?: bool, tags?: string[]}` using std:json and std:json/decode, rejects unknown fields, and prints either the parsed values or the path-qualified validation error. Run it on six built-in inputs (one valid, five invalid).

Rules: use only the published documentation; the files in this directory are the final program (`main.or`), the expected output (`expected.out`) and, where the program reads input, `stdin` and `args`.
