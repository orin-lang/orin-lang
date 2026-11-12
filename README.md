# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

26 runs, 2026-10-18 to 2026-11-12. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-11-12T12:13:12Z. Machine: AMD EPYC 9V45 96-Core Processor, 4 cores, 15.6 GiB, Linux-7.0.0-1017-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.005 (0.005-0.005) | 0.004 (0.004-0.007) | 0.004 (0.003-0.004) | 0.006 (0.006-0.007) | 0.053 (0.042-0.064) | 0.003 (0.003-0.003) |
| bintrees | 0.235 (0.232-0.237) | 0.223 (0.218-0.225) | 0.290 (0.288-0.296) | 0.698 (0.693-0.723) | 0.214 (0.209-0.220) | 0.383 (0.374-0.392) |
| bytesstr | 0.023 (0.023-0.023) | 0.020 (0.019-0.024) | 0.015 (0.015-0.015) | 0.005 (0.005-0.006) | 0.072 (0.071-0.080) | 0.029 (0.028-0.030) |
| fib | 0.184 (0.179-0.188) | 0.201 (0.198-0.206) | 0.101 (0.101-0.102) | 0.356 (0.355-0.377) | 0.260 (0.254-0.265) | 0.195 (0.192-0.196) |
| html | 0.086 (0.083-0.125) | 0.071 (0.069-0.071) | 0.081 (0.079-0.084) | 0.133 (0.130-0.135) | n/a | n/a |
| html_hand | 0.071 (0.070-0.073) | 0.051 (0.050-0.053) | n/a | n/a | n/a | n/a |
| http_parse | 0.065 (0.064-0.065) | 0.052 (0.052-0.055) | n/a | n/a | n/a | n/a |
| mapfreq | 0.089 (0.089-0.090) | 0.089 (0.089-0.090) | 0.044 (0.044-0.045) | 0.063 (0.062-0.063) | n/a | n/a |
| mutres | 0.085 (0.084-0.087) | 0.054 (0.053-0.054) | 0.020 (0.020-0.020) | 0.022 (0.022-0.027) | 0.055 (0.054-0.060) | 0.026 (0.025-0.028) |
| nbody | 0.045 (0.045-0.046) | 0.043 (0.042-0.043) | 0.044 (0.044-0.045) | 0.055 (0.054-0.055) | n/a | n/a |
| pqueue | 0.090 (0.089-0.101) | 0.073 (0.071-0.075) | 0.048 (0.047-0.048) | 0.123 (0.120-0.128) | 0.154 (0.151-0.157) | 0.053 (0.052-0.054) |
| qsort_func | 0.144 (0.143-0.146) | 0.139 (0.138-0.142) | 0.162 (0.162-0.166) | 0.252 (0.240-0.270) | n/a | n/a |
| qsort_inplace | 0.080 (0.079-0.081) | 0.079 (0.078-0.080) | 0.068 (0.067-0.070) | 0.078 (0.077-0.080) | n/a | n/a |
| sieve | 0.072 (0.070-0.074) | 0.070 (0.069-0.078) | 0.067 (0.067-0.069) | 0.144 (0.137-0.160) | 0.119 (0.113-0.119) | 0.068 (0.067-0.069) |
| sortedmap | 0.147 (0.146-0.148) | 0.148 (0.148-0.150) | n/a | n/a | n/a | n/a |
| streams | 0.081 (0.081-0.083) | 0.069 (0.069-0.070) | n/a | n/a | n/a | n/a |
| strings | 0.049 (0.048-0.049) | 0.044 (0.044-0.044) | 0.041 (0.040-0.042) | 0.043 (0.037-0.045) | 0.165 (0.161-0.169) | 0.018 (0.018-0.019) |
| tasks | 2.859 (2.774-2.927) | 2.841 (2.811-2.900) | n/a | n/a | n/a | n/a |
| url | 0.205 (0.200-0.208) | 0.167 (0.163-0.171) | n/a | n/a | n/a | n/a |
| wordfreq | 0.076 (0.074-0.082) | 0.072 (0.071-0.089) | 0.062 (0.062-0.066) | 0.077 (0.074-0.078) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.38x | 1.18x | 1.69x | 14.90x | 0.78x |
| bintrees | 0.81x | 0.77x | 2.40x | 0.74x | 1.32x |
| bytesstr | 1.51x | 1.30x | 0.35x | 4.76x | 1.89x |
| fib | 1.82x | 1.99x | 3.53x | 2.58x | 1.94x |
| html | 1.06x | 0.87x | 1.63x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.01x | 2.01x | 1.42x | n/a | n/a |
| mutres | 4.28x | 2.71x | 1.13x | 2.79x | 1.29x |
| nbody | 1.02x | 0.96x | 1.24x | n/a | n/a |
| pqueue | 1.88x | 1.53x | 2.57x | 3.24x | 1.10x |
| qsort_func | 0.89x | 0.86x | 1.55x | n/a | n/a |
| qsort_inplace | 1.17x | 1.16x | 1.14x | n/a | n/a |
| sieve | 1.07x | 1.04x | 2.13x | 1.76x | 1.01x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.17x | 1.07x | 1.04x | 3.99x | 0.45x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.22x | 1.16x | 1.25x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.005 | 0.004 | 0.003 | 0.008 | 0.070 | 0.003 | 4.6 | 4.9 | 4.9 | 7.2 | 47.9 | 5.0 |
| bintrees | 0.234 | 0.222 | 0.290 | 1.497 | 0.252 | 0.383 | 17.6 | 17.9 | 9.7 | 12.8 | 301.1 | 10.1 |
| bytesstr | 0.023 | 0.019 | 0.015 | 0.007 | 0.083 | 0.028 | 11.6 | 11.8 | 11.7 | 6.3 | 104.3 | 4.9 |
| fib | 0.183 | 0.200 | 0.101 | 0.357 | 0.268 | 0.195 | 1.6 | 1.9 | 1.6 | 1.7 | 38.7 | 2.0 |
| html | 0.086 | 0.070 | 0.081 | 0.178 | n/a | n/a | 3.9 | 4.2 | 2.2 | 7.6 | n/a | n/a |
| html_hand | 0.070 | 0.051 | n/a | n/a | n/a | n/a | 2.5 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.064 | 0.052 | n/a | n/a | n/a | n/a | 1.7 | 2.1 | n/a | n/a | n/a | n/a |
| mapfreq | 0.089 | 0.089 | 0.044 | 0.071 | n/a | n/a | 11.4 | 11.7 | 5.1 | 7.2 | n/a | n/a |
| mutres | 0.085 | 0.053 | 0.020 | 0.022 | 0.074 | 0.025 | 1.6 | 1.9 | 1.6 | 1.7 | 39.0 | 2.1 |
| nbody | 0.045 | 0.042 | 0.044 | 0.055 | n/a | n/a | 1.9 | 1.9 | 2.0 | 1.8 | n/a | n/a |
| pqueue | 0.089 | 0.073 | 0.047 | 0.129 | 0.197 | 0.052 | 6.2 | 6.5 | 4.9 | 14.9 | 62.1 | 5.0 |
| qsort_func | 0.144 | 0.138 | 0.162 | 0.307 | n/a | n/a | 36.5 | 36.8 | 23.8 | 37.6 | n/a | n/a |
| qsort_inplace | 0.080 | 0.078 | 0.068 | 0.087 | n/a | n/a | 16.8 | 17.1 | 16.9 | 24.3 | n/a | n/a |
| sieve | 0.072 | 0.070 | 0.067 | 0.242 | 0.140 | 0.068 | 77.8 | 78.1 | 77.7 | 185.9 | 116.0 | 78.4 |
| sortedmap | 0.146 | 0.148 | n/a | n/a | n/a | n/a | 11.3 | 11.5 | n/a | n/a | n/a | n/a |
| streams | 0.081 | 0.069 | n/a | n/a | n/a | n/a | 39.8 | 40.0 | n/a | n/a | n/a | n/a |
| strings | 0.048 | 0.043 | 0.041 | 0.051 | 0.312 | 0.018 | 46.2 | 46.5 | 34.7 | 23.3 | 139.3 | 20.0 |
| tasks | 3.334 | 3.315 | n/a | n/a | n/a | n/a | 14.3 | 14.6 | n/a | n/a | n/a | n/a |
| url | 0.205 | 0.166 | n/a | n/a | n/a | n/a | 6.5 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.075 | 0.072 | 0.062 | 0.079 | n/a | n/a | 2.4 | 2.6 | 2.0 | 6.5 | n/a | n/a |

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
| parallel_collatz | 1 | 0.381 (0.374-0.389) | 0.381 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.219 (0.218-0.223) | 0.399 | 1.74x | 87 % | 1.05x | same |
| parallel_collatz | 4 | 0.136 (0.136-0.139) | 0.457 | 2.81x | 70 % | 1.20x | same |
| streams_parallel | 1 | 0.424 (0.416-0.425) | 0.424 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.226 (0.219-0.239) | 0.434 | 1.88x | 94 % | 1.02x | same |
| streams_parallel | 4 | 0.142 (0.141-0.146) | 0.516 | 2.98x | 75 % | 1.22x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.245 (2.218-2.279) | 3.535 | 426.4 | 32,946,589,724 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
| 2026-11-12T12:13:12Z | `148472c2cd` | main | 32,946,589,724 | 2.245 | [json](history/2026-11-12-148472c2cdb0.json) |
| 2026-11-11T11:53:54Z | `148472c2cd` | main | 32,947,093,605 | 3.132 | [json](history/2026-11-11-148472c2cdb0.json) |
| 2026-11-10T12:13:41Z | `148472c2cd` | main | 32,946,478,802 | 2.528 | [json](history/2026-11-10-148472c2cdb0.json) |
| 2026-11-09T12:41:22Z | `148472c2cd` | main | 32,943,133,157 | 3.155 | [json](history/2026-11-09-148472c2cdb0.json) |
| 2026-11-08T11:10:36Z | `148472c2cd` | main | 32,942,986,207 | 2.851 | [json](history/2026-11-08-148472c2cdb0.json) |
| 2026-11-07T11:06:25Z | `148472c2cd` | main | 32,947,521,547 | 2.963 | [json](history/2026-11-07-148472c2cdb0.json) |
| 2026-11-06T11:56:28Z | `148472c2cd` | main | 32,943,001,622 | 2.818 | [json](history/2026-11-06-148472c2cdb0.json) |
| 2026-11-05T11:55:43Z | `148472c2cd` | main | 32,945,209,327 | 2.273 | [json](history/2026-11-05-148472c2cdb0.json) |
| 2026-11-04T12:03:12Z | `148472c2cd` | main | 32,941,929,762 | 3.262 | [json](history/2026-11-04-148472c2cdb0.json) |
| 2026-11-03T11:47:47Z | `148472c2cd` | main | 32,948,784,955 | 3.012 | [json](history/2026-11-03-148472c2cdb0.json) |
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
