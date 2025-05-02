

#pragma once

#include "fileReader.h"

#include <netcdf>
#include <stdexcept>
#include <vector>

template <typename T> class NetCDFReader : public FileReader<T> {
public:
  // TODO: Maybe add explicit
  NetCDFReader(const std::string &path) : _file(path, netCDF::NcFile::read) {
    if (_file.isNull()) {
      throw std::runtime_error("Cannot open " + path + "!");
    }
  }

  void readSlice(const std::string &var, size_t time, std::vector<T> &out,
                 typename FileReader<T>::MetaData &meta) const {
    using namespace netCDF;

    NcVar v = _file.getVar(var);
    if (v.isNull()) {
      throw std::runtime_error("var " + var + " missing!");
    }

    // TODO: Think about 2D simulation files
    auto dims = v.getDims();
    if (dims.size() != 4) {
      throw std::runtime_error(
          "Variable has wrong dimensions. Need 3 space dimensions + time.");
    }

    meta.nx = dims[1].getSize();
    meta.ny = dims[2].getSize();
    meta.nz = dims[3].getSize();

    out.resize(meta.nx * meta.ny * meta.nz);

    std::vector<size_t> start{time, 0, 0, 0};
    std::vector<size_t> count{1, meta.nx, meta.ny, meta.nz};

    v.getVar(start, count, out.data());
  }

private:
  netCDF::NcFile _file;
};
