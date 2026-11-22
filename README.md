# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

35 runs, 2026-10-18 to 2026-11-22. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-11-22T12:22:22Z. Machine: AMD EPYC 9V45 96-Core Processor, 4 cores, 15.6 GiB, Linux-7.0.0-1020-azure-x86_64-with-glibc2.43. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.005 (0.005-0.005) | 0.004 (0.004-0.004) | 0.004 (0.004-0.004) | 0.006 (0.005-0.007) | 0.057 (0.046-0.070) | 0.003 (0.003-0.005) |
| bintrees | 0.234 (0.231-0.239) | 0.224 (0.220-0.268) | 0.563 (0.561-0.566) | 0.717 (0.700-0.734) | 0.204 (0.201-0.210) | 0.662 (0.654-0.664) |
| bytesstr | 0.023 (0.023-0.024) | 0.020 (0.020-0.023) | 0.014 (0.014-0.014) | 0.006 (0.006-0.008) | 0.076 (0.072-0.079) | 0.028 (0.028-0.029) |
| fib | 0.174 (0.173-0.175) | 0.189 (0.188-0.195) | 0.089 (0.089-0.090) | 0.356 (0.352-0.362) | 0.254 (0.253-0.256) | 0.192 (0.191-0.195) |
| html | 0.087 (0.086-0.089) | 0.070 (0.068-0.071) | 0.081 (0.079-0.083) | 0.131 (0.128-0.132) | n/a | n/a |
| html_hand | 0.073 (0.072-0.077) | 0.055 (0.053-0.055) | n/a | n/a | n/a | n/a |
| http_parse | 0.063 (0.062-0.067) | 0.052 (0.052-0.052) | n/a | n/a | n/a | n/a |
| mapfreq | 0.091 (0.091-0.094) | 0.090 (0.089-0.091) | 0.045 (0.044-0.047) | 0.064 (0.063-0.066) | n/a | n/a |
| mutres | 0.085 (0.083-0.085) | 0.053 (0.052-0.058) | 0.022 (0.021-0.022) | 0.023 (0.023-0.023) | 0.058 (0.055-0.058) | 0.025 (0.025-0.027) |
| nbody | 0.041 (0.041-0.042) | 0.044 (0.043-0.054) | 0.046 (0.046-0.046) | 0.055 (0.047-0.055) | n/a | n/a |
| pqueue | 0.092 (0.091-0.098) | 0.079 (0.077-0.082) | 0.048 (0.047-0.048) | 0.125 (0.124-0.127) | 0.170 (0.151-0.181) | 0.056 (0.054-0.059) |
| qsort_func | 0.148 (0.147-0.150) | 0.151 (0.149-0.155) | 0.134 (0.132-0.134) | 0.241 (0.238-0.248) | n/a | n/a |
| qsort_inplace | 0.087 (0.086-0.089) | 0.080 (0.079-0.080) | 0.070 (0.068-0.071) | 0.079 (0.079-0.081) | n/a | n/a |
| sieve | 0.074 (0.070-0.074) | 0.071 (0.069-0.072) | 0.069 (0.067-0.071) | 0.148 (0.141-0.161) | 0.120 (0.116-0.125) | 0.069 (0.068-0.074) |
| sortedmap | 0.158 (0.152-0.228) | 0.165 (0.157-0.210) | n/a | n/a | n/a | n/a |
| streams | 0.084 (0.084-0.086) | 0.070 (0.069-0.071) | n/a | n/a | n/a | n/a |
| strings | 0.047 (0.047-0.048) | 0.044 (0.044-0.045) | 0.043 (0.043-0.043) | 0.043 (0.037-0.044) | 0.163 (0.159-0.178) | 0.019 (0.019-0.019) |
| tasks | 2.737 (2.726-2.753) | 2.668 (2.644-2.736) | n/a | n/a | n/a | n/a |
| url | 0.180 (0.177-0.185) | 0.163 (0.162-0.168) | n/a | n/a | n/a | n/a |
| wordfreq | 0.073 (0.072-0.074) | 0.071 (0.069-0.072) | 0.060 (0.059-0.061) | 0.075 (0.075-0.076) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.38x | 1.14x | 1.80x | 15.77x | 0.78x |
| bintrees | 0.42x | 0.40x | 1.27x | 0.36x | 1.17x |
| bytesstr | 1.62x | 1.40x | 0.39x | 5.29x | 1.98x |
| fib | 1.94x | 2.12x | 3.98x | 2.84x | 2.14x |
| html | 1.07x | 0.87x | 1.61x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.02x | 2.00x | 1.41x | n/a | n/a |
| mutres | 3.91x | 2.45x | 1.05x | 2.66x | 1.16x |
| nbody | 0.90x | 0.95x | 1.20x | n/a | n/a |
| pqueue | 1.94x | 1.65x | 2.63x | 3.56x | 1.19x |
| qsort_func | 1.11x | 1.13x | 1.80x | n/a | n/a |
| qsort_inplace | 1.25x | 1.14x | 1.13x | n/a | n/a |
| sieve | 1.07x | 1.03x | 2.15x | 1.74x | 1.00x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.10x | 1.03x | 1.00x | 3.78x | 0.44x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.21x | 1.18x | 1.25x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.005 | 0.004 | 0.003 | 0.009 | 0.072 | 0.003 | 4.8 | 4.9 | 4.8 | 7.3 | 48.8 | 5.2 |
| bintrees | 0.234 | 0.223 | 0.563 | 1.543 | 0.236 | 0.662 | 17.7 | 17.8 | 9.6 | 13.3 | 301.3 | 10.1 |
| bytesstr | 0.023 | 0.020 | 0.014 | 0.007 | 0.086 | 0.028 | 11.7 | 11.8 | 11.6 | 6.3 | 103.3 | 5.0 |
| fib | 0.173 | 0.189 | 0.089 | 0.357 | 0.263 | 0.191 | 1.6 | 1.8 | 1.5 | 1.7 | 38.7 | 2.1 |
| html | 0.086 | 0.068 | 0.081 | 0.173 | n/a | n/a | 3.9 | 4.1 | 2.1 | 7.5 | n/a | n/a |
| html_hand | 0.073 | 0.054 | n/a | n/a | n/a | n/a | 2.6 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.063 | 0.052 | n/a | n/a | n/a | n/a | 1.8 | 1.9 | n/a | n/a | n/a | n/a |
| mapfreq | 0.090 | 0.090 | 0.045 | 0.071 | n/a | n/a | 11.2 | 11.4 | 5.0 | 7.9 | n/a | n/a |
| mutres | 0.085 | 0.053 | 0.022 | 0.023 | 0.078 | 0.025 | 1.6 | 1.9 | 1.5 | 1.9 | 39.1 | 2.1 |
| nbody | 0.041 | 0.043 | 0.046 | 0.055 | n/a | n/a | 1.8 | 1.8 | 1.8 | 1.7 | n/a | n/a |
| pqueue | 0.092 | 0.078 | 0.047 | 0.131 | 0.215 | 0.056 | 6.3 | 6.5 | 4.8 | 14.9 | 61.4 | 5.2 |
| qsort_func | 0.148 | 0.150 | 0.133 | 0.293 | n/a | n/a | 36.4 | 36.6 | 22.0 | 36.4 | n/a | n/a |
| qsort_inplace | 0.087 | 0.079 | 0.070 | 0.088 | n/a | n/a | 17.0 | 17.1 | 16.8 | 24.4 | n/a | n/a |
| sieve | 0.073 | 0.071 | 0.069 | 0.234 | 0.142 | 0.069 | 77.9 | 78.2 | 77.7 | 204.6 | 116.2 | 78.4 |
| sortedmap | 0.158 | 0.165 | n/a | n/a | n/a | n/a | 11.2 | 11.4 | n/a | n/a | n/a | n/a |
| streams | 0.084 | 0.069 | n/a | n/a | n/a | n/a | 39.9 | 40.1 | n/a | n/a | n/a | n/a |
| strings | 0.047 | 0.044 | 0.043 | 0.055 | 0.310 | 0.019 | 46.3 | 46.5 | 34.8 | 23.6 | 139.2 | 20.1 |
| tasks | 3.155 | 3.064 | n/a | n/a | n/a | n/a | 14.2 | 14.4 | n/a | n/a | n/a | n/a |
| url | 0.180 | 0.163 | n/a | n/a | n/a | n/a | 6.5 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.073 | 0.070 | 0.060 | 0.077 | n/a | n/a | 2.3 | 2.6 | 1.9 | 6.6 | n/a | n/a |

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
| parallel_collatz | 1 | 0.424 (0.421-0.438) | 0.424 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.261 (0.247-0.288) | 0.459 | 1.62x | 81 % | 1.08x | same |
| parallel_collatz | 4 | 0.154 (0.153-0.156) | 0.521 | 2.75x | 69 % | 1.23x | same |
| streams_parallel | 1 | 0.434 (0.431-0.437) | 0.432 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.223 (0.222-0.225) | 0.428 | 1.95x | 97 % | 0.99x | same |
| streams_parallel | 4 | 0.147 (0.146-0.147) | 0.532 | 2.95x | 74 % | 1.23x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.218 (2.205-2.304) | 3.479 | 427.3 | 32,508,585,656 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
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
