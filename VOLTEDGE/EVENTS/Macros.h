
GUARD_VOLTEDGE_EVENTS_MACROS :?= false
.if (!GUARD_VOLTEDGE_EVENTS_MACROS)
  GUARD_VOLTEDGE_EVENTS_MACROS := true

  VoltEdge_Events_Macros_Created = 0.03
  VoltEdge_Events_Macros_Updated = 0.06

  ; Condition macros

    ; Created: 0.03
    ; Updated: 0.03
    macroECCheckCoordinates .macro Coordinates
      CMP_BYTE wCursorXCoord, \Coordinates[0]
      CMP_BYTE wCursorYCoord, \Coordinates[1]
    .endm

    ; Created: 0.03
    ; Updated: 0.03
    macroECCheckCoordinateRanges .macro UpperLeftCoordinates, LowerRightCoordinates
      CMP_BYTE_RANGE wCursorXCoord, \UpperLeftCoordinates[0], \LowerRightCoordinates[0]
      CMP_BYTE_RANGE wCursorYCoord, \UpperLeftCoordinates[1], \LowerRightCoordinates[1]
    .endm

    ; Created: 0.03
    ; Updated: 0.03
    macroECCheckCoordinateRect .macro Rectangle
      ; Instead of taking two sets of coordinates,
      ; takes a 4-tuple/list of the form
      ; [X, Y, W, H]
      CMP_BYTE_RANGE wCursorXCoord, \Rectangle[0], \Rectangle[0]+\Rectangle[2]
      CMP_BYTE_RANGE wCursorYCoord, \Rectangle[1], \Rectangle[1]+\Rectangle[3]
    .endm

    ; Created: 0.03
    ; Updated: 0.03
    macroECShop .macro ShopDataPointer
      EVENT FlagAlwaysZero, \ShopDataPointer
        CMP_BYTE_AT wCursorXCoord, \ShopDataPointer
        CMP_BYTE_AT wCursorYCoord, \ShopDataPointer+1
      END_DEFINITION
    .endm

    ; Created: 0.03
    ; Updated: 0.04
    macroECBossQuote .macro EventFlag, Character
      EVENT \EventFlag, eventBattleQuoteDummyEvent
        CHECK_SINGLE \Character
      END_DEFINITION
    .endm

    ; Created: 0.04
    ; Updated: 0.04
    macroECDoor .macro EventFlag, Coordinates, EventPointer
      EVENT \EventFlag, \EventPointer
        CMP_BYTE wActiveTileXCoordinate, \Coordinates[0]
        CMP_BYTE wActiveTileYCoordinate, \Coordinates[1]
      END_DEFINITION
    .endm

    ; Created: 0.04
    ; Updated: 0.04
    macroECVanillaChest .macro EventFlag, ChestDataPointer
      ; This macro mimics the way vanilla
      ; FE5 does chests: each chest gets a
      ; unique chunk of events and its coordinates
      ; are part of this chunk rather than the
      ; EC definition.
      ; For use with the VANILLA_CHEST helper.
      EVENT \EventFlag, \ChestDataPointer._Events
        CMP_BYTE_AT wCursorXCoord, \ChestDataPointer._Coordinates
        CMP_BYTE_AT wCursorYCoord, \ChestDataPointer._Coordinates+size(byte)
      END_DEFINITION
    .endm

    ; Created: 0.04
    ; Updated: 0.04
    macroECChest .macro EventFlag, Coordinates, EventPointer
      EVENT \EventFlag, \EventPointer
        CMP_BYTE wCursorXCoord, \Coordinates[0]
        CMP_BYTE wCursorYCoord, \Coordinates[1]
      END_DEFINITION
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroECPlayerRetreat .macro EventFlag, EventPointer, Lord
      EVENT \EventFlag, \EventPointer
        ; Lord retreating
        CMP_BITS wUnknown7E4F98, $0008 ; TODO: figure this out
        RUN_ASM rlECCheckRetreatCoordinates
        CMP_WORD aSelectedCharacterBuffer.Character,\Lord
      END_DEFINITION
      EVENT \EventFlag, \EventPointer
        ; Unit holding lord retreating
        CMP_BITS wUnknown7E4F98, $0008 ; TODO: figure this out
        RUN_ASM rlECCheckRetreatCoordinates
        CHECK_ACTIVE_CARRYING \Lord
      END_DEFINITION
      EVENT FlagAlwaysZero, \EventPointer
        ; Anyone else retreating
        CMP_BITS wUnknown7E4F98, $0008 ; TODO: figure this out
        TEST_FLAG_UNSET \EventFlag
        RUN_ASM rlECCheckRetreatCoordinates
        CMP_WORD wCurrentPhase, Player
      END_DEFINITION
    .endm

  ; ASMC macros

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCChangeAllegianceToPlayer .macro Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCChangeAllegianceToPlayer
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCChangeAllegianceToEnemy .macro Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCChangeAllegianceToEnemy
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCChangeAllegianceToNPC .macro Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCChangeAllegianceToNPC
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCChangeAllegiance .macro Character, CurrentAllegiance, NewAllegiance, NewLeader
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineCharacterStructParameter, \NewLeader
      STORE_WORD wEventEngineParameter2, \CurrentAllegiance
      STORE_WORD wEventEngineParameter3, \NewAllegiance
      CALL_ASM_LOOP rlASMCChangeAllegiance
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCChangeAllegianceToPlayerIfHeld .macro Character
      ; Returns failure if unit is not
      ; being held or player is out of
      ; deployment slots.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCChangeAllegianceToPlayerIfHeld
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCMount .macro Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCMount
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCDismount .macro Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCDismount
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCIsUnitHeld .macro Character
      ; Returns success if unit is
      ; being held/captured, failure
      ; if not held or not found.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCIsUnitHeld
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCIsUnitHeldByEnemy .macro Character
      ; macroASMCIsUnitHeld but
      ; if unit is held by an enemy.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCIsUnitHeldByEnemy
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCClearRescue .macro Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCClearRescue
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCSetFlagIfRetreatingUnitByTable .macro TablePointer
      STORE_LONG lEventEngineLongParameter, \TablePointer
      CALL_ASM_LOOP rlASMCSetFlagIfRetreatingUnitByTable
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCRemoveUnit .macro Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCRemoveUnit
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCPromoteUnit .macro Character, NewClass
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \NewClass
      CALL_ASM_LOOP rlASMCPromoteUnit
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCPromoteUnitSilent .macro Character, NewClass
      STORE_WORD aSelectedCharacterBuffer.Character, \Character
      STORE_WORD wEventEngineParameter1, \NewClass
      CALL_ASM_LOOP rlASMCPromoteUnitSilent
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCSetUnitPosition .macro Character, Coordinates
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      CALL_ASM_LOOP rlASMCSetUnitPosition
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCSetUnitState .macro Character, UnitState
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCSetUnitState
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCUnsetUnitState .macro Character, UnitState
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCUnsetUnitState
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCheckUnitStateSet .macro Character, UnitState
      ; Returns success if unit has all
      ; of the specified bits set, failure
      ; otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCCheckUnitStateSet
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCheckUnitStateUnset .macro Character, UnitState
      ; Returns success if unit has all
      ; of the specified bits unset, failure
      ; otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCCheckUnitStateUnset
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCheckUnitStatus .macro Character, Status
      ; Returns success if unit has
      ; the specified status, failure
      ; otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \Status
      CALL_ASM_LOOP rlASMCCheckUnitStatus
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCheckAbleToTalk .macro Character
      ; Returns success if unit is
      ; able to talk, failure otherwise.
      ; Does not check if unit has any
      ; talks available, however.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCheckAbleToTalk
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCAllUnitsSetUnitState .macro UnitState
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCAllUnitsSetUnitState
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCAllUnitsUnsetUnitState .macro UnitState
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCAllUnitsUnsetUnitState
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCActiveUnitSetUnitState .macro UnitState
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCActiveUnitSetUnitState
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCActiveUnitUnsetUnitState .macro UnitState
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCActiveUnitUnsetUnitState
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCActiveUnitCheckUnitState .macro UnitState
      ; Returns success if unit in
      ; aSelectedCharacterBuffer has
      ; the specified unit state bits set,
      ; failure otherwise.
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCActiveUnitCheckUnitState
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCActiveUnitCheckCarrying .macro Character
      ; Returns success if the active unit
      ; is carrying the specified unit,
      ; failure otherwise.
      STORE_WORD wEventEngineParameter1, \Character
      CALL_ASM_LOOP rlASMCActiveUnitCheckCarrying
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCountOwnedItem .macro Item
      ; Returns number of item owned
      ; in wEventEngineParameter3.
      ; Returns success if the player owns
      ; at least one of the item, failure
      ; otherwise.
      STORE_WORD wEventEngineParameter1, \Item
      CALL_ASM_LOOP rlASMCCountOwnedItem
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCheckUnitForItem .macro Character, Item
      ; Returns success if unit is
      ; holding at least one of the
      ; specified item, failure
      ; otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \Item
      CALL_ASM_LOOP rlASMCCheckUnitForItem
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCGiveUnitItemSilent .macro Character, Item
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \Item
      CALL_ASM_LOOP rlASMCGiveUnitItemSilent
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCheckUnitExists .macro Character
      ; Returns success if the unit
      ; exists in any unit pool.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCheckUnitExists
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCRemoveItemFromUnit .macro Character, Item
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \Item
      CALL_ASM_LOOP rlASMCRemoveItemFromUnit
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCGiveUnitItemsToConvoy .macro Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCGiveUnitItemsToConvoy
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCGiveActiveUnitItem .macro Item
      ; Returns success if able
      ; to give item, failure if
      ; unable (i.e. inventory full).
      STORE_WORD wEventEngineParameter1, \Item
      CALL_ASM_LOOP rlASMCGiveActiveUnitItem
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCGiveActiveUnitItemCurrentDurability .macro Item, Durability
      ; Returns success if able
      ; to give item, failure if
      ; unable (i.e. inventory full).
      STORE_WORD wEventEngineParameter1, pack([\Item, \Durability])
      CALL_ASM_LOOP rlASMCGiveActiveUnitItemCurrentDurability
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCGiveConvoyItem .macro Item
      STORE_WORD wEventEngineParameter1, \Item
      CALL_ASM_LOOP rlASMCGiveConvoyItem
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCheckIfUnitHasEquippedWeapon .macro Character
      ; Returns success if unit has a
      ; weapon that they can use, failure
      ; otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCheckIfUnitHasEquippedWeapon
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCAddGoldWord .macro Amount
      STORE_WORD wEventEngineParameter1, \Amount
      CALL_ASM_LOOP rlASMCAddGoldWord
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCSubtractGoldWord .macro Amount
      STORE_WORD wEventEngineParameter1, \Amount
      CALL_ASM_LOOP rlASMCSubtractGoldWord
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCompareGoldGTE .macro Amount
      STORE_WORD wEventEngineParameter1, \Amount
      CALL_ASM_LOOP rlASMCCompareGoldGTE
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCStoreUnitToUnitMapByCoordinates .macro DeploymentNumber, Coordinates
      STORE_WORD wEventEngineParameter1, \DeploymentNumber
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      CALL_ASM_LOOP rlASMCStoreUnitToUnitMapByCoordinates
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCSingleTileChangeSavedTile .macro TileID, Coordinates
      ; Saves original tile to wEventEngineSavedTile.
      STORE_WORD wEventEngineParameter1, \TileID
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      CALL_ASM_LOOP rlASMCSingleTileChangeSavedTile
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCRevertSingleTileChangeSavedTile .macro Coordinates
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      CALL_ASM_LOOP rlASMCRevertSingleTileChangeSavedTile
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCSingleTileChangeByCoords .macro Coordinates, TileID
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      STORE_WORD wEventEngineParameter1, \TileID
      CALL_ASM_LOOP rlASMCSingleTileChangeByCoords
      YIELD_UNK
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCSetTileToDoor .macro TileID, Coordinates
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      STORE_WORD wEventEngineParameter1, \TileID
      CALL_ASM_LOOP rlASMCSetTileToDoor
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCWriteUnitAtTileToBuffer .macro Coordinates
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      CALL_ASM_LOOP rlASMCWriteUnitAtTileToBuffer
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCheckIfUnitAtCoords .macro Character, Coordinates
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCheckIfUnitAtCoords
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCLoadUnitGroup .macro UnitGroupPointer
      STORE_LONG lEventEngineUnitGroupPointer, \UnitGroupPointer
      CALL_ASM_LOOP rlASMCLoadUnitGroup
      YIELD_UNK
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCPrepareCapturedUnitsForRescue .macro Allegiance, CoordinateTablePointer
      STORE_LONG lEventEngineLongParameter, \CoordinateTablePointer
      STORE_WORD lEventEngineUnitGroupPointer, ((\Allegiance + 1) * size(word))
      CALL_ASM_LOOP rlASMCPrepareCapturedUnitsForRescue
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCAllUnitsSetCharacterDataByte .macro CharacterDataField, Value
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCAllUnitsSetCharacterDataByte
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCSetCharacterDataByte .macro Character, CharacterDataField, Value
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCSetCharacterDataByte
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCSetCharacterDataWord .macro Character, CharacterDataField, Value
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCSetCharacterDataWord
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCAddCharacterDataByte .macro Character, CharacterDataField, Value
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCAddCharacterDataByte
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCSubtractCharacterDataByte .macro Character, CharacterDataField, Value
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCSubtractCharacterDataByte
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCSetBitsCharacterDataWord .macro Character, CharacterDataField, Value
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCSetBitsCharacterDataWord
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCUnsetBitsCharacterDataWord .macro Character, CharacterDataField, Value
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCUnsetBitsCharacterDataWord
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCheckBitsCharacterDataWord .macro Character, CharacterDataField, Value
      ; Returns success if any of the character's
      ; data word has any bits in common with the
      ; value, failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCCheckBitsCharacterDataWord
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCSetCharacterDataByteIfCharacterDataByte .macro CharacterDataField, Value, FieldToCheck, ValueToMatch
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      STORE_WORD wEventEngineCharacterTarget, \ValueToMatch
      STORE_WORD wEventEngineCharacterStructParameter, structCharacterDataRAM.\FieldToCheck
      CALL_ASM_LOOP rlASMCSetCharacterDataByteIfCharacterDataByte
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCSetCharacterDataByteIfCharacterDataWord .macro CharacterDataField, Value, FieldToCheck, ValueToMatch
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      STORE_WORD wEventEngineCharacterTarget, \ValueToMatch
      STORE_WORD wEventEngineCharacterStructParameter, structCharacterDataRAM.\FieldToCheck
      CALL_ASM_LOOP rlASMCSetCharacterDataByteIfCharacterDataWord
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCSetCharacterDataWordBitsIfCharacterDataWord .macro CharacterDataField, Value, FieldToCheck, ValueToMatch
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      STORE_WORD wEventEngineCharacterTarget, \ValueToMatch
      STORE_WORD wEventEngineCharacterStructParameter, structCharacterDataRAM.\FieldToCheck
      CALL_ASM_LOOP rlASMCSetCharacterDataWordBitsIfCharacterDataWord
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCUnsetCharacterDataWordBitsIfCharacterDataWord .macro CharacterDataField, Value, FieldToCheck, ValueToMatch
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      STORE_WORD wEventEngineCharacterTarget, \ValueToMatch
      STORE_WORD wEventEngineCharacterStructParameter, structCharacterDataRAM.\FieldToCheck
      CALL_ASM_LOOP rlASMCUnsetCharacterDataWordBitsIfCharacterDataWord
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCountAllUnitsWithCharacterDataByte .macro CharacterDataField, Value
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit with
      ; the value is found, failure otherwise.
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCCountAllUnitsWithCharacterDataByte
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCountPlayerUnitsWithCharacterDataByte .macro CharacterDataField, Value
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit with
      ; the value is found, failure otherwise.
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCCountPlayerUnitsWithCharacterDataByte
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCountAllUnitsWithCharacterDataWord .macro CharacterDataField, Value
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit with
      ; the value is found, failure otherwise.
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCCountAllUnitsWithCharacterDataWord
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCountAllUnitsWithCharacterDataWordBitsSet .macro CharacterDataField, Value
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit with
      ; any bits in common with the
      ; value is found, failure otherwise.
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCCountAllUnitsWithCharacterDataWordBitsSet
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCountAllUnitsUncapturedAlive .macro Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountAllUnitsUncapturedAlive
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCountPlayerUnitsUncapturedAlive .macro Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountPlayerUnitsUncapturedAlive
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCountEnemyUnitsUncapturedAlive .macro Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountEnemyUnitsUncapturedAlive
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCountNPCUnitsUncapturedAlive .macro Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountNPCUnitsUncapturedAlive
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCountAllUnitsUncapturedAliveWithActing .macro Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountAllUnitsUncapturedAliveWithAcing
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCountAllUnitsUncapturedAliveByTable .macro TablePointer
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_LONG lEventEngineLongParameter, \TablePointer
      CALL_ASM_LOOP rlASMCCountAllUnitsUncapturedAliveByTable
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCountAllUnitsRescuedByPlayerOrNPCByTable .macro TablePointer
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_LONG lEventEngineLongParameter, \TablePointer
      CALL_ASM_LOOP rlASMCCountAllUnitsRescuedByPlayerOrNPCByTable
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCountAllUnitsRescuedByPlayerOrNPC .macro Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountAllUnitsRescuedByPlayerOrNPC
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCCountAllUnitsAlive .macro Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountAllUnitsAlive
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCGetChapterTurncount .macro Chapter
      ; Retturns turncount in wEventEngineParameter1
      ; and success if turncount is nonzero,
      ; failure otherwise.
      STORE_WORD wEventEngineParameter1, \Chapter
      CALL_ASM_LOOP rlASMCGetChapterTurncount
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCWorldMapDialogue .macro DialoguePointer
      STORE_LONG lEventEngineLongParameter, \DialoguePointer
      CALL_ASM_SKIPPABLE rlASMCWorldMapDialogue
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCDialogueWithBGStart .macro DialoguePointer
      CALL_ASM_LONG_SKIPPABLE rlASMCDialogueWithBGStart, \DialoguePointer
      YIELD_UNK
      YIELD_UNK
      YIELD_UNK
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroASMCDialogueWithBGSetup .macro BackgroundID
      STORE_WORD wEventEngineParameter1, \BackgroundID
      CALL_ASM_SKIPPABLE rlASMCDialogueWithBGSetup, <>rsDialogueWitBGHandler
      HALT_UNTIL_WORD_SKIPPABLE wUnknown000302, $0009 ; TODO: figure this out
    .endm

  ; Large event macros

    ; Created: 0.06
    ; Updated: 0.06
    macroHaveActiveUnitRetreat .macro MovestringPointer, QuoteTablePointer=aRetreatQuoteTable
      PAUSE_SKIPPABLE 15
      YIELD

      STORE_WORD wEventEngineCharacterTarget, None
      STORE_WORD_FROM wEventEngineCharacterTarget, aSelectedCharacterBuffer.Character
      DIALOGUE_ARRAY \QuoteTablePointer
      YIELD

      CALL_ASM_LOOP rlASMCUpdateRetreatingUnitState
      CALL_ASM_LOOP rlASMCCopyUnitToEventBuffer

      MOVE_ACTIVE_UNIT [0, 0], 1, \MovestringPointer
      YIELD_UNK

      CALL_ASM_LOOP rlASMCClearActiveMapSprites
      WAIT_MOVE
      YIELD

      CALL_ASM_LOOP rlASMCCopyUnitFromEventBuffer
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroGiveActiveUnitItem .macro Item
      STORE_WORD wEventEngineParameter1, \Item

      PAUSE_SKIPPABLE 10
      YIELD

      CALL_ASM_LOOP rlASMCGiveActiveUnitItem
      YIELD_UNK

      CALL_ASM_LOOP rlASMCSetupGiveItemPopup
      CALL_ASM_LOOP rlASMCWaitWhileGiveItemPopup
      CALL_ASM_LOOP rlASMCSetupGiveToConvoyIfInventoryFull
      CALL_ASM_LOOP rlASMCWaitWhileGiveToConvoyIfInventoryFull
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroItemHouse .macro DialoguePointer, Item, Coordinates, TileID
      PLAY_SOUND_WORD $00F7 ; TODO: sound definitions

      DIALOGUE \DialoguePointer
      YIELD

      macroASMCActiveUnitSetUnitState UnitStateActing

      macroGiveActiveUnitItem \Item

      macroASMCActiveUnitUnsetUnitState UnitStateActing

      macroASMCSingleTileChangeByCoords \Coordinates, \TileID
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroDialogueHouse .macro DialoguePointer
      PLAY_SOUND_WORD $00F7 ; TODO: sound definitions

      DIALOGUE \DialoguePointer
      YIELD
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroLoadPlayerUnitsByStartingPositions .macro
      STORE_WORD lEventEngineUnitGroupPointer, ((Player + 1) * size(word))
      CALL_ASM_LOOP rlASMCGetStartingPositionsArrayPointerAndLength
      CALL_ASM_LOOP rlASMCLoadPlayerUnitsByStartingPositions
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroTileChangeByID .macro TileChangeID
      HALT_UNTIL_BYTE bDecompressionArrayFlag, $00

      CALL_ASM_LOOP rlASMCDecompressChapterMapChanges

      HALT_UNTIL_BYTE bDecompressionArrayFlag, $00
      HALT_UNTIL_BYTE bDMAArrayFlag, $00

      STORE_WORD wEventEngineParameter1, \TileChangeID
      CALL_ASM_LOOP rlASMCTileChangeByID
      HALT_UNTIL_BYTE bDMAArrayFlag, $00
      YIELD_UNK
      YIELD_UNK
    .endm

    ; Created: 0.06
    ; Updated: 0.06
    macroDestroyHouseByTileChangeID .macro TileChangeID
      PLAY_SOUND_BYTE $45 ; TODO: sound definitions
      macroTileChangeByID \TileChangeID

      PAUSE_SKIPPABLE 10
      YIELD
    .endm


.endif ; GUARD_VOLTEDGE_EVENTS_MACROS
