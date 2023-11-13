
GUARD_VOLTEDGE_BATTLE_MAPSPRITE_SCRIPT_HELPERS :?= false
.if (!GUARD_VOLTEDGE_BATTLE_MAPSPRITE_SCRIPT_HELPERS)
  GUARD_VOLTEDGE_BATTLE_MAPSPRITE_SCRIPT_HELPERS := true

  VoltEdge_BattleMapSpriteScriptHelpers_Created = 0.23
  VoltEdge_BattleMapSpriteScriptHelpers_Updated = 0.23

  ; This file is intended to be included on its own within a
  ; battle map sprite script, and as such is not included
  ; with the main library.

  ; General Helpers

    None = 0

    Small = 0
    Large = 1

  ; Object helpers

    Object .struct Coordinates, Size, Index, Priority, Palette, HFlip, VFlip
      .if !(\Coordinates === ?)
        xc := \Coordinates[0]
        yc := \Coordinates[1]
        hf := int(\HFlip)
        vf := int(\VFlip)
        .word (\Size << 15) | ((\Size == Small ? $00 : $21) << 9) | (xc & $1FF)
        .char yc
        .word (vf << 15) | (hf << 14) | (\Priority << 12) | (\Palette << 9) | \Index
      .endif
    .endstruct

    Sprite .struct ObjectList
      .if !(\ObjectList === ?)
        .word len(\ObjectList)
        .for _Object in \ObjectList
          _Coords   := _Object[0]
          _Size     := _Object[1]
          _Index    := _Object[2]
          _Priority := _Object[3]
          _Palette  := _Object[4]
          _HFlip    := _Object[5]
          _VFlip    := _Object[6]
          .dstruct Object, _Coords, _Size, _Index, _Priority, _Palette, _HFlip, _VFlip
        .endfor
      .endif
    .endstruct

  ; Object index helpers

    Common .sfunction Index, Index
      ; This type of object is drawn from the BMS's
      ; `common` graphics.

    Shadow .sfunction Index, $100 | Index
      ; This type of object is drawn from a fixed set
      ; of graphics.

    ShadowSmall      = Shadow($00F)
    ShadowNormal     = Shadow($00E)
    ShadowLargeLeft  = Shadow($01E)
    ShadowLargeRight = Shadow($01F)

    Normal .function Cel, Index, Lower, Set2

      Result := $80 | Index

      Result |= (Cel & %011) << 2
      Result |= (Cel & %100) << 4

      Result |= Lower ? $10 : None

      Result |= Set2 ? $20 : None

    .endfunction Result

  ; Script helpers

    DIRECTIONS .macro UpRight, Up, UpLeft, Right, Left, DownRight, Down, DownLeft
      .word \UpRight
      .word \Up
      .word \UpLeft
      .word \Right
      .word \Left
      .word \DownRight
      .word \Down
      .word \DownLeft
    .endmacro

    NORMAL_MODES .macro Idle, Dodge, Melee, Ranged
      _Start := *
      .word \Idle - _Start
      .word \Idle - _Start
      .word \Dodge - _Start
      .word \Idle - _Start
      .word \Melee - _Start
      .word \Idle - _Start
      .word \Ranged - _Start
      .word \Idle - _Start
    .endmacro

  ; Script commands

    MODE_END .macro
      .byte $01
    .endmacro

    MODE_LOOP .macro Position
      .byte $16
      .char \Position - *
    .endmacro

    MODE_FRAME .macro Time, Direction, Frame
      .byte $18
      .byte \Time
      .word \Frame - \Direction + $0E
    .endmacro

    MODE_IDLE .macro
      .byte $22
    .endmacro

    MODE_ATTACK .macro
      .byte $23
    .endmacro

    MODE_BEGIN_SPELL .macro
      .byte $25
    .endmacro

    MODE_HALT_WHILE_SPELL .macro
      .byte $26
    .endmacro

    MODE_SIGNAL_ATTACK_FINISHED .macro
      .byte $29
    .endmacro

    MODE_WAIT_UNTIL_ATTACK_FINISHED .macro
      .byte $2A
    .endmacro

    MODE_PLAY_SOUND .macro Sound
      .byte $2B
      .word \Sound
    .endmacro

.endif ; GUARD_VOLTEDGE_BATTLE_MAPSPRITE_SCRIPT_HELPERS
