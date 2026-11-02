# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

16 runs, 2026-10-18 to 2026-11-02. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-11-02T12:05:49Z. Machine: AMD EPYC 9V45 96-Core Processor, 4 cores, 15.6 GiB, Linux-7.0.0-1017-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.006 (0.005-0.006) | 0.005 (0.005-0.006) | 0.005 (0.004-0.008) | 0.008 (0.007-0.009) | 0.057 (0.044-0.061) | 0.003 (0.003-0.003) |
| bintrees | 0.241 (0.240-0.243) | 0.231 (0.230-0.233) | 0.306 (0.303-0.320) | 0.746 (0.719-0.889) | 0.221 (0.218-0.269) | 0.389 (0.386-0.394) |
| bytesstr | 0.024 (0.024-0.024) | 0.020 (0.020-0.021) | 0.016 (0.016-0.019) | 0.006 (0.005-0.007) | 0.072 (0.071-0.088) | 0.030 (0.030-0.031) |
| fib | 0.183 (0.180-0.193) | 0.204 (0.195-0.205) | 0.101 (0.100-0.108) | 0.370 (0.367-0.394) | 0.270 (0.263-0.290) | 0.198 (0.196-0.202) |
| html | 0.087 (0.087-0.088) | 0.072 (0.071-0.073) | 0.082 (0.079-0.085) | 0.134 (0.134-0.138) | n/a | n/a |
| html_hand | 0.070 (0.070-0.071) | 0.052 (0.052-0.054) | n/a | n/a | n/a | n/a |
| http_parse | 0.068 (0.067-0.068) | 0.054 (0.054-0.055) | n/a | n/a | n/a | n/a |
| mapfreq | 0.091 (0.091-0.093) | 0.089 (0.087-0.090) | 0.047 (0.047-0.048) | 0.065 (0.064-0.067) | n/a | n/a |
| mutres | 0.083 (0.082-0.091) | 0.052 (0.051-0.056) | 0.020 (0.020-0.020) | 0.023 (0.022-0.025) | 0.057 (0.056-0.065) | 0.025 (0.025-0.026) |
| nbody | 0.045 (0.045-0.045) | 0.045 (0.045-0.045) | 0.044 (0.044-0.044) | 0.058 (0.057-0.059) | n/a | n/a |
| pqueue | 0.089 (0.089-0.090) | 0.073 (0.072-0.073) | 0.048 (0.047-0.048) | 0.127 (0.125-0.131) | 0.152 (0.140-0.156) | 0.055 (0.054-0.055) |
| qsort_func | 0.144 (0.142-0.146) | 0.144 (0.138-0.146) | 0.162 (0.157-0.167) | 0.244 (0.240-0.246) | n/a | n/a |
| qsort_inplace | 0.085 (0.083-0.086) | 0.083 (0.082-0.084) | 0.071 (0.069-0.073) | 0.084 (0.082-0.085) | n/a | n/a |
| sieve | 0.072 (0.072-0.074) | 0.072 (0.070-0.073) | 0.069 (0.069-0.070) | 0.163 (0.143-0.170) | 0.123 (0.120-0.126) | 0.070 (0.070-0.071) |
| sortedmap | 0.155 (0.153-0.161) | 0.156 (0.154-0.158) | n/a | n/a | n/a | n/a |
| streams | 0.080 (0.075-0.082) | 0.070 (0.069-0.073) | n/a | n/a | n/a | n/a |
| strings | 0.049 (0.048-0.050) | 0.046 (0.045-0.047) | 0.043 (0.042-0.044) | 0.043 (0.039-0.051) | 0.170 (0.157-0.182) | 0.019 (0.019-0.020) |
| tasks | 2.903 (2.782-3.011) | 2.875 (2.812-2.953) | n/a | n/a | n/a | n/a |
| url | 0.209 (0.203-0.214) | 0.171 (0.169-0.173) | n/a | n/a | n/a | n/a |
| wordfreq | 0.078 (0.077-0.079) | 0.073 (0.073-0.074) | 0.065 (0.062-0.065) | 0.079 (0.078-0.080) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.39x | 1.17x | 1.69x | 12.58x | 0.65x |
| bintrees | 0.79x | 0.75x | 2.44x | 0.72x | 1.27x |
| bytesstr | 1.50x | 1.27x | 0.38x | 4.48x | 1.88x |
| fib | 1.80x | 2.01x | 3.65x | 2.66x | 1.96x |
| html | 1.06x | 0.88x | 1.64x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 1.96x | 1.90x | 1.40x | n/a | n/a |
| mutres | 4.18x | 2.64x | 1.15x | 2.87x | 1.28x |
| nbody | 1.03x | 1.02x | 1.31x | n/a | n/a |
| pqueue | 1.88x | 1.53x | 2.67x | 3.18x | 1.15x |
| qsort_func | 0.89x | 0.89x | 1.51x | n/a | n/a |
| qsort_inplace | 1.19x | 1.16x | 1.18x | n/a | n/a |
| sieve | 1.05x | 1.05x | 2.36x | 1.78x | 1.02x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.14x | 1.07x | 0.99x | 3.96x | 0.45x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.20x | 1.13x | 1.22x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.005 | 0.004 | 0.004 | 0.009 | 0.071 | 0.003 | 4.6 | 4.8 | 4.9 | 7.7 | 48.3 | 5.2 |
| bintrees | 0.240 | 0.230 | 0.306 | 1.580 | 0.256 | 0.389 | 17.6 | 17.9 | 9.7 | 12.8 | 301.2 | 10.1 |
| bytesstr | 0.024 | 0.020 | 0.016 | 0.008 | 0.085 | 0.030 | 11.6 | 11.8 | 11.7 | 6.3 | 103.1 | 5.0 |
| fib | 0.182 | 0.203 | 0.101 | 0.370 | 0.276 | 0.198 | 1.6 | 1.9 | 1.6 | 1.7 | 38.5 | 2.0 |
| html | 0.087 | 0.072 | 0.082 | 0.177 | n/a | n/a | 3.9 | 4.2 | 2.2 | 7.5 | n/a | n/a |
| html_hand | 0.070 | 0.052 | n/a | n/a | n/a | n/a | 2.5 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.067 | 0.054 | n/a | n/a | n/a | n/a | 1.7 | 2.1 | n/a | n/a | n/a | n/a |
| mapfreq | 0.091 | 0.089 | 0.046 | 0.073 | n/a | n/a | 11.4 | 11.7 | 5.1 | 7.7 | n/a | n/a |
| mutres | 0.083 | 0.052 | 0.020 | 0.023 | 0.078 | 0.025 | 1.6 | 1.9 | 1.6 | 1.7 | 39.1 | 2.1 |
| nbody | 0.045 | 0.045 | 0.044 | 0.058 | n/a | n/a | 1.9 | 1.9 | 2.0 | 1.8 | n/a | n/a |
| pqueue | 0.089 | 0.073 | 0.047 | 0.132 | 0.196 | 0.054 | 6.2 | 6.5 | 4.9 | 14.7 | 62.1 | 5.0 |
| qsort_func | 0.144 | 0.144 | 0.162 | 0.301 | n/a | n/a | 36.5 | 36.8 | 23.8 | 36.6 | n/a | n/a |
| qsort_inplace | 0.085 | 0.083 | 0.071 | 0.094 | n/a | n/a | 16.8 | 17.1 | 16.9 | 24.4 | n/a | n/a |
| sieve | 0.072 | 0.072 | 0.069 | 0.274 | 0.145 | 0.070 | 77.8 | 78.1 | 77.7 | 185.8 | 115.9 | 78.4 |
| sortedmap | 0.155 | 0.155 | n/a | n/a | n/a | n/a | 11.3 | 11.5 | n/a | n/a | n/a | n/a |
| streams | 0.079 | 0.069 | n/a | n/a | n/a | n/a | 39.8 | 40.0 | n/a | n/a | n/a | n/a |
| strings | 0.049 | 0.046 | 0.043 | 0.051 | 0.322 | 0.019 | 46.2 | 46.5 | 34.7 | 23.8 | 139.3 | 20.0 |
| tasks | 3.379 | 3.343 | n/a | n/a | n/a | n/a | 14.2 | 14.6 | n/a | n/a | n/a | n/a |
| url | 0.207 | 0.170 | n/a | n/a | n/a | n/a | 6.5 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.078 | 0.073 | 0.064 | 0.081 | n/a | n/a | 2.4 | 2.6 | 2.0 | 6.5 | n/a | n/a |

