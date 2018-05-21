#ifndef GROUP_SIZE_ENCODING_H
#define GROUP_SIZE_ENCODING_H

#include <stdlib.h>

#pragma pack(push)
#pragma pack(1)
typedef struct
{
   uint16_t blockLength;
   uint16_t numInGroup;
} group_size_encoding_t;
#pragma pack(pop)


typedef struct
{
    char* buffer;
    size_t bufferLength;
    size_t offset;
} group_size_encoding_codec_t;


void
group_size_encoding_reset(group_size_encoding_codec_t* h, char* buffer, size_t len, size_t offset);


// char* group_size_encoding_codec_get_buffer(group_size_encoding_codec_t* h);
// size_t group_size_encoding_codec_get_bufferLength(group_size_encoding_codec_t* h);
// size_t group_size_encoding_codec_get_offset(group_size_encoding_codec_t* h);


uint16_t
group_size_encoding_get_blockLength(group_size_encoding_codec_t* h);

void
group_size_encoding_set_blockLength(group_size_encoding_codec_t* h, uint16_t newValue);

uint16_t
group_size_encoding_get_numInGroup(group_size_encoding_codec_t* h);

void
group_size_encoding_set_numInGroup(group_size_encoding_codec_t* h, uint16_t newValue);


#endif
