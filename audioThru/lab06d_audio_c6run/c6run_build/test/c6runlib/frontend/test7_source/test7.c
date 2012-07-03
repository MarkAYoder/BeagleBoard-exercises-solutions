#include <stdio.h>

#define TESTNUM "7"

void test7_v( void )
{
  printf("Running Test #" TESTNUM ".\n");
}

int test7_i( void )
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 0;
}

float test7_f(void)
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 1.0f;
}
