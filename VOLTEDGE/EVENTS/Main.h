
GUARD_VOLTEDGE_EVENTS_MAIN :?= false
.if (!GUARD_VOLTEDGE_EVENTS_MAIN)
  GUARD_VOLTEDGE_EVENTS_MAIN := true

  VoltEdge_Events_Main_Created = 0.03
  VoltEdge_Events_Main_Updated = 0.23

  ; Psuedo-end code YIELD

    ; Created: 0.03
    ; Updated: 0.07
    YIELD .segment
      ; Breaks out of event execution.
      ; See YIELD_UNK.
      .char -4
    .endsegment

  ; Raw event codes

    ; Some codes are prefixed with 'EVENT_'
    ; to delineate them from similar event
    ; condition codes.

    ; Created: 0.03
    ; Updated: 0.07
    YIELD_UNK .segment
      ; Breaks out of event execution.
      ; The only difference between
      ; YIELD_UNK and YIELD is that
      ; YIELD is checked like an end code while
      ; YIELD_UNK is treated like a normal event
      ; code. The implications of this are not
      ; currently known.
      .byte $00
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    EVENT_NOP_01 .segment
      ; This event code does nothing.
      .byte $01
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    JUMP .segment Address
      ; Moves event execution to a
      ; specified Address within the same bank.
      .byte $02
      .addr \Address
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    JUMP_TRUE .segment Address
      ; Moves event execution to a
      ; specified Address within the same bank
      ; if wEventEngineTruthFlag is nonzero.
      .byte $03
      .addr \Address
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    JUMP_FALSE .segment Address
      ; Moves event execution to a
      ; specified Address within the same bank
      ; if wEventEngineTruthFlag is zero.
      .byte $04
      .addr \Address
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    JUMP_RELATIVE .segment Distance
      ; Unused in vanilla.
      ; Moves event execution a signed Distance
      ; from the current execution address.
      ; The actual distance is measured from
      ; the second byte; this macro assumes you
      ; would rather measure distance from the
      ; start of this event code.
      .byte $05
      .sint (\Distance - 1)
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    JUMP_RELATIVE_TRUE .segment Distance
      ; Unused in vanilla.
      ; Works like JUMP_RELATIVE but
      ; only jumps if wEventEngineTruthFlag
      ; is nonzero.
      .byte $06
      .sint (\Distance - 1)
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    JUMP_RELATIVE_FALSE .segment Distance
      ; Unused in vanilla.
      ; Works like JUMP_RELATIVE but
      ; only jumps if wEventEngineTruthFlag
      ; is zero.
      .byte $07
      .sint (\Distance - 1)
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    EVENT_CMP_BYTE_LT .segment Address, Value
      ; Returns wEventEngineTruthFlag nonzero
      ; if the byte at Address is less than Value,
      ; else returns wEventEngineTruthFlag zero.
      .byte $08
      .long \Address
      .byte \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    EVENT_CMP_WORD_LT .segment Address, Value
      ; Returns wEventEngineTruthFlag nonzero
      ; if the word at Address is less than Value,
      ; else returns wEventEngineTruthFlag zero.
      .byte $09
      .long \Address
      .word \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    EVENT_CMP_BYTE_EQ .segment Address, Value
      ; Returns wEventEngineTruthFlag nonzero
      ; if the byte at Address is equal to Value,
      ; else returns wEventEngineTruthFlag zero.
      .byte $0A
      .long \Address
      .byte \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    EVENT_CMP_WORD_EQ .segment Address, Value
      ; Returns wEventEngineTruthFlag nonzero
      ; if the word at Address is equal to Value,
      ; else returns wEventEngineTruthFlag zero.
      .byte $0B
      .long \Address
      .word \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    SET_FLAG .segment Flag
      ; Sets the specified flag.
      .byte $0C
      .byte \Flag
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    UNSET_FLAG .segment Flag
      ; Clears the specified flag.
      .byte $0D
      .byte \Flag
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    EVENT_TEST_FLAG_SET .segment Flag
      ; Returns wEventEngineTruthFlag nonzero
      ; if the specified Flag is set, else
      ; returns wEventEngineTruthFlag zero.
      .byte $0E
      .byte \Flag
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    STORE_BYTE .segment Address, Value
      ; Stores the Value byte to Address.
      .byte $0F
      .long \Address
      .byte \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    STORE_WORD .segment Address, Value
      ; Stores the Value word to Address.
      .byte $10
      .long \Address
      .word \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    STORE_LONG .segment Address, Value
      ; Stores the Value long to Address.
      .byte $11
      .long \Address
      .long \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    STORE_BYTE_FROM .segment Destination, Source
      ; Stores a byte from Source to Destination.
      .byte $12
      .long \Destination
      .long \Source
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    STORE_WORD_FROM .segment Destination, Source
      ; Stores a word from Source to Destination.
      .byte $13
      .long \Destination
      .long \Source
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    STORE_LONG_FROM .segment Destination, Source
      ; Stores a long from Source to Destination.
      .byte $14
      .long \Destination
      .long \Source
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    ADD_BYTE .segment Address, Value
      ; Adds a Value to the byte at Address.
      .byte $15
      .long \Address
      .byte \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    ADD_WORD .segment Address, Value
      ; Adds a Value to the word at Address.
      .byte $16
      .long \Address
      .word \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    ADD_LONG .segment Address, Value
      ; Adds a Value to the long at Address.
      .byte $17
      .long \Address
      .long \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    ORR_BYTE .segment Address, Value
      ; ORRs a Value to the byte at Address.
      .byte $18
      .long \Address
      .byte \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    ORR_WORD .segment Address, Value
      ; ORRs a Value to the word at Address.
      .byte $19
      .long \Address
      .word \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    ORR_LONG .segment Address, Value
      ; ORRs a Value to the long at Address.
      .byte $1A
      .long \Address
      .long \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CALL_ASM_SKIPPABLE .segment Address, Argument=$0000
      ; Runs the (long return) assembly routine at Address,
      ; with Argument passed in the X register. Many
      ; routines do not use the Argument, so a default
      ; zero value is provided. If events are currently
      ; being skipped, the routine is not run.
      .byte $1B
      .long \Address
      .word \Argument
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CALL_ASM_LONG_SKIPPABLE .segment Address, Argument=$000000
      ; Runs the (long return) assembly routine at Address,
      ; with Argument passed in lR18. If events are
      ; currently being skipped, the routine is not run.
      .byte $1C
      .long \Address
      .long \Argument
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CALL_ASM_LOOP .segment Address, Argument=$0000
      ; Runs the (long return) assembly routine at Address,
      ; with Argument passed in the X register. Many
      ; routines do not use the Argument, so a default
      ; zero value is provided. The position within the
      ; events will not advance and the routine will be
      ; run again on the next event engine cycle if the
      ; routine returns carry set. Execution continues
      ; as normal if the routine returns carry clear.
      .byte $1D
      .long \Address
      .word \Argument
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    PAUSE_SKIPPABLE .segment Time
      ; Pauses event execution for
      ; a Time number of event engine cycles.
      ; Events that are already in progress,
      ; such as unit movement, continue to execute.
      ; This variant is skipped if events are
      ; currently being skipped.
      .byte $1E
      .word \Time
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    PAUSE .segment Time
      ; Pauses event execution for
      ; a Time number of event engine cycles.
      ; Events that are already in progress,
      ; such as unit movement, continue to execute.
      .byte $1F
      .word \Time
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    SCAN_INPUT .segment
      ; Unused in vanilla.
      ; Creates a proc procExistUntilRightButton
      ; ($828E6C) that exists until any of the
      ; A, B, X, or Y buttons are pressed.
      ; Does not pause event execution, does
      ; not return anything. You should
      ; use a CALL_ASM_ code to call some
      ; routine to scan for the proc's existence.
      .byte $20
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    SCAN_INPUT_TIME .segment Time
      ; Same as SCAN_INPUT, but the
      ; proc only exists for Time cycles
      ; until automatically killed if no
      ; buttons are pressed.
      .byte $21
      .word \Time
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    HALT_UNTIL_BYTE .segment Address, Value
      ; Halts event execution until the
      ; byte at Address is equal to Value.
      .byte $22
      .long \Address
      .byte \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    HALT_UNTIL_WORD .segment Address, Value
      ; Halts event execution until the
      ; word at Address is equal to Value.
      .byte $23
      .long \Address
      .word \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    HALT_UNTIL_BYTE_SKIPPABLE .segment Address, Value
      ; Same as HALT_UNTIL_BYTE but
      ; is skipped if events are being skipped.
      .byte $24
      .long \Address
      .byte \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    HALT_UNTIL_WORD_SKIPPABLE .segment Address, Value
      ; Same as HALT_UNTIL_WORD but
      ; is skipped if events are being skipped.
      .byte $25
      .long \Address
      .word \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    FADE_IN .segment Step
      ; Fades the screen in from black,
      ; increasing the brightness by
      ; one every Step cycles.
      .byte $26
      .byte \Step
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    FADE_OUT .segment Step
      ; Fades the screen out to black,
      ; decreasing the brightness by
      ; one every Step cycles.
      .byte $27
      .byte \Step
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    CYCLE_COLORS .segment PaletteAddress, InfoAddress
      ; Unused in vanilla.
      ; I'm unable to figure out how to get
      ; this code to work properly, each cycle
      ; advances two bytes into the cycle info,
      ; but each cycle info struct is four bytes.
      ; Use at your own risk.
      ; This cycles through colors taken from
      ; data at PaletteAddress using information
      ; from data at InfoAddress.
      ; This event is skipped if events are
      ; currently being skipped.
      ; Event execution will run until the next
      ; yielding code, including end codes, but
      ; will block the event engine from running
      ; again until the proc it creates,
      ; procEventCycleColors ($828F09), is killed.
      ; See "EVENTS/Helpers.h" for details.
      .byte $28
      .long \PaletteAddress
      .long \InfoAddress
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    EVENT_UNK_29 .segment
      ; Unused in vanilla.
      ; The exact purpose of this code
      ; is unknown. It seems to reset
      ; various dialogue text-related
      ; variables.
      .byte $29
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    EVENT_UNK_2A .segment
      ; Unused in vanilla.
      ; The exact purpose of this code
      ; is unknown. It resets a bit that
      ; is set by EVENT_UNK_29, so I
      ; assume that they are related.
      .byte $2A
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    DIALOGUE .segment Address
      ; Queues up dialogue at Address to
      ; be interpreted. Events continue to
      ; be executed until the next yield/end,
      ; after which the dialogue halts event
      ; execution until it has finished. If you
      ; want the dialogue to play immediately, use
      ; a YIELD after the DIALOGUE.
      .byte $2B
      .long \Address
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    DIALOGUE_ARRAY .segment Address
      ; Similar to DIALOGUE but instead
      ; of interpreting dialogue at Address,
      ; Address points to a table of `structQuoteEntry`s,
      ; using the character ID in wEventEngineCharacterTarget
      ; to match against the entry's character field and
      ; wCurrentChapter to match against the entry's
      ; chapter field.
      ; Also, sets the flag specified by the entry's
      ; flag field on a match.
      ; Returns wEventEngineTruthFlag nonzero on a match,
      ; zero if no match.
      .byte $2C
      .long \Address
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    EVENT_UNK_2D .segment Address, Value1, Value2
      ; Unused in vanilla.
      ; Something dialogue-related.
      ; Address is a pointer to dialogue.
      ; Value1 has a special case of $FF,
      ; although its purpose is unknown.
      .byte $2D
      .long \Address
      .byte \Value1
      .byte \Value2
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    EVENT_UNK_2E .segment
      ; Unused in vanilla.
      ; This code DMAs glyph data
      ; (presumably in RAM as part of an
      ; assembled dialogue string) pointed
      ; to by $7E458B.
      .byte $2E
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    EVENT_UNK_2F .segment Address
      ; Unused in vanilla.
      ; Thus code sets the pointer
      ; at $7E458B. See EVENT_UNK_2E.
      .byte $2F
      .long \Address
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    SET_DIALOGUE_POINTER .segment Address
      ; Unused in vanilla.
      ; Sets the dialogue pointer to
      ; Address.
      .byte $30
      .long \Address
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    SET_MUSIC .segment Song
      ; If events are not being skipped,
      ; sets the map music to Song
      ; and begins playing.
      .byte $31
      .byte \Song
    .endsegment

    ; Created: 0.03
    ; Updated: 0.23
    PLAY_SOUND .segment NormalSFX
      ; Unused in vanilla.
      ; This plays a normal sound effect
      ; (one that you'd play with rlPlaySoundEffect ($808C87))
      ; if events are not currently being skipped.
      ; This does not play a sound if sound effects are disabled.
      ; This provides $00 as the parameter for the sound system.
      .byte $32
      .byte \NormalSFX
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    EVENT_NOP_33 .segment Value
      ; Unused in vanilla.
      ; This code does nothing.
      .byte $33
      .byte \Value
    .endsegment

    ; Created: 0.03
    ; Updated: 0.23
    PLAY_EXTENDED_SOUND .segment ExtendedSFX
      ; This plays an extended sound effect
      ; (one that you'd play with rlPlayExtendedSoundEffect ($808CDD))
      ; if events are not currently being skipped.
      .byte $34
      .byte \ExtendedSFX
    .endsegment

    ; Created: 0.03
    ; Updated: 0.23
    PLAY_SOUND_FORCED .segment NormalSFX, Parameter=None
      ; This plays a sound even if sound effects
      ; are disabled. This includes a parameter, unlike
      ; `PLAY_SOUND`.
      ; This plays a normal sound effect
      ; (one that you'd play with rlPlaySoundEffectForced ($808C7D))
      ; if events are not currently being skipped.
      .byte $35
      .byte \NormalSFX, \Parameter
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    RESET_PHASE_MUSIC .segment
      ; Changes the current music
      ; back to the phase's music setting.
      .byte $36
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    GET_CHARACTER_COORDS .segment Character
      ; Sets [wEventEngineXCoordinate, wEventEngineYCoordinate]
      ; to the Character's coordinates. Caution:
      ; this treats character IDs as bytes
      ; rather than words, and won't work
      ; correctly for IDs higher than $00FF.
      .byte $37
      .byte \Character
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    SET_CURSOR_POSITION .segment
      ; Sets the cursor position
      ; to [wEventEngineXCoordinate, wEventEngineYCoordinate]
      .byte $38
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    SET_CAMERA_POSITION .segment Coordinates
      ; Instantly moves the camera to
      ; Coordinates.
      .byte $39
      .byte \Coordinates
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    SET_FADE_STEP .segment Step
      ; Unused in vanilla.
      ; Sets the input step speed for some
      ; kinds of fades, although the
      ; result of this is normally
      ; overridden by things that govern
      ; fading.
      .byte $3A
      .byte \Step
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    EVENT_NOP_3B .segment
      ; Unused in vanilla.
      ; This code does nothing.
      .byte $3B
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    EVENT_NOP_3C .segment Value1, Value2, Value3
      ; Unused in vanilla.
      ; This code does nothing.
      .byte $3C
      .byte \Value1
      .byte \Value2
      .byte \Value3
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    SCROLL_CAMERA_COORDS .segment Coordinates, Speed
      ; Smoothly scrolls the camera
      ; to Coordinates, stepping Speed
      ; pixels every cycle.
      .byte $3D
      .byte \Coordinates
      .byte \Speed
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    SCROLL_CAMERA .segment Speed
      ; Smoothly scrolls the camera
      ; to [wEventEngineXCoordinate, wEventEngineYCoordinate],
      ; stepping Speed pixels every cycle.
      .byte $3E
      .byte \Speed
    .endsegment

    ; Created: 0.03
    ; Updated: 0.19
    MOVE_TEMPORARY .segment Character, StartingCoordinates, Speed, Color, Movestring=None
      ; Creates a temporary Character at
      ; StartingCoordinates using Color,
      ; Moves them according to the data
      ; pointed to by Movestring using Speed,
      ; and deletes them once they reach
      ; their destination. Color should
      ; be one of Player, Enemy, or NPC.
      .byte $3F
      .word \Character
      .byte \StartingCoordinates
      .byte \Speed
      .byte \Color >> 6
      .long \Movestring
    .endsegment

    ; Created: 0.03
    ; Updated: 0.23
    MOVE_TEMPORARY_CENTERED .segment Character, StartingCoordinates, Speed, Color, Movestring=None
      ; Same as MOVE_TEMPORARY but
      ; the camera follows the unit.
      .byte $40
      .word \Character
      .byte \StartingCoordinates
      .byte \Speed
      .byte \Color >> 6
      .long \Movestring
    .endsegment

    ; Created: 0.03
    ; Updated: 0.19
    MOVE_UNIT .segment Character, TargetCoordinates, MoveCoordinates, Speed, Movestring=None
      ; Moves a unit to MoveCoordinates
      ; at Speed, then have them move
      ; according to the data pointed
      ; to by Movestring. You may target
      ; a unit by specifying a Character
      ; or a pair of TargetCoordinates.
      ; If a Character is specified, the
      ; first unit with that Character ID
      ; is used. If TargetCoordinates are
      ; specified, moves the unit at that tile.
      ; Only one should be used at a time,
      ; and the unused targeting parameter
      ; should be zero.
      ; Warning: In vanilla the size of this
      ; event code is wrong, you should include
      ; a dummy byte, such as a YIELD_UNK, after
      ; using this event.
      .byte $41
      .word \Character
      .byte \TargetCoordinates
      .byte \MoveCoordinates
      .byte \Speed
      .long \Movestring
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    LOAD_GROUP .segment Address
      ; Loads a group of units
      ; pointed to by Address.
      ; This event code will attempt
      ; to spawn units in occupied tiles,
      ; moving them to the closest empty tile.
      .byte $42
      .long \Address
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    LOAD_GROUP_BLOCKABLE .segment Address
      ; Loads a group of units
      ; pointed to by Address.
      ; This event code will skip
      ; units whose target tile is
      ; occupied by another unit.
      .byte $43
      .long \Address
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    SCROLL_CAMERA_ADDRESS .segment Address
      ; Scrolls the camera to the
      ; coordinate bytes given by
      ; the data at Address.
      .byte $44
      .long \Address
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    WAIT_MOVE .segment
      ; Halts event execution until units,
      ; mapsprites are done moving.
      .byte $45
    .endsegment

    ; Created: 0.03
    ; Updated: 0.07
    WARP_UNIT .segment Character, TargetCoordinates, MoveCoordinates
      ; Works like MOVE_UNIT but
      ; the unit is instantly
      ; moved to MoveCoordinates.
      .byte $46
      .word \Character
      .byte \TargetCoordinates
      .byte \MoveCoordinates
    .endsegment

.endif ; GUARD_VOLTEDGE_EVENTS_MAIN
