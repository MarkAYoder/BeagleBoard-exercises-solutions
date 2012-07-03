#include <stdio.h>

#define TESTNUM "12"

long long test12_ll( void )
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 0;
}

double test12_d(void)
{
  printf("Running Test #" TESTNUM ".\n");
  
  return 1.0;
}
