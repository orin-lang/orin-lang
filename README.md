# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

5 runs, 2026-10-18 to 2026-10-22. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-10-22T09:19:15Z. Machine: AMD EPYC 9V74 80-Core Processor, 4 cores, 15.6 GiB, Linux-7.0.0-1017-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

<details><summary>Tool versions</summary>

- cc: `cc (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0`
- clang: `Ubuntu clang version 18.1.3 (1ubuntu1)`
- go: `go version go1.24.13 linux/amd64`
- java: `openjdk version "21.0.12.1" 2026-08-18 LTS`
- python: `3.12.3`
- rustc: `rustc 1.99.1 (58cf8f9c3 2026-10-13)`
- valgrind: `valgrind-3.22.0`

</details>

### Wall time, seconds (median; min-max)

| benchmark | Orin (C backend) | Orin (LLVM backend) | C | Go | Java | Rust |
|---|---:|---:|---:|---:|---:|---:|
| appends | 0.007 (0.007-0.007) | 0.007 (0.006-0.007) | 0.005 (0.005-0.034) | 0.009 (0.009-0.012) | 0.060 (0.055-0.070) | 0.004 (0.004-0.004) |
| bintrees | 0.315 (0.313-0.320) | 0.325 (0.323-0.327) | 0.456 (0.455-0.460) | 0.960 (0.952-0.964) | 0.282 (0.277-0.288) | 0.569 (0.566-0.589) |
| bytesstr | 0.033 (0.033-0.033) | 0.028 (0.028-0.029) | 0.020 (0.020-0.091) | 0.009 (0.008-0.010) | 0.084 (0.084-0.095) | 0.035 (0.032-0.035) |
| fib | 0.244 (0.244-0.244) | 0.247 (0.246-0.249) | 0.151 (0.151-0.151) | 0.512 (0.510-0.514) | 0.324 (0.313-0.346) | 0.271 (0.271-0.271) |
| html | 0.124 (0.124-0.125) | 0.102 (0.102-0.104) | 0.123 (0.123-0.142) | 0.182 (0.179-0.188) | n/a | n/a |
| html_hand | 0.104 (0.104-0.105) | 0.080 (0.077-0.083) | n/a | n/a | n/a | n/a |
| http_parse | 0.091 (0.091-0.093) | 0.077 (0.077-0.078) | n/a | n/a | n/a | n/a |
| mapfreq | 0.121 (0.120-0.121) | 0.122 (0.121-0.123) | 0.060 (0.059-0.062) | 0.090 (0.088-0.090) | n/a | n/a |
| mutres | 0.137 (0.137-0.137) | 0.087 (0.087-0.122) | 0.027 (0.027-0.028) | 0.037 (0.036-0.037) | 0.072 (0.069-0.080) | 0.032 (0.032-0.033) |
| nbody | 0.064 (0.064-0.064) | 0.064 (0.064-0.064) | 0.061 (0.061-0.104) | 0.072 (0.071-0.072) | n/a | n/a |
| pqueue | 0.135 (0.131-0.138) | 0.109 (0.105-0.114) | 0.059 (0.058-0.068) | 0.170 (0.165-0.174) | 0.217 (0.207-0.223) | 0.076 (0.075-0.078) |
| qsort_func | 0.183 (0.180-0.184) | 0.181 (0.179-0.183) | 0.192 (0.191-0.249) | 0.324 (0.315-0.333) | n/a | n/a |
| qsort_inplace | 0.099 (0.097-0.100) | 0.109 (0.103-0.113) | 0.076 (0.076-0.076) | 0.104 (0.098-0.106) | n/a | n/a |
| sieve | 0.125 (0.122-0.128) | 0.123 (0.121-0.126) | 0.117 (0.106-0.213) | 0.223 (0.203-0.277) | 0.178 (0.171-0.191) | 0.118 (0.114-0.119) |
| sortedmap | 0.238 (0.222-0.245) | 0.238 (0.222-0.272) | n/a | n/a | n/a | n/a |
| streams | 0.109 (0.109-0.110) | 0.102 (0.101-0.142) | n/a | n/a | n/a | n/a |
| strings | 0.067 (0.066-0.067) | 0.064 (0.063-0.065) | 0.057 (0.056-0.057) | 0.056 (0.053-0.063) | 0.202 (0.194-0.203) | 0.027 (0.026-0.027) |
| tasks | 3.413 (3.358-3.495) | 3.448 (3.368-3.524) | n/a | n/a | n/a | n/a |
| url | 0.293 (0.289-0.309) | 0.251 (0.249-0.254) | n/a | n/a | n/a | n/a |
| wordfreq | 0.097 (0.097-0.115) | 0.098 (0.097-0.200) | 0.086 (0.082-0.106) | 0.120 (0.096-0.142) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.57x | 1.39x | 2.00x | 12.69x | 0.77x |
| bintrees | 0.69x | 0.71x | 2.10x | 0.62x | 1.25x |
| bytesstr | 1.63x | 1.40x | 0.44x | 4.18x | 1.71x |
| fib | 1.61x | 1.63x | 3.39x | 2.14x | 1.80x |
| html | 1.01x | 0.83x | 1.48x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.01x | 2.04x | 1.50x | n/a | n/a |
| mutres | 5.00x | 3.19x | 1.33x | 2.62x | 1.17x |
| nbody | 1.05x | 1.06x | 1.18x | n/a | n/a |
| pqueue | 2.28x | 1.83x | 2.86x | 3.65x | 1.28x |
| qsort_func | 0.95x | 0.95x | 1.69x | n/a | n/a |
| qsort_inplace | 1.31x | 1.44x | 1.38x | n/a | n/a |
| sieve | 1.07x | 1.05x | 1.91x | 1.52x | 1.01x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.18x | 1.13x | 0.99x | 3.55x | 0.47x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.13x | 1.14x | 1.40x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.007 | 0.006 | 0.004 | 0.013 | 0.089 | 0.003 | 4.6 | 4.9 | 4.9 | 10.8 | 47.6 | 5.1 |
| bintrees | 0.315 | 0.324 | 0.456 | 2.034 | 0.326 | 0.568 | 17.6 | 17.9 | 9.7 | 12.1 | 300.9 | 10.1 |
| bytesstr | 0.032 | 0.028 | 0.020 | 0.013 | 0.102 | 0.034 | 11.6 | 11.8 | 11.7 | 7.3 | 103.2 | 5.0 |
| fib | 0.243 | 0.246 | 0.151 | 0.514 | 0.330 | 0.271 | 1.6 | 1.9 | 1.6 | 1.6 | 38.5 | 2.1 |
| html | 0.124 | 0.102 | 0.122 | 0.237 | n/a | n/a | 3.9 | 4.2 | 2.2 | 7.5 | n/a | n/a |
| html_hand | 0.104 | 0.079 | n/a | n/a | n/a | n/a | 2.5 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.091 | 0.077 | n/a | n/a | n/a | n/a | 1.7 | 2.1 | n/a | n/a | n/a | n/a |
| mapfreq | 0.120 | 0.122 | 0.060 | 0.100 | n/a | n/a | 11.4 | 11.7 | 5.1 | 7.7 | n/a | n/a |
| mutres | 0.137 | 0.087 | 0.027 | 0.037 | 0.099 | 0.032 | 1.6 | 1.9 | 1.6 | 1.7 | 39.0 | 2.1 |
| nbody | 0.064 | 0.064 | 0.060 | 0.072 | n/a | n/a | 1.9 | 1.9 | 2.0 | 1.6 | n/a | n/a |
| pqueue | 0.135 | 0.108 | 0.059 | 0.181 | 0.274 | 0.076 | 6.2 | 6.5 | 4.9 | 14.3 | 62.0 | 5.0 |
| qsort_func | 0.183 | 0.181 | 0.191 | 0.399 | n/a | n/a | 36.5 | 36.8 | 23.8 | 38.0 | n/a | n/a |
| qsort_inplace | 0.099 | 0.109 | 0.075 | 0.128 | n/a | n/a | 16.8 | 17.1 | 16.9 | 35.2 | n/a | n/a |
| sieve | 0.124 | 0.123 | 0.116 | 0.331 | 0.196 | 0.118 | 77.8 | 78.1 | 77.7 | 185.9 | 116.1 | 78.3 |
| sortedmap | 0.238 | 0.238 | n/a | n/a | n/a | n/a | 11.3 | 11.5 | n/a | n/a | n/a | n/a |
| streams | 0.109 | 0.100 | n/a | n/a | n/a | n/a | 39.8 | 40.0 | n/a | n/a | n/a | n/a |
| strings | 0.067 | 0.064 | 0.056 | 0.070 | 0.377 | 0.026 | 46.2 | 46.5 | 34.7 | 21.3 | 139.3 | 20.0 |
| tasks | 4.023 | 3.943 | n/a | n/a | n/a | n/a | 14.3 | 14.6 | n/a | n/a | n/a | n/a |
| url | 0.292 | 0.250 | n/a | n/a | n/a | n/a | 6.5 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.097 | 0.097 | 0.082 | 0.098 | n/a | n/a | 2.4 | 2.6 | 2.0 | 6.5 | n/a | n/a |

