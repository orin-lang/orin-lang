# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

36 runs, 2026-10-18 to 2026-11-23. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-11-23T14:06:57Z. Machine: AMD EPYC 9V45 96-Core Processor, 4 cores, 15.6 GiB, Linux-7.0.0-1020-azure-x86_64-with-glibc2.43. Runs per cell: 5 (median after one warm-up).

<details><summary>Tool versions</summary>

- cc: `cc (Ubuntu 15.2.0-16ubuntu1) 15.2.0`
- clang: `Ubuntu clang version 21.1.8 (6ubuntu1)`
- go: `go version go1.24.13 linux/amd64`
- java: `openjdk version "21.0.13" 2026-10-20 LTS`
- python: `3.14.4`
- rustc: `rustc 1.100.0 (0ef1bc386 2026-11-09)`
- valgrind: `valgrind-3.26.0`

</details>

### Wall time, seconds (median; min-max)

| benchmark | Orin (C backend) | Orin (LLVM backend) | C | Go | Java | Rust |
|---|---:|---:|---:|---:|---:|---:|
| appends | 0.006 (0.005-0.006) | 0.005 (0.004-0.005) | 0.004 (0.004-0.004) | 0.007 (0.006-0.008) | 0.057 (0.047-0.065) | 0.003 (0.003-0.003) |
| bintrees | 0.251 (0.248-0.273) | 0.249 (0.240-0.278) | 0.603 (0.591-0.623) | 0.755 (0.740-0.765) | 0.222 (0.215-0.285) | 0.709 (0.704-0.745) |
| bytesstr | 0.024 (0.024-0.025) | 0.020 (0.020-0.021) | 0.015 (0.015-0.016) | 0.006 (0.005-0.006) | 0.073 (0.067-0.076) | 0.030 (0.029-0.030) |
| fib | 0.183 (0.181-0.186) | 0.198 (0.193-0.203) | 0.094 (0.093-0.095) | 0.376 (0.375-0.378) | 0.275 (0.267-0.294) | 0.211 (0.204-0.485) |
| html | 0.095 (0.091-0.124) | 0.073 (0.072-0.077) | 0.089 (0.085-0.127) | 0.138 (0.135-0.143) | n/a | n/a |
| html_hand | 0.077 (0.075-0.088) | 0.058 (0.057-0.059) | n/a | n/a | n/a | n/a |
| http_parse | 0.065 (0.065-0.066) | 0.054 (0.054-0.055) | n/a | n/a | n/a | n/a |
| mapfreq | 0.094 (0.091-0.095) | 0.094 (0.091-0.095) | 0.047 (0.046-0.049) | 0.067 (0.067-0.080) | n/a | n/a |
| mutres | 0.089 (0.088-0.091) | 0.054 (0.054-0.055) | 0.023 (0.023-0.024) | 0.023 (0.023-0.024) | 0.059 (0.055-0.061) | 0.026 (0.026-0.030) |
| nbody | 0.045 (0.044-0.047) | 0.045 (0.045-0.045) | 0.049 (0.049-0.050) | 0.059 (0.059-0.062) | n/a | n/a |
| pqueue | 0.094 (0.093-0.096) | 0.078 (0.077-0.080) | 0.050 (0.049-0.050) | 0.132 (0.129-0.135) | 0.165 (0.155-0.177) | 0.057 (0.056-0.058) |
| qsort_func | 0.156 (0.153-0.158) | 0.150 (0.148-0.161) | 0.137 (0.136-0.138) | 0.251 (0.244-0.282) | n/a | n/a |
| qsort_inplace | 0.095 (0.092-0.097) | 0.085 (0.083-0.088) | 0.071 (0.071-0.072) | 0.087 (0.080-0.093) | n/a | n/a |
| sieve | 0.074 (0.073-0.075) | 0.072 (0.071-0.073) | 0.069 (0.068-0.071) | 0.145 (0.142-0.168) | 0.119 (0.115-0.126) | 0.069 (0.068-0.072) |
| sortedmap | 0.153 (0.152-0.154) | 0.156 (0.155-0.160) | n/a | n/a | n/a | n/a |
| streams | 0.090 (0.088-0.092) | 0.074 (0.073-0.075) | n/a | n/a | n/a | n/a |
| strings | 0.052 (0.050-0.053) | 0.047 (0.046-0.047) | 0.045 (0.044-0.045) | 0.044 (0.037-0.044) | 0.177 (0.170-0.196) | 0.019 (0.019-0.022) |
| tasks | 2.935 (2.844-2.992) | 2.917 (2.848-2.929) | n/a | n/a | n/a | n/a |
| url | 0.194 (0.191-0.194) | 0.176 (0.173-0.178) | n/a | n/a | n/a | n/a |
| wordfreq | 0.083 (0.081-0.100) | 0.078 (0.077-0.082) | 0.066 (0.064-0.067) | 0.083 (0.083-0.085) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.46x | 1.19x | 1.90x | 15.14x | 0.79x |
| bintrees | 0.42x | 0.41x | 1.25x | 0.37x | 1.18x |
| bytesstr | 1.57x | 1.32x | 0.36x | 4.70x | 1.93x |
| fib | 1.94x | 2.10x | 4.00x | 2.92x | 2.24x |
| html | 1.06x | 0.81x | 1.55x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.00x | 2.00x | 1.43x | n/a | n/a |
| mutres | 3.96x | 2.42x | 1.03x | 2.62x | 1.17x |
| nbody | 0.91x | 0.92x | 1.21x | n/a | n/a |
| pqueue | 1.89x | 1.57x | 2.65x | 3.32x | 1.14x |
| qsort_func | 1.14x | 1.10x | 1.83x | n/a | n/a |
| qsort_inplace | 1.32x | 1.19x | 1.22x | n/a | n/a |
| sieve | 1.08x | 1.05x | 2.11x | 1.74x | 1.01x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.16x | 1.05x | 0.99x | 3.97x | 0.44x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.26x | 1.19x | 1.26x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.005 | 0.004 | 0.004 | 0.009 | 0.074 | 0.003 | 4.8 | 4.9 | 4.8 | 7.8 | 48.2 | 5.2 |
| bintrees | 0.250 | 0.248 | 0.603 | 1.625 | 0.259 | 0.708 | 17.6 | 17.9 | 9.6 | 12.7 | 301.4 | 10.1 |
| bytesstr | 0.024 | 0.020 | 0.015 | 0.008 | 0.086 | 0.030 | 11.7 | 11.9 | 11.6 | 6.1 | 103.2 | 5.0 |
| fib | 0.182 | 0.197 | 0.094 | 0.377 | 0.284 | 0.206 | 1.6 | 1.9 | 1.5 | 1.6 | 38.7 | 2.0 |
| html | 0.094 | 0.072 | 0.087 | 0.182 | n/a | n/a | 4.0 | 4.2 | 2.1 | 7.6 | n/a | n/a |
| html_hand | 0.077 | 0.058 | n/a | n/a | n/a | n/a | 2.6 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.065 | 0.054 | n/a | n/a | n/a | n/a | 1.8 | 1.9 | n/a | n/a | n/a | n/a |
| mapfreq | 0.093 | 0.094 | 0.047 | 0.075 | n/a | n/a | 11.2 | 11.3 | 5.0 | 7.6 | n/a | n/a |
| mutres | 0.089 | 0.054 | 0.022 | 0.024 | 0.081 | 0.026 | 1.6 | 1.8 | 1.5 | 1.7 | 39.2 | 2.1 |
| nbody | 0.044 | 0.045 | 0.049 | 0.059 | n/a | n/a | 1.8 | 1.9 | 1.8 | 1.8 | n/a | n/a |
| pqueue | 0.094 | 0.078 | 0.049 | 0.137 | 0.214 | 0.056 | 6.3 | 6.5 | 4.8 | 14.8 | 62.2 | 5.2 |
| qsort_func | 0.154 | 0.150 | 0.137 | 0.307 | n/a | n/a | 36.3 | 36.6 | 22.0 | 36.9 | n/a | n/a |
| qsort_inplace | 0.094 | 0.085 | 0.071 | 0.096 | n/a | n/a | 16.9 | 17.1 | 16.8 | 24.5 | n/a | n/a |
| sieve | 0.074 | 0.072 | 0.068 | 0.243 | 0.141 | 0.068 | 78.0 | 78.2 | 77.7 | 185.9 | 116.2 | 78.4 |
| sortedmap | 0.153 | 0.155 | n/a | n/a | n/a | n/a | 11.2 | 11.4 | n/a | n/a | n/a | n/a |
| streams | 0.090 | 0.073 | n/a | n/a | n/a | n/a | 39.8 | 40.1 | n/a | n/a | n/a | n/a |
| strings | 0.051 | 0.047 | 0.044 | 0.055 | 0.342 | 0.019 | 46.3 | 46.4 | 34.8 | 23.4 | 139.4 | 20.1 |
| tasks | 3.373 | 3.324 | n/a | n/a | n/a | n/a | 14.1 | 14.4 | n/a | n/a | n/a | n/a |
| url | 0.193 | 0.176 | n/a | n/a | n/a | n/a | 6.5 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.082 | 0.078 | 0.066 | 0.085 | n/a | n/a | 2.3 | 2.6 | 1.9 | 6.5 | n/a | n/a |

