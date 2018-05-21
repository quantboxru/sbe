#include "custom_group_size_encoding.h"

void
custom_group_size_encoding_reset(custom_group_size_encoding_codec_t* h, char* buffer, size_t len, size_t offset)
{
    h->buffer = buffer;
    h->bufferLength = len;
    h->offset = offset;
}


uint16_t
custom_group_size_encoding_get_blockLength(custom_group_size_encoding_codec_t* h)
{
    custom_group_size_encoding_t* p = (custom_group_size_encoding_t*)(h->buffer + h->offset);
    return p->blockLength;
}


void
custom_group_size_encoding_set_blockLength(custom_group_size_encoding_codec_t* h, uint16_t newValue)
{
    custom_group_size_encoding_t* p = (custom_group_size_encoding_t*)(h->buffer + h->offset);
    p->blockLength = newValue;
}


uint8_t
custom_group_size_encoding_get_numInGroup(custom_group_size_encoding_codec_t* h)
{
    custom_group_size_encoding_t* p = (custom_group_size_encoding_t*)(h->buffer + h->offset);
    return p->numInGroup;
}


void
custom_group_size_encoding_set_numInGroup(custom_group_size_encoding_codec_t* h, uint8_t newValue)
{
    custom_group_size_encoding_t* p = (custom_group_size_encoding_t*)(h->buffer + h->offset);
    p->numInGroup = newValue;
}
