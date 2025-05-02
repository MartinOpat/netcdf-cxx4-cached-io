
#pragma once

#include <cstddef>
#include <string>
#include <vector>

template <typename T> class FileReader {
public:
  typedef struct MetaData {
    size_t nx, ny, nz;
  } MetaData;

  virtual void readSlice(const std::string &var, size_t timeIdx,
                         std::vector<T> &out, MetaData &meta) const = 0;
};
