from setuptools import setup
from distutils.core import setup, Extension
from Cython.Build import cythonize

extensions = [
  Extension(
    name="cppInterfacePackage",
    sources=["interfacepackage/*.pyx"], # cython sources
    include_dirs=["sources/include"],
    libraries=["cppInterface"], # this is the c++ library name from CMakeLists.txt
    library_dirs=["sources/bin"],
    extra_compile_args=['-std=c++11'],
    language="c++"
    )

]


setup(
    name = "pyCppInterface", # name of package in 'pip freeze'
    # package_dir = {"":"build",
    #                "":"python"}, # site_packages, having "" in this list
    ext_modules = cythonize(extensions)
)
