import ctypes


class CountingIterator(ctypes.Structure):
    _fields_ = [("offset", ctypes.c_int64)]

    def advance(self_ptr, offset):
        self_ptr[0] = self_ptr[0] + offset

    def dereference(self_ptr):
        return self_ptr[0]


def count(start):
    return CountingIterator(start)
