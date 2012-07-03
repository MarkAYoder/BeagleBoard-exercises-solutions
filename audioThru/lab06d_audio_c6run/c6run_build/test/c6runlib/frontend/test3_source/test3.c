#include <stdio.h>

#define TESTNUM "3"

void test3_v( void )
{
  printf("Running Test #" TESTNUM ".\n");
}

int test3_i( void )
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 0;
}

float test3_f(void)
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 1.0f;
}

