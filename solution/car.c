#include "car.h"
#include <stdlib.h>

struct sbe_RequiredPrimitives_s
{
  char Char;
  int8_t Int8_t;
  uint8_t uint8_t;
  int16_t Int16_t;
  uint16_t uint16_t;
  int32_t Int32_t;
  uint32_t uint32_t;
  int64_t Int64_t;
  uint64_t uint64_t;
};

struct sbe_OptionalPrimitives_s
{
  char Char;
  int8_t Int8_t;
  uint8_t uint8_t;
  int16_t Int16_t;
  uint16_t uint16_t;
  int32_t Int32_t;
  uint32_t uint32_t;
  int64_t Int64_t;
  uint64_t uint64_t;
};

struct sbe_Car_s
{
  uint32_t serialNumber;
  ModelYear modelYear;
  BooleanType available;
  Model code;
  VehicleCode vehicleCode;
  Int64 magicNumber;
  decimal magicDecimalNumber;
  Engine engine;
};

//--------------------------------------------------------------------------------------------------------------------//
void* sbe_create(sbe_msg_type_t type)
{
   switch(type)
   {
      case sbe_msg_type_RequiredPrimitives:
      {
        return malloc(sizeof(sbe_msg_type_RequiredPrimitives))
      }
      case sbe_msg_type_OptionalPrimitives:
      {
        return malloc(sizeof(sbe_msg_type_RequiredPrimitives))
      }
      case sbe_msg_type_Car:
      {
        return malloc(sizeof(sbe_msg_type_RequiredPrimitives))
      }
   }
   return NULL;
}

//--------------------------------------------------------------------------------------------------------------------//
void* sbe_decode(char* buf, size_t len)
{
   return (void*)buf;
}
