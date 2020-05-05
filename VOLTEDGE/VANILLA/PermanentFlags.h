
GUARD_VOLTEDGE_VANILLA_PERMANENT_FLAGS :?= false
.if (!GUARD_VOLTEDGE_VANILLA_PERMANENT_FLAGS)
  GUARD_VOLTEDGE_VANILLA_PERMANENT_FLAGS := true

  VoltEdge.Vanilla.PermanentFlags .namespace

    Created = 0.01
    Updated = 0.01

  .endn

  ; This is a list of permanent event
  ; flags in vanilla FE5.

  ; Created: 0.01
  ; Updated: 0.01
  FlagCairpreSaved       = $81
  FlagShivaDiedInChp2x   = $82
  FlagHubertSaved        = $83
  ;                      = $84 ; $84 - $88 unused in vanilla
  ;                      = $85
  ;                      = $86
  ;                      = $87
  ;                      = $88
  FlagEmilySaved         = $89
  FlagMuffySaved         = $8A
  FlagVeraSaved          = $8B
  FlagCliffSaved         = $8C
  FlagBowieSaved         = $8D
  FlagLinaSaved          = $8E
  FlagMareetaDiedInChp5  = $8F
  FlagFredSaved          = $90
  FlagPeterSaved         = $91
  FlagRosaSaved          = $92
  FlagSaylaSaved         = $93
  FlagSalemCaptured      = $94
  FlagChp4Civilian2Saved = $95
  FlagChp4Civilian3Saved = $96
  FlagChp4Civilian4Saved = $97
  FlagChp4Civilian5Saved = $98
  FlagChp4Civilian6Saved = $99
  FlagChp4Civilian7Saved = $9A
  FlagChp14House1        = $9B
  FlagChp14House2        = $9C
  FlagChp14House3        = $9D
  FlagChp14House4        = $9E
  FlagChp14House5        = $9F
  FlagChp14House6        = $A0
  FlagChp15ChurchVisited = $A1
  FlagAmaldaDead         = $A2
  FlagShanamDead         = $A3
  FlagConomoreDead       = $A4
  FlagRaydrikDead        = $A5
  FlagGalzusDead         = $A6
  ;                      = $A7 ; $A7-A8 unused in vanilla
  ;                      = $A8

.endif ; GUARD_VOLTEDGE_VANILLA_PERMANENT_FLAGS
