# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

12 runs, 2026-10-18 to 2026-10-29. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-10-29T10:55:59Z. Machine: INTEL(R) XEON(R) PLATINUM 8573C, 4 cores, 15.6 GiB, Linux-7.0.0-1017-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.007 (0.007-0.007) | 0.007 (0.007-0.007) | 0.005 (0.005-0.005) | 0.011 (0.010-0.012) | 0.080 (0.072-0.083) | 0.004 (0.004-0.007) |
| bintrees | 0.486 (0.484-0.501) | 0.519 (0.517-0.520) | 0.571 (0.571-0.572) | 1.224 (1.219-1.233) | 0.387 (0.383-0.394) | 0.729 (0.727-0.732) |
| bytesstr | 0.055 (0.050-0.071) | 0.047 (0.045-0.053) | 0.052 (0.052-0.060) | 0.011 (0.010-0.012) | 0.114 (0.109-0.125) | 0.036 (0.035-0.038) |
| fib | 0.368 (0.367-0.368) | 0.336 (0.336-0.336) | 0.179 (0.178-0.185) | 0.597 (0.597-0.600) | 0.550 (0.549-0.554) | 0.325 (0.324-0.328) |
| html | 0.150 (0.149-0.151) | 0.128 (0.126-0.131) | 0.150 (0.150-0.152) | 0.271 (0.266-0.277) | n/a | n/a |
| html_hand | 0.132 (0.131-0.132) | 0.096 (0.095-0.096) | n/a | n/a | n/a | n/a |
| http_parse | 0.114 (0.113-0.115) | 0.097 (0.096-0.100) | n/a | n/a | n/a | n/a |
| mapfreq | 0.145 (0.144-0.145) | 0.146 (0.145-0.147) | 0.067 (0.066-0.070) | 0.106 (0.105-0.106) | n/a | n/a |
| mutres | 0.130 (0.130-0.131) | 0.091 (0.090-0.092) | 0.026 (0.026-0.027) | 0.078 (0.077-0.078) | 0.087 (0.083-0.089) | 0.030 (0.030-0.032) |
| nbody | 0.061 (0.061-0.061) | 0.060 (0.060-0.061) | 0.058 (0.058-0.058) | 0.093 (0.092-0.093) | n/a | n/a |
| pqueue | 0.153 (0.153-0.154) | 0.113 (0.112-0.114) | 0.077 (0.077-0.077) | 0.193 (0.191-0.194) | 0.262 (0.258-0.268) | 0.088 (0.088-0.090) |
| qsort_func | 0.238 (0.237-0.239) | 0.241 (0.240-0.242) | 0.258 (0.257-0.259) | 0.430 (0.409-0.439) | n/a | n/a |
| qsort_inplace | 0.131 (0.130-0.132) | 0.127 (0.126-0.127) | 0.102 (0.101-0.104) | 0.120 (0.115-0.120) | n/a | n/a |
| sieve | 0.178 (0.175-0.189) | 0.176 (0.171-0.185) | 0.166 (0.156-0.170) | 0.309 (0.293-0.320) | 0.238 (0.232-0.240) | 0.168 (0.166-0.179) |
| sortedmap | 0.254 (0.253-0.254) | 0.255 (0.255-0.256) | n/a | n/a | n/a | n/a |
| streams | 0.152 (0.141-0.153) | 0.121 (0.114-0.124) | n/a | n/a | n/a | n/a |
| strings | 0.071 (0.070-0.073) | 0.062 (0.062-0.066) | 0.067 (0.066-0.069) | 0.064 (0.058-0.067) | 0.245 (0.242-0.259) | 0.029 (0.029-0.032) |
| tasks | 4.927 (4.123-5.019) | 4.934 (4.420-5.003) | n/a | n/a | n/a | n/a |
| url | 0.334 (0.332-0.341) | 0.321 (0.320-0.323) | n/a | n/a | n/a | n/a |
| wordfreq | 0.113 (0.112-0.113) | 0.111 (0.110-0.111) | 0.103 (0.103-0.103) | 0.117 (0.116-0.117) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.41x | 1.35x | 2.07x | 15.47x | 0.80x |
| bintrees | 0.85x | 0.91x | 2.14x | 0.68x | 1.28x |
| bytesstr | 1.06x | 0.90x | 0.22x | 2.18x | 0.68x |
| fib | 2.05x | 1.88x | 3.33x | 3.07x | 1.81x |
| html | 1.00x | 0.85x | 1.80x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.15x | 2.17x | 1.58x | n/a | n/a |
| mutres | 4.92x | 3.44x | 2.94x | 3.31x | 1.15x |
| nbody | 1.05x | 1.04x | 1.59x | n/a | n/a |
| pqueue | 1.99x | 1.48x | 2.52x | 3.42x | 1.15x |
| qsort_func | 0.92x | 0.93x | 1.67x | n/a | n/a |
| qsort_inplace | 1.29x | 1.25x | 1.18x | n/a | n/a |
| sieve | 1.07x | 1.06x | 1.86x | 1.43x | 1.01x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.05x | 0.92x | 0.96x | 3.64x | 0.43x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.09x | 1.08x | 1.13x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.007 | 0.007 | 0.005 | 0.014 | 0.117 | 0.004 | 4.5 | 4.8 | 4.9 | 8.5 | 47.8 | 5.0 |
| bintrees | 0.486 | 0.518 | 0.571 | 2.654 | 0.447 | 0.728 | 17.5 | 17.9 | 9.5 | 12.7 | 301.0 | 10.1 |
| bytesstr | 0.055 | 0.047 | 0.052 | 0.015 | 0.138 | 0.035 | 11.5 | 11.8 | 11.7 | 6.2 | 104.4 | 5.0 |
| fib | 0.367 | 0.335 | 0.179 | 0.598 | 0.568 | 0.325 | 1.5 | 1.9 | 1.6 | 1.7 | 38.7 | 2.1 |
| html | 0.149 | 0.127 | 0.150 | 0.358 | n/a | n/a | 3.9 | 4.1 | 2.2 | 7.7 | n/a | n/a |
| html_hand | 0.131 | 0.095 | n/a | n/a | n/a | n/a | 2.5 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.113 | 0.096 | n/a | n/a | n/a | n/a | 1.7 | 2.1 | n/a | n/a | n/a | n/a |
| mapfreq | 0.144 | 0.145 | 0.067 | 0.122 | n/a | n/a | 11.3 | 11.6 | 5.1 | 7.2 | n/a | n/a |
| mutres | 0.130 | 0.090 | 0.026 | 0.078 | 0.122 | 0.030 | 1.5 | 1.9 | 1.6 | 1.9 | 38.9 | 2.1 |
| nbody | 0.060 | 0.060 | 0.058 | 0.092 | n/a | n/a | 1.9 | 1.9 | 1.9 | 1.8 | n/a | n/a |
| pqueue | 0.152 | 0.113 | 0.076 | 0.201 | 0.342 | 0.088 | 6.1 | 6.5 | 4.9 | 15.0 | 61.9 | 5.1 |
| qsort_func | 0.238 | 0.240 | 0.257 | 0.513 | n/a | n/a | 36.4 | 36.8 | 23.8 | 36.7 | n/a | n/a |
| qsort_inplace | 0.131 | 0.126 | 0.101 | 0.134 | n/a | n/a | 16.7 | 17.1 | 16.9 | 30.4 | n/a | n/a |
| sieve | 0.177 | 0.175 | 0.166 | 0.476 | 0.267 | 0.167 | 77.7 | 78.1 | 77.6 | 231.7 | 116.1 | 78.3 |
| sortedmap | 0.253 | 0.255 | n/a | n/a | n/a | n/a | 11.1 | 11.6 | n/a | n/a | n/a | n/a |
| streams | 0.151 | 0.120 | n/a | n/a | n/a | n/a | 39.6 | 40.0 | n/a | n/a | n/a | n/a |
| strings | 0.070 | 0.062 | 0.067 | 0.079 | 0.510 | 0.029 | 46.1 | 46.5 | 34.7 | 23.5 | 138.9 | 19.9 |
| tasks | 5.017 | 5.066 | n/a | n/a | n/a | n/a | 14.1 | 14.5 | n/a | n/a | n/a | n/a |
| url | 0.334 | 0.321 | n/a | n/a | n/a | n/a | 6.4 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.112 | 0.110 | 0.102 | 0.119 | n/a | n/a | 2.2 | 2.6 | 2.0 | 6.5 | n/a | n/a |

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
| parallel_collatz | 1 | 0.715 (0.714-0.717) | 0.714 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.408 (0.406-0.410) | 0.754 | 1.75x | 88 % | 1.06x | same |
| parallel_collatz | 4 | 0.285 (0.285-0.291) | 1.001 | 2.50x | 63 % | 1.40x | same |
| streams_parallel | 1 | 0.759 (0.759-0.761) | 0.759 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.393 (0.393-0.394) | 0.763 | 1.93x | 97 % | 1.01x | same |
| streams_parallel | 4 | 0.273 (0.273-0.275) | 1.018 | 2.78x | 69 % | 1.34x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 3.250 (3.217-3.304) | 5.319 | 426.1 | 32,942,981,735 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
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
