#include <stdio.h>

#define TESTNUM "12"

void test12_v( void )
{
  printf("Running Test #" TESTNUM ".\n");
}

int test12_i( void )
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 0;
}

float test12_f(void)
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 1.0f;
}
