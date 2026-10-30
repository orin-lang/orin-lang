# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

13 runs, 2026-10-18 to 2026-10-30. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-10-30T10:51:26Z. Machine: AMD EPYC 9V45 96-Core Processor, 4 cores, 15.6 GiB, Linux-7.0.0-1017-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

<details><summary>Tool versions</summary>

- cc: `cc (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0`
- clang: `Ubuntu clang version 18.1.3 (1ubuntu1)`
- go: `go version go1.24.13 linux/amd64`
- java: `openjdk version "21.0.13" 2026-10-20 LTS`
- python: `3.12.3`
- rustc: `rustc 1.99.1 (58cf8f9c3 2026-10-13)`
- valgrind: `valgrind-3.22.0`

</details>

### Wall time, seconds (median; min-max)

| benchmark | Orin (C backend) | Orin (LLVM backend) | C | Go | Java | Rust |
|---|---:|---:|---:|---:|---:|---:|
| appends | 0.005 (0.005-0.006) | 0.005 (0.005-0.005) | 0.004 (0.004-0.004) | 0.008 (0.007-0.008) | 0.057 (0.050-0.066) | 0.003 (0.003-0.003) |
| bintrees | 0.251 (0.247-0.254) | 0.240 (0.236-0.268) | 0.330 (0.327-0.351) | 0.756 (0.741-0.780) | 0.225 (0.220-0.227) | 0.403 (0.399-0.432) |
| bytesstr | 0.026 (0.026-0.027) | 0.023 (0.022-0.024) | 0.018 (0.017-0.018) | 0.007 (0.006-0.008) | 0.076 (0.076-0.083) | 0.032 (0.031-0.033) |
| fib | 0.195 (0.188-0.199) | 0.213 (0.210-0.217) | 0.110 (0.108-0.113) | 0.381 (0.379-0.386) | 0.275 (0.272-0.284) | 0.204 (0.202-0.206) |
| html | 0.091 (0.090-0.136) | 0.074 (0.073-0.075) | 0.087 (0.084-0.088) | 0.146 (0.140-0.159) | n/a | n/a |
| html_hand | 0.076 (0.075-0.084) | 0.058 (0.054-0.082) | n/a | n/a | n/a | n/a |
| http_parse | 0.070 (0.070-0.071) | 0.057 (0.056-0.058) | n/a | n/a | n/a | n/a |
| mapfreq | 0.105 (0.100-0.111) | 0.106 (0.104-0.108) | 0.050 (0.049-0.070) | 0.068 (0.067-0.070) | n/a | n/a |
| mutres | 0.091 (0.089-0.094) | 0.056 (0.055-0.059) | 0.022 (0.021-0.023) | 0.024 (0.023-0.024) | 0.066 (0.061-0.067) | 0.027 (0.027-0.027) |
| nbody | 0.047 (0.047-0.047) | 0.046 (0.046-0.047) | 0.047 (0.046-0.047) | 0.060 (0.059-0.060) | n/a | n/a |
| pqueue | 0.098 (0.095-0.101) | 0.081 (0.079-0.090) | 0.049 (0.049-0.051) | 0.136 (0.131-0.138) | 0.187 (0.167-0.219) | 0.058 (0.057-0.060) |
| qsort_func | 0.152 (0.149-0.177) | 0.147 (0.146-0.149) | 0.167 (0.166-0.170) | 0.266 (0.260-0.273) | n/a | n/a |
| qsort_inplace | 0.086 (0.085-0.086) | 0.085 (0.083-0.090) | 0.073 (0.073-0.075) | 0.083 (0.081-0.085) | n/a | n/a |
| sieve | 0.075 (0.074-0.103) | 0.075 (0.074-0.076) | 0.074 (0.072-0.075) | 0.155 (0.147-0.171) | 0.126 (0.121-0.129) | 0.071 (0.070-0.073) |
| sortedmap | 0.169 (0.168-0.204) | 0.178 (0.170-0.187) | n/a | n/a | n/a | n/a |
| streams | 0.082 (0.080-0.087) | 0.074 (0.074-0.078) | n/a | n/a | n/a | n/a |
| strings | 0.052 (0.050-0.113) | 0.047 (0.047-0.048) | 0.043 (0.043-0.044) | 0.046 (0.040-0.051) | 0.179 (0.175-0.181) | 0.022 (0.022-0.025) |
| tasks | 3.062 (3.031-3.145) | 2.998 (2.975-3.067) | n/a | n/a | n/a | n/a |
| url | 0.211 (0.208-0.212) | 0.178 (0.176-0.180) | n/a | n/a | n/a | n/a |
| wordfreq | 0.079 (0.079-0.080) | 0.074 (0.072-0.075) | 0.065 (0.064-0.066) | 0.079 (0.077-0.081) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.38x | 1.19x | 2.01x | 14.71x | 0.83x |
| bintrees | 0.76x | 0.73x | 2.29x | 0.68x | 1.22x |
| bytesstr | 1.46x | 1.26x | 0.39x | 4.22x | 1.76x |
| fib | 1.78x | 1.94x | 3.47x | 2.51x | 1.87x |
| html | 1.05x | 0.86x | 1.69x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.08x | 2.11x | 1.35x | n/a | n/a |
| mutres | 4.19x | 2.59x | 1.11x | 3.04x | 1.25x |
| nbody | 1.01x | 0.99x | 1.29x | n/a | n/a |
| pqueue | 2.00x | 1.66x | 2.76x | 3.81x | 1.17x |
| qsort_func | 0.91x | 0.88x | 1.59x | n/a | n/a |
| qsort_inplace | 1.17x | 1.16x | 1.13x | n/a | n/a |
| sieve | 1.01x | 1.02x | 2.11x | 1.72x | 0.96x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.21x | 1.09x | 1.07x | 4.15x | 0.51x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.23x | 1.14x | 1.22x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.005 | 0.004 | 0.004 | 0.011 | 0.084 | 0.003 | 4.6 | 4.8 | 4.9 | 7.4 | 48.1 | 5.2 |
| bintrees | 0.250 | 0.239 | 0.329 | 1.627 | 0.262 | 0.403 | 17.6 | 17.9 | 9.7 | 13.1 | 301.1 | 10.2 |
| bytesstr | 0.026 | 0.022 | 0.018 | 0.009 | 0.091 | 0.032 | 11.6 | 11.8 | 11.7 | 6.2 | 104.3 | 4.9 |
| fib | 0.194 | 0.213 | 0.109 | 0.381 | 0.283 | 0.203 | 1.6 | 1.9 | 1.6 | 1.9 | 38.6 | 2.1 |
| html | 0.090 | 0.074 | 0.086 | 0.195 | n/a | n/a | 3.9 | 4.2 | 2.2 | 8.6 | n/a | n/a |
| html_hand | 0.076 | 0.054 | n/a | n/a | n/a | n/a | 2.5 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.070 | 0.057 | n/a | n/a | n/a | n/a | 1.7 | 2.1 | n/a | n/a | n/a | n/a |
| mapfreq | 0.104 | 0.106 | 0.050 | 0.077 | n/a | n/a | 11.4 | 11.7 | 5.1 | 7.1 | n/a | n/a |
| mutres | 0.090 | 0.056 | 0.021 | 0.024 | 0.087 | 0.027 | 1.6 | 1.9 | 1.6 | 1.9 | 39.1 | 2.2 |
| nbody | 0.047 | 0.046 | 0.046 | 0.060 | n/a | n/a | 1.9 | 1.9 | 2.0 | 1.6 | n/a | n/a |
| pqueue | 0.097 | 0.081 | 0.049 | 0.142 | 0.231 | 0.057 | 6.2 | 6.5 | 4.9 | 15.0 | 62.1 | 5.1 |
| qsort_func | 0.152 | 0.147 | 0.167 | 0.327 | n/a | n/a | 36.5 | 36.8 | 23.8 | 37.4 | n/a | n/a |
| qsort_inplace | 0.085 | 0.085 | 0.072 | 0.092 | n/a | n/a | 16.8 | 17.1 | 16.9 | 24.3 | n/a | n/a |
| sieve | 0.074 | 0.074 | 0.073 | 0.244 | 0.148 | 0.071 | 77.8 | 78.1 | 77.7 | 204.5 | 116.0 | 78.4 |
| sortedmap | 0.169 | 0.178 | n/a | n/a | n/a | n/a | 11.3 | 11.5 | n/a | n/a | n/a | n/a |
| streams | 0.081 | 0.074 | n/a | n/a | n/a | n/a | 39.8 | 40.0 | n/a | n/a | n/a | n/a |
| strings | 0.051 | 0.047 | 0.043 | 0.058 | 0.343 | 0.021 | 46.2 | 46.5 | 34.7 | 23.3 | 139.3 | 20.0 |
| tasks | 3.494 | 3.409 | n/a | n/a | n/a | n/a | 14.3 | 14.6 | n/a | n/a | n/a | n/a |
| url | 0.210 | 0.177 | n/a | n/a | n/a | n/a | 6.5 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.079 | 0.073 | 0.064 | 0.080 | n/a | n/a | 2.4 | 2.6 | 2.0 | 6.5 | n/a | n/a |

