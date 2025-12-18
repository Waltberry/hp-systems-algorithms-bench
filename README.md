# High-Performance Systems & Algorithms Bench (C++/Python)

A small, portfolio-grade benchmark suite demonstrating performance-minded systems programming:
- Monte Carlo simulation kernel
- Numeric kernels + data-structure choices
- Profiling workflow on Linux (perf, valgrind/callgrind)
- Tests for correctness and reproducibility
- Python runner for repeatable benchmark experiments

## Why this repo exists
EDA / simulation software lives and dies by correctness, performance, and engineering discipline.
This project demonstrates:
- Efficient C++ implementation with attention to memory/layout
- Deterministic benchmarks (seed control)
- Unit tests validating statistical properties
- Profiling + basic optimization workflow

## Build
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/bench --help
