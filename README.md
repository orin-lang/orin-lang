# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

21 runs, 2026-10-18 to 2026-11-07. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-11-07T11:06:25Z. Machine: AMD EPYC 7763 64-Core Processor, 4 cores, 15.6 GiB, Linux-7.0.0-1017-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.009 (0.009-0.009) | 0.008 (0.008-0.008) | 0.005 (0.005-0.006) | 0.013 (0.012-0.014) | 0.068 (0.066-0.078) | 0.005 (0.005-0.005) |
| bintrees | 0.397 (0.394-0.399) | 0.397 (0.394-0.401) | 0.542 (0.539-0.543) | 1.298 (1.288-1.308) | 0.335 (0.334-0.339) | 0.712 (0.712-0.717) |
| bytesstr | 0.039 (0.039-0.039) | 0.035 (0.035-0.036) | 0.026 (0.026-0.027) | 0.012 (0.010-0.018) | 0.098 (0.096-0.101) | 0.040 (0.039-0.040) |
| fib | 0.284 (0.284-0.286) | 0.307 (0.306-0.307) | 0.198 (0.198-0.206) | 0.598 (0.595-0.599) | 0.419 (0.418-0.436) | 0.314 (0.314-0.316) |
| html | 0.163 (0.161-0.169) | 0.136 (0.135-0.138) | 0.169 (0.162-0.169) | 0.238 (0.235-0.254) | n/a | n/a |
| html_hand | 0.130 (0.130-0.131) | 0.100 (0.100-0.101) | n/a | n/a | n/a | n/a |
| http_parse | 0.126 (0.125-0.127) | 0.107 (0.106-0.108) | n/a | n/a | n/a | n/a |
| mapfreq | 0.155 (0.154-0.155) | 0.155 (0.154-0.157) | 0.075 (0.074-0.077) | 0.116 (0.115-0.116) | n/a | n/a |
| mutres | 0.164 (0.164-0.164) | 0.102 (0.101-0.102) | 0.031 (0.031-0.032) | 0.045 (0.045-0.045) | 0.086 (0.083-0.096) | 0.038 (0.038-0.038) |
| nbody | 0.077 (0.077-0.077) | 0.079 (0.078-0.079) | 0.070 (0.070-0.070) | 0.088 (0.088-0.088) | n/a | n/a |
| pqueue | 0.150 (0.150-0.151) | 0.125 (0.124-0.127) | 0.064 (0.064-0.064) | 0.201 (0.196-0.203) | 0.241 (0.237-0.245) | 0.090 (0.087-0.091) |
| qsort_func | 0.219 (0.218-0.221) | 0.214 (0.213-0.215) | 0.235 (0.234-0.236) | 0.390 (0.377-0.402) | n/a | n/a |
| qsort_inplace | 0.109 (0.107-0.109) | 0.109 (0.108-0.109) | 0.086 (0.086-0.086) | 0.119 (0.106-0.121) | n/a | n/a |
| sieve | 0.116 (0.113-0.117) | 0.121 (0.118-0.124) | 0.104 (0.103-0.104) | 0.293 (0.246-0.339) | 0.169 (0.167-0.176) | 0.103 (0.103-0.104) |
| sortedmap | 0.248 (0.245-0.248) | 0.254 (0.252-0.256) | n/a | n/a | n/a | n/a |
| streams | 0.133 (0.132-0.134) | 0.110 (0.108-0.110) | n/a | n/a | n/a | n/a |
| strings | 0.077 (0.077-0.077) | 0.074 (0.073-0.076) | 0.075 (0.075-0.075) | 0.078 (0.068-0.085) | 0.235 (0.231-0.238) | 0.031 (0.031-0.032) |
| tasks | 3.977 (3.889-4.131) | 3.997 (3.912-4.035) | n/a | n/a | n/a | n/a |
| url | 0.354 (0.353-0.364) | 0.314 (0.313-0.323) | n/a | n/a | n/a | n/a |
| wordfreq | 0.127 (0.126-0.128) | 0.126 (0.125-0.127) | 0.114 (0.112-0.124) | 0.118 (0.116-0.120) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.65x | 1.49x | 2.41x | 12.62x | 0.86x |
| bintrees | 0.73x | 0.73x | 2.39x | 0.62x | 1.31x |
| bytesstr | 1.51x | 1.36x | 0.45x | 3.79x | 1.52x |
| fib | 1.43x | 1.55x | 3.02x | 2.12x | 1.58x |
| html | 0.96x | 0.81x | 1.41x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.06x | 2.07x | 1.54x | n/a | n/a |
| mutres | 5.23x | 3.24x | 1.43x | 2.74x | 1.20x |
| nbody | 1.10x | 1.12x | 1.25x | n/a | n/a |
| pqueue | 2.35x | 1.96x | 3.15x | 3.77x | 1.40x |
| qsort_func | 0.93x | 0.91x | 1.66x | n/a | n/a |
| qsort_inplace | 1.26x | 1.26x | 1.37x | n/a | n/a |
| sieve | 1.12x | 1.17x | 2.83x | 1.63x | 1.00x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.02x | 0.98x | 1.03x | 3.12x | 0.41x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.11x | 1.11x | 1.04x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.009 | 0.008 | 0.005 | 0.018 | 0.105 | 0.004 | 4.5 | 4.7 | 4.7 | 9.6 | 47.5 | 5.0 |
| bintrees | 0.396 | 0.396 | 0.542 | 2.832 | 0.394 | 0.712 | 17.5 | 17.7 | 9.5 | 12.2 | 300.9 | 10.0 |
| bytesstr | 0.039 | 0.035 | 0.026 | 0.018 | 0.119 | 0.039 | 11.5 | 11.8 | 11.6 | 7.0 | 103.1 | 4.8 |
| fib | 0.283 | 0.306 | 0.198 | 0.601 | 0.433 | 0.313 | 1.5 | 1.7 | 1.5 | 1.6 | 38.5 | 2.0 |
| html | 0.162 | 0.136 | 0.169 | 0.319 | n/a | n/a | 3.7 | 4.1 | 2.1 | 7.4 | n/a | n/a |
| html_hand | 0.130 | 0.100 | n/a | n/a | n/a | n/a | 2.4 | 2.8 | n/a | n/a | n/a | n/a |
| http_parse | 0.125 | 0.107 | n/a | n/a | n/a | n/a | 1.6 | 1.9 | n/a | n/a | n/a | n/a |
| mapfreq | 0.154 | 0.155 | 0.075 | 0.130 | n/a | n/a | 11.3 | 11.5 | 5.0 | 7.3 | n/a | n/a |
| mutres | 0.164 | 0.101 | 0.031 | 0.045 | 0.114 | 0.038 | 1.5 | 1.8 | 1.5 | 1.8 | 38.8 | 2.0 |
| nbody | 0.077 | 0.078 | 0.070 | 0.088 | n/a | n/a | 1.8 | 1.8 | 1.8 | 1.7 | n/a | n/a |
| pqueue | 0.150 | 0.124 | 0.064 | 0.215 | 0.317 | 0.090 | 6.1 | 6.4 | 4.7 | 14.8 | 61.9 | 4.9 |
| qsort_func | 0.218 | 0.213 | 0.235 | 0.490 | n/a | n/a | 36.4 | 36.6 | 23.7 | 41.3 | n/a | n/a |
| qsort_inplace | 0.108 | 0.108 | 0.086 | 0.147 | n/a | n/a | 16.7 | 17.0 | 16.7 | 28.5 | n/a | n/a |
| sieve | 0.116 | 0.120 | 0.103 | 0.428 | 0.196 | 0.103 | 77.7 | 78.0 | 77.6 | 250.1 | 115.9 | 78.2 |
| sortedmap | 0.247 | 0.254 | n/a | n/a | n/a | n/a | 11.1 | 11.4 | n/a | n/a | n/a | n/a |
| streams | 0.133 | 0.109 | n/a | n/a | n/a | n/a | 39.6 | 39.9 | n/a | n/a | n/a | n/a |
| strings | 0.077 | 0.073 | 0.075 | 0.102 | 0.455 | 0.030 | 46.1 | 46.4 | 34.6 | 23.5 | 139.4 | 19.9 |
| tasks | 4.697 | 4.738 | n/a | n/a | n/a | n/a | 14.2 | 14.4 | n/a | n/a | n/a | n/a |
| url | 0.353 | 0.313 | n/a | n/a | n/a | n/a | 6.4 | 6.7 | n/a | n/a | n/a | n/a |
| wordfreq | 0.126 | 0.126 | 0.113 | 0.121 | n/a | n/a | 2.2 | 2.6 | 1.8 | 6.3 | n/a | n/a |

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
| parallel_collatz | 1 | 0.501 (0.499-0.502) | 0.500 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.296 (0.295-0.296) | 0.534 | 1.69x | 85 % | 1.07x | same |
| parallel_collatz | 4 | 0.193 (0.191-0.204) | 0.649 | 2.59x | 65 % | 1.30x | same |
| streams_parallel | 1 | 0.491 (0.490-0.492) | 0.490 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.259 (0.258-0.259) | 0.493 | 1.89x | 95 % | 1.01x | same |
| streams_parallel | 4 | 0.183 (0.182-0.205) | 0.656 | 2.69x | 67 % | 1.34x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.963 (2.943-3.006) | 5.330 | 425.9 | 32,947,521,547 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
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
