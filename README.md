# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

18 runs, 2026-10-18 to 2026-11-04. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-11-04T12:03:12Z. Machine: AMD EPYC 7763 64-Core Processor, 4 cores, 15.6 GiB, Linux-7.0.0-1017-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.009 (0.009-0.010) | 0.008 (0.008-0.008) | 0.006 (0.006-0.007) | 0.012 (0.010-0.016) | 0.071 (0.063-0.077) | 0.005 (0.005-0.005) |
| bintrees | 0.410 (0.410-0.420) | 0.405 (0.404-0.417) | 0.544 (0.539-0.548) | 1.342 (1.321-1.352) | 0.358 (0.352-0.368) | 0.725 (0.714-0.734) |
| bytesstr | 0.039 (0.038-0.040) | 0.035 (0.034-0.035) | 0.024 (0.024-0.025) | 0.010 (0.009-0.019) | 0.106 (0.105-0.120) | 0.039 (0.039-0.040) |
| fib | 0.284 (0.284-0.284) | 0.307 (0.307-0.307) | 0.199 (0.199-0.199) | 0.603 (0.601-0.604) | 0.444 (0.438-0.446) | 0.317 (0.316-0.317) |
| html | 0.164 (0.163-0.165) | 0.136 (0.135-0.138) | 0.169 (0.166-0.175) | 0.238 (0.235-0.243) | n/a | n/a |
| html_hand | 0.132 (0.131-0.134) | 0.102 (0.101-0.105) | n/a | n/a | n/a | n/a |
| http_parse | 0.129 (0.126-0.131) | 0.112 (0.111-0.116) | n/a | n/a | n/a | n/a |
| mapfreq | 0.156 (0.155-0.158) | 0.156 (0.155-0.159) | 0.077 (0.075-0.078) | 0.117 (0.116-0.118) | n/a | n/a |
| mutres | 0.167 (0.165-0.168) | 0.102 (0.101-0.103) | 0.033 (0.032-0.033) | 0.045 (0.045-0.046) | 0.086 (0.081-0.093) | 0.039 (0.039-0.039) |
| nbody | 0.077 (0.077-0.078) | 0.079 (0.078-0.079) | 0.070 (0.070-0.070) | 0.088 (0.088-0.089) | n/a | n/a |
| pqueue | 0.152 (0.150-0.161) | 0.129 (0.126-0.138) | 0.065 (0.064-0.066) | 0.204 (0.200-0.208) | 0.255 (0.240-0.262) | 0.093 (0.090-0.095) |
| qsort_func | 0.223 (0.222-0.224) | 0.222 (0.218-0.223) | 0.240 (0.239-0.241) | 0.405 (0.400-0.427) | n/a | n/a |
| qsort_inplace | 0.111 (0.111-0.113) | 0.112 (0.111-0.112) | 0.090 (0.089-0.090) | 0.116 (0.111-0.127) | n/a | n/a |
| sieve | 0.137 (0.131-0.156) | 0.147 (0.139-0.151) | 0.128 (0.125-0.134) | 0.322 (0.279-0.361) | 0.199 (0.191-0.200) | 0.124 (0.122-0.125) |
| sortedmap | 0.251 (0.250-0.270) | 0.263 (0.259-0.272) | n/a | n/a | n/a | n/a |
| streams | 0.142 (0.138-0.147) | 0.124 (0.123-0.127) | n/a | n/a | n/a | n/a |
| strings | 0.082 (0.080-0.083) | 0.079 (0.078-0.082) | 0.079 (0.078-0.080) | 0.084 (0.075-0.095) | 0.248 (0.246-0.256) | 0.034 (0.033-0.035) |
| tasks | 4.052 (4.012-4.078) | 3.983 (3.943-4.052) | n/a | n/a | n/a | n/a |
| url | 0.358 (0.358-0.361) | 0.317 (0.315-0.317) | n/a | n/a | n/a | n/a |
| wordfreq | 0.127 (0.126-0.128) | 0.124 (0.124-0.125) | 0.113 (0.111-0.121) | 0.120 (0.118-0.121) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.47x | 1.28x | 1.87x | 11.37x | 0.76x |
| bintrees | 0.75x | 0.74x | 2.47x | 0.66x | 1.33x |
| bytesstr | 1.60x | 1.43x | 0.39x | 4.38x | 1.60x |
| fib | 1.43x | 1.55x | 3.03x | 2.23x | 1.59x |
| html | 0.97x | 0.81x | 1.41x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.02x | 2.02x | 1.52x | n/a | n/a |
| mutres | 5.10x | 3.10x | 1.38x | 2.63x | 1.19x |
| nbody | 1.11x | 1.12x | 1.26x | n/a | n/a |
| pqueue | 2.34x | 1.98x | 3.14x | 3.91x | 1.43x |
| qsort_func | 0.93x | 0.93x | 1.69x | n/a | n/a |
| qsort_inplace | 1.24x | 1.25x | 1.29x | n/a | n/a |
| sieve | 1.07x | 1.15x | 2.51x | 1.55x | 0.97x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.05x | 1.01x | 1.06x | 3.15x | 0.43x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.12x | 1.10x | 1.06x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.009 | 0.008 | 0.006 | 0.017 | 0.107 | 0.004 | 4.5 | 4.7 | 4.7 | 7.9 | 47.5 | 5.0 |
| bintrees | 0.409 | 0.404 | 0.543 | 2.933 | 0.428 | 0.725 | 17.5 | 17.7 | 9.5 | 13.0 | 301.0 | 10.1 |
| bytesstr | 0.038 | 0.034 | 0.024 | 0.014 | 0.127 | 0.039 | 11.5 | 11.7 | 11.6 | 6.2 | 104.5 | 4.8 |
| fib | 0.283 | 0.307 | 0.198 | 0.604 | 0.459 | 0.316 | 1.5 | 1.8 | 1.5 | 1.7 | 38.5 | 2.0 |
| html | 0.163 | 0.136 | 0.169 | 0.312 | n/a | n/a | 3.7 | 4.1 | 2.1 | 7.5 | n/a | n/a |
| html_hand | 0.132 | 0.101 | n/a | n/a | n/a | n/a | 2.4 | 2.7 | n/a | n/a | n/a | n/a |
| http_parse | 0.129 | 0.111 | n/a | n/a | n/a | n/a | 1.6 | 1.9 | n/a | n/a | n/a | n/a |
| mapfreq | 0.156 | 0.156 | 0.077 | 0.134 | n/a | n/a | 11.3 | 11.5 | 5.0 | 7.3 | n/a | n/a |
| mutres | 0.167 | 0.101 | 0.032 | 0.046 | 0.119 | 0.039 | 1.5 | 1.8 | 1.5 | 1.7 | 38.9 | 2.0 |
| nbody | 0.077 | 0.078 | 0.070 | 0.089 | n/a | n/a | 1.8 | 1.8 | 1.8 | 1.8 | n/a | n/a |
| pqueue | 0.151 | 0.128 | 0.065 | 0.217 | 0.324 | 0.092 | 6.1 | 6.4 | 4.7 | 14.7 | 61.2 | 5.0 |
| qsort_func | 0.222 | 0.222 | 0.239 | 0.501 | n/a | n/a | 36.4 | 36.7 | 23.7 | 38.6 | n/a | n/a |
| qsort_inplace | 0.111 | 0.112 | 0.089 | 0.142 | n/a | n/a | 16.7 | 17.0 | 16.7 | 26.2 | n/a | n/a |
| sieve | 0.137 | 0.147 | 0.128 | 0.501 | 0.226 | 0.124 | 77.7 | 78.0 | 77.6 | 226.9 | 115.9 | 78.2 |
| sortedmap | 0.251 | 0.262 | n/a | n/a | n/a | n/a | 11.1 | 11.4 | n/a | n/a | n/a | n/a |
| streams | 0.141 | 0.124 | n/a | n/a | n/a | n/a | 39.6 | 39.9 | n/a | n/a | n/a | n/a |
| strings | 0.082 | 0.079 | 0.078 | 0.108 | 0.473 | 0.033 | 46.1 | 46.3 | 34.6 | 23.5 | 139.2 | 19.8 |
| tasks | 4.715 | 4.626 | n/a | n/a | n/a | n/a | 14.2 | 14.4 | n/a | n/a | n/a | n/a |
| url | 0.358 | 0.316 | n/a | n/a | n/a | n/a | 6.4 | 6.7 | n/a | n/a | n/a | n/a |
| wordfreq | 0.126 | 0.124 | 0.112 | 0.123 | n/a | n/a | 2.2 | 2.5 | 1.9 | 6.6 | n/a | n/a |

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
| parallel_collatz | 1 | 0.504 (0.504-0.505) | 0.504 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.300 (0.300-0.302) | 0.541 | 1.68x | 84 % | 1.07x | same |
| parallel_collatz | 4 | 0.195 (0.192-0.196) | 0.653 | 2.59x | 65 % | 1.30x | same |
| streams_parallel | 1 | 0.495 (0.494-0.495) | 0.494 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.262 (0.262-0.263) | 0.497 | 1.89x | 94 % | 1.01x | same |
| streams_parallel | 4 | 0.186 (0.186-0.187) | 0.661 | 2.66x | 66 % | 1.34x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 3.262 (3.232-3.323) | 5.660 | 426.2 | 32,941,929,762 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
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
