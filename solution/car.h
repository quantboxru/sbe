#include <string.h>
#include <stdint.h>

#ifdef _cplusplus
extern "C"
{
#endif
#define SBE_OK 0
#define SBE_FAILED 1

typedef int64_t Int64_t;

typedef struct
{
  int64_t mantissa;
  int8_t exponent;
} sbe_car_decimal_t;

typedef uint16_t sbe_car_ModelYear_t;
typedef char sbe_car_VehicleCode_t[6];
typedef int32_t sbe_car_someNumbers_t[5];

typedef enum
{
  sbe_car_BooleanType_F = 0,
  sbe_car_BooleanType_T = 1
} sbe_car_BooleanType_t;

typedef enum
{
  sbe_car_Model_A = 'A',
  sbe_car_Model_B = 'B',
  sbe_car_Model_C = 'C'
} sbe_car_Model_t;

// Types section ended.

typedef enum {
  sbe_car_type_RequiredPrimitives = 10,
  sbe_car_type_OptionalPrimitives = 2,
  sbe_car_type_Car = 3
} sbe_car_type_t;

void* sbe_create(sbe_car_type_t);
void* sbe_create_inplace(sbe_car_type_t type, void* buf, size_t buf_len);
void* sbe_decode(char* buf, size_t len, sbe_error_t** err);

#ifdef _cplusplus
}
#endif
