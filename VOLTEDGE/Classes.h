
GUARD_VOLTEDGE_CLASSES :?= false
.if (!GUARD_VOLTEDGE_CLASSES)
  GUARD_VOLTEDGE_CLASSES := true

  VoltEdge_Classes_Created = 0.01
  VoltEdge_Classes_Updated = 0.07

  ; Class helpers

  ; Created: 0.01
  ; Updated: 0.07
  structClassDataEntry .struct HP, Strength, Magic, Skill, Speed, Defense, Constitution, Movement, ClassRelativePower, SwordRank, LanceRank, AxeRank, BowRank, StaffRank, FireRank, ThunderRank, WindRank, LightRank, DarkRank, Skills1, Skills2, Skills3, MapSprite, MovementTypePointer, TerrainAvoidPointer, TerrainDefensePointer, TerrainHitAvoidPointer, Unknown1, Unknown2, Unknown3, Unknown4, Tier1Class
    HP                      .byte \HP                       ; $00
    Strength                .byte \Strength                 ; $01
    Magic                   .byte \Magic                    ; $02
    Skill                   .byte \Skill                    ; $03
    Speed                   .byte \Speed                    ; $04
    Defense                 .byte \Defense                  ; $05
    Constitution            .byte \Constitution             ; $06
    Movement                .byte \Movement                 ; $07
    ClassRelativePower      .byte \ClassRelativePower       ; $08
    .union
      WeaponRanks           .fill 10                        ; $09
      .struct
        SwordRank           .byte \SwordRank                ; $09
        LanceRank           .byte \LanceRank                ; $0A
        AxeRank             .byte \AxeRank                  ; $0B
        BowRank             .byte \BowRank                  ; $0C
        StaffRank           .byte \StaffRank                ; $0D
        FireRank            .byte \FireRank                 ; $0E
        ThunderRank         .byte \ThunderRank              ; $0F
        WindRank            .byte \WindRank                 ; $10
        LightRank           .byte \LightRank                ; $11
        DarkRank            .byte \DarkRank                 ; $12
      .endstruct
    .endunion
    Skills1                 .byte \Skills1                  ; $13
    Skills2                 .byte \Skills2                  ; $14
    Skills3                 .byte \Skills3                  ; $15
    MapSprite               .byte \MapSprite                ; $16
    MovementTypePointer     .word <>\MovementTypePointer    ; $17
    TerrainAvoidPointer     .word <>\TerrainAvoidPointer    ; $19
    TerrainDefensePointer   .word <>\TerrainDefensePointer  ; $1B
    TerrainHitAvoidPointer  .word <>\TerrainHitAvoidPointer ; $1D
    Unknown1                .byte \Unknown1                 ; $1F
    Unknown2                .byte \Unknown2                 ; $20
    Unknown3                .byte \Unknown3                 ; $21
    Unknown4                .byte \Unknown4                 ; $22
    Tier1Class              .byte \Tier1Class               ; $23
  .endstruct

.endif ; GUARD_VOLTEDGE_CLASSES
