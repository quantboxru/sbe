#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "location.h"
#include "group_size_encoding.h"
#include "custom_group_size_encoding.h"
#include "message_header.h"
#include "utils.h"

// business logic

typedef enum
{
    car_template_car = 1,
} car_templates_t;


#pragma pack(push)
#pragma pack(1)
typedef struct
{
    int32_t code;
} car_t;
#pragma pack(pop)


#pragma pack(push)
#pragma pack(1)
typedef struct
{
    uint32_t octaneRating;
} car_performance_t;
#pragma pack(pop)


#pragma pack(push)
#pragma pack(1)
typedef struct
{
    uint16_t mph;
    uint32_t seconds;
} car_performance_acceleration_t;
#pragma pack(pop)


#pragma pack(push)
#pragma pack(1)
typedef struct
{
   uint32_t length;
   uint8_t varData;
} var_string_encoding_type_t;
#pragma pack(pop)


typedef struct
{
    group_location_t location;
    custom_group_size_encoding_codec_t dimensions;
} car_performance_acceleration_codec_t;


typedef struct
{
    group_location_t location;
    group_size_encoding_codec_t dimensions;
    car_performance_acceleration_codec_t acceleration;
} car_performance_codec_t;


typedef struct
{
    message_location_t location;
    car_performance_codec_t performance;
} car_codec_t;


void
car_reset(car_codec_t* codec, char* buffer, size_t len, size_t offset, size_t blklen)
{
    codec->location.buffer = buffer;
    codec->location.offset = offset;
    codec->location.bufferLength = len;
    codec->location.blockLength = blklen;
    codec->location.positionPtr = &codec->location.position;
    codec->location.position = codec->location.offset + codec->location.blockLength;
}


void
car_wrap_to_decode(car_codec_t* codec, char* buffer, size_t len, size_t offset, size_t blklen)
{
    car_reset(codec, buffer, len, offset, blklen);
}


void
car_wrap_to_encode(car_codec_t* codec, char* buffer, size_t len, size_t offset)
{
    car_reset(codec, buffer, len, offset, sizeof(car_t));
}


void
car_performance_wrap_to_decode(car_performance_codec_t* codec, char* buffer, size_t len, size_t* pos)
{
    car_performance_codec_t* obj = codec;

    group_location_t* l = &obj->location;
    l->buffer = buffer;
    l->bufferLength = len;

    // group_size_encoding_reset(&obj->dimensions, buffer, len, *pos);
    // l->blockLength = group_size_encoding_get_blockLength(&obj->dimensions);
    // l->count = group_size_encoding_get_numInGroup(&obj->dimensions);

    // obj->dimensions.buffer = buffer;
    // obj->dimensions.bufferLength = len;
    // obj->dimensions.offset = *pos;
    group_size_encoding_t* p = (group_size_encoding_t*)(buffer + *pos);
    l->blockLength = p->blockLength;
    l->count = p->numInGroup;

    l->index = -1;
    l->positionPtr = pos;
    *l->positionPtr = *l->positionPtr + sizeof(group_size_encoding_t);
}


void
car_performance_wrap_to_encode(car_performance_codec_t* codec, char* buffer, size_t len, size_t* pos, uint16_t count)
{
    car_performance_codec_t* obj = codec;
    group_location_t* l = &obj->location;
    l->buffer = buffer;
    l->bufferLength = len;

    // group_size_encoding_reset(&obj->dimensions, buffer, len, *pos);
    // group_size_encoding_set_blockLength(&obj->dimensions, sizeof(car_performance_t));
    // group_size_encoding_set_numInGroup(&obj->dimensions, count);

    group_size_encoding_t* p = (group_size_encoding_t*)(buffer + *pos);
    p->blockLength = sizeof(car_performance_t);
    p->numInGroup = count;

    l->offset = 0;
    l->index = -1;
    l->count = count;
    l->blockLength = sizeof(car_performance_t);
    l->positionPtr = pos;
    *l->positionPtr = *l->positionPtr + sizeof(group_size_encoding_t);
}


