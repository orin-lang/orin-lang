# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

7 runs, 2026-10-18 to 2026-10-24. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-10-24T08:45:58Z. Machine: AMD EPYC 9V74 80-Core Processor, 4 cores, 15.6 GiB, Linux-6.17.0-1022-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.007 (0.007-0.007) | 0.006 (0.006-0.006) | 0.004 (0.004-0.005) | 0.006 (0.005-0.006) | 0.059 (0.052-0.065) | 0.003 (0.003-0.069) |
| bintrees | 0.311 (0.310-0.315) | 0.312 (0.310-0.315) | 0.454 (0.452-0.459) | 0.958 (0.953-0.961) | 0.165 (0.163-0.166) | 0.567 (0.564-0.569) |
| bytesstr | 0.028 (0.028-0.080) | 0.024 (0.024-0.024) | 0.015 (0.014-0.015) | 0.007 (0.005-0.024) | 0.053 (0.050-0.057) | 0.032 (0.031-0.057) |
| fib | 0.243 (0.243-0.244) | 0.246 (0.246-0.246) | 0.151 (0.150-0.151) | 0.514 (0.512-0.515) | 0.315 (0.312-0.322) | 0.271 (0.271-0.271) |
| html | 0.124 (0.124-0.127) | 0.102 (0.100-0.104) | 0.124 (0.119-0.125) | 0.180 (0.170-0.186) | n/a | n/a |
| html_hand | 0.104 (0.104-0.120) | 0.083 (0.081-0.107) | n/a | n/a | n/a | n/a |
| http_parse | 0.091 (0.091-0.093) | 0.078 (0.077-0.078) | n/a | n/a | n/a | n/a |
| mapfreq | 0.119 (0.118-0.120) | 0.121 (0.120-0.121) | 0.058 (0.057-0.058) | 0.085 (0.084-0.131) | n/a | n/a |
| mutres | 0.137 (0.137-0.137) | 0.087 (0.087-0.088) | 0.027 (0.027-0.027) | 0.036 (0.036-0.036) | 0.071 (0.066-0.104) | 0.033 (0.032-0.033) |
| nbody | 0.064 (0.064-0.064) | 0.065 (0.064-0.065) | 0.061 (0.061-0.061) | 0.072 (0.072-0.072) | n/a | n/a |
| pqueue | 0.125 (0.123-0.127) | 0.108 (0.105-0.111) | 0.059 (0.058-0.059) | 0.157 (0.153-0.158) | 0.177 (0.175-0.178) | 0.077 (0.075-0.078) |
| qsort_func | 0.172 (0.171-0.175) | 0.173 (0.172-0.176) | 0.185 (0.182-0.185) | 0.275 (0.271-0.287) | n/a | n/a |
| qsort_inplace | 0.096 (0.093-0.096) | 0.103 (0.099-0.104) | 0.070 (0.070-0.070) | 0.080 (0.078-0.081) | n/a | n/a |
| sieve | 0.089 (0.089-0.090) | 0.091 (0.090-0.093) | 0.080 (0.079-0.081) | 0.116 (0.113-0.126) | 0.128 (0.125-0.129) | 0.082 (0.082-0.083) |
| sortedmap | 0.209 (0.207-0.213) | 0.213 (0.212-0.218) | n/a | n/a | n/a | n/a |
| streams | 0.087 (0.086-0.087) | 0.078 (0.078-0.080) | n/a | n/a | n/a | n/a |
| strings | 0.063 (0.062-0.063) | 0.061 (0.060-0.061) | 0.053 (0.053-0.054) | 0.043 (0.041-0.044) | 0.158 (0.154-0.162) | 0.024 (0.023-0.025) |
| tasks | 3.710 (3.665-3.716) | 3.707 (3.678-3.736) | n/a | n/a | n/a | n/a |
| url | 0.285 (0.282-0.289) | 0.246 (0.245-0.254) | n/a | n/a | n/a | n/a |
| wordfreq | 0.097 (0.097-0.098) | 0.096 (0.096-0.097) | 0.082 (0.082-0.141) | 0.090 (0.089-0.090) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.58x | 1.39x | 1.26x | 13.20x | 0.77x |
| bintrees | 0.68x | 0.69x | 2.11x | 0.36x | 1.25x |
| bytesstr | 1.89x | 1.61x | 0.50x | 3.63x | 2.15x |
| fib | 1.61x | 1.63x | 3.41x | 2.09x | 1.80x |
| html | 1.00x | 0.82x | 1.45x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.06x | 2.09x | 1.47x | n/a | n/a |
| mutres | 5.02x | 3.20x | 1.32x | 2.59x | 1.21x |
| nbody | 1.05x | 1.06x | 1.18x | n/a | n/a |
| pqueue | 2.14x | 1.84x | 2.68x | 3.03x | 1.31x |
| qsort_func | 0.93x | 0.94x | 1.49x | n/a | n/a |
| qsort_inplace | 1.36x | 1.46x | 1.13x | n/a | n/a |
| sieve | 1.11x | 1.13x | 1.45x | 1.58x | 1.02x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.17x | 1.14x | 0.80x | 2.95x | 0.44x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.18x | 1.17x | 1.09x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.007 | 0.006 | 0.004 | 0.007 | 0.077 | 0.003 | 4.6 | 4.8 | 4.9 | 9.8 | 58.5 | 5.2 |
| bintrees | 0.311 | 0.312 | 0.454 | 2.031 | 0.204 | 0.566 | 17.6 | 17.9 | 9.7 | 14.4 | 307.8 | 10.2 |
| bytesstr | 0.028 | 0.023 | 0.014 | 0.012 | 0.067 | 0.031 | 11.6 | 11.8 | 11.7 | 9.6 | 108.1 | 5.0 |
| fib | 0.243 | 0.246 | 0.150 | 0.515 | 0.325 | 0.271 | 1.6 | 1.9 | 1.6 | 3.4 | 47.6 | 2.1 |
| html | 0.124 | 0.102 | 0.124 | 0.242 | n/a | n/a | 3.9 | 4.2 | 2.2 | 8.3 | n/a | n/a |
| html_hand | 0.104 | 0.081 | n/a | n/a | n/a | n/a | 2.5 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.091 | 0.077 | n/a | n/a | n/a | n/a | 1.7 | 2.1 | n/a | n/a | n/a | n/a |
| mapfreq | 0.119 | 0.120 | 0.057 | 0.094 | n/a | n/a | 11.4 | 11.6 | 5.2 | 10.0 | n/a | n/a |
| mutres | 0.137 | 0.087 | 0.027 | 0.036 | 0.092 | 0.033 | 1.6 | 1.9 | 1.6 | 3.4 | 47.9 | 2.1 |
| nbody | 0.063 | 0.064 | 0.060 | 0.072 | n/a | n/a | 1.9 | 1.9 | 2.0 | 3.4 | n/a | n/a |
| pqueue | 0.125 | 0.107 | 0.058 | 0.160 | 0.239 | 0.076 | 6.2 | 6.5 | 4.9 | 16.1 | 70.4 | 5.1 |
| qsort_func | 0.172 | 0.173 | 0.184 | 0.325 | n/a | n/a | 36.6 | 36.7 | 24.2 | 41.1 | n/a | n/a |
| qsort_inplace | 0.095 | 0.102 | 0.070 | 0.085 | n/a | n/a | 16.8 | 17.1 | 16.9 | 31.6 | n/a | n/a |
| sieve | 0.089 | 0.090 | 0.080 | 0.161 | 0.150 | 0.082 | 78.6 | 78.9 | 78.5 | 239.9 | 124.6 | 79.1 |
| sortedmap | 0.208 | 0.213 | n/a | n/a | n/a | n/a | 11.3 | 11.5 | n/a | n/a | n/a | n/a |
| streams | 0.087 | 0.078 | n/a | n/a | n/a | n/a | 42.7 | 40.9 | n/a | n/a | n/a | n/a |
| strings | 0.062 | 0.061 | 0.053 | 0.050 | 0.314 | 0.023 | 47.5 | 47.8 | 36.5 | 25.7 | 145.6 | 20.1 |
| tasks | 4.258 | 4.225 | n/a | n/a | n/a | n/a | 18.2 | 18.6 | n/a | n/a | n/a | n/a |
| url | 0.284 | 0.246 | n/a | n/a | n/a | n/a | 6.5 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.097 | 0.096 | 0.082 | 0.092 | n/a | n/a | 2.4 | 2.6 | 2.0 | 7.9 | n/a | n/a |

