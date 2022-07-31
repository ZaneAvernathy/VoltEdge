
GUARD_VOLTEDGE_EVENTS_CONDITIONS :?= false
.if (!GUARD_VOLTEDGE_EVENTS_CONDITIONS)
  GUARD_VOLTEDGE_EVENTS_CONDITIONS := true

  VoltEdge_Events_Conditions_Created = 0.03
  VoltEdge_Events_Conditions_Updated = 0.21

  ; Event definition helper

    ; Created: 0.03
    ; Updated: 0.07
    EVENT .segment Flag, Address
      ; Runs events at Address if conditions
      ; between it and the next END_DEFINITION
      ; are met and Flag is unset. Sets Flag
      ; before running the events.
      .byte \Flag
      .long \Address
    .endsegment

  ; Event definition conditions.

    ; CHECK_CHARS1 and CHECK_CHARS2 are
    ; identical; vanilla only uses CHECK_CHARS2.

    ; Created: 0.03
    ; Updated: 0.07
    CHECK_CHARS1 .segment Character1, Character2
      ; Unused in vanilla.
      ; Returns true if:
      ; Character1 in wEventEngineCharacterStructParameter
      ; and
      ; Character2 in wEventEngineCharacterTarget
      ; otherwise returns false.
      ; Also returns false if Character2 == 0.
      .byte $00
      .word \Character1
      .word \Character2
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CHECK_CHARS2 .segment Character1, Character2
      ; Identical to CHECK_CHARS1.
      .byte $01
      .word \Character1
      .word \Character2
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CHECK_SINGLE .segment Character
      ; Returns true if:
      ; Character in wEventEngineCharacterStructParameter
      ; or
      ; Character in wEventEngineCharacterTarget
      ; otherwise returns false.
      ; Also returns false if Character2 == 0.
      ; If either matches, the character's ID is
      ; stored in the other variable, i.e.
      ; if the Character is in wEventEngineCharacterTarget,
      ; it is stored to wEventEngineCharacterStructParameter
      ; regardless of wEventEngineCharacterStructParameter's contents.
      .byte $02
      .word \Character
    .endsegment

    ; Created: 0.03
    ; Updated: 0.20
    CHECK_COORDS .segment Coordinates
      ; Returns true if:
      ; Coordinates match [wEventEngineXCoordinate, wEventEngineYCoordinate]
      .byte $03
      .word pack(\Coordinates)
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CMP_BITS .segment Address, Value
      ; Returns true if:
      ; (The word at Address) & Value != 0
      ; Thus, it returns true if any of the bits
      ; in Value are set in the word at Address.
      ; Vanilla uses this to check for single bits,
      ; which functions as returning true if
      ; the word at Address has the Value bit set.
      .byte $04
      .long \Address
      .word \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CMP_BYTE .segment Address, Value
      ; Returns true if:
      ; (The byte at Address) == Value
      .byte $05
      .long \Address
      .byte \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CMP_WORD .segment Address, Value
      ; Returns true if:
      ; (The word at Address) == Value
      .byte $06
      .long \Address
      .word \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CMP_LONG .segment Address, Value
      ; Returns true if:
      ; (The long at Address) == Value
      .byte $07
      .long \Address
      .long \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CMP_WORD_FALSE .segment Address, Value
      ; Returns true if:
      ; (The word at Address) != Value
      .byte $08
      .long \Address
      .word \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CMP_BYTE_AT .segment Address1, Address2
      ; Returns true if:
      ; (The byte at Address1) == (The byte at Address2)
      .byte $09
      .long \Address1
      .long \Address2
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CMP_WORD_AT .segment Address1, Address2
      ; Returns true if:
      ; (The word at Address1) == (The word at Address2)
      .byte $0A
      .long \Address1
      .long \Address2
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CMP_BYTE_RANGE .segment Address, Minimum, Maximum
      ; Returns true if:
      ; Minimum <= (The byte at Address) <= Maximum
      .byte $0B
      .long \Address
      .byte \Minimum
      .byte \Maximum
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CMP_WORD_RANGE .segment Address, Minimum, Maximum
      ; Returns true if:
      ; Minimum <= (The word at Address) <= Maximum
      .byte $0C
      .long \Address
      .word \Minimum
      .word \Maximum
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    TEST_FLAG_SET .segment Flag
      ; Returns true if:
      ; The specified flag is set
      .byte $0D
      .byte \Flag
    .endsegment

    ; Created: 0.03
    ; Updated: 0.21
    TEST_FLAG_UNSET .segment Flag
      ; Returns true if:
      ; The specified flag is unset
      .byte $0E
      .byte \Flag
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    RUN_ASM .segment Address
      ; Returns true if:
      ; ASM at Address returns true (carry set)
      .byte $0F
      .long \Address
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CMP_UNITSTATE_SET .segment Character, State
      ; Returns true if:
      ; ((Character's unit state) & State) == State
      .byte $10
      .word \Character
      .word \State
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CMP_UNITSTATE_UNSET .segment Character, State
      ; Returns true if:
      ; ((Character's unit state) & State) != State
      .byte $11
      .word \Character
      .word \State
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CHECK_HOLDING_ITEM .segment Item
      ; Unused in vanilla.
      ; Don't use this: a programming error
      ; causes this to crash if the target unit
      ; is not found. Also, it's programmed
      ; specifically to read character IDs as a byte,
      ; and will potentially select the wrong unit.
      ; Returns true if:
      ; The first unit given by (character ID & 0xFF) in
      ; wEventEngineCharacterTarget is holding at least
      ; one of Item.
      .byte $12
      .byte \Item
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CHECK_ACTIVE_HOLDING_ITEM .segment Item
      ; Unused in vanilla.
      ; Returns true if:
      ; The active unit (in aSelectedCharacterBuffer)
      ; is holding at least one of Item.
      .byte $13
      .byte \Item
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CHECK_ACTIVE_CARRYING .segment Character
      ; Returns true if:
      ; The active unit (in aSelectedCharacterBuffer)
      ; is rescuing/capturing Character.
      .byte $14
      .word \Character
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CHECK_RESCUED_BY_ENEMY .segment Character
      ; Unused in vanilla.
      ; Name is a guess, as this is most
      ; likely bugged: Stores found unit to
      ; aItemSkillCharacterBuffer but checks
      ; if unit in aBurstWindowCharacterBuffer is
      ; being carried.
      .byte $15
      .word \Character
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CHECK_NUM_UNITS_LTE .segment Character, Number
      ; Returns true if:
      ; The number of uncaptured alive units with
      ; ID Character is less than or equal to Number.
      .byte $16
      .word \Character
      .byte \Number
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CHECK_NUM_UNITS_GTE .segment Character, Number
      ; Returns true if:
      ; The number of uncaptured alive units with
      ; ID Character is greater than or equal to Number.
      .byte $17
      .word \Character
      .byte \Number
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    ROLL_RNG .segment PercentChance
      ; Returns true if:
      ; Number rolled is less than PercentChance.
      .byte $18
      .byte \PercentChance
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CHECK_IF_RANDOM_CHEST .segment
      ; Returns true if:
      ; There is a randomized chest at [wCursorXCoord, wCursorYCoord].
      .byte $19
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CHECK_IF_BOSS_DEAD .segment Character
      ; Returns true if:
      ; Character is dead.
      ; Also sets FlagBossDeath.
      .byte $1A
      .word \Character
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    KILLED_IN_BATTLE .segment Character
      ; Unused in vanilla.
      ; Returns true if:
      ; Character was killed in last(?) battle.
      .byte $1B
      .word \Character
    .endsegment

.endif ; GUARD_VOLTEDGE_EVENTS_CONDITIONS
