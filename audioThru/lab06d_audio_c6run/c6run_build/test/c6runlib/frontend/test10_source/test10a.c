#include <stdio.h>

#define TESTNUM "9"

void test10_v( void )
{
  printf("Running Test #" TESTNUM ".\n");
}

int test10_i( void )
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 0;
}

float test10_f(void)
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 1.0f;
}
