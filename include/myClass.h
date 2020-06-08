#include <iostream>

namespace mySpace {
  class myClass {
  public:

      myClass();
      ~myClass();
      int getInt();
      float getFloat();
      double getDouble();
      char getChar();
      std::string getString();

      void setInt(int);
      void setFloat(float);
      void setDouble(double);
      void setChar(char);
      void setString(std::string);
      void setBytes(char* b, int l);

  };
}