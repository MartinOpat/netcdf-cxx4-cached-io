#pragma once

#include <netcdf>
#include <stdexcept>
#include <string>
#include <vector>

#include "field.h"

template <typename T> class NetCDFField final : public Field<T> {
public:
  NetCDFField(std::string file, std::string var, size_t idx)
      : _file{std::move(file)}, _var{std::move(var)}, _time{idx} {
    read();
  }

  size_t index(size_t x, size_t y, size_t z) const override {
    // [x][y][z] --> TODO: Should be adjustable in config
    return x * (_ny * _nz) + y * (_nz) + z;
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

private:
  void read() override {
    using namespace netCDF;

    NcFile f(_file, NcFile::read);

    NcVar v = f.getVar(_var);
    if (v.isNull()) {
      throw std::runtime_error("Variable not found!");
    }

    auto dims = v.getDims();
    if (dims.size() != 4) {
      // TODO: Think about 2D simulations
      throw std::runtime_error(
          "Variable has wrong dimensions. Need 3 space dimensions + time.");
    }

    // NOTE: Assume the indexing is [time][x][y][z] <----- TODO: The user should
    // be able to set this in the config
    _nx = dims[1].getSize();
    _ny = dims[2].getSize();
    _nz = dims[3].getSize();

    _data.resize(_nx * _ny * _nz);

    std::vector<size_t> start{_time, 0, 0, 0};
    std::vector<size_t> count{1, _nx, _ny, _nz};

    v.getVar(start, count, _data.data());
  }

  std::string _file, _var;
  std::vector<T> _data;
  size_t _time{}, _nx{}, _ny{}, _nz{};
};
