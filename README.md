# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

38 runs, 2026-10-18 to 2026-11-25. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-11-25T14:02:25Z. Machine: AMD EPYC 7763 64-Core Processor, 4 cores, 15.6 GiB, Linux-7.0.0-1020-azure-x86_64-with-glibc2.43. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.009 (0.009-0.009) | 0.008 (0.008-0.008) | 0.005 (0.005-0.005) | 0.011 (0.011-0.014) | 0.072 (0.068-0.074) | 0.005 (0.005-0.005) |
| bintrees | 0.408 (0.406-0.413) | 0.392 (0.388-0.397) | 1.022 (1.020-1.027) | 1.291 (1.288-1.311) | 0.328 (0.319-0.329) | 1.168 (1.165-1.171) |
| bytesstr | 0.038 (0.038-0.039) | 0.033 (0.033-0.033) | 0.028 (0.027-0.029) | 0.011 (0.009-0.018) | 0.103 (0.097-0.113) | 0.039 (0.038-0.039) |
| fib | 0.337 (0.336-0.338) | 0.334 (0.333-0.337) | 0.177 (0.176-0.177) | 0.597 (0.588-0.599) | 0.421 (0.416-0.435) | 0.313 (0.313-0.316) |
| html | 0.161 (0.160-0.162) | 0.145 (0.142-0.146) | 0.150 (0.148-0.151) | 0.241 (0.232-0.243) | n/a | n/a |
| html_hand | 0.126 (0.125-0.129) | 0.110 (0.109-0.110) | n/a | n/a | n/a | n/a |
| http_parse | 0.124 (0.124-0.127) | 0.106 (0.106-0.107) | n/a | n/a | n/a | n/a |
| mapfreq | 0.157 (0.156-0.159) | 0.156 (0.155-0.158) | 0.073 (0.073-0.075) | 0.115 (0.114-0.115) | n/a | n/a |
| mutres | 0.169 (0.167-0.174) | 0.102 (0.101-0.102) | 0.037 (0.037-0.038) | 0.045 (0.045-0.045) | 0.083 (0.081-0.084) | 0.037 (0.037-0.037) |
| nbody | 0.083 (0.083-0.084) | 0.079 (0.078-0.080) | 0.073 (0.073-0.074) | 0.088 (0.086-0.088) | n/a | n/a |
| pqueue | 0.146 (0.143-0.146) | 0.127 (0.125-0.133) | 0.074 (0.072-0.075) | 0.204 (0.199-0.206) | 0.238 (0.226-0.240) | 0.090 (0.089-0.092) |
| qsort_func | 0.218 (0.217-0.219) | 0.216 (0.216-0.216) | 0.185 (0.184-0.186) | 0.376 (0.373-0.416) | n/a | n/a |
| qsort_inplace | 0.111 (0.111-0.112) | 0.109 (0.109-0.109) | 0.087 (0.087-0.087) | 0.113 (0.101-0.130) | n/a | n/a |
| sieve | 0.118 (0.117-0.119) | 0.122 (0.120-0.124) | 0.101 (0.100-0.102) | 0.305 (0.271-0.312) | 0.162 (0.161-0.170) | 0.105 (0.105-0.110) |
| sortedmap | 0.248 (0.245-0.250) | 0.252 (0.251-0.259) | n/a | n/a | n/a | n/a |
| streams | 0.137 (0.137-0.138) | 0.110 (0.109-0.111) | n/a | n/a | n/a | n/a |
| strings | 0.076 (0.076-0.077) | 0.074 (0.074-0.075) | 0.070 (0.069-0.073) | 0.079 (0.070-0.089) | 0.231 (0.227-0.237) | 0.030 (0.029-0.031) |
| tasks | 3.933 (3.914-4.508) | 3.959 (3.807-3.999) | n/a | n/a | n/a | n/a |
| url | 0.333 (0.331-0.338) | 0.302 (0.302-0.303) | n/a | n/a | n/a | n/a |
| wordfreq | 0.127 (0.126-0.127) | 0.128 (0.125-0.129) | 0.109 (0.105-0.119) | 0.116 (0.115-0.117) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.89x | 1.60x | 2.38x | 14.83x | 0.97x |
| bintrees | 0.40x | 0.38x | 1.26x | 0.32x | 1.14x |
| bytesstr | 1.36x | 1.19x | 0.41x | 3.69x | 1.39x |
| fib | 1.91x | 1.89x | 3.38x | 2.38x | 1.77x |
| html | 1.07x | 0.97x | 1.61x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.14x | 2.13x | 1.56x | n/a | n/a |
| mutres | 4.54x | 2.72x | 1.21x | 2.22x | 0.99x |
| nbody | 1.13x | 1.07x | 1.19x | n/a | n/a |
| pqueue | 1.98x | 1.72x | 2.77x | 3.23x | 1.22x |
| qsort_func | 1.18x | 1.17x | 2.03x | n/a | n/a |
| qsort_inplace | 1.28x | 1.25x | 1.31x | n/a | n/a |
| sieve | 1.17x | 1.21x | 3.01x | 1.60x | 1.04x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.08x | 1.06x | 1.13x | 3.29x | 0.43x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.16x | 1.17x | 1.07x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.009 | 0.008 | 0.005 | 0.015 | 0.099 | 0.004 | 4.8 | 5.0 | 4.8 | 9.6 | 47.8 | 5.2 |
| bintrees | 0.408 | 0.391 | 1.021 | 2.809 | 0.384 | 1.167 | 17.6 | 17.8 | 9.6 | 12.4 | 301.1 | 10.0 |
| bytesstr | 0.037 | 0.033 | 0.027 | 0.018 | 0.120 | 0.038 | 11.7 | 11.9 | 11.6 | 7.5 | 103.1 | 5.1 |
| fib | 0.336 | 0.334 | 0.176 | 0.598 | 0.435 | 0.313 | 1.5 | 1.8 | 1.5 | 1.8 | 38.7 | 2.1 |
| html | 0.160 | 0.145 | 0.149 | 0.324 | n/a | n/a | 3.9 | 4.1 | 2.1 | 7.6 | n/a | n/a |
| html_hand | 0.126 | 0.109 | n/a | n/a | n/a | n/a | 2.7 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.123 | 0.106 | n/a | n/a | n/a | n/a | 1.8 | 2.0 | n/a | n/a | n/a | n/a |
| mapfreq | 0.156 | 0.156 | 0.073 | 0.130 | n/a | n/a | 11.2 | 11.4 | 5.0 | 7.1 | n/a | n/a |
| mutres | 0.169 | 0.101 | 0.037 | 0.045 | 0.114 | 0.037 | 1.6 | 1.8 | 1.5 | 1.8 | 39.1 | 2.1 |
| nbody | 0.083 | 0.078 | 0.073 | 0.088 | n/a | n/a | 1.8 | 1.9 | 1.8 | 1.8 | n/a | n/a |
| pqueue | 0.145 | 0.126 | 0.073 | 0.217 | 0.307 | 0.089 | 6.3 | 6.4 | 4.8 | 14.6 | 62.0 | 5.2 |
| qsort_func | 0.218 | 0.216 | 0.185 | 0.469 | n/a | n/a | 36.4 | 36.6 | 22.0 | 41.0 | n/a | n/a |
| qsort_inplace | 0.111 | 0.109 | 0.087 | 0.139 | n/a | n/a | 16.9 | 17.1 | 16.8 | 28.6 | n/a | n/a |
| sieve | 0.118 | 0.122 | 0.101 | 0.467 | 0.188 | 0.105 | 77.9 | 78.3 | 77.7 | 255.2 | 116.1 | 78.5 |
| sortedmap | 0.248 | 0.252 | n/a | n/a | n/a | n/a | 11.3 | 11.4 | n/a | n/a | n/a | n/a |
| streams | 0.136 | 0.109 | n/a | n/a | n/a | n/a | 39.9 | 40.1 | n/a | n/a | n/a | n/a |
| strings | 0.076 | 0.074 | 0.070 | 0.104 | 0.451 | 0.030 | 46.3 | 46.5 | 34.8 | 23.9 | 139.5 | 20.0 |
| tasks | 4.590 | 4.663 | n/a | n/a | n/a | n/a | 14.1 | 14.4 | n/a | n/a | n/a | n/a |
| url | 0.332 | 0.302 | n/a | n/a | n/a | n/a | 6.5 | 6.7 | n/a | n/a | n/a | n/a |
| wordfreq | 0.126 | 0.127 | 0.108 | 0.119 | n/a | n/a | 2.4 | 2.5 | 1.9 | 6.5 | n/a | n/a |

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
| parallel_collatz | 1 | 0.489 (0.485-0.492) | 0.488 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.286 (0.286-0.287) | 0.519 | 1.71x | 85 % | 1.06x | same |
| parallel_collatz | 4 | 0.179 (0.177-0.179) | 0.599 | 2.74x | 68 % | 1.23x | same |
| streams_parallel | 1 | 0.495 (0.494-0.496) | 0.494 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.260 (0.259-0.261) | 0.495 | 1.90x | 95 % | 1.00x | same |
| streams_parallel | 4 | 0.173 (0.173-0.175) | 0.620 | 2.85x | 71 % | 1.26x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.807 (2.783-2.861) | 5.147 | 427.3 | 32,508,995,900 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
| 2026-11-25T14:02:25Z | `148472c2cd` | main | 32,508,995,900 | 2.807 | [json](history/2026-11-25-148472c2cdb0.json) |
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
