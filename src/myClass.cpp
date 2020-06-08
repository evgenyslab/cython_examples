#include "myClass.h"

using namespace mySpace;

myClass::myClass(){

}

myClass::~myClass(){

}

int myClass::getInt(){
  return 10;
}

float myClass::getFloat(){
  return 10.1;
}

double myClass::getDouble(){
  return double(10.02131094810239810398120938);
}

char myClass::getChar(){
  return 'c';
}

std::string myClass::getString(){
  return std::string("hello world\n");
}

void myClass::setInt(int i){
  std::cout << "Got int: " << i << "\n";
}

void myClass::setFloat(float f){
  std::cout << "Got float: " << f << "\n";
}

void myClass::setDouble(double d){
  std::cout << "Got double: " << d << "\n";
}

void myClass::setChar(char c){
  std::cout << "Got char: " << c << "\n";
}

void myClass::setString(std::string s){
  std::cout << "Got string: " << s << "\n";
}

void myClass::setBytes(char* b, int l){
  std::cout << "Got bytes: " << b << "\n";
}
