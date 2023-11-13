
GUARD_VOLTEDGE_FUNCTIONS_ENUMERATIONS :?= false
.if (!GUARD_VOLTEDGE_FUNCTIONS_ENUMERATIONS)
  GUARD_VOLTEDGE_FUNCTIONS_ENUMERATIONS := true

  VoltEdge_Functions_Enumerations_Created = 0.23
  VoltEdge_Functions_Enumerations_Updated = 0.23

  ; These functions are for working with
  ; enumerated values.

  enum .namespace

    ; Created: 0.19
    ; Updated: 0.23
    ; enum(Init=?, Increment=EnumDefaultIncrement)

      ; Inputs:
        ; Init: Optional initial value

      ; Outputs:
        ; An integer

      ; If invoked with an Init value, initializes
      ; a new enumeration starting with that
      ; value and returns it.

      ; If invoked without an Init value, returns
      ; the next value in the enumeration, counting up
      ; by one and saving the state for the next invocation.

      ; Example:

      ; enum.enum(42)    = 42
      ; enum.enum()      = 43
      ; enum.enum(0, 2)  = 0
      ; enum.enum()      = 2
      ; enum.enum()      = 4

    EnumDefaultIncrement = 1
    EnumIndex :?= 0
    EnumIncrement :?= EnumDefaultIncrement

    enum .function Init=?, Increment=EnumDefaultIncrement
      enum.EnumIndex :?= 0
      enum.EnumIncrement :?= Increment
      .if (Init === ?)
        enum.EnumIndex += enum.EnumIncrement
      .else
        enum.EnumIndex ::= Init
        enum.EnumIncrement ::= Increment
      .endif
    .endfunction enum.EnumIndex

  .endnamespace ; enum

.endif ; GUARD_VOLTEDGE_FUNCTIONS_ENUMERATIONS