### Executed instructions (valgrind; the regression metric)

| benchmark | Orin C | Orin LLVM | C | Orin C/C | Orin LLVM/C | note |
|---|---:|---:|---:|---:|---:|---|
| appends | 63,532,173 | 44,305,018 | 25,381,150 | 2.50x | 1.75x |  |
| bintrees | 4,323,683,959 | 4,219,297,433 | 7,242,293,438 | 0.60x | 0.58x |  |
| bytesstr | 349,909,247 | 259,440,726 | 178,695,502 | 1.96x | 1.45x |  |
| fib | 3,200,320,076 | 2,483,953,618 | 3,170,983,191 | 1.01x | 0.78x |  |
| html | 1,786,500,088 | 1,465,345,195 | 1,581,660,490 | 1.13x | 0.93x |  |
| html_hand | 1,335,187,118 | 980,559,871 | n/a | n/a | n/a |  |
| http_parse | 1,494,543,487 | 1,314,023,622 | n/a | n/a | n/a |  |
| mapfreq | 1,050,476,701 | 993,975,269 | 719,855,461 | 1.46x | 1.38x |  |
| mutres | 2,300,282,894 | 1,420,255,452 | 291,450,124 | 7.89x | 4.87x |  |
| nbody | 850,321,975 | 772,258,372 | 651,230,691 | 1.31x | 1.19x |  |
| pqueue | 1,383,801,416 | 1,349,545,582 | 355,213,566 | 3.90x | 3.80x |  |
| qsort_func | 1,335,897,346 | 1,268,411,938 | 1,528,677,738 | 0.87x | 0.83x |  |
| qsort_inplace | 563,393,101 | 521,077,328 | 273,751,964 | 2.06x | 1.90x |  |
| sieve | 443,198,013 | 456,725,927 | 191,756,537 | 2.31x | 2.38x |  |
| sortedmap | 1,354,678,419 | 1,354,047,042 | n/a | n/a | n/a |  |
| streams | 1,173,757,205 | 1,173,731,122 | n/a | n/a | n/a |  |
| strings | 647,534,749 | 558,940,686 | 685,893,535 | 0.94x | 0.81x |  |
| tasks | n/a | n/a | n/a | n/a | n/a | llvm skipped: multi-threaded (20,000 tasks, channels): valgrind serialises threads, so the count would include scheduler waits; orin skipped: multi-threaded (20,000 tasks, channels): valgrind serialises threads, so the count would include scheduler waits |
| url | 4,455,707,359 | 4,066,090,862 | n/a | n/a | n/a |  |
| wordfreq | 760,380,161 | 706,684,023 | 880,390,194 | 0.86x | 0.80x |  |

