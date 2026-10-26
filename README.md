# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

9 runs, 2026-10-18 to 2026-10-26. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-10-26T09:51:02Z. Machine: AMD EPYC 7763 64-Core Processor, 4 cores, 15.6 GiB, Linux-6.17.0-1022-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.008 (0.008-0.010) | 0.008 (0.007-0.008) | 0.005 (0.005-0.005) | 0.007 (0.007-0.009) | 0.068 (0.061-0.071) | 0.004 (0.004-0.004) |
| bintrees | 0.394 (0.393-0.401) | 0.395 (0.393-0.397) | 0.538 (0.536-0.553) | 1.296 (1.281-1.311) | 0.216 (0.209-0.224) | 0.709 (0.701-0.714) |
| bytesstr | 0.032 (0.032-0.033) | 0.028 (0.028-0.028) | 0.018 (0.017-0.019) | 0.007 (0.006-0.010) | 0.065 (0.062-0.072) | 0.035 (0.035-0.036) |
| fib | 0.283 (0.283-0.287) | 0.307 (0.306-0.309) | 0.198 (0.198-0.200) | 0.599 (0.599-0.600) | 0.418 (0.417-0.434) | 0.314 (0.313-0.315) |
| html | 0.163 (0.162-0.168) | 0.137 (0.136-0.141) | 0.167 (0.166-0.168) | 0.235 (0.234-0.239) | n/a | n/a |
| html_hand | 0.131 (0.130-0.136) | 0.100 (0.100-0.100) | n/a | n/a | n/a | n/a |
| http_parse | 0.126 (0.125-0.126) | 0.107 (0.107-0.108) | n/a | n/a | n/a | n/a |
| mapfreq | 0.153 (0.153-0.155) | 0.155 (0.154-0.156) | 0.073 (0.072-0.076) | 0.111 (0.111-0.113) | n/a | n/a |
| mutres | 0.164 (0.164-0.164) | 0.101 (0.101-0.101) | 0.033 (0.032-0.033) | 0.045 (0.044-0.045) | 0.082 (0.079-0.085) | 0.038 (0.038-0.039) |
| nbody | 0.077 (0.077-0.077) | 0.078 (0.078-0.079) | 0.070 (0.070-0.070) | 0.088 (0.088-0.088) | n/a | n/a |
| pqueue | 0.147 (0.146-0.148) | 0.126 (0.125-0.128) | 0.063 (0.063-0.064) | 0.191 (0.189-0.194) | 0.198 (0.191-0.209) | 0.090 (0.089-0.090) |
| qsort_func | 0.208 (0.206-0.210) | 0.208 (0.206-0.209) | 0.227 (0.227-0.228) | 0.338 (0.331-0.346) | n/a | n/a |
| qsort_inplace | 0.105 (0.104-0.106) | 0.105 (0.105-0.107) | 0.082 (0.082-0.083) | 0.091 (0.091-0.095) | n/a | n/a |
| sieve | 0.097 (0.091-0.098) | 0.095 (0.093-0.097) | 0.081 (0.080-0.083) | 0.129 (0.126-0.140) | 0.136 (0.133-0.140) | 0.081 (0.081-0.084) |
| sortedmap | 0.245 (0.244-0.247) | 0.254 (0.253-0.257) | n/a | n/a | n/a | n/a |
| streams | 0.107 (0.106-0.109) | 0.086 (0.084-0.087) | n/a | n/a | n/a | n/a |
| strings | 0.075 (0.073-0.081) | 0.071 (0.070-0.073) | 0.073 (0.072-0.073) | 0.060 (0.056-0.060) | 0.198 (0.192-0.209) | 0.028 (0.027-0.030) |
| tasks | 4.922 (4.790-5.026) | 4.853 (4.754-4.966) | n/a | n/a | n/a | n/a |
| url | 0.355 (0.352-0.376) | 0.309 (0.308-0.315) | n/a | n/a | n/a | n/a |
| wordfreq | 0.127 (0.127-0.128) | 0.125 (0.125-0.126) | 0.110 (0.110-0.111) | 0.112 (0.109-0.112) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.68x | 1.50x | 1.38x | 13.59x | 0.88x |
| bintrees | 0.73x | 0.74x | 2.41x | 0.40x | 1.32x |
| bytesstr | 1.78x | 1.54x | 0.37x | 3.59x | 1.94x |
| fib | 1.43x | 1.55x | 3.02x | 2.11x | 1.58x |
| html | 0.97x | 0.82x | 1.40x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.10x | 2.12x | 1.53x | n/a | n/a |
| mutres | 5.02x | 3.09x | 1.37x | 2.50x | 1.17x |
| nbody | 1.10x | 1.12x | 1.26x | n/a | n/a |
| pqueue | 2.32x | 1.99x | 3.02x | 3.13x | 1.42x |
| qsort_func | 0.92x | 0.91x | 1.49x | n/a | n/a |
| qsort_inplace | 1.27x | 1.28x | 1.11x | n/a | n/a |
| sieve | 1.19x | 1.17x | 1.59x | 1.68x | 1.01x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.03x | 0.97x | 0.82x | 2.73x | 0.39x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.16x | 1.14x | 1.02x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.008 | 0.007 | 0.005 | 0.009 | 0.096 | 0.004 | 4.5 | 4.8 | 4.7 | 10.2 | 58.7 | 4.9 |
| bintrees | 0.394 | 0.395 | 0.537 | 2.829 | 0.272 | 0.709 | 17.5 | 17.8 | 9.5 | 14.3 | 307.8 | 10.0 |
| bytesstr | 0.032 | 0.028 | 0.018 | 0.010 | 0.086 | 0.035 | 11.5 | 11.8 | 11.5 | 7.9 | 108.0 | 4.8 |
| fib | 0.283 | 0.306 | 0.198 | 0.601 | 0.433 | 0.313 | 1.5 | 1.8 | 1.5 | 3.4 | 47.4 | 2.1 |
| html | 0.163 | 0.137 | 0.166 | 0.316 | n/a | n/a | 3.7 | 4.1 | 2.1 | 8.2 | n/a | n/a |
| html_hand | 0.130 | 0.100 | n/a | n/a | n/a | n/a | 2.4 | 2.7 | n/a | n/a | n/a | n/a |
| http_parse | 0.125 | 0.107 | n/a | n/a | n/a | n/a | 1.6 | 2.0 | n/a | n/a | n/a | n/a |
| mapfreq | 0.153 | 0.154 | 0.073 | 0.129 | n/a | n/a | 11.3 | 11.5 | 5.1 | 9.9 | n/a | n/a |
| mutres | 0.163 | 0.101 | 0.032 | 0.045 | 0.112 | 0.038 | 1.5 | 1.7 | 1.5 | 3.4 | 47.8 | 2.1 |
| nbody | 0.077 | 0.078 | 0.070 | 0.088 | n/a | n/a | 1.9 | 1.8 | 1.8 | 3.4 | n/a | n/a |
| pqueue | 0.146 | 0.125 | 0.063 | 0.197 | 0.273 | 0.090 | 6.1 | 6.4 | 4.7 | 16.1 | 70.4 | 5.0 |
| qsort_func | 0.208 | 0.207 | 0.227 | 0.403 | n/a | n/a | 36.4 | 36.7 | 24.0 | 40.6 | n/a | n/a |
| qsort_inplace | 0.104 | 0.105 | 0.082 | 0.099 | n/a | n/a | 16.7 | 17.0 | 16.8 | 31.8 | n/a | n/a |
| sieve | 0.096 | 0.094 | 0.081 | 0.175 | 0.163 | 0.081 | 79.0 | 79.3 | 78.4 | 319.8 | 124.5 | 79.4 |
| sortedmap | 0.245 | 0.254 | n/a | n/a | n/a | n/a | 11.1 | 11.4 | n/a | n/a | n/a | n/a |
| streams | 0.107 | 0.086 | n/a | n/a | n/a | n/a | 42.5 | 40.8 | n/a | n/a | n/a | n/a |
| strings | 0.074 | 0.070 | 0.072 | 0.073 | 0.407 | 0.028 | 48.3 | 47.7 | 36.4 | 25.6 | 145.3 | 20.0 |
| tasks | 5.475 | 5.392 | n/a | n/a | n/a | n/a | 18.1 | 18.5 | n/a | n/a | n/a | n/a |
| url | 0.354 | 0.309 | n/a | n/a | n/a | n/a | 6.4 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.127 | 0.125 | 0.110 | 0.115 | n/a | n/a | 2.2 | 2.6 | 1.9 | 7.9 | n/a | n/a |

