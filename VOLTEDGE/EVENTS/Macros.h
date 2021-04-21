
GUARD_VOLTEDGE_EVENTS_MACROS :?= false
.if (!GUARD_VOLTEDGE_EVENTS_MACROS)
  GUARD_VOLTEDGE_EVENTS_MACROS := true

  VoltEdge_Events_Macros_Created = 0.03
  VoltEdge_Events_Macros_Updated = 0.04

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
    ; Updated: 0.04
    macroECBossQuote .macro EventFlag, Character
      EVENT \EventFlag, eventBattleQuoteDummyEvent
        CHECK_SINGLE \Character
      END_DEFINITION
    .endm

    ; Created: 0.04
    ; Updated: 0.04
    macroECDoor .macro EventFlag, Coordinates, EventPointer
      EVENT \EventFlag, \EventPointer
        CMP_BYTE wActiveTileXCoordinate, \Coordinates[0]
        CMP_BYTE wActiveTileYCoordinate, \Coordinates[1]
      END_DEFINITION
    .endm

    ; Created: 0.04
    ; Updated: 0.04
    macroECVanillaChest .macro EventFlag, ChestDataPointer
      ; This macro mimics the way vanilla
      ; FE5 does chests: each chest gets a
      ; unique chunk of events and its coordinates
      ; are part of this chunk rather than the
      ; EC definition.
      ; For use with the VANILLA_CHEST helper.
      EVENT \EventFlag, \ChestDataPointer._Events
        CMP_BYTE_AT wCursorXCoord, \ChestDataPointer._Coordinates
        CMP_BYTE_AT wCursorYCoord, \ChestDataPointer._Coordinates+size(byte)
      END_DEFINITION
    .endm

    ; Created: 0.04
    ; Updated: 0.04
    macroECChest .macro EventFlag, Coordinates, EventPointer
      EVENT \EventFlag, \EventPointer
        CMP_BYTE wCursorXCoord, \Coordinates[0]
        CMP_BYTE wCursorYCoord, \Coordinates[1]
      END_DEFINITION
    .endm

.endif ; GUARD_VOLTEDGE_EVENTS_MACROS