### Executed instructions (valgrind; the regression metric)

| benchmark | Orin C | Orin LLVM | C | Orin C/C | Orin LLVM/C | note |
|---|---:|---:|---:|---:|---:|---|
| appends | 63,532,187 | 44,305,032 | 25,381,145 | 2.50x | 1.75x |  |
| bintrees | 4,323,683,959 | 4,219,297,433 | 7,242,293,424 | 0.60x | 0.58x |  |
| bytesstr | 349,909,247 | 259,440,726 | 178,695,488 | 1.96x | 1.45x |  |
| fib | 3,200,320,090 | 2,483,953,632 | 3,170,983,196 | 1.01x | 0.78x |  |
| html | 1,786,500,083 | 1,465,345,190 | 1,581,660,476 | 1.13x | 0.93x |  |
| html_hand | 1,335,187,104 | 980,559,857 | n/a | n/a | n/a |  |
| http_parse | 1,494,543,487 | 1,314,023,622 | n/a | n/a | n/a |  |
| mapfreq | 1,050,476,715 | 993,975,283 | 719,855,456 | 1.46x | 1.38x |  |
| mutres | 2,300,282,894 | 1,420,255,452 | 291,450,138 | 7.89x | 4.87x |  |
| nbody | 850,321,961 | 772,258,358 | 651,230,701 | 1.31x | 1.19x |  |
| pqueue | 1,383,801,416 | 1,349,545,582 | 355,213,580 | 3.90x | 3.80x |  |
| qsort_func | 1,335,897,346 | 1,268,411,938 | 1,528,677,752 | 0.87x | 0.83x |  |
| qsort_inplace | 563,393,087 | 521,077,314 | 273,751,964 | 2.06x | 1.90x |  |
| sieve | 443,197,999 | 456,725,913 | 191,756,547 | 2.31x | 2.38x |  |
| sortedmap | 1,354,678,405 | 1,354,047,028 | n/a | n/a | n/a |  |
| streams | 1,173,757,219 | 1,173,731,136 | n/a | n/a | n/a |  |
| strings | 647,534,763 | 558,940,700 | 685,893,530 | 0.94x | 0.81x |  |
| tasks | n/a | n/a | n/a | n/a | n/a | llvm skipped: multi-threaded (20,000 tasks, channels): valgrind serialises threads, so the count would include scheduler waits; orin skipped: multi-threaded (20,000 tasks, channels): valgrind serialises threads, so the count would include scheduler waits |
| url | 4,455,707,373 | 4,066,090,876 | n/a | n/a | n/a |  |
| wordfreq | 760,380,161 | 706,684,023 | 880,390,180 | 0.86x | 0.80x |  |