### Executed instructions (valgrind; the regression metric)

| benchmark | Orin C | Orin LLVM | C | Orin C/C | Orin LLVM/C | note |
|---|---:|---:|---:|---:|---:|---|
| appends | 63,532,187 | 44,305,032 | 25,381,145 | 2.50x | 1.75x |  |
| bintrees | 4,323,683,959 | 4,219,297,433 | 7,242,293,424 | 0.60x | 0.58x |  |
| bytesstr | 349,909,247 | 259,440,726 | 178,695,488 | 1.96x | 1.45x |  |
| fib | 3,200,320,090 | 2,483,953,632 | 3,170,983,196 | 1.01x | 0.78x |  |
| html | 1,786,500,083 | 1,465,345,190 | 1,581,660,476 | 1.13x | 0.93x |  |
| html_hand | 1,335,187,104 | 980,559,857 | n/a | n/a | n/a |  |
| http_parse | 1,494,543,487 | 1,314,023,622 | n/a | n/a | n/a |  |
| mapfreq | 1,050,476,715 | 993,975,283 | 719,855,456 | 1.46x | 1.38x |  |
| mutres | 2,300,282,894 | 1,420,255,452 | 291,450,138 | 7.89x | 4.87x |  |
| nbody | 850,321,961 | 772,258,358 | 651,230,701 | 1.31x | 1.19x |  |
| pqueue | 1,383,801,416 | 1,349,545,582 | 355,213,580 | 3.90x | 3.80x |  |
| qsort_func | 1,335,897,346 | 1,268,411,938 | 1,528,677,752 | 0.87x | 0.83x |  |
| qsort_inplace | 563,393,087 | 521,077,314 | 273,751,964 | 2.06x | 1.90x |  |
| sieve | 443,197,999 | 456,725,913 | 191,756,547 | 2.31x | 2.38x |  |
| sortedmap | 1,354,678,405 | 1,354,047,028 | n/a | n/a | n/a |  |
| streams | 1,173,757,219 | 1,173,731,136 | n/a | n/a | n/a |  |
| strings | 647,534,763 | 558,940,700 | 685,893,530 | 0.94x | 0.81x |  |
| tasks | n/a | n/a | n/a | n/a | n/a | llvm skipped: multi-threaded (20,000 tasks, channels): valgrind serialises threads, so the count would include scheduler waits; orin skipped: multi-threaded (20,000 tasks, channels): valgrind serialises threads, so the count would include scheduler waits |
| url | 4,455,707,373 | 4,066,090,876 | n/a | n/a | n/a |  |
| wordfreq | 760,380,161 | 706,684,023 | 880,390,180 | 0.86x | 0.80x |  |

