
GUARD_VOLTEDGE_PALETTES :?= false
.if (!GUARD_VOLTEDGE_PALETTES)
  GUARD_VOLTEDGE_PALETTES := true

  VoltEdge.Palettes .namespace

    Created = 0.01
    Updated = 0.01

  .endn

  ; Palette constants

    ; Created = 0.01
    ; Updated = 0.01
    Color_Unused = bits(%1000000000000000)
    Color_Blue   = bits(%0111110000000000)
    Color_Green  = bits(%0000001111100000)
    Color_Red    = bits(%0000000000011111)

  ; Palette helpers

    ; Created = 0.01
    ; Updated = 0.01
    Color .struct
      .fill len(bytes(Color_Red | Color_Green | Color_Blue))
    .ends

    ; Created = 0.01
    ; Updated = 0.01
    Palette .struct
      Colors .brept 16
        .dstruct Color
      .next
    .ends

.endif ; GUARD_VOLTEDGE_PALETTES
