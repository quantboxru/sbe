/**
 * car.c
 */
#include "car.h"
#include <stdlib.h>

struct sbe_car_s
{
   Id id;
   CarName name;
};

//--------------------------------------------------------------------------------------------------------------------//
void* sbe_create(sbe_msg_type_t type)
{
   switch(type)
   {
      case sbe_msg_type_car:
      {
         return malloc(sizeof(sbe_car_t));
      }
   }
   return NULL;
}

//--------------------------------------------------------------------------------------------------------------------//
void* sbe_decode(char* buf, size_t len)
{
   return (void*)buf;
}

//--------------------------------------------------------------------------------------------------------------------//
Id sbe_car_get_id(const sbe_car_t* msg)
{
   return msg->id;
}

//--------------------------------------------------------------------------------------------------------------------//
int32_t sbe_car_set_id(sbe_car_t* msg, Id val)
{
   msg->id = val;
   return OK;
}

//--------------------------------------------------------------------------------------------------------------------//
const CarName* sbe_car_get_name(const sbe_car_t* msg)
{
   return &msg->name;
}

//--------------------------------------------------------------------------------------------------------------------//
int32_t sbe_car_set_name(sbe_car_t* msg, const char* val, size_t len)
{
   memcpy(msg->name, val, len);
   return OK;
}
