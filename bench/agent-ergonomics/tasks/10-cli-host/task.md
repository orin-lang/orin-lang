# 10-cli-host

Write an Orin command-line tool `cli-host FILE` that reads the file named in the first program argument and prints it with line numbers, skipping blank lines, writing through the stdio grant. A missing argument or unreadable file prints an error on standard error and exits with status 1 or 2. Use the grants from std:host (no ambient I/O).

Rules: use only the published documentation; the files in this directory are the final program (`main.or`), the expected output (`expected.out`) and, where the program reads input, `stdin` and `args`.
