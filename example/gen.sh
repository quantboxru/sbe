#!/bin/bash

while getopts "fh" opt; do
   case $opt in
      f)
         FLAGS=-f
      ;;
   [\?,h])
      echo "usage: ./gen.sh [-h] [-f]"
      exit 0
      ;;
   esac
done

../gen/gen.py $FLAGS                            \
   -p car.xml                                   \
   -x ../config/SimpleBinary1-0.xsd             \
   -r ../gen/transform.py                       \
   -t ../gen/h.jinja2                           \
   -o car.h                                     \

../gen/gen.py $FLAGS                            \
   -p car.xml                                   \
   -x ../config/SimpleBinary1-0.xsd             \
   -r ../gen/transform.py                       \
   -t ../gen/h_priv.encoder.jinja2              \
   -e "{'header': 'car.h'}"                     \
   -o car_encoder_priv.h                        \

../gen/gen.py $FLAGS                            \
   -p car.xml                                   \
   -x ../config/SimpleBinary1-0.xsd             \
   -r ../gen/transform.py                       \
   -t ../gen/c.encoder.jinja2                   \
   -e "{'priv_header': 'car_encoder_priv.h'}"   \
   -o car_encoder.c                             \

../gen/gen.py $FLAGS                            \
   -p car.xml                                   \
   -x ../config/SimpleBinary1-0.xsd             \
   -r ../gen/transform.py                       \
   -t ../gen/h_priv.decoder.jinja2              \
   -e "{'header': 'proto.h'}"                   \
   -o car_decoder_priv.h                        \

../gen/gen.py $FLAGS                            \
   -p car.xml                                   \
   -x ../config/SimpleBinary1-0.xsd             \
   -r ../gen/transform.py                       \
   -t ../gen/c.decoder.jinja2                   \
   -e "{'priv_header': 'proto_decoder_priv.h'}" \
   -o car_decoder.c                             \

../gen/gen.py $FLAGS                            \
   -p car.xml                                   \
   -x ../config/SimpleBinary1-0.xsd             \
   -r ../gen/transform.py                       \
   -t ../gen/cs.jinja2                          \
   -o car.cs                                    \

../gen/gen.py $FLAGS                            \
   -p car.xml                                   \
   -x ../config/SimpleBinary1-0.xsd             \
   -r ../gen/transform.py                       \
   -t ../gen/py.jinja2                          \
   -o car.py                                    \
