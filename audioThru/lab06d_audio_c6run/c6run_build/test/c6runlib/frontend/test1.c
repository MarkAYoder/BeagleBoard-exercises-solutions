#include <stdio.h>

#define TESTNUM "1"

void test1_v( void )
{
  printf("Running Test #" TESTNUM ".\n");
}

int test1_i( void )
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 0;
}

float test1_f(void)
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 1.0f;
}
