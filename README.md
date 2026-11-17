# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

31 runs, 2026-10-18 to 2026-11-17. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-11-17T12:56:05Z. Machine: INTEL(R) XEON(R) PLATINUM 8573C, 4 cores, 15.6 GiB, Linux-7.0.0-1019-azure-x86_64-with-glibc2.43. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.006 (0.006-0.007) | 0.006 (0.005-0.006) | 0.003 (0.003-0.004) | 0.008 (0.007-0.008) | 0.059 (0.055-0.067) | 0.003 (0.003-0.003) |
| bintrees | 0.413 (0.410-0.427) | 0.413 (0.408-0.419) | 0.766 (0.761-0.766) | 0.998 (0.991-1.000) | 0.315 (0.312-0.321) | 0.893 (0.880-0.902) |
| bytesstr | 0.034 (0.034-0.035) | 0.032 (0.031-0.033) | 0.031 (0.030-0.032) | 0.008 (0.007-0.008) | 0.085 (0.083-0.097) | 0.026 (0.026-0.026) |
| fib | 0.322 (0.322-0.334) | 0.343 (0.340-0.344) | 0.137 (0.136-0.137) | 0.499 (0.498-0.523) | 0.461 (0.458-0.470) | 0.269 (0.269-0.270) |
| html | 0.130 (0.129-0.131) | 0.110 (0.109-0.110) | 0.122 (0.121-0.122) | 0.220 (0.215-0.232) | n/a | n/a |
| html_hand | 0.112 (0.111-0.114) | 0.088 (0.088-0.089) | n/a | n/a | n/a | n/a |
| http_parse | 0.096 (0.095-0.098) | 0.079 (0.078-0.081) | n/a | n/a | n/a | n/a |
| mapfreq | 0.119 (0.119-0.122) | 0.121 (0.120-0.123) | 0.059 (0.057-0.068) | 0.090 (0.089-0.103) | n/a | n/a |
| mutres | 0.112 (0.109-0.129) | 0.074 (0.074-0.074) | 0.026 (0.026-0.028) | 0.065 (0.065-0.065) | 0.071 (0.067-0.073) | 0.024 (0.024-0.026) |
| nbody | 0.047 (0.046-0.047) | 0.050 (0.050-0.050) | 0.052 (0.052-0.053) | 0.077 (0.077-0.077) | n/a | n/a |
| pqueue | 0.128 (0.128-0.129) | 0.096 (0.096-0.098) | 0.068 (0.067-0.069) | 0.160 (0.159-0.162) | 0.219 (0.218-0.222) | 0.075 (0.075-0.075) |
| qsort_func | 0.197 (0.196-0.197) | 0.200 (0.199-0.200) | 0.172 (0.171-0.173) | 0.338 (0.328-0.372) | n/a | n/a |
| qsort_inplace | 0.108 (0.107-0.110) | 0.105 (0.104-0.108) | 0.084 (0.084-0.085) | 0.095 (0.095-0.098) | n/a | n/a |
| sieve | 0.108 (0.108-0.117) | 0.110 (0.093-0.114) | 0.100 (0.096-0.115) | 0.213 (0.191-0.228) | 0.156 (0.151-0.159) | 0.083 (0.082-0.086) |
| sortedmap | 0.211 (0.210-0.212) | 0.215 (0.214-0.216) | n/a | n/a | n/a | n/a |
| streams | 0.120 (0.114-0.122) | 0.088 (0.082-0.093) | n/a | n/a | n/a | n/a |
| strings | 0.057 (0.052-0.058) | 0.048 (0.047-0.052) | 0.052 (0.051-0.053) | 0.049 (0.047-0.056) | 0.199 (0.189-0.216) | 0.023 (0.023-0.024) |
| tasks | 4.233 (4.199-4.574) | 4.348 (4.220-4.439) | n/a | n/a | n/a | n/a |
| url | 0.285 (0.284-0.286) | 0.268 (0.267-0.268) | n/a | n/a | n/a | n/a |
| wordfreq | 0.093 (0.093-0.094) | 0.094 (0.093-0.094) | 0.084 (0.084-0.084) | 0.098 (0.097-0.102) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.93x | 1.66x | 2.32x | 17.86x | 0.91x |
| bintrees | 0.54x | 0.54x | 1.30x | 0.41x | 1.17x |
| bytesstr | 1.09x | 1.02x | 0.24x | 2.72x | 0.84x |
| fib | 2.35x | 2.50x | 3.64x | 3.37x | 1.97x |
| html | 1.07x | 0.90x | 1.81x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.04x | 2.07x | 1.53x | n/a | n/a |
| mutres | 4.30x | 2.85x | 2.49x | 2.73x | 0.93x |
| nbody | 0.89x | 0.96x | 1.48x | n/a | n/a |
| pqueue | 1.88x | 1.40x | 2.34x | 3.20x | 1.10x |
| qsort_func | 1.15x | 1.17x | 1.97x | n/a | n/a |
| qsort_inplace | 1.29x | 1.25x | 1.14x | n/a | n/a |
| sieve | 1.08x | 1.09x | 2.12x | 1.56x | 0.83x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.08x | 0.91x | 0.94x | 3.80x | 0.44x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.11x | 1.11x | 1.17x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.006 | 0.005 | 0.003 | 0.010 | 0.098 | 0.003 | 4.8 | 5.1 | 4.8 | 8.0 | 48.1 | 5.2 |
| bintrees | 0.412 | 0.413 | 0.766 | 2.195 | 0.367 | 0.893 | 17.7 | 17.8 | 9.6 | 12.8 | 301.3 | 10.0 |
| bytesstr | 0.034 | 0.032 | 0.031 | 0.010 | 0.107 | 0.026 | 11.6 | 11.8 | 11.6 | 6.2 | 104.7 | 5.1 |
| fib | 0.322 | 0.342 | 0.137 | 0.500 | 0.476 | 0.269 | 1.6 | 1.8 | 1.5 | 1.7 | 38.9 | 2.1 |
| html | 0.130 | 0.109 | 0.121 | 0.289 | n/a | n/a | 4.0 | 4.2 | 2.1 | 7.6 | n/a | n/a |
| html_hand | 0.111 | 0.088 | n/a | n/a | n/a | n/a | 2.7 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.095 | 0.078 | n/a | n/a | n/a | n/a | 1.8 | 2.0 | n/a | n/a | n/a | n/a |
| mapfreq | 0.119 | 0.121 | 0.058 | 0.108 | n/a | n/a | 11.2 | 11.4 | 5.0 | 7.3 | n/a | n/a |
| mutres | 0.111 | 0.074 | 0.026 | 0.065 | 0.107 | 0.024 | 1.7 | 1.8 | 1.5 | 1.7 | 39.3 | 2.1 |
| nbody | 0.046 | 0.050 | 0.052 | 0.077 | n/a | n/a | 1.9 | 1.9 | 2.0 | 1.9 | n/a | n/a |
| pqueue | 0.128 | 0.096 | 0.068 | 0.167 | 0.281 | 0.075 | 6.3 | 6.5 | 4.8 | 14.9 | 61.4 | 5.1 |
| qsort_func | 0.197 | 0.199 | 0.171 | 0.405 | n/a | n/a | 36.4 | 36.6 | 22.0 | 38.7 | n/a | n/a |
| qsort_inplace | 0.108 | 0.104 | 0.084 | 0.109 | n/a | n/a | 16.9 | 17.1 | 16.8 | 24.4 | n/a | n/a |
| sieve | 0.108 | 0.109 | 0.100 | 0.317 | 0.182 | 0.083 | 77.9 | 78.2 | 77.7 | 231.7 | 116.2 | 78.4 |
| sortedmap | 0.210 | 0.214 | n/a | n/a | n/a | n/a | 11.2 | 11.5 | n/a | n/a | n/a | n/a |
| streams | 0.120 | 0.088 | n/a | n/a | n/a | n/a | 39.9 | 40.1 | n/a | n/a | n/a | n/a |
| strings | 0.056 | 0.047 | 0.052 | 0.057 | 0.421 | 0.023 | 46.3 | 46.6 | 34.8 | 21.5 | 139.4 | 20.1 |
| tasks | 3.917 | 4.134 | n/a | n/a | n/a | n/a | 14.2 | 14.5 | n/a | n/a | n/a | n/a |
| url | 0.284 | 0.267 | n/a | n/a | n/a | n/a | 6.5 | 6.7 | n/a | n/a | n/a | n/a |
| wordfreq | 0.093 | 0.093 | 0.084 | 0.100 | n/a | n/a | 2.4 | 2.6 | 1.9 | 6.4 | n/a | n/a |

