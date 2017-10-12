#include <string.h>
#include <stdint.h>

#ifdef _cplusplus
extern "C"
{
#endif
#define SBE_OK 0
#define SBE_FAILED 1

typedef int64_t sbe_car_Int64;

typedef struct
{
  int64_t mantissa;
  int8_t exponent;
} sbe_car_decimal;

typedef uint16_t sbe_car_ModelYear;
typedef char sbe_car_VehicleCode[6];
typedef int32_t sbe_car_someNumbers[5];

typedef enum
{
  F = 0,
  T = 1
} sbe_car_BooleanType;

typedef enum
{
  model_A = 'A',
  model_B = 'B',
  model_C = 'C'
} sbe_car_Model;

// Types section ended.

typedef enum {
  sbe_car_type_RequiredPrimitives = 10,
  sbe_car_type_OptionalPrimitives = 2,
  sbe_car_type_Car = 3
} sbe_car_type_t;

typedef struct sbe_RequiredPrimitives_s sbe_RequiredPrimitives_t;
typedef struct sbe_OptionalPrimitives_s sbe_OptionalPrimitives_t;
typedef struct sbe_Car_s sbe_Car_t;

void* sbe_create(sbe_car_type_t);
void* sbe_recreate(sbe_car_type_t type, void* ptr);
int8_t sbe_decode(char* buf, size_t len, void* ptr);

#ifdef _cplusplus
}
#endif
