#pragma once
#include <cstdint>

struct RunningStats {
  uint64_t n = 0;
  double mean = 0.0;
  double m2 = 0.0; // sum of squares of differences from the current mean

  void push(double x);
  double variance() const;
  double stddev() const;
};

struct BenchResult {
  double pi_estimate = 0.0;
  double seconds = 0.0;
  uint64_t samples = 0;
};

BenchResult monte_carlo_pi(uint64_t samples, uint64_t seed);
