#include <string.h>
#include <stdint.h>

#define OK 0
#define FAILED 1

typedef struct
{
  uint16_t blockLength;
  uint16_t templateId;
  uint16_t schemaId;
  uint16_t version;
} messageHeader;

typedef int64_t Int64;

typedef struct
{
  int64_t mantissa;
  int8_t exponent;
} decimal;

typedef uint16_t ModelYear;
typedef char VehicleCode[6];
typedef int32_t someNumbers[5];

typedef struct
{
  uint16_t capacity;
  uint8_t numCylinders;
  const uint16_t maxRpm; // const == 9000
} Engine;

typedef enum
{
  F = 0,
  T = 1
} BooleanType;

typedef enum
{
  A = 'A',
  B = 'B',
  C = 'C'
} Model;

// Types section ended.

typedef enum {
  sbe_msg_type_RequiredPrimitives = 10,
  sbe_msg_type_OptionalPrimitives = 2,
  sbe_msg_type_Car = 3
} sbe_msg_type_t;

typedef struct sbe_RequiredPrimitives_s sbe_RequiredPrimitives_t;
typedef struct sbe_OptionalPrimitives_s sbe_OptionalPrimitives_t;
typedef struct sbe_Car_s sbe_Car_t;

void* sbe_create(sbe_msg_type_t);
void* sbe_decode(char* buf, size_t len);

// а дальше - геттеры и сеттеры.
