#include "car.h"
#include <stdlib.h>

struct sbe_messageHeader_s
{
  uint16_t blockLength;
  uint16_t templateId;
  uint16_t schemaId;
  uint16_t version;
};

struct sbe_car_Engine_s
{
  uint16_t capacity;
  uint8_t numCylinders;
  const uint16_t maxRpm; // const == 9000
};

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
  sbe_car_ModelYear_t modelYear;
  sbe_car_BooleanType_t available;
  sbe_car_Model_t code;
  sbe_car_VehicleCode_t vehicleCode;
  Int64_t magicNumber;
  sbe_car_decimal_t magicDecimalNumber;
  sbe_car_Engine_t engine;
};

//--------------------------------------------------------------------------------------------------------------------//
void* sbe_create(sbe_car_type_t type)
{
   switch(type)
   {
      case sbe_car_type_RequiredPrimitives:
      {
          return malloc(sizeof(sbe_RequiredPrimitives_s));
      }
      case sbe_car_type_OptionalPrimitives:
      {
          return malloc(sizeof(sbe_OptionalPrimitives_s));
      }
      case sbe_car_type_Car:
      {
          return malloc(sizeof(sbe_Car_s));
      }
   }
   return NULL;
}

//--------------------------------------------------------------------------------------------------------------------//
void* sbe_create_inplace(she_msg_type_t type, void* buf, size_t buf_len)
{
   return NULL;
}

//--------------------------------------------------------------------------------------------------------------------//
void* sbe_create_inplace(sbe_car_type_t type, void* buf, size_t buf_len)
{
   return NULL;
}

//--------------------------------------------------------------------------------------------------------------------//
void* sbe_decode(char* buf, size_t len, sbe_error_t** err)
{
   return NULL;
}

//--------------------------------------------------------------------------------------------------------------------//
//RequiredPrimitives type section
//--------------------------------------------------------------------------------------------------------------------//
uint32_t sbe_car_get_serialNumber(const sbe_Car_t* msg)
{
    return msg->serialNumber;
}

int32_t sbe_car_set_serialNumber(sbe_Car_t* msg, uint32_t val)
{
    msg->serialNumber = val;
    return OK;
}

//--------------------------------------------------------------------------------------------------------------------//
ModelYear sbe_car_get_modelYear(const sbe_Car_t* msg)
{
    return msg->modelYear;
}

int32_t sbe_car_set_modelYear(sbe_Car_t* msg, ModelYear val)
{
    msg->modelYear = val;
    return OK;
}

//--------------------------------------------------------------------------------------------------------------------//
BooleanType sbe_car_get_booleanType(const sbe_Car_t* msg)
{
    return msg->available;
}

int32_t sbe_car_set_booleanType(sbe_Car_t* msg, BooleanType value)
{
    msg->available = value;
    return OK;
}

//--------------------------------------------------------------------------------------------------------------------//
Model sbe_car_get_model(const sbe_Car_t* msg)
{
    return msg->code;
}

int32_t sbe_car_set_model(sbe_Car_t* msg, Model value)
{
    msg->code = value;
    return OK;
}

//--------------------------------------------------------------------------------------------------------------------//
VehicleCode* sbe_car_get_vehicleCode(const sbe_Car_t* msg)
{
    return &msg->vehicleCode;
}

int32_t sbe_car_set_VehicleCode(sbe_Car_t* msg, const char* value, size_t len)
{
    memcpy(msg->vehicleCode, value, len);
    return OK;
}

//--------------------------------------------------------------------------------------------------------------------//
Int64 sbe_car_get_magicNumber(const sbe_Car_t* msg)
{
    return msg->magicNumber;
}

int32_t sbe_car_set_magicNumber(sbe_Car_t* msg, Int64 value)
{
    msg->magicNumber = value;
    return OK;
}

//--------------------------------------------------------------------------------------------------------------------//
decimal sbe_car_get_magicDecimalNumber(const sbe_Car_t* msg)
{
    return msg->magicDecimalNumber;
}

int32_t sbe_car_set_magicDecimalNumber(sbe_Car_t* msg, decimal value)
{
    msg->magicDecimalNumber = value;
    return OK;
}

//--------------------------------------------------------------------------------------------------------------------//
Engine sbe_car_get_Engine(const sbe_Car_t* msg)
{
    return msg->engine;
}

int32_t sbe_car_set_Engine(sbe_Car_t* msg, Engine value)
{
    msg->engine = value;
    return OK;
}







