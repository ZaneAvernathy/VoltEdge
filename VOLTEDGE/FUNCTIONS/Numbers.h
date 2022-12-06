
GUARD_VOLTEDGE_FUNCTIONS_NUMBERS :?= false
.if (!GUARD_VOLTEDGE_FUNCTIONS_NUMBERS)
  GUARD_VOLTEDGE_FUNCTIONS_NUMBERS := true

  VoltEdge_Functions_Numbers_Created = 0.23
  VoltEdge_Functions_Numbers_Updated = 0.23

  ; These functions perform operations on
  ; numeric values.

  num .namespace

    ; Created: 0.19
    ; Updated: 0.19
    ; clamp(Value, Minimum, Maximum)

      ; Inputs:
        ; Value: Value to clamp
        ; Minimum: Minimum value that will be used if Value
          ; is smaller.
        ; Maximum: Maximum value that will be used if Value
          ; is larger.

      ; Outputs:
        ; Value in [Minimum, Maximum]

      ; Clamp a value such that it falls between two other values.

      clamp .sfunction Value, Minimum, Maximum, (Value >? Minimum) <? Maximum

    ; Created: 0.19
    ; Updated: 0.19
    ; divmod(Dividend, Divisor)

      ; Inputs:
        ; Dividend: Value to be divided
        ; Divisor: Value to divide by

      ; Outputs:
        ; Quotient: Result of division
        ; Remainder: Remainder after division

      ; Divides a value by another, giving the quotient and
      ; remainder as a 2-tuple.

      divmod .sfunction A, B, (A / B, A % B)

    ; Created: 0.19
    ; Updated: 0.19
    ; max(Value1, Value2)

      ; Inputs:
        ; Values: numbers to compare

      ; Outputs:
        ; Largest number

      ; Returns the largest of two numbers.

      max .sfunction A, B, (A >? B)

    ; Created: 0.19
    ; Updated: 0.19
    ; min(Value1, Value2)

      ; Inputs:
        ; Values: numbers to compare

      ; Outputs:
        ; Smallest number

      ; Returns the smallest of two numbers.

      min .sfunction A, B, (A <? B)

    ; Created: 0.22
    ; Updated: 0.22
    ; logn(Value, Base)

      ; Inputs:
        ; Value: value to take the logarithm of.
        ; Base: base to give the logarithm of.

      ; Outputs:
        ; logarithm of value to the base.

      ; Gets the logarithm of a value to some base.

      logn .sfunction Value, Base, (log(Value) / log(Base))

    ; Created: 0.22
    ; Updated: 0.22
    ; bit_length(Value)

      ; Inputs:
        ; Value: value to count

      ; Outputs:
        ; number of bits

      ; Counts the number of bits needed to represent an integer
      ; in binary.

      bit_length .function Value

          Return := 0

        .if (Value != 0)

          Return := 1 + int(logn(abs(Value), 2))

        .endif

      .endfunction Return

    ; Created: 0.22
    ; Updated: 0.22
    ; bit_count(Value)

      ; Inputs:
        ; Value: value to count

      ; Outputs:
        ; number of bits set

      ; Gives the number of ones in the binary representation
      ; of the absolute value of an integer.

      bit_count .sfunction Value, zstr.count(str(bits(abs(Value))), "1")

    ; Created: 0.22
    ; Updated: 0.22
    ; hex(Value, Width=?)

      ; Inputs:
        ; Value: number to format as a string
        ; Width: number of bytes to express value as

      ; Outputs:
        ; String representing the number

      ; Gives a string representation of a number in
      ; hex. The optional `Width` parameter can be used
      ; to override the padding of the output:

      ; num.hex(42) -> "2A"
      ; num.hex(42, 2) -> "002A"

      ; Widths smaller than the minimum size needed
      ; to express the number will be ignored.

      hex .function Value, Width=?

        ByteCount := (num.bit_length(Value) + 7) / 8

        .if !(Width === ?)

          ByteCount := Width < ByteCount ? ByteCount : Width

        .endif ; !(Width === ?)

        FormatString := format("%%0%dX", ByteCount * 2)

      .endfunction format(FormatString, Value)

  .endnamespace ; num

.endif ; GUARD_VOLTEDGE_FUNCTIONS_NUMBERS
