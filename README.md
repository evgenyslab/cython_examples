# Cython Example

This project presents an example of creating a cython (python) wrapper for a
c++ class/library.

To begin, create the following folder structure:

```python
|- include/
    |- myClass.h  # place C++ header files here
|- src/
    |- myClass.cpp  # place C++ source files here
|- python/
    |- myClass.pyx  # this will be python interface
|- CmakeLists.txt  # this will define C++ class compile
|- setup.py   # this will define cython wrapper creation & python package
              # installation
|- requirements.txt  # this is the python virtual environment requirements.
| .gitignore  # ingore some byproduct files
```

This example project is built around the use of `cmake` with python virutal
environments to ensure clean builds of custom packages.

The general process flow to create a C++ library and wrap it with python using
cython follows:

1. Write C++ library in `src` and `include` folders and create `CmakeLists.txt`
that defines compilation of the custom class as a static library

2. Wrap the C++ library with python in the `python/myClass.pyx` file by creating
python interfaces for specific class members and functions.

3. Compile C++ library with `cmake` and `make`:

  ```bash
  mkdir build
  cd build
  cmake ..
  make
  ```

4. [Optionally - but highly recommended] Create local python virtual environment
with at minimum `cython` package installed. Enable virtual environment before
installing wrapped package.

5. Write python package install script `setup.py`.

6. Cythonize and install wrapped python package using (*in virtual environment*):
  ```bash
  python setup.py install  
  ```

## Some Issues to resolve

- string is passed as an array of bytes to python
- not sure if setString works expected bytes but got string..
