#pragma once

#include "timeKey.hpp"

#include <deque>
#include <unordered_map>

template <typename ValuePtr, typename Hash = TimeKeyHash,
          typename Eq = std::equal_to<TimeKey>>
class TimeBuffer {
public:
  explicit TimeBuffer(size_t num_steps) : _num_steps{num_steps} {}

  ValuePtr get(const std::string &file, const std::string &var, size_t time) {
    TimeKey k{file, var, time};

    if (auto it = _dict.find(k); it != _dict.end()) {
      return it->second;
    }

    ValuePtr obj = load(k);
    _dict.emplace(k, obj);
    _order.push_back(k);

    while (_order.size() > _num_steps) {
      _dict.erase(_order.front());
      _order.pop_front();
    }
    return obj;
  }

protected:
  virtual ValuePtr load(const TimeKey &k) = 0;

private:
  size_t _num_steps;

  std::unordered_map<TimeKey, ValuePtr, Hash, Eq> _dict;
  std::deque<TimeKey> _order;
};
