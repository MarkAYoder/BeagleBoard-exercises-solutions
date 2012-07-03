#include <stdio.h>

#define TESTNUM "8"

void test8_v( void )
{
  printf("Running Test #" TESTNUM ".\n");
}

int test8_i( void )
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 0;
}

float test8_f(void)
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 1.0f;
}
