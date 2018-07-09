#include "utils.h"
#include "proto.h"
#include <gmock/gmock.h>

//-------------------------------------------------------------------------------------------------------------------//
TEST(proto_tests, test1)
{
   char data[1024];

   proto_NewOrderSingle_encoder_t* encoder = (proto_NewOrderSingle_encoder_t*)proto_create_encoder(
         proto_template_NewOrderSingle, data, sizeof(data), NULL);
   proto_NewOrderSingle_set_instr_id(encoder, 1000);
}
