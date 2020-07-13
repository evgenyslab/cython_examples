# Notes

TODO:
- [ ] Python unit testing
- [ ] setup.py force c++ build
- [ ] pycharm force setup.py build on console or application run...

How to structure cython repo to use both clion & pycharm separatel?

How to get cython to build binaries for an environment and make it useable?

i.e. cython package developed concurrently with a python application?

How to setup c++ to run on docker container at the same time as the pycharm?

- using `bin` in cpp side as build directory - need to configure clion for it...

- I'm not sure if its possible to avoid running setup.py on cythonized code, however I know C++ compiled modules can
be used by python without cython; that might be better

- it seems inescapible to run python setup.py install - but how to make this automated for docker system for any N
sets of python wrapped c++ libraries? How to make sure they are testable? How to develop them?

Proposal:

1. run docker container
2. develop C++ library in `sources` with Clion in ssh docker
3. Write python interface `.pyx` for sources in host application
4. use script to upload project to container, build & install python package 
    - currently testing ssh'ed install... need to fix LD_library_path...
    -> note that exporting the LD_LIBRARY_PATH will only work in the connected docker instance...
    -> maybe in pycharm starting script need to do export of LD library path to get it to see correctly..
    
NOTE: when using CLion with ssh - it creates a different project folder! Might not be able to run both C++ and python
concurrently in CLion and Pycharm! Develop C++ FIRST, Then close and use Pycharm w/ shh...

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

## Example Usage

Once the C++ has been compiled and the cython wrapper generated and installed
(into virtual environment), the following usage example is provided in `ipython`
console:

```python
import myClass

obj = myClass.PymyClass()
# test getters:
obj.getInt()
obj.getFloat()
obj.getChar()
obj.getString()

# test setters:
obj.setInt(12398)
obj.setFloat(10.312)
obj.setDouble(842.129381084170238102489712)
obj.setChar('c')
obj.setString("test string")  # <- WILL NOT WORK
b = bytes("test string with bytes", "UTF-8")  # UTF-8 or ascii encoding will print out correctly on C++ side; otherwise it will just receive a byte array, which is useful for data such as images.
obj.setBytes(b, len(b))

```

## Some Issues to resolve

*IMPORTANT*
The current CMakeLists.txt file creates a Static library object `.a`, this works fine with MacOS compiler, however
when moving to linux, gcc compiler has trouble linking to a static library, therefore the CmakeLists.txt should
change the desigation of the library from `STATIC` to `SHARED` when non-MacOs host is detected. 

Next problem is that the compiled shared library in Linux is locaated in the build folder `build/*.so`, however,
when trying to load the class object in python, python says it cannot open the library object.
[this](https://stackoverflow.com/questions/1099981/why-cant-python-find-shared-objects-that-are-in-directories-in-sys-path) 
suggests that the LD_LIBRARY_PATH should include the `.so` location - need to verify this and check.

SOLUTION:
- updated CMakeLists.txt for Linux to create shared library object (`.so`) in build folder.
- Need to check in linux `LD_LIBRARY_PATH` environment variable - it might be empty.
- Need to add, temporarily the build dir to the `LD_LIBRARY_PATH` variable for python to correctly
link the libraries:
```bash
export LD_LIBRARY_PATH='$LD_LIBRARY_PATH:path/to/build/folder'
```

- string is passed as an array of bytes to python
- not sure if setString works expected bytes but got string..
