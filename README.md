# Orin benchmark history

Written by `.github/workflows/bench.yml` (nightly and manual runs on `main`); one JSON file per run in [`history/`](history/), charts rendered by `tooling/benchmarks` (`bench-report render`, no external services). The same data as a stand-alone page: [`report.html`](report.html). Metrics and methodology: `docs/benchmarks.md` on `main`. Do not edit this branch by hand.

24 runs, 2026-10-18 to 2026-11-10. Latest: [`148472c2cd`](https://github.com/orin-lang/orin-lang/commit/148472c2cdb025d701598706b95f6b90f7f7fa44).

Instruction counts are the regression metric: they are deterministic for single-threaded programs, while wall time on a shared runner moves by 10-25 % between identical binaries.

![Orin to C wall-time ratio per benchmark over time](charts/ratio_wall.svg)

![Orin to C executed-instruction ratio per benchmark over time](charts/ratio_instructions.svg)

![Self-compile instructions and wall time over time](charts/selfcompile.svg)

![Parallel speedup by worker threads](charts/parallel.svg)

## Latest run


Commit `148472c2cd` (main), 2026-11-10T12:13:41Z. Machine: Intel(R) Xeon(R) 6973P-C, 4 cores, 15.6 GiB, Linux-7.0.0-1017-azure-x86_64-with-glibc2.39. Runs per cell: 5 (median after one warm-up).

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
| appends | 0.006 (0.006-0.006) | 0.005 (0.004-0.005) | 0.004 (0.004-0.004) | 0.009 (0.008-0.011) | 0.057 (0.052-0.067) | 0.003 (0.003-0.003) |
| bintrees | 0.338 (0.334-0.357) | 0.346 (0.340-0.374) | 0.395 (0.393-0.404) | 0.879 (0.867-0.900) | 0.304 (0.300-0.313) | 0.523 (0.508-0.553) |
| bytesstr | 0.036 (0.034-0.038) | 0.033 (0.032-0.036) | 0.035 (0.034-0.035) | 0.008 (0.008-0.009) | 0.086 (0.085-0.089) | 0.027 (0.026-0.028) |
| fib | 0.239 (0.234-0.267) | 0.229 (0.227-0.232) | 0.132 (0.131-0.134) | 0.401 (0.399-0.404) | 0.345 (0.337-0.346) | 0.223 (0.222-0.227) |
| html | 0.113 (0.110-0.115) | 0.088 (0.088-0.089) | 0.106 (0.106-0.106) | 0.202 (0.196-0.205) | n/a | n/a |
| html_hand | 0.092 (0.092-0.093) | 0.066 (0.066-0.066) | n/a | n/a | n/a | n/a |
| http_parse | 0.084 (0.084-0.085) | 0.070 (0.070-0.071) | n/a | n/a | n/a | n/a |
| mapfreq | 0.113 (0.112-0.113) | 0.116 (0.113-0.126) | 0.062 (0.060-0.063) | 0.084 (0.082-0.086) | n/a | n/a |
| mutres | 0.097 (0.096-0.097) | 0.066 (0.066-0.067) | 0.020 (0.019-0.020) | 0.058 (0.058-0.059) | 0.064 (0.062-0.069) | 0.024 (0.023-0.024) |
| nbody | 0.050 (0.045-0.053) | 0.049 (0.044-0.050) | 0.042 (0.042-0.042) | 0.066 (0.066-0.066) | n/a | n/a |
| pqueue | 0.117 (0.116-0.117) | 0.091 (0.091-0.092) | 0.064 (0.057-0.065) | 0.144 (0.140-0.154) | 0.210 (0.206-0.216) | 0.069 (0.069-0.070) |
| qsort_func | 0.174 (0.174-0.175) | 0.176 (0.174-0.177) | 0.199 (0.189-0.214) | 0.312 (0.307-0.314) | n/a | n/a |
| qsort_inplace | 0.098 (0.097-0.098) | 0.095 (0.094-0.105) | 0.082 (0.074-0.083) | 0.098 (0.095-0.098) | n/a | n/a |
| sieve | 0.146 (0.144-0.168) | 0.134 (0.123-0.145) | 0.126 (0.114-0.139) | 0.259 (0.235-0.275) | 0.192 (0.181-0.194) | 0.132 (0.131-0.140) |
| sortedmap | 0.208 (0.200-0.214) | 0.204 (0.203-0.217) | n/a | n/a | n/a | n/a |
| streams | 0.108 (0.104-0.138) | 0.108 (0.105-0.112) | n/a | n/a | n/a | n/a |
| strings | 0.055 (0.055-0.057) | 0.046 (0.045-0.050) | 0.050 (0.049-0.052) | 0.052 (0.051-0.055) | 0.192 (0.187-0.212) | 0.021 (0.021-0.021) |
| tasks | 3.743 (3.537-3.836) | 3.762 (3.508-3.932) | n/a | n/a | n/a | n/a |
| url | 0.246 (0.244-0.250) | 0.225 (0.223-0.226) | n/a | n/a | n/a | n/a |
| wordfreq | 0.085 (0.084-0.086) | 0.082 (0.082-0.082) | 0.075 (0.074-0.078) | 0.086 (0.086-0.086) | n/a | n/a |

### Ratio to C (wall-time median; lower is better, 1.00x = as fast as C)

| benchmark | Orin C/C | Orin LLVM/C | Go/C | Java/C | Rust/C |
|---|---:|---:|---:|---:|---:|
| appends | 1.55x | 1.26x | 2.44x | 15.18x | 0.76x |
| bintrees | 0.86x | 0.88x | 2.23x | 0.77x | 1.33x |
| bytesstr | 1.04x | 0.94x | 0.23x | 2.48x | 0.78x |
| fib | 1.80x | 1.73x | 3.03x | 2.60x | 1.68x |
| html | 1.06x | 0.83x | 1.90x | n/a | n/a |
| html_hand | n/a | n/a | n/a | n/a | n/a |
| http_parse | n/a | n/a | n/a | n/a | n/a |
| mapfreq | 1.83x | 1.89x | 1.37x | n/a | n/a |
| mutres | 4.96x | 3.39x | 2.98x | 3.28x | 1.23x |
| nbody | 1.18x | 1.16x | 1.57x | n/a | n/a |
| pqueue | 1.82x | 1.42x | 2.24x | 3.27x | 1.08x |
| qsort_func | 0.88x | 0.89x | 1.57x | n/a | n/a |
| qsort_inplace | 1.19x | 1.16x | 1.19x | n/a | n/a |
| sieve | 1.17x | 1.07x | 2.06x | 1.53x | 1.05x |
| sortedmap | n/a | n/a | n/a | n/a | n/a |
| streams | n/a | n/a | n/a | n/a | n/a |
| strings | 1.10x | 0.92x | 1.05x | 3.85x | 0.42x |
| tasks | n/a | n/a | n/a | n/a | n/a |
| url | n/a | n/a | n/a | n/a | n/a |
| wordfreq | 1.14x | 1.10x | 1.15x | n/a | n/a |

### CPU time (user + sys, median s) and peak RSS (MiB)

| benchmark | orin CPU | llvm CPU | c CPU | go CPU | java CPU | rust CPU | orin RSS | llvm RSS | c RSS | go RSS | java RSS | rust RSS |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| appends | 0.005 | 0.004 | 0.003 | 0.011 | 0.082 | 0.002 | 4.6 | 4.8 | 4.9 | 10.1 | 47.9 | 5.1 |
| bintrees | 0.337 | 0.346 | 0.394 | 1.967 | 0.349 | 0.523 | 17.6 | 17.9 | 9.7 | 13.1 | 301.1 | 10.2 |
| bytesstr | 0.033 | 0.032 | 0.034 | 0.010 | 0.103 | 0.027 | 11.6 | 11.8 | 11.7 | 6.3 | 102.9 | 4.9 |
| fib | 0.238 | 0.228 | 0.132 | 0.402 | 0.353 | 0.222 | 1.5 | 1.9 | 1.6 | 1.7 | 38.6 | 2.0 |
| html | 0.112 | 0.088 | 0.106 | 0.247 | n/a | n/a | 3.9 | 4.2 | 2.2 | 7.5 | n/a | n/a |
| html_hand | 0.091 | 0.065 | n/a | n/a | n/a | n/a | 2.5 | 2.9 | n/a | n/a | n/a | n/a |
| http_parse | 0.084 | 0.070 | n/a | n/a | n/a | n/a | 1.7 | 2.1 | n/a | n/a | n/a | n/a |
| mapfreq | 0.112 | 0.116 | 0.061 | 0.100 | n/a | n/a | 11.4 | 11.7 | 5.1 | 7.3 | n/a | n/a |
| mutres | 0.096 | 0.066 | 0.019 | 0.058 | 0.091 | 0.024 | 1.6 | 1.9 | 1.6 | 1.7 | 39.3 | 2.1 |
| nbody | 0.049 | 0.049 | 0.042 | 0.066 | n/a | n/a | 1.9 | 1.9 | 2.0 | 1.8 | n/a | n/a |
| pqueue | 0.116 | 0.091 | 0.064 | 0.147 | 0.266 | 0.069 | 6.2 | 6.5 | 4.9 | 14.5 | 61.8 | 5.1 |
| qsort_func | 0.173 | 0.175 | 0.198 | 0.372 | n/a | n/a | 36.5 | 36.8 | 23.8 | 36.3 | n/a | n/a |
| qsort_inplace | 0.097 | 0.095 | 0.082 | 0.110 | n/a | n/a | 16.8 | 17.1 | 16.9 | 24.6 | n/a | n/a |
| sieve | 0.146 | 0.132 | 0.125 | 0.393 | 0.212 | 0.131 | 77.8 | 78.1 | 77.7 | 231.7 | 115.9 | 78.4 |
| sortedmap | 0.208 | 0.204 | n/a | n/a | n/a | n/a | 11.3 | 11.5 | n/a | n/a | n/a | n/a |
| streams | 0.107 | 0.108 | n/a | n/a | n/a | n/a | 39.8 | 40.0 | n/a | n/a | n/a | n/a |
| strings | 0.054 | 0.045 | 0.049 | 0.065 | 0.403 | 0.021 | 46.2 | 46.5 | 34.7 | 23.5 | 139.2 | 19.9 |
| tasks | 3.894 | 3.900 | n/a | n/a | n/a | n/a | 14.3 | 14.6 | n/a | n/a | n/a | n/a |
| url | 0.245 | 0.225 | n/a | n/a | n/a | n/a | 6.5 | 6.8 | n/a | n/a | n/a | n/a |
| wordfreq | 0.084 | 0.082 | 0.074 | 0.087 | n/a | n/a | 2.4 | 2.6 | 2.0 | 6.5 | n/a | n/a |

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
| parallel_collatz | 1 | 0.519 (0.494-0.552) | 0.518 | 1.00x | 100 % | 1.00x | same |
| parallel_collatz | 2 | 0.288 (0.286-0.288) | 0.523 | 1.80x | 90 % | 1.01x | same |
| parallel_collatz | 4 | 0.201 (0.198-0.224) | 0.689 | 2.58x | 65 % | 1.33x | same |
| streams_parallel | 1 | 0.513 (0.511-0.518) | 0.512 | 1.00x | 100 % | 1.00x | same |
| streams_parallel | 2 | 0.269 (0.267-0.271) | 0.515 | 1.91x | 95 % | 1.00x | same |
| streams_parallel | 4 | 0.188 (0.187-0.189) | 0.686 | 2.73x | 68 % | 1.34x | same |

Speedup = wall(1 thread) / wall(n); efficiency = speedup / n. CPU time that grows with n is overhead or oversubscription (more threads than free cores).

### Self-compile (orin2 compiles compiler/main.or)

| wall s (min-max) | CPU s | peak RSS MiB | instructions | output identical to stage2.c |
|---:|---:|---:|---:|---|
| 2.528 (2.432-2.596) | 4.032 | 426.2 | 32,946,478,802 | yes |


## All runs

| date | commit | ref | self-compile instructions | self-compile wall s | file |
|---|---|---|---:|---:|---|
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
