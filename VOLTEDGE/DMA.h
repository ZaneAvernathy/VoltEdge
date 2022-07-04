
GUARD_VOLTEDGE_DMA :?= false
.if (!GUARD_VOLTEDGE_DMA)
  GUARD_VOLTEDGE_DMA := true

  VoltEdge_DMA_Created = 0.01
  VoltEdge_DMA_Updated = 0.20

  ; DMA constants

    .weak

      ; Created: 0.01
      ; Updated: 0.01
      ; DMA struct types
      DMAToCGRAM          :?= 1
      DMAToVRAM           :?= 2
      DMAFromVRAM         :?= 3
      DMAInputDestination :?= 4

    .endweak

  ; DMA Helpers

    ; Created: 0.01
    ; Updated: 0.07
    structDMAChannel .struct Parameters, Port, Source, Count
      Parameters .byte \Parameters
      Port .byte \Port
      Source .long \Source
      Count .word \Count
    .endstruct

    ; Created: 0.01
    ; Updated: 0.20
    structDMAToCGRAM .struct Source, Count, StartIndex
      .if (\Source === ?)
        TransferType .byte ?
        Source .long ?
        Count .word ?
        StartIndex .byte ?
      .else
        .byte DMAToCGRAM
        .long \Source
        .if (\Count == $10000)
          .word 0
        .else
          .word \Count
        .endif
        .byte \StartIndex
      .endif
    .endstruct

    ; Created: 0.01
    ; Updated: 0.20
    structDMAToVRAM .struct Source, Count, Mode, Destination
      .if (\Source === ?)
        TransferType .byte ?
        Source .long ?
        Count .word ?
        Mode .byte ?
        Destination .word ?
      .else
        .byte DMAToVRAM
        .long \Source
        .if (\Count == $10000)
          .word 0
        .else
          .word \Count
        .endif
        .byte \Mode
        .word (\Destination >> 1)
      .endif
    .endstruct

    ; Created: 0.01
    ; Updated: 0.20
    structDMAFromVRAM .struct Destination, Count, Mode, Source
      .if (\Source === ?)
        TransferType .byte ?
        Destination .long ?
        Count .word ?
        Mode .byte ?
        Source .word ?
      .else
        .byte DMAFromVRAM
        .long \Destination
        .if (\Count == $10000)
          .word 0
        .else
          .word \Count
        .endif
        .byte \Mode
        .word (\Source >> 1)
      .endif
    .endstruct

    ; Created: 0.01
    ; Updated: 0.20
    structDMAInputPort .struct Source, Count, Parameter, Port, Mode, Destination
      .if (\Source === ?)
        TransferType .byte ?
        Source .long ?
        Count .word ?
        Parameter .byte ?
        Port .byte ?
        Mode .byte ?
        Destination .word ?
      .else
        .byte DMAInputDestination
        .long \Source
        .if (\Count == $10000)
          .word 0
        .else
          .word \Count
        .endif
        .byte \Parameter
        .byte \Port
        .byte \Mode
        .word (\Destination >> 1)
      .endif
    .endstruct

.endif ; GUARD_VOLTEDGE_DMA