#include "cppInterface.h"

// Use namespace if desired
using namespace cppInterfaceSpace;

// class constructor
cppInterface::cppInterface(){

}

// class destructor
cppInterface::~cppInterface(){

}

// test to pass integer to python:
int cppInterface::getInt(){
  return 10;
}

// test to pass float to python:
float cppInterface::getFloat(){
  return 10.1;
}

// test to pass double to python:
double cppInterface::getDouble(){
  return double(10.02131094810239810398120938);
}

// test to pass char to python:
char cppInterface::getChar(){
  return 'c';
}

// test to pass string to python (returns as byte array!):
std::string cppInterface::getString(){
  return std::string("hello world\n");
}

// test to set integer from python:
void cppInterface::setInt(int i){
  std::cout << "Got int: " << i << "\n";
}

// test to set float from python:
void cppInterface::setFloat(float f){
  std::cout << "Got float: " << f << "\n";
}

// test to set double from python:
void cppInterface::setDouble(double d){
  std::cout << "Got double: " << d << "\n";
}

// test to set char from python:
void cppInterface::setChar(char c){
  std::cout << "Got char: " << c << "\n";
}

// test to set string from python (DOES NOT WORK! receives byte array):
void cppInterface::setString(std::string s){
  std::cout << "Got string: " << s << "\n";
}

// test to set byte array from python:
void cppInterface::setBytes(char* b, int l){
  std::cout << "Got bytes: " << b << "\n";
}
