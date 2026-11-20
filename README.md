# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

33 runs, 2026-10-18 to 2026-11-20. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-11-20T12:37:57Z. Machine: Intel(R) Xeon(R) 6975P-C, 4 cores, 15.3 GiB, Linux-7.0.0-1016-aws-x86_64-with-glibc2.43. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.005 (0.004-0.005) | 0.004 (0.004-0.004) | 0.003 (0.003-0.003) | 0.007 (0.006-0.007) | 0.051 (0.047-0.061) | 0.003 (0.003-0.003) |
| bintrees | 0.363 (0.362-0.370) | 0.363 (0.362-0.365) | 0.674 (0.674-0.676) | 0.874 (0.872-0.883) | 0.272 (0.261-0.277) | 0.779 (0.777-0.791) |
| bytesstr | 0.033 (0.033-0.036) | 0.031 (0.031-0.032) | 0.031 (0.031-0.031) | 0.008 (0.007-0.008) | 0.075 (0.070-0.089) | 0.024 (0.024-0.024) |
| fib | 0.250 (0.250-0.251) | 0.280 (0.280-0.281) | 0.128 (0.127-0.128) | 0.417 (0.417-0.417) | 0.350 (0.345-0.354) | 0.233 (0.233-0.233) |
| html | 0.114 (0.113-0.115) | 0.095 (0.094-0.096) | 0.105 (0.105-0.106) | 0.195 (0.191-0.203) | n/a | n/a |
| html_hand | 0.097 (0.097-0.097) | 0.072 (0.071-0.072) | n/a | n/a | n/a | n/a |
| http_parse | 0.088 (0.088-0.089) | 0.072 (0.072-0.072) | n/a | n/a | n/a | n/a |
| mapfreq | 0.116 (0.115-0.116) | 0.117 (0.116-0.118) | 0.057 (0.054-0.058) | 0.085 (0.083-0.085) | n/a | n/a |
| mutres | 0.102 (0.102-0.103) | 0.068 (0.068-0.068) | 0.026 (0.026-0.027) | 0.061 (0.061-0.061) | 0.066 (0.061-0.070) | 0.024 (0.024-0.024) |
| nbody | 0.043 (0.043-0.043) | 0.047 (0.047-0.047) | 0.049 (0.049-0.049) | 0.070 (0.069-0.070) | n/a | n/a |
| pqueue | 0.124 (0.123-0.124) | 0.096 (0.094-0.102) | 0.064 (0.064-0.065) | 0.148 (0.148-0.151) | 0.211 (0.203-0.212) | 0.072 (0.072-0.074) |
| qsort_func | 0.183 (0.182-0.183) | 0.185 (0.183-0.186) | 0.158 (0.157-0.159) | 0.327 (0.322-0.337) | n/a | n/a |
| qsort_inplace | 0.101 (0.101-0.101) | 0.099 (0.098-0.099) | 0.078 (0.078-0.079) | 0.094 (0.093-0.097) | n/a | n/a |
| sieve | 0.111 (0.109-0.123) | 0.112 (0.108-0.114) | 0.103 (0.102-0.109) | 0.242 (0.230-0.299) | 0.144 (0.142-0.148) | 0.105 (0.095-0.112) |
| sortedmap | 0.202 (0.202-0.203) | 0.207 (0.207-0.208) | n/a | n/a | n/a | n/a |
| streams | 0.094 (0.088-0.096) | 0.083 (0.080-0.125) | n/a | n/a | n/a | n/a |
| strings | 0.051 (0.050-0.052) | 0.048 (0.047-0.048) | 0.052 (0.051-0.052) | 0.052 (0.047-0.052) | 0.186 (0.182-0.191) | 0.021 (0.021-0.024) |
| tasks | 2.267 (2.159-2.307) | 2.205 (2.114-2.286) | n/a | n/a | n/a | n/a |
| url | 0.235 (0.234-0.236) | 0.234 (0.233-0.235) | n/a | n/a | n/a | n/a |
| wordfreq | 0.088 (0.088-0.088) | 0.088 (0.087-0.088) | 0.077 (0.076-0.077) | 0.090 (0.089-0.090) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.56x | 1.34x | 2.43x | 17.52x | 0.96x |
| bintrees | 0.54x | 0.54x | 1.30x | 0.40x | 1.15x |
| bytesstr | 1.06x | 1.00x | 0.25x | 2.40x | 0.77x |
| fib | 1.95x | 2.19x | 3.25x | 2.73x | 1.82x |
| html | 1.08x | 0.90x | 1.86x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.02x | 2.05x | 1.49x | n/a | n/a |
| mutres | 3.89x | 2.57x | 2.31x | 2.50x | 0.93x |
| nbody | 0.89x | 0.97x | 1.43x | n/a | n/a |
| pqueue | 1.92x | 1.49x | 2.30x | 3.27x | 1.12x |
| qsort_func | 1.16x | 1.17x | 2.07x | n/a | n/a |
| qsort_inplace | 1.30x | 1.26x | 1.20x | n/a | n/a |
| sieve | 1.08x | 1.09x | 2.35x | 1.40x | 1.03x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 0.98x | 0.92x | 1.01x | 3.59x | 0.41x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.15x | 1.15x | 1.17x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.004 | 0.004 | 0.003 | 0.010 | 0.082 | 0.003 | 4.8 | 5.0 | 4.8 | 8.4 | 48.0 | 5.2 |
| bintrees | 0.362 | 0.363 | 0.674 | 1.935 | 0.310 | 0.778 | 17.7 | 17.9 | 9.6 | 13.3 | 296.3 | 10.1 |
| bytesstr | 0.033 | 0.031 | 0.031 | 0.011 | 0.088 | 0.024 | 11.6 | 11.9 | 11.6 | 6.3 | 103.1 | 5.1 |
| fib | 0.250 | 0.280 | 0.128 | 0.418 | 0.360 | 0.233 | 1.6 | 1.8 | 1.5 | 1.7 | 39.0 | 2.1 |
| html | 0.114 | 0.094 | 0.105 | 0.255 | n/a | n/a | 3.9 | 4.1 | 2.1 | 7.7 | n/a | n/a |
| html_hand | 0.097 | 0.071 | n/a | n/a | n/a | n/a | 2.7 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.088 | 0.072 | n/a | n/a | n/a | n/a | 1.8 | 2.0 | n/a | n/a | n/a | n/a |
| mapfreq | 0.116 | 0.117 | 0.057 | 0.100 | n/a | n/a | 11.2 | 11.5 | 5.0 | 7.5 | n/a | n/a |
| mutres | 0.102 | 0.067 | 0.026 | 0.061 | 0.090 | 0.024 | 1.6 | 1.9 | 1.5 | 1.7 | 39.2 | 2.2 |
| nbody | 0.043 | 0.047 | 0.048 | 0.070 | n/a | n/a | 2.0 | 1.9 | 1.9 | 1.6 | n/a | n/a |
| pqueue | 0.123 | 0.096 | 0.064 | 0.155 | 0.264 | 0.072 | 6.3 | 6.6 | 4.8 | 15.0 | 62.3 | 5.2 |
| qsort_func | 0.183 | 0.184 | 0.157 | 0.390 | n/a | n/a | 36.4 | 36.6 | 22.0 | 37.5 | n/a | n/a |
| qsort_inplace | 0.101 | 0.098 | 0.078 | 0.108 | n/a | n/a | 17.0 | 17.2 | 16.8 | 24.5 | n/a | n/a |
| sieve | 0.111 | 0.112 | 0.102 | 0.377 | 0.165 | 0.105 | 77.9 | 78.3 | 77.7 | 204.5 | 116.3 | 78.5 |
| sortedmap | 0.202 | 0.207 | n/a | n/a | n/a | n/a | 11.2 | 11.4 | n/a | n/a | n/a | n/a |
| streams | 0.094 | 0.083 | n/a | n/a | n/a | n/a | 39.8 | 40.1 | n/a | n/a | n/a | n/a |
| strings | 0.050 | 0.048 | 0.052 | 0.068 | 0.386 | 0.021 | 46.3 | 46.6 | 34.8 | 23.5 | 139.4 | 20.1 |
| tasks | 3.099 | 3.051 | n/a | n/a | n/a | n/a | 14.1 | 14.3 | n/a | n/a | n/a | n/a |
| url | 0.235 | 0.234 | n/a | n/a | n/a | n/a | 6.6 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.088 | 0.088 | 0.076 | 0.091 | n/a | n/a | 2.4 | 2.6 | 1.9 | 6.5 | n/a | n/a |