### Executed instructions (valgrind; the regression metric)

| benchmark | Orin C | Orin LLVM | C | Orin C/C | Orin LLVM/C | note |
|---|---:|---:|---:|---:|---:|---|
| appends | 60,400,606 | 43,975,658 | 18,927,362 | 3.19x | 2.32x |  |
| bintrees | 4,217,620,511 | 4,213,208,414 | 11,630,513,487 | 0.36x | 0.36x |  |
| bytesstr | 349,647,141 | 259,441,956 | 103,926,179 | 3.36x | 2.50x |  |
| fib | 3,200,259,808 | 2,342,472,432 | 2,780,168,025 | 1.15x | 0.84x |  |
| html | 1,578,539,715 | 1,381,614,046 | 1,521,579,597 | 1.04x | 0.91x |  |
| html_hand | 1,201,359,326 | 981,754,879 | n/a | n/a | n/a |  |
| http_parse | 1,466,351,609 | 1,315,702,334 | n/a | n/a | n/a |  |
| mapfreq | 1,013,671,870 | 996,589,343 | 681,408,294 | 1.49x | 1.46x |  |
| mutres | 2,280,222,342 | 1,420,196,407 | 267,648,838 | 8.52x | 5.31x |  |
| nbody | 655,257,509 | 768,198,964 | 386,175,662 | 1.70x | 1.99x |  |
| pqueue | 1,345,424,376 | 1,321,812,336 | 359,470,793 | 3.74x | 3.68x |  |
| qsort_func | 1,321,582,510 | 1,278,327,655 | 1,064,640,580 | 1.24x | 1.20x |  |
| qsort_inplace | 609,054,278 | 521,083,870 | 275,674,807 | 2.21x | 1.89x |  |
| sieve | 423,203,312 | 451,732,345 | 161,705,036 | 2.62x | 2.79x |  |
| sortedmap | 1,332,999,715 | 1,338,880,433 | n/a | n/a | n/a |  |
| streams | 1,207,160,677 | 1,173,802,976 | n/a | n/a | n/a |  |
| strings | 653,262,497 | 578,559,242 | 734,241,501 | 0.89x | 0.79x |  |
| tasks | n/a | n/a | n/a | n/a | n/a | llvm skipped: multi-threaded (20,000 tasks, channels): valgrind serialises threads, so the count would include scheduler waits; orin skipped: multi-threaded (20,000 tasks, channels): valgrind serialises threads, so the count would include scheduler waits |
| url | 4,188,201,717 | 4,071,298,635 | n/a | n/a | n/a |  |
| wordfreq | 758,664,398 | 707,702,180 | 864,991,374 | 0.88x | 0.82x |  |

