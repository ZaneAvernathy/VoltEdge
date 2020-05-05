
GUARD_VOLTEDGE_WRAM :?= false
.if (!GUARD_VOLTEDGE_WRAM)
  GUARD_VOLTEDGE_WRAM := true

  VoltEdge.WRAM .namespace

    Created = 0.01
    Updated = 0.01

  .endn

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
        .ends
      .endu
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
    .bend

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

  .endv

  .virtual $0000BC

    bBufferNMITIMEN .byte ? ; $0000BC 0.01
    bBufferVTIMEL   .byte ? ; $0000BD 0.01
    bBufferVTIMEH   .byte ? ; $0000BE 0.01
    bBufferHTIMEL   .byte ? ; $0000BF 0.01
    bBufferHTIMEH   .byte ? ; $0000C0 0.01
    bBufferHDMAEN   .byte ? ; $0000C1 0.01
    bBufferMEMSEL   .byte ? ; $0000C2 0.01

  .endv

  .virtual $0000D3

    ; These are used for NMI and IRQ
    ; interrupts.

    wUnknown0000D3 .word ? ; $0000D3 0.01
    wUnknown0000D5 .word ? ; $0000D5 0.01
    wUnknown0000D7 .word ? ; $0000D7 0.01
    wUnknown0000D9 .word ? ; $0000D9 0.01
    wUnknown0000DB .word ? ; $0000DB 0.01
    wUnknown0000DD .word ? ; $0000DD 0.01

  .endv

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
    .bend

    aOAMPaletteBuffer .block     ; $000200 0.01
      aPalette0 .dstruct Palette ; $000200 0.01
      aPalette1 .dstruct Palette ; $000220 0.01
      aPalette2 .dstruct Palette ; $000240 0.01
      aPalette3 .dstruct Palette ; $000260 0.01
      aPalette4 .dstruct Palette ; $000280 0.01
      aPalette5 .dstruct Palette ; $0002A0 0.01
      aPalette6 .dstruct Palette ; $0002C0 0.01
      aPalette7 .dstruct Palette ; $0002E0 0.01
    .bend

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
    .bend
      ; This is a block memory copy
      ; routine that is copied to RAM
      ; and has the parameters of the
      ; mvn opcode modified to fit the
      ; source and destination.
    rsBlockCopyMVPRAM .block      ; $0004B2 0.01
      mvp #$00,#$00
      rts
    .bend
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
        .ends
      .endu
    .bend

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
    .bend

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
    .bend

  .endv

  .virtual $000DDE

    lUnknown000DDE .long ? ; $000DDE 0.01
    lUnknown000DE1 .long ? ; $000DE1 0.01
    lUnknown000DE4 .long ? ; $000DE4 0.01
    wUnknown000DE7 .word ? ; $000DE7 0.01
    wUnknown000DE9 .word ? ; $000DE9 0.01

  .endv

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

  .endv

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

  .endv

  .virtual $00172C

    wEventEngineStatus .word ? ; $00172C 0.01
      ; This is a status bitfield
      ; that controls the event engine.

  .endv

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

  .endv

  .virtual $7E4E18

    ; These variables correspond to
    ; the options menu settings.

    aOptions .block              ; $7E4E18 0.01
      wWindow .word ?            ; $7E4E18 0.01
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
      .next
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
    .bend

  .endv

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

  .endv

  .virtual $7E524C

    wUnknownMapBattleFlag .word ? ; $7E524C 0.01
      ; Needs research. Seems to be
      ; set to 1 during map battles.
    wUnknown7E524E .word ?        ; $7E524E 0.01
      ; Needs research. Normally 0,
      ; incremented during battles?

  .endv

  .virtual $7E6FCB

    ; These arrays are for units/tiles
    ; on the map.

    aPlayerVisibleUnitMap .fill $600 ; $7E6FCB 0.01
      ; This map is filled with the
      ; deployment numbers of units
      ; visible to the player. If there
      ; is no visible unit at a tile,
      ; the value in the map is 00.
    aUnitMap              .fill $600 ; $7E75CB 0.01
      ; This map is filled with the
      ; deployment numbers of all
      ; units. If there is no unit
      ; at that tile, the value in
      ; the map is 00.

  .endv

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

  .endv

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

  .endv

  .virtual $7EC1AF

    ; These are for keeping track of map sprites
    ; and status effect sprites on the map.

    aUpperMapSpriteAndStatusBuffer .fill (120 * size(structMapSpriteAndStatusEntry)) ; $7EC1AF 0.01
    aLowerMapSpriteBuffer .fill (127 * size(structMapSpriteAndStatusEntry))          ; $7EC47F 0.01

    lUnknown7EC779 .long ? ; $7EC779 0.01

    ; These are buffers for each tilemap layer.

    aBG1TilemapBuffer .fill $1000 ; $7EC77C 0.01
    aBG2TilemapBuffer .fill $1000 ; $7ED77C 0.01
    aBG3TilemapBuffer .fill $1000 ; $7EE77C 0.01

  .endv

  .virtual $7FAA14

    wMapBattleFlag .word ? ; $7FAA14 0.01
        ; This is set to 1 during
        ; map sprite battles.

  .endv

  .virtual $7FAA42

    aActiveMapSpriteIndexArray .fill (size(word) * 4)      ; $7FAA42 0.01
      ; These are the sprite IDs
      ; of active map sprites.
    aActiveMapSpriteUnknownBitfield .fill (size(word) * 4) ; $7FAA4A 0.01
      ; These status bitfields are
      ; for controlling the active
      ; map sprites.

    .endv

  .virtual $7FAAAA

    aActiveMapSpriteMovementSpeedArray .fill (size(word) * 4) ; $7FAAAA 0.01
      ; These control the movement speed
      ; of active moving map sprites.

  .endv

.endif ; GUARD_VOLTEDGE_WRAM
