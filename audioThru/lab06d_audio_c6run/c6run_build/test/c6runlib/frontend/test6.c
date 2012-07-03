#include <stdio.h>

#define TESTNUM "6"

void test6_v( void )
{
  printf("Running Test #" TESTNUM ".\n");
}

int test6_i( void )
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 0;
}

float test6_f(void)
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 1.0f;
}
