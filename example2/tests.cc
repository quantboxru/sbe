#include "utils.h"
#include "car.h"
#include <gtest/gtest.h>

//-------------------------------------------------------------------------------------------------------------------//
size_t car_encode(char* data, size_t datalen)
{
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
   car_car_set_model(car, (const uint8_t*)"!ABCDEF", 8);

   size_t len = car_car_encoder_get_var_offset(car);
   car_encoder_destroy(car);
   return len;
}

//-------------------------------------------------------------------------------------------------------------------//
size_t car_decode(char* data, size_t datalen)
{
   car_car_decoder_t* car;
   car_car_performance_decoder_t* performance;
   car_car_performance_acceleration_decoder_t* acceleration;
   car_car_another_decoder_t* another;

   car = (car_car_decoder_t*)car_decoder_create(data, sizeof(data));
   printf("car.code=0x%08X\n", car_car_get_code(car));

   performance = car_car_get_performance(car);
   printf("car.performance.count=%lu\n", car_car_performance_decode_get_count(performance));
   while ((performance = car_car_performance_decode_next(performance)))
   {
      printf("car.performance.idx=%d\n", (int)car_car_performance_decode_get_idx(performance));
      printf("car.performance.octaneRating=0x%08X\n", car_car_performance_get_octaneRating(performance));

      acceleration = car_car_performance_get_acceleration(performance);
      printf("car.performance.acceleration.count=%lu\n", car_car_performance_acceleration_decode_get_count(acceleration));
      while ((acceleration = car_car_performance_acceleration_decode_next(acceleration)))
      {
         printf("car.performance.acceleration.idx=%d\n", car_car_performance_decode_get_idx(acceleration));
         printf("car.performance.acceleration.mph=0x%04X\n", car_car_performance_acceleration_get_mph(acceleration));
         printf("car.performance.acceleration.seconds=0x%08X\n", car_car_performance_acceleration_get_seconds(acceleration));
      }
   }

   another = car_car_get_another(car);
   printf("car.another.count=%lu\n", car_car_another_decode_get_count(another));
   while ((another = car_car_another_decode_next(another)))
   {
      printf("car.another.idx=%d\n", car_car_another_decode_get_idx(another));
      printf("car.another.number=0x%08X\n", car_car_another_get_number(another));
   }
   size_t model_len = car_car_model_get_length(car);
   printf("car.model(%lu)=%s\n", model_len, (const char*)car_car_model_get_varData(car));

   size_t len = car_car_decoder_get_var_offset(car);
   car_decoder_destroy(car);
   return len;
}

//-------------------------------------------------------------------------------------------------------------------//
TEST(car_tests, test_car_encode_decode)
{
   char data[512];

   printf("Encoding...\n");
   size_t enc_len = car_encode(data, sizeof(data));
   printf("Encoded length: %lu\n", enc_len);

   printf("\n");
   DumpHex(data, enc_len);
   printf("\n");

   printf("Decoding...\n");
   size_t dec_len = car_decode(data, sizeof(data));
   printf("Decoded length: %lu\n", dec_len);

   ASSERT_EQ(enc_len, dec_len) << "Decoded length is not equal to encoded length";
}
