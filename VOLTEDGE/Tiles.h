
GUARD_VOLTEDGE_TILES :?= false
.if (!GUARD_VOLTEDGE_TILES)
  GUARD_VOLTEDGE_TILES := true

  VoltEdge_Tiles_Created = 0.01
  VoltEdge_Tiles_Updated = 0.02

  ; Tile constants

    ; Tile sizes

      ; Created: 0.01
      ; Updated: 0.01
      Tile2bpp .struct
        .fill ((2 * 64) / 8)
      .ends

      ; Created: 0.01
      ; Updated: 0.01
      Tile4bpp .struct
        .fill ((4 * 64) / 8)
      .ends

      ; Created: 0.01
      ; Updated: 0.01
      Tile8bpp .struct
        .fill ((8 * 64) / 8)
      .ends

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
    ; Updated: 0.01
    ; TilemapEntry

      ; This function creates a hardware
      ; tilemap entry that can be used with
      ; .word or in opcode parameters.

      ; Examples:

      ; .word TilemapEntry($000, 1, false, false, false)

      ; lda #TilemapEntry($012, 3, false, true, true)

      TilemapEntry .function TileIndex, Palette, Priority, XFlip, YFlip
      .endf bits((int(YFlip) << 15) | (int(XFlip) << 14) | (int(Priority) << 13) | ((Palette << 10) & TM_Palette) | (TileIndex & TM_TileIndex))

    ; Created: 0.01
    ; Updated: 0.01
    ; VRAMToTile

      ; This function converts an actual
      ; VRAM address to its offset past a base
      ; address in word steps.

      VRAMToTile .function Offset, Base, TileSize=size(Tile4bpp)
      .endf ((Offset - Base) / TileSize)

.endif ; GUARD_VOLTEDGE_TILES
