
GUARD_VOLTEDGE_EVENTS_MACROS :?= false
.if (!GUARD_VOLTEDGE_EVENTS_MACROS)
  GUARD_VOLTEDGE_EVENTS_MACROS := true

  VoltEdge_Events_Macros_Created = 0.03
  VoltEdge_Events_Macros_Updated = 0.03

  ; Condition macros

    ; Created: 0.03
    ; Updated: 0.03
    macroECCheckCoordinates .macro Coordinates
      CMP_BYTE wCursorXCoord, \Coordinates[0]
      CMP_BYTE wCursorYCoord, \Coordinates[1]
    .endm

    ; Created: 0.03
    ; Updated: 0.03
    macroECCheckCoordinateRanges .macro UpperLeftCoordinates, LowerRightCoordinates
      CMP_BYTE_RANGE wCursorXCoord, \UpperLeftCoordinates[0], \LowerRightCoordinates[0]
      CMP_BYTE_RANGE wCursorYCoord, \UpperLeftCoordinates[1], \LowerRightCoordinates[1]
    .endm

    ; Created: 0.03
    ; Updated: 0.03
    macroECCheckCoordinateRect .macro Rectangle
      ; Instead of taking two sets of coordinates,
      ; takes a 4-tuple/list of the form
      ; [X, Y, W, H]
      CMP_BYTE_RANGE wCursorXCoord, \Rectangle[0], \Rectangle[0]+\Rectangle[2]
      CMP_BYTE_RANGE wCursorYCoord, \Rectangle[1], \Rectangle[1]+\Rectangle[3]
    .endm

    ; Created: 0.03
    ; Updated: 0.03
    macroECShop .macro ShopDataPointer
      EVENT FlagAlwaysZero, \ShopDataPointer
        CMP_BYTE_AT wCursorXCoord, \ShopDataPointer
        CMP_BYTE_AT wCursorYCoord, \ShopDataPointer+1
      END_DEFINITION
    .endm

    ; Created: 0.03
    ; Updated: 0.03
    macroECBossQuote .macro EventFlag, Character
      EVENT \EventFlag, 



.endif ; GUARD_VOLTEDGE_EVENTS_MACROS
