/**
 * car.h
 */

#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define OK 0
#define FAILED 1

typedef int32_t Id;
typedef char CarName[20];

typedef enum
{
   sbe_msg_type_car = 1
} sbe_msg_type_t;

typedef struct sbe_car_s sbe_car_t;

void* sbe_create(sbe_msg_type_t);
void* sbe_decode(char* buf, size_t len);

Id sbe_car_get_id(const sbe_car_t* msg);
int32_t sbe_car_set_id(sbe_car_t* msg, Id val);

const CarName* sbe_car_get_name(const sbe_car_t* msg);
int32_t sbe_car_set_name(sbe_car_t* msg, const char* val, size_t len);

#ifdef __cplusplus
}
#endif
