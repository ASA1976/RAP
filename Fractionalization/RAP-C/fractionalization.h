/*
   © 2015 Aaron Sami Abassi
   Licensed under the Academic Free License version 3.0
*/
#ifndef FRACTIONALIZATION_ASSOCIATION
#define FRACTIONALIZATION_ASSOCIATION

typedef int boolean;
typedef unsigned int natural;
typedef struct fractional_s {
  natural numerator, denominator;
} fractional;
typedef fractional (*arithmetic_function_situational)(fractional, fractional);
typedef boolean (*relation_function_situational)(fractional, fractional);
typedef struct arithmetical_s {
  arithmetic_function_situational
    add,
    subtract,
    multiply,
    divide;
} arithmetical;
typedef struct relational_s {
  relation_function_situational
    lesser,
    greater,
    equal,
    not_greater,
    not_lesser,
    not_equal;
} relational;
typedef struct operational_s {
  const arithmetical *arithmetic;
  const relational *relation;
} operational;

static natural GreatestCommonDivisor(const natural a, const natural b) {
  /* Euclidean Algorithm */
  natural dividend, divisor, remainder;
  if (a > b) {
    dividend = a;
    divisor = b;
  } else {
    dividend = b;
    divisor = a;
  }
  while ((remainder = dividend % divisor) > 0) {
    dividend = divisor;
    divisor = remainder;
  }
  return divisor;
}
static natural LeastCommonMultiple(const natural a, const natural b) {
  const natural divisor = GreatestCommonDivisor(a, b);
  if (a > b)
    return a / divisor * b;
  return b / divisor * a;
}
static fractional Reduce(const fractional fraction)
{
  natural divisor;
  fractional result;
  if (fraction.numerator == 0) {
    result.numerator = 0;
    result.denominator = 1;
  } else {
    divisor = GreatestCommonDivisor(fraction.numerator, fraction.denominator);
    result.numerator = fraction.numerator / divisor;
    result.denominator = fraction.denominator / divisor;
  }
  return result;
}
static fractional FastAdd(const fractional left, const fractional right)
{
  fractional result;
  result.numerator = left.numerator * right.denominator + right.numerator * left.denominator;
  result.denominator = left.denominator * right.denominator;
  return result;
}
static fractional FastSubtract(const fractional left, const fractional right)
{
  fractional result;
  result.numerator = left.numerator * right.denominator - right.numerator * left.denominator;
  result.denominator = left.denominator * right.denominator;
  return result;
}
static fractional FastMultiply(const fractional left, const fractional right)
{
  fractional result;
  result.numerator = left.numerator * right.numerator;
  result.denominator = left.denominator * right.denominator;
  return result;
}
static fractional FastDivide(const fractional left, const fractional right)
{
  fractional result;
  result.numerator = left.numerator * right.denominator;
  result.denominator = left.denominator * right.numerator;
  return result;
}
static fractional ReducingAdd(const fractional left, const fractional right)
{
  natural factor;
  fractional result;
  if (left.denominator == right.denominator) {
    result.numerator = left.numerator + right.numerator;
    result.denominator = left.denominator;
  } else {
    factor = LeastCommonMultiple(left.denominator, right.denominator);
    if (left.denominator < right.denominator) {
      factor /= left.denominator;
      result.numerator = left.numerator * factor + right.numerator;
      result.denominator = right.denominator;
    } else {
      factor /= right.denominator;
      result.numerator = left.numerator + right.numerator * factor;
      result.denominator = left.denominator;
    }
  }
  return Reduce(result);
}
static fractional ReducingSubtract(const fractional left, const fractional right)
{
  natural factor;
  fractional result;
  if (left.denominator == right.denominator) {
    result.numerator = left.numerator - right.numerator;
    result.denominator = left.denominator;
  } else {
    factor = LeastCommonMultiple(left.denominator, right.denominator);
    if (left.denominator < right.denominator) {
      factor /= left.denominator;
      result.numerator = left.numerator * factor - right.numerator;
      result.denominator = right.denominator;
    } else {
      factor /= right.denominator;
      result.numerator = left.numerator - right.numerator * factor;
      result.denominator = left.denominator;
    }
  }
  return Reduce(result);
}
static fractional ReducingMultiply(const fractional left, const fractional right)
{
  const natural
    lnrd_divisor = GreatestCommonDivisor(left.numerator, right.denominator),
    ldrn_divisor = GreatestCommonDivisor(left.denominator, right.numerator);
  fractional result;
  result.numerator = (left.numerator / lnrd_divisor) * (right.numerator / ldrn_divisor);
  result.denominator = (left.denominator / ldrn_divisor) * (right.denominator / lnrd_divisor);
  return result;
}
static fractional ReducingDivide(const fractional left, const fractional right)
{
  const natural
    lnrn_divisor = GreatestCommonDivisor(left.numerator, right.numerator),
    ldrd_divisor = GreatestCommonDivisor(left.denominator, right.denominator);
  fractional result;
  result.numerator = (left.numerator / lnrn_divisor) * (right.denominator / ldrd_divisor);
  result.denominator = (left.denominator / ldrd_divisor) * (right.numerator / lnrn_divisor);
  return result;
}
static boolean FastLesser(const fractional left, const fractional right)
{
  return left.numerator * right.denominator < right.numerator * left.denominator;
}
static boolean FastGreater(const fractional left, const fractional right)
{
  return left.numerator * right.denominator > right.numerator * left.denominator;
}
static boolean FastEqual(const fractional left, const fractional right)
{
  return left.numerator * right.denominator == right.numerator * left.denominator;
}
static boolean FastLesserEqual(const fractional left, const fractional right)
{
  return left.numerator * right.denominator <= right.numerator * left.denominator;
}
static boolean FastGreaterEqual(const fractional left, const fractional right)
{
  return left.numerator * right.denominator >= right.numerator * left.denominator;
}
static boolean FastNotEqual(const fractional left, const fractional right)
{
  return left.numerator * right.denominator != right.numerator * left.denominator;
}
static boolean ReducingLesser(const fractional left, const fractional right)
{
  natural factor;
  boolean result;
  if (left.denominator == right.denominator) {
    result = left.numerator < right.numerator;
  } else {
    factor = LeastCommonMultiple(left.denominator, right.denominator);
    if (left.denominator < right.denominator) {
      factor /= left.denominator;
      result = left.numerator * factor < right.numerator;
    } else {
      factor /= right.denominator;
      result = left.numerator < right.numerator * factor;
    }
  }
  return result;
}
static boolean ReducingGreater(const fractional left, const fractional right)
{
  natural factor;
  boolean result;
  if (left.denominator == right.denominator) {
    result = left.numerator > right.numerator;
  } else {
    factor = LeastCommonMultiple(left.denominator, right.denominator);
    if (left.denominator < right.denominator) {
      factor /= left.denominator;
      result = left.numerator * factor > right.numerator;
    } else {
      factor /= right.denominator;
      result = left.numerator > right.numerator * factor;
    }
  }
  return result;
}
static boolean ReducingEqual(const fractional left, const fractional right)
{
  natural factor;
  boolean result;
  if (left.denominator == right.denominator) {
    result = left.numerator == right.numerator;
  } else {
    factor = LeastCommonMultiple(left.denominator, right.denominator);
    if (left.denominator < right.denominator) {
      factor /= left.denominator;
      result = left.numerator * factor == right.numerator;
    } else {
      factor /= right.denominator;
      result = left.numerator == right.numerator * factor;
    }
  }
  return result;
}
static boolean ReducingNotGreater(const fractional left, const fractional right)
{
  natural factor;
  boolean result;
  if (left.denominator == right.denominator) {
    result = left.numerator <= right.numerator;
  } else {
    factor = LeastCommonMultiple(left.denominator, right.denominator);
    if (left.denominator < right.denominator) {
      factor /= left.denominator;
      result = left.numerator * factor <= right.numerator;
    } else {
      factor /= right.denominator;
      result = left.numerator <= right.numerator * factor;
    }
  }
  return result;
}
static boolean ReducingNotLesser(const fractional left, const fractional right)
{
  natural factor;
  boolean result;
  if (left.denominator == right.denominator) {
    result = left.numerator >= right.numerator;
  } else {
    factor = LeastCommonMultiple(left.denominator, right.denominator);
    if (left.denominator < right.denominator) {
      factor /= left.denominator;
      result = left.numerator * factor >= right.numerator;
    } else {
      factor /= right.denominator;
      result = left.numerator >= right.numerator * factor;
    }
  }
  return result;
}
static boolean ReducingNotEqual(const fractional left, const fractional right)
{
  natural factor;
  boolean result;
  if (left.denominator == right.denominator) {
    result = left.numerator != right.numerator;
  } else {
    factor = LeastCommonMultiple(left.denominator, right.denominator);
    if (left.denominator < right.denominator) {
      factor /= left.denominator;
      result = left.numerator * factor != right.numerator;
    } else {
      factor /= right.denominator;
      result = left.numerator != right.numerator * factor;
    }
  }
  return result;
}

static const arithmetical
  FastArithmetic = {
    FastAdd,
    FastSubtract,
    FastMultiply,
    FastDivide
  },
  ReducingArithmetic = {
    ReducingAdd,
    ReducingSubtract,
    ReducingMultiply,
    ReducingDivide
  };
static const relational
  FastRelation = {
    FastLesser,
    FastGreater,
    FastEqual,
    FastLesserEqual,
    FastGreaterEqual,
    FastNotEqual
  },
  ReducingRelation = {
    ReducingLesser,
    ReducingGreater,
    ReducingEqual,
    ReducingNotGreater,
    ReducingNotLesser,
    ReducingNotEqual
  };
static const operational
  FastOperation = {
    &FastArithmetic,
    &FastRelation
  },
  ReducingOperation = {
    &ReducingArithmetic,
    &ReducingRelation
  };
#endif
