#ifndef LOCATION_H
#define LOCATION_H

#include <stdlib.h>

typedef struct
{
    char* buffer;
    size_t bufferLength;
    size_t offset;
} composite_location_t;


// void composite_location_reset(composite_location_t* h, char* buffer, size_t len, size_t offset);


// char* composite_location_get_buffer(composite_location_t* h);
// size_t composite_location_get_bufferLength(composite_location_t* h);
// size_t composite_location_get_offset(composite_location_t* h);


typedef struct
{
    char* buffer;
    size_t bufferLength;
    size_t offset;
    size_t blockLength;
    size_t *positionPtr;
    size_t position;
} message_location_t;


typedef struct
{
    char* buffer;
    size_t bufferLength;
    size_t offset;
    size_t blockLength;
    size_t *positionPtr;
    size_t count;
    size_t index;
} group_location_t;


#endif