### Executed instructions (valgrind; the regression metric)

| benchmark | Orin C | Orin LLVM | C | Orin C/C | Orin LLVM/C | note |
|---|---:|---:|---:|---:|---:|---|
| appends | 63,532,187 | 44,305,032 | 25,381,131 | 2.50x | 1.75x |  |
| bintrees | 4,323,683,945 | 4,219,297,419 | 7,242,293,438 | 0.60x | 0.58x |  |
| bytesstr | 349,909,233 | 259,440,712 | 178,695,502 | 1.96x | 1.45x |  |
| fib | 3,200,320,090 | 2,483,953,632 | 3,170,983,182 | 1.01x | 0.78x |  |
| html | 1,786,500,069 | 1,465,345,176 | 1,581,660,490 | 1.13x | 0.93x |  |
| html_hand | 1,335,187,118 | 980,559,871 | n/a | n/a | n/a |  |
| http_parse | 1,494,543,487 | 1,314,023,622 | n/a | n/a | n/a |  |
| mapfreq | 1,050,476,715 | 993,975,283 | 719,855,442 | 1.46x | 1.38x |  |
| mutres | 2,300,282,894 | 1,420,255,452 | 291,450,138 | 7.89x | 4.87x |  |
| nbody | 850,321,975 | 772,258,372 | 651,230,701 | 1.31x | 1.19x |  |
| pqueue | 1,383,801,416 | 1,349,545,582 | 355,213,580 | 3.90x | 3.80x |  |
| qsort_func | 1,335,897,346 | 1,268,411,938 | 1,528,677,752 | 0.87x | 0.83x |  |
| qsort_inplace | 563,393,101 | 521,077,328 | 273,751,964 | 2.06x | 1.90x |  |
| sieve | 443,198,013 | 456,725,927 | 191,756,547 | 2.31x | 2.38x |  |
| sortedmap | 1,354,678,419 | 1,354,047,042 | n/a | n/a | n/a |  |
| streams | 1,173,757,219 | 1,173,731,136 | n/a | n/a | n/a |  |
| strings | 647,534,763 | 558,940,700 | 685,893,516 | 0.94x | 0.81x |  |
| tasks | n/a | n/a | n/a | n/a | n/a | llvm skipped: multi-threaded (20,000 tasks, channels): valgrind serialises threads, so the count would include scheduler waits; orin skipped: multi-threaded (20,000 tasks, channels): valgrind serialises threads, so the count would include scheduler waits |
| url | 4,455,707,373 | 4,066,090,876 | n/a | n/a | n/a |  |
| wordfreq | 760,380,147 | 706,684,009 | 880,390,194 | 0.86x | 0.80x |  |

