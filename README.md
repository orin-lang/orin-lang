# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

10 runs, 2026-10-18 to 2026-10-27. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-10-27T09:43:14Z. Machine: AMD EPYC 9V74 80-Core Processor, 4 cores, 15.6 GiB, Linux-6.17.0-1022-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.007 (0.007-0.007) | 0.007 (0.007-0.007) | 0.005 (0.005-0.005) | 0.006 (0.006-0.007) | 0.059 (0.053-0.077) | 0.004 (0.003-0.004) |
| bintrees | 0.312 (0.310-0.316) | 0.320 (0.318-0.326) | 0.455 (0.454-0.464) | 0.961 (0.951-0.964) | 0.176 (0.171-0.259) | 0.567 (0.565-0.577) |
| bytesstr | 0.028 (0.028-0.029) | 0.023 (0.023-0.137) | 0.015 (0.014-0.165) | 0.006 (0.005-0.176) | 0.051 (0.049-0.110) | 0.031 (0.029-0.032) |
| fib | 0.244 (0.243-0.244) | 0.246 (0.246-0.247) | 0.151 (0.151-0.151) | 0.515 (0.514-0.515) | 0.312 (0.310-0.318) | 0.271 (0.271-0.271) |
| html | 0.124 (0.124-0.127) | 0.102 (0.100-0.104) | 0.124 (0.123-0.129) | 0.184 (0.173-0.184) | n/a | n/a |
| html_hand | 0.104 (0.104-0.107) | 0.081 (0.080-0.083) | n/a | n/a | n/a | n/a |
| http_parse | 0.091 (0.091-0.091) | 0.077 (0.077-0.077) | n/a | n/a | n/a | n/a |
| mapfreq | 0.119 (0.118-0.119) | 0.120 (0.119-0.120) | 0.058 (0.056-0.060) | 0.084 (0.083-0.085) | n/a | n/a |
| mutres | 0.137 (0.137-0.607) | 0.088 (0.087-0.088) | 0.027 (0.027-0.027) | 0.036 (0.036-0.036) | 0.067 (0.065-0.078) | 0.032 (0.032-0.033) |
| nbody | 0.064 (0.064-0.064) | 0.064 (0.064-0.157) | 0.061 (0.061-0.061) | 0.071 (0.069-0.072) | n/a | n/a |
| pqueue | 0.123 (0.123-0.210) | 0.102 (0.101-0.103) | 0.058 (0.057-0.131) | 0.153 (0.152-0.158) | 0.177 (0.164-0.179) | 0.075 (0.075-0.118) |
| qsort_func | 0.172 (0.168-0.174) | 0.171 (0.171-0.171) | 0.184 (0.181-0.185) | 0.271 (0.269-0.287) | n/a | n/a |
| qsort_inplace | 0.096 (0.093-0.096) | 0.103 (0.103-0.105) | 0.070 (0.070-0.070) | 0.079 (0.078-0.134) | n/a | n/a |
| sieve | 0.084 (0.083-0.087) | 0.087 (0.085-0.091) | 0.077 (0.075-0.077) | 0.118 (0.115-0.127) | 0.121 (0.120-0.124) | 0.078 (0.077-0.078) |
| sortedmap | 0.205 (0.204-0.219) | 0.211 (0.210-0.211) | n/a | n/a | n/a | n/a |
| streams | 0.088 (0.087-0.090) | 0.079 (0.079-0.079) | n/a | n/a | n/a | n/a |
| strings | 0.062 (0.062-0.063) | 0.061 (0.060-0.113) | 0.053 (0.053-0.053) | 0.042 (0.041-0.043) | 0.152 (0.151-0.166) | 0.023 (0.023-0.024) |
| tasks | 3.762 (3.722-3.802) | 3.735 (3.680-3.806) | n/a | n/a | n/a | n/a |
| url | 0.285 (0.284-0.287) | 0.246 (0.246-0.250) | n/a | n/a | n/a | n/a |
| wordfreq | 0.097 (0.097-0.098) | 0.096 (0.096-0.096) | 0.082 (0.082-0.090) | 0.089 (0.088-0.154) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.46x | 1.40x | 1.29x | 12.15x | 0.77x |
| bintrees | 0.69x | 0.70x | 2.11x | 0.39x | 1.25x |
| bytesstr | 1.84x | 1.56x | 0.39x | 3.41x | 2.08x |
| fib | 1.61x | 1.63x | 3.41x | 2.07x | 1.80x |
| html | 1.00x | 0.82x | 1.48x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.05x | 2.07x | 1.45x | n/a | n/a |
| mutres | 5.04x | 3.22x | 1.33x | 2.46x | 1.16x |
| nbody | 1.06x | 1.06x | 1.17x | n/a | n/a |
| pqueue | 2.12x | 1.76x | 2.64x | 3.04x | 1.28x |
| qsort_func | 0.93x | 0.93x | 1.47x | n/a | n/a |
| qsort_inplace | 1.36x | 1.47x | 1.13x | n/a | n/a |
| sieve | 1.09x | 1.13x | 1.53x | 1.58x | 1.01x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.17x | 1.16x | 0.79x | 2.86x | 0.44x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.18x | 1.17x | 1.08x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.007 | 0.007 | 0.005 | 0.008 | 0.077 | 0.003 | 4.6 | 4.9 | 4.9 | 9.8 | 58.8 | 5.1 |
| bintrees | 0.312 | 0.320 | 0.455 | 2.035 | 0.215 | 0.567 | 17.6 | 17.9 | 9.7 | 14.3 | 307.9 | 10.1 |
| bytesstr | 0.027 | 0.023 | 0.015 | 0.009 | 0.066 | 0.031 | 11.6 | 11.8 | 11.6 | 9.9 | 108.1 | 5.0 |
| fib | 0.243 | 0.246 | 0.151 | 0.516 | 0.322 | 0.271 | 1.6 | 1.9 | 1.6 | 3.4 | 47.5 | 2.1 |
| html | 0.124 | 0.101 | 0.124 | 0.247 | n/a | n/a | 3.9 | 4.2 | 2.2 | 8.3 | n/a | n/a |
| html_hand | 0.104 | 0.080 | n/a | n/a | n/a | n/a | 2.5 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.090 | 0.077 | n/a | n/a | n/a | n/a | 1.7 | 2.1 | n/a | n/a | n/a | n/a |
| mapfreq | 0.119 | 0.120 | 0.058 | 0.095 | n/a | n/a | 11.4 | 11.6 | 5.2 | 8.1 | n/a | n/a |
| mutres | 0.137 | 0.087 | 0.027 | 0.036 | 0.092 | 0.031 | 1.6 | 1.9 | 1.6 | 3.4 | 47.9 | 2.1 |
| nbody | 0.064 | 0.064 | 0.060 | 0.071 | n/a | n/a | 1.9 | 1.9 | 2.0 | 3.4 | n/a | n/a |
| pqueue | 0.123 | 0.102 | 0.057 | 0.156 | 0.226 | 0.074 | 6.2 | 6.5 | 4.9 | 16.0 | 70.3 | 5.1 |
| qsort_func | 0.171 | 0.171 | 0.184 | 0.317 | n/a | n/a | 36.5 | 36.8 | 23.7 | 40.5 | n/a | n/a |
| qsort_inplace | 0.095 | 0.103 | 0.070 | 0.086 | n/a | n/a | 16.8 | 17.1 | 17.0 | 27.5 | n/a | n/a |
| sieve | 0.084 | 0.087 | 0.076 | 0.159 | 0.143 | 0.077 | 78.6 | 78.9 | 78.9 | 285.9 | 124.5 | 79.2 |
| sortedmap | 0.204 | 0.211 | n/a | n/a | n/a | n/a | 11.3 | 11.5 | n/a | n/a | n/a | n/a |
| streams | 0.087 | 0.079 | n/a | n/a | n/a | n/a | 42.7 | 40.9 | n/a | n/a | n/a | n/a |
| strings | 0.062 | 0.059 | 0.053 | 0.049 | 0.313 | 0.023 | 47.4 | 47.8 | 36.5 | 25.5 | 145.4 | 21.9 |
| tasks | 4.300 | 4.247 | n/a | n/a | n/a | n/a | 18.2 | 18.5 | n/a | n/a | n/a | n/a |
| url | 0.285 | 0.246 | n/a | n/a | n/a | n/a | 6.5 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.097 | 0.096 | 0.082 | 0.091 | n/a | n/a | 2.4 | 2.6 | 2.0 | 7.9 | n/a | n/a |

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
| parallel_collatz | 1 | 0.419 (0.416-0.477) | 0.418 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.237 (0.231-0.287) | 0.429 | 1.77x | 88 % | 1.03x | same |
| parallel_collatz | 4 | 0.148 (0.146-0.148) | 0.513 | 2.83x | 71 % | 1.23x | same |
| streams_parallel | 1 | 0.412 (0.412-0.413) | 0.412 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.214 (0.213-0.227) | 0.414 | 1.92x | 96 % | 1.01x | same |
| streams_parallel | 4 | 0.143 (0.142-0.144) | 0.534 | 2.89x | 72 % | 1.30x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.709 (2.675-2.781) | 4.643 | 432.2 | 32,942,699,177 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
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
