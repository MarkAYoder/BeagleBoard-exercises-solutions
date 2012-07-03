#include <stdio.h>

#define TESTNUM "13"

void test13_v( void )
{
  printf("Running Test #" TESTNUM ".\n");
}

int test13_i( void )
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 0;
}

float test13_f(void)
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 1.0f;
}