void
car_performance_acceleration_wrap_to_decode(car_performance_acceleration_codec_t* codec, char* buffer, size_t len, size_t* pos)
{
    car_performance_acceleration_codec_t* obj = codec;
    group_location_t* l = &obj->location;
    l->buffer = buffer;
    l->bufferLength = len;

    // custom_group_size_encoding_reset(&obj->dimensions, buffer, len, *pos);
    // l->blockLength = custom_group_size_encoding_get_blockLength(&obj->dimensions);
    // l->count = custom_group_size_encoding_get_numInGroup(&obj->dimensions);

    custom_group_size_encoding_t* p = (custom_group_size_encoding_t*)(buffer + *pos);
    l->blockLength = p->blockLength;
    l->count = p->numInGroup;

    l->index = -1;
    l->positionPtr = pos;
    *l->positionPtr = *l->positionPtr + sizeof(custom_group_size_encoding_t);
}


void
car_performance_acceleration_wrap_to_encode(car_performance_acceleration_codec_t* codec, char* buffer, size_t len, size_t* pos, uint16_t count)
{
    car_performance_acceleration_codec_t* obj = codec;
    group_location_t* l = &obj->location;
    l->buffer = buffer;
    l->bufferLength = len;

    // custom_group_size_encoding_reset(&obj->dimensions, buffer, len, *pos);
    // custom_group_size_encoding_set_blockLength(&obj->dimensions, sizeof(car_performance_acceleration_t));
    // custom_group_size_encoding_set_numInGroup(&obj->dimensions, count);

    custom_group_size_encoding_t* p = (custom_group_size_encoding_t*)(buffer + *pos);
    p->blockLength = sizeof(car_performance_acceleration_t);
    p->numInGroup = count;

    l->index = -1;
    l->count = count;
    l->blockLength = sizeof(car_performance_acceleration_t);
    l->positionPtr = pos;
    *l->positionPtr = *l->positionPtr + sizeof(custom_group_size_encoding_t);
}


car_performance_codec_t* 
car_get_performance(car_codec_t* codec)
{
    car_performance_codec_t* obj = &codec->performance;
    message_location_t* l = &codec->location;
    car_performance_wrap_to_decode(obj, l->buffer, l->bufferLength, l->positionPtr);
    return obj;
}


car_performance_codec_t* 
car_set_performanceCount(car_codec_t* codec, uint16_t count)
{
    car_performance_codec_t* obj = &codec->performance;
    message_location_t* l = &codec->location;
    car_performance_wrap_to_encode(obj, l->buffer, l->bufferLength, l->positionPtr, count);
    return obj;
}


bool
car_performance_has_next(car_performance_codec_t* codec)
{
    return codec->location.index + 1 < codec->location.count;
}


car_performance_codec_t*
car_performance_next(car_performance_codec_t* codec)
{
    // printf("car_performance_next(): performance.offset.in=%lu, blockLength=%lu\n", codec->location.offset, codec->location.blockLength);
    codec->location.offset = *codec->location.positionPtr;
    // printf("car_performance_next(): performance.offset.mid=%lu, blockLength=%lu\n", codec->location.offset, codec->location.blockLength);
    *codec->location.positionPtr = codec->location.offset + codec->location.blockLength;
    // printf("car_performance_next(): performance.positionPtr=%lu\n", *codec->location.positionPtr);
    ++codec->location.index;
    // printf("car_performance_next(): performance.offset.out=%lu, blockLength=%lu\n", codec->location.offset, codec->location.blockLength);
    return codec;
}


car_performance_acceleration_codec_t*
car_performance_get_acceleration(car_performance_codec_t* codec)
{
    car_performance_acceleration_codec_t* obj = &codec->acceleration;
    group_location_t* l = &codec->location;
    car_performance_acceleration_wrap_to_decode(obj, l->buffer, l->bufferLength, l->positionPtr);
    return obj;
}


