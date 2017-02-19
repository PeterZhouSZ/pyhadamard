#!/usr/bin/env python

from distutils.core import setup, Extension
import numpy.distutils.misc_util
import numpy

setup(
    ext_modules=[Extension("fast_wh", ["fast_wh.c", "fast_wh_core.c"])],
    include_dirs=[numpy.get_include(), '.'],
)
