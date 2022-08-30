// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <chrono>
#include <random>
#include <thread>

#include "Util.hpp"

// Try to get a seed from hardware, if available
static std::random_device::result_type seed = std::random_device()();
// This object generates randon numbers using the Mersenne-Twister algoritym
static std::mt19937 randomEngine(seed);

int Util::random(int min, int max) {
  // Produce random values with uniform discrete distribution
  std::uniform_int_distribution<int> randomDistribution(min, max - 1);
  // Generate and return a random number using the uniform distribution
  return randomDistribution(randomEngine);
}

void Util::sleepFor(int milliseconds) {
  if ( milliseconds < 0 ) {
    milliseconds = Util::random(0, std::abs(milliseconds));
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

std::vector<std::string> Util::split(const std::string& text,
  const std::string& delim, bool trimEmpty) {
  std::vector<std::string> tokens;
  // Util::tokenize(text, tokens, static_cast<size_t(std::string::*)(const
  // std::string&, size_t)>(&std::string::find_first_of), delim, trimEmpty);
  Util::tokenize(text, tokens, delim, trimEmpty);
  return tokens;
}
