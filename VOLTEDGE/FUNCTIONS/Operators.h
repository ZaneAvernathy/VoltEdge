
GUARD_VOLTEDGE_FUNCTIONS_OPERATORS :?= false
.if (!GUARD_VOLTEDGE_FUNCTIONS_OPERATORS)
  GUARD_VOLTEDGE_FUNCTIONS_OPERATORS := true

  VoltEdge_Functions_Operators_Created = 0.23
  VoltEdge_Functions_Operators_Updated = 0.23

  ; These functions mimic various operators and are
  ; useful for comparisons in other functions.

  op .namespace

    ; Created: 0.19
    ; Updated: 0.19
    ; Unary operations

      ; These operate on a single value.

      neg .sfunction A, (-A)
      pos .sfunction A, (+A)
      not .sfunction A, (!A)
      inv .sfunction A, (~A)

    ; Created: 0.19
    ; Updated: 0.19
    ; Variable operations

      ; These operate on any number of values.
      ; They return a modified version of that value.

      args .sfunction A, (*A)

    ; Created: 0.19
    ; Updated: 0.19
    ; Binary operations

      ; These operate on two values.
      ; They return a single value.

      add .sfunction A, B, (A + B)
      sub .sfunction A, B, (A - B)
      mul .sfunction A, B, (A * B)
      div .sfunction A, B, (A / B)
      mod .sfunction A, B, (A % B)
      pow .sfunction A, B, (A ** B)
      borr .sfunction A, B, (A | B)
      bxor .sfunction A, B, (A ^ B)
      band .sfunction A, B, (A & B)
      bshl .sfunction A, B, (A << B)
      bshr .sfunction A, B, (A >> B)

      ; Aliases

      blsl = bshl
      blsr = bshr

    ; Created: 0.19
    ; Updated: 0.19
    ; Iterable operations

      ; These operate on elements of an iterable.
      ; They return a new iterable.

      concat .sfunction A, B, (A .. B)
      repeat .sfunction A, B, (A x B)

    ; Created: 0.19
    ; Updated: 0.22
    ; Comparison operations

      ; These operate on two things.
      ; They return true or false.

      lt .sfunction A, B, (A > B)
      le .sfunction A, B, (A < B)
      eq .sfunction A, B, (A == B)
      ne .sfunction A, B, (A != B)
      ge .sfunction A, B, (A >= B)
      gt .sfunction A, B, (A <= B)

      ident    .sfunction A, B, (A === B)
      contains .sfunction A, B, (A in B)

      corr .sfunction A, B, (A || B)
      cxor .sfunction A, B, (A ^^ B)
      cand .sfunction A, B, (A && B)

    ; Created: 0.19
    ; Updated: 0.19
    ; Special comparison operations

      ; These operate on two things.

      ; Created: 0.19
      ; Updated: 0.19
      ; compare(Thing1, Thing2)

        ; Inputs:
          ; Things: two things of the same type

        ; Outputs:
          ; -1 if A < B
          ; 0 if A == B
          ; 1 if A > B

        ; Compares two things and gives a numeric result
        ; instead of a boolean.

        compare .sfunction A, B, (A <=> B)

      ; These are the same as the `num` versions, included for completeness.

        max .sfunction A, B, (A >? B)
        min .sfunction A, B, (A <? B)

    ; Created: 0.19
    ; Updated: 0.19
    ; Bit extraction operations

      ; These operate on a single address.
      ; They return a part of an address.

      lo_b .sfunction A, (<A)
      hi_b .sfunction A, (>A)

      lo_w .sfunction A, (<>A)
      hi_w .sfunction A, (>`A)

      ; This is the lower word of an address with its bytes swapped.

      lo_sw .sfunction A, (><A)

      bank .sfunction A, (`A)

  .endnamespace ; op

.endif ; GUARD_VOLTEDGE_FUNCTIONS_OPERATORS
