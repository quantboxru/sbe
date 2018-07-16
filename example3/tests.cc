#include "utils.h"
#include "proto.h"
// #include <gmock/gmock.h>
#include <gtest/gtest.h>

//-------------------------------------------------------------------------------------------------------------------//
TEST(proto_tests, testMdSubscribe)
{
   char data[1024];

   proto_MdSubscribe_encoder_t* encoder = (proto_MdSubscribe_encoder_t*)proto_encoder_create(
         proto_template_MdSubscribe, data, sizeof(data));
   proto_MdSubscribe_set_req_id(encoder, 0x12345678);
   proto_MdSubscribe_set_instr_id(encoder, 0x1111111111111111);
   proto_MdSubscribe_set_type(encoder, proto_MdType_Statistic);
   proto_MdSubscribe_set_action(encoder, proto_SubsActionType_Snapshot);
   proto_MdSubscribe_set_field_id(encoder, proto_FieldId_Volume);
   proto_MdSubscribe_set_sender_id(encoder, "sender1", strlen("sender1")+1);

   size_t enc_len = proto_MdSubscribe_encoder_get_encoded_length(encoder);
   printf("Encoded length: %lu\n", enc_len);
   proto_encoder_destroy(encoder);

   printf("\n");
   DumpHex(data, enc_len);
   printf("\n");

   proto_MdSubscribe_decoder_t* decoder = (proto_MdSubscribe_decoder_t*)proto_decoder_create(
         data, sizeof(data));

   ASSERT_EQ(proto_MdSubscribe_get_req_id(decoder), 0x12345678);
   ASSERT_EQ(proto_MdSubscribe_get_instr_id(decoder), 0x1111111111111111);
   ASSERT_EQ(proto_MdSubscribe_get_type(decoder), proto_MdType_Statistic);
   ASSERT_EQ(proto_MdSubscribe_get_action(decoder), proto_SubsActionType_Snapshot);
   ASSERT_EQ(proto_MdSubscribe_get_field_id(decoder), proto_FieldId_Volume);

   sbe_str_t sender_id = proto_MdSubscribe_get_sender_id(decoder);
   ASSERT_STREQ(sender_id.data, "sender1");

   size_t dec_len = proto_MdSubscribe_decoder_get_decoded_length(decoder);
   proto_encoder_destroy(decoder);
   printf("Decoded length: %lu\n", dec_len);

   ASSERT_EQ(enc_len, dec_len);
}
