#include "car.h"

#include <gmock/gmock.h>

//-------------------------------------------------------------------------------------------------------------------//
TEST(car_tests, test1)
{
   sbe_car_t* car = (sbe_car_t*)sbe_create(sbe_msg_type_car);
   ASSERT_TRUE(car != NULL);
   ASSERT_EQ(OK, sbe_car_set_id(car, 1));
   ASSERT_EQ(OK, sbe_car_set_name(car, "name", strlen("name")));
}
