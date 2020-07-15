# test_interfacepackage.py

import unittest
import os, sys

sys.path.append('/'.join(os.getcwd().split('/')[:-1])+'/')
try:
    from cppinterfacepackage import pyCppInterface
except Exception as e:
    print("Could not import package")

class TestModule(unittest.TestCase):
    def test_module(self):
        obj = pyCppInterface()
        self.assertEqual(obj.getChar(), 99)

if __name__ == '__main__':
    unittest.main()