
GUARD_VOLTEDGE_SRAM :?= false
.if (!GUARD_VOLTEDGE_SRAM)
  GUARD_VOLTEDGE_SRAM := true

  VoltEdge_SRAM_Created = 0.01
  VoltEdge_SRAM_Updated = 0.02

  .virtual $700000

    ; Created: 0.01
    ; Updated: 0.01
    aSRAM .block

      aSaveDataHeader  .dstruct structSaveDataHeader ; $700000
      aSaveSlot1       .dstruct structSaveDataEntry  ; $700008
      aSaveSlot2       .dstruct structSaveDataEntry  ; $702000
      aSaveSlot3       .dstruct structSaveDataEntry  ; $703FF8
      aSaveSlotSuspend .dstruct structSaveDataEntry  ; $705FF0
      .fill ($708000 - *), ?

    .bend

  .endv

.endif ; GUARD_VOLTEDGE_SRAM
