# © 2015 Aaron Sami Abassi
# Licensed under the Academic Free License version 3.0
namespace eval ::fractionalization {
  set Functional {LeftFraction RightFraction}
  proc GreatestCommonDivisor {UnsignedIntegerA UnsignedIntegerB} {
    # Euclidean Algorithm
    if {$UnsignedIntegerA >= $UnsignedIntegerB} {
      set Dividend $UnsignedIntegerA
      set Divisor $UnsignedIntegerB
    } else {
      set Dividend $UnsignedIntegerB
      set Divisor $UnsignedIntegerA
    }
    while {[set Remainder [expr $Dividend % $Divisor]] > 0} {
      set Dividend $Divisor
      set Divisor $Remainder
    }
    return $Divisor
  }
  proc LeastCommonMultiple {UnsignedIntegerA UnsignedIntegerB} {
    set Divisor [GreatestCommonDivisor $UnsignedIntegerA $UnsignedIntegerB]
    if {$UnsignedIntegerA > $UnsignedIntegerB} {
      return [expr $UnsignedIntegerA / $Divisor * $UnsignedIntegerB]
    }
    return [expr $UnsignedIntegerB / $Divisor * $UnsignedIntegerA]
  }
  proc Reduce {FractionValue} {
    array set Fraction $FractionValue
    if {$Fraction(Numerator) == 0} {
      set Result(Numerator) 0
      set Result(Denominator) 1
    } else {
      set Divisor [GreatestCommonDivisor $Fraction(Numerator) $Fraction(Denominator)]
      set Result(Numerator) [expr $Fraction(Numerator) / $Divisor]
      set Result(Denominator) [expr $Fraction(Denominator) / $Divisor] 
    }
    return [array get Result]
  }
  proc FastAdd $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    set Result(Numerator) [expr $Left(Numerator) * $Right(Denominator) + $Right(Numerator) * $Left(Denominator)]
    set Result(Denominator) [expr $Left(Denominator) * $Right(Denominator)]
    return [array get Result]
  }
  proc FastSubtract $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    set Result(Numerator) [expr $Left(Numerator) * $Right(Denominator) - $Right(Numerator) * $Left(Denominator)]
    set Result(Denominator) [expr $Left(Denominator) * $Right(Denominator)]
    return [array get Result]
  }
  proc FastMultiply $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    set Result(Numerator) [expr $Left(Numerator) * $Right(Numerator)]
    set Result(Denominator) [expr $Left(Denominator) * $Right(Denominator)]
    return [array get Result]
  }
  proc FastDivide $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    set Result(Numerator) [expr $Left(Numerator) * $Right(Denominator)]
    set Result(Denominator) [expr $Left(Denominator) * $Right(Numerator)]
    return [array get Result]
  }
  proc ReducingAdd $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    if {$Left(Denominator) == $Right(Denominator)} {
      set Result(Numerator) [expr $Left(Numerator) + $Right(Numerator)]
      set Result(Denominator) $Left(Denominator)
    } else {
      set Factor [LeastCommonMultiple $Left(Denominator) $Right(Denominator)]
      if {$Left(Denominator) < $Right(Denominator)} {
        set Factor [expr $Factor / $Left(Denominator)]
        set Result(Numerator) [expr $Left(Numerator) * $Factor + $Right(Numerator)]
        set Result(Denominator) $Right(Denominator)
      } else {
        set Factor [expr $Factor / $Right(Denominator)]
        set Result(Numerator) [expr $Left(Numerator) + $Right(Numerator) * $Factor]
        set Result(Denominator) [expr $Left(Denominator)]
      }
    }
    return [Reduce [array get Result]]
  }
  proc ReducingSubtract $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    if {$Left(Denominator) == $Right(Denominator)} {
      set Result(Numerator) [expr $Left(Numerator) - $Right(Numerator)]
      set Result(Denominator) $Left(Denominator)
    } else {
      set Factor [LeastCommonMultiple $Left(Denominator) $Right(Denominator)]
      if {$Left(Denominator) < $Right(Denominator)} {
        set Factor [expr $Factor / $Left(Denominator)]
        set Result(Numerator) [expr $Left(Numerator) * $Factor - $Right(Numerator)]
        set Result(Denominator) $Right(Denominator)
      } else {
        set Factor [expr $Factor / $Right(Denominator)]
        set Result(Numerator) [expr $Left(Numerator) - $Right(Numerator) * $Factor]
        set Result(Denominator) [expr $Left(Denominator)]
      }
    }
    return [Reduce [array get Result]]
  }
  proc ReducingMultiply $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    set LNRDDivisor [GreatestCommonDivisor $Left(Numerator) $Right(Denominator)]
    set LDRNDivisor [GreatestCommonDivisor $Right(Numerator) $Left(Denominator)]
    set Result(Numerator) [expr ($Left(Numerator) / $LNRDDivisor) * ($Right(Numerator) / $LDRNDivisor)]
    set Result(Denominator) [expr ($Left(Denominator) / $LDRNDivisor) * ($Right(Denominator) / $LNRDDivisor)]
    return [array get Result]
  }
  proc ReducingDivide $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    set LNRNDivisor [GreatestCommonDivisor $Left(Numerator) $Right(Numerator)]
    set LDRDDivisor [GreatestCommonDivisor $Left(Denominator) $Right(Denominator)]
    set Result(Numerator) [expr ($Left(Numerator) / $LNRNDivisor) * ($Right(Denominator) / $LDRDDivisor)]
    set Result(Denominator) [expr ($Left(Denominator) / $LDRDDivisor) * ($Right(Numerator) / $LNRNDivisor)]
    return [array get Result]
  }
  proc FastLesser $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    return [expr $Left(Numerator) * $Right(Denominator)< $Right(Numerator) * $Left(Denominator)]
  }
  proc FastGreater $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    return [expr $Left(Numerator) * $Right(Denominator) > $Right(Numerator) * $Left(Denominator)]
  }
  proc FastEqual $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    return [expr $Left(Numerator) * $Right(Denominator) == $Right(Numerator) * $Left(Denominator)]
  }
  proc FastNotGreater $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    return [expr $Left(Numerator) * $Right(Denominator) <= $Right(Numerator) * $Left(Denominator)]
  }
  proc FastNotLesser $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    return [expr $Left(Numerator) * $Right(Denominator) >= $Right(Numerator) * $Left(Denominator)]
  }
  proc FastNotEqual $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    return [expr $Left(Numerator) * $Right(Denominator) != $Right(Numerator) * $Left(Denominator)]
  }
  proc ReducingLesser $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    if {$Left(Denominator) == $Right(Denominator)} {
      set Result [expr $Left(Numerator) < $Right(Numerator)]
    } else {
      set Factor [LeastCommonMultiple $Left(Denominator) $Right(Denominator)]
      if {$Left(Denominator) < $Right(Denominator)} {
        set Factor [expr $Factor / $Left(Denominator)]
        set Result [expr $Left(Numerator) * $Factor < $Right(Numerator)]
      } else {
        set Factor [expr $Factor / $Right(Denominator)]
        set Result [expr $Left(Numerator) < $Right(Numerator) * $Factor]
      }
    }
    return $Result
  }
  proc ReducingGreater $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    if {$Left(Denominator) == $Right(Denominator)} {
      set Result [expr $Left(Numerator) > $Right(Numerator)]
    } else {
      set Factor [LeastCommonMultiple $Left(Denominator) $Right(Denominator)]
      if {$Left(Denominator) < $Right(Denominator)} {
        set Factor [expr $Factor / $Left(Denominator)]
        set Result [expr $Left(Numerator) * $Factor > $Right(Numerator)]
      } else {
        set Factor [expr $Factor / $Right(Denominator)]
        set Result [expr $Left(Numerator) > $Right(Numerator) * $Factor]
      }
    }
    return $Result
  }
  proc ReducingEqual $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    if {$Left(Denominator) == $Right(Denominator)} {
      set Result [expr $Left(Numerator) == $Right(Numerator)]
    } else {
      set Factor [LeastCommonMultiple $Left(Denominator) $Right(Denominator)]
      if {$Left(Denominator) < $Right(Denominator)} {
        set Factor [expr $Factor / $Left(Denominator)]
        set Result [expr $Left(Numerator) * $Factor == $Right(Numerator)]
      } else {
        set Factor [expr $Factor / $Right(Denominator)]
        set Result [expr $Left(Numerator) == $Right(Numerator) * $Factor]
      }
    }
    return $Result
  }
  proc ReducingNotGreater $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    if {$Left(Denominator) == $Right(Denominator)} {
      set Result [expr $Left(Numerator) <= $Right(Numerator)]
    } else {
      set Factor [LeastCommonMultiple $Left(Denominator) $Right(Denominator)]
      if {$Left(Denominator) < $Right(Denominator)} {
        set Factor [expr $Factor / $Left(Denominator)]
        set Result [expr $Left(Numerator) * $Factor <= $Right(Numerator)]
      } else {
        set Factor [expr $Factor / $Right(Denominator)]
        set Result [expr $Left(Numerator) <= $Right(Numerator) * $Factor]
      }
    }
    return $Result
  }
  proc ReducingNotLesser $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    if {$Left(Denominator) == $Right(Denominator)} {
      set Result [expr $Left(Numerator) >= $Right(Numerator)]
    } else {
      set Factor [LeastCommonMultiple $Left(Denominator) $Right(Denominator)]
      if {$Left(Denominator) < $Right(Denominator)} {
        set Factor [expr $Factor / $Left(Denominator)]
        set Result [expr $Left(Numerator) * $Factor >= $Right(Numerator)]
      } else {
        set Factor [expr $Factor / $Right(Denominator)]
        set Result [expr $Left(Numerator) >= $Right(Numerator) * $Factor]
      }
    }
    return $Result
  }
  proc ReducingNotEqual $Functional {
    array set Left $LeftFraction
    array set Right $RightFraction
    if {$Left(Denominator) == $Right(Denominator)} {
      set Result [expr $Left(Numerator) != $Right(Numerator)]
    } else {
      set Factor [LeastCommonMultiple $Left(Denominator) $Right(Denominator)]
      if {$Left(Denominator) < $Right(Denominator)} {
        set Factor [expr $Factor / $Left(Denominator)]
        set Result [expr $Left(Numerator) * $Factor != $Right(Numerator)]
      } else {
        set Factor [expr $Factor / $Right(Denominator)]
        set Result [expr $Left(Numerator) != $Right(Numerator) * $Factor]
      }
    }
    return $Result
  }
  array set FastArithmetic {
    + ::fractionalization::FastAdd
    - ::fractionalization::FastSubtract
    * ::fractionalization::FastMultiply
    / ::fractionalization::FastDivide
  }
  array set ReducingArithmetic {
    + ::fractionalization::ReducingAdd
    - ::fractionalization::ReducingSubtract
    * ::fractionalization::ReducingMultiply
    / ::fractionalization::ReducingDivide
  }
  array set FastRelation {
    <  ::fractionalization::FastLesser
    >  ::fractionalization::FastGreater
    == ::fractionalization::FastEqual
    <= ::fractionalization::FastNotGreater
    >= ::fractionalization::FastNotLesser
    != ::fractionalization::FastNotEqual
  }
  array set ReducingRelation {
    <  ::fractionalization::ReducingLesser
    >  ::fractionalization::ReducingGreater
    == ::fractionalization::ReducingEqual
    <= ::fractionalization::ReducingNotGreater
    >= ::fractionalization::ReducingNotLesser
    != ::fractionalization::ReducingNotEqual
  }
  set FastOperation(Arithmetic) [array get FastArithmetic]
  set FastOperation(Relation) [array get FastRelation]
  set ReducingOperation(Arithmetic) [array get ReducingArithmetic]
  set ReducingOperation(Relation) [array get ReducingRelation]
}
proc DisplayFraction {FractionValue} {
  array set Fraction $FractionValue
  puts -nonewline [format {%u} $Fraction(Numerator)]
  if {$Fraction(Denominator) > 1} {
    puts -nonewline [format {/%u} $Fraction(Denominator)]
  }
}
proc DisplayFractionalRelation {Left Symbol Right Result} {
  DisplayFraction $Left
  puts -nonewline [format { %s } $Symbol]
  DisplayFraction $Right
  puts -nonewline { = }
  if {$Result} {
    puts true
  } else {
    puts false
  }
}
proc DisplayFractionalArithmetic {Left Symbol Right Equals} {
  DisplayFraction $Left
  puts -nonewline [format { %s } $Symbol]
  DisplayFraction $Right
  puts -nonewline { = }
  DisplayFraction $Equals
  puts {}
}
proc DisplayFractionalOperations {OperationValue} {
  array set Operation $OperationValue
  array set Arithmetic $Operation(Arithmetic)
  array set Relation $Operation(Relation)
  set X {Numerator 1 Denominator 6}
  set Y {Numerator 1 Denominator 12}
  DisplayFractionalArithmetic $X + $Y [$Arithmetic(+) $X $Y]
  DisplayFractionalArithmetic $X - $Y [$Arithmetic(-) $X $Y]
  DisplayFractionalArithmetic $X * $Y [$Arithmetic(*) $X $Y]
  DisplayFractionalArithmetic $X / $Y [$Arithmetic(/) $X $Y]
  DisplayFractionalRelation $X < $Y [$Relation(<) $X $Y]
  DisplayFractionalRelation $X > $Y [$Relation(>) $X $Y]
  DisplayFractionalRelation $X == $Y [$Relation(==) $X $Y]
  DisplayFractionalRelation $X <= $Y [$Relation(<=) $X $Y]
  DisplayFractionalRelation $X >= $Y [$Relation(>=) $X $Y]
  DisplayFractionalRelation $X != $Y [$Relation(!=) $X $Y]
}
set FastOperation [array get ::fractionalization::FastOperation]
set ReducingOperation [array get ::fractionalization::ReducingOperation] 
puts {Fast Fractional Operations}
DisplayFractionalOperations $FastOperation
puts {}
puts {Reducing Fractional Operations}
DisplayFractionalOperations $ReducingOperation
exit 0