### Parallel speedup (std:task; worker threads = first argument of the program)

| benchmark | threads | wall s (min-max) | CPU s (user+sys) | speedup | efficiency | CPU vs 1 thread | output |
|---|---:|---:|---:|---:|---:|---:|---|
| parallel_collatz | 1 | 0.493 (0.493-0.494) | 0.493 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.270 (0.269-0.271) | 0.505 | 1.83x | 91 % | 1.02x | same |
| parallel_collatz | 4 | 0.179 (0.177-0.179) | 0.626 | 2.76x | 69 % | 1.27x | same |
| streams_parallel | 1 | 0.479 (0.479-0.480) | 0.479 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.247 (0.247-0.248) | 0.481 | 1.94x | 97 % | 1.00x | same |
| streams_parallel | 4 | 0.172 (0.172-0.174) | 0.646 | 2.78x | 70 % | 1.35x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.974 (2.967-3.027) | 5.337 | 431.2 | 32,947,201,465 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
| 2026-10-26T09:51:02Z | `148472c2cd` | main | 32,947,201,465 | 2.974 | [json](history/2026-10-26-148472c2cdb0.json) |
| 2026-10-25T09:03:06Z | `148472c2cd` | main | 32,936,964,885 | 2.535 | [json](history/2026-10-25-148472c2cdb0.json) |
| 2026-10-24T08:45:58Z | `148472c2cd` | main | 32,941,665,170 | 2.841 | [json](history/2026-10-24-148472c2cdb0.json) |
| 2026-10-23T09:15:05Z | `148472c2cd` | main | 32,944,434,877 | 3.020 | [json](history/2026-10-23-148472c2cdb0.json) |
| 2026-10-22T09:19:15Z | `148472c2cd` | main | 32,948,490,800 | 2.785 | [json](history/2026-10-22-148472c2cdb0.json) |
| 2026-10-21T09:18:17Z | `148472c2cd` | main | 32,944,599,759 | 3.076 | [json](history/2026-10-21-148472c2cdb0.json) |
| 2026-10-20T09:18:44Z | `4fca791aa7` | main | 32,689,556,132 | 3.135 | [json](history/2026-10-20-4fca791aa730.json) |
| 2026-10-19T09:42:12Z | `4fca791aa7` | main | 32,690,856,642 | 2.491 | [json](history/2026-10-19-4fca791aa730.json) |
| 2026-10-18T08:41:01Z | `f9a96b20cf` | main | 32,474,433,787 | 2.653 | [json](history/2026-10-18-f9a96b20cf4a.json) |
