
GUARD_VOLTEDGE_ITEMS :?= false
.if (!GUARD_VOLTEDGE_ITEMS)
  GUARD_VOLTEDGE_ITEMS := true

  VoltEdge_Items_Created = 0.01
  VoltEdge_Items_Updated = 0.07

  ; Created: 0.01
  ; Updated: 0.01
  ; Item types

    TypeSword   = 0
    TypeLance   = 1
    TypeAxe     = 2
    TypeBow     = 3
    TypeStaff   = 4
    TypeFire    = 5
    TypeThunder = 6
    TypeWind    = 7
    TypeLight   = 8
    TypeDark    = 9

    TypeItem    = 11

  ; Created: 0.01
  ; Updated: 0.01
  ; Weapon ranks

    .weak

      WeaponRankIncrement := 50

      RankE := WeaponRankIncrement * 1
      RankD := WeaponRankIncrement * 2
      RankC := WeaponRankIncrement * 3
      RankB := WeaponRankIncrement * 4
      RankA := WeaponRankIncrement * 5

    .endweak

  ; Created: 0.01
  ; Updated: 0.01
  ; Item traits

    TraitBallista    = bits($01)
    TraitMagicRanged = bits($02)
    TraitWeapon      = bits($04)
    TraitTome        = bits($08)
    TraitStaff       = bits($10)
    TraitUnbreakable = bits($20)
    TraitUnsellable  = bits($40)
    TraitBroken      = bits($80)

  ; Item helpers

    ; Created: 0.01
    ; Updated: 0.07
    structItemDataEntryRAM .struct
      Type            .byte ? ; $00
      Might           .byte ? ; $01
      Accuracy        .byte ? ; $02
      Weight          .byte ? ; $03
      Durability      .byte ? ; $04
      Critrate        .byte ? ; $05
      Range           .byte ? ; $06
      WeaponRank      .word ? ; $07
      Effectiveness   .word ? ; $09
      StatBonus       .word ? ; $0B
      Cost            .word ? ; $0D
      Description     .word ? ; $0F
      UseEffect       .byte ? ; $11
      WeaponEffect    .byte ? ; $12
      Skills2         .byte ? ; $13
      Skills3         .byte ? ; $14
      Traits          .byte ? ; $15
      Icon            .byte ? ; $16
      DisplayedWeapon .byte ? ; $17
      BaseWeapon      .byte ? ; $18
    .endstruct

    ; Created: 0.01
    ; Updated: 0.07
    structItemDataEntry .struct Type, AlternateType, Might, Accuracy, Weight, Durability, Critrate, MinRange, MaxRange, WeaponRank, Effectiveness, StatBonus, Cost, Description, UseEffect, WeaponEffect, Skills2, Skills3, Traits, Icon
      Type          .byte (\AlternateType << 4) | \Type ; $00
      Might         .char \Might           ; $01
      Accuracy      .byte \Accuracy        ; $02
      Weight        .byte \Weight          ; $03
      Durability    .char \Durability      ; $04
      Critrate      .byte \Critrate        ; $05
      Range         .byte (\MaxRange << 4) | (\MinRange) ; $06
      WeaponRank    .word <>\WeaponRank    ; $07
      Effectiveness .word <>\Effectiveness ; $09
      StatBonus     .word <>\StatBonus     ; $0B
      Cost ; $0D
      .if \Cost != 0
        .if \Durability != -1
          .word (\Cost - 200) / (\Durability)
        .else
          .word (\Cost - 200)
        .endif
      .else
        .word 0
      .endif
      Description  .word <>\Description ; $0F
      UseEffect    .byte \UseEffect     ; $11
      WeaponEffect .byte \WeaponEffect  ; $12
      Skills2      .byte \Skills2       ; $13
      Skills3      .byte \Skills3       ; $14
      Traits       .byte \Traits        ; $15
      Icon         .byte \Icon          ; $16
    .endstruct

    ; Created: 0.01
    ; Updated: 0.07
    structItemStatBonuses .struct Strength, Magic, Skill, Speed, Defense, Constitution, Luck, Movement
      Strength     .byte \Strength     ; $00
      Magic        .byte \Magic        ; $01
      Skill        .byte \Skill        ; $02
      Speed        .byte \Speed        ; $03
      Defense      .byte \Defense      ; $04
      Constitution .byte \Constitution ; $05
      Luck         .byte \Luck         ; $06
      Movement     .byte \Movement     ; $07
    .endstruct

.endif ; GUARD_VOLTEDGE_ITEMS
