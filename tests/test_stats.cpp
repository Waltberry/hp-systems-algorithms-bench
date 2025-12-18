#include "bench.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

int main() {
  // Basic sanity: Monte Carlo should get within a loose bound with enough samples
  auto r = monte_carlo_pi(500000, 123);
  double err = std::fabs(r.pi_estimate - 3.141592653589793);

  // Loose bound to avoid flaky tests in CI; still proves correctness.
  assert(err < 0.02);

  std::cout << "OK: pi=" << r.pi_estimate << " err=" << err << "\n";
  return 0;
}