car_performance_acceleration_codec_t*
car_performance_set_accelerationCount(car_performance_codec_t* codec, uint8_t count)
{
    car_performance_acceleration_codec_t* obj = &codec->acceleration;
    group_location_t* l = &codec->location;
    car_performance_acceleration_wrap_to_encode(obj, l->buffer, l->bufferLength, l->positionPtr, count);
    return obj;
}


bool
car_performance_acceleration_has_next(car_performance_acceleration_codec_t* codec)
{
    return codec->location.index + 1 < codec->location.count;
}


car_performance_acceleration_codec_t*
car_performance_acceleration_next(car_performance_acceleration_codec_t* codec)
{
    codec->location.offset = *codec->location.positionPtr;
    *codec->location.positionPtr = codec->location.offset + codec->location.blockLength;
    ++codec->location.index;
    return codec;
}

void car_set_code(car_codec_t* codec, int32_t newValue)
{
    car_t* p = (car_t*)(codec->location.buffer+codec->location.offset);
    p->code = newValue;
}

int32_t car_get_code(car_codec_t* codec)
{
    car_t* p = (car_t*)(codec->location.buffer+codec->location.offset);
    return p->code;
}

void car_performance_set_octaneRating(car_performance_codec_t* codec, uint32_t newValue)
{
    car_performance_t* p = (car_performance_t*)(codec->location.buffer+codec->location.offset);
    p->octaneRating = newValue;
}

uint32_t car_performance_get_octaneRating(car_performance_codec_t* codec)
{
    car_performance_t* p = (car_performance_t*)(codec->location.buffer+codec->location.offset);
    return p->octaneRating;
}


#if 0
//----------------------
uint32_t car_performance_get_usageDescriptionLength(car_performance_codec_t* codec)
{
    group_location_t* l = &codec->location;
    var_string_encoding_type_t* p = (var_string_encoding_type_t*)(codec->location.buffer + *l->positionPtr);
    return p->length;
}

const char* car_performance_get_usageDescription(car_performance_codec_t* codec)
{
    group_location_t* l = &codec->location;
    var_string_encoding_type_t* p = (var_string_encoding_type_t*)(codec->location.buffer + *l->positionPtr);
    return (const char*)p->varData;
}
#endif


void
car_performance_acceleration_set_mph(car_performance_acceleration_codec_t* codec, uint16_t newValue)
{
    car_performance_acceleration_t* p = (car_performance_acceleration_t*)(codec->location.buffer+codec->location.offset);
    p->mph = newValue;
}

uint16_t
car_performance_acceleration_get_mph(car_performance_acceleration_codec_t* codec)
{
    car_performance_acceleration_t* p = (car_performance_acceleration_t*)(codec->location.buffer+codec->location.offset);
    return p->mph;
}

void
car_performance_acceleration_set_seconds(car_performance_acceleration_codec_t* codec, uint32_t newValue)
{
    car_performance_acceleration_t* p = (car_performance_acceleration_t*)(codec->location.buffer+codec->location.offset);
    p->seconds = newValue;
}

uint32_t
car_performance_acceleration_get_seconds(car_performance_acceleration_codec_t* codec)
{
    car_performance_acceleration_t* p = (car_performance_acceleration_t*)(codec->location.buffer+codec->location.offset);
    return p->seconds;
}

// testing

size_t encode_hdr(message_header_t* hdr, char* buffer, size_t len, size_t offset)
{
    message_header_t* p = (message_header_t*)(buffer + offset);
    *p = *hdr;

    // hdr->blockLength = sizeof(car_t);
    // hdr->template_id = car_template_car;
    // hdr->schema_id = 123;
    // hdr->version = 456;

    return sizeof(message_header_t);
}

size_t decode_hdr(message_header_t* hdr, char *buffer, size_t len, size_t offset)
{
    message_header_t* p = (message_header_t*)(buffer + offset);
    *hdr = *p;

    printf("messageHeader.blockLength=%u\n",  hdr->blockLength);
    printf("messageHeader.templateId=%u\n", hdr->template_id);
    printf("messageHeader.schemaId=%u\n", hdr->schema_id);
    printf("messageHeader.schemaVersion=%u\n", hdr->version);
    printf("messageHeader.encodedLength=%lu\n", sizeof(message_header_t));

    return sizeof(message_header_t);
}