### Parallel speedup (std:task; worker threads = first argument of the program)

| benchmark | threads | wall s (min-max) | CPU s (user+sys) | speedup | efficiency | CPU vs 1 thread | output |
|---|---:|---:|---:|---:|---:|---:|---|
| parallel_collatz | 1 | 0.395 (0.385-0.397) | 0.395 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.227 (0.226-0.229) | 0.415 | 1.74x | 87 % | 1.05x | same |
| parallel_collatz | 4 | 0.142 (0.141-0.156) | 0.477 | 2.79x | 70 % | 1.21x | same |
| streams_parallel | 1 | 0.435 (0.432-0.436) | 0.434 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.228 (0.226-0.230) | 0.438 | 1.90x | 95 % | 1.01x | same |
| streams_parallel | 4 | 0.148 (0.147-0.150) | 0.537 | 2.94x | 73 % | 1.24x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.307 (2.236-2.448) | 3.614 | 426.4 | 32,932,422,001 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
| 2026-11-02T12:05:49Z | `148472c2cd` | main | 32,932,422,001 | 2.307 | [json](history/2026-11-02-148472c2cdb0.json) |
| 2026-11-01T11:14:05Z | `148472c2cd` | main | 32,942,553,657 | 2.842 | [json](history/2026-11-01-148472c2cdb0.json) |
| 2026-10-31T10:16:06Z | `148472c2cd` | main | 32,947,431,130 | 2.238 | [json](history/2026-10-31-148472c2cdb0.json) |
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
