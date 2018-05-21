#ifndef CUSTOM_GROUP_SIZE_ENCODING_H
#define CUSTOM_GROUP_SIZE_ENCODING_H

#include <stdlib.h>

#pragma pack(push)
#pragma pack(1)
typedef struct
{
   uint16_t blockLength;
   uint8_t numInGroup;
} custom_group_size_encoding_t;
#pragma pack(pop)


typedef struct
{
    char* buffer;
    size_t bufferLength;
    size_t offset;
} custom_group_size_encoding_codec_t;


void
custom_group_size_encoding_reset(custom_group_size_encoding_codec_t* h, char* buffer, size_t len, size_t offset);

// char* custom_group_size_encoding_get_buffer(custom_group_size_encoding_codec_t* h);
// size_t custom_group_size_encoding_get_bufferlength(custom_group_size_encoding_codec_t* h);
// size_t custom_group_size_encoding_get_offset(custom_group_size_encoding_codec_t* h);

uint16_t
custom_group_size_encoding_get_blockLength(custom_group_size_encoding_codec_t* h);

void
custom_group_size_encoding_set_blockLength(custom_group_size_encoding_codec_t* h, uint16_t newValue);

uint8_t
custom_group_size_encoding_get_numInGroup(custom_group_size_encoding_codec_t* h);

void
custom_group_size_encoding_set_numInGroup(custom_group_size_encoding_codec_t* h, uint8_t newValue);


#endif
