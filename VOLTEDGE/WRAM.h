
GUARD_VOLTEDGE_WRAM :?= false
.if (!GUARD_VOLTEDGE_WRAM)
  GUARD_VOLTEDGE_WRAM := true

  VoltEdge_WRAM_Created = 0.01
  VoltEdge_WRAM_Updated = 0.24

  ; This is a work-in-progress RAM map of FE5.

  ; Names are likely to change, gaps are likely to
  ; be filled. Variables and structures may be
  ; given temporary names and may lack comments
  ; describing their use.

  ; The format for each of these WRAM variables is:
  ; SomeName .thing ? ; Address LastUpdatedVersion
  ;  ; Possibly some comment describing the variable(s)

  .virtual $000000

    ; These variables are used by
    ; the decompressor.

    DecompressionVariables .block ; $000000 0.01
      ; The sound system clears
      ; these variables as a single block.
      lSource .long ?             ; $000000 0.01
        ; This is an internal long pointer
        ; to the start of compressed
        ; data.
      .union
        lDest .long ?             ; $000003 0.01
          ; This is (initially) an
          ; internal long pointer to
          ; where the decompressed
          ; data will be written to.
        .struct
          ; These variables are used
          ; by individual decompression
          ; methods for various purposes.
          bVar0 .byte ?           ; $000003 0.01
          bVar1 .byte ?           ; $000004 0.01
          bMethodCount .byte ?    ; $000005 0.01
        .endstruct
      .endunion
      lTemp .long ?               ; $000006 0.01
        ; This is a temporary long
        ; pointer used by special
        ; decompression methods.
      bCount .byte ?              ; $000009 0.01
        ; This is a counter used by
        ; a special decompression method.
      bFlag .byte ?               ; $00000A 0.01
        ; This flag is set during
        ; a special decompression method.
    .endblock

    ; These are a set of variables
    ; that are used like CPU registers
    ; for the purpose of holding
    ; routine parameters or temporary
    ; data during subroutine calls.

    wR0 .word ? ; $00000B 0.01
    wR1 .word ? ; $00000D 0.01
    wR2 .word ? ; $00000F 0.01
    wR3 .word ? ; $000011 0.01
    wR4 .word ? ; $000013 0.01
    wR5 .word ? ; $000015 0.01
    wR6 .word ? ; $000017 0.01
    wR7 .word ? ; $000019 0.01
    wR8 .word ? ; $00001B 0.01
    wR9 .word ? ; $00001D 0.01
      ; These are general-purpose
      ; registers for passing in
      ; (mostly) small parameters.

    wR10 .word ? ; $00001F 0.01
    wR11 .word ? ; $000021 0.01
    wR12 .word ? ; $000023 0.01
    wR13 .word ? ; $000025 0.01
    wR14 .word ? ; $000027 0.01
    wR15 .word ? ; $000029 0.01
    wR16 .word ? ; $00002B 0.01
    wR17 .word ? ; $00002D 0.01
      ; These are generally used
      ; for math-related parameters

    lR18 .long ? ; $00002F 0.01
    lR19 .long ? ; $000032 0.01
    lR20 .long ? ; $000035 0.01
    lR21 .long ? ; $000038 0.01
    lR22 .long ? ; $00003B 0.01
    lR23 .long ? ; $00003E 0.01
    lR24 .long ? ; $000041 0.01
    lR25 .long ? ; $000044 0.01
      ; These are generally used
      ; to pass long pointers to
      ; routines.

    wR26 .word ? ; $000047 0.01
    wR27 .word ? ; $000049 0.01
    wR28 .word ? ; $00004B 0.01
    wR29 .word ? ; $00004D 0.01
    wR30 .word ? ; $00004F 0.01
    wR31 .word ? ; $000051 0.01
    wR32 .word ? ; $000053 0.01
    wR33 .word ? ; $000055 0.01
    wR34 .word ? ; $000057 0.01
    wR35 .word ? ; $000059 0.01
    wR36 .word ? ; $00005B 0.01
    wR37 .word ? ; $00005D 0.01

    lR38 .long ? ; $00005F 0.01
    lR39 .long ? ; $000062 0.01

    wR40 .word ? ; $000065 0.01
    wR41 .word ? ; $000067 0.01
    wR42 .word ? ; $000069 0.01
    wR43 .word ? ; $00006B 0.01

    lR44 .long ? ; $00006D 0.01
      ; This is used as a long pointer
      ; input for the proc system.

    lR45 .long ? ; $000070 0.01
      ; This is used as a long pointer
      ; to compressed source data
      ; for some decompression
      ; routines.

    wR46 .word ? ; $000073 0.01

    lR47 .long ? ; $000075 0.01
      ; This is used as a long pointer
      ; to the target decompression
      ; destination for some
      ; decompression routines.

    lR48 .long ? ; $000078 0.01

    ; These variables are a
    ; buffer for various IO
    ; registers. They are copied
    ; to their respective IO
    ; registers every frame.

    bBufferINIDISP   .byte ? ; $00007B 0.01
    bBufferOBSEL     .byte ? ; $00007C 0.01
    wBufferOAMADD    .word ? ; $00007D 0.01
    bBufferBGMODE    .byte ? ; $00007F 0.01
    bBufferMOSAIC    .byte ? ; $000080 0.01
    bBufferBG1SC     .byte ? ; $000081 0.01
    bBufferBG2SC     .byte ? ; $000082 0.01
    bBufferBG3SC     .byte ? ; $000083 0.01
    bBufferBG4SC     .byte ? ; $000084 0.01
    bBufferBG12NBA   .byte ? ; $000085 0.01
    bBufferBG34NBA   .byte ? ; $000086 0.01
    bBufferM7SEL     .byte ? ; $000087 0.01
    bBufferW12SEL    .byte ? ; $000088 0.01
    bBufferW34SEL    .byte ? ; $000089 0.01
    wBufferBG1HOFS   .word ? ; $00008A 0.01
    wBufferBG1VOFS   .word ? ; $00008C 0.01
    wBufferBG2HOFS   .word ? ; $00008E 0.01
    wBufferBG2VOFS   .word ? ; $000090 0.01
    wBufferBG3HOFS   .word ? ; $000092 0.01
    wBufferBG3VOFS   .word ? ; $000094 0.01
    wBufferBG4HOFS   .word ? ; $000096 0.01
    wBufferBG4VOFS   .word ? ; $000098 0.01
    bBufferWOBJSEL   .byte ? ; $00009A 0.01
    bBufferWH0       .byte ? ; $00009B 0.01
    bBufferWH1       .byte ? ; $00009C 0.01
    bBufferWH2       .byte ? ; $00009D 0.01
    bBufferWH3       .byte ? ; $00009E 0.01
    bBufferWBGLOG    .byte ? ; $00009F 0.01
    bBufferWOBJLOG   .byte ? ; $0000A0 0.01
    bBufferTM        .byte ? ; $0000A1 0.01
    bBufferTS        .byte ? ; $0000A2 0.01
    bBufferTMW       .byte ? ; $0000A3 0.01
    bBufferTSW       .byte ? ; $0000A4 0.01
    bBufferCGWSEL    .byte ? ; $0000A5 0.01
    bBufferCGADSUB   .byte ? ; $0000A6 0.01
    bBufferCOLDATA_0 .byte ? ; $0000A7 0.01
    bBufferCOLDATA_1 .byte ? ; $0000A8 0.01
    bBufferCOLDATA_2 .byte ? ; $0000A9 0.01
    bBufferCOLDATA_3 .byte ? ; $0000AA 0.01
    bBufferSETINI    .byte ? ; $0000AB 0.01

  .endvirtual

  .virtual $0000BC

    bBufferNMITIMEN .byte ? ; $0000BC 0.01
    bBufferVTIMEL   .byte ? ; $0000BD 0.01
    bBufferVTIMEH   .byte ? ; $0000BE 0.01
    bBufferHTIMEL   .byte ? ; $0000BF 0.01
    bBufferHTIMEH   .byte ? ; $0000C0 0.01
    bBufferHDMAEN   .byte ? ; $0000C1 0.01
    bBufferMEMSEL   .byte ? ; $0000C2 0.01

  .endvirtual

  .virtual $0000D3

    ; These are used for NMI and IRQ
    ; interrupts.

    wVBlankPointer            .word ? ; $0000D3 0.02
      ; This is a short pointer to a routine
      ; in bank $80 to run every VBlank.
    wIRQPointer               .word ? ; $0000D5 0.02
      ; This is a short pointer to a routine
      ; in bank $80 to run during an IRQ.
    wMainLoopPointer          .word ? ; $0000D7 0.02
      ; This is a short pointer to a routine
      ; in bank $80 to run every mainloop cycle.
    wVBlankFlag               .word ? ; $0000D9 0.02
      ; When its upper bit is set, don't run
      ; the routine pointed to wVBlankPointer
      ; during this VBlank.
    wVBlankEnabledFramecount  .word ? ; $0000DB 0.02
      ; This is a counter for frames where a
      ; wVBlankPointer routine is run.
    wVBlankDisabledFramecount .word ? ; $0000DD 0.02
      ; This is a counter for frames where a
      ; wVBlankPointer routine is not run.

  .endvirtual

  .virtual $0000E0

    ; These variables are where
    ; joypad inputs are written to.

    wJoyRepeatDelay    .word ? ; $0000E0 0.01
      ; This is the time before
      ; an input is set to automatically
      ; repeat.
    wJoyRepeatInterval .word ? ; $0000E2 0.01
      ; This is the time between
      ; automatically-repeated inputs.
    wJoy1Input         .word ? ; $0000E4 0.01
    wJoy2Input         .word ? ; $0000E6 0.01
      ; These are the inputs
      ; being read from the joypads.
    wJoy1New           .word ? ; $0000E8 0.01
    wJoy2New           .word ? ; $0000EA 0.01
      ; These are the strictly-new
      ; button presses this frame.
    wJoy1Repeated      .word ? ; $0000EC 0.01
    wJoy2Repeated      .word ? ; $0000EE 0.01
      ; These are the buttons that
      ; are being automatically
      ; repeated.
    wJoy1Old           .word ? ; $0000F0 0.01
      ; This is the previous frame's
      ; inputs for joypad 1.
                       .fill 4 ; $0000F2 0.01
    wJoy1RepeatTimer   .word ? ; $0000F6 0.01
      ; This timer is decremented
      ; every frame while a button
      ; combination is held. Starts
      ; at wJoyRepeatDelay and is
      ; reset to wJoyRepeatInterval
      ; when it reaches 0.
    wJoy2Old           .word ? ; $0000F8 0.01
      ; This is the previous frame's
      ; inputs for joypad 2.
                       .fill 4 ; $0000FA 0.01
    wJoy2RepeatTimer   .word ? ; $0000FE 0.01
      ; This timer is decremented
      ; every frame while a button
      ; combination is held. Starts
      ; at wJoyRepeatDelay and is
      ; reset to wJoyRepeatInterval
      ; when it reaches 0.

    ; These are the buffers for
    ; palettes, which are copied
    ; to PalRAM.

    aBGPaletteBuffer .block      ; $000100 0.01
      aPalette0 .dstruct Palette ; $000100 0.01
      aPalette1 .dstruct Palette ; $000120 0.01
      aPalette2 .dstruct Palette ; $000140 0.01
      aPalette3 .dstruct Palette ; $000160 0.01
      aPalette4 .dstruct Palette ; $000180 0.01
      aPalette5 .dstruct Palette ; $0001A0 0.01
      aPalette6 .dstruct Palette ; $0001C0 0.01
      aPalette7 .dstruct Palette ; $0001E0 0.01
    .endblock

    aOAMPaletteBuffer .block     ; $000200 0.01
      aPalette0 .dstruct Palette ; $000200 0.01
      aPalette1 .dstruct Palette ; $000220 0.01
      aPalette2 .dstruct Palette ; $000240 0.01
      aPalette3 .dstruct Palette ; $000260 0.01
      aPalette4 .dstruct Palette ; $000280 0.01
      aPalette5 .dstruct Palette ; $0002A0 0.01
      aPalette6 .dstruct Palette ; $0002C0 0.01
      aPalette7 .dstruct Palette ; $0002E0 0.01
    .endblock

    ; These affect control flow for menus,
    ; although their exact purpose is
    ; currently unknown.

    wUnknown000300 .word ?                 ; $000300 0.01
    wUnknown000302 .word ?                 ; $000302 0.01
    wUnknown000304 .word ?                 ; $000304 0.01
    lUnknown000306 .long ?                 ; $000306 0.01
    aUnknown000309 .fill (size(long) * 16) ; $000309 0.01

    ; These are settings for various screen
    ; fading routines.

    wScreenFadingTimeIncrement .word ? ; $000339 0.01
      ; This is the number of frames
      ; between each change in intensity.
    wScreenFadingTimer         .word ? ; $00033B 0.01
      ; This is the current number
      ; of frames until the next change
      ; in intensity.
    wScreenFadingFlag          .word ? ; $00033D 0.01
      ; This flag is cleared while
      ; fading is in progress and
      ; is set to -1 when fading
      ; is complete.
    wScreenFadingProcInput     .word ? ; $00033F 0.01
      ; This value is used as the input
      ; for the wScreenFadingTimeIncrement
      ; when creating fading procs.

    ; These variables make up
    ; a system for queuing DMA
    ; transfers.

    bDMAPendingChannels .byte ?       ; $000341 0.01
      ; This variable holds the
      ; pending DMA channels that
      ; need to be transfered.
    bHDMAPendingChannels .byte ?      ; $000342 0.01
      ; This variable holds the
      ; pending HDMA channels that
      ; need to be transfered.
    wDMAArrayPosition .word ?         ; $000343 0.01
      ; This contains the offset
      ; of the next free entry in
      ; the aDMAArray.
    bDMAArrayFlag .byte ?             ; $000345 0.01
      ; This variable is nonzero
      ; if there are DMA entries waiting
      ; to be transfered in aDMAArray.
    aDMAArray .fill $100              ; $000346 0.01
      ; This is an array of DMA
      ; structs of various sizes.

    ; These variables make up
    ; a system for queuing up
    ; data to be decompressed.

    wDecompressionArrayPosition .word ? ; $000446 0.01
      ; This contains the offset
      ; of the next free entry in
      ; the aDecompressionArray.
    bDecompressionArrayFlag .byte ?     ; $000448 0.01
      ; This variable is nonzero
      ; if there are decompression
      ; entries waiting to be
      ; decompressed.
    aDecompressionArray .fill $20       ; $000449 0.01
      ; This is an array of
      ; structDecompressionEntry

    ; These variables manage
    ; random numbers.

    bFrameCounterByOnes .byte ?   ; $000469 0.01
      ; This is a counter that is
      ; incremented by one every frame
      ; on most frames. Exceptions
      ; are undocumented. Overflows
      ; rather than being reset.
    bFrameCounterByThrees .byte ? ; $00046A 0.01
      ; This is a counter that is
      ; incremented by three every frame
      ; on most frames. Exceptions
      ; are undocumented. Overflows
      ; rather than being reset.
    aRNArray .fill 55             ; $00046B 0.01
      ; This is an array of 55
      ; pseudo-random numbers.
    wRNIndex .word ?              ; $0004A2 0.01
      ; This is the index
      ; of the last fetched RN
      ; in aRNArray.
    bRNShuffleVar1 .byte ?        ; $0004A4 0.01
    bRNShuffleVar2 .byte ?        ; $0004A5 0.01
      ; These variables are used
      ; to generate aRNArray.

    ; These are for use with two
    ; block memory transfer routines.

    lBlockCopySource .long ?      ; $0004A6 0.01
      ; This is a long pointer
      ; to the source data.
    lBlockCopyDestination .long ? ; $0004A9 0.01
      ; This is a long pointer
      ; to the destination.
    wBlockCopySize .word ?        ; $0004AC 0.01
      ; This is the size in bytes
      ; of the data to transfer.
    rsBlockCopyMVNRAM .block      ; $0004AE 0.01
      mvn #$00,#$00
      rts
    .endblock
      ; This is a block memory copy
      ; routine that is copied to RAM
      ; and has the parameters of the
      ; mvn opcode modified to fit the
      ; source and destination.
    rsBlockCopyMVPRAM .block      ; $0004B2 0.01
      mvp #$00,#$00
      rts
    .endblock
      ; This is a block memory copy
      ; routine that is copied to RAM
      ; and has the parameters of the
      ; mvp opcode modified to fit the
      ; source and destination.

    ; These variables are for managing
    ; the sound system.

    aSoundSystem .block                                 ; $0004B6 0.01
      .union
        ; Temporarily filled until contents
        ; are understood.
        .fill $70
        .struct
          wOffset .word ?                               ; $0004B6 0.01
            ; This is the lower 16 bits
            ; of a long pointer to the
            ; beginning of sound system data.
          wBank .word ?                                 ; $0004B8 0.01
            ; This is the upper 8 bits
            ; of a long pointer to the
            ; beginning of sound system data.
            ; It is shifted 8 bits such
            ; that it occupies the upper
            ; byte in this word.
          aUnknown0004BA .fill (size(word) * 2)         ; $0004BA 0.01
            ; Needs research. Seems to be
            ; two song IDs and status bits
            ; for each. Difference between
            ; the two is unknown.
          aSongDataCurrentOffset .fill (size(word) * 2) ; $0004BE 0.01
            ; Needs research. Used as an offset
            ; into some kind of data for the
            ; songs specified by aUnknown0004BA.
          aUnknown0004C2 .fill (size(word) * 2)         ; $0004C2 0.01
            ; Needs research. Used as a counter
            ; for going through the song data
            ; at aSongDataCurrentOffset.
          aUnknown0004C6 .fill (size(word) * 2)         ; $0004C6 0.01
            ; Needs research. Seems like a
            ; mirror of aUnknown0004BA and
            ; is used to prevent resetting
            ; song data read progress if the
            ; same song ID is written to
            ; aUnknown0004BA.
          aUnknown0004CA .fill (size(word) * 3)         ; $0004CA 0.01
          aUnknown0004D0 .fill (size(word) * 3)         ; $0004D0 0.01
          aSoundQueue1 .fill (size(word) * 5)           ; $0004D6 0.01
            ; This is a queue of three sound(?)
            ; IDs/parameters that will be fed to the
            ; sound system in order. This one is
            ; for single note (?) sounds.
          aSoundQueue2 .fill (size(word) * 5)           ; $0004E0 0.01
            ; This is a queue of three sound(?)
            ; IDs/parameters that will be fed to the
            ; sound system in order. This one is
            ; for multiple note (?) sounds.

          .fill ($0004EA - *)

          wStatus .word ? ; $0004EA 0.22

          .fill ($0004F0 - *)

          wUnknown0004F0 .word ? ; $0004F0 0.17

          .fill ($0004FD - *)

          bUnknown0004FD .byte ? ; $0004FD 0.17
          aUnknown0004FE .fill (size(byte) * 2) ; $0004FE 0.17

          .fill ($00050C - *)

          wUnknown00050C .word ? ; $00050C 0.17
          wUnknown00050E .word ? ; $00050E 0.17

        .endstruct
      .endunion
    .endblock

    ; These are for managing the proc
    ; system, which is used for
    ; multitasking.

    aProcSystem .block                            ; $000526 0.01
      wFlag .word ?                               ; $000526 0.01
        ; This is set to $8000
        ; while the proc system is
        ; running.
      wOffset .word ?                             ; $000528 0.01
        ; This is the offset
        ; of the currently-active
        ; proc.
      lPointer .long ?                            ; $00052A 0.01
        ; This is used to hold a pointer
        ; to routines or proc code
        ; used when initializing a proc,
        ; running its on-cycle routine, or
        ; running its proc code.
      wInput0 .word ?                             ; $00052D 0.01
      wInput1 .word ?                             ; $00052F 0.01
      wInput2 .word ?                             ; $000531 0.01
      wInput3 .word ?                             ; $000533 0.01
      wInput4 .word ?                             ; $000535 0.01
      wInput5 .word ?                             ; $000537 0.01
      wInput6 .word ?                             ; $000539 0.01
      wInput7 .word ?                             ; $00053B 0.01
        ; These are used to pass
        ; parameters into a proc's
        ; init routine.
      aHeaderTypeOffset .fill (size(word) * 16)   ; $00053D 0.01
        ; This is the lower 16 bits of the
        ; pointer to a proc's proc info in
        ; the ROM. A slot in the proc system
        ; is considered free when this is zero.
      aHeaderTypeBank .fill (size(word) * 16)     ; $00055D 0.01
        ; This is the upper 8 bits of the
        ; pointer to a proc's proc info in
        ; the ROM.
      aHeaderName .fill (size(word) * 16)         ; $00057D 0.01
        ; This is a two-byte field that usually
        ; contains a two-character name for a proc.
        ; Names are not unique to each proc type.
        ; There are many procs with the name "  "
        ; or "xx". "xx" procs often seem to be
        ; destructors, but more research is needed.
        ; Some procs, such as procs that handle portraits,
        ; use numbers in their names (ex: x"\x00@"
        ; for the first (zeroth) portrait).
        ; There is a proc code instruction that
        ; uses this name field to temporarily store
        ; the proc code execution offset.
      aHeaderBitfield .fill (size(word) * 16)     ; $00059D 0.01
        ; Needs research. This status bitfield
        ; controls proc execution.
      aHeaderOnCycle .fill (size(word) * 16)      ; $0005BD 0.01
        ; This is the lower 16 bits of a pointer
        ; to a routine to execute on every proc
        ; cycle that the proc is active. The bank
        ; is taken from aHeaderTypeBank.
      aHeaderCodeOffset .fill (size(word) * 16)   ; $0005DD 0.01
        ; This is the lower 16 bits of a pointer
        ; to an array of proc code instructions
        ; to be executed on every proc cycle that
        ; the proc is active. The bank is taken from
        ; aHeaderTypeBank.
      aHeaderSleepTimer .fill (size(word) * 16)   ; $0005FD 0.01
        ; This is a counter for proc cycles
        ; between executing proc code.
      aHeaderUnknownTimer .fill (size(word) * 16) ; $00061D 0.01
        ; This timer is used by proc code
        ; in a similar manner to aHeaderSleepTimer
        ; but must be manually set/decremented by
        ; proc code.
      aBody0 .fill (size(word) * 16)              ; $00063D 0.01
      aBody1 .fill (size(word) * 16)              ; $00065D 0.01
      aBody2 .fill (size(word) * 16)              ; $00067D 0.01
      aBody3 .fill (size(word) * 16)              ; $00069D 0.01
      aBody4 .fill (size(word) * 16)              ; $0006BD 0.01
      aBody5 .fill (size(word) * 16)              ; $0006DD 0.01
      aBody6 .fill (size(word) * 16)              ; $0006FD 0.01
      aBody7 .fill (size(word) * 16)              ; $00071D 0.01
        ; These variables are to be filled with
        ; whatever information a proc needs to keep.
      aUnknownBitfield .fill (size(word) * 16)    ; $00073D 0.01
        ; Needs research. This status bitfield is
        ; similar to aHeaderBitfield but its use is
        ; unknown.
    .endblock

    ; These are for managing certain map sprite actions.

    aActiveSpriteSystem .block               ; $00075D 0.01
      wFlag .word ?                          ; $00075D 0.01
        ; This is a bitfield for managing
        ; the active sprite system.
      wOffset .word ?                        ; $00075F 0.01
        ; This is the offset
        ; of the currently-active
        ; sprite.
      lPointer .long ?                       ; $000761 0.01
        ; This is used to hold a pointer
        ; to routines or code
        ; used when initializing a sprite,
        ; running its on-cycle routine, or
        ; running its code.
      aTypeOffset .fill (size(word) * 16)    ; $000764 0.01
      aBanks .fill (size(word) * 16)         ; $000784 0.01
      aRenderer .fill (size(word) * 16)      ; $0007A4 0.01
      aUpdater .fill (size(word) * 16)       ; $0007C4 0.01
      aOnCycle .fill (size(word) * 16)       ; $0007E4 0.01
      aFrameTimer .fill (size(word) * 16)    ; $000804 0.01
      aCodeOffset .fill (size(word) * 16)    ; $000824 0.01
      aFrameOffset .fill (size(word) * 16)   ; $000844 0.01
      aUnknown000864 .fill (size(word) * 16) ; $000864 0.01
      aXCoordinate .fill (size(word) * 16)   ; $000884 0.01
      aUnknown0008A4 .fill (size(word) * 16) ; $0008A4 0.01
      aYCoordinate .fill (size(word) * 16)   ; $0008C4 0.01
      aSpriteBase .fill (size(word) * 16)    ; $0008E4 0.01
      aUnknown000904 .fill (size(word) * 16) ; $000904 0.01
      aPalette .fill (size(word) * 16)       ; $000924 0.01
      aUnknown000944 .fill (size(word) * 16) ; $000944 0.01
      aUnknown000964 .fill (size(word) * 16) ; $000964 0.01
      aUnknown000984 .fill (size(word) * 16) ; $000984 0.01
      aUnknown0009A4 .fill (size(word) * 16) ; $0009A4 0.01
      aUnknown0009C4 .fill (size(word) * 16) ; $0009C4 0.01
      aUnknown0009E4 .fill (size(word) * 16) ; $0009E4 0.01
      aUnknown000A04 .fill (size(word) * 16) ; $000A04 0.01
      aUnknown000A24 .fill (size(word) * 16) ; $000A24 0.01
      aUnknown000A44 .fill (size(word) * 16) ; $000A44 0.01
      aUnknown000A64 .fill (size(word) * 16) ; $000A64 0.01
    .endblock

  .endvirtual

  .virtual $000C6D

    aHDMASystem .block                   ; $000C6D 0.22
      wFlag .word ?                      ; $000C6D 0.22
        ; Presumably this is a flag that would disable the
        ; HDMA system, much like the proc system, but this value
        ; is only ever cleared and not read.
      wOffset .word ?                    ; $000C6F 0.22
        ; This is the offset of the currently running
        ; HDMA entry.
      lPointer .long ?                   ; $000C71 0.22
        ; This is used to hold a pointer
        ; to routines or HDMA entry code
        ; used when initializing an HDMA entry,
        ; running its on-cycle routine, or
        ; running its HDMA entry code.
      bPendingChannels .byte ?           ; $000C74 0.22
        ; This holds the pending HDMA channels that
        ; need to be transferred.
      aTypeOffset .fill (size(word) * 8) ; $000C75 0.22
        ; This is the lower word of the pointer
        ; to an HDMA entry's info struct in the ROM.
        ; A slot in the HDMA system is considered free
        ; when this is zero.
      aTypeBank .fill (size(word) * 8)   ; $000C85 0.22
        ; This is the bank byte of the pointer
        ; to an HDMA entry's info struct in the ROM.
      aBitfield .fill (size(word) * 8)   ; $000C95 0.22
        ; This is a status bitfield that controls
        ; the HDMA entry. More research is needed.
      aOnCycle .fill (size(word) * 8)    ; $000CA5 0.22
        ; This is the lower word of a pointer to
        ; an assembly routine to execute on every cycle
        ; that the HDMA entry is active. The bank for the
        ; routine is taken from aTypeBank.
      aCodeOffset .fill (size(word) * 8) ; $000CB5 0.22
        ; This is the lower word of a pointer
        ; to the current HDMA entry code instruction
        ; that will be executed while the HDMA entry is
        ; active. The bank for the pointer is taken
        ; from aTypeBank.
      aSleepTimer .fill (size(word) * 8) ; $000CC5 0.22
        ; This is a timer that ticks down once per
        ; HDMA system cycle that prevents HDMA entry code
        ; from being run while nonzero.
      aTimer .fill (size(word) * 8)      ; $000CD5 0.22
        ; This is a timer that is written to, read by, and
        ; decremented by HDMA entry code.
      aOffset .fill (size(word) * 8)     ; $000CE5 0.22
        ; This is the lower word of a pointer to an HDMA table.
        ; The format of the HDMA table depends on whether
        ; the HDMA mode is Direct or Indirect. If Direct,
        ; each entry in this table consists of an NTRL setting
        ; byte and then the data to be transferred to the selected
        ; register. In Indirect mode, each entry is an NTRL setting
        ; followed by the lower word of a pointer to the data
        ; to be transferred. The bank for the pointer is given
        ; by aDMAPxAndIndirectBank.bIndirectBank.
      aBankAndBBADx .brept 8             ; $000CF5 0.22
        bBank .byte ?                    ; $000CF5 0.22
          ; This is the bank of the HDMA table for the netry.
          ; See aOffset.
        bBBADx .byte ?                   ; $000CF6 0.22
          ; This is the BBADx setting for the entry,
          ; which is the lower byte of the address
          ; of a PPU register to write to.
        .endrept
      aDMAPxAndIndirectBank .brept 8     ; $000D05 0.22
        bDMAPx .byte ?                   ; $000D05 0.22
          ; This is the DMAPx setting for the HDMA entry.
          ; It seems like some HDMA entries are doing
          ; weird things like setting the A-bus step.
          ; Needs more research.
        bIndirectBank .byte ?            ; $000D06 0.22
          ; This is the bank byte of the pointers given by
          ; HDMA table entries in Indirect mode.
        .endrept
    .endblock

  .endvirtual

  .virtual $000DDE

    aCurrentTilemapInfo .block ; $000DDE 0.22

      ; I don't know precisely where this begins.

      lInfoPointer .long ?     ; $000DDE 0.22
        ; This is a long pointer to a structTilemapInfo.
        ; It's used to get the main info about the tilemap.

      .fill (size(long) * 2)

      wBaseTile .word ?        ; $000DE7 0.22
        ; This is a TilemapEntry that gets added to entries
        ; that are written to this tilemap. It's used to apply
        ; things like starting tile indices, palettes, etc.
      wFillTile .word ?        ; $000DE9 0.22
        ; This is a TilemapEntry that is used for blank tiles.
      wIgnoreTile .word ?      ; $000DEB 0.22
        ; This is a TilemapEntry that is used to specify that
        ; a TilemapEntry from the source should not overwrite
        ; the corresponding entry in the destination.

    .endblock

  .endvirtual

  .virtual $000E05

    wIngameTime .word ?            ; $000E05 0.01
      ; This value ticks up once
      ; per frame for every frame
      ; the screen is enabled.
    wMenuCounter .word ?           ; $000E07 0.01
      ; Needs research. This is some
      ; kind of counter for certain
      ; actions on the map.
    wWinCounter .word ?            ; $000E09 0.01
      ; This is the total number
      ; of wins on the current save file.
    wCaptureCounter .word ?        ; $000E0B 0.01
      ; This is the total number
      ; of captures on the current save file.
    wParagonModeEnable .word ?     ; $000E0D 0.01
      ; This is set to 1 if
      ; paragon mode is enabled.
    wCursorCycleTimer .word ?      ; $000E0F 0.01
      ; This value is used to track
      ; things like cursor bobbing.
    wCurrentChapter .word ?        ; $000E11 0.01
      ; This is the current chapter
      ; number. This is set to a
      ; special chapter number during
      ; world map events.
    wCurrentTurn .word ?           ; $000E13 0.01
      ; This is the current turn.
    wCurrentPhase .word ?          ; $000E15 0.01
      ; This is the current phase.
    wDefaultVisibilityFill .word ? ; $000E17 0.01
      ; This is actually a byte that
      ; is duplicated for the high and
      ; low bytes. This value is used
      ; to fill the visibility map.
    wVisionRange .word ?           ; $000E19 0.01
      ; This is the default vision range
      ; during fog. Set to 0 when there
      ; is no fog.
    wSaveSlotOffset .word ?        ; $000E1B 0.01
      ; This is the offset in SRAM where
      ; the current save is stored.
    wUnknown000E1D .word ?         ; $000E1D 0.01
    wUnknown000E1F .word ?         ; $000E1F 0.01
    wChapterBoss .word ?           ; $000E21 0.01
      ; This is the character ID of
      ; the chapter's boss.
    wUnknown000E23 .word ?         ; $000E23 0.01
      ; Needs research. Seems like an
      ; action index for phases.
    wUnknown000E25 .word ?         ; $000E25 0.01
      ; Needs research. Seems like
      ; an action index when on the map.
    wUnknown000E27 .word ?         ; $000E27 0.01
    wPrepScreenFlag .word ?        ; $000E29 0.01
      ; This is set to 1 when there
      ; is a chapter preparation screen.
    wUnknown000E2B .word ?         ; $000E2B 0.01
    wCurrentMapMusic .word ?       ; $000E2D 0.01
      ; This is the song ID of the
      ; current map music.

    ; These variables are for map-related things.

    wMapWidthMetatiles .word ?           ; $000E2F 0.01
    wMapHeightMetatiles .word ?          ; $000E31 0.01
      ; These are the size of the map
      ; in 16x16 pixel metatiles.
    wMapWidthPixels .word ?              ; $000E33 0.01
    wMapHeightPixels .word ?             ; $000E35 0.01
      ; These are the size of the map
      ; in pixels.
    wMapScrollXMetatiles .word ?         ; $000E37 0.01
    wMapScrollYMetatiles .word ?         ; $000E39 0.01
      ; These are the current scroll amounts
      ; in 16x16 pixel metatiles. These are
      ; only updated during certain actions.
    wMapScrollXPixels .word ?            ; $000E3B 0.01
    wMapScrollYPixels .word ?            ; $000E3D 0.01
      ; These are the current scroll amounts
      ; in pixels. These are updated any time
      ; the map scrolls.
    wMapOffsetXPixels .word ?            ; $000E3F 0.01
    wMapOffsetYPixels .word ?            ; $000E41 0.01
    wMapPartialScrollWidthTimer .word ?  ; $000E43 0.01
    wMapPartialScrollHeightTimer .word ? ; $000E45 0.01
    s16MapScrollWidthModifier .sint ?    ; $000E47 0.01
    s16MapScrollHeightModifier .sint ?   ; $000E49 0.01
    wCursorTileIndex .word ?             ; $000E4B 0.01
    wCursorXCoord .word ?                ; $000E4D 0.01
    wCursorYCoord .word ?                ; $000E4F 0.01
    wCursorXCoordPixelsScrolling .word ? ; $000E51 0.01
    wCursorYCoordPixelsScrolling .word ? ; $000E53 0.01
    wCursorXCoordPixels .word ?          ; $000E55 0.01
    wCursorYCoordPixels .word ?          ; $000E57 0.01
    wCursorXOffset .word ?               ; $000E59 0.01
    wCursorYOffset .word ?               ; $000E5B 0.01

  .endvirtual

  .virtual $000E67

    wMapTileCount .word ? ; $000E67 0.19
      ; This is the number of tiles in the current map.
    wMapRowSize   .word ? ; $000E69 0.19
      ; This is the width of each row in the map.

  .endvirtual

  .virtual $000E6F

    ; These buffers are for holding
    ; character data temporarily.

    aSelectedCharacterBuffer .dstruct structExpandedCharacterDataRAM    ; $000E6F 0.01
      ; This could probably use a better
      ; name. This is the most commonly-used
      ; character data buffer.
    aTargetingCharacterBuffer .dstruct structExpandedCharacterDataRAM   ; $000EB3 0.01
      ; This could probably use a better
      ; name. This buffer is used
      ; during some targeting routines.
    aBurstWindowCharacterBuffer .dstruct structExpandedCharacterDataRAM ; $000EF7 0.01
      ; This could probably use a better
      ; name. This buffer is used when
      ; drawing the burst window.

    ; This buffer holds item data
    ; temporarily.

    aItemDataBuffer .dstruct structItemDataEntryRAM ; $000F3B 0.01

    ; Misc. variables

    bUnknown000F54   .byte ? ; $000F54 0.01
      ; Needs research.
    bMovementCostCap .byte ? ; $000F55 0.01
      ; Needs research. Seems to
      ; be used as the cap for movement
      ; range calculations.

    aTemporaryActionStruct .dstruct structActionStructEntry ; $000F56 0.01
      ; This is used when a character's
      ; full adjusted data (all bonuses, etc.)
      ; is needed.

    aItemSkillCharacterBuffer .dstruct structExpandedCharacterDataRAM ; $000FC7 0.01
      ; Needs a better name. This
      ; is used when determining the
      ; item skills a character
      ; currently has.

  .endvirtual

  .virtual $0015A1

    aMapBattleMapSpriteActiveOffsetArray .fill (2 * size(word)) ; $0015A1 0.02

  .endvirtual

  .virtual $0015BF

    aMapBattleRangedFlag .word ?                                    ; $0015BF 0.02
    aMapBattleMapSpriteIndexArray .fill (2 * size(word))            ; $0015C1 0.02
    aMapBattleActionStructArray .fill (2 * size(addr))              ; $0015C5 0.02
    aMapBattleDirectionArray .fill (2 * size(word))                 ; $0015C9 0.02
    aMapBattleXCoordArray .fill (2 * size(word))                    ; $0015CD 0.02
    aMapBattleYCoordArray .fill (2 * size(word))                    ; $0015D1 0.02
    aMapBattleTargetXCoordArray .fill (2 * size(word))              ; $0015D5 0.02
    aMapBattleTargetYCoordArray .fill (2 * size(word))              ; $0015D9 0.02
    aMapBattleWeaponAndWeaponTypeArray .fill (2 * (2 * size(byte))) ; $0015DD 0.02
    aMapBattleWeaponArray .fill (2 * size(word))                    ; $0015E1 0.02
    aMapBattleActiveSpriteIndexArray .fill (2 * size(word))         ; $0015E5 0.02

  .endvirtual

  .virtual $00172C

    ; Event engine variables

    wEventEngineStatus .word ? ; $00172C 0.01
      ; This is a status bitfield
      ; that controls the event engine.

    wEventEngineCycleType .word ? ; $00172E 0.17
      ; This controls the handling of event
      ; engine cycles.
    wEventEngineMapChangeFlag .word ? ; $001730 0.17
      ; This is nonzero if the event engine is
      ; currently checking/running events for
      ; map changes that have already occurred,
      ; such as after loading a suspended save
      ; after triggering map changes. You can
      ; check against this to avoid running events
      ; like dialogue at this time.

  .endvirtual

  .virtual $001734

    wEventEngineCharacterStructParameter .word ?                  ; $001734 0.03
      ; This is used as a parameter for
      ; events that access the character data
      ; struct. It is set to the struct field
      ; offset that is being accessed.
    wEventEngineCharacterTarget .word ?                           ; $001736 0.03
      ; This is used as a parameter for
      ; events that search for or affect
      ; units with a specific character ID.
    wEventEngineXCoordinate .word ?                               ; $001738 0.03
    wEventEngineYCoordinate .word ?                               ; $00173A 0.03
      ; These are used as parameters
      ; for events that target specific
      ; coordinates.
    wEventEngineXCoordinateAlt .word ?                            ; $00173C 0.03
    wEventEngineYCoordinateAlt .word ?                            ; $00173E 0.03
      ; Similar to wEventEngineXCoordinate
      ; and wEventEngineYCoordinate, used
      ; rarely if an event needs two
      ; pairs of coordinates.
    wEventEngineParameter1 .word ?                                ; $001740 0.03
    wEventEngineParameter2 .word ?                                ; $001742 0.03
    wEventEngineParameter3 .word ?                                ; $001744 0.03
      ; These are used as general
      ; purpose parameters for events.
    lEventEngineLongParameter .long ?                             ; $001746 0.18
      ; This is a general purpose
      ; long parameter for events.
    wEventEngineSavedTile .word ?                                 ; $001749 0.03
      ; This is set to the map
      ; metatile of the original
      ; tile of the single tile change
      ; when using rlASMCSingleTileChangeSaved.
    wEventEngineTruthFlag .word ?                                 ; $00174B 0.03
      ; Used as a return value for events.
      ; Zero if false, nonzero if true.
    aEventCharacterBuffer .dstruct structExpandedCharacterDataRAM ; $00174D 0.03
      ; This is rarely written to internally
      ; by events.

  .endvirtual

  .virtual $001791

    wEventEngineUnknown001791 .sint ?    ; $001791 0.19
    wEventEngineOffset .word ?           ; $001793 0.19
    lEventEngineStartPointer .long ?     ; $001795 0.19
    lEventEngineUnitGroupPointer .long ? ; $001798 0.13
    bEventEngineUnitLoadingFlag .byte ?  ; $00179B 0.13

  .endvirtual

  .virtual $0017E9

    wDialogueEngineStatus .word ? ; $0017E9 0.14
      ; This is a status bitfield
      ; that controls the dialogue engine.
    wDialogueEngineControlCodeExecutionStep .word ? ; $0017EB 0.14
      ; This is an index into a control code's
      ; handler table.

  .endvirtual

  .virtual $0017F9

    bDialogueEngineFontPage .byte ? ; $0017F9 0.14
      ; This is the current font page being
      ; used to draw dialogue characters.
    wDialogueEngineCurrentCharacterIndex .word ? ; $0017FA 0.14
    wDialogueEngineCurrentPixelWidth .word ? ; $0017FC 0.14
    wDialogueEngineTotalPixelWidth .word ? ; $0017FE 0.14

  .endvirtual

  .virtual $001804

    wDialogueEngineTileBase .word ? ; $001804 0.14

  .endvirtual

  .virtual $001808

    wDialogueEngineTargetIndex .word ? ; $001808 0.14
    lDialogueEngineTextPointer .long ? ; $00180A 0.14

  .endvirtual

  .virtual $00182E

    wDialogueEnginePendingDMAChunkSize .word ? ; $00182E 0.19
    wDialogueEngineLastCharacterTileSlice .word ? ; $001830 0.19

  .endvirtual

  .virtual $001982

    lBattleAnimationScriptPointer .long ? ; $001982 0.03

  .endvirtual

  .virtual $001993

    lBattleAnimationSubsheetPointer .long ? ; $001993 0.03

  .endvirtual

  .virtual $001AA1

    wBattleAnimationUnit1TerrainBackground .word ? ; $001AA1 0.03
    wBattleAnimationUnit2TerrainBackground .word ? ; $001AA3 0.03
    bBattleAnimationDistanceBetweenUnits .byte ?   ; $001AA5 0.03
    wBattleAnimationStartingExperience .word ?     ; $001AA6 0.03
    wBattleAnimationGainedExperience .word ?       ; $001AA8 0.03
    bBattleAnimationEndLevel .byte ?               ; $001AAA 0.03

    aBattleAnimationUnit1Info .block ; $001AAB 0.03
      wClass .word ?                 ; $001AAB 0.03
      wAdjustedCharacter .word ?     ; $001AAD 0.03
        ; This is either the lower byte of the
        ; unit's character ID or it is set to a default.
      wCharacter .word ?             ; $001AAF 0.03
      wWeapon .word ?                ; $001AB1 0.03
      wWeaponAfter .word ?           ; $001AB3 0.03
        ; This is the unit's weapon after combat,
        ; with the upper byte being the remaining
        ; durability.
      bHPChangeProgress .byte ?      ; $001AB5 0.03
        ; When a unit's HP is changing, this is
        ; the progress toward the next point.
      bCurrentHP .byte ?             ; $001AB6 0.03
      bMaxHP .byte ?                 ; $001AB7 0.03
      wHPChangeIncrement .word ?     ; $001AB8 0.03
        ; This is the value to change
        ; bHPChangeProgress by every tick.
      bHPChangeTarget .byte ?        ; $001ABA 0.03
        ; This is the target HP for a unit's
        ; HP change.
      bGender .byte ?                ; $001ABB 0.03
      bWeaponStyle .byte ?           ; $001ABC 0.03
        ; This is a packed byte, where the
        ; upper nybble is the battle animation
        ; weapon type, lower nybble is
        ; unknown.
    .endblock

    aBattleAnimationUnit2Info .block ; $001ABD 0.03
      wClass .word ?                 ; $001ABD 0.03
      wAdjustedCharacter .word ?     ; $001ABF 0.03
        ; This is either the lower byte of the
        ; unit's character ID or it is set to a default.
      wCharacter .word ?             ; $001AC1 0.03
      wWeapon .word ?                ; $001AC3 0.03
      wWeaponAfter .word ?           ; $001AC5 0.03
        ; This is the unit's weapon after combat,
        ; with the upper byte being the remaining
        ; durability.
      bHPChangeProgress .byte ?      ; $001AC7 0.03
        ; When a unit's HP is changing, this is
        ; the progress toward the next point.
      bCurrentHP .byte ?             ; $001AC8 0.03
      bMaxHP .byte ?                 ; $001AC9 0.03
      wHPChangeIncrement .word ?     ; $001ACA 0.03
        ; This is the value to change
        ; bHPChangeProgress by every tick.
      bHPChangeTarget .byte ?        ; $001ACC 0.03
        ; This is the target HP for a unit's
        ; HP change.
      bGender .byte ?                ; $001ACD 0.03
      bWeaponStyle .byte ?           ; $001ACE 0.03
        ; This is a packed byte, where the
        ; upper nybble is the battle animation
        ; weapon type, lower nybble is
        ; unknown.
    .endblock

    .word ? ; $001ACF 0.23

    wTemporaryDeploymentInfo .word ? ; $001AD1 0.23
      ; This is either a deployment number (during animations-on battles)
      ; or a short pointer to a deployment slot (on the unit window)
    lTemporaryNamePointer .long ? ; $001AD3 0.23
      ; This holds a long pointer to menu text
      ; when drawing character, class, and item
      ; names on the unit window.
    wTemporaryUnitWindowCounter .word ? ; $001AD6 0.23
      ; This is a counter used when getting unit info
      ; for the holdover FE4 unit window code.

    .fill 6

    wTemporaryUnitWindowSkillCounter .word ? ; $001ADE 0.23
      ; This is used as a counter when getting/drawing
      ; skills on the unit window.

    aTemporaryUnitWindowSkillList .fill 22 * size(byte) ; $001AE0 0.23
      ; This is a list of slots for skills drawn on the
      ; unit window. The number of nonzero entries denotes
      ; how many displayable skills a unit has.

    wTemporaryUnitWindowItem .word ? ; $001AF6 0.23
      ; This is an item ID used on the unit window
      ; to draw a unit's equipped weapon.

  .endvirtual

  .virtual $001C00

    ; These are a sprite buffer that
    ; is copied to OAM every frame.

    aSpriteBuffer .fill (128 * size(structPPUOAMEntry)) ; $001C00 0.01
      ; This is a buffer of sprite data.
      ; The upper bit of the X coordinate
      ; and the sprite size are stored
      ; within aSpriteExtBuffer.
    aSpriteExtBuffer .fill ((128 * 2) / 8)              ; $001E00 0.01
      ; This is a buffer of 128 two-bit
      ; pairs, with each byte filled from
      ; least-significant bit to most-
      ; significant bit with the pattern:
      ; X-coordinate upper bit, size bit.
    wNextFreeSpriteOffset .word ?                       ; $001E20 0.01
      ; This is the offset of the next
      ; free sprite in aSpriteBuffer.
    wUnknown001E22 .word ?                              ; $001E22 0.01

    ; This is the space allotted to the stack.

    aStackSpace .block                      ; $001E24 0.02
      aTop .fill ($001FF8 - size(byte) - *) ; $001E24 0.02
      bFirstFree .byte ?                    ; $001FF7 0.02
      aBottom                               ; $001FF8 0.02
    .endblock

    ; These are for identifying the engine
    ; and are used on reset.

    aEngineUnknown .fill 4 ; $001FF8 0.02
    aEngineName    .fill 4 ; $001FFC 0.02

  .endvirtual

  .virtual $7E4000

    ; AI-related variables

    wAIEngineCycleType    .word ?          ; $7E4000 0.19
      ; This is the current AI engine cycle.
    wAIEngineStatus       .word ?          ; $7E4002 0.19
      ; This is a status flag for when the
      ; AI engine is currently doing something.
    wAIEngineStackPointer .word ?          ; $7E4004 0.19
      ; At the start of every AI engine cycle,
      ; the AI engine saves the current stack
      ; pointer here.
    wAIEngineCycleDeploymentNumber .word ? ; $7E4006 0.19
      ; This is the deployment number of
      ; the unit being handled during a cycle.
    wAITemp7E4008 .word ?                  ; $7E4008 0.19
    wAITemp7E400A .word ?                  ; $7E400A 0.19
    wAITemp7E400C .word ?                  ; $7E400C 0.19
    wAITemp7E400E .word ?                  ; $7E400E 0.19
    wAITemp7E4010 .word ?                  ; $7E4010 0.19

    wAILeastThreatenedTileThreatCount .word ? ; $7E4012 0.19
      ; This is the number of units that can threaten
      ; the tile with the fewest units that can threaten it.
    wAIThreatMask .word ?                     ; $7E4014 0.19
      ; This is either 0000 or FFFF, depending if
      ; the unit's selected AI byte has its upper
      ; bit unset or set, respectively.
    wAICurrentBestTarget .word ?              ; $7E4016 0.19
      ; This is the (current) best target for some AI
      ; action, like healing, stealing, etc.

    wAITemp7E4018 .word ? ; $7E4018 0.21

    bAIPathCounter .byte ? ; $7E401A 0.19
      ; This is used as a counter when refilling the movement map
      ; after failing to find a route? Needs research.

    wAITemp7E401B .word ? ; $7E401B 0.19
      ; Multipurpose, normally the current AI script
      ; index for the type of script being interpreted.
    wAITemp7E401D .word ? ; $7E401D 0.19
    wAITemp7E401F .word ? ; $7E401F 0.19
    wAITemp7E4021 .word ? ; $7E4021 0.19
    wAITemp7E4023 .word ? ; $7E4023 0.21
    wAITemp7E4025 .word ? ; $7E4025 0.21

  .endvirtual

  .virtual $7E4029

    aAISelectedUnitInfo .block        ; $7E4029 0.19
      bDeploymentNumber .byte ?       ; $7E4029 0.19
      bStartXCoordinate .byte ?       ; $7E402A 0.19
      bStartYCoordinate .byte ?       ; $7E402B 0.19
        ; These are the starting coordinates of the current
        ; AI engine unit.
      bDestinationXCoordinate .byte ? ; $7E402C 0.19
      bDestinationYCoordinate .byte ? ; $7E402D 0.19
        ; These are the destination coordinates of the current
        ; AI engine unit's decided action.
      bActionDecision .byte ?         ; $7E402E 0.19
        ; This contains the action that the AI decided
        ; the unit will take. Possible values:
        ;   00 - Move
        ;   01 - Attack, trade, ??
        ;   02 - Staff
        ;   03 - Item
        ;   05 - Flee
        ;   06 - Path is blocked?
        ;   07 - Talk
        ;   08 - Steal
        ;   0C - Buy from shop
        ;   0D - Dance
      aDecisionParameters .brept 4     ; $7E402F 0.19
        ; These are filled with information
        ; about an AI decision, such as coordinates
        ; for Warp stave casts, etc.
        .byte ?
      .endrept
      bDecisionDistance .byte ?       ; $7E4033 0.19
        ; This is the distance between the unit and
        ; their destination.
    .endblock
    wAITemp7E4034 .word ?             ; $7E4034 0.19
    wAITemp7E4036 .word ?             ; $7E4036 0.19
    wAITemp7E4038 .word ?             ; $7E4038 0.19
    wAITemp7E403A .word ?             ; $7E403A 0.19
    wAIBuiltThreatMapFlag .word ?     ; $7E403C 0.19
      ; Nonzero if the threatened tile map has already
      ; been built.
    lAIParameterRoutine .long ?       ; $7E403E 0.19

    wAIUnitPriority .word ? ; $7E4041 0.19

    wAIStationaryFlag .sint ? ; $7E4043 0.19
      ; -1 if unit has a stationary AI, 0 otherwise.

    wAIAlternateDeploymentListIndex .word ?   ; $7E4045 0.21
      ; Like aAIMainVariables.wCurrentDeploymentListIndex but
      ; for berserked units and group AI?
    wAIBerserkedActorFlag .word ?             ; $7E4047 0.21
      ; Nonzero when the AI is processing berserked units.
    wAIActionCapabilityBitfield .word ?       ; $7E4049 0.19
      ; This is a bitfield for actions that
      ; a selected AI engine unit can perform.
      ; Possible values:
      ;   0001 - can use unlock staff
      ;   0002 - can capture
      ;   0004 - can use a weapon
      ;   0010 - can use pure water
      ;   0020 - can use lockpick
      ;   0040 - can use door keys
      ;   0080 - can use chest keys
      ;   4000 - also door keys?
    wUnknown7E404B .word ?                    ; $7E404B 0.19
    wAIHighestOpponentMove .word ?            ; $7E404D 0.19
      ; This contains the highest effective
      ; move of any unit in opposing allegiances.
    wAIConsiderRecoveryModeFlag .sint ?       ; $7E404F 0.19
      ; -1 if healer AI should ignore
      ; recover mode settings.

  .endvirtual

  .virtual $7E4053

    wAICycleScriptCounter .word ? ; $7E4053 0.19
      ; This is the current counter into the
      ; current AI cycle's AI script. Used for
      ; avoiding long (infinite?) AI loops?

    aAIMainVariables .block ; $7E4055 0.19

      aTemp .block ; $7E4055 0.19
        _Vars .brept 5
          .word ?
        .endrept
      .endblock

      wTempDeploymentNumber .word ?            ; $7E405F 0.19
      wCurrentDeploymentListIndex .word ?      ; $7E4061 0.19
      aDeploymentList .fill (size(byte) * 52)  ; $7E4063 0.19

      aCurrentScriptCommand .block ; $7E4097 0.19

        ; Holds the current AI script command being
        ; interpreted.

        wOpcode .word ? ; $7E4097 0.19
          ; This is the identifier index of
          ; the script command, used to fetch the
          ; pointer to its handler.
        aParameters .brept 5 ; $7E4099 0.19
          ; These are the fields of the script command.
          .word ?
        .endrept

      .bend

      wBestTarget .word ?                ; $7E40A3 0.19
        ; This is the deployment number of the current
        ; best target.
      wScriptContinueFlag .word ?        ; $7E40A5 0.19
        ; This is nonzero when the AI engine should
        ; continue reading AI script commands.
      wTargetArrayOffset .word ?         ; $7E40A7 0.19
      aTargetArray .fill  7 * size(word) ; $7E40A9 0.19

    .bend

  .endvirtual

  .virtual $7E41AE

    bBattleDistance .byte ? ; $7E41AE 0.03
      ; This is the distance between battling units.

  .endvirtual

  .virtual $7E428C

    aBattleRoundsData .fill $200

  .endvirtual

  .virtual $7E4498

    wUnitWindowScrollPixels  .word ? ; $7E4498 0.23
    wUnitWindowScrollRows    .word ? ; $7E449A 0.23
    wUnitWindowCurrentRow    .word ? ; $7E449C 0.23
    wUnitWindowCurrentColumn .word ? ; $7E449E 0.23

    aUnitWindowDeploymentSlots .macroUnitWindowSlots word, UnitWindowSlotCount+1 ; $7E44A0 0.23
      ; These are short pointers to the deployment slots
      ; of the units on the unit window.
      ; The endcap slot should remain unused.

    wUnitWindowMaxRows       .word ? ; $7E4508 0.23
    wUnitWindowCurrentPage   .word ? ; $7E450A 0.23
    wUnitWindowSortDirection .word ? ; $7E450C 0.23
    wUnitWindowSortType      .word ? ; $7E450E 0.23

    aUnitWindowUnknown7E4510 .macroUnitWindowSlots byte ; $7E4510 0.23

    wUnitWindowUnknown7E4543 .word ? ; $7E4543 0.23

    .union

      .struct

        .fill ($7E454D - *)

        bUnitWindowActive .char ? ; $7E454D 0.23
          ; This is set to 1 when on the unit window and
          ; -1 when leaving/not on it. This is initialized to 0
          ; on chapter start.
        aUnitWindowUnknown7E454E .macroUnitWindowSlots byte ; $7E454E 0.23

      .endstruct

      .struct

        .fill ($7E4547 - *)

          aUnitWindowFE4MapSpriteSlots .block ; $7E4547 0.23

            aNormalMapSpriteSlots .fill (48 * size(sint)) ; $7E4547 0.23

            aTallMapSpriteSlots .fill (24 * size(sint)) ; $7E45A7 0.23

          .endblock

      .endstruct

    .endunion

  .endvirtual

  .virtual $7E45B2

    lDialogueWidthTablePointer .long ? ; $7E45B2 0.14

  .endvirtual

  .virtual $7E45BA

    wDialogueVRAMTilemapStartOffset  .word ? ; $7E45BA 0.14
    lDialogueTilemapBufferPointer    .long ? ; $7E45BC 0.14
    wDialogueVRAMGraphicsStartOffset .word ? ; $7E45BF 0.14

  .endvirtual

  .virtual $7E45C4

    bDialogueTilemapRowWidth      .byte ? ; $7E45C4 0.14
    wDialogueCurrentTilemapIndex  .word ? ; $7E45C5 0.14
    wDialogueCurrentTilemapOffset .word ? ; $7E45C7 0.14
    wDialogueNextTilemapIndex     .word ? ; $7E45C9 0.14

  .endvirtual

  .virtual $7E496E

    aPermanentEventFlags .fill len(bytes(%1 x 40)) ; $7E496E 0.21
    aTemporaryEventFlags .fill len(bytes(%1 x 96)) ; $7E4973 0.21

  .endvirtual

  .virtual $7E4DFA

    wTradeWindowActionIndex  .word ? ; $7E4DFA 0.22
    wShopWindowActionIndex   .word ? ; $7E4DFC 0.24
    wConvoyWindowActionIndex .word ? ; $7E4DFE 0.24

  .endvirtual

  .virtual $7E4E00

    wOptionsWindowActionIndex .word ? ; $7E4E00 0.22
      ; This is the current index into the options window's
      ; action table.

  .endvirtual

  .virtual $7E4E0A

    wPrepItemsActionIndex .word ? ; $7E4E0A 0.24
      ; This is the current index into the prep screen item window's
      ; action table.

  .endvirtual

  .virtual $7E4E0E

    wConvoyWindowItemListSortSetting .word ? ; $7E4E0E 0.24
      ; This is 0 when sorting the convoy item list by
      ; item type and size(word) when sorting by kana.

  .endvirtual

  .virtual $7E4E12

    wPrepItemsInventoryFlag .word ? ; $7E4E12 0.22

    wInfoWindowTarget .word ? ; $7E4E14 0.22
      ; This is normally the packed item that
      ; an info window is being displayed for.

  .endvirtual

  .virtual $7E4E18

    ; These variables correspond to
    ; the options menu settings.

    aOptions .block              ; $7E4E18 0.01
      wBackground .word ?        ; $7E4E18 0.22
        ; This variable is the current
        ; window setting (0-4).
      aWindowColors .brept 5     ; $7E4E1A 0.01
        wUpperRed .word ?
        wUpperGreen .word ?
        wUpperBlue .word ?
          ; These are the color settings
          ; for each channel, with their
          ; intensities subtracted from 24, i.e.
          ; full intensity is 0 and zero
          ; intensity is 24. These select
          ; the color at the top of
          ; the window.
        wLowerRed .word ?
        wLowerGreen .word ?
        wLowerBlue .word ?
          ; These are the color settings
          ; for each channel, with their
          ; intensities subtracted from 24, i.e.
          ; full intensity is 0 and zero
          ; intensity is 24. These select
          ; the color at the bottom of
          ; the window.
      .endrept
      wAnimation .word ?         ; $7E4E56 0.01
        ; This controls the battle
        ; animation setting:
        ; 0 - Normal
        ; 1 - Map
        ; 2 - Set individually
      wTerrainWindow .word ?     ; $7E4E58 0.01
        ; This is set to 1 to disable
        ; the terrain window, otherwise
        ; it is zero.
      wBurstWindow .word ?       ; $7E4E5A 0.01
        ; This is set to 1 to disable
        ; the burst window, otherwise
        ; it is zero.
      wTextSpeed .word ?         ; $7E4E5C 0.01
        ; This controls the speed
        ; at which dialogue text is drawn.
        ; 0 - Slow
        ; 1 - Normal
        ; 2 - Fast
      wUnitSpeed .word ?         ; $7E4E5E 0.01
        ; This controls the speed
        ; at which units move on
        ; the map.
        ; 0 - Normal
        ; 1 - Fast
      wSound .word ?             ; $7E4E60 0.01
        ; This controls whether
        ; sound is stereo or mono.
        ; 0 - Stereo
        ; 1 - Mono
      wBGM .word ?               ; $7E4E62 0.01
        ; This setting turns
        ; background music on and off.
        ; 0 - On
        ; 1 - Off
      wAutocursor .word ?        ; $7E4E64 0.01
        ; This setting causes the
        ; cursor to be moved onto
        ; the lord at the start of the
        ; player's turn.
        ; 0 - Starts on lord
        ; 1 - Holds previous position
      wVolume .word ?            ; $7E4E66 0.01
        ; This controls volume.
        ; 0 - Full volume
        ; 1 - Medium volume
        ; 2 - Low volume
        ; 3 - Muted
    .endblock

  .endvirtual

  .virtual $7E4E6B

    lWindowBackgroundPatternPointer .long ?        ; $7E4E6B 0.22
    lWindowBackgroundPatternPointerUnknown .long ? ; $7E4E6E 0.23
    lActiveMenuTempBufferPointer .long ?           ; $7E4E71 0.23
    aActiveMenuSlots .fill (5 * size(addr))        ; $7E4E74 0.23
    aActiveMenuData .block                         ; $7E4E7E 0.23
      aSlots .brept 4
        .dstruct structActiveMenu
      .endrept
    .endblock
    aActiveMenuTemp .dstruct structActiveMenu      ; $7E4EE2 0.23
    wActiveMenuCurrentSlot .addr ?                 ; $7E4EFB 0.23

  .endvirtual

  .virtual $7E4F39

    lMenuAPressCallback .long ? ; $7E4F39 0.22
      ; This is a pointer to a function
      ; that gets called when the `A` button is pressed.
    lMenuBPressCallback .long ? ; $7E4F3C 0.22
      ; This is a pointer to a function
      ; that gets called when the `B` button is pressed.

  .endvirtual

  .virtual $7E4F4A

    wStaffInventoryOffset .word ? ; $7E4F4A 0.19
      ; This is the offset of a selected staff in
      ; a unit's inventory.

  .endvirtual

  .virtual $7E4F67

    ; This is a temporary copy of the current menu
    ; tint setting that's used while in the options menu.

    aCurrentWindowColors .block ; $7E4F67 0.22
      wUpperRed .word ?
      wUpperGreen .word ?
      wUpperBlue .word ?
        ; These are the color settings
        ; for each channel, with their
        ; intensities subtracted from 24, i.e.
        ; full intensity is 0 and zero
        ; intensity is 24. These select
        ; the color at the top of
        ; the window.
      wLowerRed .word ?
      wLowerGreen .word ?
      wLowerBlue .word ?
        ; These are the color settings
        ; for each channel, with their
        ; intensities subtracted from 24, i.e.
        ; full intensity is 0 and zero
        ; intensity is 24. These select
        ; the color at the bottom of
        ; the window.
    .endblock

  .endvirtual

  .virtual $7E4F83

    wBGUpdateFlags .word ? ; $7E4F83 0.01
      ; Setting bits 1-3 will
      ; mark background tilemaps
      ; 1-3 as needing to be DMA'd
      ; to VRAM.

    ; These are used for the terrain window.

    wTerrainWindowSide .word ?    ; $7E4F85 0.01
      ; Determines which side of
      ; the screen to draw the
      ; terrain window on.
      ; 0 - Left
      ; 2 - Right
    wTerrainWindowTerrain .word ? ; $7E4F87 0.01
      ; This is the terrain type
      ; that the cursor is over,
      ; or is -1 when the terrain
      ; window should not be drawn.

    ; These are used for the burst window.

    wBurstWindowTarget .word ?      ; $7E4F89 0.01
      ; This is the deployment number
      ; of the unit the cursor is over.
      ; It is zero when the cursor is
      ; not over a unit.
    wBurstWindowXCoordinate .word ? ; $7E4F8B 0.01
    wBurstWindowYCoordinate .word ? ; $7E4F8D 0.01
      ; These are the coordinates of the
      ; tile that the cursor is over.
    wBurstWindowCounter .word ?     ; $7E4F8F 0.01
      ; This is a frame counter used
      ; to delay drawing the burst window.
      ; Initially 0, ticks up to 10
      ; before drawing the burst window.
    wBurstWindowDrawn .word ?       ; $7E4F91 0.01
      ; This is set to -1 when the burst
      ; window is drawn, else it is 0.

    lGold .long ? ; $7E4F93 0.01

    wUnknown7E4F96 .word ? ; $7E4F96 0.02
    wUnknown7E4F98 .word ? ; $7E4F98 0.02
    wUnknown7E4F9A .word ? ; $7E4F9A 0.04
    wRemainingMovement .word ? ; $7E4F9C 0.19
      ; This is a unit's remaining movement after moving,
      ; used for canto.
    wUnknown7E4F9E .word ? ; $7E4F9E 0.04

    wActiveTileUnitParameter1 .word ? ; $7E4FA0 0.18
    wActiveTileUnitParameter2 .word ? ; $7E4FA2 0.18

    wActiveTileUnitAllegiance .word ? ; $7E4FA4 0.17

  .endvirtual

  .virtual $7E4FC2

    wObjectiveMarkerFrame .word ? ; $7E4FC2 0.17
      ; This is the current objective marker
      ; frame tile index.

  .endvirtual

  .virtual $7E4FCE

    bDefeatedUnitDeploymentNumber .byte ? ; $7E4FCE 0.18
      ; This will be set to the deployment number
      ; of a unit defeated during combat, if there
      ; is one.
    bUnknown7E4FCF                .byte ? ; $7E4FCF 0.18
    aConvoy .block                        ; $7E4FD0 0.24
      ; This is a list of packed item IDs/durabilities
      ; in the player's convoy.
      Items .brept 128                    ; $7E4FD0 0.24
        .word ?
      .endrept
    .endblock

  .endvirtual

  .virtual $7E50E6

    aClassDataBuffer .dstruct structClassDataEntry            ; $7E50E6 0.02
      ; This buffer is filled with a ROM class data struct.
    aCharacterDataBuffer .dstruct structCharacterDataROMEntry ; $7E510A 0.02
      ; This buffer is filled with a ROM character data struct.
    aItemStatBonusBuffer .dstruct structItemStatBonuses       ; $7E513A 0.02
      ; This buffer is filled with an item's stat bonuses.

  .endvirtual

  .virtual $7E51CC

    wCurrentRegisteringMapSpriteID .word ? ; $7E51CC 0.02

  .endvirtual

  .virtual $7E520C

    aTerrainMovementCostBuffer .dstruct structTerrainEntry ; $7E520C 0.02

  .endvirtual

  .virtual $7E524C

    wUnknownMapBattleFlag .word ? ; $7E524C 0.01
      ; Needs research. Seems to be
      ; set to 1 during map battles.
    wUnknown7E524E .word ?        ; $7E524E 0.01
      ; Needs research. Normally 0,
      ; incremented during battles?

    wObjectiveMarkerColorIndex .word ? ; $7E5250 0.17
      ; This determines the color of the chapter's
      ; objective markers. Possible values:
      ; 1 - Red
      ; 2 - Blue
      ; 3 - Renders blue, possibly meant to be green
    wObjectiveMarkerColorValue .word ? ; $7E5252 0.17
      ; This is the actual palette setting for the
      ; objective markers' OAM data. See
      ; wObjectiveMarkerColorIndex.
    aObjectiveMarkers .fill 7 * size(structObjectiveMarkerEntryRAM) ; $7E5254 0.17
      ; This is an array that holds 6 objective markers
      ; and one terminator. There is no bounds checking,
      ; so don't have more than 6.

    aAllegianceInfo     .block  ; $7E528C 0.02
      bAlliedAllegiance .byte ? ; $7E528C 0.02
      bEnemyAllegiance  .byte ? ; $7E528D 0.02
      bNPCAllegiance    .byte ? ; $7E528E 0.02
                        .byte ? ; $7E528F 0.02
    .endblock

    aPhaseControllerInfo     .block  ; $7E5290 0.02
      bPlayerPhaseController .byte ? ; $7E5290 0.02
      bEnemyPhaseController  .byte ? ; $7E5291 0.02
      bNPCPhaseController    .byte ? ; $7E5292 0.02
                             .byte ? ; $7E5293 0.02
    .endblock

    aAllegianceTargets            .block  ; $7E5294 0.02
      bAlliedAllegianceTargetable .byte ? ; $7E5294 0.02
      bEnemyAllegianceTargetable  .byte ? ; $7E5295 0.02
      bNPCAllegianceTargetable    .byte ? ; $7E5296 0.02
                                  .byte ? ; $7E5297 0.02
    .endblock

    ; These arrays are for units.

    ; You can use the ._Units to get pointers to individual
    ; slots in the arrays, such as aPlayerUnits._Units to
    ; get a tuple of pointers to all slots or aPlayerUnits._Units[1]
    ; to get a pointer to the second player unit.

    ; You can also get pointers to individual fields, like
    ; aNPCUnits._Units[0].Level

    aPlayerUnits .block ; $7E5298 0.18
      _Units .brept 48
        .dstruct structCharacterDataRAM
      .endrept
    .endblock

    aEnemyUnits .block ; $7E5EC8 0.18
      _Units .brept 51
        .dstruct structCharacterDataRAM
      .endrept
    .endblock

    aNPCUnits .block ;  $7E6BBB 0.18
      _Units .brept 16
        .dstruct structCharacterDataRAM
      .endrept
    .endblock

    ; The contents of this block of RAM change
    ; depending on if the game is on the map or
    ; prep screen.

    .union
      .struct

        ; These arrays are for units/tiles
        ; on the map.

        aPlayerVisibleUnitMap .fill $600 ; $7E6FCB 0.15
          ; This map is filled with the
          ; deployment numbers of units
          ; visible to the player. If there
          ; is no visible unit at a tile,
          ; the value in the map is 00.
        aUnitMap              .fill $600 ; $7E75CB 0.15
          ; This map is filled with the
          ; deployment numbers of all
          ; units. If there is no unit
          ; at that tile, the value in
          ; the map is 00.
      .endstruct
      .struct
        aPrepItemsListItemArray  .fill ($300 * size(word)) ; $7E6FCB 0.15
        aPrepItemsListOwnerArray .fill ($300 * size(word)) ; $7E75CB 0.15
      .endstruct
    .endunion

  .endvirtual

  .virtual $7E7BCB

    aTerrainMap .fill $600 ; $7E7BCB 0.02
      ; This map is filled with the
      ; terrain IDs of all tiles on
      ; the map.
    aMapMetatileMap    .fill (size(word) * $600) ; 7E81CB 0.23
    aVisibilityMap     .fill $600 ; $7E8DCB 0.15
    aTargetableUnitMap .fill $600 ; $7E93CB 0.15
    aThreatenedTileMap .fill $600 ; $7E99CB 0.15

  .endvirtual

  .virtual $7EA0CD

    ; These variables are used to manage
    ; a set of icons in RAM.

    aIconArrayIconTableIndex .fill (24 * size(word)) ; $7EA0CD 0.14
    aIconArrayTileIndex      .fill (24 * size(word)) ; $7EA0FD 0.14
    aIconArrayXCoordinate    .fill (24 * size(word)) ; $7EA12D 0.14
    aIconArrayYCoordinate    .fill (24 * size(word)) ; $7EA15D 0.14
    aIconArrayAttributes     .fill (24 * size(word)) ; $7EA18D 0.14
    aIconArrayFlag           .fill (24 * size(word)) ; $7EA1BD 0.14
      ; This is set to -1 if the slot is being used.

  .endvirtual

  .virtual $7EA1ED

    wMenuLineScrollCount     .word ? ; $7EA1ED 0.22
    wMenuMinimumLine         .word ? ; $7EA1EF 0.22
    wMenuMaximumLine         .word ? ; $7EA1F1 0.22
    wMenuUpScrollThreshold   .word ? ; $7EA1F3 0.22
    wMenuDownScrollThreshold .word ? ; $7EA1F5 0.22
    wMenuBottomThreshold     .word ? ; $7EA1F7 0.22

    ; These variables are used for usable items.

    lItemUseRoutineCurrentPosition .long ? ; $7EA1F9 0.15
      ; This is a pointer to the current item use routine pointer.
      ; It is used to fetch the pointer for lItemUseRoutine.
    lItemUseRoutine .long ? ; $7EA1FC 0.15
      ; This is a pointer to the current item use routine.

  .endvirtual

  .virtual $7EA202

    aLossesTable     .fill 49 ; $7EA202 0.16
    aWinsTable       .fill 49 ; $7EA233 0.16
    aTurncountsTable .fill size(structTurncountEntryRAM) * 40 ; $7EA264 0.16

  .endvirtual

  .virtual $7EA4DC

    wActionStructRoundTempUnknownAttackCount .word ? ; $7EA4DC 0.18

    bActionStructDistance .byte ? ; $7EA4DE 0.17
      ; This is the distance between the units in
      ; aActionStructUnit1 and aActionStructUnit2.

    .byte ?

    wActionStructTempRoundAttackBitfield .word ? ; $7EA4E0 0.18
    wActionStructRoundFlowBitfield       .word ? ; $7EA4E2 0.18
    wActionStructRoundAttackBitfield     .word ? ; $7EA4E4 0.18
    wActionStructRoundTempDamage         .word ? ; $7EA4E6 0.18

    wStaffHitCounter .word ? ; $7EA4E8 0.19

  .endvirtual

  .virtual $7EA4EA

    wCapturingFlag     .word ? ; $7EA4EA 0.01
      ; This variable is set to -1
      ; when trying to capture a unit.
    lUnknown7EA4EC     .long ? ; $7EA4EC 0.01
      ; Needs research. Has something
      ; to do with battles.
    aActionStructUnit1 .dstruct structActionStructEntry  ; $7EA4EF 0.01
    aActionStructUnit2 .dstruct structActionStructEntry  ; $7EA560 0.01
      ; These structs are filled with
      ; character-related data during
      ; certain actions, like battles.

  .endvirtual

  .virtual $7EA5D1

    aActionStructGeneratedRounds .fill (40 * size(structBattleGeneratedRound)) ; $7EA5D1 0.17
      ; This is an array of raw battle rounds.
    wActionStructGeneratedRoundVar1 .word ? ; $7EA671 0.17
      ; This is used for multiple action struct
      ; round related variables, such as the number of
      ; attacks in a generated round, a unit's
      ; deployment number, and more.
    wActionStructGeneratedRoundOffset .word ? ; $7EA673 0.17
      ; This is the offset of the current round
      ; in aActionStructGeneratedRounds during
      ; round generation.
    wActionStructGeneratedRoundLastOffset .word ? ; $7EA675 0.17
      ; This is the offset of the last round in
      ; aActionStructGeneratedRounds.
    wActionStructGeneratedRoundBonusCombat .word ? ; $7EA677 0.17
      ; This is nonzero if assail has been activated
      ; during this fight.
    wActionStructGeneratedRoundDamage .word ? ; $7EA679 0.17
      ; This is the amount of damage that is
      ; expected to be dealt per hit during
      ; a round of combat.
    wActionStructGeneratedRoundBufferPointer .word ? ; $7EA67B 0.17
      ; This is a short pointer to a character
      ; buffer filled with the first unit
      ; (usually the player unit?).
    wActionStructGeneratedRoundDeploymentNumber .word ? ; $7EA67D 0.17
      ; This is the deployment number of the
      ; second unit (usually an enemy?).
    wActionStructGeneratedRoundCombatType .word ? ; $7EA67F 0.17
      ; This seems to be a value to show what
      ; kind of 'battle' is taking place. Most values
      ; are unknown:
      ; 0 - Default
      ; 1 - Unknown
      ; 2 - Dance
      ; 3 - Unknown
      ; 4 - Unknown
      ; 5 - Unknown
      ; 6 - Capture
      ; 7 - Promotion
      ; 8 - Unknown
      ; 9 - Unknown
      ; A - Unknown
      ; B - Unknown
    wActionStructType .word ? ; $7EA681 0.17
      ; This dictates how the action structs
      ; are interpreted.
      ; 0 - Default
      ; 1 - Enemy-initiated targeting
      ; 2 - Player-initiated targeting
      ; 3 - Unknown
      ; 4 - Single unit
    wActionStructGeneratedRoundUnknownActor .word ? ; $7EA683 0.17
      ; This is copied from
      ; wActionStructGeneratedRoundActor.
    wActionStructGeneratedRoundActor .word ? ; $7EA685 0.17
      ; This is which unit is currently acting,
      ; 0 or 2.

    .fill 4 ; Unknown, unused?

    wActionStructGeneratedRoundMight .word ? ; $7EA68B 0.17
      ; This is the might of the active unit.
    wActionStructGeneratedRoundDefense .word ? ; $7EA68D 0.17
      ; This is the defensive stat of
      ; the inactive unit.
    wActionStructGeneratedRoundHit .word ? ; $7EA68F 0.17
      ; This is the hitrate of the active unit.
    wActionStructGeneratedRoundCrit .word ? ; $7EA691 0.17
      ; This is the critrate of the active unit.
    wHitAvoidBonus .word ? ; $7EA693 0.17
      ; This is an action struct's hit/avoid
      ; bonus from supports and the charm skill.
    wGainedExperience .word ? ; $7EA695 0.18
      ; This is the amount of experience
      ; gained after performing an action.

    .word ? ; Unknown

    wSupportBonus .word ? ; $7EA699 0.17
      ; This is an action struct's bonus
      ; hit/avoid from supports.

    ; These are used for leveling units.

    aUnitAdjustedGrowths .block ; $7EA69B 0.03
      wHP .word ?               ; $7EA69B 0.03
      wSTR .word ?              ; $7EA69D 0.03
      wMAG .word ?              ; $7EA69F 0.03
      wSKL .word ?              ; $7EA6A1 0.03
      wSPD .word ?              ; $7EA6A3 0.03
      wDEF .word ?              ; $7EA6A5 0.03
      wCON .word ?              ; $7EA6A7 0.03
      wLUK .word ?              ; $7EA6A9 0.03
      wMOV .word ?              ; $7EA6AB 0.03
    .endblock

  .endvirtual

  .virtual $7EA72D

    aMovementDirectionArray .fill $80 ; $7EA72D 0.19

  .endvirtual

  .virtual $7EA7AF

    ; This block of WRAM gets reused for
    ; multiple different kinds of target/selection
    ; lists and variables.

    aStatusWindowTempLeaderList .fill size(word) * 6 ; $7EA7AF
      ; This is a list of deployment number words.
    aStatusWindowTempCountList .fill size(word) * 5 ; $7EA7BB
      ; This is a list of faction member count words.

  .endvirtual

  .virtual $7E99CB

    aTradeWindowSavedPalette .dstruct Palette

  .endvirtual

  .virtual $7EA937

    ; This block of WRAM gets reused for
    ; multiple things that don't need to exist
    ; at the same time.

    .union

      .struct
        lUNITGroupLoadingPointer .long ?        ; $7EA937 0.02
          ; This points to the current UNIT struct entry
          ; being loaded.
        wUNITGroupLoadingCount          .word ? ; $7EA93A 0.02
          ; This is the count of the number of units to be loaded.
        wUNITGroupLoadingInventoryIndex .word ? ; $7EA93C 0.02
          ; This is a counter for the current item to
          ; be added from a UNIT struct.
      .endstruct

      .struct
        aMovementMap .fill $600 ; $7EA937 0.19

        .fill ($7EAF73 - *)

        aRangeMap .fill $600 ; $7EAF73 0.19
      .endstruct

      .struct

        .fill ($7EACDE - *)

        wTradeWindowTempTextBaseTile .word ? ; $7EACDE 0.22
        wTradeWindowTempTextType     .word ? ; $7EACE0 0.22

        aInventoryBuffers .block ; $7EACE2 0.22
          Buffers .brept 2
            .dstruct structInventoryBuffer
          .endrept
        .endblock

        aTradeWindowIconIndexes .fill size(word) * 15 ; $7EAD02 0.22

        .word ?

        aTradeWindowItemTypes .fill size(word) * 15 ; $7EAD22 0.22
          ; 0: movable
          ; 2: unmovable

        .word ?

        wTradeWindowInventoryOffset       .word ? ; $7EAD42 0.22
        wTradeWindowSelectedItemOffset    .word ? ; $7EAD44 0.22
        wTradeWindowCursorOffset          .word ? ; $7EAD46 0.22
        wTradeWindowCursorUnknownOffset   .word ? ; $7EAD48 0.22
        wTradeWindowSelectedSideOffset    .word ? ; $7EAD4A 0.22
          ; These are offsets into aInventoryBuffers.
        wTradeWindowType                  .word ? ; $7EAD4C 0.22
          ; 1: Stealing
          ; 2: Trading
        wTradeWindowInitiatorConstitution .word ? ; $7EAD4E 0.22
          ; This is the initiator's Constitution,
          ; used when stealing.
        wTradeWindowCursorStartingOffset  .word ? ; $7EAD50 0.22
        wTradeWindowTargetEmptySlotOffset .word ? ; $7EAD52 0.22
          ; These are offsets into aInventoryBuffers.

      .endstruct

      .struct

        wConvoyWindowItemListScrolledRowOffset .word ? ; $7EA937 0.24
          ; This is the number of rows scrolled * size(word).
        wConvoyWindowItemListScrolledRow .word ?       ; $7EA939 0.24
          ; This is the number of rows scrolled.
        wConvoyWindowItemListSelectedSide .word ?      ; $7EA93B 0.24
          ; This is 0 when the left-side item is selected and
          ; size(word) when the right-side item is selected.
        wConvoyWindowItemListSelectedRow .word ?       ; $7EA93D 0.24
          ; This is the row number of the currently-selected item.
        wConvoyWindowDiscardOffset .word ?             ; $7EA93F 0.24
          ; This is the offset of the item being discarded.
        wConvoyWindowUnitItemOffset .word ?            ; $7EA941 0.24
          ; This is the offset of the currently-selected item within
          ; the unit's inventory.
        wConvoyWindowUnitMaxItemOffset .word ?         ; $7EA943 0.24
          ; This is the offset of the last item in the unit's
          ; inventory.
        aConvoyWindowOFSHDMATable .block               ; $7EA945 0.24
          ; This is a table of H/VOFS positions for BG2/3.

          Entries .brept 4                             ; $7EA945 0.24
            NTRLSetting .byte ?
            HOFS        .word ?
            VOFS        .word ?
            .endrept

          Terminator .byte ?                           ; $7EA959 0.24
          .endblock

        .word ?

        wConvoyWindowSourceSelectionSetting .word ?    ; $7EA95C 0.24
          ; This is the currently-selected option within the
          ; center window in the convoy when selecting what
          ; to do. Possible values:
          ;   0 * size(word): hovering over 'take'
          ;   2 * size(word): hovering over 'give'
          ;   4 * size(word): hovering over 'discard'

        .union

          .struct

            aMapConvoyWindowBG1VOFSHDMATable .block ; $7EA95E 0.24
              ; This is a table of VOFS positions for BG1, used by the
              ; map convoy window..

              Entries .brept 4                      ; $7EA95E 0.24
                NTRLSetting .byte ?
                HOFS        .word ?
                VOFS        .word ?
                .endrept

              Terminator .byte ?                    ; $7EA972 0.24
              .endblock

          .endstruct

          .struct

            .fill $7EA968 - *

            aConvoyWindowSortWeightList .block ; $7EA968 0.24
              ; This is a list of weights used to sort the convoy item list.
              Items .rept 128
                .word ?
                .endrept
              .endblock

          .endstruct

        .endunion

      .endstruct

      .struct

        wStatusWindowIndex .word ?                         ; $7EA937 0.22
          ; This is the currently-selected faction's index.
        wStatusWindowCount .word ?                         ; $7EA939 0.22
          ; This is the number of factions on the field.
        aStatusWindowLeaders .fill size(sint) * 5          ; $7EA93B 0.22
          ; This is an array of deployment number sints
          ; for the faction leaders on the field. 
        aStatusWindowLeaderCharacters .fill size(word) * 5 ; $7EA945 0.22
          ; This is an array of character ID words
          ; for the faction leaders on the field.
        wStatusWindowCurrentLeader .word ?                 ; $7EA94F 0.22
          ; This is the character ID word of the
          ; currently-selected faction's leader. This is
          ; set to None if there is no leader on the map.
        aStatusWindowFactionCount .fill size(word) * 5     ; $7EA951 0.22
          ; This is an array of faction member counts
          ; for the factions on the field.

      .endstruct

      .struct

        aOptionsWindowTempMenuLine .structOptionsWindowLine     ; $7EA937 0.22
          ; This is a temporary struct used when interpreting a
          ; structOptionsWindowLine.
        wOptionsMenuMenuLineOffset .word ?                      ; $7EA95D 0.22
          ; This is the current offset into a list of short
          ; pointers to structOptionsWindowLines
        aOptionsWindowMenuLinePointers .fill size(addr) * 16    ; $7EA95F 0.22
          ; This is a copy of the ROM version of the
          ; list of short pointers to the menu's lines.
        aOptionsWindowMenuLineSelections .fill size(word) * 16  ; $7EA97F 0.22
          ; This is an array of position words for each
          ; menu line's options.
        wOptionsWindowMenuLineIndex .word ?                     ; $7EA99F 0.22
          ; This is the current line number that is currently selected.
        wOptionsWindowMenuLineFromIndex .word ?                 ; $7EA9A1 0.22
          ; Names are hard. This is the line number that is
          ; currently being scrolled off of when moving between
          ; lines. Most of the time this is the same as wOptionsWindowMenuLineIndex
        wOptionsWindowScrolledLines .word ?                     ; $7EA9A3 0.22
          ; This is the number of lines that the screen is currently
          ; scrolled down.
        wOptionsWindowCursorYPosition .word ?                   ; $7EA9A5 0.22
          ; This is the Y position of the cursor in pixels.
        wOptionsWindowCursorXPosition .word ?                   ; $7EA9A7 0.22
          ; This is the X position of the cursor in pixels.
        wOptionsWindowScrollTimer .word ?                       ; $7EA9A9 0.22
          ; This is a timer that ticks down while the
          ; options window is scrolling.
        wOptionsWindowTempTextCoordinates .block                ; $7EA9AB 0.22
          ; These are the coordinates (in tiles) of the piece of
          ; text currently being drawn to the options window.
          X .byte ? ; $7EA9AB 0.22
          Y .byte ? ; $7EA9AC 0.22
          .endblock
        aOptionsWindowUpperColorSliderYCoordinatesPixels .block ; $7EA9AD 0.22
          ; These are the base Y coordinates (in pixels)
          ; of the sliders on the menu background color
          ; selectors.
          wRed   .word ? ; $7EA9AD 0.22
          wGreen .word ? ; $7EA9AF 0.22
          wBlue  .word ? ; $7EA9B1 0.22
          .endblock
        aOptionsWindowLowerColorSliderYCoordinatesPixels .block ; $7EA9B3 0.22
          ; These are the base Y coordinates (in pixels)
          ; of the sliders on the menu background color
          ; selectors.
          wRed   .word ? ; $7EA9B3 0.22
          wGreen .word ? ; $7EA9B5 0.22
          wBlue  .word ? ; $7EA9B7 0.22
          .endblock
        wOptionsWindowSliderBarTilemapBufferBase .word ?        ; $7EA9B9 0.22
          ; This is the base offset of the menu
          ; background color selector bar tilemaps in
          ; aBG2TilemapBuffer.
        aOptionsWindowScrollPositionsHDMA .fill 13              ; $7EA9BB 0.22
          ; TODO: make the size dependent on the ROM copy?
          ; This is a copy of the HDMA stuff for the options
          ; window that gets updated to match the screen's
          ; scrolled position.
        wOptionsWindowScrollPixels .word ?                      ; $7EA9C8 0.22
          ; This is the amount that the screen has
          ; scrolled in pixels.
        aOptionsWindowUpperColorSliderYCoordinates .block       ; $7EA9CA 0.22
          ; These are the base Y coordinates (in tiles) - 1
          ; of the sliders on the menu background color
          ; selectors.
          wRed   .word ? ; $7EA9CA 0.22
          wGreen .word ? ; $7EA9CC 0.22
          wBlue  .word ? ; $7EA9CE 0.22
          .endblock
        aOptionsWindowLowerColorSliderYCoordinates .block       ; $7EA9D0 0.22
          ; These are the base Y coordinates (in tiles) - 1
          ; of the sliders on the menu background color
          ; selectors.
          wRed   .word ? ; $7EA9D0 0.22
          wGreen .word ? ; $7EA9D2 0.22
          wBlue  .word ? ; $7EA9D4 0.22
          .endblock
        wOptionsWindowLowerColorDefaultYCoordinate .word ?      ; $7EA9D6 0.22
          ; This is the base Y coordinate (in tiles) - 1
          ; of the `Default` option for the selected color setting.
        wOptionsWindowColorModifiedFlag .sint ?                 ; $7EA9D8 0.22
          ; This is zero if the color for the current menu
          ; tile setting has been changed from its default,
          ; otherwise it is -1. This is set to 1 briefly during
          ; menu creation.
        wOptionsWindowMaxScrollDistance .word ?                 ; $7EA9DA 0.22
          ; This is the maximum amount that the options
          ; window can scroll in pixels.

      .endstruct

      .struct

        .fill $7EA943 - *

        aUnitWindowFE4SkillIconTilemap .fill 32 * 64 * size(word) ; $7EA943 0.23

      .endstruct

      .struct

        wShopWindowUnitFlag .word ?         ; $7EA937 0.24
          ; This is size(word) when the items displayed in a
          ; shop are a unit's inventory.
        wShopWindowReadyFlag .word ?        ; $7EA939 0.24
          ; This is negative when the shop is
          ; not yet displaying items.
        wShopWindowConfirmOffset .word ?    ; $7EA93B 0.24
        lShopWindowInventoryPointer .long ? ; $7EA93D 0.24

        ; These arrays are used for items shown in shops.

        aShopWindowItemIconArray .block          ; $7EA940 0.24
          ; This is an unused array of item icon ID words.
          Icons .brept 7                         ; $7EA940 0.24
            .word ?
          .endrept
          Terminator .word ?                     ; $7EA94E 0.24
          .endblock
        aShopWindowItemIDArray .block            ; $7EA950 0.24
          ; This is an array of packed item ID/durability
          ; words.
          IDs .brept 7                           ; $7EA950 0.24
            .word ?
          .endrept
          Terminator .word ?                     ; $7EA95E 0.24
          .endblock
        aShopWindowItemTextBaseArray .block      ; $7EA960 0.24
          ; This is an array of text base tilemap entries
          ; used to color unselectable items.
          ; Technically, these aren't text bases, but
          ; rather that the durability drawing function
          ; passes in 0 or 2 through aCurrentTilemapInfo.wBaseTile
          ; for blue/gray.
          Bases .brept 7                         ; $7EA960 0.24
            .word ?
          .endrept
          Terminator .word ?                     ; $7EA96E 0.24
          .endblock
        aShopWindowItemDurabilityArray .block    ; $7EA970 0.24
          ; This is an array of item durabilities.
          Durabilities .brept 7                  ; $7EA970 0.24
            .word ?
          .endrept
          Terminator .word ?                     ; $7EA97E 0.24
          .endblock
        aShopWindowItemPriceArray .block         ; $7EA980 0.24
          ; This is an array of prices.
          Prices .brept 7                        ; $7EA980 0.24
            .word ?
          .endrept
          Terminator .word ?                     ; $7EA98E 0.24
          .endblock
        aShopWindowItemSelectabilityArray .block ; $7EA990 0.24
          ; This is an array where nonselectable items will
          ; have a nonzero value.
          Selectabilities .brept 7               ; $7EA990 0.24
            .word ?
          .endrept
          Terminator .word ?                     ; $7EA99E 0.24
          .endblock
        aShopWindowItemOffsetArray .block        ; $7EA9A0 0.24
          ; This is an array that maps an item to sell
          ; to its offset within a unit's inventory.
          Offsets .brept 7                       ; $7EA9A0 0.24
            .word ?
          .endrept
          Terminator .word ?                     ; $7EA9AE 0.24
          .endblock

        wShopWindowCurrentRowOffset .word ? ; $7EA9B0 0.24
          ; This is the offset of the current item into the
          ; above arrays.
        wShopWindowMaxRowOffset .word ?     ; $7EA9B2 0.24
          ; This is the next offset value after the end of
          ; the item list.

      .endstruct

    .endunion

  .endvirtual

  .virtual $7EB5F7

    wBurstWindowStyle .word ?         ; $7EB5F7 0.01
      ; This value determines
      ; where/how the burst window
      ; is drawn. Possible values:
      ; 0 - Above the unit
      ; 1 - Above and to the right of the unit
      ; 2 - Above and to the left of the unit
      ; 3 - Below the unit
      ; 4 - Below and to the right of the unit
      ; 5 - Below and to the left of the unit
    wBurstWindowOriginXTile .word ?   ; $7EB5F9 0.01
    wBurstWindowOriginYTile .word ?   ; $7EB5FB 0.01
      ; These are the coordinates for
      ; the upper-leftmost
      ; tile of the unit that the
      ; burst window is drawn for.
    wBurstWindowPositionXTile .word ? ; $7EB5FD 0.01
    wBurstWindowPositionYTile .word ? ; $7EB5FF 0.01
      ; These are the coordinates for
      ; the upper-leftmost tile of
      ; the burst window tilemap.
    wBurstWindowNameYTile .word ?     ; $7EB601 0.01
      ; This is the Y coordinate of
      ; the burst window's name text.

    aPrepDeploymentSlots .fill (51 * size(word)) ; $7EB603 0.23

  .endvirtual

  .virtual $7EB6C3

    wPrepDeploymentSlotsOffset .word ?           ; $7EB6C3 0.24
    wPrepUnitListColumn .word ?                  ; $7EB6C5 0.24
    wPrepUnitListRow .word ?                     ; $7EB6C7 0.24
    wPrepMinimumDeployableUnits .word ?          ; $7EB6C9 0.24
    wPrepMaximumDeployableUnits .word ?          ; $7EB6CB 0.24
    wPrepSelectedDeployableUnits .word ?         ; $7EB6CD 0.24
    wPrepTotalDeployableUnits .word ?            ; $7EB6CF 0.24

  .endvirtual

  .virtual $7EB6DB

    wPrepUnitListTextCoordinateBase .word ?    ; $7EB6DB 0.24
    wPrepUnitListSpriteVerticalOffset .word ?  ; $7EB6DD 0.24
    wPrepUnitListMovingFlag .word ?            ; $7EB6DF 0.24

    .word ? ; $7EB6E1 ; 0.24

    wPrepScrollDirectionIncrement .word ?      ; $7EB6E3 0.24
    wPrepScrollDirectionStep .word ?           ; $7EB6E5 0.24
    wPrepListCursorXCoordinate .word ?         ; $7EB6E7 0.24
    wPrepListCursorYCoordinate .word ?         ; $7EB6E9 0.24
    wPrepItemsSelectedOption .word ?           ; $7EB6EB 0.24
    wPrepItemsDiscardOffset .word ?            ; $7EB6ED 0.24
    wPrepItemsDiscardLength .word ?            ; $7EB6EF 0.24
    wPrepUnitListLastSelectedColumn .word ?    ; $7EB6F1 0.24
    wPrepUnitListLastSelectedRow .word ?       ; $7EB6F3 0.24
    wPrepUnitListLastScrollOffset .word ?      ; $7EB6F5 0.24
    wPrepUnitListLastScrolledMenuLine .word ?  ; $7EB6F7 0.24

  .endvirtual

  .virtual $7EC1AF

    ; These are for keeping track of map sprites
    ; and status effect sprites on the map.

    aUpperMapSpriteAndStatusBuffer .fill (120 * size(structMapSpriteAndStatusEntry)) ; $7EC1AF 0.01
    aLowerMapSpriteBuffer .fill (127 * size(structMapSpriteAndStatusEntry))          ; $7EC47F 0.01

    lUnknown7EC779 .long ? ; $7EC779 0.01

    ; These are buffers for each tilemap layer.

    aBG1TilemapBuffer .block             ; $7EC77C 0.24
      Page0 .fill (32 * 32 * size(word)) ; $7EC77C 0.24
      Page1 .fill (32 * 32 * size(word)) ; $7ECF7C 0.24
      .endblock
    aBG2TilemapBuffer .block             ; $7ED77C 0.24
      Page0 .fill (32 * 32 * size(word)) ; $7ED77C 0.24
      Page1 .fill (32 * 32 * size(word)) ; $7EDF7C 0.24
      .endblock
    aBG3TilemapBuffer .block             ; $7EE77C 0.24
      Page0 .fill (32 * 32 * size(word)) ; $7EE77C 0.24
      Page1 .fill (32 * 32 * size(word)) ; $7EEF7C 0.24
      .endblock

  .endvirtual

  .virtual $7F8614

    aMenuTilemapBuffers .block ; $7F8614 0.22

      ; These are temporary spaces for working with
      ; flattened tilemap slices when building menus.

      aBuffers .brept 3
        .fill (32 * 24 * size(word))
      .endrept
    .endblock

  .endvirtual

  .virtual $7FAA14

    wMapBattleFlag .word ? ; $7FAA14 0.01
        ; This is set to 1 during
        ; map sprite battles.

    wActiveMapSpriteCurrentSpriteOffset .word ? ; $7FAA16 0.02

  .endvirtual

  .virtual $7FAA5A

    aUnknown7FAA5A .fill (size(word) * 4) ; $7FAA5A 0.02

  .endvirtual

  .virtual $7FAA7A

    aActiveMapSpriteScreenXMetatileOffsetArray .fill (size(word) * 4) ; $7FAA7A 0.02
    aActiveMapSpriteScreenYMetatileOffsetArray .fill (size(word) * 4) ; $7FAA82 0.02

  .endvirtual

  .virtual $7FAA92

    aUnknown7FAA92 .fill (size(word) * 4) ; $7FAA92 0.02

  .endvirtual

  .virtual $7FAA42

    aActiveMapSpriteIndexArray .fill (size(word) * 4)      ; $7FAA42 0.01
      ; These are the sprite IDs
      ; of active map sprites.
    aActiveMapSpriteUnknownBitfield .fill (size(word) * 4) ; $7FAA4A 0.01
      ; These status bitfields are
      ; for controlling the active
      ; map sprites.

    .endvirtual

  .virtual $7FAAAA

    aActiveMapSpriteMovementSpeedArray .fill (size(word) * 4) ; $7FAAAA 0.01
      ; These control the movement speed
      ; of active moving map sprites.

  .endvirtual

  .virtual $7FAAF3

    lUnknown7FAAF3 .long ? ; $7FAAF3 0.02

  .endvirtual

  .virtual $7FAB34

    .union

      .struct

        .fill $7FB0F5 - *

        aDecompressionBuffer .fill ($800000 - *) ; $7FB0F5 0.23
          ; The decompression buffer here seems like it
          ; goes all the way until the end of RAM, and things are
          ; free to use as much or as little as they want.

      .endstruct

      .struct

        .fill ($7FE1B7 - *)

        ; These values are copied from aBattleAnimationUnit1Info
        ; and aBattleAnimationUnit2Info when filling in
        ; aBattleAnimationUnit1Data and aBattleAnimationUnit2Data.

        aBattleAnimationCurrentUnitTemp .block ; $7FE1B7 0.03
          bClass .byte ?                       ; $7FE1B7 0.03
          bWeaponType .byte ?                  ; $7FE1B8 0.03
          bAdjustedCharacter .byte ?           ; $7FE1B9 0.03
          bGender .byte ?                      ; $7FE1BA 0.03
        .endblock

        .fill ($7FE1BF - *)

        ; These values control distances at which
        ; parts of a battle animation happen.

        bBattleAnimationUnit1MovementDataIndex .byte ? ; $7FE1BF 0.03
        bBattleAnimationUnit2MovementDataIndex .byte ? ; $7FE1C0 0.03

      .endstruct

      .struct

        .fill ($7FE1B7 - *)

        ; These values will be copied into one of
        ; aBattleAnimationUnit1Data or
        ; aBattleAnimationUnit2Data.

        aBattleAnimationCurrentUnitDataTemp .block ; $7FE1B7 0.03
          bScriptIndex .byte ?                     ; $7FE1B7 0.03
          bUnderlayIndex .byte ?                   ; $7FE1B8 0.03
          bOverlayIndex .byte ?                    ; $7FE1B9 0.03
          bPaletteIndex .byte ?                    ; $7FE1BA 0.03
        .endblock

      .endstruct

      .struct

        .byte ?

        ; These are used for displaying animations
        ; during a battle.

        aBattleAnimationUnit1Data .block ; $7FE1B8 0.03
          bUnderlayIndex .byte ?         ; $7FE1B8 0.03
          bOverlayIndex .byte ?          ; $7FE1B9 0.03
          bPaletteIndex .byte ?          ; $7FE1BA 0.03
          bScriptIndex .byte ?           ; $7FE1BB 0.03
        .endblock

        aBattleAnimationUnit2Data .block ; $7FE1BC 0.03
          bUnderlayIndex .byte ?         ; $7FE1BC 0.03
          bOverlayIndex .byte ?          ; $7FE1BD 0.03
          bPaletteIndex .byte ?          ; $7FE1BE 0.03
          bScriptIndex .byte ?           ; $7FE1BF 0.03
        .endblock

      .endstruct

      .struct

        aUnitWindowSlotsStrength     .macroUnitWindowSlots byte ; $7FAB34 0.23
        aUnitWindowSlotsMight        .macroUnitWindowSlots byte ; $7FAB67 0.23
        aUnitWindowSlotsMagic        .macroUnitWindowSlots byte ; $7FAB9A 0.23
        aUnitWindowSlotsSkill        .macroUnitWindowSlots byte ; $7FABCD 0.23
        aUnitWindowSlotsSpeed        .macroUnitWindowSlots byte ; $7FAC00 0.23
        aUnitWindowSlotsLuck         .macroUnitWindowSlots byte ; $7FAC33 0.23
        aUnitWindowSlotsDefense      .macroUnitWindowSlots byte ; $7FAC66 0.23
        aUnitWindowSlotsConstitution .macroUnitWindowSlots byte ; $7FAC99 0.23
        aUnitWindowSlotsHit          .macroUnitWindowSlots byte ; $7FACCC 0.23
        aUnitWindowSlotsAvoid        .macroUnitWindowSlots byte ; $7FACFF 0.23
        aUnitWindowSlotsSwordRank    .macroUnitWindowSlots byte ; $7FAD32 0.23
        aUnitWindowSlotsLanceRank    .macroUnitWindowSlots byte ; $7FAD65 0.23
        aUnitWindowSlotsAxeRank      .macroUnitWindowSlots byte ; $7FAD98 0.23
        aUnitWindowSlotsBowRank      .macroUnitWindowSlots byte ; $7FADCB 0.23
        aUnitWindowSlotsStaffRank    .macroUnitWindowSlots byte ; $7FADFE 0.23
        aUnitWindowSlotsFireRank     .macroUnitWindowSlots byte ; $7FAE31 0.23
        aUnitWindowSlotsThunderRank  .macroUnitWindowSlots byte ; $7FAE64 0.23
        aUnitWindowSlotsWindRank     .macroUnitWindowSlots byte ; $7FAE97 0.23
        aUnitWindowSlotsLightRank    .macroUnitWindowSlots byte ; $7FAECA 0.23
        aUnitWindowSlotsDarkRank     .macroUnitWindowSlots byte ; $7FAEFD 0.23
        aUnitWindowSlotsSkills1      .macroUnitWindowSlots byte ; $7FAF30 0.23
        aUnitWindowSlotsSkills2      .macroUnitWindowSlots byte ; $7FAF63 0.23
        aUnitWindowSlotsSkills3      .macroUnitWindowSlots byte ; $7FAF96 0.23

        wUnitWindowAllegiance              .word ? ; $7FAFC9 0.23
        wUnitWindowUnknown7FAFCB           .word ? ; $7FAFCB 0.23

        .fill ($7FB10D - *)

        wUnitWindowType                    .word ? ; $7FB10D 0.23
          ; This tells how we arrived at the unit window, with:
          ;   0 - Open the menu from a chapter map
          ;   1 - Return to the menu from a unit on a chapter map
          ;   2 - Open the menu from the preparations screen
          ;   3 - Return to the menu from a unit on the preparations screen
        wUnitWindowFE4CurrentLine          .word ? ; $7FB10F 0.23
          ; In FE4, this is the currently-selected unit list line,
          ; 1-indexed.
        wUnitWindowFE4CurrentHighlightLine .word ? ; $7FB111 0.23
          ; In FE4, this is the currently-selected highlighted unit
          ; list line, 0-indexed.
        wUnitWindowFE4ScrolledLines        .word ? ; $7FB113 0.23
          ; In FE4, this is the number of lines currently scrolled
          ; on the unit list.
        ; FE4 puts its unit count for the window here.
        wUnitWindowFE4SkippedUnitCount     .word ? ; $7FB115 0.23
          ; In FE4, this is the number of units that have been
          ; excluded from the unit list.
        wUnitWindowCanScrollDownFlag    .word ? ; $7FB117 0.23
          ; This is set to 1 when the player has more
          ; units than what fits on a single screen and is 0 otherwise.

        .fill size(word)

        wUnitWindowFE4LastScrolledFlag  .sint ? ; $7FB11B 0.23
          ; In FE4, this is set to -1 upon moving downward in the list
          ; of units, and is 0 otherwise.
        wUnitWindowUnknown7FB11D        .word ? ; $7FB11D 0.23
        wUnitWindowFE4ScrollingStep     .word ? ; $7FB11F 0.23
          ; In FE4, this is 0-2 based on progress when scrolling on
          ; the list of units.
        wUnitWindowFE4UnitListCursorYCoordinate .word ? ; $7FB121 0.23
          ; In FE4, this is the Y coordinate of the cursor in pixels.
          ; In FE5, it is initialized to its default position in FE4 but
          ; is not touched afterwards.
        wUnitWindowFE4ScrollingFlag     .sint ? ; $7FB123 0.23
          ; In FE4, this is set to -1 while scrolling on the list of units,
          ; and is 0 otherwise.
        wUnitWindowFE4ScrollPixels      .word ? ; $7FB125 0.23
          ; In FE4, this is how many pixels down the unit list is scrolled.
        wUnitWindowFE4PageScrollFlag    .sint ? ; $7FB127 0.23
          ; In FE4, this is set to -1 while changing pages left/right on
          ; the list of units.
        wUnitWindowFE4Action            .word ? ; $7FB129 0.23
          ; In FE4, this is the action index for the unit window.
          ; In FE5, this is set to 1 and doesn't handle actions.
        wUnitWindowFE4SortTypeFlag      .word ? ; $7FB12B 0.23
          ; TODO: values
          ; In FE4, this is set to 1 when selecting a sort type and
          ; is 0 otherwise.
        wUnitWindowUnknown7FB12D        .word ? ; $7FB12D 0.23
        wUnitWindowFE4CurrentColumn     .word ? ; $7FB12F 0.23
          ; In FE4, this is the current sort column type.
        wUnitWindowFE4UnitSwapStep      .word ? ; $7FB131 0.23
          ; In FE4, this is 1-3 when swapping two units on the list
          ; of units, and is 0 when not swapping.
        wUnitWindowFE4UnitSwapStartSlot .word ? ; $7FB133 0.23
          ; In FE4, this is the list position of the selected unit
          ; when swapping units.
        wUnitWindowFE4UnitSwapStartCursorYCoordinate .word ? ; $7FB135 0.23
          ; In FE4, this is the Y coordinate of the cursor at the initial
          ; unit being swapped.

        .fill size(word) * 3

        wUnitWindowFE4HightlightStep            .word ? ; $7FB13D 0.23
          ; In FE4, this is the current step 0-31 for cycling the
          ; unit highlight on theunit list.
          ; In FE5, this does one step, although the highlight is not used.
        wUnitWindowFE4HightlightCounter         .word ? ; $7FB13F 0.23
          ; In FE4, this is a counter 0-5 that increments
          ; wUnitWindowFE4HightlightStep when it loops.
        aUnitWindowFE4HighlightColors           .block ; $7FB141 0.23
          ; This is an array of unit list line higlight color information. In FE4,
          ; this is used to perform color math on the highlighted line. In FE5, this
          ; is initialized with color data but is never used.
          _Colors .brept 16
            .dstruct structUnitWindowFE4HighlightColor
            .endrept
          .endblock
        aUnitWindowItemIconTileIndexes          .macroUnitWindowSlots word, UnitWindowSlotCount+1 ; $7FB171 0.23
          ; These are the tile indexes of the units' equipped weapons.
          ; Units without weapons get $0000.
        aUnitWindowFE4SpriteSlots               .macroUnitWindowSlots word, UnitWindowSlotCount+1 ; $7FB1D9 0.23
          ; These mark the order of various sprites in FE4?
          ; This value is not used in FE5 after it's initially written.
        aUnitWindowFE4ReadyToPromoteFlags       .macroUnitWindowSlots word, UnitWindowSlotCount+1 ; $7FB241 0.23
          ; In FE4, these are set to 1 if the unit in the slot can promote,
          ; and are 0 otherwise. This controls displaying the little `OK!` sprite.
        wUnitWindowFE4CurrentNameLine           .word ? ; $7FB2A9 0.23
          ; In FE4, this is the tile row, measured from the first unit's line,
          ; of the unit being processed's name.
        wUnitWindowUnknown7FB2AB                .word ? ; $7FB2AB 0.23
        wUnitWindowUnknown7FB2AD                .word ? ; $7FB2AD 0.23
        wUnitWindowFE4ProcessingHighlightLine   .word ? ; $7FB2AF 0.23
          ; In FE4, this is the unit list line that the highlight system
          ; is currently processing.
        wUnitWindowFE4ProcessingHighlightOffset .word ? ; $7FB2B1 0.23
          ; In FE4, this is the current offset into the highlight colors
          ; that the highlight system is currently processing.
        wUnitWindowFE4CurrentLineSlotOffset     .word ? ; $7FB2B3 0.23
          ; In FE4, this is the offset of the currently-selected
          ; unit's slot.
        wUnitWindowUnknown7FB2B5                .word ? ; $7FB2B5 0.23
        wUnitWindowUnknown7FB2B7                .word ? ; $7FB2B7 0.23
        wUnitWindowFE4CurrentItemIconSlot       .word ? ; $7FB2B9 0.23
          ; In FE4, this is the current number of item icons drawn
          ; while drawing item icons to VRAM.
        aUnitWindowCurrentSortScores            .macroUnitWindowSlots word ; $7FB2BB 0.23
          ; This is an array of all of the current sort scores for the current
          ; sort type.

        .fill $7FDF0A - *

        aUnitWindowFE4BG1VOFSHDMATable .block ; $7FDF0A 0.23

          _Entries .brept 4

            _NTRLSetting    .byte ?
            _BG1VOFSSetting .word ?

          .endrept

        .endblock

        aUnitWindowFE4BG2VOFSHDMATable .block ; $7FDF16 0.23

          _Entries .brept 4

            _NTRLSetting    .byte ?
            _BG2VOFSSetting .word ?

          .endrept

        .endblock

        aUnitWindowFE4BG3VOFSHDMATable .block ; $7FDF22 0.23

          _Entries .brept 4

            _NTRLSetting    .byte ?
            _BG3VOFSSetting .word ?

          .endrept

        .endblock

        aUnitWindowFE4HighlightHeights .block ; $7FDF2E 0.23

          _Rows .brept 27
            .byte ?
          .endrept

        .endblock

        .fill $7FDF4C - *

        aUnitWindowFE4HighlightPackedColors .block ; $7FDF4C 0.23

          _Main .block ; $7FDF4C
            _Colors .brept 16
              .dstruct structUnitWindowFE4HighlightColor
            .endrept
          .endblock

          _Unknown .block ; $7FDF7C
            _Colors .brept 10
              .dstruct structUnitWindowFE4HighlightColor
            .endrept
          .endblock

        .endblock

        .fill $7FDFA0 - *

        aUnitWindowFE4HighlightUnpackedColors .block ; $7FDFA0 0.23

          _Entries .brept 32
            .dstruct structUnitWindowFE4HighlightColorUnpacked
          .endrept

        .endblock

      .endstruct

    .endunion

  .endvirtual

.endif ; GUARD_VOLTEDGE_WRAM
