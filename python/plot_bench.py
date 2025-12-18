# python/plot_bench.py
from __future__ import annotations
import argparse
import csv
from pathlib import Path

import matplotlib.pyplot as plt

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--csv", default="results/bench.csv", help="CSV path produced by run_bench.py")
    ap.add_argument("--out", default="results/throughput.png", help="Output image path")
    args = ap.parse_args()

    csv_path = Path(args.csv)
    out_path = Path(args.out)
    out_path.parent.mkdir(parents=True, exist_ok=True)

    trials = []
    seconds = []
    thr = []
    with csv_path.open("r", newline="") as f:
        r = csv.DictReader(f)
        for row in r:
            trials.append(int(row["trial"]))
            seconds.append(float(row["seconds"]))
            thr.append(float(row["throughput"]))

    plt.figure()
    plt.plot(trials, thr, marker="o")
    plt.xlabel("Trial")
    plt.ylabel("Throughput (samples/sec)")
    plt.title("Benchmark Throughput Across Trials")
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig(out_path, dpi=160)
    print(f"Saved plot: {out_path}")

if __name__ == "__main__":
    main()
