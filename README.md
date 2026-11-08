# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

22 runs, 2026-10-18 to 2026-11-08. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-11-08T11:10:36Z. Machine: AMD EPYC 9V74 80-Core Processor, 4 cores, 15.6 GiB, Linux-7.0.0-1017-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.007 (0.007-0.007) | 0.006 (0.006-0.007) | 0.005 (0.005-0.005) | 0.010 (0.008-0.013) | 0.059 (0.056-0.125) | 0.004 (0.003-0.004) |
| bintrees | 0.313 (0.312-0.330) | 0.324 (0.320-0.328) | 0.504 (0.485-0.516) | 0.968 (0.965-0.985) | 0.284 (0.275-0.285) | 0.567 (0.565-0.572) |
| bytesstr | 0.060 (0.032-0.061) | 0.027 (0.027-0.058) | 0.020 (0.019-0.025) | 0.008 (0.007-0.011) | 0.091 (0.083-0.113) | 0.032 (0.032-0.086) |
| fib | 0.244 (0.244-0.248) | 0.247 (0.246-0.284) | 0.151 (0.151-0.151) | 0.513 (0.512-0.515) | 0.322 (0.319-0.324) | 0.271 (0.271-0.271) |
| html | 0.124 (0.124-0.126) | 0.103 (0.100-0.150) | 0.123 (0.118-0.131) | 0.182 (0.175-0.226) | n/a | n/a |
| html_hand | 0.104 (0.104-0.108) | 0.081 (0.077-0.081) | n/a | n/a | n/a | n/a |
| http_parse | 0.094 (0.091-0.095) | 0.078 (0.077-0.133) | n/a | n/a | n/a | n/a |
| mapfreq | 0.120 (0.119-0.131) | 0.120 (0.120-0.120) | 0.059 (0.059-0.060) | 0.087 (0.087-0.089) | n/a | n/a |
| mutres | 0.137 (0.137-0.138) | 0.088 (0.087-0.088) | 0.028 (0.027-0.028) | 0.036 (0.036-0.037) | 0.089 (0.071-0.125) | 0.032 (0.032-0.032) |
| nbody | 0.064 (0.063-0.064) | 0.064 (0.064-0.094) | 0.061 (0.061-0.061) | 0.072 (0.072-0.093) | n/a | n/a |
| pqueue | 0.125 (0.124-0.192) | 0.102 (0.102-0.103) | 0.058 (0.057-0.059) | 0.164 (0.160-0.171) | 0.208 (0.199-0.224) | 0.075 (0.075-0.075) |
| qsort_func | 0.179 (0.177-0.180) | 0.181 (0.179-0.182) | 0.191 (0.189-0.202) | 0.320 (0.301-0.329) | n/a | n/a |
| qsort_inplace | 0.100 (0.097-0.101) | 0.107 (0.105-0.166) | 0.076 (0.076-0.076) | 0.102 (0.096-0.112) | n/a | n/a |
| sieve | 0.113 (0.109-0.119) | 0.115 (0.112-0.115) | 0.107 (0.100-0.109) | 0.223 (0.206-0.274) | 0.157 (0.150-0.163) | 0.109 (0.105-0.112) |
| sortedmap | 0.213 (0.209-0.219) | 0.219 (0.216-0.222) | n/a | n/a | n/a | n/a |
| streams | 0.110 (0.109-0.112) | 0.101 (0.100-0.102) | n/a | n/a | n/a | n/a |
| strings | 0.067 (0.067-0.068) | 0.064 (0.064-0.065) | 0.061 (0.057-0.094) | 0.063 (0.058-0.073) | 0.197 (0.195-0.201) | 0.026 (0.026-0.027) |
| tasks | 3.553 (3.530-3.595) | 3.413 (3.360-3.420) | n/a | n/a | n/a | n/a |
| url | 0.287 (0.286-0.305) | 0.250 (0.249-0.252) | n/a | n/a | n/a | n/a |
| wordfreq | 0.098 (0.097-0.098) | 0.097 (0.096-0.097) | 0.082 (0.082-0.082) | 0.095 (0.094-0.095) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.58x | 1.39x | 2.06x | 12.66x | 0.77x |
| bintrees | 0.62x | 0.64x | 1.92x | 0.56x | 1.12x |
| bytesstr | 3.01x | 1.37x | 0.41x | 4.55x | 1.61x |
| fib | 1.62x | 1.63x | 3.40x | 2.13x | 1.80x |
| html | 1.01x | 0.84x | 1.48x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.02x | 2.03x | 1.47x | n/a | n/a |
| mutres | 4.96x | 3.18x | 1.32x | 3.22x | 1.15x |
| nbody | 1.05x | 1.06x | 1.19x | n/a | n/a |
| pqueue | 2.17x | 1.77x | 2.85x | 3.60x | 1.30x |
| qsort_func | 0.94x | 0.95x | 1.68x | n/a | n/a |
| qsort_inplace | 1.32x | 1.41x | 1.35x | n/a | n/a |
| sieve | 1.06x | 1.08x | 2.10x | 1.47x | 1.03x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.11x | 1.06x | 1.04x | 3.25x | 0.43x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.19x | 1.18x | 1.16x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.007 | 0.006 | 0.004 | 0.013 | 0.090 | 0.003 | 4.6 | 4.9 | 4.9 | 9.0 | 47.6 | 5.1 |
| bintrees | 0.312 | 0.324 | 0.503 | 2.039 | 0.325 | 0.566 | 17.6 | 17.9 | 9.7 | 12.6 | 301.1 | 10.1 |
| bytesstr | 0.032 | 0.027 | 0.020 | 0.012 | 0.102 | 0.032 | 11.6 | 11.8 | 11.7 | 6.3 | 103.2 | 4.9 |
| fib | 0.243 | 0.246 | 0.151 | 0.514 | 0.332 | 0.271 | 1.6 | 1.9 | 1.6 | 1.7 | 38.7 | 2.1 |
| html | 0.124 | 0.102 | 0.122 | 0.239 | n/a | n/a | 3.9 | 4.2 | 2.2 | 7.7 | n/a | n/a |
| html_hand | 0.104 | 0.080 | n/a | n/a | n/a | n/a | 2.5 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.092 | 0.077 | n/a | n/a | n/a | n/a | 1.7 | 2.0 | n/a | n/a | n/a | n/a |
| mapfreq | 0.119 | 0.120 | 0.059 | 0.098 | n/a | n/a | 11.4 | 11.6 | 5.1 | 7.1 | n/a | n/a |
| mutres | 0.137 | 0.087 | 0.027 | 0.037 | 0.094 | 0.031 | 1.6 | 1.9 | 1.6 | 1.7 | 39.0 | 2.1 |
| nbody | 0.063 | 0.064 | 0.060 | 0.073 | n/a | n/a | 1.9 | 1.9 | 2.0 | 1.8 | n/a | n/a |
| pqueue | 0.124 | 0.102 | 0.057 | 0.167 | 0.266 | 0.075 | 6.2 | 6.5 | 4.9 | 14.6 | 62.1 | 5.0 |
| qsort_func | 0.178 | 0.180 | 0.190 | 0.394 | n/a | n/a | 36.5 | 36.8 | 23.8 | 38.5 | n/a | n/a |
| qsort_inplace | 0.099 | 0.107 | 0.075 | 0.125 | n/a | n/a | 16.8 | 17.1 | 16.9 | 31.6 | n/a | n/a |
| sieve | 0.112 | 0.114 | 0.106 | 0.340 | 0.177 | 0.109 | 77.8 | 78.1 | 77.7 | 231.9 | 115.9 | 78.4 |
| sortedmap | 0.212 | 0.219 | n/a | n/a | n/a | n/a | 11.3 | 11.5 | n/a | n/a | n/a | n/a |
| streams | 0.110 | 0.101 | n/a | n/a | n/a | n/a | 39.8 | 40.0 | n/a | n/a | n/a | n/a |
| strings | 0.067 | 0.064 | 0.057 | 0.079 | 0.375 | 0.026 | 46.2 | 46.5 | 34.7 | 23.3 | 139.2 | 20.0 |
| tasks | 4.203 | 3.962 | n/a | n/a | n/a | n/a | 14.2 | 14.6 | n/a | n/a | n/a | n/a |
| url | 0.287 | 0.249 | n/a | n/a | n/a | n/a | 6.5 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.097 | 0.096 | 0.082 | 0.097 | n/a | n/a | 2.4 | 2.6 | 2.0 | 6.6 | n/a | n/a |

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
| parallel_collatz | 1 | 0.424 (0.423-0.424) | 0.424 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.251 (0.250-0.254) | 0.453 | 1.69x | 84 % | 1.07x | same |
| parallel_collatz | 4 | 0.159 (0.157-0.161) | 0.530 | 2.67x | 67 % | 1.25x | same |
| streams_parallel | 1 | 0.421 (0.421-0.421) | 0.421 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.222 (0.222-0.230) | 0.423 | 1.90x | 95 % | 1.01x | same |
| streams_parallel | 4 | 0.152 (0.151-0.152) | 0.544 | 2.78x | 69 % | 1.29x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.851 (2.824-2.875) | 4.740 | 426.2 | 32,942,986,207 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
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
