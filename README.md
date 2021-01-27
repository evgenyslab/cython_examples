# README

2021-01-27 - Generating Sphinx side by side with Doxygen

- run sphinx-quickstart in docs folder, use separate build/source option
- configure the conf.py file in docs/sources
- add rst files to docs/sources
- in doxygen set output dir to doxygen + generate HTML
- See MakeFile and conf.py to see how doxygen is auto generated, and copied into 
gh-pages

TODO: add notes on generating doxy for cython specific project...

Note: if using gh-pages (github pages) use a side-by-side repository
structure to keep track of the branch to push pages, make sure to set
the `BUILDDIR` in the `MakeFile` to the correct relative path, otherwise, 
if generating the docs in a nested location, set the build file to 
the required location. Please note, the `Makefile` has directive to build
the doxygen structure as well

TODO: might want to add the makefile directive to the labmanual sauces page

In the index rst / or wherever, add relative link to doxygen/index.html to access it

TODO: how to add readme.md as main page in both sphinx/doxygen?

## More info


Use Cases:
A. C++ packages that need to used in C++ and Python Application
B. C++ packages that will be exclusively used by Python Applications

Project Structure:

```bash
# MIXED STRUCTURE

.
├── docs
│   └── Doxyfile
├── include
│   ├── header1.h
│   └── header2.h
├── pythonpackagename
│   ├── __init__.py
│   └── pythonpackagename.pyx
├── src
│   ├── sourceFile1.cpp
│   └── sourceFile2.cpp
├── tests
│   ├── CMakeLists.txt
│   ├── __init__.py
│   ├── genericTestSuite.cpp
│   └── test_interfacepackage.py
├── CMakeLists.txt
├── LICENSE
├── requirements.txt
├── setup.py

```

Workflows:

1. Develop C++ Library with concurrent tests, until required functionality is met by library.
    - Open Clion Project with SSH into running docker container
    - Develop in Clion with remote docker
    - Run tests in docker container
    - Verify operation
    
2. Write one .pyx cython wrapper for C++ library in `python` folder

3. Write and place python tests in `tests` folder side by side with c++ tests

(at this point, in CLion - all folders should sycn to docker container)

4. SSH into docker container using `docker exec -it container_name zsh`

5. (docker) navigate to project folder

6. (docker) run `python3 setup.py install` to install the package into the container's system python

7. (docker) Run python tests `python3 tests/testSuite.py`, verify tests pass (repeat #2-7 as needed)

Option A:

8. Create `Install` targets in `CMakeLists.txt` for C++ Library to place compiled binaries in correct system
folder and move headers into system `include`. [This creates install instructions for target systems]

(***TODO***: Bundle python install with CMake Install Instructions)

9. Run standard C++ library install procedure on target system:

```bash
mkdir build
cd build
cmake ..
make
sudo make install
```

Option B: 

8. On target system, clone/copy repository (i.e. docker), and run `python3 setup.py install`
    
    - this will be either in docker container (through ssh), or on a target system
    - Alternatively can run `pip3 install .` for automation.


## OLD    

it seems like its possible to run `python3 setup install` without building any sources; I think its automated 
by cython

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
    
To run remote testing, could use pycharm to upload with ssh, then ssh into docker and run:

`python3 setup.py build_ext --inplace`

to build the project inplace, then run `pythonr3 tests/testSuite.py` but this has import error :()


NOTE: when using CLion with ssh - it creates a different project folder! Might not be able to run both C++ and python
concurrently in CLion and Pycharm! Develop C++ FIRST, Then close and use Pycharm w/ shh...

## Cython Example

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
