#include "utils.h"
#include "car_encoder.h"
#include <gtest/gtest.h>

//-------------------------------------------------------------------------------------------------------------------//
#define SBE_CAR_EXAMPLE2_FILEPATH "/tmp/sbe_car_example2.bin"

//-------------------------------------------------------------------------------------------------------------------//
TEST(car_tests, test_car_encoder)
{
   char data[512];

   car_car_encoder_t* car;
   car_car_performance_encoder_t* performance;
   car_car_performance_acceleration_encoder_t* acceleration;
   car_car_another_encoder_t* another;

   car = (car_car_encoder_t*)car_encoder_create(car_template_car, data, sizeof(data));

   car_car_set_code(car, 0x11111111);

   performance = car_car_add_performance(car, 3);

   performance = car_car_performance_encode_next(performance);
   car_car_performance_set_octaneRating(performance, 0x22222222);
   acceleration = car_car_performance_add_acceleration(performance, 4);

   acceleration = car_car_performance_acceleration_encode_next(acceleration);
   car_car_performance_acceleration_set_mph(acceleration, 0x3333);
   car_car_performance_acceleration_set_seconds(acceleration, 0x44444444);

   acceleration = car_car_performance_acceleration_encode_next(acceleration);
   car_car_performance_acceleration_set_mph(acceleration, 0x5555);
   car_car_performance_acceleration_set_seconds(acceleration, 0x66666666);

   acceleration = car_car_performance_acceleration_encode_next(acceleration);
   car_car_performance_acceleration_set_mph(acceleration, 0x7777);
   car_car_performance_acceleration_set_seconds(acceleration, 0x88888888);

   acceleration = car_car_performance_acceleration_encode_next(acceleration);
   car_car_performance_acceleration_set_mph(acceleration, 0xAAAA);
   car_car_performance_acceleration_set_seconds(acceleration, 0xBBBBBBBB);

   performance = car_car_performance_encode_next(performance);
   car_car_performance_set_octaneRating(performance, 0x99999999);
   acceleration = car_car_performance_add_acceleration(performance, 0);

   performance = car_car_performance_encode_next(performance);
   car_car_performance_set_octaneRating(performance, 0x11111111);
   acceleration = car_car_performance_add_acceleration(performance, 2);

   acceleration = car_car_performance_acceleration_encode_next(acceleration);
   car_car_performance_acceleration_set_mph(acceleration, 0x2222);
   car_car_performance_acceleration_set_seconds(acceleration, 0x33333333);

   acceleration = car_car_performance_acceleration_encode_next(acceleration);
   car_car_performance_acceleration_set_mph(acceleration, 0x4444);
   car_car_performance_acceleration_set_seconds(acceleration, 0x55555555);

   another = car_car_add_another(car, 1);
   another = car_car_another_encode_next(another);
   car_car_another_set_number(another, 0xDDDDDDDD);

   size_t len = car_car_encoder_get_var_offset(car);

   FILE* fp;
   if ((fp = fopen(SBE_CAR_EXAMPLE2_FILEPATH, "wb")))
   {
      fwrite(data, 1, len, fp);
      fclose(fp);
   }

   DumpHex(data, len);
   printf("Encoded length: %lu\n", len);

   car_encoder_destroy(car);
}

//-------------------------------------------------------------------------------------------------------------------//
TEST(car_tests, test2)
{
   ASSERT_EQ(0, 0) << "0 is equal 0";
}
