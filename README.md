# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

37 runs, 2026-10-18 to 2026-11-24. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-11-24T14:44:32Z. Machine: AMD EPYC 7763 64-Core Processor, 4 cores, 15.6 GiB, Linux-7.0.0-1020-azure-x86_64-with-glibc2.43. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.009 (0.009-0.009) | 0.008 (0.008-0.008) | 0.005 (0.005-0.005) | 0.012 (0.010-0.013) | 0.075 (0.067-0.077) | 0.005 (0.004-0.005) |
| bintrees | 0.411 (0.410-0.419) | 0.398 (0.397-0.541) | 1.031 (1.024-1.037) | 1.312 (1.303-1.315) | 0.333 (0.329-0.337) | 1.184 (1.171-1.195) |
| bytesstr | 0.039 (0.038-0.039) | 0.035 (0.034-0.035) | 0.029 (0.028-0.029) | 0.010 (0.008-0.012) | 0.100 (0.095-0.105) | 0.039 (0.038-0.039) |
| fib | 0.331 (0.330-0.332) | 0.334 (0.333-0.336) | 0.178 (0.177-0.179) | 0.599 (0.595-0.623) | 0.422 (0.419-0.436) | 0.314 (0.313-0.328) |
| html | 0.161 (0.160-0.162) | 0.146 (0.143-0.146) | 0.151 (0.149-0.154) | 0.242 (0.237-0.273) | n/a | n/a |
| html_hand | 0.128 (0.127-0.128) | 0.110 (0.109-0.110) | n/a | n/a | n/a | n/a |
| http_parse | 0.125 (0.125-0.128) | 0.107 (0.107-0.108) | n/a | n/a | n/a | n/a |
| mapfreq | 0.156 (0.155-0.157) | 0.157 (0.155-0.160) | 0.075 (0.073-0.076) | 0.116 (0.114-0.117) | n/a | n/a |
| mutres | 0.168 (0.167-0.169) | 0.101 (0.101-0.102) | 0.038 (0.037-0.038) | 0.045 (0.044-0.047) | 0.085 (0.082-0.088) | 0.038 (0.037-0.038) |
| nbody | 0.083 (0.083-0.084) | 0.079 (0.079-0.079) | 0.074 (0.074-0.074) | 0.088 (0.088-0.089) | n/a | n/a |
| pqueue | 0.151 (0.150-0.155) | 0.138 (0.131-0.150) | 0.082 (0.076-0.084) | 0.203 (0.203-0.213) | 0.269 (0.256-0.283) | 0.097 (0.092-0.098) |
| qsort_func | 0.221 (0.221-0.226) | 0.220 (0.220-0.226) | 0.189 (0.189-0.190) | 0.418 (0.407-0.447) | n/a | n/a |
| qsort_inplace | 0.111 (0.111-0.112) | 0.110 (0.110-0.111) | 0.087 (0.087-0.088) | 0.120 (0.107-0.120) | n/a | n/a |
| sieve | 0.134 (0.128-0.143) | 0.136 (0.130-0.138) | 0.118 (0.115-0.120) | 0.336 (0.298-0.374) | 0.174 (0.172-0.184) | 0.116 (0.112-0.124) |
| sortedmap | 0.257 (0.251-0.296) | 0.265 (0.263-0.271) | n/a | n/a | n/a | n/a |
| streams | 0.138 (0.138-0.140) | 0.113 (0.111-0.117) | n/a | n/a | n/a | n/a |
| strings | 0.079 (0.078-0.079) | 0.076 (0.075-0.077) | 0.072 (0.070-0.072) | 0.076 (0.068-0.079) | 0.236 (0.234-0.246) | 0.032 (0.031-0.033) |
| tasks | 4.194 (4.060-4.242) | 4.069 (4.010-4.098) | n/a | n/a | n/a | n/a |
| url | 0.338 (0.335-0.342) | 0.308 (0.305-0.309) | n/a | n/a | n/a | n/a |
| wordfreq | 0.127 (0.127-0.129) | 0.127 (0.127-0.127) | 0.109 (0.106-0.111) | 0.118 (0.118-0.121) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.88x | 1.58x | 2.55x | 15.26x | 0.93x |
| bintrees | 0.40x | 0.39x | 1.27x | 0.32x | 1.15x |
| bytesstr | 1.35x | 1.21x | 0.33x | 3.48x | 1.35x |
| fib | 1.86x | 1.88x | 3.37x | 2.37x | 1.77x |
| html | 1.06x | 0.97x | 1.60x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.09x | 2.11x | 1.55x | n/a | n/a |
| mutres | 4.45x | 2.69x | 1.19x | 2.25x | 1.01x |
| nbody | 1.13x | 1.07x | 1.20x | n/a | n/a |
| pqueue | 1.84x | 1.68x | 2.48x | 3.27x | 1.18x |
| qsort_func | 1.17x | 1.16x | 2.21x | n/a | n/a |
| qsort_inplace | 1.27x | 1.26x | 1.37x | n/a | n/a |
| sieve | 1.13x | 1.15x | 2.84x | 1.47x | 0.98x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.11x | 1.06x | 1.06x | 3.30x | 0.44x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.16x | 1.16x | 1.08x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.009 | 0.008 | 0.005 | 0.016 | 0.106 | 0.004 | 4.8 | 5.0 | 4.8 | 9.7 | 47.8 | 5.2 |
| bintrees | 0.411 | 0.398 | 1.030 | 2.835 | 0.391 | 1.183 | 17.6 | 17.8 | 9.6 | 12.3 | 301.1 | 10.1 |
| bytesstr | 0.038 | 0.034 | 0.028 | 0.014 | 0.119 | 0.038 | 11.6 | 11.8 | 11.6 | 6.2 | 103.1 | 5.1 |
| fib | 0.330 | 0.333 | 0.177 | 0.600 | 0.436 | 0.314 | 1.6 | 1.8 | 1.5 | 1.8 | 38.8 | 2.1 |
| html | 0.160 | 0.145 | 0.150 | 0.321 | n/a | n/a | 3.9 | 4.1 | 2.1 | 7.4 | n/a | n/a |
| html_hand | 0.128 | 0.110 | n/a | n/a | n/a | n/a | 2.6 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.125 | 0.107 | n/a | n/a | n/a | n/a | 1.8 | 1.9 | n/a | n/a | n/a | n/a |
| mapfreq | 0.156 | 0.157 | 0.074 | 0.130 | n/a | n/a | 11.2 | 11.4 | 5.0 | 7.7 | n/a | n/a |
| mutres | 0.168 | 0.101 | 0.037 | 0.045 | 0.113 | 0.038 | 1.6 | 1.9 | 1.5 | 1.8 | 39.1 | 2.1 |
| nbody | 0.083 | 0.078 | 0.073 | 0.089 | n/a | n/a | 1.9 | 1.9 | 1.7 | 1.7 | n/a | n/a |
| pqueue | 0.151 | 0.138 | 0.082 | 0.216 | 0.333 | 0.096 | 6.3 | 6.5 | 4.8 | 15.0 | 62.0 | 5.2 |
| qsort_func | 0.221 | 0.220 | 0.189 | 0.523 | n/a | n/a | 36.4 | 36.6 | 22.0 | 42.5 | n/a | n/a |
| qsort_inplace | 0.111 | 0.110 | 0.087 | 0.150 | n/a | n/a | 17.0 | 17.1 | 16.8 | 26.1 | n/a | n/a |
| sieve | 0.134 | 0.136 | 0.118 | 0.508 | 0.199 | 0.115 | 77.9 | 78.2 | 77.7 | 289.6 | 116.1 | 78.5 |
| sortedmap | 0.257 | 0.265 | n/a | n/a | n/a | n/a | 11.3 | 11.4 | n/a | n/a | n/a | n/a |
| streams | 0.138 | 0.113 | n/a | n/a | n/a | n/a | 39.9 | 40.1 | n/a | n/a | n/a | n/a |
| strings | 0.079 | 0.076 | 0.071 | 0.099 | 0.465 | 0.031 | 46.3 | 46.5 | 34.8 | 23.3 | 139.3 | 20.1 |
| tasks | 4.903 | 4.669 | n/a | n/a | n/a | n/a | 14.2 | 14.4 | n/a | n/a | n/a | n/a |
| url | 0.338 | 0.307 | n/a | n/a | n/a | n/a | 6.5 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.127 | 0.126 | 0.109 | 0.121 | n/a | n/a | 2.4 | 2.5 | 1.9 | 6.5 | n/a | n/a |

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
| parallel_collatz | 1 | 0.489 (0.489-0.490) | 0.489 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.288 (0.286-0.289) | 0.521 | 1.70x | 85 % | 1.07x | same |
| parallel_collatz | 4 | 0.179 (0.178-0.179) | 0.600 | 2.74x | 69 % | 1.23x | same |
| streams_parallel | 1 | 0.496 (0.495-0.496) | 0.495 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.261 (0.260-0.261) | 0.497 | 1.90x | 95 % | 1.00x | same |
| streams_parallel | 4 | 0.174 (0.174-0.177) | 0.622 | 2.84x | 71 % | 1.25x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.929 (2.875-3.074) | 5.258 | 427.3 | 32,509,049,726 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
| 2026-11-24T14:44:32Z | `148472c2cd` | main | 32,509,049,726 | 2.929 | [json](history/2026-11-24-148472c2cdb0.json) |
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
