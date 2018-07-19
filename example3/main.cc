/**
 * @file   main.cc
 * @author Dmitry S. Melnikov, dmitryme@gmail.com
 */

#include <gtest/gtest.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[])
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
