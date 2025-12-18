#include "bench.hpp"
#include <iostream>
#include <string>

static void usage() {
  std::cout
    << "bench --samples N [--seed S]\n"
    << "Example: bench --samples 2000000 --seed 123\n";
}

int main(int argc, char** argv) {
  uint64_t samples = 0;
  uint64_t seed = 123;

  for (int i = 1; i < argc; i++) {
    std::string a = argv[i];
    if (a == "--samples" && i + 1 < argc) {
      samples = std::stoull(argv[++i]);
    } else if (a == "--seed" && i + 1 < argc) {
      seed = std::stoull(argv[++i]);
    } else if (a == "--help" || a == "-h") {
      usage();
      return 0;
    } else {
      std::cerr << "Unknown arg: " << a << "\n";
      usage();
      return 1;
    }
  }

  if (samples == 0) {
    usage();
    return 1;
  }

  auto r = monte_carlo_pi(samples, seed);

  std::cout << "samples=" << r.samples
            << " pi=" << r.pi_estimate
            << " seconds=" << r.seconds
            << " throughput=" << (static_cast<double>(r.samples) / r.seconds) << " samples/sec\n";

  return 0;
}
