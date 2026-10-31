# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

14 runs, 2026-10-18 to 2026-10-31. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-10-31T10:16:06Z. Machine: AMD EPYC 9V45 96-Core Processor, 4 cores, 15.6 GiB, Linux-7.0.0-1017-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.005 (0.005-0.008) | 0.004 (0.004-0.009) | 0.004 (0.004-0.027) | 0.006 (0.006-0.008) | 0.057 (0.049-0.068) | 0.003 (0.003-0.006) |
| bintrees | 0.234 (0.229-0.239) | 0.225 (0.219-0.228) | 0.301 (0.293-0.314) | 0.683 (0.680-0.686) | 0.206 (0.203-0.208) | 0.370 (0.367-0.371) |
| bytesstr | 0.023 (0.023-0.023) | 0.019 (0.019-0.019) | 0.015 (0.015-0.015) | 0.006 (0.005-0.008) | 0.069 (0.068-0.083) | 0.028 (0.028-0.028) |
| fib | 0.183 (0.173-0.187) | 0.201 (0.195-0.214) | 0.100 (0.099-0.102) | 0.353 (0.350-0.363) | 0.255 (0.251-0.279) | 0.191 (0.190-0.193) |
| html | 0.083 (0.082-0.084) | 0.069 (0.068-0.070) | 0.081 (0.080-0.081) | 0.130 (0.127-0.137) | n/a | n/a |
| html_hand | 0.071 (0.070-0.072) | 0.052 (0.050-0.052) | n/a | n/a | n/a | n/a |
| http_parse | 0.064 (0.064-0.066) | 0.052 (0.052-0.054) | n/a | n/a | n/a | n/a |
| mapfreq | 0.088 (0.088-0.088) | 0.089 (0.087-0.094) | 0.044 (0.043-0.047) | 0.062 (0.061-0.065) | n/a | n/a |
| mutres | 0.087 (0.085-0.091) | 0.052 (0.052-0.054) | 0.020 (0.020-0.021) | 0.022 (0.022-0.023) | 0.058 (0.054-0.061) | 0.025 (0.024-0.027) |
| nbody | 0.044 (0.043-0.044) | 0.042 (0.042-0.043) | 0.042 (0.042-0.042) | 0.055 (0.054-0.055) | n/a | n/a |
| pqueue | 0.088 (0.086-0.089) | 0.071 (0.070-0.073) | 0.045 (0.045-0.046) | 0.122 (0.118-0.124) | 0.146 (0.144-0.149) | 0.053 (0.052-0.058) |
| qsort_func | 0.139 (0.137-0.141) | 0.138 (0.137-0.139) | 0.158 (0.153-0.162) | 0.227 (0.224-0.235) | n/a | n/a |
| qsort_inplace | 0.080 (0.079-0.081) | 0.077 (0.077-0.078) | 0.068 (0.066-0.069) | 0.078 (0.076-0.079) | n/a | n/a |
| sieve | 0.070 (0.069-0.070) | 0.069 (0.069-0.069) | 0.068 (0.067-0.069) | 0.141 (0.138-0.161) | 0.117 (0.115-0.121) | 0.066 (0.066-0.067) |
| sortedmap | 0.148 (0.144-0.149) | 0.146 (0.146-0.147) | n/a | n/a | n/a | n/a |
| streams | 0.078 (0.075-0.079) | 0.070 (0.070-0.071) | n/a | n/a | n/a | n/a |
| strings | 0.049 (0.048-0.050) | 0.044 (0.043-0.046) | 0.041 (0.040-0.042) | 0.044 (0.038-0.054) | 0.162 (0.160-0.166) | 0.019 (0.018-0.019) |
| tasks | 2.753 (2.737-2.996) | 2.769 (2.713-2.847) | n/a | n/a | n/a | n/a |
| url | 0.193 (0.191-0.196) | 0.164 (0.161-0.173) | n/a | n/a | n/a | n/a |
| wordfreq | 0.074 (0.073-0.075) | 0.071 (0.068-0.100) | 0.061 (0.060-0.061) | 0.074 (0.073-0.074) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.31x | 1.13x | 1.59x | 14.41x | 0.71x |
| bintrees | 0.78x | 0.75x | 2.27x | 0.68x | 1.23x |
| bytesstr | 1.52x | 1.28x | 0.40x | 4.63x | 1.88x |
| fib | 1.84x | 2.02x | 3.54x | 2.56x | 1.92x |
| html | 1.03x | 0.85x | 1.61x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.01x | 2.03x | 1.41x | n/a | n/a |
| mutres | 4.29x | 2.57x | 1.10x | 2.83x | 1.20x |
| nbody | 1.04x | 1.00x | 1.29x | n/a | n/a |
| pqueue | 1.95x | 1.56x | 2.70x | 3.24x | 1.16x |
| qsort_func | 0.88x | 0.88x | 1.44x | n/a | n/a |
| qsort_inplace | 1.17x | 1.13x | 1.15x | n/a | n/a |
| sieve | 1.03x | 1.01x | 2.06x | 1.72x | 0.98x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.19x | 1.07x | 1.06x | 3.94x | 0.45x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.22x | 1.16x | 1.21x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.005 | 0.004 | 0.004 | 0.009 | 0.072 | 0.003 | 4.6 | 4.8 | 4.9 | 7.9 | 47.7 | 5.2 |
| bintrees | 0.234 | 0.224 | 0.301 | 1.469 | 0.238 | 0.370 | 17.6 | 17.9 | 9.7 | 12.6 | 301.0 | 10.1 |
| bytesstr | 0.023 | 0.019 | 0.015 | 0.008 | 0.082 | 0.028 | 11.6 | 11.8 | 11.7 | 7.2 | 104.6 | 5.0 |
| fib | 0.183 | 0.201 | 0.099 | 0.353 | 0.263 | 0.191 | 1.6 | 1.9 | 1.6 | 1.7 | 38.6 | 2.1 |
| html | 0.083 | 0.068 | 0.080 | 0.171 | n/a | n/a | 3.9 | 4.2 | 2.2 | 7.6 | n/a | n/a |
| html_hand | 0.071 | 0.051 | n/a | n/a | n/a | n/a | 2.5 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.064 | 0.052 | n/a | n/a | n/a | n/a | 1.7 | 2.1 | n/a | n/a | n/a | n/a |
| mapfreq | 0.088 | 0.089 | 0.044 | 0.069 | n/a | n/a | 11.4 | 11.7 | 5.1 | 7.2 | n/a | n/a |
| mutres | 0.087 | 0.052 | 0.020 | 0.023 | 0.076 | 0.024 | 1.6 | 1.9 | 1.6 | 1.7 | 38.9 | 2.1 |
| nbody | 0.043 | 0.042 | 0.042 | 0.055 | n/a | n/a | 1.9 | 1.9 | 2.0 | 1.7 | n/a | n/a |
| pqueue | 0.088 | 0.070 | 0.045 | 0.127 | 0.189 | 0.052 | 6.2 | 6.5 | 4.9 | 14.8 | 61.8 | 5.1 |
| qsort_func | 0.138 | 0.138 | 0.158 | 0.279 | n/a | n/a | 36.5 | 36.8 | 23.8 | 36.4 | n/a | n/a |
| qsort_inplace | 0.079 | 0.077 | 0.068 | 0.090 | n/a | n/a | 16.8 | 17.1 | 16.9 | 26.0 | n/a | n/a |
| sieve | 0.070 | 0.069 | 0.068 | 0.236 | 0.137 | 0.066 | 77.8 | 78.1 | 77.7 | 185.9 | 115.9 | 78.3 |
| sortedmap | 0.145 | 0.146 | n/a | n/a | n/a | n/a | 11.3 | 11.5 | n/a | n/a | n/a | n/a |
| streams | 0.077 | 0.070 | n/a | n/a | n/a | n/a | 39.8 | 40.0 | n/a | n/a | n/a | n/a |
| strings | 0.049 | 0.043 | 0.041 | 0.055 | 0.311 | 0.018 | 46.2 | 46.5 | 34.7 | 23.4 | 139.2 | 19.9 |
| tasks | 3.251 | 3.184 | n/a | n/a | n/a | n/a | 14.3 | 14.8 | n/a | n/a | n/a | n/a |
| url | 0.193 | 0.164 | n/a | n/a | n/a | n/a | 6.5 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.074 | 0.071 | 0.061 | 0.075 | n/a | n/a | 2.4 | 2.6 | 2.0 | 6.5 | n/a | n/a |

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
| parallel_collatz | 1 | 0.373 (0.372-0.377) | 0.372 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.218 (0.218-0.231) | 0.397 | 1.71x | 85 % | 1.07x | same |
| parallel_collatz | 4 | 0.140 (0.134-0.142) | 0.478 | 2.65x | 66 % | 1.29x | same |
| streams_parallel | 1 | 0.417 (0.415-0.432) | 0.417 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.222 (0.219-0.261) | 0.427 | 1.88x | 94 % | 1.02x | same |
| streams_parallel | 4 | 0.145 (0.144-0.146) | 0.521 | 2.87x | 72 % | 1.25x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.238 (2.194-2.302) | 3.524 | 426.2 | 32,947,431,130 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
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