### Parallel speedup (std:task; worker threads = first argument of the program)

| benchmark | threads | wall s (min-max) | CPU s (user+sys) | speedup | efficiency | CPU vs 1 thread | output |
|---|---:|---:|---:|---:|---:|---:|---|
| parallel_collatz | 1 | 0.418 (0.417-0.420) | 0.417 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.231 (0.230-0.231) | 0.429 | 1.81x | 91 % | 1.03x | same |
| parallel_collatz | 4 | 0.147 (0.146-0.147) | 0.513 | 2.85x | 71 % | 1.23x | same |
| streams_parallel | 1 | 0.412 (0.412-0.413) | 0.412 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.213 (0.212-0.213) | 0.413 | 1.94x | 97 % | 1.00x | same |
| streams_parallel | 4 | 0.143 (0.143-0.143) | 0.535 | 2.89x | 72 % | 1.30x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.841 (2.801-2.883) | 4.689 | 431.5 | 32,941,665,170 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
| 2026-10-24T08:45:58Z | `148472c2cd` | main | 32,941,665,170 | 2.841 | [json](history/2026-10-24-148472c2cdb0.json) |
| 2026-10-23T09:15:05Z | `148472c2cd` | main | 32,944,434,877 | 3.020 | [json](history/2026-10-23-148472c2cdb0.json) |
| 2026-10-22T09:19:15Z | `148472c2cd` | main | 32,948,490,800 | 2.785 | [json](history/2026-10-22-148472c2cdb0.json) |
| 2026-10-21T09:18:17Z | `148472c2cd` | main | 32,944,599,759 | 3.076 | [json](history/2026-10-21-148472c2cdb0.json) |
| 2026-10-20T09:18:44Z | `4fca791aa7` | main | 32,689,556,132 | 3.135 | [json](history/2026-10-20-4fca791aa730.json) |
| 2026-10-19T09:42:12Z | `4fca791aa7` | main | 32,690,856,642 | 2.491 | [json](history/2026-10-19-4fca791aa730.json) |
| 2026-10-18T08:41:01Z | `f9a96b20cf` | main | 32,474,433,787 | 2.653 | [json](history/2026-10-18-f9a96b20cf4a.json) |
