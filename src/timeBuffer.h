#pragma once

#include "field.h"
#include "netcdfField.h"

#include <deque>
#include <memory>
#include <unordered_map>

template <typename T> class TimeBuffer {
public:
  using FieldPtr = std::shared_ptr<Field<T>>;

  TimeBuffer(size_t num_steps = 3) : _num_steps{num_steps} {}

  FieldPtr get(const std::string &file, const std::string &var, size_t time) {
    Key k{file, var, time};
    if (auto it = _dict.find(k); it != _dict.end()) {
      return it->second;
    }

    // If we are here then the time step is not cached yet
    auto field = std::make_shared<NetCDFField<T>>(file, var, time);
    _dict.emplace(k, field);
    _order.push_back(k);

    // Drop oldest
    while (_order.size() > _num_steps) {
      _dict.erase(_order.front());
      _order.pop_front();
    }

    return field;
  }

private:
  struct Key {
    std::string file, var;
    size_t time;
    bool operator==(const Key &k) const noexcept {
      return file == k.file && var == k.var && time == k.time;
    }
  };

  // TODO:This is a very straightforward hashing logic, might wanna improve it
  struct KeyHash {
    size_t operator()(const Key &k) const noexcept {
      return std::hash<std::string>{}(k.file) ^
             std::hash<std::string>{}(k.var) ^ std::hash<size_t>{}(k.time);
    }
  };

  size_t _num_steps = 3;
  std::unordered_map<Key, FieldPtr, KeyHash> _dict;
  std::deque<Key> _order;
};
