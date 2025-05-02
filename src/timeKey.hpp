

#pragma once

#include <string>

struct TimeKey {
  std::string file, var;
  size_t time;

  bool operator==(const TimeKey &k) const noexcept {
    return file == k.file && var == k.var && time == k.time;
  }
};
struct TimeKeyHash {
  size_t operator()(const TimeKey &k) const noexcept {
    return std::hash<std::string>{}(k.file) ^ std::hash<std::string>{}(k.var) ^
           std::hash<size_t>{}(k.time);
  }
};
