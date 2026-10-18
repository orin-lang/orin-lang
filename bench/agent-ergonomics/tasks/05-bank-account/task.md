# 05-bank-account

Write an Orin `Account` class with `deposit`, `withdraw` and `tryWithdraw`, an `@Invariant` that the balance is never negative, and `@Requires`/`@Ensures` (using `old`) on every operation, plus a `transfer` function. It should pass `orin test` and `orin verify --contracts`.

Rules: use only the published documentation; the files in this directory are the final program (`main.or`), the expected output (`expected.out`) and, where the program reads input, `stdin` and `args`.
