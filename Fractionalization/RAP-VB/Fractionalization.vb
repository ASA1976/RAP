' © Aaron Sami Abassi
' Licensed under the Academic Free License version 3.0
Module Fractionalization

	Public Delegate Function ArithmeticFunctional(ByRef Left As Fractional, ByRef Right As Fractional) As Fractional
	Public Delegate Function RelationFunctional(ByRef Left As Fractional, ByRef Right As Fractional) As Boolean

	Public Structure Fractional
		Dim Numerator, Denominator As UInteger
		Sub New(ByRef Numerator As UInteger, ByRef Denominator As UInteger)
			Me.Numerator = Numerator
			Me.Denominator = Denominator
		End Sub
	End Structure
	Public Structure Arithmetical
		ReadOnly Add, Subtract, Multiply, Divide As ArithmeticFunctional
		Sub New(ByRef Add As ArithmeticFunctional, ByRef Subtract As ArithmeticFunctional, ByRef Multiply As ArithmeticFunctional, ByRef Divide As ArithmeticFunctional)
			Me.Add = Add
			Me.Subtract = Subtract
			Me.Multiply = Multiply
			Me.Divide = Divide
		End Sub
	End Structure
	Public Structure Relational
		ReadOnly Lesser, Greater, Equal, NotGreater, NotLesser, NotEqual As RelationFunctional
		Sub New(ByRef Lesser As RelationFunctional, ByRef Greater As RelationFunctional, ByRef Equal As RelationFunctional, ByRef NotGreater As RelationFunctional, ByRef NotLesser As RelationFunctional, ByRef NotEqual As RelationFunctional)
			Me.Lesser = Lesser
			Me.Greater = Greater
			Me.Equal = Equal
			Me.NotGreater = NotGreater
			Me.NotLesser = NotLesser
			Me.NotEqual = NotEqual
		End Sub
	End Structure
	Public Structure Operational
		ReadOnly Arithmetic As Arithmetical
		ReadOnly Relation As Relational
		Sub New(ByRef Arithmetic As Arithmetical, ByRef Relation As Relational)
			Me.Arithmetic = Arithmetic
			Me.Relation = Relation
		End Sub
	End Structure

	Public Function GreatestCommonDivisor(A As UInteger, B As UInteger) As UInteger
		' Eclidean Algorithm
		Dim Dividend, Divisor, Remainder As UInteger
		If A > B Then
			Dividend = A
			Divisor = B
		Else
			Dividend = B
			Divisor = A
		End If
		While (Remainder = Dividend Mod Divisor) > 0
			Dividend = Divisor
			Divisor = Remainder
		End While
		Return Divisor
	End Function
	Public Function LeastCommonMultiple(A As UInteger, B As UInteger) As UInteger
		Dim Divisor As UInteger
		Divisor = GreatestCommonDivisor(A, B)
		If A > B Then
			Return A / Divisor * B
		End If
		Return B / Divisor * A
	End Function
	Public Function Reduce(ByRef Fraction As Fractional) As Fractional
		Dim Divisor As UInteger
		Dim Result As Fractional
		If Fraction.Numerator = 0 Then
			Result.Numerator = 0
			Result.Denominator = 1
		Else
			Divisor = GreatestCommonDivisor(Fraction.Numerator, Fraction.Denominator)
			Result.Numerator = Fraction.Numerator / Divisor
			Result.Denominator = Fraction.Denominator / Divisor
		End If
		Return Result
	End Function
	Public Function FastAdd(ByRef Left As Fractional, ByRef Right As Fractional) As Fractional
		Dim Result As Fractional
		Result.Numerator = Left.Numerator * Right.Denominator + Right.Numerator * Left.Denominator
		Result.Denominator = Left.Denominator * Right.Denominator
		Return Result
	End Function
	Public Function FastSubtract(ByRef Left As Fractional, ByRef Right As Fractional) As Fractional
		Dim Result As Fractional
		Result.Numerator = Left.Numerator * Right.Denominator - Right.Numerator * Left.Denominator
		Result.Denominator = Left.Denominator * Right.Denominator
		Return Result
	End Function
	Public Function FastMultiply(ByRef Left As Fractional, ByRef Right As Fractional) As Fractional
		Dim Result As Fractional
		Result.Numerator = Left.Numerator * Right.Numerator
		Result.Denominator = Left.Denominator * Right.Denominator
		Return Result
	End Function
	Public Function FastDivide(ByRef Left As Fractional, ByRef Right As Fractional) As Fractional
		Dim Result As Fractional
		Result.Numerator = Left.Numerator * Right.Denominator
		Result.Denominator = Left.Denominator * Right.Numerator
		Return Result
	End Function
	Public Function ReducingAdd(ByRef Left As Fractional, ByRef Right As Fractional) As Fractional
		Dim Factor As UInteger
		Dim Result As Fractional
		If Left.Denominator = Right.Denominator Then
			Result.Numerator = Left.Numerator + Right.Numerator
			Result.Denominator = Left.Denominator
		Else
			Factor = LeastCommonMultiple(Left.Denominator, Right.Denominator)
			If Left.Denominator < Right.Denominator Then
				Factor /= Left.Denominator
				Result.Numerator = Left.Numerator * Factor + Right.Numerator
				Result.Denominator = Right.Denominator
			Else
				Factor /= Right.Denominator
				Result.Numerator = Left.Numerator + Right.Numerator * Factor
				Result.Denominator = Left.Denominator
			End If
		End If
		Return Reduce(Result)
	End Function
	Public Function ReducingSubtract(ByRef Left As Fractional, ByRef Right As Fractional) As Fractional
		Dim Factor As UInteger
		Dim Result As Fractional
		If Left.Denominator = Right.Denominator Then
			Result.Numerator = Left.Numerator + Right.Numerator
			Result.Denominator = Left.Denominator
		Else
			Factor = LeastCommonMultiple(Left.Denominator, Right.Denominator)
			If Left.Denominator < Right.Denominator Then
				Factor /= Left.Denominator
				Result.Numerator = Left.Numerator * Factor + Right.Numerator
				Result.Denominator = Right.Denominator
			Else
				Factor /= Right.Denominator
				Result.Numerator = Left.Numerator + Right.Numerator * Factor
				Result.Denominator = Left.Denominator
			End If
		End If
		Return Reduce(Result)
	End Function
	Public Function ReducingMultiply(ByRef Left As Fractional, ByRef Right As Fractional) As Fractional
		Dim LNRDDivisor, LDRNDivisor As UInteger
		Dim Result As Fractional
		LNRDDivisor = GreatestCommonDivisor(Left.Numerator, Right.Denominator)
		LDRNDivisor = GreatestCommonDivisor(Left.Denominator, Right.Numerator)
		Result.Numerator = (Left.Numerator / LNRDDivisor) * (Right.Numerator / LDRNDivisor)
		Result.Denominator = (Left.Denominator / LDRNDivisor) * (Right.Denominator / LNRDDivisor)
		Return Result
	End Function
	Public Function ReducingDivide(ByRef Left As Fractional, ByRef Right As Fractional) As Fractional
		Dim LNRNDivisor, LDRDDivisor As UInteger
		Dim Result As Fractional
		LNRNDivisor = GreatestCommonDivisor(Left.Numerator, Right.Numerator)
		LDRDDivisor = GreatestCommonDivisor(Left.Denominator, Right.Denominator)
		Result.Numerator = (Left.Numerator / LNRNDivisor) * (Right.Denominator / LDRDDivisor)
		Result.Denominator = (Left.Denominator / LDRDDivisor) * (Right.Numerator / LNRNDivisor)
		Return Result
	End Function
	Public Function FastLesser(ByRef Left As Fractional, ByRef Right As Fractional) As Boolean
		Return Left.Numerator * Right.Denominator < Right.Numerator * Left.Denominator
	End Function
	Public Function FastGreater(ByRef Left As Fractional, ByRef Right As Fractional) As Boolean
		Return Left.Numerator * Right.Denominator > Right.Numerator * Left.Denominator
	End Function
	Public Function FastEqual(ByRef Left As Fractional, ByRef Right As Fractional) As Boolean
		Return Left.Numerator * Right.Denominator = Right.Numerator * Left.Denominator
	End Function
	Public Function FastNotGreater(ByRef Left As Fractional, ByRef Right As Fractional) As Boolean
		Return Left.Numerator * Right.Denominator <= Right.Numerator * Left.Denominator
	End Function
	Public Function FastNotLesser(ByRef Left As Fractional, ByRef Right As Fractional) As Boolean
		Return Left.Numerator * Right.Denominator >= Right.Numerator * Left.Denominator
	End Function
	Public Function FastNotEqual(ByRef Left As Fractional, ByRef Right As Fractional) As Boolean
		Return Left.Numerator * Right.Denominator <> Right.Numerator * Left.Denominator
	End Function
	Public Function ReducingLesser(ByRef Left As Fractional, ByRef Right As Fractional) As Boolean
		Dim Factor As UInteger
		Dim Result As Boolean
		If Left.Denominator = Right.Denominator Then
			Result = Left.Numerator < Right.Numerator
		Else
			Factor = LeastCommonMultiple(Left.Denominator, Right.Denominator)
			If Left.Denominator < Right.Denominator Then
				Factor /= Left.Denominator
				Result = Left.Numerator * Factor < Right.Numerator
			Else
				Factor /= Right.Denominator
				Result = Left.Numerator < Right.Numerator * Factor
			End If
		End If
		Return Result
	End Function
	Public Function ReducingGreater(ByRef Left As Fractional, ByRef Right As Fractional) As Boolean
		Dim Factor As UInteger
		Dim Result As Boolean
		If Left.Denominator = Right.Denominator Then
			Result = Left.Numerator > Right.Numerator
		Else
			Factor = LeastCommonMultiple(Left.Denominator, Right.Denominator)
			If Left.Denominator < Right.Denominator Then
				Factor /= Left.Denominator
				Result = Left.Numerator * Factor > Right.Numerator
			Else
				Factor /= Right.Denominator
				Result = Left.Numerator > Right.Numerator * Factor
			End If
		End If
		Return Result
	End Function
	Public Function ReducingEqual(ByRef Left As Fractional, ByRef Right As Fractional) As Boolean
		Dim Factor As UInteger
		Dim Result As Boolean
		If Left.Denominator = Right.Denominator Then
			Result = Left.Numerator = Right.Numerator
		Else
			Factor = LeastCommonMultiple(Left.Denominator, Right.Denominator)
			If Left.Denominator < Right.Denominator Then
				Factor /= Left.Denominator
				Result = Left.Numerator * Factor = Right.Numerator
			Else
				Factor /= Right.Denominator
				Result = Left.Numerator = Right.Numerator * Factor
			End If
		End If
		Return Result
	End Function
	Public Function ReducingNotGreater(ByRef Left As Fractional, ByRef Right As Fractional) As Boolean
		Dim Factor As UInteger
		Dim Result As Boolean
		If Left.Denominator = Right.Denominator Then
			Result = Left.Numerator <= Right.Numerator
		Else
			Factor = LeastCommonMultiple(Left.Denominator, Right.Denominator)
			If Left.Denominator < Right.Denominator Then
				Factor /= Left.Denominator
				Result = Left.Numerator * Factor <= Right.Numerator
			Else
				Factor /= Right.Denominator
				Result = Left.Numerator <= Right.Numerator * Factor
			End If
		End If
		Return Result
	End Function
	Public Function ReducingNotLesser(ByRef Left As Fractional, ByRef Right As Fractional) As Boolean
		Dim Factor As UInteger
		Dim Result As Boolean
		If Left.Denominator = Right.Denominator Then
			Result = Left.Numerator >= Right.Numerator
		Else
			Factor = LeastCommonMultiple(Left.Denominator, Right.Denominator)
			If Left.Denominator < Right.Denominator Then
				Factor /= Left.Denominator
				Result = Left.Numerator * Factor >= Right.Numerator
			Else
				Factor /= Right.Denominator
				Result = Left.Numerator >= Right.Numerator * Factor
			End If
		End If
		Return Result
	End Function
	Public Function ReducingNotEqual(ByRef Left As Fractional, ByRef Right As Fractional) As Boolean
		Dim Factor As UInteger
		Dim Result As Boolean
		If Left.Denominator = Right.Denominator Then
			Result = Left.Numerator <> Right.Numerator
		Else
			Factor = LeastCommonMultiple(Left.Denominator, Right.Denominator)
			If Left.Denominator < Right.Denominator Then
				Factor /= Left.Denominator
				Result = Left.Numerator * Factor <> Right.Numerator
			Else
				Factor /= Right.Denominator
				Result = Left.Numerator <> Right.Numerator * Factor
			End If
		End If
		Return Result
	End Function

	Public ReadOnly FastArithmetic As New Arithmetical(AddressOf FastAdd, AddressOf FastSubtract, AddressOf FastMultiply, AddressOf FastDivide)
	Public ReadOnly ReducingArithmetic As New Arithmetical(AddressOf ReducingAdd, AddressOf ReducingSubtract, AddressOf ReducingMultiply, AddressOf ReducingDivide)
	Public ReadOnly FastRelation As New Relational(AddressOf FastLesser, AddressOf FastGreater, AddressOf FastEqual, AddressOf FastNotGreater, AddressOf FastNotLesser, AddressOf FastNotEqual)
	Public ReadOnly ReducingRelation As New Relational(AddressOf ReducingLesser, AddressOf ReducingGreater, AddressOf ReducingEqual, AddressOf ReducingNotGreater, AddressOf ReducingNotLesser, AddressOf ReducingNotEqual)
	Public ReadOnly FastOperation As New Operational(FastArithmetic, FastRelation)
	Public ReadOnly ReducingOperation As New Operational(ReducingArithmetic, ReducingRelation)

