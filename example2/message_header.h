#ifndef MESSAGE_HEADER_H
#define MESSAGE_HEADER_H

#include <stdlib.h>

#pragma pack(push)
#pragma pack(1)
typedef struct
{
   uint16_t blockLength;
   uint16_t template_id;
   uint16_t schema_id;
   uint16_t version;
} message_header_t;
#pragma pack(pop)


typedef struct
{
    char* buffer;
    size_t bufferLength;
    size_t offset;
} message_header_codec_t;


// void message_header_reset(message_header_codec_t* h, char* buffer, size_t len, size_t offset);


// char* message_header_get_buffer(message_header_codec_t* h);
// size_t message_header_get_bufferLength(message_header_codec_t* h);
// size_t message_header_get_offset(message_header_codec_t* h);


// uint16_t message_header_get_blockLength(message_header_codec_t* h);
// void message_header_set_blockLength(message_header_codec_t* h, uint16_t newValue);


#endif
