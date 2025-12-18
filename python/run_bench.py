import argparse
import subprocess
import statistics
from pathlib import Path
import os

def find_bench_exe() -> Path:
    repo_root = Path(__file__).resolve().parents[1]
    candidates = [
        repo_root / "build" / "bench",
        repo_root / "build" / "bench.exe",
        repo_root / "cmake-build-release" / "bench",
        repo_root / "cmake-build-release" / "bench.exe",
    ]
    for c in candidates:
        if c.exists():
            return c
    raise FileNotFoundError(
        "Could not find bench executable. Build first:\n"
        "  cmake -S . -B build -DCMAKE_BUILD_TYPE=Release\n"
        "  cmake --build build -j\n"
        "Expected at: build/bench(.exe)"
    )

def run_once(bench_exe: Path, samples: int, seed: int):
    proc = subprocess.run(
        [str(bench_exe), "--samples", str(samples), "--seed", str(seed)],
        cwd=str(bench_exe.parent),
        capture_output=True,
        text=True,
        check=True,
    )
    out = proc.stdout.strip()
    parts = out.split()
    sec = float([p for p in parts if p.startswith("seconds=")][0].split("=")[1])
    thr = float([p for p in parts if p.startswith("throughput=")][0].split("=")[1])
    return sec, thr, out

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--samples", type=int, default=2_000_000)
    ap.add_argument("--trials", type=int, default=5)
    ap.add_argument("--seed", type=int, default=123)
    args = ap.parse_args()

    bench_exe = find_bench_exe()
    print(f"Using executable: {bench_exe}")

    secs, thrs = [], []
    for t in range(args.trials):
        sec, thr, line = run_once(bench_exe, args.samples, args.seed + t)
        print(line)
        secs.append(sec)
        thrs.append(thr)

    print("\nSummary")
    print(f"seconds: mean={statistics.mean(secs):.4f} stdev={statistics.pstdev(secs):.4f}")
    print(f"throughput: mean={statistics.mean(thrs):.2f} samples/sec")

if __name__ == "__main__":
    main()
