from setuptools import setup
from distutils.core import setup, Extension
from Cython.Build import cythonize

extensions = [
    # Extension(
    #        "rect",                                # the extesion name
    #        sources=["rect.pyx", "Rectangle.cpp"], # the Cython source and
    #                                               # additional C++ source files
    #        language="c++",                        # generate and compile C++ code
    #   )
  Extension(
    name="myClass",
    sources=["python/*.pyx"],
    include_dirs=["include"],
    libraries=["CythonWrapper"], # this is the c++ library name!
    library_dirs=["build"],
    extra_compile_args=['-std=c++11'],
    language="c++"
    )

]


setup(
    name = "myClass", # name of package in 'pip freeze'
    # packages = {"rect_pack"},
    package_dir = {"":"build",
                   "":"python"}, # site_packages, having "" in this list
    ext_modules = cythonize(extensions)
)
