
GUARD_VOLTEDGE_EVENTS_MACROS :?= false
.if (!GUARD_VOLTEDGE_EVENTS_MACROS)
  GUARD_VOLTEDGE_EVENTS_MACROS := true

  VoltEdge_Events_Macros_Created = 0.03
  VoltEdge_Events_Macros_Updated = 0.23

  ; Condition macros

    ; Created: 0.03
    ; Updated: 0.12
    macroECCheckCoordinates .segment Coordinates
      CMP_BYTE wCursorXCoord, \Coordinates[0]
      CMP_BYTE wCursorYCoord, \Coordinates[1]
    .endsegment

    ; Created: 0.03
    ; Updated: 0.12
    macroECCheckCoordinateRanges .segment UpperLeftCoordinates, LowerRightCoordinates
      CMP_BYTE_RANGE wCursorXCoord, \UpperLeftCoordinates[0], \LowerRightCoordinates[0]
      CMP_BYTE_RANGE wCursorYCoord, \UpperLeftCoordinates[1], \LowerRightCoordinates[1]
    .endsegment

    ; Created: 0.03
    ; Updated: 0.12
    macroECCheckCoordinateRect .segment Rectangle
      ; Instead of taking two sets of coordinates,
      ; takes a 4-tuple/list of the form
      ; [X, Y, W, H]
      CMP_BYTE_RANGE wCursorXCoord, \Rectangle[0], \Rectangle[0]+\Rectangle[2]
      CMP_BYTE_RANGE wCursorYCoord, \Rectangle[1], \Rectangle[1]+\Rectangle[3]
    .endsegment

    ; Created: 0.03
    ; Updated: 0.12
    macroECShop .segment ShopDataPointer
      EVENT FlagAlwaysZero, \ShopDataPointer
        CMP_BYTE_AT wCursorXCoord, \ShopDataPointer
        CMP_BYTE_AT wCursorYCoord, \ShopDataPointer+1
      END_DEFINITION
    .endsegment

    ; Created: 0.03
    ; Updated: 0.12
    macroECBossQuote .segment EventFlag, Character
      EVENT \EventFlag, eventBattleQuoteDummyEvent
        CHECK_SINGLE \Character
      END_DEFINITION
    .endsegment

    ; Created: 0.04
    ; Updated: 0.18
    macroECDoor .segment EventFlag, Coordinates, EventPointer
      EVENT \EventFlag, \EventPointer
        CMP_BYTE wActiveTileUnitParameter1, \Coordinates[0]
        CMP_BYTE wActiveTileUnitParameter2, \Coordinates[1]
      END_DEFINITION
    .endsegment

    ; Created: 0.04
    ; Updated: 0.12
    macroECVanillaChest .segment EventFlag, ChestDataPointer
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
    .endsegment

    ; Created: 0.04
    ; Updated: 0.12
    macroECChest .segment EventFlag, Coordinates, EventPointer
      EVENT \EventFlag, \EventPointer
        CMP_BYTE wCursorXCoord, \Coordinates[0]
        CMP_BYTE wCursorYCoord, \Coordinates[1]
      END_DEFINITION
    .endsegment

    ; Created: 0.06
    ; Updated: 0.19
    macroECPlayerRetreat .segment EventFlag, EventPointer, Lord, Coordinates=?
      EVENT \EventFlag, \EventPointer
        ; Lord retreating
        CMP_BITS wUnknown7E4F98, $0008 ; TODO: figure this out
        .if (\Coordinates === ?)
          RUN_ASM rlECCheckRetreatCoordinates
        .else
          macroECCheckCoordinates \Coordinates
        .endif
        CMP_WORD aSelectedCharacterBuffer.Character,\Lord
      END_DEFINITION
      EVENT \EventFlag, \EventPointer
        ; Unit holding lord retreating
        CMP_BITS wUnknown7E4F98, $0008 ; TODO: figure this out
        .if (\Coordinates === ?)
          RUN_ASM rlECCheckRetreatCoordinates
        .else
          macroECCheckCoordinates \Coordinates
        .endif
        CHECK_ACTIVE_CARRYING \Lord
      END_DEFINITION
      EVENT FlagAlwaysZero, \EventPointer
        ; Anyone else retreating
        CMP_BITS wUnknown7E4F98, $0008 ; TODO: figure this out
        TEST_FLAG_UNSET \EventFlag
        .if (\Coordinates === ?)
          RUN_ASM rlECCheckRetreatCoordinates
          CMP_WORD wCurrentPhase, Player
        .else
          macroECCheckCoordinates \Coordinates
        .endif
      END_DEFINITION
    .endsegment

  ; ASMC macros

    ; Created: 0.19
    ; Updated: 0.19
    macroASMCGameOver .segment
      CALL_ASM_SKIPPABLE rlASMCGameOver
      STORE_WORD wEventEngineUnknown001791, narrow(-1, 2)
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCChangeAllegianceToPlayer .segment Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCChangeAllegianceToPlayer
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCChangeAllegianceToEnemy .segment Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCChangeAllegianceToEnemy
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCChangeAllegianceToNPC .segment Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCChangeAllegianceToNPC
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCChangeAllegiance .segment Character, CurrentAllegiance, NewAllegiance, NewLeader
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineCharacterStructParameter, \NewLeader
      STORE_WORD wEventEngineParameter2, \CurrentAllegiance
      STORE_WORD wEventEngineParameter3, \NewAllegiance
      CALL_ASM_LOOP rlASMCChangeAllegiance
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCChangeAllegianceToPlayerIfHeld .segment Character
      ; Returns failure if unit is not
      ; being held or player is out of
      ; deployment slots.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCChangeAllegianceToPlayerIfHeld
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCMount .segment Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCMount
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCDismount .segment Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCDismount
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCIsUnitHeld .segment Character
      ; Returns success if unit is
      ; being held/captured, failure
      ; if not held or not found.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCIsUnitHeld
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCIsUnitHeldByEnemy .segment Character
      ; macroASMCIsUnitHeld but
      ; if unit is held by an enemy.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCIsUnitHeldByEnemy
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCClearRescue .segment Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCClearRescue
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCSetFlagIfRetreatingUnitByTable .segment TablePointer
      STORE_LONG lEventEngineLongParameter, \TablePointer
      CALL_ASM_LOOP rlASMCSetFlagIfRetreatingUnitByTable
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCRemoveUnit .segment Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCRemoveUnit
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCPromoteUnit .segment Character, NewClass
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \NewClass
      CALL_ASM_LOOP rlASMCPromoteUnit
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCPromoteUnitSilent .segment Character, NewClass
      STORE_WORD aSelectedCharacterBuffer.Character, \Character
      STORE_WORD wEventEngineParameter1, \NewClass
      CALL_ASM_LOOP rlASMCPromoteUnitSilent
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCSetUnitPosition .segment Character, Coordinates
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      CALL_ASM_LOOP rlASMCSetUnitPosition
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCSetUnitState .segment Character, UnitState
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCSetUnitState
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCUnsetUnitState .segment Character, UnitState
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCUnsetUnitState
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCheckUnitStateSet .segment Character, UnitState
      ; Returns success if unit has all
      ; of the specified bits set, failure
      ; otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCCheckUnitStateSet
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCheckUnitStateUnset .segment Character, UnitState
      ; Returns success if unit has all
      ; of the specified bits unset, failure
      ; otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCCheckUnitStateUnset
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCheckUnitStatus .segment Character, Status
      ; Returns success if unit has
      ; the specified status, failure
      ; otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \Status
      CALL_ASM_LOOP rlASMCCheckUnitStatus
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCheckAbleToTalk .segment Character
      ; Returns success if unit is
      ; able to talk, failure otherwise.
      ; Does not check if unit has any
      ; talks available, however.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCheckAbleToTalk
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCAllUnitsSetUnitState .segment UnitState
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCAllUnitsSetUnitState
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCAllUnitsUnsetUnitState .segment UnitState
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCAllUnitsUnsetUnitState
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCActiveUnitSetUnitState .segment UnitState
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCActiveUnitSetUnitState
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCActiveUnitUnsetUnitState .segment UnitState
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCActiveUnitUnsetUnitState
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCActiveUnitCheckUnitState .segment UnitState
      ; Returns success if unit in
      ; aSelectedCharacterBuffer has
      ; the specified unit state bits set,
      ; failure otherwise.
      STORE_WORD wEventEngineParameter1, \UnitState
      CALL_ASM_LOOP rlASMCActiveUnitCheckUnitState
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCActiveUnitCheckCarrying .segment Character
      ; Returns success if the active unit
      ; is carrying the specified unit,
      ; failure otherwise.
      STORE_WORD wEventEngineParameter1, \Character
      CALL_ASM_LOOP rlASMCActiveUnitCheckCarrying
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCountOwnedItem .segment Item
      ; Returns number of item owned
      ; in wEventEngineParameter3.
      ; Returns success if the player owns
      ; at least one of the item, failure
      ; otherwise.
      STORE_WORD wEventEngineParameter1, \Item
      CALL_ASM_LOOP rlASMCCountOwnedItem
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCheckUnitForItem .segment Character, Item
      ; Returns success if unit is
      ; holding at least one of the
      ; specified item, failure
      ; otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \Item
      CALL_ASM_LOOP rlASMCCheckUnitForItem
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCGiveUnitItemSilent .segment Character, Item
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \Item
      CALL_ASM_LOOP rlASMCGiveUnitItemSilent
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCheckUnitExists .segment Character
      ; Returns success if the unit
      ; exists in any unit pool.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCheckUnitExists
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCRemoveItemFromUnit .segment Character, Item
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, \Item
      CALL_ASM_LOOP rlASMCRemoveItemFromUnit
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCGiveUnitItemsToConvoy .segment Character
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCGiveUnitItemsToConvoy
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCGiveActiveUnitItem .segment Item
      ; Returns success if able
      ; to give item, failure if
      ; unable (i.e. inventory full).
      STORE_WORD wEventEngineParameter1, \Item
      CALL_ASM_LOOP rlASMCGiveActiveUnitItem
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCGiveActiveUnitItemCurrentDurability .segment Item, Durability
      ; Returns success if able
      ; to give item, failure if
      ; unable (i.e. inventory full).
      STORE_WORD wEventEngineParameter1, pack([\Item, \Durability])
      CALL_ASM_LOOP rlASMCGiveActiveUnitItemCurrentDurability
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCGiveConvoyItem .segment Item
      STORE_WORD wEventEngineParameter1, \Item
      CALL_ASM_LOOP rlASMCGiveConvoyItem
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCheckIfUnitHasEquippedWeapon .segment Character
      ; Returns success if unit has a
      ; weapon that they can use, failure
      ; otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCheckIfUnitHasEquippedWeapon
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCAddGoldWord .segment Amount
      STORE_WORD wEventEngineParameter1, \Amount
      CALL_ASM_LOOP rlASMCAddGoldWord
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCSubtractGoldWord .segment Amount
      STORE_WORD wEventEngineParameter1, \Amount
      CALL_ASM_LOOP rlASMCSubtractGoldWord
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCompareGoldGTE .segment Amount
      STORE_WORD wEventEngineParameter1, \Amount
      CALL_ASM_LOOP rlASMCCompareGoldGTE
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCStoreUnitToUnitMapByCoordinates .segment DeploymentNumber, Coordinates
      STORE_WORD wEventEngineParameter1, \DeploymentNumber
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      CALL_ASM_LOOP rlASMCStoreUnitToUnitMapByCoordinates
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCSingleTileChangeSavedTile .segment TileID, Coordinates
      ; Saves original tile to wEventEngineSavedTile.
      STORE_WORD wEventEngineParameter1, \TileID
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      CALL_ASM_LOOP rlASMCSingleTileChangeSavedTile
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCRevertSingleTileChangeSavedTile .segment Coordinates
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      CALL_ASM_LOOP rlASMCRevertSingleTileChangeSavedTile
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCSingleTileChangeByCoords .segment Coordinates, TileID
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      STORE_WORD wEventEngineParameter1, \TileID
      CALL_ASM_LOOP rlASMCSingleTileChangeByCoords
      YIELD_UNK
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCSetTileToDoor .segment TileID, Coordinates
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      STORE_WORD wEventEngineParameter1, \TileID
      CALL_ASM_LOOP rlASMCSetTileToDoor
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCWriteUnitAtTileToBuffer .segment Coordinates
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      CALL_ASM_LOOP rlASMCWriteUnitAtTileToBuffer
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCheckIfUnitAtCoords .segment Character, Coordinates
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCheckIfUnitAtCoords
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCLoadUnitGroup .segment UnitGroupPointer
      STORE_LONG lEventEngineUnitGroupPointer, \UnitGroupPointer
      CALL_ASM_LOOP rlASMCLoadUnitGroup
      YIELD_UNK
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCPrepareCapturedUnitsForRescue .segment Allegiance, CoordinateTablePointer
      STORE_LONG lEventEngineLongParameter, \CoordinateTablePointer
      STORE_WORD lEventEngineUnitGroupPointer, ((\Allegiance + 1) * size(word))
      CALL_ASM_LOOP rlASMCPrepareCapturedUnitsForRescue
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCAllUnitsSetCharacterDataByte .segment CharacterDataField, Value
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCAllUnitsSetCharacterDataByte
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCSetCharacterDataByte .segment Character, CharacterDataField, Value
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCSetCharacterDataByte
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCSetCharacterDataWord .segment Character, CharacterDataField, Value
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCSetCharacterDataWord
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCAddCharacterDataByte .segment Character, CharacterDataField, Value
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCAddCharacterDataByte
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCSubtractCharacterDataByte .segment Character, CharacterDataField, Value
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCSubtractCharacterDataByte
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCSetBitsCharacterDataWord .segment Character, CharacterDataField, Value
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCSetBitsCharacterDataWord
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCUnsetBitsCharacterDataWord .segment Character, CharacterDataField, Value
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCUnsetBitsCharacterDataWord
    .endsegment

    ; Created: 0.06
    ; Updated: 0.19
    macroASMCCheckBitsSetCharacterDataWord .segment Character, CharacterDataField, Value
      ; Returns success if any of the character's
      ; data word has any bits in common with the
      ; value, failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCCheckBitsSetCharacterDataWord
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCSetCharacterDataByteIfCharacterDataByte .segment CharacterDataField, Value, FieldToCheck, ValueToMatch
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      STORE_WORD wEventEngineCharacterTarget, \ValueToMatch
      STORE_WORD wEventEngineCharacterStructParameter, structCharacterDataRAM.\FieldToCheck
      CALL_ASM_LOOP rlASMCSetCharacterDataByteIfCharacterDataByte
    .endsegment

    ; Created: 0.06
    ; Updated: 0.18
    macroASMCSetCharacterDataByteIfCharacterDataWord .segment CharacterDataField, Value, FieldToCheck, ValueToMatch
      STORE_WORD wEventEngineCharacterStructParameter, structCharacterDataRAM.\FieldToCheck
      STORE_WORD wEventEngineCharacterTarget, \ValueToMatch
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCSetCharacterDataByteIfCharacterDataWord
    .endsegment

    ; Created: 0.06
    ; Updated: 0.23
    macroASMCSetCharacterDataWordBitsIfCharacterDataWord .segment CharacterDataField, Value, FieldToCheck, ValueToMatch
      STORE_WORD wEventEngineCharacterStructParameter, structCharacterDataRAM.\FieldToCheck
      STORE_WORD wEventEngineCharacterTarget, \ValueToMatch
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCSetCharacterDataWordBitsIfCharacterDataWord
    .endsegment

    ; Created: 0.06
    ; Updated: 0.23
    macroASMCUnsetCharacterDataWordBitsIfCharacterDataWord .segment CharacterDataField, Value, FieldToCheck, ValueToMatch
      STORE_WORD wEventEngineCharacterStructParameter, structCharacterDataRAM.\FieldToCheck
      STORE_WORD wEventEngineCharacterTarget, \ValueToMatch
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCUnsetCharacterDataWordBitsIfCharacterDataWord
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCountAllUnitsWithCharacterDataByte .segment CharacterDataField, Value
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit with
      ; the value is found, failure otherwise.
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCCountAllUnitsWithCharacterDataByte
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCountPlayerUnitsWithCharacterDataByte .segment CharacterDataField, Value
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit with
      ; the value is found, failure otherwise.
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCCountPlayerUnitsWithCharacterDataByte
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCountAllUnitsWithCharacterDataWord .segment CharacterDataField, Value
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit with
      ; the value is found, failure otherwise.
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCCountAllUnitsWithCharacterDataWord
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCountAllUnitsWithCharacterDataWordBitsSet .segment CharacterDataField, Value
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit with
      ; any bits in common with the
      ; value is found, failure otherwise.
      STORE_WORD wEventEngineParameter1, structCharacterDataRAM.\CharacterDataField
      STORE_WORD wEventEngineParameter2, \Value
      CALL_ASM_LOOP rlASMCCountAllUnitsWithCharacterDataWordBitsSet
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCountAllUnitsUncapturedAlive .segment Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountAllUnitsUncapturedAlive
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCountPlayerUnitsUncapturedAlive .segment Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountPlayerUnitsUncapturedAlive
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCountEnemyUnitsUncapturedAlive .segment Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountEnemyUnitsUncapturedAlive
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCountNPCUnitsUncapturedAlive .segment Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountNPCUnitsUncapturedAlive
    .endsegment

    ; Created: 0.06
    ; Updated: 0.19
    macroASMCCountAllUnitsUncapturedAliveWithHidden .segment Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountAllUnitsUncapturedAliveWithHidden
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCountAllUnitsUncapturedAliveByTable .segment TablePointer
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_LONG lEventEngineLongParameter, \TablePointer
      CALL_ASM_LOOP rlASMCCountAllUnitsUncapturedAliveByTable
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCountAllUnitsRescuedByPlayerOrNPCByTable .segment TablePointer
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_LONG lEventEngineLongParameter, \TablePointer
      CALL_ASM_LOOP rlASMCCountAllUnitsRescuedByPlayerOrNPCByTable
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCountAllUnitsRescuedByPlayerOrNPC .segment Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountAllUnitsRescuedByPlayerOrNPC
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCCountAllUnitsAlive .segment Character
      ; Returns count in wEventEngineParameter1
      ; and success if at least one unit found,
      ; failure otherwise.
      STORE_WORD wEventEngineCharacterTarget, \Character
      CALL_ASM_LOOP rlASMCCountAllUnitsAlive
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCGetChapterTurncount .segment Chapter
      ; Retturns turncount in wEventEngineParameter1
      ; and success if turncount is nonzero,
      ; failure otherwise.
      STORE_WORD wEventEngineParameter1, \Chapter
      CALL_ASM_LOOP rlASMCGetChapterTurncount
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCDialogueWithBGStart .segment DialoguePointer
      CALL_ASM_LONG_SKIPPABLE rlASMCDialogueWithBGStart, \DialoguePointer
      YIELD_UNK
      YIELD_UNK
      YIELD_UNK
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroASMCDialogueWithBGSetup .segment BackgroundID
      STORE_WORD wEventEngineParameter1, \BackgroundID
      CALL_ASM_SKIPPABLE rlASMCDialogueWithBGSetup, <>rsDialogueWithBGHandler
      HALT_UNTIL_WORD_SKIPPABLE wUnknown000302, $0009 ; TODO: figure this out
    .endsegment

  ; Large event macros

    ; Created: 0.06
    ; Updated: 0.17
    macroHaveActiveUnitRetreat .segment MovestringPointer, QuoteTablePointer=aRetreatQuoteTable
      PAUSE_SKIPPABLE 15
      YIELD

      STORE_WORD wEventEngineCharacterTarget, None
      STORE_WORD_FROM wEventEngineCharacterTarget, aSelectedCharacterBuffer.Character
      DIALOGUE_ARRAY \QuoteTablePointer
      YIELD

      CALL_ASM_LOOP rlASMCUpdateRetreatingUnitState
      CALL_ASM_LOOP rlASMCCopyUnitToEventBuffer

      MOVE_ACTIVE_UNIT [0, 0], 1, \MovestringPointer

      CALL_ASM_LOOP rlASMCClearActiveMapSprites
      WAIT_MOVE
      YIELD

      CALL_ASM_LOOP rlASMCCopyUnitFromEventBuffer
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroGiveActiveUnitItem .segment Item
      STORE_WORD wEventEngineParameter1, \Item

      PAUSE_SKIPPABLE 10
      YIELD

      CALL_ASM_LOOP rlASMCGiveActiveUnitItem
      YIELD_UNK

      CALL_ASM_LOOP rlASMCSetupGiveItemPopup
      CALL_ASM_LOOP rlASMCWaitWhileGiveItemPopup
      CALL_ASM_LOOP rlASMCSetupGiveToConvoyIfInventoryFull
      CALL_ASM_LOOP rlASMCWaitWhileGiveToConvoyIfInventoryFull
    .endsegment

    ; Created: 0.06
    ; Updated: 0.16
    macroItemHouse .segment DialoguePointer, Item, Coordinates, TileID
      macroDialogue \DialoguePointer

      macroASMCActiveUnitSetUnitState UnitStateHidden

      macroGiveActiveUnitItem \Item

      macroASMCActiveUnitUnsetUnitState UnitStateHidden

      macroASMCSingleTileChangeByCoords \Coordinates, \TileID
    .endsegment

    ; Created: 0.06
    ; Updated: 0.23
    macroDialogue .segment DialoguePointer
      PLAY_SOUND_FORCED $00F7 ; TODO: sound definitions

      DIALOGUE \DialoguePointer
      YIELD
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroLoadPlayerUnitsByStartingPositions .segment
      STORE_WORD lEventEngineUnitGroupPointer, ((Player + 1) * size(word))
      CALL_ASM_LOOP rlASMCGetStartingPositionsArrayPointerAndLength
      CALL_ASM_LOOP rlASMCLoadPlayerUnitsByStartingPositions
    .endsegment

    ; Created: 0.06
    ; Updated: 0.12
    macroTileChangeByID .segment TileChangeID
      HALT_UNTIL_BYTE bDecompressionArrayFlag, $00

      CALL_ASM_LOOP rlASMCDecompressChapterMapChanges

      HALT_UNTIL_BYTE bDecompressionArrayFlag, $00
      HALT_UNTIL_BYTE bDMAArrayFlag, $00

      STORE_WORD wEventEngineParameter1, \TileChangeID
      CALL_ASM_LOOP rlASMCTileChangeByID
      HALT_UNTIL_BYTE bDMAArrayFlag, $00
      YIELD_UNK
      YIELD_UNK
    .endsegment

    ; Created: 0.06
    ; Updated: 0.23
    macroDestroyHouseByTileChangeID .segment TileChangeID, SoundID=$45
      PLAY_EXTENDED_SOUND \SoundID ; TODO: sound definitions
      macroTileChangeByID \TileChangeID

      PAUSE_SKIPPABLE 10
      YIELD
    .endsegment

    ; Created: 0.12
    ; Updated: 0.23
    macroOpenDoorByTileChangeID .segment TileChangeID, SoundID=$6B
      PLAY_EXTENDED_SOUND \SoundID ; TODO: sound definitions
      macroTileChangeByID \TileChangeID
    .endsegment

    ; Created: 0.12
    ; Updated: 0.23
    macroOpenDrawbridgeByTileChangeID .segment TileChangeID, SoundID=$6E
      PLAY_EXTENDED_SOUND \SoundID ; TODO: sound definitions
      macroTileChangeByID \TileChangeID
    .endsegment

    ; Created: 0.13
    ; Updated: 0.13
    macroDialogueWithBG .segment DialoguePointer, BackgroundID
      macroASMCDialogueWithBGSetup \BackgroundID
      macroASMCDialogueWithBGStart \DialoguePointer
    .endsegment

    ; Created: 0.19
    ; Updated: 0.19
    macroDialogueContinue .segment DialoguePointer
      STORE_LONG lEventEngineLongParameter, \DialoguePointer
      CALL_ASM_LOOP rlASMCDialogueContinue
      YIELD
    .endsegment

    ; Created: 0.14
    ; Updated: 0.14
    macroChapterTitlePopup .segment DialoguePointer
      STORE_LONG aProcSystem.wInput1+size(byte), \DialoguePointer
      STORE_WORD aProcSystem.wInput1, <>\DialoguePointer
      STORE_LONG lR44, procChapterTitle
      CALL_ASM_SKIPPABLE rlEventEngineCreateProcAndSetActive
      YIELD
    .endsegment

    ; Created: 0.17
    ; Updated: 0.19
    macroSetCharacterAI .segment Character, AISetting=[$00, $00, $00, $00]
      ; Shorthand for setting a character's Action and Movement
      ; AI bytes.
      macroASMCSetCharacterDataByte \Character, ActionAI, \AISetting[0]
      macroASMCSetCharacterDataByte \Character, ActionAIOffset, \AISetting[1]
      macroASMCSetCharacterDataByte \Character, MovementAI, \AISetting[2]
      macroASMCSetCharacterDataByte \Character, MovementAIOffset, \AISetting[3]
    .endsegment

    ; Created: 0.18
    ; Updated: 0.19
    macroSetAllUnitsAIIfCharacterDataWord .segment CharacterDataField, Value, AISetting=[$00, $00, $00, $00]
      ; Shorthand for setting all characters' (with a specific
      ; character data field (usually leader) set to a specific
      ; value) AI.
      macroASMCSetCharacterDataByteIfCharacterDataWord ActionAI, \AISetting[0], \CharacterDataField, \Value
      macroASMCSetCharacterDataByteIfCharacterDataWord ActionAIOffset, \AISetting[1], \CharacterDataField, \Value
      macroASMCSetCharacterDataByteIfCharacterDataWord MovementAI, \AISetting[2], \CharacterDataField, \Value
      macroASMCSetCharacterDataByteIfCharacterDataWord MovementAIOffset, \AISetting[3], \CharacterDataField, \Value
    .endsegment

    ; Created: 0.18
    ; Updated: 0.18
    macroASMCScriptedCastMapBattleSetup .macro Staff, Caster, Target, Coords=None
      ; Should be followed by a call to
      ; rlASMCBeginScriptedCastMapBattle.
      STORE_WORD wEventEngineParameter1, \Staff
      STORE_WORD wEventEngineParameter2, None
      STORE_WORD wEventEngineCharacterStructParameter, \Caster
      STORE_WORD wEventEngineCharacterTarget, \Target
      .if (type(\Coords) != type(None))
        STORE_WORD wEventEngineXCoordinate, (\Coords[0] & $FF)
        STORE_WORD wEventEngineYCoordinate, (\Coords[1] & $FF)
      .endif
      CALL_ASM_SKIPPABLE rlASMCScriptedCastMapBattleSetup
    .endmacro

    ; Created: 0.18
    ; Updated: 0.18
    macroASMCBeginScriptedCastMapBattle .macro Callback=None
      .if (\Callback != None)
        STORE_LONG lUnknown7EA4EC, \Callback
      .endif
      CALL_ASM_SKIPPABLE rlASMCBeginScriptedCastMapBattle
      HALT_UNTIL_WORD_SKIPPABLE wMapBattleFlag, 0
    .endmacro

    ; Created: 0.18
    ; Updated: 0.18
    macroScriptedWarpStaff .macro Caster, Target, Coords=[-1, -1]
      ; Coordinates of [-1, -1] mean "off the map"
      ; and should be followed by removing the target unit.
      ; Otherwise, this should be followed by a WARP_UNIT.
      macroASMCCountAllUnitsUncapturedAlive \Caster
      JUMP_FALSE +

      macroASMCCountAllUnitsUncapturedAlive \Target
      JUMP_FALSE +

        macroASMCScriptedCastMapBattleSetup Warp, \Caster, \Target, \Coords
        macroASMCBeginScriptedCastMapBattle rlScriptedWarpCallback

        CALL_ASM_SKIPPABLE rlUpdateUnitMaps
        CALL_ASM_SKIPPABLE rlUpdateVisibilityMap

        PAUSE_SKIPPABLE 2
        YIELD

      +
    .endmacro

    ; Created: 0.18
    ; Updated: 0.18
    macroScriptedStone .macro Caster, Target
      macroASMCCountAllUnitsUncapturedAlive \Caster
      JUMP_FALSE +

      macroASMCCountAllUnitsUncapturedAlive \Target
      JUMP_FALSE +

        macroASMCScriptedCastMapBattleSetup Stone, \Caster, \Target
        macroASMCBeginScriptedCastMapBattle rlScriptedStoneCallback

        CALL_ASM_SKIPPABLE rlUpdateUnitMaps
        CALL_ASM_SKIPPABLE rlUpdateVisibilityMap

        PAUSE_SKIPPABLE 2
        YIELD

      +
    .endmacro

    ; Created: 0.18
    ; Updated: 0.18
    macroScriptedRewarpStaff .macro Caster, Coords=[-1, -1]
      ; Coordinates of [-1, -1] mean "off the map"
      ; and should be followed by removing the caster.
      ; Otherwise, this should be followed by a WARP_UNIT.
      macroASMCScriptedCastMapBattleSetup Rewarp, \Caster, None, \Coords
      .if ((\Coords[0] == -1) && (\Coords[1] == -1))
        STORE_LONG lUnknown7EA4EC, rlScriptedWarpCallback
      .else
        STORE_LONG lUnknown7EA4EC, rlScriptedRewarpCallback
      .endif
      CALL_ASM_SKIPPABLE rlASMCScriptedRewarpSetup
      macroASMCBeginScriptedCastMapBattle

      CALL_ASM_SKIPPABLE rlUpdateUnitMaps
      CALL_ASM_SKIPPABLE rlUpdateVisibilityMap

      PAUSE_SKIPPABLE 2
      YIELD
    .endmacro

    ; Created: 0.18
    ; Updated: 0.18
    macroSetCursorPosition .segment Coordinates=[0, 0]
      STORE_WORD wEventEngineXCoordinate, \Coordinates[0]
      STORE_WORD wEventEngineYCoordinate, \Coordinates[1]
      SET_CURSOR_POSITION
    .endsegment

  ; World map macros

    ; Created: 0.06
    ; Updated: 0.18
    macroASMCWMDialogue .segment DialoguePointer
      STORE_LONG lEventEngineLongParameter, \DialoguePointer
      CALL_ASM_SKIPPABLE rlASMCWorldMapDialogue
    .endsegment

    ; Created: 0.18
    ; Updated: 0.19
    macroWMSetCyclePalette .segment ColorSetting, PalettePointer
      STORE_WORD $7EA93B, \ColorSetting
      STORE_WORD $7EA93F, (\PalettePointer - aBGPaletteBuffer)
      CALL_ASM_SKIPPABLE rlASMCWMSetCyclePalette
    .endsegment

    ; Created: 0.18
    ; Updated: 0.19
    macroWMDrawSpecialMarker .segment Coordinates=[0, 0], MarkerSetting, ActiveSpriteIndex, PalettePointer=$101
      STORE_WORD $7EA93D, \ActiveSpriteIndex
      STORE_WORD $7EA937, \Coordinates[0]
      STORE_WORD $7EA939, \Coordinates[1]
      STORE_WORD $7EA93B, \MarkerSetting
      STORE_WORD $7EA93F, (\PalettePointer - aBGPaletteBuffer)
      CALL_ASM_SKIPPABLE rlASMCWMDrawSpecialMarker
    .endsegment

    ; Created: 0.18
    ; Updated: 0.19
    macroWMClearCyclePalette .segment PalettePointer
      STORE_WORD $7EA93F, (\PalettePointer - aBGPaletteBuffer)
      CALL_ASM_SKIPPABLE rlASMCWMClearCyclePalette
    .endsegment

    ; Created: 0.18
    ; Updated: 0.19
    macroWMClearSpecialMarker .segment ActiveSpriteIndex
      STORE_WORD $7EA93D, \ActiveSpriteIndex
      CALL_ASM_SKIPPABLE rlASMCWMClearSpecialMarker
    .endsegment

.endif ; GUARD_VOLTEDGE_EVENTS_MACROS
