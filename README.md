# NetCDF C++4 File Library with Caching
A lightweight C++ library for reading NetCDF files, built on the NetCDF CXX4 interface. Optional file caching is implemented for easy and efficient temporal interpolation.

This project was originally developed as a part of the high-performance flexible Lagrangian particle tracer: [Link goes here once public]

## Example use
For this library to work, you need to have the netcdf libraries installed.
- Ubuntu:
```bash
sudo apt install libnetcdf-c++4-dev
```
- Arch:
```bash
sudo pacman -S netcdf-cxx
```

After that, the files can be compiled simply by running the following command in the `src` directory:
```bash
g++ -g -std=c++17 -Wall -O2 filePathManager.cpp example.cpp -o example.o -lnetcdf -lnetcdf_c++4
```
Inside the `example.cpp`  file, you can find a simple example of how to use the library. The example uses a `Field` and `NetCDFField` classes which are example classes showing how the library can be utilized with different implementations.

Simple netcdf files can be generated using the [python script](./src/test_data/gen_test_cdf.py).

## Future work
The O part of IO (coming soon)

## License
This project is listed under a custom non-commercial license. You are free to use, share, and modify the project with attribution. **Commercial use requires explicit permission and compensation.** See the [LICENSE](./LICENSE)
