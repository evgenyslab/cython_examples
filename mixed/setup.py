from setuptools import setup
from distutils.core import setup, Extension
from Cython.Build import cythonize

# TODO: add scripting to build c++
"""
1. check if sources/bin directory exists
2. check if sources/bin is populated with *.a or *.so libs
3. check if $LD_LIBRARY_PATH (in container) includes the path to sources/bin

fullInstall -> (conditions?)
  # get local path -> PACKAGE_PATH
  mkdir sources/bin
  cd sources/bin
  cmake ..
  make
  export $LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$PACKAGE_PATH"
  
reinstall -> (bin exists but empty/ no .a or .so files
  
"""

extensions = [
  Extension(
    name="cppinterfacepackage",
    sources=["interfacepackage/*.pyx", "src/cppInterface.cpp"], # cython sources
    include_dirs=["include"],
    # libraries=["cppInterface"], # this is the c++ library name from CMakeLists.txt
    # library_dirs=["sources/build"],
    extra_compile_args=['-std=c++11'],
    language="c++"
    )

]


setup(
    author="Sherlock",
    name="cppinterfacepackage",  # name of package in 'pip freeze'
    # package_dir = {} # leave this empty to install to dist-packages
    ext_modules=cythonize(extensions)
)
