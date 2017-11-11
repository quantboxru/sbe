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
  struct sbe_car_Engine_s engine;
};

//--------------------------------------------------------------------------------------------------------------------//
void* sbe_create(sbe_car_type_t type)
{
   switch(type)
   {
      case sbe_car_type_RequiredPrimitives:
      {
          return malloc(sizeof(struct sbe_RequiredPrimitives_s));
      }
      case sbe_car_type_OptionalPrimitives:
      {
          return malloc(sizeof(struct sbe_OptionalPrimitives_s));
      }
      case sbe_car_type_Car:
      {
          return malloc(sizeof(struct sbe_Car_s));
      }
   }
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
uint32_t sbe_car_get_serialNumber(const struct sbe_Car_s* msg)
{
    return msg->serialNumber;
}

int32_t sbe_car_set_serialNumber(struct sbe_Car_s* msg, uint32_t val)
{
    msg->serialNumber = val;
    return SBE_OK;
}

//--------------------------------------------------------------------------------------------------------------------//
sbe_car_ModelYear_t sbe_car_get_modelYear(const struct sbe_Car_s* msg)
{
    return msg->modelYear;
}

int32_t sbe_car_set_modelYear(struct sbe_Car_s* msg, sbe_car_ModelYear_t val)
{
    msg->modelYear = val;
    return SBE_OK;
}

//--------------------------------------------------------------------------------------------------------------------//
sbe_car_BooleanType_t sbe_car_get_booleanType(const struct sbe_Car_s* msg)
{
    return msg->available;
}

int32_t sbe_car_set_booleanType(struct sbe_Car_s* msg, sbe_car_BooleanType_t value)
{
    msg->available = value;
    return SBE_OK;
}

//--------------------------------------------------------------------------------------------------------------------//
sbe_car_Model_t sbe_car_get_model(const struct sbe_Car_s* msg)
{
    return msg->code;
}

int32_t sbe_car_set_model(struct sbe_Car_s* msg, sbe_car_Model_t value)
{
    msg->code = value;
    return SBE_OK;
}

//--------------------------------------------------------------------------------------------------------------------//
const sbe_car_VehicleCode_t* sbe_car_get_vehicleCode(const struct sbe_Car_s* msg)
{
    return &msg->vehicleCode;
}

int32_t sbe_car_set_VehicleCode(struct sbe_Car_s* msg, const char* value, size_t len)
{
    memcpy(msg->vehicleCode, value, len);
    return SBE_OK;
}

//--------------------------------------------------------------------------------------------------------------------//
Int64_t sbe_car_get_magicNumber(const struct sbe_Car_s* msg)
{
    return msg->magicNumber;
}

int32_t sbe_car_set_magicNumber(struct sbe_Car_s* msg, Int64_t value)
{
    msg->magicNumber = value;
    return SBE_OK;
}

//--------------------------------------------------------------------------------------------------------------------//
sbe_car_decimal_t sbe_car_get_magicDecimalNumber(const struct sbe_Car_s* msg)
{
    return msg->magicDecimalNumber;
}

int32_t sbe_car_set_magicDecimalNumber(struct sbe_Car_s* msg, sbe_car_decimal_t value)
{
    msg->magicDecimalNumber = value;
    return SBE_OK;
}

//--------------------------------------------------------------------------------------------------------------------//
struct sbe_car_Engine_s sbe_car_get_Engine(const struct sbe_Car_s* msg)
{
    return msg->engine;
}

int32_t sbe_car_set_Engine(struct sbe_Car_s* msg, struct sbe_car_Engine_s value)
{
    msg->engine = value;
    return SBE_OK;
}







