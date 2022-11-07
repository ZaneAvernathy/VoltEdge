
GUARD_VOLTEDGE_HDMA_HELPERS :?= false
.if (!GUARD_VOLTEDGE_HDMA_HELPERS)
  GUARD_VOLTEDGE_HDMA_HELPERS := true

  VoltEdge_HDMA_Helpers_Created = 0.22
  VoltEdge_HDMA_Helpers_Updated = 0.22

  ; HDMA info helpers

    ; Created: 0.22
    ; Updated: 0.22
    structHDMADirectEntryInfo .struct Init, OnCycle, Code, HDMATable, BBADxSetting, DMAPxSetting
      Init    .word <>\Init
      OnCycle .word <>\OnCycle
      Code    .word <>\Code
      .union
        .struct
          TableOffset       .word ?
          TableBankAndBBADx .word ?
        .endstruct
        .struct
          Table .long \HDMATable
          BBADx .byte (\BBADxSetting - PPU_REG_BASE)
        .endstruct
      .endunion
      DMAPx .byte \DMAPxSetting
    .endstruct

    ; Created: 0.22
    ; Updated: 0.22
    structHDMAIndirectEntryInfo .struct Init, OnCycle, Code, HDMATable, BBADxSetting, DMAPxSetting, IndirectBank
      Init    .word <>\Init
      OnCycle .word <>\OnCycle
      Code    .word <>\Code
      .union
        .struct
          TableOffset       .word ?
          TableBankAndBBADx .word ?
        .endstruct
        .struct
          Table .long \HDMATable
          BBADx .byte (\BBADxSetting - PPU_REG_BASE)
        .endstruct
      .endunion
      DMAPx .byte \DMAPxSetting
      IndirectBank .byte \IndirectBank
    .endstruct

  ; HDMA code helpers

    ; Created: 0.22
    ; Updated: 0.22
    HDMA_YIELD .segment Cycles, Offset
      ; This causes the HDMA entry to sleep for
      ; a number of Cycles, resetting its aOffset
      ; to Offset.
      .word \Cycles, <>\Offset
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    HDMA_SLEEP .segment Cycles
      ; 82/A5A8
      ; This causes the HDMA entry to sleep for
      ; a number of Cycles, pausing execution of
      ; its code while nonzero.
      .word <>rsHDMACodeSleep
      .word \Cycles
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    HDMA_END .segment
      ; 82/A5B6
      ; This causes execution for this HDMA entry
      ; to end, and will not resume next cycle.
      .word <>rsHDMACodeEnd
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    HDMA_HALT_SLEEP .segment
      ; 82/A5C4
      ; This causes code execution to stall until something
      ; else changes its code execution offset. It also sets
      ; the entry's aSleepTimer to 1.
      .word <>rsHDMACodeHaltSleep
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    HDMA_HALT .segment
      ; 82/A5CA
      ; This causes code execution to stall until something
      ; else changes its code execution offset.
      .word <>rsHDMACodeHalt
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    HDMA_CALL .segment Routine
      ; 82/A5D2
      ; This calls a native assembly function.
      .word <>rsHDMACodeCall
      .long \Routine
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    HDMA_SET_ONCYCLE .segment OnCycle
      ; 82/A5ED
      ; This sets the entry's OnCycle routine to
      ; a function within the same bank as the HDMA entry info.
      .word <>rsHDMACodeSetOnCycle
      .word <>\OnCycle
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    HDMA_JUMP .segment Position
      ; 82/A5FF
      ; Unconditionally jumps to a Position.
      .word <>rsHDMACodeJump
      .word <>\Position
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    HDMA_SET_TIMER .segment Time
      ; 82/A604
      ; Sets the entry's aTimer to a Time.
      .word <>rsHDMACodeSetTimer
      .word \Time
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    HDMA_JUMP_WHILE_TIMER .segment Position
      ; 82/A60D
      ; Decrements the entry's aTimer and jumps to
      ; a Position while it is nonzero.
      .word <>rsHDMACodeJumpWhileTimer
      .word <>\Position
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    HDMA_JUMP_IF_BITS_UNSET .segment Position, Bits
      ; 82/A615
      ; Jumps to a Position if all of the specified
      ; Bits in the entry's aBitfield are not set.
      .word <>rsHDMACodeJumpIfBitsUnset
      .word <>\Position
      .word \Bits
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    HDMA_JUMP_IF_BITS_SET .segment Position, Bits
      ; 82/A622
      ; Jumps to a Position if all of the specified
      ; Bits in the entry's aBitfield are set.
      .word <>rsHDMACodeJumpIfBitsSet
      .word <>\Position
      .word \Bits
    .endsegment

    ; Created: 0.22
    ; Updated: 0.22
    HDMA_SET_INDIRECT_BANK .segment Bank
      ; 82/A62F
      ; Sets the entry's aDMAPxAndIndirectBank.bIndirectBank
      .word <>rsHDMACodeSetTableBank
      .byte \Bank
    .endsegment

.endif ; GUARD_VOLTEDGE_HDMA_HELPERS
