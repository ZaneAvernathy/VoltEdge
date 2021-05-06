
GUARD_VOLTEDGE_SPRITES :?= false
.if (!GUARD_VOLTEDGE_SPRITES)
  GUARD_VOLTEDGE_SPRITES := true

  VoltEdge_Sprites_Created = 0.01
  VoltEdge_Sprites_Updated = 0.07

  ; Created: 0.01
  ; Updated: 0.01
  ; Sprite constants

    SpriteSmall = 0
    SpriteLarge = 1

  ; Sprite Helpers

    ; Created: 0.01
    ; Updated: 0.07
    structSpriteEntry .struct Coordinates, Unknown, Size, Index, Priority, Palette, HFlip, VFlip
      ; size(), len() use type(gap) for fields
      .if (type(\Coordinates) == gap)
        xc := ?
        yc := ?
      .else
        xc := \Coordinates[0]
        yc := \Coordinates[1]
      .endif
      .if (type(\VFlip) == gap)
        vf := ?
      .else
        vf := int(\VFlip)
      .endif
      .if (type(\HFlip) == gap)
        hf := ?
      .else
        hf := int(\HFlip)
      .endif
      X .word (\Size << 15) | (\Unknown << 9) | (xc & $1FF)
      Y .char yc
      Attr .word (vf << 15) | (hf << 14) | (\Priority << 12) | (\Palette << 9) | \Index
    .endstruct

    ; Created: 0.01
    ; Updated: 0.07
    structSpriteArray .struct SpriteList
      ; size(), len() use type(gap) for fields
      .if (type(\SpriteList) == gap)
        SpriteCount .fill 2
        Sprites
      .else
        SpriteCount .word len(\SpriteList)
        Sprites .bfor i := 0, i < len(\SpriteList), i += 1
          .dstruct structSpriteEntry, \SpriteList[i][0], \SpriteList[i][1], \SpriteList[i][2], \SpriteList[i][3], \SpriteList[i][4], \SpriteList[i][5], \SpriteList[i][6], \SpriteList[i][7]
        .next
      .endif
    .endstruct

    ; Created: 0.01
    ; Updated: 0.07
    OAMTileAndAttr .function TileIndex, Pal, Priority, XFlip, YFlip
    .endfunction ((int(YFlip) << 15) | (int(XFlip) << 14) | ((Priority & $3) << 12) | ((Pal & $7) << 9) | TileIndex)

    ; Created: 0.01
    ; Updated: 0.07
    structPPUOAMEntry .struct
      X .byte ?
      Y .byte ?
      Index .byte ?
      Attributes .byte ?
    .endstruct

    ; Created: 0.01
    ; Updated: 0.07
    structMapSpriteAndStatusEntry .struct
      X .word ?
      Y .word ?
      .union
        TileAndAttr .word ?
        HiddenStatusFlag .word ?
      .endunion
    .endstruct

.endif ; GUARD_VOLTEDGE_SPRITES
