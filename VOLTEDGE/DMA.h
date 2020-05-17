
GUARD_VOLTEDGE_DMA :?= false
.if (!GUARD_VOLTEDGE_DMA)
  GUARD_VOLTEDGE_DMA := true

  VoltEdge_DMA_Created = 0.01
  VoltEdge_DMA_Updated = 0.02

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
    ; Updated: 0.01
    structDMAChannel .struct Parameters, Port, Source, Count
      Parameters .byte \Parameters
      Port .byte \Port
      Source .long \Source
      Count .word \Count
    .ends

    ; Created: 0.01
    ; Updated: 0.01
    structDMAToCGRAM .struct Source, Count, StartIndex
      .if (type(\Source) == gap)
        TransferType .byte ?
        Source .long ?
        Count .word ?
        StartIndex .byte ?
      .else
        TransferType .byte DMAToCGRAM
        Source .long \Source
        Count
        .if (\Count == $10000)
          .word 0
        .else
          .word \Count
        .endif
        StartIndex .byte \StartIndex
      .endif
    .ends

    ; Created: 0.01
    ; Updated: 0.01
    structDMAToVRAM .struct Source, Count, Mode, Destination
      .if (type(\Source) == gap)
        TransferType .byte ?
        Source .long ?
        Count .word ?
        Mode .byte ?
        Destination .word ?
      .else
        TransferType .byte DMAToVRAM
        Source .long \Source
        Count
        .if (\Count == $10000)
          .word 0
        .else
          .word \Count
        .endif
        Mode .byte \Mode
        Destination .word (\Destination >> 1)
      .endif
    .ends

    ; Created: 0.01
    ; Updated: 0.01
    structDMAFromVRAM .struct Destination, Count, Mode, Source
      .if (type(\Source) == gap)
        TransferType .byte ?
        Destination .long ?
        Count .word ?
        Mode .byte ?
        Source .word ?
      .else
        TransferType .byte DMAFromVRAM
        Destination .long \Destination
        Count
        .if (\Count == $10000)
          .word 0
        .else
          .word \Count
        .endif
        Mode .byte \Mode
        Source .word (\Source >> 1)
      .endif
    .ends

    ; Created: 0.01
    ; Updated: 0.01
    structDMAInputPort .struct Source, Count, Parameter, Port, Mode, Destination
      .if (type(\Source) == gap)
        TransferType .byte ?
        Source .long ?
        Count .word ?
        Parameter .byte ?
        Port .byte ?
        Mode .byte ?
        Destination .word ?
      .else
        TransferType .byte DMAInputDestination
        Source .long \Source
        Count
        .if (\Count == $10000)
          .word 0
        .else
          .word \Count
        .endif
        Parameter .byte \Parameter
        Port .byte \Port
        Mode .byte \Mode
        Destination .word (\Destination >> 1)
      .endif
    .ends

.endif ; GUARD_VOLTEDGE_DMA