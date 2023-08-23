#include <fmt/core.h>
#include <fmt/ostream.h>
#include <thread>
#include "estimator.hpp"

int main()
{
  Estimator estimator;
  estimator.setSeed(0);
  estimator.setNumSamples(100000000);
  estimator.setNumDimensions(2);
  estimator.setNumThreads(4);
  estimator.estimate();
  fmt::print("Pi: {}\n", estimator.getPi());
  return 0;
}