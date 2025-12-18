#!/usr/bin/env bash
set -euo pipefail

SAMPLES="${1:-5000000}"

echo "Building Release..."
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j

echo "Running perf profile (requires Linux perf)..."
perf stat -d ./build/bench --samples "$SAMPLES" --seed 123 | tee report.txt

echo "Done. Output: report.txt"
