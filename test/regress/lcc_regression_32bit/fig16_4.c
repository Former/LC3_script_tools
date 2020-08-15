#include <stdio.h>

void NewSwap(int *firstVal, int *secondVal);

int main()
{
  int valueA = 312345;
  int valueB = 454321;

  printf("Before Swap ");
  printf("valueA = %d and valueB = %d\n", valueA, valueB);

  NewSwap(&valueA, &valueB);

  printf("After  Swap ");
  printf("valueA = %d and valueB = %d\n", valueA, valueB);
  return 0;
}

void NewSwap(int *firstVal, int *secondVal)
{
  int tempVal;          /* Holds firstVal when swapping */

  tempVal = *firstVal;
  *firstVal = *secondVal;
  *secondVal = tempVal;
}
