import ctypes


class ConstantIterator(ctypes.Structure):
    _fields_ = [("value", ctypes.c_int64)]

    def advance(self, offset):
        del offset

    def dereference(self):
        return self.value


def repeat(value):
    return ConstantIterator(value)


class CountingIterator(ctypes.Structure):
    _fields_ = [("current", ctypes.c_int64)]

    def advance(self, offset):
        self.current += offset

    def dereference(self):
        return self.current


def count(start):
    return CountingIterator(start)