### Parallel speedup (std:task; worker threads = first argument of the program)

| benchmark | threads | wall s (min-max) | CPU s (user+sys) | speedup | efficiency | CPU vs 1 thread | output |
|---|---:|---:|---:|---:|---:|---:|---|
| parallel_collatz | 1 | 0.425 (0.424-0.426) | 0.424 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.251 (0.251-0.252) | 0.453 | 1.69x | 84 % | 1.07x | same |
| parallel_collatz | 4 | 0.158 (0.157-0.160) | 0.531 | 2.69x | 67 % | 1.25x | same |
| streams_parallel | 1 | 0.421 (0.421-0.424) | 0.421 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.221 (0.221-0.222) | 0.422 | 1.90x | 95 % | 1.00x | same |
| streams_parallel | 4 | 0.152 (0.151-0.153) | 0.544 | 2.78x | 69 % | 1.29x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.785 (2.759-2.853) | 4.656 | 426.3 | 32,948,490,800 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
| 2026-10-22T09:19:15Z | `148472c2cd` | main | 32,948,490,800 | 2.785 | [json](history/2026-10-22-148472c2cdb0.json) |
| 2026-10-21T09:18:17Z | `148472c2cd` | main | 32,944,599,759 | 3.076 | [json](history/2026-10-21-148472c2cdb0.json) |
| 2026-10-20T09:18:44Z | `4fca791aa7` | main | 32,689,556,132 | 3.135 | [json](history/2026-10-20-4fca791aa730.json) |
| 2026-10-19T09:42:12Z | `4fca791aa7` | main | 32,690,856,642 | 2.491 | [json](history/2026-10-19-4fca791aa730.json) |
| 2026-10-18T08:41:01Z | `f9a96b20cf` | main | 32,474,433,787 | 2.653 | [json](history/2026-10-18-f9a96b20cf4a.json) |
