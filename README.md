# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

1 runs, 2026-10-18 to 2026-10-18. Latest: [`f9a96b20cf`](https://github.com/orin-lang/orin-lang/commit/f9a96b20cf4aedb334d2028ebecab5aab8bdf3b7).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `f9a96b20cf` (main), 2026-10-18T08:41:01Z. Machine: AMD EPYC 9V74 80-Core Processor, 4 cores, 15.6 GiB, Linux-6.17.0-1022-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.007 (0.007-0.007) | 0.006 (0.006-0.006) | 0.004 (0.004-0.005) | 0.005 (0.005-0.006) | 0.056 (0.044-0.063) | 0.003 (0.003-0.003) |
| bintrees | 0.306 (0.304-0.308) | 0.321 (0.320-0.333) | 0.457 (0.455-0.460) | 0.951 (0.950-0.955) | 0.165 (0.164-0.174) | 0.563 (0.562-0.567) |
| bytesstr | 0.027 (0.027-0.027) | 0.023 (0.023-0.023) | 0.014 (0.014-0.015) | 0.006 (0.006-0.010) | 0.051 (0.049-0.054) | 0.031 (0.029-0.031) |
| fib | 0.274 (0.274-0.274) | 0.246 (0.246-0.246) | 0.151 (0.151-0.152) | 0.514 (0.512-0.515) | 0.313 (0.311-0.324) | 0.271 (0.271-0.271) |
| html | 0.130 (0.128-0.132) | 0.102 (0.102-0.105) | 0.124 (0.124-0.124) | 0.180 (0.177-0.190) | n/a | n/a |
| html_hand | 0.100 (0.100-0.101) | 0.083 (0.081-0.085) | n/a | n/a | n/a | n/a |
| http_parse | 0.091 (0.091-0.095) | 0.078 (0.078-0.078) | n/a | n/a | n/a | n/a |
| mapfreq | 0.119 (0.119-0.119) | 0.121 (0.120-0.121) | 0.057 (0.056-0.060) | 0.084 (0.083-0.085) | n/a | n/a |
| mutres | 0.141 (0.141-0.144) | 0.088 (0.087-0.088) | 0.027 (0.027-0.027) | 0.036 (0.036-0.036) | 0.068 (0.067-0.075) | 0.033 (0.032-0.033) |
| nbody | 0.064 (0.064-0.064) | 0.064 (0.064-0.064) | 0.061 (0.061-0.061) | 0.072 (0.070-0.072) | n/a | n/a |
| pqueue | 0.123 (0.123-0.123) | 0.103 (0.102-0.104) | 0.057 (0.057-0.058) | 0.154 (0.152-0.154) | 0.174 (0.169-0.177) | 0.075 (0.074-0.075) |
| qsort_func | 0.170 (0.168-0.172) | 0.172 (0.171-0.173) | 0.183 (0.182-0.186) | 0.276 (0.268-0.279) | n/a | n/a |
| qsort_inplace | 0.094 (0.093-0.096) | 0.104 (0.102-0.107) | 0.070 (0.070-0.071) | 0.079 (0.077-0.082) | n/a | n/a |
| sieve | 0.082 (0.081-0.082) | 0.086 (0.085-0.087) | 0.074 (0.073-0.074) | 0.113 (0.103-0.121) | 0.121 (0.118-0.124) | 0.076 (0.076-0.077) |
| sortedmap | 0.206 (0.205-0.207) | 0.212 (0.211-0.214) | n/a | n/a | n/a | n/a |
| streams | 0.088 (0.088-0.088) | 0.079 (0.078-0.079) | n/a | n/a | n/a | n/a |
| strings | 0.061 (0.060-0.061) | 0.059 (0.059-0.060) | 0.053 (0.053-0.054) | 0.042 (0.040-0.046) | 0.154 (0.152-0.163) | 0.023 (0.023-0.023) |
| tasks | 3.619 (3.592-3.662) | 3.609 (3.581-3.652) | n/a | n/a | n/a | n/a |
| url | 0.282 (0.277-0.289) | 0.251 (0.249-0.257) | n/a | n/a | n/a | n/a |
| wordfreq | 0.097 (0.096-0.097) | 0.096 (0.095-0.097) | 0.082 (0.082-0.082) | 0.089 (0.088-0.089) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.61x | 1.39x | 1.23x | 12.73x | 0.74x |
| bintrees | 0.67x | 0.70x | 2.08x | 0.36x | 1.23x |
| bytesstr | 1.90x | 1.60x | 0.43x | 3.61x | 2.15x |
| fib | 1.81x | 1.63x | 3.40x | 2.07x | 1.79x |
| html | 1.05x | 0.82x | 1.45x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.09x | 2.11x | 1.47x | n/a | n/a |
| mutres | 5.18x | 3.22x | 1.33x | 2.50x | 1.21x |
| nbody | 1.05x | 1.06x | 1.18x | n/a | n/a |
| pqueue | 2.14x | 1.79x | 2.68x | 3.03x | 1.30x |
| qsort_func | 0.93x | 0.94x | 1.51x | n/a | n/a |
| qsort_inplace | 1.33x | 1.48x | 1.12x | n/a | n/a |
| sieve | 1.11x | 1.16x | 1.53x | 1.64x | 1.03x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.14x | 1.11x | 0.78x | 2.89x | 0.44x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.18x | 1.17x | 1.09x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.007 | 0.006 | 0.004 | 0.008 | 0.077 | 0.003 | 4.6 | 4.8 | 4.9 | 10.5 | 58.0 | 5.2 |
| bintrees | 0.306 | 0.321 | 0.456 | 2.027 | 0.202 | 0.563 | 17.6 | 17.9 | 9.7 | 14.2 | 307.9 | 10.1 |
| bytesstr | 0.027 | 0.023 | 0.014 | 0.009 | 0.065 | 0.030 | 11.5 | 11.9 | 11.6 | 9.9 | 108.0 | 5.0 |
| fib | 0.274 | 0.246 | 0.151 | 0.515 | 0.323 | 0.271 | 1.6 | 1.9 | 1.6 | 3.4 | 47.6 | 2.0 |
| html | 0.130 | 0.102 | 0.124 | 0.236 | n/a | n/a | 3.9 | 4.2 | 2.2 | 12.2 | n/a | n/a |
| html_hand | 0.099 | 0.083 | n/a | n/a | n/a | n/a | 2.5 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.091 | 0.077 | n/a | n/a | n/a | n/a | 1.7 | 2.1 | n/a | n/a | n/a | n/a |
| mapfreq | 0.119 | 0.120 | 0.057 | 0.096 | n/a | n/a | 11.4 | 11.7 | 5.2 | 9.9 | n/a | n/a |
| mutres | 0.141 | 0.087 | 0.027 | 0.036 | 0.091 | 0.033 | 1.6 | 1.9 | 1.6 | 3.4 | 47.9 | 2.1 |
| nbody | 0.063 | 0.064 | 0.060 | 0.072 | n/a | n/a | 1.9 | 1.9 | 1.9 | 3.4 | n/a | n/a |
| pqueue | 0.123 | 0.102 | 0.057 | 0.158 | 0.235 | 0.074 | 6.2 | 6.5 | 4.9 | 16.1 | 70.4 | 5.1 |
| qsort_func | 0.169 | 0.172 | 0.182 | 0.328 | n/a | n/a | 36.5 | 36.8 | 24.3 | 40.6 | n/a | n/a |
| qsort_inplace | 0.093 | 0.103 | 0.070 | 0.088 | n/a | n/a | 16.8 | 17.2 | 17.0 | 25.6 | n/a | n/a |
| sieve | 0.082 | 0.086 | 0.074 | 0.158 | 0.144 | 0.076 | 78.6 | 78.9 | 78.5 | 257.9 | 124.6 | 79.6 |
| sortedmap | 0.206 | 0.212 | n/a | n/a | n/a | n/a | 11.3 | 11.5 | n/a | n/a | n/a | n/a |
| streams | 0.087 | 0.078 | n/a | n/a | n/a | n/a | 42.7 | 40.9 | n/a | n/a | n/a | n/a |
| strings | 0.060 | 0.059 | 0.053 | 0.049 | 0.307 | 0.023 | 47.5 | 47.8 | 36.5 | 25.6 | 145.6 | 20.9 |
| tasks | 4.146 | 4.150 | n/a | n/a | n/a | n/a | 18.2 | 18.6 | n/a | n/a | n/a | n/a |
| url | 0.281 | 0.251 | n/a | n/a | n/a | n/a | 6.5 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.097 | 0.095 | 0.082 | 0.091 | n/a | n/a | 2.4 | 2.6 | 2.0 | 7.8 | n/a | n/a |

### Executed instructions (valgrind; the regression metric)

| benchmark | Orin C | Orin LLVM | C | Orin C/C | Orin LLVM/C | note |
|---|---:|---:|---:|---:|---:|---|
| appends | 63,530,232 | 44,305,216 | 25,381,145 | 2.50x | 1.75x |  |
| bintrees | 4,323,682,013 | 4,219,297,590 | 7,242,293,424 | 0.60x | 0.58x |  |
| bytesstr | 349,907,372 | 259,440,863 | 178,695,488 | 1.96x | 1.45x |  |
| fib | 3,200,318,135 | 2,483,953,775 | 3,170,983,196 | 1.01x | 0.78x |  |
| html | 1,784,203,884 | 1,471,870,947 | 1,581,660,476 | 1.13x | 0.93x |  |
| html_hand | 1,332,890,896 | 987,886,014 | n/a | n/a | n/a |  |
| http_parse | 1,505,848,095 | 1,315,003,738 | n/a | n/a | n/a |  |
| mapfreq | 1,050,474,760 | 994,975,460 | 719,855,456 | 1.46x | 1.38x |  |
| mutres | 2,300,280,939 | 1,420,255,607 | 291,450,138 | 7.89x | 4.87x |  |
| nbody | 850,315,519 | 772,258,282 | 651,230,701 | 1.31x | 1.19x |  |
| pqueue | 1,383,799,470 | 1,349,545,759 | 355,213,580 | 3.90x | 3.80x |  |
| qsort_func | 1,329,379,228 | 1,269,367,676 | 1,528,677,752 | 0.87x | 0.83x |  |
| qsort_inplace | 563,391,117 | 521,077,490 | 273,751,964 | 2.06x | 1.90x |  |
| sieve | 443,196,044 | 456,726,088 | 191,756,547 | 2.31x | 2.38x |  |
| sortedmap | 1,354,104,476 | 1,354,114,561 | n/a | n/a | n/a |  |
| streams | 1,173,755,255 | 1,173,731,310 | n/a | n/a | n/a |  |
| strings | 647,532,808 | 559,940,881 | 685,893,530 | 0.94x | 0.82x |  |
| tasks | n/a | n/a | n/a | n/a | n/a | llvm skipped: multi-threaded (20,000 tasks, channels): valgrind serialises threads, so the count would include scheduler waits; orin skipped: multi-threaded (20,000 tasks, channels): valgrind serialises threads, so the count would include scheduler waits |
| url | 4,455,711,379 | 4,066,091,050 | n/a | n/a | n/a |  |
| wordfreq | 760,378,197 | 707,684,200 | 880,390,180 | 0.86x | 0.80x |  |

### Parallel speedup (std:task; worker threads = first argument of the program)

| benchmark | threads | wall s (min-max) | CPU s (user+sys) | speedup | efficiency | CPU vs 1 thread | output |
|---|---:|---:|---:|---:|---:|---:|---|
| parallel_collatz | 1 | 0.417 (0.416-0.419) | 0.417 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.231 (0.228-0.232) | 0.428 | 1.81x | 90 % | 1.03x | same |
| parallel_collatz | 4 | 0.146 (0.145-0.147) | 0.511 | 2.86x | 72 % | 1.23x | same |
| streams_parallel | 1 | 0.415 (0.415-0.416) | 0.414 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.214 (0.213-0.214) | 0.416 | 1.94x | 97 % | 1.00x | same |
| streams_parallel | 4 | 0.134 (0.133-0.134) | 0.500 | 3.10x | 77 % | 1.21x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.653 (2.638-2.668) | 4.535 | 425.9 | 32,474,433,787 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
| 2026-10-18T08:41:01Z | `f9a96b20cf` | main | 32,474,433,787 | 2.653 | [json](history/2026-10-18-f9a96b20cf4a.json) |
