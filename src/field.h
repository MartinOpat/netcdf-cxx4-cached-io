#pragma once

#include <functional>
#include <string>

template <typename T> class Field {
public:
  virtual size_t index(size_t x, size_t y, size_t z) const = 0;
  virtual const T &at(size_t x, size_t y, size_t z) const = 0; // For reading
  virtual T &at(size_t x, size_t y, size_t z) = 0; // For writing (if necessary)
  virtual void generate(std::function<T(size_t, size_t, size_t)> generator) = 0;

private:
  virtual void read() = 0;

  size_t _nx, _ny, _nz;
};
