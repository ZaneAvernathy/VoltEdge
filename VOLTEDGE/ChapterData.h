
GUARD_VOLTEDGE_CHAPTER_DATA :?= false
.if (!GUARD_VOLTEDGE_CHAPTER_DATA)
  GUARD_VOLTEDGE_CHAPTER_DATA := true

  VoltEdge_CHAPTER_DATA_Created = 0.08
  VoltEdge_CHAPTER_DATA_Updated = 0.08

  ; Chapter data values

    ; Created: 0.08
    ; Updated: 0.08
    ; Phase controller values

    CD_NoneControlled   = $00
    CD_PlayerControlled = $02
    CD_AIControlled     = $04

    ; Created: 0.08
    ; Updated: 0.08
    ; Hostility bitfield values

    ; Combine these as necessary.

    CD_EnemyHostile = %001
    CD_EnemyVsNPC   = %010
    CD_NPCHostile   = %100

    ; Created: 0.08
    ; Updated: 0.08
    ; Hostility bitfield shorthands

    CD_Peaceful    = %000
    CD_AllVsEnemy  = CD_EnemyHostile | CD_EnemyVsNPC
    CD_AllVsPlayer = CD_EnemyHostile | CD_NPCHostile
    CD_FreeForAll  = CD_EnemyHostile | CD_EnemyVsNPC | CD_NPCHostile

  ; Chapter data helpers

    ; Created: 0.08
    ; Updated: 0.08
    structChapterDataTableEntry .struct TilesetGraphics, TilesetConfig, TilesetPalette, Map, MapChanges, StartingPositions, ObjectiveMarkers, VisionRange, PrepScreen, MinUnits, MaxUnits, PlayerController, EnemyController, NPCController, HostilityBitfield, PlayerPhaseMusic, EnemyPhaseMusic, NPCPhaseMusic, AlternateGraphics, TilesetAnimations
      TilesetGraphics   .long \TilesetGraphics
      .long 0, 0
      TilesetConfig     .long \TilesetConfig
      TilesetPalette    .long \TilesetPalette
      Map               .long \Map
      MapChanges        .long \MapChanges
      StartingPositions .long \StartingPositions
      ObjectiveMarkers  .long \ObjectiveMarkers
      .word 0, 7, 0, 7
      VisionRange       .byte \VisionRange
      PrepScreen        .byte \PrepScreen
      MinUnits          .byte \MinUnits
      MaxUnits          .byte \MaxUnits
      PlayerController  .byte \PlayerController
      EnemyController   .byte \EnemyController
      NPCController     .byte \NPCController
      HostilityBitfield .byte \HostilityBitfield
      PlayerPhaseMusic  .byte \PlayerPhaseMusic
      EnemyPhaseMusic   .byte \EnemyPhaseMusic
      NPCPhaseMusic     .byte \NPCPhaseMusic
      AlternateGraphics .long \AlternateGraphics
      TilesetAnimations .long \TilesetAnimations
    .endstruct

.endif ; GUARD_VOLTEDGE_CHAPTER_DATA
