
GUARD_VOLTEDGE_MENUS :?= false
.if (!GUARD_VOLTEDGE_MENUS)
  GUARD_VOLTEDGE_MENUS := true

  VoltEdge_Menus_Created = 0.22
  VoltEdge_Menus_Updated = 0.23

  ; Definitions

    ; Created: 0.23
    ; Updated: 0.23
    UnitWindowSlotCount = 51

  ; Helpers

    ; Created: 0.22
    ; Updated: 0.22
    structOptionsWindowLine .struct Usability=?, NameText=?, OptionText=?, SubtitleText=?, OnOpen=?, OnClose=?, IconVRAM=?
      .if (\Usability === ?)
        Usability    .addr ?
        NameText     .addr ?
        OptionText   .addr ?
        SubtitleText .addr ?
        OnOpen       .addr ?
        OnClose      .addr ?
        IconVRAM     .word ?
        OptionCount  .word ?
        ; It seems like vanilla acts like there
        ; can be 6 options but doesn't include
        ; space for the last's width?
        Options .brept 5
          Position .word ?
          Width    .word ?
        .endrept
        .word ?
      .else ; (\Usability === ?)
        .word <>\Usability, <>\NameText, <>\OptionText, <>\SubtitleText, <>\OnOpen, <>\OnClose, \IconVRAM
        .word \OptionText._Count
        .for _Position, _Width in \OptionText._OptionsInfo
          .word _Position, _Width
        .endfor
      .endif ; (\Usability === ?)
    .endstruct

    ; Created: 0.23
    ; Updated: 0.23
      structActiveMenu .struct
        EnabledFlag .byte ?
        Position .block
          X .byte ?
          Y .byte ?
        .endblock
        ShadingDisabledFlag .byte ?
        MenuStructPointer .long ?
        BG1Info .dstruct structTilemapInfo
        BG3Info .dstruct structTilemapInfo
      .endstruct

    ; Created: 0.23
    ; Updated: 0.23
      macroUnitWindowSlots .macro Field, Size=UnitWindowSlotCount
        _Slots .brept \Size
          .fill size(\Field), ?
        .endrept
      .endmacro

    ; Created: 0.23
    ; Updated: 0.23
      structUnitWindowFE4HighlightColor .struct ColorData0, ColorData1, Control=CGADSUB_Setting(CGADSUB_Add, false, true, false, false, false, false, false)
        .if (\ColorData0 === ?)
          Control    .byte ?
          ColorData0 .byte ?
          ColorData1 .byte ?
        .else
          .byte \Control, \ColorData0, \ColorData1
        .endif
      .endstruct

    ; Created: 0.23
    ; Updated: 0.23
      structUnitWindowFE4HighlightColorUnpacked .struct
        LineCount .byte ?
        CGADSUB   .word ?
        COLDATA   .word ?
      .endstruct

    ; Created: 0.23
    ; Updated: 0.23
      macroUnitWindowPageElement .macro XOffset, TextGetter, Renderer, BaseTile
        .if (\XOffset === ?)
          XOffset    .byte ?
          TextGetter .long ?
          Renderer   .long ?
          BaseTile   .word ?
        .else
          XOffset    .byte \XOffset
          TextGetter .long \TextGetter
          Renderer   .long \Renderer
          BaseTile   .word \BaseTile
        .endif
      .endmacro

.endif ; GUARD_VOLTEDGE_MENUS
