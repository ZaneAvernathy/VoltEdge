
GUARD_VOLTEDGE_MENUS :?= false
.if (!GUARD_VOLTEDGE_MENUS)
  GUARD_VOLTEDGE_MENUS := true

  VoltEdge_Menus_Created = 0.22
  VoltEdge_Menus_Updated = 0.22

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

.endif ; GUARD_VOLTEDGE_MENUS
