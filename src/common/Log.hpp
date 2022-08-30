// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <fstream>
#include <mutex>
#include <string>

#include "common.hpp"

// TODO(jhc): Provide examples
/// Singleton thread-safe log manager
class Log {
  DISABLE_COPY(Log);

 public:
  /// The types of records/messages to be written to the log
  enum MessageType {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
  };
  /// The respective texts for the message types
  static const char* const MESSAGE_TYPE_TEXT[];

 private:
  /// All write operations are mutually exclusive
  std::mutex mutex;
  /// The output stream where all output will be sent
  /// This can point to file or std::cout
  std::ostream output;
  /// The log filename. If empty, std::cout will be used
  std::string filename;
  /// The log file if using named files
  std::ofstream file;

 public:
  /// Get access to the unique instance of this Singleton class
  static Log& getInstance();
  /// Open the log file for appending
  /// If no filename is give, standard output is used
  /// @throw std::runtime_error if file could not be open
  void start(const std::string& logFilename = std::string());
  /// Closes the log file
  void stop();
  /// Appends a record to the log file
  /// @throw std::runtime_error if record could not be written
  /// @see append
  void write(MessageType type, const std::string& category
    , const std::string& text);
  /// Appends a record to the log file
  /// This is a convenience static method that calls write
  /// @param type A constant: DEBUG, INFO, WARNING, ERROR.
  /// @param category Any text that is useful for distinguish messages, such as
  /// the name of the module or class, e.g: producer or socket
  /// @param text Text should not contain tab characters ('\t')
  /// @throw std::runtime_error if record could not be written
  static inline void append(MessageType type, const std::string& category
    , const std::string& text) {
    return Log::getInstance().write(type, category, text);
  }

 private:
  /// Singleton. Implement code in start() method instead
  Log();
  /// Singleton. Implement code in stop() method instead
  ~Log() = default;
};

#endif  // LOG_HPP
