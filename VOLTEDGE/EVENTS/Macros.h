
GUARD_VOLTEDGE_EVENTS_MACROS :?= false
.if (!GUARD_VOLTEDGE_EVENTS_MACROS)
  GUARD_VOLTEDGE_EVENTS_MACROS := true

  VoltEdge_Events_Macros_Created = 0.03
  VoltEdge_Events_Macros_Updated = 0.07

  ; Condition macros

    ; Created: 0.03
    ; Updated: 0.07
    macroECCheckCoordinates .macro Coordinates
      CMP_BYTE wCursorXCoord, \Coordinates[0]
      CMP_BYTE wCursorYCoord, \Coordinates[1]
    .endmacro

    ; Created: 0.03
    ; Updated: 0.07
    macroECCheckCoordinateRanges .macro UpperLeftCoordinates, LowerRightCoordinates
      CMP_BYTE_RANGE wCursorXCoord, \UpperLeftCoordinates[0], \LowerRightCoordinates[0]
      CMP_BYTE_RANGE wCursorYCoord, \UpperLeftCoordinates[1], \LowerRightCoordinates[1]
    .endmacro

    ; Created: 0.03
    ; Updated: 0.07
    macroECCheckCoordinateRect .macro Rectangle
      ; Instead of taking two sets of coordinates,
      ; takes a 4-tuple/list of the form
      ; [X, Y, W, H]
      CMP_BYTE_RANGE wCursorXCoord, \Rectangle[0], \Rectangle[0]+\Rectangle[2]
      CMP_BYTE_RANGE wCursorYCoord, \Rectangle[1], \Rectangle[1]+\Rectangle[3]
    .endmacro

    ; Created: 0.03
    ; Updated: 0.07
    macroECShop .macro ShopDataPointer
      EVENT FlagAlwaysZero, \ShopDataPointer
        CMP_BYTE_AT wCursorXCoord, \ShopDataPointer
        CMP_BYTE_AT wCursorYCoord, \ShopDataPointer+1
      END_DEFINITION
    .endmacro

    ; Created: 0.03
    ; Updated: 0.07
    macroECBossQuote .macro EventFlag, Character
      EVENT \EventFlag, eventBattleQuoteDummyEvent
        CHECK_SINGLE \Character
      END_DEFINITION
    .endmacro

    ; Created: 0.04
    ; Updated: 0.07
    macroECDoor .macro EventFlag, Coordinates, EventPointer
      EVENT \EventFlag, \EventPointer
        CMP_BYTE wActiveTileXCoordinate, \Coordinates[0]
        CMP_BYTE wActiveTileYCoordinate, \Coordinates[1]
      END_DEFINITION
    .endmacro

    ; Created: 0.04
    ; Updated: 0.07
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
    .endmacro

    ; Created: 0.04
    ; Updated: 0.07
    macroECChest .macro EventFlag, Coordinates, EventPointer
      EVENT \EventFlag, \EventPointer
        CMP_BYTE wCursorXCoord, \Coordinates[0]
        CMP_BYTE wCursorYCoord, \Coordinates[1]
      END_DEFINITION
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
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
    .endmacro

  ; ASMC macros

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCChangeAllegianceToPlayer .macro Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCChangeAllegianceToPlayer
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCChangeAllegianceToEnemy .macro Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCChangeAllegianceToEnemy
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCChangeAllegianceToNPC .macro Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCChangeAllegianceToNPC
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCChangeAllegiance .macro Character, CurrentAllegiance, NewAllegiance, NewLeader
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineCharacterStructParameter, \NewLeader
      STORE_WORD wEventEngineParameter2, \CurrentAllegiance
      STORE_WORD wEventEngineParameter3, \NewAllegiance
      CALL_ASM_LOOP rlASMCChangeAllegiance
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCChangeAllegianceToPlayerIfHeld .macro Character
      ; Returns failure if unit is not
      ; being held or player is out of
      ; deployment slots.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCChangeAllegianceToPlayerIfHeld
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCMount .macro Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCMount
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCDismount .macro Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCDismount
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCIsUnitHeld .macro Character
      ; Returns success if unit is
      ; being held/captured, failure
      ; if not held or not found.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCIsUnitHeld
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCIsUnitHeldByEnemy .macro Character
      ; macroASMCIsUnitHeld but
      ; if unit is held by an enemy.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCIsUnitHeldByEnemy
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCClearRescue .macro Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCClearRescue
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCSetFlagIfRetreatingUnitByTable .macro TablePointer
      STORE_LONG lEventEngineLongParameter, \TablePointer
      CALL_ASM_LOOP rlASMCSetFlagIfRetreatingUnitByTable
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCRemoveUnit .macro Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCRemoveUnit
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCPromoteUnit .macro Character, NewClass
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \NewClass
      CALL_ASM_LOOP rlASMCPromoteUnit
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCPromoteUnitSilent .macro Character, NewClass
      STORE_WORD aSelectedCharacterBuffer.Character, \Character
      STORE_WORD wEventEngineParameter1, \NewClass
      CALL_ASM_LOOP rlASMCPromoteUnitSilent
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCSetUnitPosition .macro Character, Coordinates
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      CALL_ASM_LOOP rlASMCSetUnitPosition
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCSetUnitState .macro Character, UnitState
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCSetUnitState
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCUnsetUnitState .macro Character, UnitState
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCUnsetUnitState
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCheckUnitStateSet .macro Character, UnitState
      ; Returns success if unit has all
      ; of the specified bits set, failure
      ; otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCCheckUnitStateSet
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCheckUnitStateUnset .macro Character, UnitState
      ; Returns success if unit has all
      ; of the specified bits unset, failure
      ; otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCCheckUnitStateUnset
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCheckUnitStatus .macro Character, Status
      ; Returns success if unit has
      ; the specified status, failure
      ; otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \Status
      CALL_ASM_LOOP rlASMCCheckUnitStatus
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCheckAbleToTalk .macro Character
      ; Returns success if unit is
      ; able to talk, failure otherwise.
      ; Does not check if unit has any
      ; talks available, however.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCheckAbleToTalk
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCAllUnitsSetUnitState .macro UnitState
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCAllUnitsSetUnitState
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCAllUnitsUnsetUnitState .macro UnitState
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCAllUnitsUnsetUnitState
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCActiveUnitSetUnitState .macro UnitState
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCActiveUnitSetUnitState
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCActiveUnitUnsetUnitState .macro UnitState
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCActiveUnitUnsetUnitState
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCActiveUnitCheckUnitState .macro UnitState
      ; Returns success if unit in
      ; aSelectedCharacterBuffer has
      ; the specified unit state bits set,
      ; failure otherwise.
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCActiveUnitCheckUnitState
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCActiveUnitCheckCarrying .macro Character
      ; Returns success if the active unit
      ; is carrying the specified unit,
      ; failure otherwise.
      STORE_WORD wEventEngineParameter1, \Character
      CALL_ASM_LOOP rlASMCActiveUnitCheckCarrying
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCountOwnedItem .macro Item
      ; Returns number of item owned
      ; in wEventEngineParameter3.
      ; Returns success if the player owns
      ; at least one of the item, failure
      ; otherwise.
      STORE_WORD wEventEngineParameter1, \Item
      CALL_ASM_LOOP rlASMCCountOwnedItem
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCheckUnitForItem .macro Character, Item
      ; Returns success if unit is
      ; holding at least one of the
      ; specified item, failure
      ; otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \Item
      CALL_ASM_LOOP rlASMCCheckUnitForItem
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCGiveUnitItemSilent .macro Character, Item
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \Item
      CALL_ASM_LOOP rlASMCGiveUnitItemSilent
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCheckUnitExists .macro Character
      ; Returns success if the unit
      ; exists in any unit pool.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCheckUnitExists
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCRemoveItemFromUnit .macro Character, Item
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \Item
      CALL_ASM_LOOP rlASMCRemoveItemFromUnit
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCGiveUnitItemsToConvoy .macro Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCGiveUnitItemsToConvoy
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCGiveActiveUnitItem .macro Item
      ; Returns success if able
      ; to give item, failure if
      ; unable (i.e. inventory full).
      STORE_WORD wEventEngineParameter1, \Item
      CALL_ASM_LOOP rlASMCGiveActiveUnitItem
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCGiveActiveUnitItemCurrentDurability .macro Item, Durability
      ; Returns success if able
      ; to give item, failure if
      ; unable (i.e. inventory full).
      STORE_WORD wEventEngineParameter1, pack([\Item, \Durability])
      CALL_ASM_LOOP rlASMCGiveActiveUnitItemCurrentDurability
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCGiveConvoyItem .macro Item
      STORE_WORD wEventEngineParameter1, \Item
      CALL_ASM_LOOP rlASMCGiveConvoyItem
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCheckIfUnitHasEquippedWeapon .macro Character
      ; Returns success if unit has a
      ; weapon that they can use, failure
      ; otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCheckIfUnitHasEquippedWeapon
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCAddGoldWord .macro Amount
      STORE_WORD wEventEngineParameter1, \Amount
      CALL_ASM_LOOP rlASMCAddGoldWord
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCSubtractGoldWord .macro Amount
      STORE_WORD wEventEngineParameter1, \Amount
      CALL_ASM_LOOP rlASMCSubtractGoldWord
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCompareGoldGTE .macro Amount
      STORE_WORD wEventEngineParameter1, \Amount
      CALL_ASM_LOOP rlASMCCompareGoldGTE
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCStoreUnitToUnitMapByCoordinates .macro DeploymentNumber, Coordinates
      STORE_WORD wEventEngineParameter1, \DeploymentNumber
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      CALL_ASM_LOOP rlASMCStoreUnitToUnitMapByCoordinates
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCSingleTileChangeSavedTile .macro TileID, Coordinates
      ; Saves original tile to wEventEngineSavedTile.
      STORE_WORD wEventEngineParameter1, \TileID
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      CALL_ASM_LOOP rlASMCSingleTileChangeSavedTile
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCRevertSingleTileChangeSavedTile .macro Coordinates
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      CALL_ASM_LOOP rlASMCRevertSingleTileChangeSavedTile
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCSingleTileChangeByCoords .macro Coordinates, TileID
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      STORE_WORD wEventEngineParameter1, \TileID
      CALL_ASM_LOOP rlASMCSingleTileChangeByCoords
      YIELD_UNK
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCSetTileToDoor .macro TileID, Coordinates
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      STORE_WORD wEventEngineParameter1, \TileID
      CALL_ASM_LOOP rlASMCSetTileToDoor
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCWriteUnitAtTileToBuffer .macro Coordinates
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      CALL_ASM_LOOP rlASMCWriteUnitAtTileToBuffer
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCheckIfUnitAtCoords .macro Character, Coordinates
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCheckIfUnitAtCoords
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCLoadUnitGroup .macro UnitGroupPointer
      STORE_LONG lEventEngineUnitGroupPointer, \UnitGroupPointer
      CALL_ASM_LOOP rlASMCLoadUnitGroup
      YIELD_UNK
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCPrepareCapturedUnitsForRescue .macro Allegiance, CoordinateTablePointer
      STORE_LONG lEventEngineLongParameter, \CoordinateTablePointer
      STORE_WORD lEventEngineUnitGroupPointer, ((\Allegiance + 1) * size(word))
      CALL_ASM_LOOP rlASMCPrepareCapturedUnitsForRescue
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCAllUnitsSetCharacterDataByte .macro CharacterDataField, Value
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCAllUnitsSetCharacterDataByte
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCSetCharacterDataByte .macro Character, CharacterDataField, Value
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCSetCharacterDataByte
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCSetCharacterDataWord .macro Character, CharacterDataField, Value
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCSetCharacterDataWord
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCAddCharacterDataByte .macro Character, CharacterDataField, Value
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCAddCharacterDataByte
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCSubtractCharacterDataByte .macro Character, CharacterDataField, Value
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCSubtractCharacterDataByte
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCSetBitsCharacterDataWord .macro Character, CharacterDataField, Value
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCSetBitsCharacterDataWord
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCUnsetBitsCharacterDataWord .macro Character, CharacterDataField, Value
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCUnsetBitsCharacterDataWord
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCheckBitsCharacterDataWord .macro Character, CharacterDataField, Value
      ; Returns success if any of the character's
      ; data word has any bits in common with the
      ; value, failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCCheckBitsCharacterDataWord
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCSetCharacterDataByteIfCharacterDataByte .macro CharacterDataField, Value, FieldToCheck, ValueToMatch
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      STORE_WORD wEventEngineCharacterTarget, \ValueToMatch
      STORE_WORD wEventEngineCharacterStructParameter, structCharacterDataRAM.\FieldToCheck
      CALL_ASM_LOOP rlASMCSetCharacterDataByteIfCharacterDataByte
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCSetCharacterDataByteIfCharacterDataWord .macro CharacterDataField, Value, FieldToCheck, ValueToMatch
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      STORE_WORD wEventEngineCharacterTarget, \ValueToMatch
      STORE_WORD wEventEngineCharacterStructParameter, structCharacterDataRAM.\FieldToCheck
      CALL_ASM_LOOP rlASMCSetCharacterDataByteIfCharacterDataWord
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCSetCharacterDataWordBitsIfCharacterDataWord .macro CharacterDataField, Value, FieldToCheck, ValueToMatch
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      STORE_WORD wEventEngineCharacterTarget, \ValueToMatch
      STORE_WORD wEventEngineCharacterStructParameter, structCharacterDataRAM.\FieldToCheck
      CALL_ASM_LOOP rlASMCSetCharacterDataWordBitsIfCharacterDataWord
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCUnsetCharacterDataWordBitsIfCharacterDataWord .macro CharacterDataField, Value, FieldToCheck, ValueToMatch
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      STORE_WORD wEventEngineCharacterTarget, \ValueToMatch
      STORE_WORD wEventEngineCharacterStructParameter, structCharacterDataRAM.\FieldToCheck
      CALL_ASM_LOOP rlASMCUnsetCharacterDataWordBitsIfCharacterDataWord
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCountAllUnitsWithCharacterDataByte .macro CharacterDataField, Value
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit with
      ; the value is found, failure otherwise.
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCCountAllUnitsWithCharacterDataByte
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCountPlayerUnitsWithCharacterDataByte .macro CharacterDataField, Value
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit with
      ; the value is found, failure otherwise.
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCCountPlayerUnitsWithCharacterDataByte
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCountAllUnitsWithCharacterDataWord .macro CharacterDataField, Value
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit with
      ; the value is found, failure otherwise.
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCCountAllUnitsWithCharacterDataWord
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCountAllUnitsWithCharacterDataWordBitsSet .macro CharacterDataField, Value
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit with
      ; any bits in common with the
      ; value is found, failure otherwise.
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCCountAllUnitsWithCharacterDataWordBitsSet
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCountAllUnitsUncapturedAlive .macro Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountAllUnitsUncapturedAlive
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCountPlayerUnitsUncapturedAlive .macro Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountPlayerUnitsUncapturedAlive
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCountEnemyUnitsUncapturedAlive .macro Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountEnemyUnitsUncapturedAlive
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCountNPCUnitsUncapturedAlive .macro Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountNPCUnitsUncapturedAlive
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCountAllUnitsUncapturedAliveWithActing .macro Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountAllUnitsUncapturedAliveWithAcing
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCountAllUnitsUncapturedAliveByTable .macro TablePointer
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_LONG lEventEngineLongParameter, \TablePointer
      CALL_ASM_LOOP rlASMCCountAllUnitsUncapturedAliveByTable
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCountAllUnitsRescuedByPlayerOrNPCByTable .macro TablePointer
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_LONG lEventEngineLongParameter, \TablePointer
      CALL_ASM_LOOP rlASMCCountAllUnitsRescuedByPlayerOrNPCByTable
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCountAllUnitsRescuedByPlayerOrNPC .macro Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountAllUnitsRescuedByPlayerOrNPC
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCCountAllUnitsAlive .macro Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountAllUnitsAlive
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCGetChapterTurncount .macro Chapter
      ; Retturns turncount in wEventEngineParameter1
      ; and success if turncount is nonzero,
      ; failure otherwise.
      STORE_WORD wEventEngineParameter1, \Chapter
      CALL_ASM_LOOP rlASMCGetChapterTurncount
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCWorldMapDialogue .macro DialoguePointer
      STORE_LONG lEventEngineLongParameter, \DialoguePointer
      CALL_ASM_SKIPPABLE rlASMCWorldMapDialogue
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCDialogueWithBGStart .macro DialoguePointer
      CALL_ASM_LONG_SKIPPABLE rlASMCDialogueWithBGStart, \DialoguePointer
      YIELD_UNK
      YIELD_UNK
      YIELD_UNK
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroASMCDialogueWithBGSetup .macro BackgroundID
      STORE_WORD wEventEngineParameter1, \BackgroundID
      CALL_ASM_SKIPPABLE rlASMCDialogueWithBGSetup, <>rsDialogueWitBGHandler
      HALT_UNTIL_WORD_SKIPPABLE wUnknown000302, $0009 ; TODO: figure this out
    .endmacro

  ; Large event macros

    ; Created: 0.06
    ; Updated: 0.07
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
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
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
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroItemHouse .macro DialoguePointer, Item, Coordinates, TileID
      PLAY_SOUND_WORD $00F7 ; TODO: sound definitions

      DIALOGUE \DialoguePointer
      YIELD

      macroASMCActiveUnitSetUnitState UnitStateActing

      macroGiveActiveUnitItem \Item

      macroASMCActiveUnitUnsetUnitState UnitStateActing

      macroASMCSingleTileChangeByCoords \Coordinates, \TileID
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroDialogueHouse .macro DialoguePointer
      PLAY_SOUND_WORD $00F7 ; TODO: sound definitions

      DIALOGUE \DialoguePointer
      YIELD
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroLoadPlayerUnitsByStartingPositions .macro
      STORE_WORD lEventEngineUnitGroupPointer, ((Player + 1) * size(word))
      CALL_ASM_LOOP rlASMCGetStartingPositionsArrayPointerAndLength
      CALL_ASM_LOOP rlASMCLoadPlayerUnitsByStartingPositions
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
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
    .endmacro

    ; Created: 0.06
    ; Updated: 0.07
    macroDestroyHouseByTileChangeID .macro TileChangeID
      PLAY_SOUND_BYTE $45 ; TODO: sound definitions
      macroTileChangeByID \TileChangeID

      PAUSE_SKIPPABLE 10
      YIELD
    .endmacro


.endif ; GUARD_VOLTEDGE_EVENTS_MACROS
