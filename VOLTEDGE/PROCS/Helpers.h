
GUARD_VOLTEDGE_PROCS_HELPERS :?= false
.if (!GUARD_VOLTEDGE_PROCS_HELPERS)
  GUARD_VOLTEDGE_PROCS_HELPERS := true

  VoltEdge_Procs_Helpers_Created = 0.22
  VoltEdge_Procs_Helpers_Updated = 0.22

  ; Proc info helper

    ; Created: 0.01
    ; Updated: 0.22
    structProcInfo .struct Name, Init, OnCycle, Code
      Name
      .union
        .word $0000
        .enc "proc"
          .cdef " ~", 32
        .text \Name
      .endunion
      Init    .word <>\Init
      OnCycle .word <>\OnCycle
      Code    .word <>\Code
    .endstruct

  ; Proc code helpers

    ; These are the individual proc code commands that
    ; make up the proc code scripts. These definitions
    ; include a comment with the original address of their
    ; functions to make disassembling vanilla procs easier.

    ; Created: 0.22
    ; Updated: 0.22
    PROC_YIELD .segment Cycles
      ; This causes proc code execution to pause for
      ; the specified number of cycles. Typically,
      ; this is used to add a single cycle delay to
      ; allow for something else to be created.
      .word \Cycles
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_END .segment
      ; 82/9DB7
      ; This causes proc execution for this proc
      ; to end, and will not resume on the next
      ; proc code cycle.
      .word <>rsProcCodeEnd
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_HALT_SLEEP .segment
      ; 82/9DC5
      ; This causes proc code execution to stall
      ; here until something else changes the proc's
      ; code execution offset. Also adds a cycle
      ; of delay before continuing proc OnCycle/Code.
      .word <>rsProcCodeHaltSleep
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_HALT .segment
      ; 82/9DCB
      ; This causes proc code execution to stall
      ; here until something else changes the proc's
      ; code execution offset.
      .word <>rsProcCodeHalt
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_CALL .segment Routine
      ; 82/9DD3
      ; This calls a native assembly function.
      .word <>rsProcCodeCall
      .long \Routine
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_CALL_ARGS .segment Routine, ArgsSize
      ; 82/9DEE
      ; This calls a native assembly function.
      ; The function's parameters follow this
      ; immediately, with the ArgsSize parameter
      ; to tell the proc system how many bytes
      ; to jump over.
      .word <>rsProcCodeCallWithArgs
      .long \Routine
      .byte \ArgsSize
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_SET_ONCYCLE .segment Routine
      ; 82/9E19
      ; This sets the proc's OnCycle routine
      ; to the specified Routine.
      .word <>rsProcCodeSetOnCycle
      .word <>\Routine
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_JUMP .segment Position
      ; 82/9E2B
      ; This changes the proc code execution
      ; offset to the Position.
      .word <>rsProcCodeJump
      .word <>\Position
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_SET_UNK_TIMER .segment Cycles
      ; 82/9E30
      ; This sets a proc's aHeaderUnknownTimer
      ; to Cycles.
      .word <>rsProcCodeSetUnknownTimer
      .word \Cycles
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_JUMP_WHILE_UNK_TIMER .segment Position
      ; 82/9E39
      ; This decrements a proc's aHeaderUnknownTimer
      ; and jumps to a Position if the timer
      ; is still nonzero.
      .word <>rsProcCodeJumpWhileUnknownTimer
      .word <>\Position
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_JUMP_IF_BITS_UNSET .segment Position, Bits
      ; 82/9E41
      ; This jumps to a Position if
      ; all of the specified Bits in the
      ; proc's aHeaderBitfield are not set.
      .word <>rsProcCodeJumpIfBitsUnset
      .word <>\Position
      .word \Bits
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_JUMP_IF_BITS_SET .segment Position, Bits
      ; 82/9E4E
      ; This jumps to a Position if
      ; all of the specified Bits in the
      ; proc's aHeaderBitfield are set.
      .word <>rsProcCodeJumpIfBitsSet
      .word <>\Position
      .word \Bits
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_JUMP_IF_ROUTINE_TRUE .segment Position, Routine
      ; 82/9E77
      ; This jumps to a Position if the
      ; Routine returns carry set.
      .word <>rsProcCodeJumpIfRoutineTrue
      .long \Routine
      .word <>\Position
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_JUMP_IF_ROUTINE_FALSE .segment Position, Routine
      ; 82/9E9B
      ; This jumps to a Position if the
      ; Routine returns carry clear.
      .word <>rsProcCodeJumpIfRoutineFalse
      .long \Routine
      .word <>\Position
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_CREATE_PROC .segment Pointer
      ; 82/9EBF
      ; This creates a proc.
      .word <>rsProcCodeCreateProc
      .long \Pointer
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_FREE_PROC .segment Pointer
      ; 82/9ED5
      ; This frees a proc.
      .word <>rsProcCodeFreeProc
      .long \Pointer
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_DELETE_HDMA_ARRAY_ENTRY .segment Pointer
      ; 82/9EF1
      ; This deletes an HDMA array entry.
      .word <>rsProcCodeDeleteHDMAArrayEntry
      .long \Pointer
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_HALT_WHILE .segment Pointer
      ; 82/9F0D
      ; This stalls proc code execution while
      ; the specified proc exists.
      .word <>rsProcCodeHaltWhile
      .long \Pointer
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_CREATE_HDMA_ARRAY_ENTRY .segment Pointer
      ; 82/9F33
      ; This creates an HDMA array entry.
      .word <>rsProcCodeCreateHDMAArrayEntry
      .long \Pointer
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_HALT_WHILE_ACTIVE_SPRITE .segment Pointer
      ; 82/9F49
      ; This causes proc code execution to stall
      ; while a specified active sprite is active.
      .word <>rsProcCodeHaltWhileActiveSprite
      .long \Pointer
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_PLAY_SFX .segment Sound
      ; 82/9F6F
      ; This plays a sound effect.
      .word <>rsProcCodePlaySoundEffect
      .word \Sound
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_PLAY_EXT_SFX .segment Sound
      ; 82/9F7D
      ; This plays an extended sound effect.
      .word <>rsProcCodePlayExtendedSoundEffect
      .word \Sound
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_PLAY_SFX_PANNED_COORDS .segment Sound, Position
      ; 82/9F8B
      ; This plays a sound effect, panned
      ; horizontally to match the X pixel coordinate
      ; byte at some Position.
      .word <>rsProcCodePlaySoundEffectPannedByCoordinates
      .word \Sound
      .long \Position
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_PLAY_EXT_SFX_PANNED_COORDS .segment Sound, Position
      ; 82/9FAF
      ; This plays an extended sound effect, panned
      ; horizontally to match the X pixel coordinate
      ; byte at some Position.
      .word <>rsProcCodePlayExtendedSoundEffectPannedByCoordinates
      .word \Sound
      .long \Position
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_PLAY_SFX_PANNED_ROUTINE .segment Sound, Routine
      ; 82/9FD3
      ; This plays a sound effect, panned
      ; horizontally to match the X pixel coordinate
      ; returned by some Routine
      .word <>rsProcCodePlaySoundEffectPannedByRoutine
      .word \Sound
      .long \Routine
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_PLAY_EXT_SFX_PANNED_ROUTINE .segment Sound, Routine
      ; 82/9FFB
      ; This plays an extended sound effect, panned
      ; horizontally to match the X pixel coordinate
      ; returned by some Routine
      .word <>rsProcCodePlayExtendedSoundEffectPannedByRoutine
      .word \Sound
      .long \Routine
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_PLAY_SONG .segment Song
      ; 82/A023
      ; This plays a given Song.
      .word <>rsProcCodePlaySong
      .word \Song
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_HALT_UNTIL_SONG_PLAYING .segment
      ; 82/A02C
      ; This stalls proc code execution until
      ; the currently-requested song is playing.
      .word <>rsProcCodeHaltUntilSongPlaying
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_SONG_FADE_OUT .segment Speed
      ; 82/A040
      ; This fades the music into silence
      ; at a given Speed (0-7, lower is faster).
      .word <>rsProcCodeSongFadeOut
      .word \Speed
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_HALT_WHILE_DECOMPRESSING .segment
      ; 82/A04A
      ; This stalls proc code execution
      ; unitl bDecompressionArrayFlag is zero.
      .word <>rsProcCodeHaltWhileDecompressing
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_BL .segment Pointer
      ; 82/A05E
      ; This sets the proc code execution
      ; offset to Pointer and stores the
      ; return address over the proc's
      ; aHeaderName. This is for calling proc
      ; code subroutines that end with
      ; PROC_RETURN.
      .word <>rsProcCodeBranchAndLink
      .word <>\Pointer
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_RETURN .segment
      ; 82/A06B
      ; This returns proc code execution to the
      ; address stored in the proc's aHeaderName.
      ; This is what ends proc code subroutines
      ; that are meant to be called with PROC_BL.
      .word <>rsProcCodeReturn
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_HALT_UNTIL_BUTTON_NEW .segment ButtonCombo
      ; 82/A070
      ; This stalls proc code execution until
      ; a specific button (or combination) is
      ; newly pressed.
      .word <>rsProcCodeHaltUntilButtonsNewPressed
      .word \ButtonCombo
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_HALT_UNTIL_BUTTON_NEW_TIME .segment Time, ButtonCombo
      ; 82/A09A
      ; This stalls proc code execution until
      ; a specific button (or combination) is
      ; newly pressed or when a timer runs out.
      .word <>rsProcCodeHaltUntilButtonsNewPressedOrTime
      .word \Time
      .word \ButtonCombo
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_JUMP_IF_BUTTON .segment Position, ButtonCombo
      ; 82/A0B9
      ; This jumps to a Position if a
      ; button (or combination) is pressed.
      .word <>rsProcCodeJumpIfButtons
      .word \ButtonCombo
      .word <>\Position
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_DECOMPRESS .segment Source, Dest
      ; 82/A0CA
      ; This decompresses data from
      ; Source to Dest.
      .word <>rsProcCodeDecompress
      .long \Source
      .long \Dest
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    PROC_DMA .segment Source, Size, Dest
      ; 82/A0ED
      ; This DMAs data with size Size
      ; from Source to Dest in VRAM.
      ; This assumes that you want to feed it
      ; the actual VRAM address and not the
      ; address in word-increments.
      .word <>rsProcCodeDMA
      .long \Source
      .word \Size
      .word \Dest >> 1
    .endsegment

.endif ; GUARD_VOLTEDGE_PROCS_HELPERS
