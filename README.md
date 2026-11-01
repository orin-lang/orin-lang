# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

15 runs, 2026-10-18 to 2026-11-01. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-11-01T11:14:05Z. Machine: Intel(R) Xeon(R) Platinum 8370C CPU @ 2.80GHz, 4 cores, 15.6 GiB, Linux-7.0.0-1017-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.007 (0.007-0.008) | 0.007 (0.007-0.007) | 0.005 (0.005-0.005) | 0.011 (0.010-0.011) | 0.071 (0.068-0.077) | 0.004 (0.004-0.004) |
| bintrees | 0.438 (0.432-0.443) | 0.455 (0.453-0.457) | 0.551 (0.546-0.555) | 1.396 (1.392-1.397) | 0.344 (0.334-0.350) | 0.706 (0.704-0.710) |
| bytesstr | 0.043 (0.043-0.044) | 0.040 (0.039-0.042) | 0.038 (0.037-0.040) | 0.009 (0.009-0.010) | 0.106 (0.096-0.107) | 0.031 (0.031-0.032) |
| fib | 0.307 (0.306-0.309) | 0.286 (0.286-0.288) | 0.190 (0.186-0.192) | 0.548 (0.540-0.551) | 0.491 (0.483-0.501) | 0.281 (0.280-0.281) |
| html | 0.148 (0.147-0.148) | 0.126 (0.126-0.126) | 0.141 (0.140-0.141) | 0.233 (0.232-0.246) | n/a | n/a |
| html_hand | 0.117 (0.117-0.117) | 0.088 (0.088-0.089) | n/a | n/a | n/a | n/a |
| http_parse | 0.118 (0.117-0.119) | 0.099 (0.098-0.099) | n/a | n/a | n/a | n/a |
| mapfreq | 0.160 (0.158-0.161) | 0.160 (0.158-0.178) | 0.075 (0.074-0.075) | 0.114 (0.114-0.116) | n/a | n/a |
| mutres | 0.147 (0.147-0.148) | 0.102 (0.101-0.102) | 0.030 (0.029-0.031) | 0.061 (0.061-0.062) | 0.081 (0.080-0.093) | 0.036 (0.036-0.037) |
| nbody | 0.073 (0.073-0.073) | 0.073 (0.072-0.074) | 0.062 (0.062-0.064) | 0.085 (0.084-0.086) | n/a | n/a |
| pqueue | 0.167 (0.166-0.172) | 0.144 (0.141-0.147) | 0.066 (0.065-0.068) | 0.202 (0.199-0.205) | 0.266 (0.259-0.270) | 0.092 (0.090-0.094) |
| qsort_func | 0.218 (0.217-0.220) | 0.226 (0.226-0.227) | 0.237 (0.236-0.237) | 0.396 (0.390-0.399) | n/a | n/a |
| qsort_inplace | 0.117 (0.117-0.118) | 0.115 (0.113-0.115) | 0.093 (0.092-0.093) | 0.108 (0.106-0.110) | n/a | n/a |
| sieve | 0.233 (0.225-0.238) | 0.233 (0.216-0.236) | 0.207 (0.201-0.216) | 0.348 (0.334-0.360) | 0.277 (0.271-0.287) | 0.205 (0.204-0.212) |
| sortedmap | 0.283 (0.278-0.289) | 0.271 (0.269-0.275) | n/a | n/a | n/a | n/a |
| streams | 0.157 (0.157-0.163) | 0.149 (0.149-0.153) | n/a | n/a | n/a | n/a |
| strings | 0.072 (0.071-0.073) | 0.068 (0.067-0.068) | 0.063 (0.063-0.064) | 0.060 (0.058-0.066) | 0.240 (0.239-0.249) | 0.030 (0.029-0.031) |
| tasks | 3.846 (3.757-3.958) | 3.944 (3.886-4.071) | n/a | n/a | n/a | n/a |
| url | 0.333 (0.331-0.335) | 0.313 (0.309-0.319) | n/a | n/a | n/a | n/a |
| wordfreq | 0.106 (0.105-0.107) | 0.105 (0.105-0.107) | 0.096 (0.095-0.097) | 0.114 (0.113-0.114) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.42x | 1.26x | 2.02x | 13.55x | 0.73x |
| bintrees | 0.80x | 0.82x | 2.53x | 0.62x | 1.28x |
| bytesstr | 1.13x | 1.05x | 0.24x | 2.78x | 0.82x |
| fib | 1.61x | 1.51x | 2.88x | 2.58x | 1.47x |
| html | 1.05x | 0.90x | 1.66x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.13x | 2.13x | 1.52x | n/a | n/a |
| mutres | 4.98x | 3.43x | 2.06x | 2.74x | 1.22x |
| nbody | 1.16x | 1.17x | 1.35x | n/a | n/a |
| pqueue | 2.54x | 2.20x | 3.09x | 4.06x | 1.40x |
| qsort_func | 0.92x | 0.95x | 1.67x | n/a | n/a |
| qsort_inplace | 1.26x | 1.23x | 1.16x | n/a | n/a |
| sieve | 1.13x | 1.13x | 1.68x | 1.34x | 0.99x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.14x | 1.07x | 0.95x | 3.79x | 0.47x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.11x | 1.09x | 1.18x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.007 | 0.006 | 0.005 | 0.014 | 0.116 | 0.004 | 4.5 | 4.8 | 4.9 | 9.8 | 47.7 | 5.1 |
| bintrees | 0.438 | 0.454 | 0.551 | 3.236 | 0.407 | 0.706 | 17.5 | 17.9 | 9.5 | 12.9 | 301.1 | 10.1 |
| bytesstr | 0.043 | 0.040 | 0.038 | 0.013 | 0.122 | 0.031 | 11.5 | 11.8 | 11.7 | 6.2 | 104.4 | 5.0 |
| fib | 0.307 | 0.286 | 0.190 | 0.549 | 0.509 | 0.280 | 1.5 | 1.9 | 1.6 | 1.9 | 38.6 | 2.1 |
| html | 0.148 | 0.126 | 0.140 | 0.308 | n/a | n/a | 3.9 | 4.2 | 2.2 | 7.6 | n/a | n/a |
| html_hand | 0.116 | 0.088 | n/a | n/a | n/a | n/a | 2.5 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.118 | 0.098 | n/a | n/a | n/a | n/a | 1.7 | 2.0 | n/a | n/a | n/a | n/a |
| mapfreq | 0.159 | 0.160 | 0.075 | 0.131 | n/a | n/a | 11.3 | 11.7 | 5.1 | 7.3 | n/a | n/a |
| mutres | 0.147 | 0.101 | 0.029 | 0.061 | 0.118 | 0.036 | 1.5 | 1.9 | 1.6 | 1.6 | 38.9 | 2.1 |
| nbody | 0.072 | 0.072 | 0.062 | 0.085 | n/a | n/a | 1.9 | 1.9 | 1.9 | 1.6 | n/a | n/a |
| pqueue | 0.166 | 0.144 | 0.065 | 0.210 | 0.340 | 0.092 | 6.1 | 6.5 | 4.9 | 14.8 | 61.9 | 5.2 |
| qsort_func | 0.218 | 0.226 | 0.236 | 0.472 | n/a | n/a | 36.4 | 36.8 | 23.8 | 37.0 | n/a | n/a |
| qsort_inplace | 0.117 | 0.114 | 0.093 | 0.123 | n/a | n/a | 16.7 | 17.1 | 16.9 | 25.9 | n/a | n/a |
| sieve | 0.233 | 0.233 | 0.206 | 0.487 | 0.314 | 0.204 | 77.7 | 78.1 | 77.6 | 231.7 | 116.1 | 78.3 |
| sortedmap | 0.283 | 0.271 | n/a | n/a | n/a | n/a | 11.1 | 11.5 | n/a | n/a | n/a | n/a |
| streams | 0.157 | 0.149 | n/a | n/a | n/a | n/a | 39.6 | 40.0 | n/a | n/a | n/a | n/a |
| strings | 0.072 | 0.067 | 0.063 | 0.069 | 0.497 | 0.029 | 46.1 | 46.5 | 34.7 | 21.6 | 139.1 | 20.0 |
| tasks | 4.070 | 4.195 | n/a | n/a | n/a | n/a | 14.1 | 14.5 | n/a | n/a | n/a | n/a |
| url | 0.332 | 0.312 | n/a | n/a | n/a | n/a | 6.4 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.106 | 0.104 | 0.095 | 0.116 | n/a | n/a | 2.2 | 2.6 | 2.0 | 6.5 | n/a | n/a |

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
| parallel_collatz | 1 | 0.609 (0.608-0.610) | 0.609 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.352 (0.352-0.353) | 0.645 | 1.73x | 86 % | 1.06x | same |
| parallel_collatz | 4 | 0.255 (0.252-0.255) | 0.882 | 2.39x | 60 % | 1.45x | same |
| streams_parallel | 1 | 0.634 (0.628-0.634) | 0.634 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.330 (0.327-0.335) | 0.636 | 1.92x | 96 % | 1.00x | same |
| streams_parallel | 4 | 0.255 (0.255-0.256) | 0.948 | 2.48x | 62 % | 1.50x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.842 (2.820-2.847) | 5.224 | 426.2 | 32,942,553,657 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
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
