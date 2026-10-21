# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

4 runs, 2026-10-18 to 2026-10-21. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-10-21T09:18:17Z. Machine: AMD EPYC 7763 64-Core Processor, 4 cores, 15.6 GiB, Linux-7.0.0-1017-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.009 (0.009-0.010) | 0.009 (0.008-0.010) | 0.006 (0.005-0.006) | 0.015 (0.013-0.017) | 0.077 (0.071-0.080) | 0.005 (0.005-0.005) |
| bintrees | 0.403 (0.400-0.409) | 0.401 (0.397-0.402) | 0.679 (0.673-0.684) | 1.293 (1.284-1.304) | 0.338 (0.335-0.340) | 0.710 (0.705-0.721) |
| bytesstr | 0.039 (0.038-0.041) | 0.035 (0.034-0.036) | 0.024 (0.024-0.025) | 0.009 (0.008-0.010) | 0.103 (0.099-0.114) | 0.039 (0.039-0.040) |
| fib | 0.283 (0.283-0.284) | 0.306 (0.306-0.306) | 0.198 (0.198-0.208) | 0.597 (0.595-0.600) | 0.421 (0.418-0.422) | 0.314 (0.313-0.315) |
| html | 0.165 (0.162-0.168) | 0.136 (0.135-0.137) | 0.166 (0.165-0.170) | 0.240 (0.237-0.246) | n/a | n/a |
| html_hand | 0.130 (0.130-0.132) | 0.101 (0.098-0.102) | n/a | n/a | n/a | n/a |
| http_parse | 0.127 (0.126-0.127) | 0.109 (0.109-0.110) | n/a | n/a | n/a | n/a |
| mapfreq | 0.159 (0.157-0.164) | 0.159 (0.157-0.162) | 0.078 (0.076-0.079) | 0.118 (0.117-0.119) | n/a | n/a |
| mutres | 0.164 (0.164-0.165) | 0.102 (0.101-0.102) | 0.033 (0.032-0.034) | 0.045 (0.045-0.046) | 0.084 (0.082-0.090) | 0.038 (0.038-0.038) |
| nbody | 0.077 (0.077-0.078) | 0.078 (0.078-0.079) | 0.070 (0.070-0.071) | 0.088 (0.088-0.091) | n/a | n/a |
| pqueue | 0.149 (0.148-0.149) | 0.129 (0.126-0.132) | 0.065 (0.065-0.066) | 0.206 (0.204-0.212) | 0.258 (0.246-0.265) | 0.091 (0.091-0.093) |
| qsort_func | 0.221 (0.220-0.223) | 0.218 (0.218-0.220) | 0.237 (0.236-0.243) | 0.412 (0.387-0.433) | n/a | n/a |
| qsort_inplace | 0.110 (0.109-0.112) | 0.110 (0.110-0.111) | 0.088 (0.088-0.088) | 0.128 (0.111-0.137) | n/a | n/a |
| sieve | 0.134 (0.130-0.145) | 0.142 (0.138-0.147) | 0.126 (0.124-0.130) | 0.393 (0.269-0.464) | 0.196 (0.194-0.202) | 0.126 (0.124-0.128) |
| sortedmap | 0.248 (0.247-0.252) | 0.258 (0.257-0.261) | n/a | n/a | n/a | n/a |
| streams | 0.136 (0.135-0.138) | 0.115 (0.113-0.117) | n/a | n/a | n/a | n/a |
| strings | 0.080 (0.078-0.081) | 0.076 (0.074-0.087) | 0.075 (0.075-0.077) | 0.081 (0.073-0.091) | 0.240 (0.236-0.252) | 0.031 (0.030-0.032) |
| tasks | 4.084 (3.975-4.154) | 4.038 (3.986-4.276) | n/a | n/a | n/a | n/a |
| url | 0.356 (0.356-0.358) | 0.315 (0.314-0.317) | n/a | n/a | n/a | n/a |
| wordfreq | 0.128 (0.126-0.140) | 0.126 (0.125-0.128) | 0.114 (0.110-0.120) | 0.119 (0.118-0.120) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.67x | 1.54x | 2.70x | 13.70x | 0.85x |
| bintrees | 0.59x | 0.59x | 1.90x | 0.50x | 1.05x |
| bytesstr | 1.61x | 1.44x | 0.38x | 4.29x | 1.63x |
| fib | 1.43x | 1.54x | 3.01x | 2.12x | 1.58x |
| html | 0.99x | 0.82x | 1.44x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.03x | 2.03x | 1.51x | n/a | n/a |
| mutres | 4.95x | 3.07x | 1.36x | 2.53x | 1.15x |
| nbody | 1.11x | 1.12x | 1.26x | n/a | n/a |
| pqueue | 2.28x | 1.98x | 3.16x | 3.96x | 1.40x |
| qsort_func | 0.93x | 0.92x | 1.74x | n/a | n/a |
| qsort_inplace | 1.25x | 1.25x | 1.45x | n/a | n/a |
| sieve | 1.06x | 1.12x | 3.12x | 1.55x | 1.00x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.06x | 1.00x | 1.08x | 3.18x | 0.41x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.12x | 1.11x | 1.04x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.009 | 0.008 | 0.005 | 0.022 | 0.109 | 0.005 | 4.5 | 4.7 | 4.7 | 9.5 | 47.5 | 5.0 |
| bintrees | 0.402 | 0.401 | 0.679 | 2.829 | 0.398 | 0.709 | 17.5 | 17.8 | 9.5 | 12.2 | 300.9 | 10.0 |
| bytesstr | 0.038 | 0.035 | 0.024 | 0.014 | 0.122 | 0.039 | 11.5 | 11.8 | 11.6 | 6.1 | 102.8 | 4.8 |
| fib | 0.283 | 0.306 | 0.198 | 0.600 | 0.433 | 0.313 | 1.5 | 1.7 | 1.5 | 1.7 | 38.5 | 2.0 |
| html | 0.164 | 0.136 | 0.166 | 0.317 | n/a | n/a | 3.7 | 4.1 | 2.1 | 7.6 | n/a | n/a |
| html_hand | 0.130 | 0.100 | n/a | n/a | n/a | n/a | 2.4 | 2.8 | n/a | n/a | n/a | n/a |
| http_parse | 0.126 | 0.109 | n/a | n/a | n/a | n/a | 1.6 | 1.9 | n/a | n/a | n/a | n/a |
| mapfreq | 0.158 | 0.158 | 0.078 | 0.134 | n/a | n/a | 11.3 | 11.5 | 5.0 | 7.5 | n/a | n/a |
| mutres | 0.164 | 0.101 | 0.033 | 0.046 | 0.118 | 0.038 | 1.5 | 1.9 | 1.5 | 1.8 | 38.9 | 2.0 |
| nbody | 0.077 | 0.078 | 0.070 | 0.089 | n/a | n/a | 1.8 | 1.8 | 1.8 | 1.6 | n/a | n/a |
| pqueue | 0.148 | 0.129 | 0.065 | 0.222 | 0.332 | 0.091 | 6.1 | 6.4 | 4.7 | 14.6 | 61.7 | 4.9 |
| qsort_func | 0.221 | 0.217 | 0.236 | 0.522 | n/a | n/a | 36.4 | 36.6 | 23.7 | 39.7 | n/a | n/a |
| qsort_inplace | 0.110 | 0.110 | 0.088 | 0.162 | n/a | n/a | 16.7 | 17.0 | 16.7 | 31.2 | n/a | n/a |
| sieve | 0.133 | 0.141 | 0.124 | 0.617 | 0.223 | 0.126 | 77.7 | 78.0 | 77.6 | 279.9 | 116.0 | 78.2 |
| sortedmap | 0.248 | 0.258 | n/a | n/a | n/a | n/a | 11.1 | 11.4 | n/a | n/a | n/a | n/a |
| streams | 0.135 | 0.114 | n/a | n/a | n/a | n/a | 39.6 | 39.9 | n/a | n/a | n/a | n/a |
| strings | 0.079 | 0.075 | 0.075 | 0.109 | 0.465 | 0.030 | 46.1 | 46.3 | 34.6 | 23.3 | 139.2 | 19.9 |
| tasks | 4.840 | 4.704 | n/a | n/a | n/a | n/a | 14.1 | 14.4 | n/a | n/a | n/a | n/a |
| url | 0.356 | 0.314 | n/a | n/a | n/a | n/a | 6.4 | 6.7 | n/a | n/a | n/a | n/a |
| wordfreq | 0.127 | 0.126 | 0.113 | 0.122 | n/a | n/a | 2.2 | 2.6 | 1.9 | 6.5 | n/a | n/a |

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
| parallel_collatz | 1 | 0.502 (0.501-0.504) | 0.502 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.299 (0.298-0.311) | 0.538 | 1.68x | 84 % | 1.07x | same |
| parallel_collatz | 4 | 0.196 (0.195-0.196) | 0.652 | 2.57x | 64 % | 1.30x | same |
| streams_parallel | 1 | 0.491 (0.491-0.494) | 0.491 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.260 (0.259-0.262) | 0.494 | 1.89x | 94 % | 1.01x | same |
| streams_parallel | 4 | 0.184 (0.184-0.185) | 0.658 | 2.67x | 67 % | 1.34x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 3.076 (3.031-3.096) | 5.454 | 426.0 | 32,944,599,759 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
| 2026-10-21T09:18:17Z | `148472c2cd` | main | 32,944,599,759 | 3.076 | [json](history/2026-10-21-148472c2cdb0.json) |
| 2026-10-20T09:18:44Z | `4fca791aa7` | main | 32,689,556,132 | 3.135 | [json](history/2026-10-20-4fca791aa730.json) |
| 2026-10-19T09:42:12Z | `4fca791aa7` | main | 32,690,856,642 | 2.491 | [json](history/2026-10-19-4fca791aa730.json) |
| 2026-10-18T08:41:01Z | `f9a96b20cf` | main | 32,474,433,787 | 2.653 | [json](history/2026-10-18-f9a96b20cf4a.json) |
