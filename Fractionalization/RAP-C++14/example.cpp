// © 2015 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#include <stdio.h>
#include "fractionalization.hpp"

using Fractional = fractionalization::Fractional< unsigned int >;
using Operational = fractionalization::Operational< unsigned int >;
using Operatory = fractionalization::Operatory< unsigned int >;

static void DisplayFraction(const Fractional &fraction)
{
  printf("%u", fraction.numerator);
  if (fraction.denominator > 1)
    printf("/%u", fraction.denominator);
}
static void DisplayArithmetic(const Fractional &left, const char* const symbol, const Fractional &right, const Fractional &equals)
{
  DisplayFraction(left);
  printf(" %s ", symbol);
  DisplayFraction(right);
  printf(" = ");
  DisplayFraction(equals);
  puts("");
}
static void DisplayRelation(const Fractional &left, const char* const symbol, const Fractional &right, const bool result)
{
  DisplayFraction(left);
  printf(" %s ", symbol);
  DisplayFraction(right);
  printf(" = %s", result ? "true" : "false");
  puts("");
}
static void DisplayOperations(const Operational &operation)
{
  const Operatory
    x = {operation, {1, 6}},
    y = {operation, {1, 12}};
  DisplayArithmetic(x.fraction, "+", y.fraction, (x + y).fraction);
  DisplayArithmetic(x.fraction, "-", y.fraction, (x - y).fraction);
  DisplayArithmetic(x.fraction, "*", y.fraction, (x * y).fraction);
  DisplayArithmetic(x.fraction, "/", y.fraction, (x / y).fraction);
  DisplayRelation(x.fraction, "<", y.fraction, x < y);
  DisplayRelation(x.fraction, ">", y.fraction, x > y);
  DisplayRelation(x.fraction, "==", y.fraction, x == y);
  DisplayRelation(x.fraction, "<=", y.fraction, x <= y);
  DisplayRelation(x.fraction, ">=", y.fraction, x >= y);
  DisplayRelation(x.fraction, "!=", y.fraction, x != y);
}
int main()
{
  puts("Fast Fractional Operations");
  DisplayOperations(fractionalization::FastOperation< unsigned int >);
  puts("");
  puts("Reducing Fractional Operations");
  DisplayOperations(fractionalization::ReducingOperation< unsigned int >);
  return 0;
}