### Executed instructions (valgrind; the regression metric)

| benchmark | Orin C | Orin LLVM | C | Orin C/C | Orin LLVM/C | note |
|---|---:|---:|---:|---:|---:|---|
| appends | 63,532,187 | 44,305,032 | 25,381,150 | 2.50x | 1.75x |  |
| bintrees | 4,323,683,959 | 4,219,297,433 | 7,242,293,438 | 0.60x | 0.58x |  |
| bytesstr | 349,909,247 | 259,440,726 | 178,695,502 | 1.96x | 1.45x |  |
| fib | 3,200,320,090 | 2,483,953,632 | 3,170,983,191 | 1.01x | 0.78x |  |
| html | 1,786,500,088 | 1,465,345,195 | 1,581,660,490 | 1.13x | 0.93x |  |
| html_hand | 1,335,187,118 | 980,559,871 | n/a | n/a | n/a |  |
| http_parse | 1,494,543,473 | 1,314,023,608 | n/a | n/a | n/a |  |
| mapfreq | 1,050,476,715 | 993,975,283 | 719,855,461 | 1.46x | 1.38x |  |
| mutres | 2,300,282,880 | 1,420,255,438 | 291,450,138 | 7.89x | 4.87x |  |
| nbody | 850,321,975 | 772,258,372 | 651,230,677 | 1.31x | 1.19x |  |
| pqueue | 1,383,801,402 | 1,349,545,568 | 355,213,580 | 3.90x | 3.80x |  |
| qsort_func | 1,335,897,332 | 1,268,411,924 | 1,528,677,752 | 0.87x | 0.83x |  |
| qsort_inplace | 563,393,101 | 521,077,328 | 273,751,950 | 2.06x | 1.90x |  |
| sieve | 443,198,013 | 456,725,927 | 191,756,523 | 2.31x | 2.38x |  |
| sortedmap | 1,354,678,419 | 1,354,047,042 | n/a | n/a | n/a |  |
| streams | 1,173,757,219 | 1,173,731,136 | n/a | n/a | n/a |  |
| strings | 647,534,763 | 558,940,700 | 685,893,535 | 0.94x | 0.81x |  |
| tasks | n/a | n/a | n/a | n/a | n/a | llvm skipped: multi-threaded (20,000 tasks, channels): valgrind serialises threads, so the count would include scheduler waits; orin skipped: multi-threaded (20,000 tasks, channels): valgrind serialises threads, so the count would include scheduler waits |
| url | 4,455,707,373 | 4,066,090,876 | n/a | n/a | n/a |  |
| wordfreq | 760,380,161 | 706,684,023 | 880,390,194 | 0.86x | 0.80x |  |

