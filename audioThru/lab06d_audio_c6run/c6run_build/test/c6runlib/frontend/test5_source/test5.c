#include <stdio.h>

#define TESTNUM "5"

void test5_v( void )
{
  printf("Running Test #" TESTNUM ".\n");
}

int test5_i( void )
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 0;
}

float test5_f(void)
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 1.0f;
}
