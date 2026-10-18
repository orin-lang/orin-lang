# 03-csv-sum

Write an Orin program `csv-sum COLUMN` that reads CSV (header row, comma separated, blank lines ignored) from standard input and prints `COLUMN total = N`. Report an unknown column or a non-numeric cell with the line number on standard error and exit status 1.

Rules: use only the published documentation; the files in this directory are the final program (`main.or`), the expected output (`expected.out`) and, where the program reads input, `stdin` and `args`.
