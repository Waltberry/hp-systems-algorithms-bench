#include "bench.hpp"
#include <random>
#include <chrono>
#include <cmath>

void RunningStats::push(double x) {
  n++;
  double delta = x - mean;
  mean += delta / static_cast<double>(n);
  double delta2 = x - mean;
  m2 += delta * delta2;
}

double RunningStats::variance() const {
  return (n > 1) ? (m2 / static_cast<double>(n - 1)) : 0.0;
}

double RunningStats::stddev() const {
  return std::sqrt(variance());
}

BenchResult monte_carlo_pi(uint64_t samples, uint64_t seed) {
  using clock = std::chrono::steady_clock;
  auto t0 = clock::now();

  std::mt19937_64 rng(seed);
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  uint64_t inside = 0;
  for (uint64_t i = 0; i < samples; i++) {
    double x = dist(rng);
    double y = dist(rng);
    double r2 = x * x + y * y;
    inside += (r2 <= 1.0) ? 1 : 0;
  }

  double pi_est = 4.0 * static_cast<double>(inside) / static_cast<double>(samples);

  auto t1 = clock::now();
  double sec = std::chrono::duration<double>(t1 - t0).count();

  return BenchResult{pi_est, sec, samples};
}