size_t encode_car(car_codec_t* car, char *buffer, size_t len, size_t offset)
{
    car_wrap_to_encode(car, buffer, len, offset);

    car_set_code(car, 0x11);

    car_performance_acceleration_codec_t* acceleration;
    car_performance_codec_t* performance = car_set_performanceCount(car, 3);

    car_performance_next(performance);
    car_performance_set_octaneRating(performance, 5);
    acceleration = car_performance_set_accelerationCount(performance, 3);
    car_performance_acceleration_next(acceleration);
    car_performance_acceleration_set_mph(acceleration, 0x1234);
    car_performance_acceleration_set_seconds(acceleration, 0x12345678);
    car_performance_acceleration_next(acceleration);
    car_performance_acceleration_set_mph(acceleration, 0x1235);
    car_performance_acceleration_set_seconds(acceleration, 0x12345679);
    car_performance_acceleration_next(acceleration);
    car_performance_acceleration_set_mph(acceleration, 0x1236);
    car_performance_acceleration_set_seconds(acceleration, 0x12345670);

    car_performance_next(performance);
    car_performance_set_octaneRating(performance, 6);
    car_performance_set_accelerationCount(performance, 0);

    car_performance_next(performance);
    car_performance_set_octaneRating(performance, 7);
    acceleration = car_performance_set_accelerationCount(performance, 2);
    car_performance_acceleration_next(acceleration);
    car_performance_acceleration_set_mph(acceleration, 0x4321);
    car_performance_acceleration_set_seconds(acceleration, 0x87654321);
    car_performance_acceleration_next(acceleration);
    car_performance_acceleration_set_mph(acceleration, 0x5321);
    car_performance_acceleration_set_seconds(acceleration, 0x97654321);

    return car->location.position - car->location.offset;
}

size_t decode_car(car_codec_t* car, char *buffer, size_t len, size_t offset, size_t blklen)
{
    car_wrap_to_decode(car, buffer, len, offset, blklen);

    printf("car.code=0x%x\n", car_get_code(car));

    car_performance_codec_t* performance = car_get_performance(car);
    while (car_performance_has_next(performance))
    {
        car_performance_next(performance);
        printf("car.performance.octaneRating=0x%x\n", car_performance_get_octaneRating(performance));
        car_performance_acceleration_codec_t* acceleration = car_performance_get_acceleration(performance);
        while (car_performance_acceleration_has_next(acceleration))
        {
            car_performance_acceleration_next(acceleration);
            printf("car.performance.acceleration.mph=0x%x\n", car_performance_acceleration_get_mph(acceleration));
            printf("car.performance.acceleration.seconds=0x%x\n", car_performance_acceleration_get_seconds(acceleration));
        }
    }

    return car->location.position - car->location.offset;
}

int main(int argc, char *argv[])
{
    char buffer[512];

    message_header_t msg_hdr;
    msg_hdr.blockLength = sizeof(car_t);
    msg_hdr.template_id = car_template_car;
    msg_hdr.schema_id = 0x12;
    msg_hdr.version = 0x34;

    car_codec_t car_enc;
    car_codec_t car_dec;

    size_t enc_hdr_len = encode_hdr(&msg_hdr, buffer, sizeof(buffer), 0);
    size_t enc_msg_len = encode_car(&car_enc, buffer, sizeof(buffer), enc_hdr_len);
    printf("Encoded Lengths are %lu + %lu\n", enc_hdr_len, enc_msg_len);

    DumpHex(buffer, enc_hdr_len+enc_msg_len);
    printf("\n");

    size_t dec_hdr_len = decode_hdr(&msg_hdr, buffer, sizeof(buffer), 0);
    size_t dec_msg_len = decode_car(&car_dec, buffer, sizeof(buffer), dec_hdr_len, msg_hdr.blockLength);
    printf("Decoded Lengths are %lu + %lu\n", dec_hdr_len, dec_msg_len);

    return 0;
}
