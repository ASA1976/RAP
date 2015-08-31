// © 2015 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#ifndef FRACTIONALIZATION_ASSOCIATION
#define FRACTIONALIZATION_ASSOCIATION

namespace fractionalization {

  template <typename Natural>
  struct Fractional {
    Natural numerator, denominator;
  };
  template <typename Natural>
  struct Arithmetical {
    Fractional< Natural > (&add)(const Fractional< Natural >&, const Fractional< Natural >&);
    Fractional< Natural > (&subtract)(const Fractional< Natural >&, const Fractional< Natural >&);
    Fractional< Natural > (&multiply)(const Fractional< Natural >&, const Fractional< Natural >&);
    Fractional< Natural > (&divide)(const Fractional< Natural >&, const Fractional< Natural >&);
  };
  template <typename Natural>
  struct Relational {
    bool (&lesser)(const Fractional< Natural >&, const Fractional< Natural >&);
    bool (&greater)(const Fractional< Natural >&, const Fractional< Natural >&);
    bool (&equal)(const Fractional< Natural >&, const Fractional< Natural >&);
    bool (&not_greater)(const Fractional< Natural >&, const Fractional< Natural >&);
    bool (&not_lesser)(const Fractional< Natural >&, const Fractional< Natural >&);
    bool (&not_equal)(const Fractional< Natural >&, const Fractional< Natural >&);
  };
  template <typename Natural>
  struct Operational {
    Arithmetical< Natural > arithmetic;
    Relational< Natural > relation;
  };
  template <typename Natural>
  struct Operatory {
    const Operational< Natural > &operation;
    Fractional< Natural > fraction;
  };

