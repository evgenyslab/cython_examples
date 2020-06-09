#include "myClass.h"

// Use namespace if desired
using namespace mySpace;

// class constructor
myClass::myClass(){

}

// class destructor
myClass::~myClass(){

}

// test to pass integer to python:
int myClass::getInt(){
  return 10;
}

// test to pass float to python:
float myClass::getFloat(){
  return 10.1;
}

// test to pass double to python:
double myClass::getDouble(){
  return double(10.02131094810239810398120938);
}

// test to pass char to python:
char myClass::getChar(){
  return 'c';
}

// test to pass string to python (returns as byte array!):
std::string myClass::getString(){
  return std::string("hello world\n");
}

// test to set integer from python:
void myClass::setInt(int i){
  std::cout << "Got int: " << i << "\n";
}

// test to set float from python:
void myClass::setFloat(float f){
  std::cout << "Got float: " << f << "\n";
}

// test to set double from python:
void myClass::setDouble(double d){
  std::cout << "Got double: " << d << "\n";
}

// test to set char from python:
void myClass::setChar(char c){
  std::cout << "Got char: " << c << "\n";
}

// test to set string from python (DOES NOT WORK! receives byte array):
void myClass::setString(std::string s){
  std::cout << "Got string: " << s << "\n";
}

// test to set byte array from python:
void myClass::setBytes(char* b, int l){
  std::cout << "Got bytes: " << b << "\n";
}