### Parallel speedup (std:task; worker threads = first argument of the program)

| benchmark | threads | wall s (min-max) | CPU s (user+sys) | speedup | efficiency | CPU vs 1 thread | output |
|---|---:|---:|---:|---:|---:|---:|---|
| parallel_collatz | 1 | 0.453 (0.449-0.490) | 0.452 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.265 (0.258-0.269) | 0.482 | 1.71x | 85 % | 1.07x | same |
| parallel_collatz | 4 | 0.163 (0.162-0.168) | 0.558 | 2.77x | 69 % | 1.23x | same |
| streams_parallel | 1 | 0.453 (0.449-0.481) | 0.453 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.237 (0.236-0.241) | 0.457 | 1.91x | 95 % | 1.01x | same |
| streams_parallel | 4 | 0.148 (0.147-0.151) | 0.541 | 3.05x | 76 % | 1.19x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.302 (2.238-2.422) | 3.657 | 427.1 | 32,509,283,292 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
| 2026-11-23T14:06:57Z | `148472c2cd` | main | 32,509,283,292 | 2.302 | [json](history/2026-11-23-148472c2cdb0.json) |
| 2026-11-22T12:22:22Z | `148472c2cd` | main | 32,508,585,656 | 2.218 | [json](history/2026-11-22-148472c2cdb0.json) |
| 2026-11-21T12:14:55Z | `148472c2cd` | main | 32,507,877,584 | 2.830 | [json](history/2026-11-21-148472c2cdb0.json) |
| 2026-11-20T12:37:57Z | `148472c2cd` | main | 32,508,382,018 | 2.292 | [json](history/2026-11-20-148472c2cdb0.json) |
| 2026-11-18T12:45:56Z | `148472c2cd` | main | 32,508,554,009 | 2.657 | [json](history/2026-11-18-148472c2cdb0.json) |
| 2026-11-17T12:56:05Z | `148472c2cd` | main | 32,508,876,011 | 2.317 | [json](history/2026-11-17-148472c2cdb0.json) |
| 2026-11-16T12:36:50Z | `148472c2cd` | main | 32,941,276,491 | 2.935 | [json](history/2026-11-16-148472c2cdb0.json) |
| 2026-11-15T11:55:27Z | `148472c2cd` | main | 32,947,512,412 | 2.250 | [json](history/2026-11-15-148472c2cdb0.json) |
| 2026-11-14T11:18:28Z | `148472c2cd` | main | 32,948,196,811 | 2.224 | [json](history/2026-11-14-148472c2cdb0.json) |
| 2026-11-13T12:02:20Z | `148472c2cd` | main | 32,944,948,551 | 2.962 | [json](history/2026-11-13-148472c2cdb0.json) |
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
