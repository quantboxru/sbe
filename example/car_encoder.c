/**
  * @brief CAUTION: do not change this file - it is autogenerated.
  */

#include ""
#include <common/xroad_aux.h>
#include <math.h>

typedef struct
{
   uint16_t block_length;
   uint16_t template_id;
   uint16_t schema_id;
   uint16_t version;
} message_header_t;

typedef struct
{
   uint16_t block_length;
   uint16_t num_in_group;
} group_size_encoding_t;

typedef struct
{
   car_templates_t tid;
   char* data;
   size_t len;
   car_logger_cback_t cback;
   size_t var_offset;
} encoder_t;

struct car_group_encoder_s
{
   void* encoder;
   uint16_t idx;
   char* data;
};

typedef struct car_group_encoder_s car_group_encoder_t;

struct car_default_encoder_s
{
   encoder_t* base;
};


// groups

// messages

typedef struct
{
   int32_t id;
   char name[20];
} car_t;



//--------------------------------------------------------------------------------------------------------------------//
void* car_create_encoder(car_templates_t tid, char* data, size_t len, car_logger_cback_t cback)
{
   switch(tid)
   {
      case car_template_car:
      {
         if (len < sizeof(message_header_t) + 24)
         {
            if (cback)
            {
               cback(car_log_level_error, "buffer is too small");
            }
            return NULL;
         }
         car_car_encoder_t* encoder = calloc(1, sizeof(car_car_encoder_t));
         encoder->base.data = data;
         encoder->base.len = len;
         encoder->base.tid = tid;
         encoder->base.cback = cback;
         message_header_t* hdr = (message_header_t*)encoder->base.data;
         hdr->template_id = tid;
         hdr->schema_id = 1;
         hdr->version = 1;
         hdr->block_length = 24;
         return encoder;
      }
      default:
      {
         if (cback)
         {
            cback(car_log_level_error, "unknown template id");
         }
         return NULL;
      }
   }
}

//--------------------------------------------------------------------------------------------------------------------//
void car_destroy_encoder(void* encoder)
{
   free(encoder);
}

//--------------------------------------------------------------------------------------------------------------------//
int32_t car_car_get_size(car_car_encoder_t* encoder)
{
   encoder_t* e = (encoder_t*)encoder;
   message_header_t* hdr = (message_header_t*)e->data;
   return sizeof(message_header_t) + hdr->block_length + e->var_offset;
}

