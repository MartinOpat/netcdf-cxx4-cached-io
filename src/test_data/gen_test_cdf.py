
import sys
from netCDF4 import Dataset
import numpy as np

if len(sys.argv) != 2:
    print("Usage: python gen_test_cdf.py <output_filename_without_extension>")
    sys.exit(1)

filename = "data/" + sys.argv[1] + ".nc"

with Dataset(filename, 'w', format='NETCDF4') as nc:
    nc.createDimension('time', 2)
    nc.createDimension('x', 3)
    nc.createDimension('y', 4)
    nc.createDimension('z', 5)

    nc.createVariable('time', 'i4', ('time',))[:] = np.arange(2)
    nc.createVariable('x', 'i4', ('x',))[:] = np.arange(3)
    nc.createVariable('y', 'i4', ('y',))[:] = np.arange(4)
    nc.createVariable('z', 'i4', ('z',))[:] = np.arange(5)

    test_val = nc.createVariable('test_value', 'f4', ('time', 'x', 'y', 'z'))

    t, x, y, z = np.meshgrid( np.arange(2),
        np.arange(3),
        np.arange(4),
        np.arange(5),
        indexing='ij'
    )
    test_val[:, :, :, :] = t + x + y + z
