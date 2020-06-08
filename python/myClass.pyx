from libcpp.string cimport string

cdef extern from "myClass.h" namespace "mySpace":
    cdef cppclass myClass:
        myClass() except +
        int getInt();
        float getFloat();
        double getDouble();
        char getChar();
        string getString();

        void setInt(int);
        void setFloat(float);
        void setDouble(double);
        void setChar(char);
        void setString(string);
        void setBytes(char*, int);

cdef class PymyClass:
    cdef myClass *thisptr
    def __cinit__(self):
        self.thisptr = new myClass()
    def __dealloc__(self):
        del self.thisptr
    def getInt(self):
        return self.thisptr.getInt()
    def getFloat(self):
        return self.thisptr.getFloat()
    def getDouble(self):
        return self.thisptr.getDouble()
    def getChar(self):
        return self.thisptr.getChar()
    def getString(self):
        return self.thisptr.getString()

    def setInt(self, i):
        self.thisptr.setInt(i)
    def setFloat(self, f):
        self.thisptr.setFloat(f)
    def setDouble(self, d):
        self.thisptr.setDouble(d)
    def setChar(self, c):
        self.thisptr.setChar(c)
    def setString(self, s):
        self.thisptr.setString(s)
    def setBytes(self, b, l):
        self.thisptr.setBytes(b,l)
