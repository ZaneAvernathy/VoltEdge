
GUARD_VOLTEDGE_TILES :?= false
.if (!GUARD_VOLTEDGE_TILES)
  GUARD_VOLTEDGE_TILES := true

  VoltEdge_Tiles_Created = 0.01
  VoltEdge_Tiles_Updated = 0.07

  ; Tile constants

    ; Tile sizes

      ; Created: 0.01
      ; Updated: 0.07
      Tile2bpp .struct
        .fill ((2 * 64) / 8)
      .endstruct

      ; Created: 0.01
      ; Updated: 0.07
      Tile4bpp .struct
        .fill ((4 * 64) / 8)
      .endstruct

      ; Created: 0.01
      ; Updated: 0.07
      Tile8bpp .struct
        .fill ((8 * 64) / 8)
      .endstruct

    ; Tilemap entry bitmasks

      ; Created: 0.01
      ; Updated: 0.01
      TM_VFlip     = bits(%1000000000000000)
      TM_HFlip     = bits(%0100000000000000)
      TM_Priority  = bits(%0010000000000000)
      TM_Palette   = bits(%0001110000000000)
      TM_TileIndex = bits(%0000001111111111)

  ; Tile helpers

    ; Created: 0.01
    ; Updated: 0.07
    ; TilemapEntry

      ; This function creates a hardware
      ; tilemap entry that can be used with
      ; .word or in opcode parameters.

      ; Examples:

      ; .word TilemapEntry($000, 1, false, false, false)

      ; lda #TilemapEntry($012, 3, false, true, true)

      TilemapEntry .function TileIndex, Pal, Priority, XFlip, YFlip
      .endfunction bits((int(YFlip) << 15) | (int(XFlip) << 14) | (int(Priority) << 13) | ((Pal << 10) & TM_Palette) | (TileIndex & TM_TileIndex))

    ; Created: 0.01
    ; Updated: 0.07
    ; VRAMToTile

      ; This function converts an actual
      ; VRAM address to its offset past a base
      ; address in word steps.

      VRAMToTile .sfunction Offset, Base, TileSize=size(Tile4bpp), ((Offset - Base) / TileSize)

.endif ; GUARD_VOLTEDGE_TILES