### Executed instructions (valgrind; the regression metric)

| benchmark | Orin C | Orin LLVM | C | Orin C/C | Orin LLVM/C | note |
|---|---:|---:|---:|---:|---:|---|
| appends | 60,400,606 | 43,975,658 | 18,927,362 | 3.19x | 2.32x |  |
| bintrees | 4,217,620,511 | 4,213,208,414 | 11,630,513,487 | 0.36x | 0.36x |  |
| bytesstr | 349,647,141 | 259,441,956 | 103,926,179 | 3.36x | 2.50x |  |
| fib | 3,200,259,808 | 2,342,472,432 | 2,780,168,025 | 1.15x | 0.84x |  |
| html | 1,578,539,715 | 1,381,614,046 | 1,521,579,597 | 1.04x | 0.91x |  |
| html_hand | 1,201,359,326 | 981,754,879 | n/a | n/a | n/a |  |
| http_parse | 1,466,351,598 | 1,315,702,323 | n/a | n/a | n/a |  |
| mapfreq | 1,013,671,870 | 996,589,343 | 681,408,294 | 1.49x | 1.46x |  |
| mutres | 2,280,222,342 | 1,420,196,407 | 267,648,838 | 8.52x | 5.31x |  |
| nbody | 655,257,509 | 768,198,964 | 386,175,662 | 1.70x | 1.99x |  |
| pqueue | 1,345,424,376 | 1,321,812,336 | 359,470,793 | 3.74x | 3.68x |  |
| qsort_func | 1,321,582,499 | 1,278,327,644 | 1,064,640,580 | 1.24x | 1.20x |  |
| qsort_inplace | 609,054,278 | 521,083,870 | 275,674,796 | 2.21x | 1.89x |  |
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
| parallel_collatz | 1 | 0.639 (0.636-0.643) | 0.639 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.360 (0.359-0.363) | 0.666 | 1.78x | 89 % | 1.04x | same |
| parallel_collatz | 4 | 0.255 (0.255-0.256) | 0.897 | 2.51x | 63 % | 1.40x | same |
| streams_parallel | 1 | 0.586 (0.585-0.595) | 0.585 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.305 (0.303-0.312) | 0.591 | 1.92x | 96 % | 1.01x | same |
| streams_parallel | 4 | 0.214 (0.214-0.215) | 0.798 | 2.73x | 68 % | 1.36x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.317 (2.308-2.354) | 4.062 | 427.0 | 32,508,876,011 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
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
