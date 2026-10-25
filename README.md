# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

8 runs, 2026-10-18 to 2026-10-25. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-10-25T09:03:06Z. Machine: AMD EPYC 9V45 96-Core Processor, 4 cores, 15.6 GiB, Linux-6.17.0-1022-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.005 (0.005-0.005) | 0.004 (0.004-0.004) | 0.004 (0.004-0.004) | 0.004 (0.004-0.004) | 0.047 (0.041-0.056) | 0.003 (0.003-0.003) |
| bintrees | 0.248 (0.245-0.252) | 0.234 (0.229-0.236) | 0.315 (0.307-0.344) | 0.742 (0.719-0.757) | 0.133 (0.131-0.135) | 0.398 (0.392-0.405) |
| bytesstr | 0.021 (0.021-0.021) | 0.018 (0.017-0.021) | 0.012 (0.012-0.013) | 0.004 (0.004-0.005) | 0.050 (0.048-0.052) | 0.029 (0.028-0.029) |
| fib | 0.190 (0.189-0.198) | 0.208 (0.207-0.210) | 0.106 (0.105-0.110) | 0.376 (0.372-0.381) | 0.274 (0.273-0.278) | 0.205 (0.201-0.208) |
| html | 0.091 (0.089-0.096) | 0.074 (0.073-0.077) | 0.087 (0.085-0.106) | 0.137 (0.136-0.141) | n/a | n/a |
| html_hand | 0.075 (0.074-0.079) | 0.053 (0.053-0.057) | n/a | n/a | n/a | n/a |
| http_parse | 0.069 (0.069-0.070) | 0.056 (0.055-0.056) | n/a | n/a | n/a | n/a |
| mapfreq | 0.096 (0.094-0.105) | 0.094 (0.094-0.095) | 0.048 (0.045-0.049) | 0.065 (0.063-0.066) | n/a | n/a |
| mutres | 0.090 (0.090-0.093) | 0.056 (0.055-0.056) | 0.022 (0.021-0.023) | 0.024 (0.024-0.025) | 0.061 (0.058-0.067) | 0.027 (0.026-0.027) |
| nbody | 0.047 (0.047-0.047) | 0.046 (0.046-0.050) | 0.046 (0.046-0.046) | 0.060 (0.060-0.060) | n/a | n/a |
| pqueue | 0.098 (0.094-0.107) | 0.081 (0.076-0.098) | 0.050 (0.049-0.050) | 0.131 (0.127-0.137) | 0.151 (0.147-0.179) | 0.058 (0.057-0.063) |
| qsort_func | 0.144 (0.142-0.148) | 0.144 (0.143-0.144) | 0.163 (0.161-0.165) | 0.238 (0.235-0.239) | n/a | n/a |
| qsort_inplace | 0.085 (0.084-0.088) | 0.083 (0.083-0.085) | 0.070 (0.069-0.072) | 0.077 (0.076-0.080) | n/a | n/a |
| sieve | 0.054 (0.052-0.057) | 0.054 (0.053-0.055) | 0.051 (0.051-0.052) | 0.078 (0.076-0.081) | 0.090 (0.089-0.093) | 0.052 (0.051-0.056) |
| sortedmap | 0.172 (0.168-0.201) | 0.166 (0.162-0.192) | n/a | n/a | n/a | n/a |
| streams | 0.069 (0.067-0.072) | 0.055 (0.053-0.056) | n/a | n/a | n/a | n/a |
| strings | 0.050 (0.048-0.050) | 0.044 (0.043-0.045) | 0.041 (0.040-0.042) | 0.032 (0.031-0.033) | 0.147 (0.142-0.154) | 0.019 (0.019-0.019) |
| tasks | 3.385 (3.368-3.427) | 3.360 (3.322-3.388) | n/a | n/a | n/a | n/a |
| url | 0.208 (0.207-0.222) | 0.172 (0.172-0.174) | n/a | n/a | n/a | n/a |
| wordfreq | 0.081 (0.080-0.082) | 0.076 (0.075-0.080) | 0.068 (0.067-0.069) | 0.079 (0.078-0.080) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.39x | 1.17x | 1.12x | 13.33x | 0.77x |
| bintrees | 0.79x | 0.74x | 2.35x | 0.42x | 1.26x |
| bytesstr | 1.69x | 1.41x | 0.35x | 3.98x | 2.30x |
| fib | 1.80x | 1.97x | 3.56x | 2.59x | 1.94x |
| html | 1.05x | 0.85x | 1.58x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 1.98x | 1.95x | 1.34x | n/a | n/a |
| mutres | 4.20x | 2.58x | 1.11x | 2.84x | 1.23x |
| nbody | 1.02x | 1.01x | 1.30x | n/a | n/a |
| pqueue | 1.95x | 1.61x | 2.62x | 3.02x | 1.16x |
| qsort_func | 0.89x | 0.88x | 1.46x | n/a | n/a |
| qsort_inplace | 1.20x | 1.18x | 1.09x | n/a | n/a |
| sieve | 1.05x | 1.05x | 1.52x | 1.76x | 1.01x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.22x | 1.09x | 0.78x | 3.64x | 0.47x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.18x | 1.12x | 1.15x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.005 | 0.004 | 0.003 | 0.005 | 0.069 | 0.002 | 4.6 | 4.8 | 4.9 | 9.7 | 58.6 | 5.2 |
| bintrees | 0.248 | 0.234 | 0.315 | 1.605 | 0.169 | 0.397 | 17.6 | 17.9 | 9.7 | 14.5 | 307.8 | 10.2 |
| bytesstr | 0.021 | 0.017 | 0.012 | 0.006 | 0.063 | 0.028 | 11.6 | 11.9 | 11.6 | 7.8 | 108.3 | 5.0 |
| fib | 0.190 | 0.208 | 0.105 | 0.377 | 0.283 | 0.205 | 1.6 | 1.9 | 1.6 | 3.4 | 47.5 | 2.0 |
| html | 0.090 | 0.074 | 0.086 | 0.180 | n/a | n/a | 3.9 | 4.2 | 2.2 | 8.4 | n/a | n/a |
| html_hand | 0.075 | 0.053 | n/a | n/a | n/a | n/a | 2.5 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.069 | 0.055 | n/a | n/a | n/a | n/a | 1.7 | 2.0 | n/a | n/a | n/a | n/a |
| mapfreq | 0.096 | 0.094 | 0.048 | 0.072 | n/a | n/a | 11.4 | 11.6 | 5.1 | 9.9 | n/a | n/a |
| mutres | 0.090 | 0.055 | 0.021 | 0.024 | 0.084 | 0.026 | 1.6 | 1.9 | 1.6 | 3.4 | 47.8 | 2.2 |
| nbody | 0.047 | 0.046 | 0.046 | 0.060 | n/a | n/a | 1.9 | 1.9 | 2.0 | 3.4 | n/a | n/a |
| pqueue | 0.097 | 0.080 | 0.050 | 0.136 | 0.203 | 0.058 | 6.2 | 6.5 | 4.9 | 16.1 | 70.4 | 5.1 |
| qsort_func | 0.144 | 0.143 | 0.162 | 0.285 | n/a | n/a | 36.5 | 36.8 | 23.8 | 38.8 | n/a | n/a |
| qsort_inplace | 0.084 | 0.083 | 0.070 | 0.084 | n/a | n/a | 16.8 | 17.3 | 16.9 | 23.7 | n/a | n/a |
| sieve | 0.053 | 0.053 | 0.051 | 0.120 | 0.112 | 0.051 | 78.6 | 78.9 | 78.5 | 225.8 | 124.5 | 79.2 |
| sortedmap | 0.171 | 0.166 | n/a | n/a | n/a | n/a | 11.3 | 11.5 | n/a | n/a | n/a | n/a |
| streams | 0.069 | 0.055 | n/a | n/a | n/a | n/a | 42.7 | 41.4 | n/a | n/a | n/a | n/a |
| strings | 0.049 | 0.044 | 0.040 | 0.038 | 0.294 | 0.019 | 47.5 | 47.8 | 36.5 | 25.6 | 145.8 | 21.9 |
| tasks | 3.682 | 3.710 | n/a | n/a | n/a | n/a | 18.3 | 18.6 | n/a | n/a | n/a | n/a |
| url | 0.208 | 0.172 | n/a | n/a | n/a | n/a | 6.5 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.081 | 0.076 | 0.068 | 0.081 | n/a | n/a | 2.4 | 2.6 | 2.0 | 7.8 | n/a | n/a |

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
| parallel_collatz | 1 | 0.402 (0.397-0.404) | 0.402 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.220 (0.218-0.221) | 0.411 | 1.83x | 92 % | 1.02x | same |
| parallel_collatz | 4 | 0.134 (0.134-0.134) | 0.474 | 3.00x | 75 % | 1.18x | same |
| streams_parallel | 1 | 0.445 (0.438-0.465) | 0.444 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.228 (0.227-0.230) | 0.445 | 1.95x | 98 % | 1.00x | same |
| streams_parallel | 4 | 0.147 (0.145-0.147) | 0.554 | 3.03x | 76 % | 1.25x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.535 (2.504-2.585) | 3.941 | 431.6 | 32,936,964,885 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
| 2026-10-25T09:03:06Z | `148472c2cd` | main | 32,936,964,885 | 2.535 | [json](history/2026-10-25-148472c2cdb0.json) |
| 2026-10-24T08:45:58Z | `148472c2cd` | main | 32,941,665,170 | 2.841 | [json](history/2026-10-24-148472c2cdb0.json) |
| 2026-10-23T09:15:05Z | `148472c2cd` | main | 32,944,434,877 | 3.020 | [json](history/2026-10-23-148472c2cdb0.json) |
| 2026-10-22T09:19:15Z | `148472c2cd` | main | 32,948,490,800 | 2.785 | [json](history/2026-10-22-148472c2cdb0.json) |
| 2026-10-21T09:18:17Z | `148472c2cd` | main | 32,944,599,759 | 3.076 | [json](history/2026-10-21-148472c2cdb0.json) |
| 2026-10-20T09:18:44Z | `4fca791aa7` | main | 32,689,556,132 | 3.135 | [json](history/2026-10-20-4fca791aa730.json) |
| 2026-10-19T09:42:12Z | `4fca791aa7` | main | 32,690,856,642 | 2.491 | [json](history/2026-10-19-4fca791aa730.json) |
| 2026-10-18T08:41:01Z | `f9a96b20cf` | main | 32,474,433,787 | 2.653 | [json](history/2026-10-18-f9a96b20cf4a.json) |
