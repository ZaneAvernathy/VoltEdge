
GUARD_VOLTEDGE_EVENTS_HELPERS :?= false
.if (!GUARD_VOLTEDGE_EVENTS_HELPERS)
  GUARD_VOLTEDGE_EVENTS_HELPERS := true

  VoltEdge_Events_Helpers_Created = 0.03
  VoltEdge_Events_Helpers_Updated = 0.07

  ; Misc. helpers for various
  ; event-related things.

  ; Event pointer helper

    ; Created: 0.03
    ; Updated: 0.07
    structChapterEventPointers .struct Opening, Turn, Talk, Location, BeforeAction, Shop, Battle, Ending, AfterAction, PrepGroups
      OpeningEventDefinitions      .long \Opening      ; $00
      TurnEventDefinitions         .long \Turn         ; $03
      TalkEventDefinitions         .long \Talk         ; $06
      LocationEventDefinitions     .long \Location     ; $09
      BeforeActionEventDefinitions .long \BeforeAction ; $0C
      ShopEventDefinitions         .long \Shop         ; $0F
      BattleEventDefinitions       .long \Battle       ; $12
      EndingEvent                  .long \Ending       ; $15
      AfterActionEventDefinitions  .long \AfterAction  ; $18
      PrepGroups                   .long \PrepGroups   ; $1B
    .endstruct

  ; Shop events

    ; Instead of normal events, shop
    ; event definitions point to SHOP codes.

      ; Created: 0.03
      ; Updated: 0.07
      SHOP .segment Coordinates, ItemList
        .byte \Coordinates
        .union
          .word [$0000] x 7
          .word \ItemList
        .endunion
        .word $0000
      .endsegment

  ; Vanilla chests

    ; Each chest in vanilla FE5 has its own
    ; block of data that includes its coordinates,
    ; item, and a chunk of events.

    ; For use with the macroECVanillaChest macro.

    ; There isn't really a reason to use this
    ; yourself, as repeating this is a waste of space.

      ; Created: 0.04
      ; Updated: 0.07
      VANILLA_CHEST .macro Item, Coordinates
        _Coordinates .byte \Coordinates
        _Item .word \Item
        _Events
          STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
          STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
          STORE_WORD wEventEngineParameter1, $0026 ; TODO: tile definitions

          CALL_ASM_LOOP rlASMCSingleTileChangeByCoords
          YIELD_UNK

          STORE_WORD_FROM wEventEngineParameter1, _Item
          CALL_ASM_LOOP rlASMCGiveActiveUnitItem
          YIELD_UNK

          CALL_ASM_LOOP rlASMCSetupGiveItemPopup
          CALL_ASM_LOOP rlASMCWaitWhileGiveItemPopup
          CALL_ASM_LOOP rlASMCSetupGiveToConvoyIfInventoryFull
          CALL_ASM_LOOP rlASMCWaitWhileGiveToConvoyIfInventoryFull
        END2
      .endmacro

  ; Unit groups

    ; For use with LOAD_GROUP_ event codes.

    ; A unit group is made up of one or more
    ; UNIT codes full of unit information followed
    ; by a UNIT code with none of the parameters set.

    ; Included here is also the definition of the
    ; structure.

      ; Created: 0.03
      ; Updated: 0.07
      UNIT .segment Character=None, Allegiance=None, StartCoords=None, MoveCoords=None, Leader=None, Inventory=None, Level=None, BossFlag=None, AI=None
        .if (\Character == None)
          .word $0000 ; End of unit block
        .else
          .word \Character
          .byte (\StartCoords[0] | \Allegiance), \StartCoords[1]
          .byte \MoveCoords
          .word \Leader
          .union
            .byte [$00] x 7
            .byte \Inventory
          .endunion
          .byte \Level | (int(\BossFlag) << 7)
          .byte \AI
        .endif
      .endsegment

      ; Created: 0.03
      ; Updated: 0.07
      structUNITEntry .struct
        ; Less of a macro and more a description of the structure
        Character    .word ? ; $00
        .union
          StartX     .byte ? ; $02
          Allegiance .byte ? ; $02 Uppermost 2 bits
        .endunion
        StartY       .byte ? ; $03
        MoveX        .byte ? ; $04
        MoveY        .byte ? ; $05
        Leader       .word ? ; $06
        .union
        Items .fill 7 ; $08
          .struct
            Item1 .byte ? ; $08
            Item2 .byte ? ; $09
            Item3 .byte ? ; $0A
            Item4 .byte ? ; $0B
            Item5 .byte ? ; $0C
            Item6 .byte ? ; $0D
            Item7 .byte ? ; $0E
          .endstruct
        .endunion
        .union
          Level    .byte ? ; $0F
          BossFlag .byte ? ; $0F Uppermost bit
        .endunion
        .union
          AI .fill 4 ; $10
          .struct
            AI1 .byte ? ; $10
            AI2 .byte ? ; $11
            AI3 .byte ? ; $12
            AI4 .byte ? ; $13
          .endstruct
        .endunion
      .endstruct

  ; MOVE_UNIT helpers

    ; These are shorthands for variants
    ; of the MOVE_UNIT event code.

    ; Remember to include a dummy byte,
    ; such as a YIELD_UNK, after using one
    ; of these.

    ; Created: 0.06
    ; Updated: 0.07
    MOVE_CHAR .segment Character, MoveCoordinates, Speed, Movestring
      MOVE_UNIT \Character, [0, 0], \MoveCoordinates, \Speed, \Movestring
    .endsegment

    ; Created: 0.06
    ; Updated: 0.07
    MOVE_ACTIVE_UNIT .segment MoveCoordinates, Speed, Movestring
      MOVE_CHAR narrow(-1, size(word)), \MoveCoordinates, \Speed, \Movestring
    .endsegment

    ; Created: 0.06
    ; Updated: 0.07
    MOVE_COORDS .segment TargetCoordinates, MoveCoordinates, Speed, Movestring
      MOVE_UNIT None, \TargetCoordinates, \MoveCoordinates, \Speed, \Movestring
    .endsegment

  ; Movestrings

    ; MOVE_ event codes may optionally
    ; have pointers to data that performs
    ; fine movement control, including
    ; movement and other commands that
    ; could not be achievable with the
    ; normal functionality of MOVE_ codes.
    ; This data consists of zero or more
    ; commands followed by a MS_END.

    ; Internal movestring helpers

      MOVESTRING_DOWN  = 1
      MOVESTRING_LEFT  = 2
      MOVESTRING_UP    = 3
      MOVESTRING_RIGHT = 4

    ; Movestring commands

      ; End of a Movestring

        ; Created: 0.03
        ; Updated: 0.07
        MS_END .segment
          .byte $00
        .endsegment

      ; Move a single tile

        ; Created: 0.03
        ; Updated: 0.07
        MS_MOVE_DOWN .segment
          .byte MOVESTRING_DOWN
        .endsegment

        ; Created: 0.03
        ; Updated: 0.07
        MS_MOVE_LEFT .segment
          .byte MOVESTRING_LEFT
        .endsegment

        ; Created: 0.03
        ; Updated: 0.07
        MS_MOVE_UP .segment
          .byte MOVESTRING_UP
        .endsegment

        ; Created: 0.03
        ; Updated: 0.07
        MS_MOVE_RIGHT .segment
          .byte MOVESTRING_RIGHT
        .endsegment

      ; Face a direction for a number
      ; of frames.

        ; Created: 0.03
        ; Updated: 0.07
        MS_FACE_DOWN .segment Time
          .byte 4 + MOVESTRING_DOWN
          .word \Time
        .endsegment

        ; Created: 0.03
        ; Updated: 0.07
        MS_FACE_LEFT .segment Time
          .byte 4 + MOVESTRING_LEFT
          .word \Time
        .endsegment

        ; Created: 0.03
        ; Updated: 0.07
        MS_FACE_UP .segment Time
          .byte 4 + MOVESTRING_UP
          .word \Time
        .endsegment

        ; Created: 0.03
        ; Updated: 0.07
        MS_FACE_RIGHT .segment Time
          .byte 4 + MOVESTRING_RIGHT
          .word \Time
        .endsegment

      ; Move a direction while facing
      ; the same direction as before.

        ; Created: 0.03
        ; Updated: 0.07
        MS_MOVE_DOWN_KEEP_DIRECTION .segment
          .byte 8 + MOVESTRING_DOWN
        .endsegment

        ; Created: 0.03
        ; Updated: 0.07
        MS_MOVE_LEFT_DIRECTION .segment
          .byte 8 + MOVESTRING_LEFT
        .endsegment

        ; Created: 0.03
        ; Updated: 0.07
        MS_MOVE_UP_DIRECTION .segment
          .byte 8 + MOVESTRING_UP
        .endsegment

        ; Created: 0.03
        ; Updated: 0.07
        MS_MOVE_RIGHT_DIRECTION .segment
          .byte 8 + MOVESTRING_RIGHT
        .endsegment

      ; Special effects

        ; Created: 0.03
        ; Updated: 0.07
        MS_DEATH .segment
          ; Causes the sprite to disappear
          ; as if they were killed in battle.
          .byte $0D
        .endsegment

        ; Created: 0.03
        ; Updated: 0.07
        MS_MOVESTAR .segment
          ; Causes the movement star note
          ; to appear over the sprite as if
          ; they procced a movement star.
          .byte $0E
        .endsegment

        ; Created: 0.03
        ; Updated: 0.07
        MS_IN_PLACE .segment
          ; Causes the unit to move in place,
          ; keeping their current direction.
          .byte $0F
        .endsegment

        ; Created: 0.03
        ; Updated: 0.07
        MS_INVIS .segment
          ; Causes the map sprite to be invisible
          ; during the next movestring command.
          .byte $FF
        .endsegment

        ; Created: 0.03
        ; Updated: 0.07
        MS_SET_SPEED .segment Speed
          ; Causes the map sprite to move
          ; faster during the next movestring
          ; command. Speed values range from
          ; 0 (normal speed) to $7E (nearly instant).
          .byte $80 | \Speed
        .endsegment

  ; Retreating unit tables

    ; For use with rlASMCSetFlagIfRetreatingUnitByTable.

    ; A retreating unit table is made
    ; up of one or more RETREAT_FLAG
    ; segments with a Character and Flag
    ; followed by a RETREAT_FLAG with
    ; none of the parameters set.

    ; Created: 0.03
    ; Updated: 0.07
    RETREAT_FLAG .segment Character=None, Flag=None
      .if (\Character == None)
        .word $0000, $0000 ; End of table
      .else
        .word \Character
        .byte \Flag
      .endif
    .endsegment

  ; Color cycling

    ; For use with the CYCLE_COLORS
    ; event code. The code has numerous
    ; issues and it isn't recommended that
    ; you use it.

    ; Each CYCLE_COLORS uses a set of
    ; palettes, pointed to by the PaletteAddress
    ; part of the code, and some cycle info,
    ; pointed to by the InfoAddress part of the code.
    ; The palettes that make up this set start
    ; with a color that is skipped (assumed to
    ; be the transparent color of a palette).

    ; The cycle info consists of one or more
    ; COLOR_CYCLE_INFO structs followed by
    ; a COLOR_CYCLE_LOOP.

    ; This helper makes some assumptions:
    ; It assumes that you start writing at
    ; the start of a palette in the palette
    ; buffer. It assumes that your palettes
    ; include the unused transparent color.
    ; It assumes that the transparent color is
    ; included in Count despite not being copied.

    ; Created: 0.03
    ; Updated: 0.07
    COLOR_CYCLE_INFO .segment BufferOffset, PaletteOffset, PaletteSize, PaletteData, Time
      .byte (\BufferOffset - aBGPaletteBuffer) / size(Color)
      .byte (\PaletteSize / size(Color)) - 1
      .byte (\PaletteOffset - \PaletteData) / size(Color)
      .byte \Time
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    COLOR_CYCLE_LOOP .segment
      .word 0
    .endsegment

.endif ; GUARD_VOLTEDGE_EVENTS_HELPERS
