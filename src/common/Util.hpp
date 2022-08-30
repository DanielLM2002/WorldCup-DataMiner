// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>

#include "common.hpp"

/**
 * @brief Container class for utility methods
 * This code is not needed for real projects
 */
class Util {
  DISABLE_COPY(Util);
  /// Constructor
  Util() = delete;
  /// Destructor
  ~Util() = delete;

 public:
  /// Generates a pseudo-random integer number in range [min, max[
  static int random(int min, int max);

  /// Utility method to simulate workload using sleep
  /// This method is for illustrative goals.
  /// Sleeps must be NEVER used for real projects.
  static void sleepFor(int milliseconds);

  /// @todo Pass the finder function by argument, e.g: find_first_of
  template <typename Container>
  static void tokenize(const std::string& text, Container& tokens,
    const std::string& delim = " ", bool trimEmpty = false) {
    // Adapted from https://stackoverflow.com/a/1493195
    std::string::size_type lastPos = 0;
    const std::string::size_type length = text.length();

    using value_type = typename Container::value_type;
    using size_type  = typename Container::size_type;

    while (lastPos < length + 1) {
      std::string::size_type pos = /*(text.*finder)*/text.find(delim, lastPos);
      if (pos == std::string::npos) {
        pos = length;
      }

      if (pos != lastPos || !trimEmpty) {
        tokens.push_back(value_type(text.data() + lastPos
          , size_type(pos) - lastPos));
      }

      lastPos = pos + 1;
    }
  }

  /// Splits a text string into array of subtexts
  static std::vector<std::string> split(const std::string& text,
    const std::string& delim = " ", bool trimEmpty = false);
};

#endif  // UTIL_HPP
