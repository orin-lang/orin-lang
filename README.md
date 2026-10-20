# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

3 runs, 2026-10-18 to 2026-10-20. Latest: [`4fca791aa7`](https://github.com/orin-lang/orin-lang/commit/4fca791aa7309ee95fe13c6ecee29d877c01efd9).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `4fca791aa7` (main), 2026-10-20T09:18:44Z. Machine: AMD EPYC 9V74 80-Core Processor, 4 cores, 15.6 GiB, Linux-6.17.0-1022-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.009 (0.009-0.009) | 0.007 (0.007-0.008) | 0.006 (0.005-0.006) | 0.006 (0.006-0.007) | 0.071 (0.068-0.079) | 0.004 (0.004-0.004) |
| bintrees | 0.382 (0.379-0.387) | 0.412 (0.411-0.420) | 0.630 (0.627-0.650) | 1.233 (1.224-1.240) | 0.205 (0.204-0.208) | 0.727 (0.725-0.731) |
| bytesstr | 0.035 (0.035-0.051) | 0.030 (0.030-0.030) | 0.018 (0.018-0.019) | 0.007 (0.006-0.009) | 0.062 (0.059-0.066) | 0.039 (0.038-0.040) |
| fib | 0.278 (0.278-0.284) | 0.281 (0.281-0.285) | 0.195 (0.194-0.212) | 0.665 (0.661-0.674) | 0.403 (0.398-0.409) | 0.349 (0.349-0.350) |
| html | 0.161 (0.161-0.163) | 0.129 (0.127-0.129) | 0.158 (0.152-0.158) | 0.228 (0.222-0.236) | n/a | n/a |
| html_hand | 0.133 (0.132-0.138) | 0.097 (0.094-0.098) | n/a | n/a | n/a | n/a |
| http_parse | 0.117 (0.116-0.117) | 0.100 (0.099-0.100) | n/a | n/a | n/a | n/a |
| mapfreq | 0.158 (0.158-0.160) | 0.159 (0.158-0.163) | 0.073 (0.072-0.078) | 0.108 (0.107-0.109) | n/a | n/a |
| mutres | 0.182 (0.182-0.182) | 0.113 (0.112-0.113) | 0.035 (0.035-0.035) | 0.046 (0.046-0.047) | 0.083 (0.082-0.090) | 0.041 (0.041-0.042) |
| nbody | 0.082 (0.082-0.082) | 0.084 (0.084-0.084) | 0.078 (0.078-0.078) | 0.093 (0.091-0.093) | n/a | n/a |
| pqueue | 0.159 (0.158-0.160) | 0.132 (0.131-0.135) | 0.074 (0.073-0.074) | 0.199 (0.197-0.203) | 0.227 (0.220-0.227) | 0.097 (0.097-0.098) |
| qsort_func | 0.219 (0.218-0.222) | 0.223 (0.222-0.225) | 0.234 (0.234-0.239) | 0.346 (0.336-0.382) | n/a | n/a |
| qsort_inplace | 0.121 (0.119-0.123) | 0.135 (0.133-0.140) | 0.090 (0.090-0.090) | 0.100 (0.100-0.101) | n/a | n/a |
| sieve | 0.093 (0.092-0.095) | 0.094 (0.093-0.095) | 0.083 (0.081-0.087) | 0.129 (0.125-0.134) | 0.139 (0.135-0.148) | 0.085 (0.084-0.088) |
| sortedmap | 0.263 (0.262-0.266) | 0.270 (0.269-0.270) | n/a | n/a | n/a | n/a |
| streams | 0.112 (0.108-0.112) | 0.103 (0.100-0.104) | n/a | n/a | n/a | n/a |
| strings | 0.076 (0.075-0.076) | 0.074 (0.073-0.075) | 0.068 (0.067-0.072) | 0.058 (0.054-0.061) | 0.193 (0.188-0.205) | 0.029 (0.029-0.029) |
| tasks | 4.666 (4.650-4.710) | 4.568 (4.530-4.664) | n/a | n/a | n/a | n/a |
| url | 0.355 (0.355-0.360) | 0.325 (0.323-0.330) | n/a | n/a | n/a | n/a |
| wordfreq | 0.125 (0.124-0.125) | 0.122 (0.122-0.123) | 0.112 (0.110-0.114) | 0.114 (0.114-0.115) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.61x | 1.33x | 1.15x | 12.71x | 0.73x |
| bintrees | 0.61x | 0.65x | 1.96x | 0.33x | 1.15x |
| bytesstr | 1.89x | 1.61x | 0.41x | 3.36x | 2.15x |
| fib | 1.42x | 1.44x | 3.40x | 2.06x | 1.79x |
| html | 1.02x | 0.82x | 1.45x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.17x | 2.19x | 1.48x | n/a | n/a |
| mutres | 5.17x | 3.21x | 1.31x | 2.35x | 1.16x |
| nbody | 1.05x | 1.07x | 1.19x | n/a | n/a |
| pqueue | 2.14x | 1.77x | 2.68x | 3.05x | 1.31x |
| qsort_func | 0.93x | 0.95x | 1.48x | n/a | n/a |
| qsort_inplace | 1.34x | 1.50x | 1.11x | n/a | n/a |
| sieve | 1.12x | 1.14x | 1.57x | 1.68x | 1.04x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.11x | 1.09x | 0.84x | 2.84x | 0.43x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.12x | 1.10x | 1.02x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.009 | 0.007 | 0.005 | 0.008 | 0.097 | 0.004 | 4.5 | 4.8 | 4.7 | 10.7 | 58.6 | 5.0 |
| bintrees | 0.382 | 0.411 | 0.630 | 2.629 | 0.254 | 0.727 | 17.5 | 17.9 | 9.5 | 14.4 | 307.9 | 10.0 |
| bytesstr | 0.034 | 0.029 | 0.018 | 0.012 | 0.081 | 0.039 | 11.5 | 11.7 | 11.5 | 9.9 | 108.1 | 4.8 |
| fib | 0.277 | 0.281 | 0.195 | 0.666 | 0.414 | 0.349 | 1.5 | 1.7 | 1.5 | 3.4 | 47.5 | 2.0 |
| html | 0.161 | 0.128 | 0.157 | 0.305 | n/a | n/a | 3.7 | 4.1 | 2.1 | 8.5 | n/a | n/a |
| html_hand | 0.133 | 0.096 | n/a | n/a | n/a | n/a | 2.4 | 2.7 | n/a | n/a | n/a | n/a |
| http_parse | 0.116 | 0.099 | n/a | n/a | n/a | n/a | 1.6 | 2.0 | n/a | n/a | n/a | n/a |
| mapfreq | 0.158 | 0.159 | 0.073 | 0.123 | n/a | n/a | 11.3 | 11.5 | 5.1 | 9.9 | n/a | n/a |
| mutres | 0.181 | 0.112 | 0.035 | 0.046 | 0.114 | 0.041 | 1.5 | 1.8 | 1.5 | 3.4 | 47.7 | 2.0 |
| nbody | 0.082 | 0.083 | 0.078 | 0.093 | n/a | n/a | 1.8 | 1.8 | 1.9 | 3.4 | n/a | n/a |
| pqueue | 0.159 | 0.131 | 0.074 | 0.204 | 0.299 | 0.097 | 6.1 | 6.3 | 4.7 | 15.9 | 70.4 | 5.0 |
| qsort_func | 0.219 | 0.223 | 0.234 | 0.405 | n/a | n/a | 36.4 | 36.7 | 24.5 | 41.5 | n/a | n/a |
| qsort_inplace | 0.120 | 0.134 | 0.090 | 0.106 | n/a | n/a | 16.7 | 17.0 | 16.8 | 37.2 | n/a | n/a |
| sieve | 0.092 | 0.094 | 0.082 | 0.173 | 0.166 | 0.085 | 78.5 | 78.8 | 78.4 | 265.8 | 124.4 | 79.5 |
| sortedmap | 0.263 | 0.270 | n/a | n/a | n/a | n/a | 11.1 | 11.5 | n/a | n/a | n/a | n/a |
| streams | 0.111 | 0.103 | n/a | n/a | n/a | n/a | 43.3 | 41.3 | n/a | n/a | n/a | n/a |
| strings | 0.075 | 0.074 | 0.068 | 0.072 | 0.393 | 0.029 | 47.4 | 47.6 | 34.5 | 24.1 | 145.3 | 20.1 |
| tasks | 5.426 | 5.214 | n/a | n/a | n/a | n/a | 18.0 | 18.4 | n/a | n/a | n/a | n/a |
| url | 0.355 | 0.324 | n/a | n/a | n/a | n/a | 6.4 | 6.7 | n/a | n/a | n/a | n/a |
| wordfreq | 0.125 | 0.122 | 0.111 | 0.117 | n/a | n/a | 2.2 | 2.5 | 1.9 | 7.9 | n/a | n/a |

### Executed instructions (valgrind; the regression metric)

| benchmark | Orin C | Orin LLVM | C | Orin C/C | Orin LLVM/C | note |
|---|---:|---:|---:|---:|---:|---|
| appends | 63,534,233 | 44,305,088 | 25,381,145 | 2.50x | 1.75x |  |
| bintrees | 4,323,686,014 | 4,219,297,489 | 7,242,293,424 | 0.60x | 0.58x |  |
| bytesstr | 349,911,373 | 259,440,782 | 178,695,488 | 1.96x | 1.45x |  |
| fib | 3,200,322,136 | 2,483,953,679 | 3,170,983,196 | 1.01x | 0.78x |  |
| html | 1,784,207,986 | 1,465,345,246 | 1,581,660,476 | 1.13x | 0.93x |  |
| html_hand | 1,332,894,998 | 980,559,913 | n/a | n/a | n/a |  |
| http_parse | 1,507,540,351 | 1,314,002,038 | n/a | n/a | n/a |  |
| mapfreq | 1,050,478,761 | 993,975,339 | 719,855,456 | 1.46x | 1.38x |  |
| mutres | 2,300,284,940 | 1,420,255,508 | 291,450,138 | 7.89x | 4.87x |  |
| nbody | 850,319,852 | 772,258,414 | 651,230,701 | 1.31x | 1.19x |  |
| pqueue | 1,383,803,471 | 1,349,545,638 | 355,213,580 | 3.90x | 3.80x |  |
| qsort_func | 1,329,383,229 | 1,268,411,994 | 1,528,677,752 | 0.87x | 0.83x |  |
| qsort_inplace | 563,395,118 | 521,077,370 | 273,751,964 | 2.06x | 1.90x |  |
| sieve | 443,200,045 | 456,725,969 | 191,756,547 | 2.31x | 2.38x |  |
| sortedmap | 1,354,108,477 | 1,354,047,084 | n/a | n/a | n/a |  |
| streams | 1,173,759,256 | 1,173,731,192 | n/a | n/a | n/a |  |
| strings | 647,536,809 | 558,940,756 | 685,893,530 | 0.94x | 0.81x |  |
| tasks | n/a | n/a | n/a | n/a | n/a | llvm skipped: multi-threaded (20,000 tasks, channels): valgrind serialises threads, so the count would include scheduler waits; orin skipped: multi-threaded (20,000 tasks, channels): valgrind serialises threads, so the count would include scheduler waits |
| url | 4,455,715,380 | 4,066,090,932 | n/a | n/a | n/a |  |
| wordfreq | 760,382,198 | 706,684,079 | 880,390,180 | 0.86x | 0.80x |  |

### Parallel speedup (std:task; worker threads = first argument of the program)

| benchmark | threads | wall s (min-max) | CPU s (user+sys) | speedup | efficiency | CPU vs 1 thread | output |
|---|---:|---:|---:|---:|---:|---:|---|
| parallel_collatz | 1 | 0.535 (0.534-0.535) | 0.534 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.293 (0.292-0.294) | 0.546 | 1.83x | 91 % | 1.02x | same |
| parallel_collatz | 4 | 0.198 (0.198-0.199) | 0.701 | 2.70x | 67 % | 1.31x | same |
| streams_parallel | 1 | 0.530 (0.530-0.530) | 0.530 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.273 (0.272-0.273) | 0.531 | 1.94x | 97 % | 1.00x | same |
| streams_parallel | 4 | 0.183 (0.183-0.183) | 0.688 | 2.89x | 72 % | 1.30x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 3.135 (3.117-3.197) | 5.649 | 429.2 | 32,689,556,132 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
| 2026-10-20T09:18:44Z | `4fca791aa7` | main | 32,689,556,132 | 3.135 | [json](history/2026-10-20-4fca791aa730.json) |
| 2026-10-19T09:42:12Z | `4fca791aa7` | main | 32,690,856,642 | 2.491 | [json](history/2026-10-19-4fca791aa730.json) |
| 2026-10-18T08:41:01Z | `f9a96b20cf` | main | 32,474,433,787 | 2.653 | [json](history/2026-10-18-f9a96b20cf4a.json) |
