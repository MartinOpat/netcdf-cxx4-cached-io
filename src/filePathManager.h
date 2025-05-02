#ifndef FILEPATHMANAGER_H
#define FILEPATHMANAGER_H

#include <string>
#include <vector>

/**
 * @brief Simple class that is responsible for mapping a file index to a file
 * path. So for example: index = 0 -> MERRA2_400.inst6_3d_ana_Np.20120101.nc4
 * index = 1 -> MERRA2_400.inst6_3d_ana_Np.20120102.nc4
 * index = 2 -> MERRA2_400.inst6_3d_ana_Np.20120103.nc4
 * index = 3 -> MERRA2_400.inst6_3d_ana_Np.20120104.nc4
 * etc...
 */
class FilePathManager {
public:
  FilePathManager(const std::string &path);
  size_t getNumberOfFiles();
  const std::string getPath(size_t index) const;

  ~FilePathManager();

private:
  std::vector<std::string> fileNames;
};

#endif // FILEPATHMANAGER_H
