#pragma once

#include <cassert>
#include <cstddef>
#include <string>
#include <vector> // TODO: Delete if implement another container

#include "field.h"

template <typename T> class BasicField : public Field<T> {
public:
  BasicField(size_t nx, size_t ny, size_t nz)
      : _nx{nx}, _ny{ny}, _nz{nz}, _data{nx * ny * nz} {}

  size_t operator()(size_t x, size_t y, size_t z) const {
    return index(x, y, z);
  }

  size_t index(size_t x, size_t y, size_t z) const override {
    assert(0 <= x && x < _nx && 0 <= y && y < _ny && 0 <= z && z < _nz);
    return x * (_ny * _nz) + y * (_nx) + z;
  }

  const T &at(size_t x, size_t y, size_t z) const override {
    return _data[index(x, y, z)];
  }

  T &at(size_t x, size_t y, size_t z) override { return _data[index(x, y, z)]; }

  void generate(std::function<T(size_t, size_t, size_t)> generator) override {
    for (size_t z = 0; z < _nz; z++) {
      for (size_t y = 0; y < _ny; y++) {
        for (size_t x = 0; x < _nx; x++) {
          _data[index(x, y, z)] = generator(x, y, z);
        }
      }
    }
  }

  // Helper function to generate a simple field
  void generate(T value) {
    generate([value](size_t, size_t, size_t) { return value; });
  }

private:
  void read(std::string path) override {
    // TODO: Use FieldInput here once it is implemented
  }

  size_t _nx, _ny, _nz;
  std::vector<T> _data;
};
