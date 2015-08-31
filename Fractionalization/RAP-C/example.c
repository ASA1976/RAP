/*
   © 2015 Aaron Sami Abassi
   Licensed under the Academic Free License version 3.0
*/
#include "fractionalization.h"
#include <stdio.h>

static void DisplayFraction(const fractional fraction) {
  printf("%u", fraction.numerator);
  if (fraction.denominator > 1)
    printf("/%u", fraction.denominator);
}
static void DisplayArithmetic(const fractional left, const char *const symbol, const fractional right, const fractional equals)
{
  DisplayFraction(left);
  printf(" %s ", symbol);
  DisplayFraction(right);
  printf(" = ");
  DisplayFraction(equals);
  printf("\n");
}
static void DisplayRelation(const fractional left, const char *const symbol, const fractional right, const int result)
{
  DisplayFraction(left);
  printf(" %s ", symbol);
  DisplayFraction(right);
  printf(" = %s\n", result ? "true" : "false");
}
static void DisplayOperations(const operational *const operation)
{
  static const fractional x = {1, 6}, y = {1, 12};
  const arithmetical *const arithmetic = operation->arithmetic;
  const relational *const relation = operation->relation;
  DisplayArithmetic(x, "+", y, arithmetic->add(x, y));
  DisplayArithmetic(x, "-", y, arithmetic->subtract(x, y));
  DisplayArithmetic(x, "*", y, arithmetic->multiply(x, y));
  DisplayArithmetic(x, "/", y, arithmetic->divide(x, y));
  DisplayRelation(x, "<", y, relation->lesser(x, y));
  DisplayRelation(x, ">", y, relation->greater(x, y));
  DisplayRelation(x, "==", y, relation->equal(x, y));
  DisplayRelation(x, "<=", y, relation->not_greater(x, y));
  DisplayRelation(x, ">=", y, relation->not_lesser(x, y));
  DisplayRelation(x, "!=", y, relation->not_equal(x, y));
}
int main()
{
  printf("Fast Fractional Operations\n");
  DisplayOperations(&FastOperation);
  printf("\n");
  printf("Reducing Fractional Operations\n");
  DisplayOperations(&ReducingOperation);
  return 0;
}