### Executed instructions (valgrind; the regression metric)

| benchmark | Orin C | Orin LLVM | C | Orin C/C | Orin LLVM/C | note |
|---|---:|---:|---:|---:|---:|---|
| appends | 60,400,499 | 43,975,648 | 18,927,262 | 3.19x | 2.32x |  |
| bintrees | 4,217,620,399 | 4,213,208,399 | 11,630,513,387 | 0.36x | 0.36x |  |
| bytesstr | 349,647,029 | 259,441,941 | 103,926,079 | 3.36x | 2.50x |  |
| fib | 3,200,259,701 | 2,342,472,422 | 2,780,167,920 | 1.15x | 0.84x |  |
| html | 1,578,539,608 | 1,381,614,036 | 1,521,579,492 | 1.04x | 0.91x |  |
| html_hand | 1,201,359,214 | 981,754,864 | n/a | n/a | n/a |  |
| http_parse | 1,466,351,440 | 1,315,702,262 | n/a | n/a | n/a |  |
| mapfreq | 1,013,671,763 | 996,589,333 | 681,408,194 | 1.49x | 1.46x |  |
| mutres | 2,280,222,230 | 1,420,196,392 | 267,648,738 | 8.52x | 5.31x |  |
| nbody | 655,257,499 | 768,198,954 | 386,175,654 | 1.70x | 1.99x |  |
| pqueue | 1,345,424,264 | 1,321,812,321 | 359,470,693 | 3.74x | 3.68x |  |
| qsort_func | 1,321,582,341 | 1,278,327,583 | 1,064,640,480 | 1.24x | 1.20x |  |
| qsort_inplace | 609,054,160 | 521,083,849 | 275,674,645 | 2.21x | 1.89x |  |
| sieve | 423,203,205 | 451,732,335 | 161,704,931 | 2.62x | 2.79x |  |
| sortedmap | 1,332,999,603 | 1,338,880,418 | n/a | n/a | n/a |  |
| streams | 1,207,160,563 | 1,173,802,959 | n/a | n/a | n/a |  |
| strings | 653,262,390 | 578,559,232 | 734,241,401 | 0.89x | 0.79x |  |
| tasks | n/a | n/a | n/a | n/a | n/a | llvm skipped: multi-threaded (20,000 tasks, channels): valgrind serialises threads, so the count would include scheduler waits; orin skipped: multi-threaded (20,000 tasks, channels): valgrind serialises threads, so the count would include scheduler waits |
| url | 4,188,201,610 | 4,071,298,625 | n/a | n/a | n/a |  |
| wordfreq | 758,664,286 | 707,702,165 | 869,980,783 | 0.87x | 0.81x |  |

### Parallel speedup (std:task; worker threads = first argument of the program)

| benchmark | threads | wall s (min-max) | CPU s (user+sys) | speedup | efficiency | CPU vs 1 thread | output |
|---|---:|---:|---:|---:|---:|---:|---|
| parallel_collatz | 1 | 0.534 (0.534-0.534) | 0.534 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.306 (0.306-0.306) | 0.560 | 1.75x | 87 % | 1.05x | same |
| parallel_collatz | 4 | 0.216 (0.215-0.218) | 0.753 | 2.47x | 62 % | 1.41x | same |
| streams_parallel | 1 | 0.510 (0.510-0.512) | 0.509 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.266 (0.265-0.267) | 0.511 | 1.92x | 96 % | 1.00x | same |
| streams_parallel | 4 | 0.188 (0.188-0.189) | 0.691 | 2.71x | 68 % | 1.36x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.292 (2.273-2.305) | 3.881 | 427.3 | 32,508,382,018 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
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
