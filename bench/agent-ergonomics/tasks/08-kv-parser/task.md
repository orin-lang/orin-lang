# 08-kv-parser

Write a parser for `key=value` lines (comments with `#`, blank lines allowed) returning `Result<Entry[], ParseError>` with a tagged-union error type (empty key, missing `=`, bad integer, duplicate key), using `?` to propagate. Print a one-line report for five inputs.

Rules: use only the published documentation; the files in this directory are the final program (`main.or`), the expected output (`expected.out`) and, where the program reads input, `stdin` and `args`.
