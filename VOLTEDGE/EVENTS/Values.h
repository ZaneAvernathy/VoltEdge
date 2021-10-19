
GUARD_VOLTEDGE_EVENTS_VALUES :?= false
.if (!GUARD_VOLTEDGE_EVENTS_VALUES)
  GUARD_VOLTEDGE_EVENTS_VALUES := true

  VoltEdge_Events_Values_Created = 0.03
  VoltEdge_Events_Values_Updated = 0.17

  ; Useful vanilla pointers

    .weak

      ; Created: 0.03
      ; Updated: 0.03
      eventBattleQuoteDummyEvent :?= address($998024)
        ; Used by boss quote EVENTs, although
        ; the pointer isn't actually read.

      ; Vanilla quote table locations

        ; Created: 0.06
        ; Updated: 0.06
        aBattleQuoteTable :?= address($8CDA07)

        ; Created: 0.06
        ; Updated: 0.06
        aDeathQuoteTable :?= address($8CDBC9)

        ; Created: 0.06
        ; Updated: 0.06
        aReleaseQuoteTable :?= address($8CDF60)

        ; Created: 0.06
        ; Updated: 0.06
        aRetreatQuoteTable :?= address($8CE0FF)

      ; Dialogue with BG handler function

        ; Used with rlASMCDialogueWithBGSetup.

        ; This is the only handler used in
        ; vanilla. Custom handlers must be in
        ; bank $80. Needs more research.

        ; Created: 0.11
        ; Updated: 0.11
        rsDialogueWithBGHandler :?= address($80A23A)

      ; For use with the RUN_ASM event condition

        ; Created: 0.03
        ; Updated: 0.03
        rlECCheckRetreatCoordinates :?= address($8CA400)
          ; Returns carry set if the
          ; tile at [wCursorXCoord, wCursorYCoord]
          ; is a retreat point.

      ; For use with the CALL_ASM_ event codes

      ; Some `ASM` `C`alls use wEventEngineTruthFlag
      ; to return success or failure. When an ASMC lists
      ; wEventEngineTruthFlag as an output, it is assumed
      ; that a failure returns zero in wEventEngineTruthFlag
      ; and a success returns nonzero (usually 1 but it's not
      ; safe to assume such) unless otherwise noted.

      ; Some ASMCs will stall event execution until some
      ; condition becomes true. These ASMCs will list
      ; what conditions cause them to loop. ASMCs with
      ; the ability to loop should be called with
      ; the CALL_ASM_LOOP event code.

      ; Rarely an ASMC will use the static argument parameter
      ; that is part of the CALL_ASM_ code. If used, the ASMC
      ; will list what the argument is.

        ; Created: 0.13
        ; Updated: 0.13
        rlASMCSwapChapterMaps :?= address($849485)
          ; Inputs:
          ;   wCurrentChapter: target chapter ID
          ; Loads and swaps to the map of the
          ; chapter specified by wCurrentChapter.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCClearActiveMapSprites :?= address($8CA097)
          ; Clears active map sprites.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCUpdateMapSpritesUnknown :?= address($8CA0B6)
          ; Re-registers all standing map
          ; sprites if wUnknown000E25 == 0.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCUpdateMapSprites :?= address($8CA0C0)
          ; Re-registers all standing map
          ; sprites. Used with CALL_ASM_SKIPPABLE.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCChangeAllegianceToPlayer :?= address($8CA177)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ; Changes the first unit found with the
          ; specified character ID to the player allegiance.

        ; Created: 0.03
        ; Updated: 0.05
        rlASMCChangeAllegianceToEnemy :?= address($8CA189)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ; Changes the first unit found with the
          ; specified character ID to the enemy allegiance.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCChangeAllegianceToNPC :?= address($8CA19B)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ; Changes the first unit found with the
          ; specified character ID to the NPC allegiance.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCChangeAllegiance :?= address($8CA1AD)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ;   wEventEngineParameter2: target character allegiance
          ;   wEventEngineParameter3: new character allegiance
          ;   wEventEngineCharacterStructParameter: new leader character ID
          ; Changes all units with a target character ID
          ; and allegiance to a new allegiance. Also sets
          ; their leader.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCChangeAllegianceToPlayerIfHeld :?= address($8CA1C7)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ; Outputs:
          ;   wEventEngineTruthFlag: failure if unit is not
          ;     being held or if the player is out of deployment slots.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCMount :?= address($8CA1FA)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ; Forces the specified unit to mount.
          ; Units without a mounted class or
          ; units that are already mounted are
          ; not affected.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCDismount :?= address($8CA203)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ; Forces the specified unit to dismount.
          ; Units without a dismounted class or
          ; units that are already dismounted are
          ; not affected.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCIsUnitHeld :?= address($8CA20C)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ; Outputs:
          ;   wEventEngineTruthFlag: success if unit
          ;     is being held/captured, failure if
          ;     not being held or if not found.
          ; Used to check if a unit is being held.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCIsUnitHeldByEnemy :?= address($8CA238)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ; Outputs:
          ;   wEventEngineTruthFlag: success if unit
          ;     is being held/captured by an enemy,
          ;     failure if not being held or if not found.
          ; Used to check if a unit is being held by an enemy.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCClearRescue :?= address($8CA270)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ; Clears the rescue(d) status from the unit
          ; and their rescuer/rescuee.

        ; Created: 0.17
        ; Updated: 0.17
        rlASMCClearActiveUnitRescue :?= address($8CA2E0)
          ; Inputs:
          ;   aSelectedCharacterBuffer: filled with target unit
          ; Clears the rescue(d) status from the active unit
          ; and their rescuer/rescuee.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCSetFlagIfRetreatingUnitByTable :?= address($8CA2F4)
          ; Inputs:
          ;   lEventEngineLongParameter: long pointer to retreat table
          ; Used to set event flags when certain units retreat
          ; from the map. See "EVENTS/Helpers.h" for a description
          ; of the table format.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCRemoveUnit :?= address($8CA343)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ; Deletes the specified unit, freeing their
          ; deployment slot.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCPromoteUnit :?= address($8CA36B)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ;   wEventEngineParameter1: class ID
          ; Promotes a unit to the specified class.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCPromoteUnitSilent :?= address($8CA376)
          ; Inputs:
          ;   aSelectedCharacterBuffer: filled with target unit
          ;   wEventEngineParameter1: class ID
          ; Promotes a unit without the normal fanfare.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCSetUnitPosition :?= address($8CA385)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ;   [wEventEngineXCoordinate, wEventEngineYCoordinate]: new coordinates
          ; Sets a unit's position to the target coordinates.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCUpdateRetreatingUnitState :?= address($8CA3C7)
          ; Inputs:
          ;   aSelectedCharacterBuffer: filled with target unit
          ; Updates the UnitState of the unit
          ; and does some bookkeeping for setting
          ; up a retreat.

        ; Created: 0.03
        ; Updated: 0.17
        rlASMCCopyUnitToEventBuffer :?= address($8CA426)
          ; Inputs:
          ;   aSelectedCharacterBuffer: filled with target unit
          ; Outputs:
          ;   aEventCharacterBuffer: filled with target unit
          ; Copies a unit from aSelectedCharacterBuffer to
          ; aEventCharacterBuffer.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCCopyUnitFromEventBuffer :?= address($8CA445)
          ; Inputs:
          ;   aEventCharacterBuffer: filled with target unit
          ; Outputs:
          ;   aSelectedCharacterBuffer: filled with target unit
          ; Copies a unit from aEventCharacterBuffer to
          ; aSelectedCharacterBuffer.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCSetUnitState :?= address($8CA464)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ;   wEventEngineParameter1: unit state bitfield
          ; Sets the specified bits in the
          ; unit's unit state.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCUnsetUnitState :?= address($8CA486)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ;   wEventEngineParameter1: unit state bitfield
          ; Unsets the specified bits in the
          ; unit's unit state.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCCheckUnitStateSet :?= address($8CA4B1)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ;   wEventEngineParameter1: unit state bitfield
          ; Outputs:
          ;   wEventEngineTruthFlag: success if unit
          ;     has the specified unit state bits set,
          ;     failure if not all of the specified bits
          ;     are set.
          ; Checks if a unit has unit state
          ; bits set.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCCheckUnitStateUnset :?= address($8CA4E0)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ;   wEventEngineParameter1: unit state bitfield
          ; Outputs:
          ;   wEventEngineTruthFlag: success if unit
          ;     has the specified unit state bits unset,
          ;     failure if not all of the specified bits
          ;     are unset.
          ; Checks if a unit has unit state
          ; bits unset.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCCheckUnitStatus :?= address($8CA50F)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ;   wEventEngineParameter1: status
          ; Outputs:
          ;   wEventEngineTruthFlag: success if unit has
          ;     the specified status, otherwise failure.
          ; Checks if a unit has a specific status.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCCheckAbleToTalk :?= address($8CA55A)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ; Outputs:
          ;   wEventEngineTruthFlag: success if unit can talk,
          ;     failure if unit has a status or
          ;     condition that prevents them from
          ;     talking.
          ; Checks if a unit can talk/be talked to.
          ; Does not check if the unit has any talks
          ; available.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCAllUnitsSetUnitState :?= address($8CA5C8)
          ; Inputs:
          ;   wEventEngineParameter1: unit state bitfield
          ; Sets the specified unit state bits
          ; for all units.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCAllUnitsUnsetUnitState :?= address($8CA5E9)
          ; Inputs:
          ;   wEventEngineParameter1: unit state bitfield
          ; Unsets the specified unit state bits
          ; for all units.

        ; Created: 0.03
        ; Updated: 0.06
        rlASMCActiveUnitSetUnitState :?= address($8CA613)
          ; Inputs:
          ;   aSelectedCharacterBuffer: filled with target unit
          ;   wEventEngineParameter1: unit state bitfield
          ; Sets the unit state bits for the target unit.

        ; Created: 0.03
        ; Updated: 0.06
        rlASMCActiveUnitUnsetUnitState :?= address($8CA62E)
          ; Inputs:
          ;   aSelectedCharacterBuffer: filled with target unit
          ;   wEventEngineParameter1: unit state bitfield
          ; Unsets the unit state bits for the target unit.

        ; Created: 0.03
        ; Updated: 0.06
        rlASMCActiveUnitCheckUnitState :?= address($8CA652)
          ; Inputs:
          ;   aSelectedCharacterBuffer: filled with target unit
          ;   wEventEngineParameter1: unit state bitfield
          ; Outputs:
          ;   wEventEngineTruthFlag: success if unit has all
          ;     of the specified unit state bits set, failure
          ;     otherwise.
          ; Checks if the active unit has the specified
          ; unit state bits set.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCActiveUnitCheckCarrying :?= address($8CA6A1)
          ; Inputs:
          ;   aSelectedCharacterBuffer: filled with target unit
          ;   wEventEngineParameter1: character ID to look for
          ; Outputs:
          ;   wEventEngineTruthFlag: success if active unit is
          ;     carrying the specified unit, otherwise failure.
          ; Checks if the active unit is carrying a
          ; specific unit.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCCountOwnedItem :?= address($8CA6F3)
          ; Inputs:
          ;   wEventEngineParameter1: item ID
          ; Outputs:
          ;   wEventEngineParameter3: number of the item owned
          ;   wEventEngineTruthFlag: success if the player
          ;     has at least one of the item, failure otherwise.
          ; Counts the number of a specific item owned
          ; by the player.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCCheckUnitForItem :?= address($8CA755)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ;   wEventEngineParameter1: item ID
          ; Outputs:
          ;   wEventEngineTruthFlag: success if unit has specified
          ;     item, otherwise failure.
          ; Checks to see if a unit is holding a specified item.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCGiveUnitItemSilent :?= address($8CA789)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ;   wEventEngineParameter1: item ID
          ; Gives a unit an item without a popup.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCCheckUnitExists :?= address($8CA7B0)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ; Outputs:
          ;   wEventEngineTruthFlag: success if unit exists,
          ;     false otherwise.
          ; Checks if a unit exists in the pool of all
          ; units.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCSaveActiveUnitClearHDMA :?= address($8CA7D0)
          ; Inputs:
          ;   aSelectedCharacterBuffer: filled with target character
          ; Copies the active unit back into their
          ; deployment slot. Also clears window HDMA.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCSaveActiveUnit :?= address($8CA7D4)
          ; Inputs:
          ;   aSelectedCharacterBuffer: filled with target character
          ; Copies the active unit back into their
          ; deployment slot.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCRemoveItemFromUnit :?= address($8CA7DF)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ;   wEventEngineParameter1: item ID
          ; Removes the first instance of a specified
          ; item from a unit.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCGiveUnitItemsToConvoy :?= address($8CA809)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ; Gives a unit's items to the convoy.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCGiveActiveUnitItem :?= address($8CA8DD)
          ; Inputs:
          ;   aSelectedCharacterBuffer: filled with target unit
          ;   wEventEngineParameter1: item ID
          ; Outputs:
          ;   wEventEngineTruthFlag: success if able to give
          ;     item, failure if unable (i.e. unit's
          ;     inventory is full).
          ; Tries to give the active unit an item,
          ; returns whether or not it succeeds.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCGiveActiveUnitItemCurrentDurability :?= address($8CA8E9)
          ; Inputs:
          ;   aSelectedCharacterBuffer: filled with target unit
          ;   wEventEngineParameter1: item ID and durability
          ; Outputs:
          ;   wEventEngineTruthFlag: success if able to give
          ;     item, failure if unable (i.e. unit's
          ;     inventory is full).
          ; Tries to give the active unit an item,
          ; returns whether or not it succeeds. The upper byte
          ; of wEventEngineParameter1 is the durability,
          ; the lower byte is the item ID.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCGiveConvoyItem :?= address($8CA939)
          ; Inputs:
          ;   wEventEngineParameter1: item ID
          ; Gives an item to the convoy.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCSetupGiveToConvoyIfInventoryFull :?= address($8CA956)
          ; Inputs:
          ;   aSelectedCharacterBuffer: filled with target unit
          ;   wEventEngineParameter1: item ID
          ;   wEventEngineTruthFlag: if success, create prompt,
          ;     otherwise ASMC is skipped.
          ; Creates a prompt to give either an
          ; item from a unit's inventory or a specified
          ; item to the convoy if wEventEngineTruthFlag
          ; was nonzero. Follow this with
          ; rlASMCWaitWhileGiveToConvoyIfInventoryFull
          ; to wait for the prompt to finish.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCWaitWhileGiveToConvoyIfInventoryFull :?= address($8CA96D)
          ; Loops: while the give item to convoy
          ;   prompt exists.
          ; Waits until rlASMCSetupGiveToConvoyIfInventoryFull
          ; is done.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCSetupGiveItemPopup :?= address($8CA97E)
          ; Shows a popup for getting an
          ; item if there is a visible unit at
          ; the cursor's coordinates after
          ; rlASMCGiveActiveUnitItem is called.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCWaitWhileGiveItemPopup :?= address($8CA9B4)
          ; Loops: while the item popup exists.
          ; Waits until rlASMCSetupGiveItemPopup
          ; is finished.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCCheckIfUnitHasEquippedWeapon :?= address($8CA9C5)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ; Outputs:
          ;   wEventEngineTruthFlag: success if unit has a weapon
          ;     equipped, failure otherwise.
          ; Checks if a unit has an equipped weapon.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCAddGoldWord :?= address($8CAA27)
          ; Inputs:
          ;   wEventEngineParameter1: gold amount
          ; Adds an amount of gold to
          ; the player's gold total.
          ; Caps at 999,999.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCSubtractGoldWord :?= address($8CAA37)
          ; Inputs:
          ;   wEventEngineParameter1: gold amount
          ; Subrtracts an amount of gold
          ; from the player's gold total.
          ; Caps at 0.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCCompareGoldGTE :?= address($8CAA47)
          ; Inputs:
          ;   wEventEngineParameter1: gold amount
          ; Outputs:
          ;   wEventEngineTruthFlag: success if player
          ;     has gold greater than or equal to the
          ;     amount specified.
          ; Checks to see if the player has at
          ; least an amount of gold.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCSetActiveUnitTileToPlains :?= address($8CAA67)
          ; Inputs:
          ;   aSelectedCharacterBuffer: filled with target unit
          ; Sets the tile of the active
          ; unit to plains.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCStoreUnitToUnitMapByCoordinates :?= address($8CAA85)
          ; Inputs:
          ;   wEventEngineParameter1: deployment number
          ;   wEventEngineXCoordinate: X coordinate
          ;   wEventEngineYCoordinate: Y coordinate
          ; Stores a unit's deployment number
          ; to the coordinates in the unit map.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCSingleTileChangeSavedTile :?= address($8CAAA5)
          ; Inputs:
          ;   wEventEngineParameter1: new metatile
          ;   wEventEngineXCoordinate: X coordinate
          ;   wEventEngineYCoordinate: Y coordinate
          ; Outputs:
          ;   wEventEngineSavedTile: original metatile
          ; Changes a single map tile into another,
          ; keeping track of the original tile.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCRevertSingleTileChangeSavedTile :?= address($8CAACE)
          ; Inputs:
          ;   wEventEngineSavedTile: new metatile
          ;   wEventEngineXCoordinate: X coordinate
          ;   wEventEngineYCoordinate: Y coordinate
          ; Sets a map tile back to the saved metatile.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCSingleTileChangeByCoords :?= address($8CAADA)
          ; Inputs:
          ;   wEventEngineParameter1: new metatile
          ;   wEventEngineXCoordinate: X coordinate
          ;   wEventEngineYCoordinate: Y coordinate
          ; Changes a single map tile into another.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCSetTileToDoor :?= address($8CAB17)
          ; Inputs:
          ;   wEventEngineXCoordinate: X coordinate
          ;   wEventEngineYCoordinate: Y coordinate
          ; Changes a map tile's terrain to door.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCChapterEnd :?= address($8CAB5B)
          ; Ends the chapter and prepares
          ; the next chapter.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCFinalChapterEnd :?= address($8CABC9)
          ; Ends the final chapter.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCSaveChapterTurncount :?= address($8CABDB)
          ; Saves the turncount for
          ; the current chapter.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCUnknownChapterEnd8CAC00 :?= address($8CAC00)
          ; Difference between this and
          ; rlASMCChapterEnd is unknown.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCUnknown8CAC3A :?= address($8CAC3A)
          ; Loops:
          ;   If wEventEngineStatus bit
          ;   $4000 is set and the screen brightness
          ;   is not off.
          ; Purpose unknown, seems to clear
          ; active sprites.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCEndWMEvents :?= address($8CAC98)
          ; Used to end world map events.
          ; Interestingly, it does have
          ; code to loop but never uses it.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCTileChangeByID :?= address($8CACD3)
          ; Inputs:
          ;   wEventEngineParameter1: tile change ID
          ; Triggers the selected tile change.
          ; Be sure to call rlASMCDecompressChapterMapChanges
          ; beforehand and wait for decompression
          ; and DMA to finish.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCDecompressChapterMapChanges :?= address($8CAD09)
          ; Decompresses the current chapter's
          ; map changes to a RAM buffer. Used before
          ; rlASMCTileChangeByID.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCWriteUnitAtTileToBuffer :?= address($8CAD2A)
          ; Inputs:
          ;   wEventEngineXCoordinate: X coordinate
          ;   wEventEngineYCoordinate: Y coordinate
          ; Outputs:
          ;   aBurstWindowCharacterBuffer: filled with unit
          ;   wEventEngineTruthFlag: success if there is a
          ;     unit at the tile, otherwise failure.
          ; Checks if a unit is at a tile and
          ; writes their data to a buffer.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCCheckIfUnitAtCoords :?= address($8CAD57)
          ; Inputs:
          ;   wEventEngineXCoordinate: X coordinate
          ;   wEventEngineYCoordinate: Y coordinate
          ;   wEventEngineCharacterTarget: target unit ID
          ; Outputs:
          ;   wEventEngineTruthFlag: success if there is
          ;     a unit at the tile and the unit matches
          ;     the target, otherwise failure.
          ; Checks if a specific unit is at a tile.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCLoopWhileSpawnedUnitsMoving :?= address($8CADC7)
          ; This ASMC is bugged, don't use it.
          ; Instead of checking all units in
          ; a group, repeatedly checks the first unit.
          ; It will hang if the unit's target tile
          ; isn't empty.
          ; Loops: If at least one of the
          ;   units' target tile is empty in
          ;   a unit group.
          ; Outputs:
          ;   wEventEngineTruthFlag: success if at least
          ;     one target tile is empty.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCLoadUnitGroup :?= address($8CAE1C)
          ; Loops: Until all units in a
          ;   group are loaded or skipped
          ;   if unable to be loaded.
          ; Inputs:
          ;   lEventEngineUnitGroupPointer: long pointer to unit group
          ; Outputs:
          ;   lEventEngineUnitGroupPointer: lower word cleared
          ; Loads a unit every event
          ; engine cycle unit all units are
          ; loaded or skipped.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCPrepareCapturedUnitsForRescue :?= address($8CAECB)
          ; Loops: Until all units in a
          ;   group are loaded or skipped
          ;   if unable to be loaded.
          ; Inputs:
          ;   lEventEngineUnitGroupPointer: (target Allegiance + 1) * size(word)
          ;   lEventEngineLongParameter: long pointer to coordinate table
          ; Outputs:
          ;   lEventEngineUnitGroupPointer: lower word cleared
          ; Loads units that have been previously captured
          ; from the specified allegiance and loads them
          ; to coordinates given by a null-terminated table of
          ; coordinate bytes.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCLoadPlayerUnitsByStartingPositions :?= address($8CAF73)
          ; Loops: Until all units in a
          ;   group are loaded or skipped
          ;   if unable to be loaded.
          ; Loads player units in chapters
          ; that lack a prep screen. Requires
          ; rlASMCGetStartingPositionsArrayPointerAndLength
          ; to be called beforehand. Units are loaded
          ; based on a $FF-byte terminated table of
          ; coordinate bytes pointed to in the chapter's
          ; chapter data.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCGetStartingPositionsArrayPointerAndLength :?= address($8CAF81)
          ; Inputs:
          ;   lEventEngineUnitGroupPointer: (target Allegiance + 1) * size(word)
          ; Generates a list of units for
          ; rlASMCLoadPlayerUnitsByStartingPositions to
          ; load. Call this before that.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCAllUnitsSetCharacterDataByte :?= address($8CB095)
          ; Inputs:
          ;   wEventEngineParameter1: character data byte offset
          ;   wEventEngineParameter2: new value
          ; Sets the specified character data byte
          ; to a new value for all units.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCSetCharacterDataByte :?= address($8CB0CC)
          ; Inputs:
          ;   wEventEngineParameter1: character data byte offset
          ;   wEventEngineParameter2: new value
          ;   wEventEngineCharacterTarget: target unit ID
          ; Sets the specified character data byte
          ; to a new value for all units with
          ; a specified unit ID.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCSetCharacterDataWord :?= address($8CB127)
          ; Inputs:
          ;   wEventEngineParameter1: character data word offset
          ;   wEventEngineParameter2: new value
          ;   wEventEngineCharacterTarget: target unit ID
          ; Sets the specified character data word
          ; to a new value for all units with
          ; a specified unit ID.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCAddCharacterDataByte :?= address($8CB167)
          ; Inputs:
          ;   wEventEngineParameter1: character data byte offset
          ;   wEventEngineParameter2: value to add
          ;   wEventEngineCharacterTarget: target unit ID
          ; Adds a value to the character data
          ; byte for all units with a specified
          ; unit ID.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCSubtractCharacterDataByte :?= address($8CB1AA)
          ; Inputs:
          ;   wEventEngineParameter1: character data byte offset
          ;   wEventEngineParameter2: value to subtract
          ;   wEventEngineCharacterTarget: target unit ID
          ; Subtracts a value from the character data
          ; byte for all units with a specified
          ; unit ID.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCSetBitsCharacterDataWord :?= address($8CB1ED)
          ; Inputs:
          ;   wEventEngineParameter1: character data word offset
          ;   wEventEngineParameter2: value to combine
          ;   wEventEngineCharacterTarget: target unit ID
          ; Combines the bits of a value with the character
          ; data word for all units with a specified
          ; unit ID.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCUnsetBitsCharacterDataWord :?= address($8CB230)
          ; Inputs:
          ;   wEventEngineParameter1: character data word offset
          ;   wEventEngineParameter2: value to strip
          ;   wEventEngineCharacterTarget: target unit ID
          ; Clears the bits of a value from the character
          ; data word for all units with a specified
          ; unit ID.

        ; Created: 0.03
        ; Updated: 0.03
        rlASMCCheckBitsSetCharacterDataWord :?= address($8CB276)
          ; Inputs:
          ;   wEventEngineParameter1: character data word offset
          ;   wEventEngineParameter2: bits to match
          ;   wEventEngineCharacterTarget: target unit ID
          ; Outputs:
          ;   wEventEngineTruthFlag: success if any of
          ;     the bits in the given value are set
          ;     in the character data word of any
          ;     of the units with a specified unit ID.
          ; Checks if any units with a specified unit ID
          ; have any bits of a character data word in common
          ; with a specified value.

        ; Created: 0.03
        ; Updated: 0.06
        rlASMCSetCharacterDataByteIfCharacterDataByte :?= address($8CB2B6)
          ; Inputs:
          ;   wEventEngineParameter1: character data byte offset
          ;   wEventEngineParameter2: value to store
          ;   wEventEngineCharacterTarget: value to check for
          ;   wEventEngineCharacterStructParameter: character data byte offset to check
          ; Sets a character data byte to a specified value
          ; for all units with some character data byte set
          ; to a specified value. You could use this to
          ; affect all units rescuing a certain character ID,
          ; for instance.

        ; Created: 0.05
        ; Updated: 0.06
        rlASMCSetCharacterDataByteIfCharacterDataWord :?= address($8CB2FC)
          ; Inputs:
          ;   wEventEngineParameter1: character data byte offset
          ;   wEventEngineParameter2: value to store
          ;   wEventEngineCharacterTarget: value to check for
          ;   wEventEngineCharacterStructParameter: character data word offset to check
          ; Sets a character data byte to a specified value
          ; for all units with some character data word set
          ; to a specified value. You could use this to
          ; affect all units rescuing a certain character ID,
          ; for instance.

        ; Created: 0.05
        ; Updated: 0.06
        rlASMCSetCharacterDataWordBitsIfCharacterDataWord :?= address($8CB33F)
          ; Inputs:
          ;   wEventEngineParameter1: character data word offset
          ;   wEventEngineParameter2: value to combine
          ;   wEventEngineCharacterTarget: value to check for
          ;   wEventEngineCharacterStructParameter: character data word offset to check
          ; rlASMCSetCharacterDataByteIfCharacterDataWord but
          ; instead sets the bits specified by wEventEngineParameter2
          ; in the character data word specified by
          ; wEventEngineParameter1.

        ; Created: 0.05
        ; Updated: 0.06
        rlASMCUnsetCharacterDataWordBitsIfCharacterWord :?= address($8CB381)
          ; Inputs:
          ;   wEventEngineParameter1: character data word offset
          ;   wEventEngineParameter2: value to strip
          ;   wEventEngineCharacterTarget: value to check for
          ;   wEventEngineCharacterStructParameter: character data word offset to check
          ; rlASMCUnsetCharacterDataWordBitsIfCharacterWord but
          ; instead unsets the bits.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCCountAllUnitsWithCharacterDataByte :?= address($8CB3C6)
          ; Inputs:
          ;   wEventEngineParameter1: character data byte offset
          ;   wEventEngineParameter2: value to check for
          ; Outputs:
          ;   wEventEngineParameter1: number of units
          ;   wEventEngineTruthFlag: success if at least one
          ;     unit with value found, failure otherwise
          ; Counts all units with a character data
          ; byte set to a specific value. Also overwrites
          ; wEventEngineParameter3 with the unit count,
          ; so be careful. It's recommended that you
          ; use wEventEngineParameter1 as the return
          ; value out of convention.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCCountPlayerUnitsWithCharacterDataByte :?= address($8CB410)
          ; Inputs:
          ;   wEventEngineParameter1: character data byte offset
          ;   wEventEngineParameter2: value to check for
          ; Outputs:
          ;   wEventEngineParameter1: number of units
          ;   wEventEngineTruthFlag: success if at least one
          ;     unit with value found, failure otherwise
          ; Same as rlASMCCountAllUnitsWithCharacterDataByte
          ; but only for player units.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCCountAllUnitsWithCharacterDataWord :?= address($8CB442)
          ; Inputs:
          ;   wEventEngineParameter1: character data word offset
          ;   wEventEngineParameter2: value to check for
          ; Outputs:
          ;   wEventEngineParameter1: number of units
          ;   wEventEngineTruthFlag: success if at least one
          ;     unit with value found, failure otherwise
          ; Same as rlASMCCountAllUnitsWithCharacterDataByte
          ; but for character data words.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCCountAllUnitsWithCharacterDataWordBitsSet :?= address($8CB488)
          ; Inputs:
          ;   wEventEngineParameter1: character data word offset
          ;   wEventEngineParameter2: bits to check for
          ; Outputs:
          ;   wEventEngineParameter1: number of units
          ;   wEventEngineTruthFlag: success if at least one
          ;     unit with value found, failure otherwise
          ; Same as rlASMCCountAllUnitsWithCharacterDataWord
          ; but counts the unit if their character data
          ; word has any bits set in common with the value.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCCountAllUnitsUncapturedAlive :?= address($8CB4CE)
          ; Inputs:
          ;   wEventEngineCharacterTarget: character to count
          ; Outputs:
          ;   wEventEngineParameter1: number of units
          ;   wEventEngineTruthFlag: success if at least one
          ;     unit found, failure otherwise
          ; Counts living units.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCCountPlayerUnitsUncapturedAlive :?= address($8CB4FA)
          ; Inputs:
          ;   wEventEngineCharacterTarget: character to count
          ; Outputs:
          ;   wEventEngineParameter1: number of units
          ;   wEventEngineTruthFlag: success if at least one
          ;     unit found, failure otherwise
          ; Counts living player units.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCCountEnemyUnitsUncapturedAlive :?= address($8CB526)
          ; Inputs:
          ;   wEventEngineCharacterTarget: character to count
          ; Outputs:
          ;   wEventEngineParameter1: number of units
          ;   wEventEngineTruthFlag: success if at least one
          ;     unit found, failure otherwise
          ; Counts living enemy units.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCCountNPCUnitsUncapturedAlive :?= address($8CB552)
          ; Inputs:
          ;   wEventEngineCharacterTarget: character to count
          ; Outputs:
          ;   wEventEngineParameter1: number of units
          ;   wEventEngineTruthFlag: success if at least one
          ;     unit found, failure otherwise
          ; Counts living NPC units.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCCountAllUnitsUncapturedAliveWithActing :?= address($8CB5C3)
          ; Inputs:
          ;   wEventEngineCharacterTarget: character to count
          ; Outputs:
          ;   wEventEngineParameter1: number of units
          ;   wEventEngineTruthFlag: success if at least one
          ;     unit found, failure otherwise
          ; Counts living units, including those that are
          ; currently acting (moving, fighting?, etc.).

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCCountAllUnitsUncapturedAliveByTable :?= address($8CB5DC)
          ; Inputs:
          ;   lEventEngineLongParameter: long pointer to table
          ; Outputs:
          ;   wEventEngineParameter1: number of units
          ;   wEventEngineTruthFlag: success if at least one
          ;     unit found, failure otherwise
          ; Same as rlASMCCountAllUnitsUncapturedAlive
          ; but takes a long pointer to a null-terminated
          ; list of character ID words.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCCountAllUnitsRescuedByPlayerOrNPCByTable :?= address($8CB621)
          ; Inputs:
          ;   lEventEngineLongParameter: long pointer to table
          ; Outputs:
          ;   wEventEngineParameter1: number of units
          ;   wEventEngineTruthFlag: success if at least one
          ;     unit found, failure otherwise
          ; Counts the number of units whose
          ; character IDs are specified by a null-terminated
          ; list of character ID words that are currently
          ; being held by player or NPC units.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCCountAllUnitsRescuedByPlayerOrNPC :?= address($8CB666)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ; Outputs:
          ;   wEventEngineParameter1: number of units
          ;   wEventEngineTruthFlag: success if at least one
          ;     unit found, failure otherwise
          ; Counts the number of units whose
          ; character ID matches the given ID who is
          ; being held by player or NPC units.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCCheckConomoreOnMap :?= address($8CB6EC)
          ; Outputs:
          ;  wEventEngineTruthFlag: success if
          ;    Conomore survived, failure otherwise
          ; Used in vanilla at the end of chapter 16A.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCCountAllUnitsAlive :?= address($8CB70C)
          ; Inputs:
          ;   wEventEngineCharacterTarget: target character ID
          ; Outputs:
          ;   wEventEngineParameter1: number of units
          ;   wEventEngineTruthFlag: success if at least one
          ;     unit found, failure otherwise
          ; Counts living units with a given character ID.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCSetUnitsLeftBehindAsCaptured :?= address($8CB789)
          ; Used at the end of escape chapter
          ; ending events to remove units from
          ; the party when left behind.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCChapter21xDisplaceUnitsLeftBehind :?= address($8CB7E6)
          ; Names are hard.
          ; Used in vanilla to move units
          ; left behind at the end of chapter 21x
          ; to [1, 1] so that they're offscreen
          ; during Julius and Ishtar's cutscene.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCCreateRandomChestItemArrayFromUnitInventories :?= address($8CB82B)
          ; Transfers items from deployed
          ; player units into an array for
          ; generating randomized chests.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCAddFixedItemsToRandomChestArray :?= address($8CB964)
          ; Adds a rapier, iron sword,
          ; steel sword, and a vulnerary
          ; to the randomized chest array.
          ; Used in chapter 4.

        ; Created: 0.05
        ; Updated: 0.17
        rlASMCCreateRandomChestTiles :?= address($8CB98A)
          ; Creates up to 16 randomized
          ; chests from items in the
          ; randomized chest array. Called
          ; after rlASMCCreateRandomChestItemArrayFromUnitInventories.
          ; The coordinates for these
          ; chests are fixed in vanilla,
          ; based on a table in chapter 4's events.

        ; Created: 0.17
        ; Updated: 0.17
        rlASMCGetRandomChestItem :?= address($8CB9C7)
          ; Selects a pregenerated random chest
          ; item to give.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCCheckForcedBlank :?= address($8CBA9F)
          ; Outputs:
          ;   wEventEngineTruthFlag: success if forced
          ;     blank, failure otherwise
          ; Checks to see if the screen is off.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCFinalChapterFlash :?= address($8CBB9B)
          ; Triggers the green flashy
          ; effect after seizing the final
          ; chapter's throne.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCDialogueContinue :?= address($8CBBAD)
          ; Continues ongoing dialogue,
          ; typically after running events
          ; or changing lEventEngineLongParameter
          ; to new dialogue. Useful for
          ; conditional dialogue.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCSetBattleQuoteMusic :?= address($8CBDB7)
          ; Inputs:
          ;   wEventEngineCharacterStructParameter: target
          ;     character ID
          ; Used internally by the battle
          ; quote handler. Sets the music
          ; based on the battle music table.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCGetChapterTurncount :?= address($8CBDDC)
          ; Inputs:
          ;   wEventEngineParameter1: chapter number
          ; Outputs:
          ;   wEventEngineParameter1: turncount for that chapter
          ;   wEventEngineTruthFlag: success if turncount
          ;     is nonzero, failure otherwise
          ; Typically used to see if a gaiden chapter
          ; was completed. A chapter that was not
          ; visited has a turncount of 0 and thus returns
          ; a failure.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCPrepActiveUnitPortrait :?= address($8CC731)
          ; Fetches the active unit's
          ; portrait ID to be used in upcoming
          ; dialogue.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCFinalChapterFadeToWhite :?= address($8CC73E)
          ; Fades out the final chapter.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCDialogueWithBGEndFadeOut :?= address($8CC78C)
          ; Ends dialogue with backgrounds
          ; after a fade, typically at the end of
          ; a chapter.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCWorldMapDialogue :?= address($8CCAD4)
          ; Inputs:
          ;   lEventEngineLongParameter: long pointer to dialogue
          ; Used for text on the world map.
          ; Used with CALL_ASM_SKIPPABLE.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCClearOlwenWinsLosses :?= address($8CCD87)
          ; Used in vanilla to clear
          ; Olwen's wins/losses when recruiting
          ; Ilios.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCDialogueWithBGStart :?= address($8CD0C3)
          ; Argument: long pointer to dialogue
          ; Begins dialogue with a BG. Requires
          ; rlASMCDialogueWithBGSetup beforehand.
          ; Afterwards must be ended with rlASMCDialogueWithBGEnd.
          ; Should be immediately followed by 3 YIELD_UNKs.
          ; Used with CALL_ASM_LONG_SKIPPABLE.

        ; Created: 0.05
        ; Updated: 0.05
        rlASMCDialogueWithBGEnd :?= address($8CD0E5)
          ; Used to end dialogue with a BG.

        ; Created: 0.05
        ; Updated: 0.06
        rlASMCChangeMapMusic :?= address($8CD0ED)
          ; Argument: song ID
          ; Changes the map music. Used
          ; with CALL_ASM_LONG_SKIPPABLE.

        ; Created: 0.05
        ; Updated: 0.11
        rlASMCDialogueWithBGSetup :?= address($8CD0FB)
          ; Argument: short pointer to handler in bank $80
          ; Inputs:
          ;   wEventEngineParameter1: background ID
          ; Sets up a dialogue background.
          ; Used with CALL_ASM_SKIPPABLE.
          ; The handler is always <>rsDialogueWithBGHandler
          ; ($80A23A) in vanilla.

    .endweak

.endif ; GUARD_VOLTEDGE_EVENTS_VALUES
