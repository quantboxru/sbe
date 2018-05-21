#include "group_size_encoding.h"


void
group_size_encoding_reset(group_size_encoding_codec_t* h, char* buffer, size_t len, size_t offset)
{
    h->buffer = buffer;
    h->bufferLength = len;
    h->offset = offset;
}


uint16_t
group_size_encoding_get_blockLength(group_size_encoding_codec_t* h)
{
    group_size_encoding_t* p = (group_size_encoding_t*)(h->buffer + h->offset);
    return p->blockLength;
}


void
group_size_encoding_set_blockLength(group_size_encoding_codec_t* h, uint16_t newValue)
{
    group_size_encoding_t* p = (group_size_encoding_t*)(h->buffer + h->offset);
    p->blockLength = newValue;
}


uint16_t
group_size_encoding_get_numInGroup(group_size_encoding_codec_t* h)
{
    group_size_encoding_t* p = (group_size_encoding_t*)(h->buffer + h->offset);
    return p->numInGroup;
}


void
group_size_encoding_set_numInGroup(group_size_encoding_codec_t* h, uint16_t newValue)
{
    group_size_encoding_t* p = (group_size_encoding_t*)(h->buffer + h->offset);
    p->numInGroup = newValue;
}