### Parallel speedup (std:task; worker threads = first argument of the program)

| benchmark | threads | wall s (min-max) | CPU s (user+sys) | speedup | efficiency | CPU vs 1 thread | output |
|---|---:|---:|---:|---:|---:|---:|---|
| parallel_collatz | 1 | 0.400 (0.393-0.439) | 0.399 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.232 (0.228-0.238) | 0.421 | 1.72x | 86 % | 1.05x | same |
| parallel_collatz | 4 | 0.145 (0.143-0.146) | 0.485 | 2.76x | 69 % | 1.21x | same |
| streams_parallel | 1 | 0.442 (0.439-0.468) | 0.442 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.230 (0.228-0.236) | 0.441 | 1.92x | 96 % | 1.00x | same |
| streams_parallel | 4 | 0.148 (0.147-0.151) | 0.534 | 2.99x | 75 % | 1.21x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.468 (2.393-2.596) | 3.812 | 426.2 | 32,943,606,281 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
| 2026-10-30T10:51:26Z | `148472c2cd` | main | 32,943,606,281 | 2.468 | [json](history/2026-10-30-148472c2cdb0.json) |
| 2026-10-29T10:55:59Z | `148472c2cd` | main | 32,942,981,735 | 3.250 | [json](history/2026-10-29-148472c2cdb0.json) |
| 2026-10-28T10:31:52Z | `148472c2cd` | main | 32,948,464,083 | 2.813 | [json](history/2026-10-28-148472c2cdb0.json) |
| 2026-10-27T09:43:14Z | `148472c2cd` | main | 32,942,699,177 | 2.709 | [json](history/2026-10-27-148472c2cdb0.json) |
| 2026-10-26T09:51:02Z | `148472c2cd` | main | 32,947,201,465 | 2.974 | [json](history/2026-10-26-148472c2cdb0.json) |
| 2026-10-25T09:03:06Z | `148472c2cd` | main | 32,936,964,885 | 2.535 | [json](history/2026-10-25-148472c2cdb0.json) |
| 2026-10-24T08:45:58Z | `148472c2cd` | main | 32,941,665,170 | 2.841 | [json](history/2026-10-24-148472c2cdb0.json) |
| 2026-10-23T09:15:05Z | `148472c2cd` | main | 32,944,434,877 | 3.020 | [json](history/2026-10-23-148472c2cdb0.json) |
| 2026-10-22T09:19:15Z | `148472c2cd` | main | 32,948,490,800 | 2.785 | [json](history/2026-10-22-148472c2cdb0.json) |
| 2026-10-21T09:18:17Z | `148472c2cd` | main | 32,944,599,759 | 3.076 | [json](history/2026-10-21-148472c2cdb0.json) |
| 2026-10-20T09:18:44Z | `4fca791aa7` | main | 32,689,556,132 | 3.135 | [json](history/2026-10-20-4fca791aa730.json) |
| 2026-10-19T09:42:12Z | `4fca791aa7` | main | 32,690,856,642 | 2.491 | [json](history/2026-10-19-4fca791aa730.json) |
| 2026-10-18T08:41:01Z | `f9a96b20cf` | main | 32,474,433,787 | 2.653 | [json](history/2026-10-18-f9a96b20cf4a.json) |
