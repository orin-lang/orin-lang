# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

11 runs, 2026-10-18 to 2026-10-28. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-10-28T10:31:52Z. Machine: INTEL(R) XEON(R) PLATINUM 8573C, 4 cores, 15.6 GiB, Linux-6.17.0-1022-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.007 (0.007-0.007) | 0.006 (0.006-0.006) | 0.005 (0.005-0.005) | 0.007 (0.007-0.008) | 0.062 (0.060-0.070) | 0.004 (0.003-0.004) |
| bintrees | 0.445 (0.442-0.448) | 0.478 (0.476-0.483) | 0.538 (0.536-0.544) | 1.200 (1.186-1.205) | 0.291 (0.288-0.293) | 0.707 (0.703-0.709) |
| bytesstr | 0.036 (0.036-0.039) | 0.035 (0.034-0.035) | 0.038 (0.037-0.039) | 0.007 (0.007-0.008) | 0.086 (0.083-0.094) | 0.031 (0.031-0.033) |
| fib | 0.369 (0.368-0.370) | 0.337 (0.337-0.339) | 0.180 (0.179-0.180) | 0.598 (0.597-0.604) | 0.555 (0.548-0.558) | 0.325 (0.324-0.325) |
| html | 0.148 (0.148-0.148) | 0.126 (0.125-0.126) | 0.151 (0.151-0.165) | 0.261 (0.247-0.273) | n/a | n/a |
| html_hand | 0.131 (0.131-0.132) | 0.095 (0.095-0.096) | n/a | n/a | n/a | n/a |
| http_parse | 0.114 (0.113-0.114) | 0.096 (0.096-0.098) | n/a | n/a | n/a | n/a |
| mapfreq | 0.140 (0.139-0.142) | 0.141 (0.140-0.142) | 0.071 (0.065-0.115) | 0.101 (0.099-0.103) | n/a | n/a |
| mutres | 0.130 (0.129-0.130) | 0.091 (0.090-0.091) | 0.026 (0.025-0.026) | 0.077 (0.077-0.078) | 0.088 (0.083-0.090) | 0.030 (0.029-0.031) |
| nbody | 0.061 (0.061-0.061) | 0.060 (0.060-0.061) | 0.058 (0.058-0.058) | 0.093 (0.092-0.096) | n/a | n/a |
| pqueue | 0.153 (0.152-0.154) | 0.113 (0.113-0.114) | 0.077 (0.077-0.079) | 0.187 (0.183-0.191) | 0.222 (0.215-0.228) | 0.088 (0.087-0.090) |
| qsort_func | 0.226 (0.225-0.227) | 0.229 (0.228-0.229) | 0.246 (0.245-0.249) | 0.374 (0.364-0.379) | n/a | n/a |
| qsort_inplace | 0.127 (0.126-0.127) | 0.122 (0.121-0.123) | 0.095 (0.095-0.096) | 0.104 (0.103-0.105) | n/a | n/a |
| sieve | 0.131 (0.119-0.138) | 0.126 (0.121-0.127) | 0.120 (0.116-0.124) | 0.181 (0.173-0.195) | 0.184 (0.167-0.188) | 0.127 (0.119-0.129) |
| sortedmap | 0.253 (0.251-0.253) | 0.255 (0.252-0.256) | n/a | n/a | n/a | n/a |
| streams | 0.122 (0.111-0.126) | 0.092 (0.092-0.093) | n/a | n/a | n/a | n/a |
| strings | 0.066 (0.065-0.067) | 0.060 (0.059-0.062) | 0.065 (0.065-0.067) | 0.051 (0.049-0.052) | 0.204 (0.197-0.206) | 0.027 (0.026-0.028) |
| tasks | 4.424 (4.404-4.488) | 4.518 (4.255-4.573) | n/a | n/a | n/a | n/a |
| url | 0.327 (0.325-0.328) | 0.315 (0.313-0.316) | n/a | n/a | n/a | n/a |
| wordfreq | 0.113 (0.112-0.113) | 0.111 (0.110-0.111) | 0.103 (0.103-0.103) | 0.112 (0.112-0.112) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.41x | 1.29x | 1.49x | 12.71x | 0.73x |
| bintrees | 0.83x | 0.89x | 2.23x | 0.54x | 1.31x |
| bytesstr | 0.96x | 0.92x | 0.20x | 2.28x | 0.82x |
| fib | 2.05x | 1.88x | 3.33x | 3.09x | 1.81x |
| html | 0.98x | 0.83x | 1.73x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 1.97x | 1.99x | 1.42x | n/a | n/a |
| mutres | 5.03x | 3.53x | 3.01x | 3.43x | 1.15x |
| nbody | 1.05x | 1.04x | 1.60x | n/a | n/a |
| pqueue | 1.99x | 1.47x | 2.43x | 2.89x | 1.14x |
| qsort_func | 0.92x | 0.93x | 1.52x | n/a | n/a |
| qsort_inplace | 1.33x | 1.27x | 1.09x | n/a | n/a |
| sieve | 1.09x | 1.05x | 1.51x | 1.53x | 1.05x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.02x | 0.92x | 0.79x | 3.14x | 0.42x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.09x | 1.07x | 1.09x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.007 | 0.006 | 0.005 | 0.010 | 0.103 | 0.003 | 4.5 | 4.8 | 4.9 | 9.7 | 58.8 | 5.2 |
| bintrees | 0.444 | 0.478 | 0.538 | 2.578 | 0.349 | 0.706 | 17.5 | 17.9 | 9.5 | 14.5 | 307.8 | 10.1 |
| bytesstr | 0.036 | 0.034 | 0.037 | 0.010 | 0.105 | 0.031 | 11.5 | 11.8 | 11.6 | 7.7 | 109.6 | 5.0 |
| fib | 0.368 | 0.337 | 0.179 | 0.599 | 0.568 | 0.324 | 1.5 | 1.9 | 1.6 | 3.4 | 47.6 | 2.1 |
| html | 0.148 | 0.126 | 0.151 | 0.344 | n/a | n/a | 3.9 | 4.2 | 2.2 | 9.7 | n/a | n/a |
| html_hand | 0.131 | 0.095 | n/a | n/a | n/a | n/a | 2.5 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.113 | 0.096 | n/a | n/a | n/a | n/a | 1.7 | 2.1 | n/a | n/a | n/a | n/a |
| mapfreq | 0.139 | 0.140 | 0.068 | 0.120 | n/a | n/a | 11.3 | 11.6 | 5.2 | 10.0 | n/a | n/a |
| mutres | 0.129 | 0.090 | 0.025 | 0.078 | 0.121 | 0.029 | 1.5 | 1.9 | 1.6 | 3.4 | 47.9 | 2.1 |
| nbody | 0.060 | 0.060 | 0.058 | 0.093 | n/a | n/a | 1.9 | 1.9 | 1.9 | 3.4 | n/a | n/a |
| pqueue | 0.152 | 0.113 | 0.076 | 0.193 | 0.293 | 0.087 | 6.1 | 6.5 | 4.9 | 16.1 | 70.5 | 5.1 |
| qsort_func | 0.226 | 0.228 | 0.246 | 0.444 | n/a | n/a | 36.4 | 36.8 | 24.2 | 38.6 | n/a | n/a |
| qsort_inplace | 0.126 | 0.121 | 0.095 | 0.116 | n/a | n/a | 16.6 | 17.3 | 17.0 | 25.3 | n/a | n/a |
| sieve | 0.131 | 0.126 | 0.120 | 0.269 | 0.213 | 0.126 | 78.5 | 78.9 | 78.3 | 233.8 | 124.6 | 79.9 |
| sortedmap | 0.252 | 0.254 | n/a | n/a | n/a | n/a | 11.1 | 11.6 | n/a | n/a | n/a | n/a |
| streams | 0.120 | 0.091 | n/a | n/a | n/a | n/a | 42.5 | 40.9 | n/a | n/a | n/a | n/a |
| strings | 0.066 | 0.059 | 0.064 | 0.060 | 0.458 | 0.027 | 47.4 | 48.7 | 36.5 | 24.1 | 145.6 | 20.9 |
| tasks | 4.583 | 4.640 | n/a | n/a | n/a | n/a | 18.0 | 18.4 | n/a | n/a | n/a | n/a |
| url | 0.327 | 0.315 | n/a | n/a | n/a | n/a | 6.4 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.112 | 0.110 | 0.103 | 0.114 | n/a | n/a | 2.2 | 2.6 | 2.0 | 7.9 | n/a | n/a |

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
| parallel_collatz | 1 | 0.712 (0.712-0.714) | 0.712 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.391 (0.389-0.391) | 0.732 | 1.82x | 91 % | 1.03x | same |
| parallel_collatz | 4 | 0.278 (0.276-0.283) | 0.990 | 2.56x | 64 % | 1.39x | same |
| streams_parallel | 1 | 0.756 (0.755-0.758) | 0.755 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.388 (0.386-0.389) | 0.759 | 1.95x | 97 % | 1.01x | same |
| streams_parallel | 4 | 0.267 (0.267-0.270) | 1.019 | 2.83x | 71 % | 1.35x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.813 (2.781-2.887) | 4.838 | 431.8 | 32,948,464,083 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
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
