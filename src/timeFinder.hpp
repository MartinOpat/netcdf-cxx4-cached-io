#pragma once

#include "filePathManager.hpp"

#include <string>

class TimeFinder {
public:
  TimeFinder(FilePathManager &fpm, size_t stepsPerFile)
      : _fpm(fpm), _stepsPerFile{stepsPerFile} {}

  std::pair<std::string, size_t> find_local(size_t globalTime) const {
    size_t fileIdx = globalTime / _stepsPerFile;
    size_t localTime = globalTime % _stepsPerFile;
    return {_fpm.getPath(fileIdx), localTime};
  }

private:
  FilePathManager &_fpm;
  size_t _stepsPerFile;
};
