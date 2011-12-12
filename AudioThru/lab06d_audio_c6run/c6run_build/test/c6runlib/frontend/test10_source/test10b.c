#include <stdio.h>

#define TESTNUM "10"

short test10_s( void )
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 1;
}

long long test10_ll( void )
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 0;
}

double test10_d(void)
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 1.0;
}