  template <typename Natural>
  static inline Natural GreatestCommonDivisor(const Natural &a, const Natural &b)
  {
    // Euclidean Algorithm
    Natural dividend, divisor, remainder;
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
  template <typename Natural>
  static inline Natural LeastCommonMultiple(const Natural &a, const Natural &b)
  {
    const Natural divisor = GreatestCommonDivisor(a, b);
    if (a > b)
      return a / divisor * b;
    return b / divisor * a;
  }
  template <typename Natural>
  static inline Fractional< Natural > Reduce(const Fractional< Natural > &fraction)
  {
    Natural divisor;
    Fractional< Natural > result;
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
  template <typename Natural>
  static inline Fractional< Natural > FastAdd(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    const Fractional< Natural > result = {
      left.numerator * right.denominator + right.numerator * left.denominator,
      left.denominator * right.denominator
    };
    return result;
  }
  template <typename Natural>
  static inline Fractional< Natural > FastSubtract(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    const Fractional< Natural > result = {
      left.numerator * right.denominator - right.numerator * left.denominator,
      left.denominator * right.denominator
    };
    return result;
  }
  template <typename Natural>
  static inline Fractional< Natural > FastMultiply(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    const Fractional< Natural > result = {
      left.numerator * right.numerator,
      left.denominator * right.denominator
    };
    return result;
  }
  template <typename Natural>
  static inline Fractional< Natural > FastDivide(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    const Fractional< Natural > result = {
      left.numerator * right.denominator,
      left.denominator * right.numerator
    };
    return result;
  }
  template <typename Natural>
  static inline Fractional< Natural > ReducingAdd(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    Fractional< Natural > result;
    Natural factor;
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
        factor /=  right.denominator;
        result.numerator = left.numerator + right.numerator * factor;
        result.denominator = left.denominator;
      }
    }
    return Reduce(result);
  }
  template <typename Natural>
  static inline Fractional< Natural > ReducingSubtract(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    Fractional< Natural > result;
    Natural factor;
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
  template <typename Natural>
  static inline Fractional< Natural > ReducingMultiply(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    const Natural
      lnrd_divisor = GreatestCommonDivisor(left.numerator, right.denominator),
      ldrn_divisor = GreatestCommonDivisor(left.denominator, right.numerator);
    const Fractional< Natural > result = {
      (left.numerator / lnrd_divisor) * (right.numerator / ldrn_divisor),
      (left.denominator / ldrn_divisor) * (right.denominator / lnrd_divisor)
    };
    return result;
  }
  template <typename Natural>
  static inline Fractional< Natural > ReducingDivide(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    const Natural
      lnrn_divisor = GreatestCommonDivisor(left.numerator, right.numerator),
      ldrd_divisor = GreatestCommonDivisor(left.denominator, right.denominator);
    const Fractional< Natural > result = {
      (left.numerator / lnrn_divisor) * (right.denominator / ldrd_divisor),
      (left.denominator / ldrd_divisor) * (right.numerator / lnrn_divisor)
    };
    return result;
  }
  template <typename Natural>
  static inline bool FastLesser(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    return left.numerator * right.denominator < right.numerator * left.denominator;
  }
  template <typename Natural>
  static inline bool FastGreater(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    return left.numerator * right.denominator > right.numerator * left.denominator;
  }
  template <typename Natural>
  static inline bool FastEqual(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    return left.numerator * right.denominator == right.numerator * left.denominator;
  }
  template <typename Natural>
  static inline bool FastNotGreater(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    return left.numerator * right.denominator <= right.numerator * left.denominator;
  }
  template <typename Natural>
  static inline bool FastNotLesser(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    return left.numerator * right.denominator >= right.numerator * left.denominator;
  }
  template <typename Natural>
  static inline bool FastNotEqual(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    return left.numerator * right.denominator != right.numerator * left.denominator;
  }
  template <typename Natural>
  static inline bool ReducingLesser(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    Natural factor;
    bool result;
    if (left.denominator == right.denominator) {
      result = left.numerator < right.numerator;
    } else {
      factor = LeastCommonMultiple(left.denominator, right.denominator);
      if (left.denominator < right.denominator)
        result = left.numerator * (factor / left.denominator) < right.numerator;
      else
        result = left.numerator < right.numerator * (factor / right.denominator);
    }
    return result;
  }
  template <typename Natural>
  static inline bool ReducingGreater(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    Natural factor;
    bool result;
    if (left.denominator == right.denominator) {
      result = left.numerator > right.numerator;
    } else {
      factor = LeastCommonMultiple(left.denominator, right.denominator);
      if (left.denominator < right.denominator)
        result = left.numerator * (factor / left.denominator) > right.numerator;
      else
        result = left.numerator > right.numerator * (factor / right.denominator);
    }
    return result;
  }
  template <typename Natural>
  static inline bool ReducingEqual(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    Natural factor;
    bool result;
    if (left.denominator == right.denominator) {
      result = left.numerator == right.numerator;
    } else {
      factor = LeastCommonMultiple(left.denominator, right.denominator);
      if (left.denominator < right.denominator)
        result = left.numerator * (factor / left.denominator) == right.numerator;
      else
        result = left.numerator == right.numerator * (factor / right.denominator);
    }
    return result;
  }
  template <typename Natural>
  static inline bool ReducingNotGreater(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    Natural factor;
    bool result;
    if (left.denominator == right.denominator) {
      result = left.numerator <= right.numerator;
    } else {
      factor = LeastCommonMultiple(left.denominator, right.denominator);
      if (left.denominator < right.denominator)
        result = left.numerator * (factor / left.denominator) <= right.numerator;
      else
        result = left.numerator <= right.numerator * (factor / right.denominator);
    }
    return result;
  }
  template <typename Natural>
  static inline bool ReducingNotLesser(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    Natural factor;
    bool result;
    if (left.denominator == right.denominator) {
      result = left.numerator >= right.numerator;
    } else {
      factor = LeastCommonMultiple(left.denominator, right.denominator);
      if (left.denominator < right.denominator)
        result = left.numerator * (factor / left.denominator) >= right.numerator;
      else
        result = left.numerator >= right.numerator * (factor / right.denominator);
    }
    return result;
  }
  template <typename Natural>
  static inline bool ReducingNotEqual(const Fractional< Natural > &left, const Fractional< Natural > &right)
  {
    Natural factor;
    bool result;
    if (left.denominator == right.denominator) {
      result = left.numerator != right.numerator;
    } else {
      factor = LeastCommonMultiple(left.denominator, right.denominator);
      if (left.denominator < right.denominator)
        result = left.numerator * (factor / left.denominator) != right.numerator;
      else
        result = left.numerator != right.numerator * (factor / right.denominator);
    }
    return result;
  }
  template <typename Natural>
  static inline Operatory< Natural > operator+ (const Operatory< Natural > &left, const Operatory< Natural > &right)
  {
    const Operatory< Natural > result = {
      left.operation,
      left.operation.arithmetic.add(left.fraction, right.fraction)
    };
    return result;
  }
  template <typename Natural>
  static inline Operatory< Natural > operator- (const Operatory< Natural > &left, const Operatory< Natural > &right)
  {
    const Operatory< Natural > result = {
      left.operation,
      left.operation.arithmetic.subtract(left.fraction, right.fraction)
    };
    return result;
  }
  template <typename Natural>
  static inline Operatory< Natural > operator* (const Operatory< Natural > &left, const Operatory< Natural > &right)
  {
    const Operatory< Natural > result = {
      left.operation,
      left.operation.arithmetic.multiply(left.fraction, right.fraction)
    };
    return result;
  }
  template <typename Natural>
  static inline Operatory< Natural > operator/ (const Operatory< Natural > &left, const Operatory< Natural > &right)
  {
    const Operatory< Natural > result = {
      left.operation,
      left.operation.arithmetic.divide(left.fraction, right.fraction)
    };
    return result;
  }
  template <typename Natural>
  static inline bool operator< (const Operatory< Natural > &left, const Operatory< Natural > &right)
  {
    return left.operation.relation.lesser(left.fraction, right.fraction);
  }
  template <typename Natural>
  static inline bool operator> (const Operatory< Natural > &left, const Operatory< Natural > &right)
  {
    return left.operation.relation.greater(left.fraction, right.fraction);
  }
  template <typename Natural>
  static inline bool operator== (const Operatory< Natural > &left, const Operatory< Natural > &right)
  {
    return left.operation.relation.equal(left.fraction, right.fraction);
  }
  template <typename Natural>
  static inline bool operator<= (const Operatory< Natural > &left, const Operatory< Natural > &right)
  {
    return left.operation.relation.not_greater(left.fraction, right.fraction);
  }
  template <typename Natural>
  static inline bool operator>= (const Operatory< Natural > &left, const Operatory< Natural > &right)
  {
    return left.operation.relation.not_lesser(left.fraction, right.fraction);
  }
  template <typename Natural>
  static inline bool operator!= (const Operatory< Natural > &left, const Operatory< Natural > &right)
  {
    return left.operation.relation.not_equal(left.fraction, right.fraction);
  }

}
#define FRACTIONALIZATION_FAST_ARITHMETIC(NATURAL) \
{ \
  fractionalization::FastAdd< NATURAL >, \
  fractionalization::FastSubtract< NATURAL >, \
  fractionalization::FastMultiply< NATURAL >, \
  fractionalization::FastDivide< NATURAL > \
}
#define FRACTIONALIZATION_REDUCING_ARITHMETIC(NATURAL) \
{ \
  fractionalization::ReducingAdd< NATURAL >, \
  fractionalization::ReducingSubtract< NATURAL >, \
  fractionalization::ReducingMultiply< NATURAL >, \
  fractionalization::ReducingDivide< NATURAL > \
}
#define FRACTIONALIZATION_FAST_RELATION(NATURAL) \
{ \
  fractionalization::FastLesser< NATURAL >, \
  fractionalization::FastGreater< NATURAL >, \
  fractionalization::FastEqual< NATURAL >, \
  fractionalization::FastNotGreater< NATURAL >, \
  fractionalization::FastNotLesser< NATURAL >, \
  fractionalization::FastNotEqual< NATURAL > \
}
#define FRACTIONALIZATION_REDUCING_RELATION(NATURAL) \
{ \
  fractionalization::ReducingLesser< NATURAL >, \
  fractionalization::ReducingGreater< NATURAL >, \
  fractionalization::ReducingEqual< NATURAL >, \
  fractionalization::ReducingNotGreater< NATURAL >, \
  fractionalization::ReducingNotLesser< NATURAL >, \
  fractionalization::ReducingNotEqual< NATURAL > \
}
#define FRACTIONALIZATION_FAST_OPERATION(NATURAL) \
{ \
  FRACTIONALIZATION_FAST_ARITHMETIC(NATURAL), \
  FRACTIONALIZATION_FAST_RELATION(NATURAL) \
}
#define FRACTIONALIZATION_REDUCING_OPERATION(NATURAL) \
{ \
  FRACTIONALIZATION_REDUCING_ARITHMETIC(NATURAL), \
  FRACTIONALIZATION_REDUCING_RELATION(NATURAL) \
}
#endif
