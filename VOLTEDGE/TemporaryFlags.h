
GUARD_VOLTEDGE_VANILLA_TEMPORARY_FLAGS :?= false
.if (!GUARD_VOLTEDGE_VANILLA_TEMPORARY_FLAGS)
  GUARD_VOLTEDGE_VANILLA_TEMPORARY_FLAGS := true

  VoltEdge_TemporaryFlags_Created = 0.01
  VoltEdge_TemporaryFlags_Updated = 0.02

  ; Created: 0.01
  ; Updated: 0.01
  FlagAlwaysZero  = $00
  FlagAlliedDeath = $01 ; Sets sad music
  FlagBossDeath   = $02
  FlagPlayerDeath = $03
  ;               = $04 ; Unused in vanilla
  ;               = $05 ; General-purpose flags
  ;               = $06 ; $05 - $13 used in vanilla
  ;               = $07
  ;               = $08
  ;               = $09
  ;               = $0A
  ;               = $0B
  ;               = $0C
  ;               = $0D
  ;               = $0E
  ;               = $0F
  ;               = $10
  ;               = $11
  ;               = $12
  ;               = $13
  ;               = $14 ; $14 - $20 unused in vanilla
  ;               = $15
  ;               = $16
  ;               = $17
  ;               = $18
  ;               = $19
  ;               = $1A
  ;               = $1B
  ;               = $1C
  ;               = $1D
  ;               = $1E
  ;               = $1F
  ;               = $20
  ;               = $21 ; Start of tile change flags
  ;               = $22 ; flag for change = change ID + $21
  ;               = $23 ; $21 - $39 used in vanilla
  ;               = $24
  ;               = $25
  ;               = $26
  ;               = $27
  ;               = $28
  ;               = $29
  ;               = $2A
  ;               = $2B
  ;               = $2C
  ;               = $2D
  ;               = $2E
  ;               = $2F
  ;               = $30
  ;               = $31
  ;               = $32
  ;               = $33
  ;               = $34
  ;               = $35
  ;               = $36
  ;               = $37
  ;               = $38
  ;               = $39
  ;               = $3A ; $3A - $40 unused in vanilla
  ;               = $3B
  ;               = $3C
  ;               = $3D
  ;               = $3E
  ;               = $3F
  ;               = $40
  ;               = $41 ; $41-$57 used for random chests
  ;               = $42
  ;               = $43
  ;               = $44
  ;               = $45
  ;               = $46
  ;               = $47
  ;               = $48
  ;               = $49
  ;               = $4A
  ;               = $4B
  ;               = $4C
  ;               = $4D
  ;               = $4E
  ;               = $4F
  ;               = $50
  ;               = $51
  ;               = $52
  ;               = $53
  ;               = $54
  ;               = $55
  ;               = $56
  ;               = $57
  ;               = $58 ; $58-$60 unused in vanilla
  ;               = $59
  ;               = $5A
  ;               = $5B
  ;               = $5C
  ;               = $5D
  ;               = $5E
  ;               = $5F
  ;               = $60

.endif ; GUARD_VOLTEDGE_VANILLA_TEMPORARY_FLAGS
