#pragma once

#include <cstddef>

class Field {
public:
  virtual size_t index(size_t x, size_t y, size_t z) const = 0;

  // TODO: Maybe rethink the void pointers here for the future. Right now this
  // is only used to work with generateField.hpp
  virtual void *data() = 0;
  virtual const void *data() const = 0;

  size_t nx() const noexcept { return _nx; };
  size_t ny() const noexcept { return _ny; };
  size_t nz() const noexcept { return _nz; };

private:
  virtual void read() = 0;

  size_t _nx, _ny, _nz;
};
