
GUARD_VOLTEDGE_BATTLE :?= false
.if (!GUARD_VOLTEDGE_BATTLE)
  GUARD_VOLTEDGE_BATTLE := true

  VoltEdge_Battle_Created = 0.17
  VoltEdge_Battle_Updated = 0.17

  ; Created: 0.17
  ; Updated: 0.17
  structBattleGeneratedRound .struct
    Bitfield1 .byte ? ; $00
    Bitfield2 .word ? ; $01
    Damage    .byte ? ; $03
  .endstruct

.endif ; GUARD_VOLTEDGE_BATTLE
