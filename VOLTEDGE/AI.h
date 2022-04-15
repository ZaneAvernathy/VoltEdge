
GUARD_VOLTEDGE_AI :?= false
.if (!GUARD_VOLTEDGE_AI)
  GUARD_VOLTEDGE_AI := true

  VoltEdge_AI_Created = 0.19
  VoltEdge_AI_Updated = 0.19

  ; AI Settings

    AI_ConsiderThreat = bits($80)
      ; If an ActionAI or MovementAI setting
      ; has this set, the AI will factor in threat
      ; levels when determining what to do, otherwise
      ; it will ignore threat.

    ActionAI_IgnoreNone          = $00
    ActionAI_100                 = $01
    ActionAI_NoAction            = $02
    ActionAI_NoAttack            = $03
    ActionAI_TargetHighestHP     = $04
    ActionAI_TargetLord          = $05
    ActionAI_Chapter1Guards      = $06
    ActionAI_Dance               = $07
    ActionAI_Chapter3Bishop      = $08
    ActionAI_AmaldaGroup         = $09
    ActionAI_80                  = $0A
    ActionAI_50                  = $0B
    ActionAI_80SkipMove          = $0C
    ActionAI_50SkipMove          = $0D
    ActionAI_Chapter4xAsbel      = $0E
    ActionAI_IgnoreLeif          = $0F
    ActionAI_Chapter8xThief      = $10
    ActionAI_11                  = $11
    ActionAI_ForceHeal           = $12
    ActionAI_20SkipMove          = $13
    ActionAI_XavierGroup         = $14
    ActionAI_Chapter18Thief      = $15
    ActionAI_Chapter20KeyEnemies = $16
    ActionAI_Chapter19Cavalry    = $17
    ActionAI_Chapter22Reinhardt  = $18
    ActionAI_Chapter3Enemies     = $19

    MovementAI_Pursue                  = $00
    MovementAI_PursueInRange           = $01
    MovementAI_PursueLowThreat         = $02
    MovementAI_Stationary              = $03
    MovementAI_Arion                   = $04
    MovementAI_05                      = $05
    MovementAI_06                      = $06
    MovementAI_StationaryIfWeapon      = $07
    MovementAI_PursueInRangeExtended   = $08
    MovementAI_09                      = $09
    MovementAI_GroupPatrolUntilAlerted = $0A
    MovementAI_Flee                    = $0B
    MovementAI_PursueIsolated          = $0C
    MovementAI_0D                      = $0D
    MovementAI_CaptureExit             = $0E
    MovementAI_CaptureGate             = $0F
    MovementAI_Random                  = $10
    MovementAI_TalkToLeif              = $11
    MovementAI_IgnoreLeif              = $12
    MovementAI_13                      = $13
    MovementAI_14                      = $14
    MovementAI_15                      = $15
    MovementAI_StayWithFred            = $16
    MovementAI_17                      = $17
    MovementAI_CaptureChurchAndGate    = $18
    MovementAI_19                      = $19
    MovementAI_XavierCivilian9         = $1A
    MovementAI_XavierCivilian10        = $1B
    MovementAI_XavierCivilian11        = $1C
    MovementAI_XavierCivilian12        = $1D
    MovementAI_XavierCivilian13        = $1E
    MovementAI_XavierCivilian14        = $1F
    MovementAI_XavierCivilian15        = $20
    MovementAI_XavierCivilian16        = $21
    MovementAI_CaptureThrone           = $22
    MovementAI_23                      = $23
    MovementAI_24                      = $24
    MovementAI_IgnoreOlwen             = $25
    MovementAI_StayWithReinhardt       = $26
    MovementAI_IgnoreCedChp23          = $27
    MovementAI_28                      = $28
    MovementAI_IgnoreChp3NPCs          = $29
    MovementAI_AvoidMultipleOpponents  = $2A

  ; AI Properties

    AI_PrioritySetting        = bits(%0000000000001111)
      ; Index into priority tables?
    AI_PropertySetting        = bits(%0000000001110000)
      ; Index into coordinate tables, isolated target
      ; threshold.
    AI_SpecialUnitFlag        = bits(%0000000010000000)
      ; Flag the unit as special, preventing them
      ; from retreating, being targeted by movement staves,
      ; buying items, or interacting with terrain.
    AI_RequestAllyInteraction = bits(%0000000100000000)
      ; Flags a unit as waiting for an allied unit
      ; to interact with them (healing, trading?, etc.)
    AI_Has1RangeHealingStaff  = bits(%0000001000000000)
      ; Flags a unit as being able to heal nearby allies
      ; using a healing staff.

  ; AI Player Properties

    AI_HasMeleeWeapon = bits(%0000000010000000)

  ; AI Action Misc

    AI_RecoveryThresholdIndex = bits(%00000111)
      ; This is the index into the recovery mode
      ; thresholds that the unit uses.
    AI_CoordinateIndex        = bits(%01111000)
      ; This is the index of the unit's
      ; target coordinate, if they have one. Used
      ; with AI_CoordinateTable.
    AI_RecoveryFlag           = bits(%10000000)
      ; This is set if the unit is in recovery mode.

  ; AI scripts

    ; Script helpers

      AI_AnyThreat = narrow(-1, 1)

      ; Comparison types for _AI_COND_BRANCH commands

        AI_CMP_COND_GT  = 0
        AI_CMP_COND_GTE = 1
        AI_CMP_COND_E   = 2
        AI_CMP_COND_LTE = 3
        AI_CMP_COND_LT  = 4

      ; Helper for _AI_SET_AI commands

        AI_NoChange = narrow(-1, 1)

      ; Search types for ACTION_AI_TARGET_BY_STAT

        AI_SEARCH_HIGHEST = 0
        AI_SEARCH_LOWEST  = 1

      ; Class types for MOVEMENT_AI_MOVE_TO_CLASS_TYPE

        AI_ClassType_Lord    = 0 ; JuniorLord, Lord
        AI_ClassType_Thieves = 1 ; Thieves, Rogues, Dancers
        AI_ClassType_Priests = 2 ; Priests, Sister
        AI_ClassType_Wyverns = 3 ; All wyvern classes
        AI_ClassType_Mages   = 4 ; All nonmounted, nonpriest magic classes
        AI_ClassType_Pegasi  = 5 ; All pegasus classes
        AI_ClassType_Armor   = 6 ; All armored units
        AI_ClassType_Cavalry = 7 ; All cavalry classes

    ; AI Script commands

      ; Action AI commands

        ACTION_AI_COND_BRANCH .segment Address, Value, ComparisonType, Destination
          ; This is the base for a series of comparison
          ; AI script codes.
          .byte $00
          .word (\Address - aAIMainVariables)
          .byte \ComparisonType
          .byte \Value
          .char (\Destination) - * + 5
        .endsegment

        ACTION_AI_BGT .segment Address, Value, Destination
          ; Branches to Destination if the
          ; byte at Address is greater than
          ; the Value.
          ACTION_AI_COND_BRANCH \Address, \Value, AI_CMP_COND_GT, \Destination
        .endsegment

        ACTION_AI_BGE .segment Address, Value, Destination
          ; Branches to Destination if the
          ; byte at Address is greater than or equal to
          ; the Value.
          ACTION_AI_COND_BRANCH \Address, \Value, AI_CMP_COND_GTE, \Destination
        .endsegment

        ACTION_AI_BEQ .segment Address, Value, Destination
          ; Branches to Destination if the
          ; byte at Address is equal to
          ; the Value.
          ACTION_AI_COND_BRANCH \Address, \Value, AI_CMP_COND_E, \Destination
        .endsegment

        ACTION_AI_BLE .segment Address, Value, Destination
          ; Branches to Destination if the
          ; byte at Address is less than or equal to
          ; the Value.
          ACTION_AI_COND_BRANCH \Address, \Value, AI_CMP_COND_LTE, \Destination
        .endsegment

        ACTION_AI_BLT .segment Address, Value, Destination
          ; Branches to Destination if the
          ; byte at Address is less than
          ; the Value.
          ACTION_AI_COND_BRANCH \Address, \Value, AI_CMP_COND_LT, \Destination
        .endsegment

        ACTION_AI_CALL_ASM .segment RoutinePointer, Parameters=[None, None, None, None]
          ; Calls a local assembly routine in bank $8D
          ; with up to four byte-sized parameters.
          .byte $01
          .word <>\RoutinePointer
          .cerror (len(\Parameters) > 4), "ACTION_AI_CALL_ASM can have up to 4 parameters."
          .union
            .byte [None, None, None, None]
            .byte \Parameters
          .endunion
        .endsegment

        ACTION_AI_SET_AI .segment ActionAI=AI_NoChange, MovementAI=AI_NoChange
          ; Overwrites the unit's Action/Movement AI
          ; with the specified values. If AI_NoChange
          ; is specified, don't overwrite that value.
          .byte $02
          .word \ActionAI
          .byte \MovementAI
        .endsegment

        ACTION_AI_BRA .segment Destination
          ; Unconditionally branches to the Destination.
          .byte $03
          .sint (\Destination) - * + 1
        .endsegment

        ACTION_AI_IF_CHARACTER .segment DeploymentSlotPointer, ActionChance, MaxThreat
          ; Unused in vanilla.
          ; Holdover from FE4?
          ; Takes a short pointer to a deployment slot,
          ; action chance, and threat.
          ; Tries reading unit data from bank $8F.
          .byte $04
          .word <>\DeploymentSlotPointer
          .byte \ActionChance
          .byte \MaxThreat
        .endsegment

        ACTION_AI_TARGET .segment IgnoredUnitTablePointer=None, ActionChance, MaxThreat
          ; Will not act against units specified by
          ; table in bank $8F. Each entry is a character ID word
          ; and the table is terminated with a 0 word.
          ; Rolls ActionChance to determine if unit should act,
          ; otherwise go to movement AI, only moving
          ; to tiles with less than MaxThreat.
          .byte $05
          .word <>\IgnoredUnitTablePointer
          .byte \ActionChance
          .byte \MaxThreat
        .endsegment

        ACTION_AI_NO_ACTION .segment Dummy=None
          ; Skip to movement AI. The Dummy value is ignored.
          .byte $06
          .word \Dummy
        .endsegment

        ACTION_AI_CHANCE .segment ActionChance
          ; Unit has ActionChance% to perform an action,
          ; otherwise doing nothing.
          .byte $07
          .word \ActionChance
        .endsegment

        ACTION_AI_TARGET_CLASS .segment Class, MaxThreat
          ; Tries to target units with the specified class.
          .byte $08
          .word \Class
          .byte \MaxThreat
        .endsegment

        ACTION_AI_NONCOMBAT .segment MaxThreat
          ; Only uses items or staves.
          .byte $09
          .word \MaxThreat
        .endsegment

        ACTION_AI_TARGET_BY_STAT .segment CharacterDataField, MaxThreat, SearchType
          ; Base for the following two codes.
          ; Only target units with either
          ; the highest or lowest value of
          ; some CharacterDataField. Selects
          ; highest or lowest using the SearchType
          ; flag.
          .byte $0A
          .word structExpandedCharacterDataRAM.\CharacterDataField
          .byte \SearchType
          .byte \MaxThreat
        .endsegment

        ACTION_AI_TARGET_BY_HIGHEST_STAT .segment CharacterDataField, MaxThreat
          ; Only target units with either
          ; the highest value of
          ; some CharacterDataField.
          ACTION_AI_TARGET_BY_STAT \CharacterDataField, \MaxThreat, AI_SEARCH_HIGHEST
        .endsegment

        ACTION_AI_TARGET_BY_LOWEST_STAT .segment CharacterDataField, MaxThreat
          ; Only target units with either
          ; the lowest value of
          ; some CharacterDataField.
          ACTION_AI_TARGET_BY_STAT \CharacterDataField, \MaxThreat, AI_SEARCH_LOWEST
        .endsegment

        ACTION_AI_0B .segment StaffChance, TargetChance
          ; Unused.
          ; Tries to fight or use staves. Unit
          ; will not act without items and will not
          ; move unless they have no weapons/only broken
          ; weapons.
          .byte $0B
          .word \StaffChance
          .byte \TargetChance
        .endsegment

      ; Movement AI commands

        MOVEMENT_AI_COND_BRANCH .segment Address, Value, ComparisonType, Destination
          ; This is the base for a series of comparison
          ; AI script codes.
          .byte $00
          .word (\Address - aAIMainVariables)
          .byte \ComparisonType
          .byte \Value
          .char (\Destination) - * + 5
        .endsegment

        MOVEMENT_AI_BGT .segment Address, Value, Destination
          ; Branches to Destination if the
          ; byte at Address is greater than
          ; the Value.
          MOVEMENT_AI_COND_BRANCH \Address, \Value, AI_CMP_COND_GT, \Destination
        .endsegment

        MOVEMENT_AI_BGE .segment Address, Value, Destination
          ; Branches to Destination if the
          ; byte at Address is greater than or equal to
          ; the Value.
          MOVEMENT_AI_COND_BRANCH \Address, \Value, AI_CMP_COND_GTE, \Destination
        .endsegment

        MOVEMENT_AI_BEQ .segment Address, Value, Destination
          ; Branches to Destination if the
          ; byte at Address is equal to
          ; the Value.
          MOVEMENT_AI_COND_BRANCH \Address, \Value, AI_CMP_COND_E, \Destination
        .endsegment

        MOVEMENT_AI_BLE .segment Address, Value, Destination
          ; Branches to Destination if the
          ; byte at Address is less than or equal to
          ; the Value.
          MOVEMENT_AI_COND_BRANCH \Address, \Value, AI_CMP_COND_LTE, \Destination
        .endsegment

        MOVEMENT_AI_BLT .segment Address, Value, Destination
          ; Branches to Destination if the
          ; byte at Address is less than
          ; the Value.
          MOVEMENT_AI_COND_BRANCH \Address, \Value, AI_CMP_COND_LT, \Destination
        .endsegment

        MOVEMENT_AI_CALL_ASM .segment RoutinePointer, Parameters=[None, None, None, None]
          ; Calls a local assembly routine in bank $8D
          ; with up to four byte-sized parameters.
          .byte $01
          .word <>\RoutinePointer
          .cerror (len(\Parameters) > 4), "ACTION_AI_CALL_ASM can have up to 4 parameters."
          .union
            .byte [None, None, None, None]
            .byte \Parameters
          .endunion
        .endsegment

        MOVEMENT_AI_SET_AI .segment ActionAI=AI_NoChange, MovementAI=AI_NoChange
          ; Overwrites the unit's Action/Movement AI
          ; with the specified values. If AI_NoChange
          ; is specified, don't overwrite that value.
          .byte $02
          .word \ActionAI
          .byte \MovementAI
        .endsegment

        MOVEMENT_AI_BRA .segment Destination
          ; Unconditionally branches to the Destination.
          .byte $03
          .sint (\Destination) - * + 1
        .endsegment

        MOVEMENT_AI_MOVE_TO_COORDINATES .segment Coordinates=[0, 0], MaxThreat
          ; Move toward the given coordinates.
          ; Sets aAIMainVariables.wTemp1 to 1 if unit is
          ; at the tile, 0 otherwise.
          .byte $04
          .word \Coordinates[0]
          .byte \Coordinates[1]
          .byte \MaxThreat
        .endsegment

        MOVEMENT_AI_MOVE_NEXT_TO_CHARACTER .segment Character, MaxThreat
          ; Move next to the specified character.
          .byte $05
          .word \Character
          .byte \MaxThreat
        .endsegment

        MOVEMENT_AI_SET_STATIONARY_FLAG .segment
          ; Sets wAIStationaryFlag to -1.
          .byte $06
          .word $00FF
        .endsegment

        MOVEMENT_AI_MOVE_TO_CLASS_TYPE .segment ClassType, MaxThreat
          ; Move to the nearest unit with a specified
          ; class type.
          .byte $07
          .word \ClassType
          .byte \MaxThreat
        .endsegment

        MOVEMENT_AI_MOVE_TO_INTERACTABLE_TERRAIN .segment InteractionIndex, MaxThreat
          ; Move to a chest, house, etc.
          .byte $08
          .word \InteractionIndex
          .byte \MaxThreat
        .endsegment

        MOVEMENT_AI_MOVE_IF_THREATENED .segment MaxThreat
          ; Moves away if tile's threat is above max.
          .byte $09
          .word \MaxThreat
        .endsegment

        MOVEMENT_AI_MOVE_TO_UNITS .segment IgnoredUnitTablePointer, MaxThreat
          ; Move to nearest targetable unit.
          ; Will not move to units specified by
          ; table in bank $8F. Each entry is a character ID word
          ; and the table is terminated with a 0 word.
          .byte $0A
          .word <>\IgnoredUnitTablePointer
          .byte \MaxThreat
        .endsegment

        MOVEMENT_AI_MOVE_TO_REACHABLE_UNITS .segment IgnoredUnitTablePointer, MaxThreat
          ; Move to nearest reachable targetable unit.
          ; Will not move to units specified by
          ; table in bank $8F. Each entry is a character ID word
          ; and the table is terminated with a 0 word.
          .byte $0B
          .word <>\IgnoredUnitTablePointer
          .byte \MaxThreat
        .endsegment

        MOVEMENT_AI_0C .segment Value
          ; Unused.
          ; Presumably Value is an action to
          ; perform on a destination tile.
          .byte $0C
          .word \Value
        .endsegment

        MOVEMENT_AI_TALK .segment TalkIndex
          ; TalkIndex is unique for each talk
          ; but their meaning is currently unknown.
          .byte $0D
          .word \TalkIndex
        .endsegment

        MOVEMENT_AI_RANDOM .segment
          ; Tries to move to a random tile
          ; within range.
          .byte $0E
          .word $00FF
        .endsegment

        MOVEMENT_AI_BEGIN_RETREAT .segment
          ; Marks a unit to begin fleeing.
          .byte $0F
          .word $00FF
        .endsegment

        MOVEMENT_AI_TARGET_BREAKABLE_WALLS .segment InteractionIndex, MaxThreat
          ; Similar to MOVEMENT_AI_MOVE_TO_INTERACTABLE_TERRAIN
          ; but for breakable walls?
          .byte $10
          .word \InteractionIndex
          .byte \MaxThreat
        .endsegment

        MOVEMENT_AI_MOVE_TO_TERRAIN .segment TerrainType, MaxThreat
          ; Tries to move toward the closest tile with
          ; a specified terrain type.
          .byte $11
          .word \TerrainType
          .byte \MaxThreat
        .endsegment

.endif ; GUARD_VOLTEDGE_AI
