#pragma once

#include <netcdf>
#include <string>
#include <vector>

#include "field.hpp"
#include "fileReader/netcdfReader.h"

template <typename T> class NetCDFField final : public Field {
public:
  NetCDFField(std::string file, std::string var, size_t idx)
      : _file{std::move(file)}, _var{std::move(var)}, _time{idx} {
    read();
  }

  size_t index(size_t x, size_t y, size_t z) const override {
    // [x][y][z] --> TODO: Should be adjustable in config
    return x * (_ny * _nz) + y * (_nz) + z;
  }

  const void *data() const override { return _data.data(); }
  void *data() override { return _data.data(); }
  const std::vector<T> &vectorData() const { return _data; }
  std::vector<T> &vectorData() { return _data; }

private:
  void read() override {
    NetCDFReader<T> ncfr(_file);
    typename FileReader<T>::MetaData meta;
    ncfr.readSlice(_var, _time, _data, meta);

    _nx = meta.nx;
    _ny = meta.ny;
    _nz = meta.nz;
  }

  std::string _file, _var;
  std::vector<T> _data;
  size_t _time{}, _nx{}, _ny{}, _nz{};
};
