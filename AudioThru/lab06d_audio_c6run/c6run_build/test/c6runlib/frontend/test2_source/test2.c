#include <stdio.h>

#define TESTNUM "2"

void test2_v( void )
{
  printf("Running Test #" TESTNUM ".\n");
}

int test2_i( void )
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 0;
}

float test2_f(void)
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 1.0f;
}

