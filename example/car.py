from enum import IntEnum
import struct


class Setter(object):
    def __init__(self, func, doc=None):
        self.func = func
        self.__doc__ = doc if doc is not None else func.__doc__
    def __set__(self, obj, value):
        return self.func(obj, value)


class Templates(IntEnum):
      car = 1


# Variable-length string decoder
class VarStringTypeDecoder(object):

    def __init__(self, data, var_offset, offset):
        self.__data = data
        self.__var_offset = var_offset
        self.__offset = offset
        self.__size = 2

    @property
    def size(self):
        return self.__size

    @property
    def val(self):
        len = struct.unpack_from("<H", self.__data, self.__var_offset[0] + self.__offset)[0]
        offset = self.__var_offset[0] + self.__offset + 2
        str = struct.unpack_from("P", self.__data[offset:len])[0]
        self.__var_offset[0] += len
        self.__size += len
        return str


# Variable-length string encoder
class VarStringTypeEncoder(object):

    def __init__(self, data, var_offset, offset):
        self.__data = data
        self.__var_offset = var_offset
        self.__offset = offset
        self.__size = 2

    @property
    def size(self):
        return self.__size

    @Setter
    def val(self, val):
        struct.pack_into("<H", self.__data, self.__var_offset[0] + self.__offset, len(val))
        struct.pack_into("P", self.__data, self.__var_offset[0] + self.__offset + 2, val)
        self.__var_offset[0] += len(val)
        self.__size += len(val)


# Group Size decoder
class GroupSizeEncodingTypeDecoder(object):

    def __init__(self, data, var_offset, offset):
        self.__data = data
        self.__var_offset = var_offset
        self.__offset = offset
        self.__size = 4

    @property
    def size(self):
        return self.__size

    @property
    def blockLength(self):
        return struct.unpack_from("<h", self.__data, self.__var_offset[0] + self.__offset)[0]

    @property
    def numInGroup(self):
        return struct.unpack_from("<h", self.__data, self.__var_offset[0] + self.__offset+2)[0]


# Group Size encoder
class GroupSizeEncodingTypeEncoder(object):

    def __init__(self, data, var_offset, offset):
        self.__data = data
        self.__var_offset = var_offset
        self.__offset = offset
        self.__size = 4

    @property
    def size(self):
        return self.__size

    @Setter
    def blockLength(self, value):
        struct.pack_into("<h", self.__data, self.__var_offset[0] + self.__offset, value)

    @Setter
    def numInGroup(self, value):
        struct.pack_into("<h", self.__data, self.__var_offset[0] + self.__offset + 2, value)


# Message Header encoder
class MessageHeaderTypeEncoder(object):

    def __init__(self, data, offset):
        self.__data = data
        self.__offset = offset
        self.__size = 8

    @property
    def size(self):
        return self.__size

    @Setter
    def blockLength(self, value):
        struct.pack_into("<h", self.__data, self.__offset, value)

    @Setter
    def templateId(self,value):
        struct.pack_into("<h", self.__data, self.__offset + 2, value)

    @Setter
    def schemaId(self,value):
        struct.pack_into("<h", self.__data, self.__offset + 4, value)

    @Setter
    def version(self,value):
        struct.pack_into("<h", self.__data, self.__offset + 6, value)


# Message Header decoder
class MessageHeaderTypeDecoder(object):

    def __init__(self, data):
        self.__data = data
        self.__size = 8

    @property
    def size(self):
        return self.__size

    @property
    def blockLength(self):
        return struct.unpack_from("<h", self.__data)[0]

    @property
    def templateId(self):
        return struct.unpack_from("<h", self.__data, 2)[0]

    @property
    def schemaId(self):
        return struct.unpack_from("<h", self.__data, 4)[0]

    @property
    def version(self):
        return struct.unpack_from("<h", self.__data, 6)[0]




class carDecoder(object):

    def __init__(self, data):
        self.__data = data
        self.__var_offset = [0]

    @property
    def size(self):
        return 24 + self.__var_offset[0]


class carEncoder(object):

    def __init__(self, data, size, offset):
        self.__data = data
        self.__offset = offset
        self.__size = size
        self.__var_offset = [0]

    @property
    def size(self):
        return self.__size + 24 + self.__var_offset[0]


def createEncoder(template, data):
    if template == Templates.car:
        hdr = MessageHeaderTypeEncoder(data, 0);
        hdr.blockLength = 24;
        hdr.templateId = 1;
        hdr.schemaId = 1;
        hdr.version = 1;
        return carEncoder(data, hdr.size, hdr.size);
