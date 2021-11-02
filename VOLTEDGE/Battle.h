
GUARD_VOLTEDGE_BATTLE :?= false
.if (!GUARD_VOLTEDGE_BATTLE)
  GUARD_VOLTEDGE_BATTLE := true

  VoltEdge_Battle_Created = 0.17
  VoltEdge_Battle_Updated = 0.18

  ; Created: 0.17
  ; Updated: 0.18
  structBattleGeneratedRound .struct
    FlowFlagBitfield   .byte ? ; $00
    AttackFlagBitfield .word ? ; $01
    Damage             .byte ? ; $03
  .endstruct

.endif ; GUARD_VOLTEDGE_BATTLE