End Module

Module Example

	Sub DisplayFraction(ByRef Fraction As Fractional)
		Console.Write(Fraction.Numerator)
		If (Fraction.Denominator > 1) Then
			Console.Write("/" & Fraction.Denominator)
		End If
	End Sub
	Sub DisplayArithmetic(ByRef Left As Fractional, Symbol As String, ByRef Right As Fractional, ByRef Equals As Fractional)
		DisplayFraction(Left)
		Console.Write(" " & Symbol & " ")
		DisplayFraction(Right)
		Console.Write(" = ")
		DisplayFraction(Equals)
		Console.WriteLine()
	End Sub
	Sub DisplayRelation(ByRef Left As Fractional, Symbol As String, ByRef Right As Fractional, ByRef Result As Boolean)
		DisplayFraction(Left)
		Console.Write(" " & Symbol & " ")
		DisplayFraction(Right)
		Console.WriteLine(" = " & Result)
	End Sub
	Sub DisplayOperations(ByRef Operation As Operational)
		Static X As New Fractional(1, 6)
		Static Y As New Fractional(1, 12)
		Dim Arithmetic As Arithmetical = Operation.Arithmetic
		Dim Relation As Relational = Operation.Relation
		DisplayArithmetic(X, "+", Y, Arithmetic.Add(X, Y))
		DisplayArithmetic(X, "-", Y, Arithmetic.Subtract(X, Y))
		DisplayArithmetic(X, "*", Y, Arithmetic.Multiply(X, Y))
		DisplayArithmetic(X, "/", Y, Arithmetic.Divide(X, Y))
		DisplayRelation(X, "<", Y, Relation.Lesser(X, Y))
		DisplayRelation(X, ">", Y, Relation.Greater(X, Y))
		DisplayRelation(X, "=", Y, Relation.Equal(X, Y))
		DisplayRelation(X, "<=", Y, Relation.NotGreater(X, Y))
		DisplayRelation(X, ">=", Y, Relation.NotLesser(X, Y))
		DisplayRelation(X, "<>", Y, Relation.NotEqual(X, Y))
	End Sub
	Sub Main()
		Console.WriteLine("Fast Fractional Operations")
		DisplayOperations(FastOperation)
		Console.WriteLine()
		Console.WriteLine("Reducing Fractional Operations")
		DisplayOperations(ReducingOperation)
	End Sub

End Module
