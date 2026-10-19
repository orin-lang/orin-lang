# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

2 runs, 2026-10-18 to 2026-10-19. Latest: [`4fca791aa7`](https://github.com/orin-lang/orin-lang/commit/4fca791aa7309ee95fe13c6ecee29d877c01efd9).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `4fca791aa7` (main), 2026-10-19T09:42:12Z. Machine: Intel(R) Xeon(R) 6973P-C, 4 cores, 15.6 GiB, Linux-6.17.0-1022-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.005 (0.005-0.006) | 0.004 (0.004-0.005) | 0.004 (0.003-0.004) | 0.007 (0.006-0.008) | 0.062 (0.057-0.065) | 0.003 (0.003-0.003) |
| bintrees | 0.331 (0.325-0.368) | 0.350 (0.348-0.354) | 0.403 (0.396-0.417) | 0.844 (0.836-0.851) | 0.258 (0.245-0.264) | 0.505 (0.502-0.511) |
| bytesstr | 0.033 (0.031-0.034) | 0.032 (0.030-0.033) | 0.031 (0.029-0.032) | 0.007 (0.007-0.007) | 0.076 (0.072-0.077) | 0.024 (0.024-0.024) |
| fib | 0.203 (0.201-0.221) | 0.208 (0.208-0.208) | 0.131 (0.131-0.131) | 0.400 (0.397-0.422) | 0.335 (0.333-0.341) | 0.223 (0.222-0.223) |
| html | 0.113 (0.112-0.113) | 0.090 (0.090-0.092) | 0.106 (0.105-0.107) | 0.210 (0.204-0.226) | n/a | n/a |
| html_hand | 0.087 (0.086-0.087) | 0.069 (0.069-0.069) | n/a | n/a | n/a | n/a |
| http_parse | 0.086 (0.084-0.090) | 0.069 (0.069-0.069) | n/a | n/a | n/a | n/a |
| mapfreq | 0.113 (0.112-0.113) | 0.114 (0.112-0.114) | 0.054 (0.050-0.055) | 0.080 (0.079-0.081) | n/a | n/a |
| mutres | 0.098 (0.096-0.125) | 0.069 (0.067-0.076) | 0.019 (0.019-0.022) | 0.058 (0.058-0.062) | 0.066 (0.065-0.068) | 0.025 (0.024-0.025) |
| nbody | 0.045 (0.044-0.045) | 0.044 (0.044-0.044) | 0.043 (0.042-0.045) | 0.066 (0.066-0.066) | n/a | n/a |
| pqueue | 0.127 (0.116-0.133) | 0.092 (0.091-0.095) | 0.057 (0.057-0.058) | 0.137 (0.134-0.138) | 0.183 (0.178-0.186) | 0.069 (0.067-0.069) |
| qsort_func | 0.166 (0.162-0.167) | 0.167 (0.165-0.169) | 0.193 (0.185-0.196) | 0.315 (0.297-0.336) | n/a | n/a |
| qsort_inplace | 0.096 (0.095-0.099) | 0.094 (0.094-0.095) | 0.072 (0.071-0.074) | 0.080 (0.080-0.083) | n/a | n/a |
| sieve | 0.124 (0.107-0.142) | 0.110 (0.107-0.118) | 0.109 (0.104-0.122) | 0.175 (0.166-0.188) | 0.173 (0.156-0.208) | 0.106 (0.093-0.112) |
| sortedmap | 0.200 (0.196-0.203) | 0.208 (0.205-0.221) | n/a | n/a | n/a | n/a |
| streams | 0.074 (0.063-0.076) | 0.062 (0.059-0.072) | n/a | n/a | n/a | n/a |
| strings | 0.052 (0.047-0.068) | 0.051 (0.048-0.053) | 0.049 (0.048-0.055) | 0.039 (0.038-0.044) | 0.164 (0.163-0.171) | 0.022 (0.022-0.022) |
| tasks | 4.030 (3.525-4.110) | 3.995 (3.925-4.003) | n/a | n/a | n/a | n/a |
| url | 0.242 (0.241-0.242) | 0.225 (0.225-0.249) | n/a | n/a | n/a | n/a |
| wordfreq | 0.085 (0.085-0.086) | 0.083 (0.083-0.083) | 0.074 (0.074-0.074) | 0.083 (0.083-0.083) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.50x | 1.22x | 2.00x | 17.39x | 0.86x |
| bintrees | 0.82x | 0.87x | 2.09x | 0.64x | 1.25x |
| bytesstr | 1.08x | 1.05x | 0.23x | 2.46x | 0.79x |
| fib | 1.55x | 1.59x | 3.05x | 2.56x | 1.70x |
| html | 1.07x | 0.85x | 1.98x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 2.08x | 2.10x | 1.48x | n/a | n/a |
| mutres | 5.10x | 3.57x | 3.01x | 3.42x | 1.28x |
| nbody | 1.03x | 1.02x | 1.53x | n/a | n/a |
| pqueue | 2.22x | 1.61x | 2.40x | 3.21x | 1.21x |
| qsort_func | 0.86x | 0.86x | 1.63x | n/a | n/a |
| qsort_inplace | 1.34x | 1.32x | 1.12x | n/a | n/a |
| sieve | 1.14x | 1.00x | 1.61x | 1.58x | 0.97x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.05x | 1.04x | 0.80x | 3.32x | 0.44x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.15x | 1.12x | 1.12x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.005 | 0.004 | 0.003 | 0.009 | 0.082 | 0.003 | 4.6 | 4.8 | 4.9 | 9.7 | 58.0 | 5.1 |
| bintrees | 0.328 | 0.348 | 0.402 | 1.873 | 0.302 | 0.505 | 17.6 | 17.9 | 9.7 | 14.5 | 307.8 | 10.1 |
| bytesstr | 0.033 | 0.032 | 0.029 | 0.009 | 0.092 | 0.024 | 11.6 | 11.9 | 11.6 | 7.8 | 108.2 | 5.0 |
| fib | 0.202 | 0.207 | 0.130 | 0.401 | 0.346 | 0.222 | 1.6 | 1.9 | 1.6 | 3.4 | 47.5 | 2.1 |
| html | 0.112 | 0.090 | 0.106 | 0.266 | n/a | n/a | 3.9 | 4.2 | 2.2 | 10.2 | n/a | n/a |
| html_hand | 0.086 | 0.068 | n/a | n/a | n/a | n/a | 2.5 | 2.8 | n/a | n/a | n/a | n/a |
| http_parse | 0.085 | 0.069 | n/a | n/a | n/a | n/a | 1.7 | 2.1 | n/a | n/a | n/a | n/a |
| mapfreq | 0.112 | 0.113 | 0.054 | 0.096 | n/a | n/a | 11.4 | 11.6 | 5.2 | 9.9 | n/a | n/a |
| mutres | 0.098 | 0.068 | 0.019 | 0.058 | 0.089 | 0.024 | 1.6 | 1.9 | 1.6 | 3.4 | 47.9 | 2.1 |
| nbody | 0.044 | 0.043 | 0.043 | 0.066 | n/a | n/a | 1.9 | 1.9 | 2.0 | 3.4 | n/a | n/a |
| pqueue | 0.125 | 0.092 | 0.056 | 0.141 | 0.242 | 0.069 | 6.3 | 6.5 | 4.9 | 16.1 | 70.4 | 5.1 |
| qsort_func | 0.165 | 0.166 | 0.192 | 0.372 | n/a | n/a | 36.6 | 36.8 | 24.2 | 38.5 | n/a | n/a |
| qsort_inplace | 0.095 | 0.094 | 0.071 | 0.092 | n/a | n/a | 16.8 | 17.0 | 17.0 | 25.7 | n/a | n/a |
| sieve | 0.123 | 0.109 | 0.108 | 0.246 | 0.193 | 0.105 | 79.1 | 79.4 | 78.5 | 188.0 | 124.6 | 79.6 |
| sortedmap | 0.199 | 0.207 | n/a | n/a | n/a | n/a | 11.3 | 11.5 | n/a | n/a | n/a | n/a |
| streams | 0.073 | 0.062 | n/a | n/a | n/a | n/a | 43.2 | 40.9 | n/a | n/a | n/a | n/a |
| strings | 0.051 | 0.051 | 0.049 | 0.046 | 0.340 | 0.022 | 47.5 | 47.8 | 36.5 | 25.6 | 145.2 | 20.0 |
| tasks | 3.894 | 3.886 | n/a | n/a | n/a | n/a | 18.2 | 18.5 | n/a | n/a | n/a | n/a |
| url | 0.241 | 0.224 | n/a | n/a | n/a | n/a | 6.5 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.084 | 0.082 | 0.074 | 0.084 | n/a | n/a | 2.4 | 2.6 | 2.0 | 7.9 | n/a | n/a |

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
| parallel_collatz | 1 | 0.528 (0.519-0.542) | 0.527 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.287 (0.284-0.294) | 0.528 | 1.84x | 92 % | 1.00x | same |
| parallel_collatz | 4 | 0.195 (0.195-0.201) | 0.687 | 2.70x | 68 % | 1.30x | same |
| streams_parallel | 1 | 0.510 (0.509-0.519) | 0.510 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.267 (0.265-0.268) | 0.519 | 1.91x | 96 % | 1.02x | same |
| streams_parallel | 4 | 0.193 (0.192-0.194) | 0.726 | 2.64x | 66 % | 1.43x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.491 (2.456-2.568) | 4.037 | 428.9 | 32,690,856,642 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
| 2026-10-19T09:42:12Z | `4fca791aa7` | main | 32,690,856,642 | 2.491 | [json](history/2026-10-19-4fca791aa730.json) |
| 2026-10-18T08:41:01Z | `f9a96b20cf` | main | 32,474,433,787 | 2.653 | [json](history/2026-10-18-f9a96b20cf4a.json) |
