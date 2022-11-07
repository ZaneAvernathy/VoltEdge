
GUARD_VOLTEDGE_HDMA_VALUES :?= false
.if (!GUARD_VOLTEDGE_HDMA_VALUES)
  GUARD_VOLTEDGE_HDMA_VALUES := true

  VoltEdge_HDMA_Values_Created = 0.22
  VoltEdge_HDMA_Values_Updated = 0.22

  .weak

    ; These are useful vanilla HDMA system functions.

      ; Created: 0.22
      ; Updated: 0.22
      rlHDMAEngineCreateEntry :?= address($82A3ED)
        ; Inputs:
        ;   lR44: long pointer to HDMA info
        ; Outputs:
        ;   Carry clear if successful,
        ;     set otherwise.
        ; Creates the specified HDMA entry.

      ; Created: 0.22
      ; Updated: 0.22
      rlHDMAEngineCreateEntryByIndex :?= address($82A470)
        ; Inputs:
        ;   A: Index into HDMA system
        ;   lR44: long pointer to HDMA info
        ; Outputs:
        ;   Carry clear if successful,
        ;     set otherwise.
        ; Creates the specified HDMA entry in the specified
        ; slot. Fails if there is already an HDMA entry in the slot.

      ; Created: 0.22
      ; Updated: 0.22
      rlHDMAEngineFreeEntryByIndex :?= address($82A495)
        ; Inputs:
        ;   A: Index into HDMA system
        ;   lR44: long pointer to HDMA info
        ; Outputs:
        ;   Carry clear if successful,
        ;     set otherwise.
        ; Disables the specified HDMA entry in the specified
        ; slot. Fails if there isn't an HDMA entry in the slot.

      ; Created: 0.22
      ; Updated: 0.22
      rlHDMAEngineFreeEntryByOffset :?= address($82A582)
        ; Inputs:
        ;   X: offset into the HDMA system
        ; Outputs:
        ;   None
        ; Disables the HDMA entry in the specified slot.

      ; Created: 0.22
      ; Updated: 0.22
      rlHDMAEngineFindEntry :?= address($82A586)
        ; Inputs:
        ;   lR44: long pointer to HDMA info to look for
        ; Outputs:
        ;   X: offset of entry in HDMA system if found
        ;   Carry set if the entry is found,
        ;     clear otherwise.
        ; Checks if a specific HDMA entry exists in the HDMA system
        ; and returns its offset if it does.

    ; These are internal HDMA system functions that
    ; are used by HDMA code.

      ; Created: 0.22
      ; Updated: 0.22
      rsHDMACodeSleep :?= address($82A5A8)
        ; Causes the HDMA engine to pause execution
        ; for a number of cycles.

      ; Created: 0.22
      ; Updated: 0.22
      rsHDMACodeEnd :?= address($82A5B6)
        ; Ends an HDMA code routine and stops
        ; the HDMA entry's code from being executed
        ; every cycle.

      ; Created: 0.22
      ; Updated: 0.22
      rsHDMACodeHaltSleep :?= address($82A5C4)
        ; Causes HDMA code execution to stall until
        ; something else changes the HDMA entry's code
        ; offset. This variant also sets the HDMA entry's
        ; aSleepTimer to 1, causing code execution
        ; to pause for a cycle.

      ; Created: 0.22
      ; Updated: 0.22
      rsHDMACodeHalt :?= address($82A5CA)
        ; Causes HDMA code execution to stall until
        ; something else changes the HDMA entry's code
        ; offset.

      ; Created: 0.22
      ; Updated: 0.22
      rsHDMACodeCall :?= address($82A5D2)
        ; Calls a native assembly function.

      ; Created: 0.22
      ; Updated: 0.22
      rsHDMACodeSetOnCycle :?= address($82A5ED)
        ; Sets the HDMA entry's OnCycle routine
        ; to a function within the same bank as
        ; the HDMA entry info.

      ; Created: 0.22
      ; Updated: 0.22
      rsHDMACodeJump :?= address($82A5FF)
        ; Jumps to an address.

      ; Created: 0.22
      ; Updated: 0.22
      rsHDMACodeSetTimer :?= address($82A604)
        ; Sets an HDMA entry's aTimer.

      ; Created: 0.22
      ; Updated: 0.22
      rsHDMACodeJumpWhileTimer :?= address($82A60D)
        ; Decrements an HDMA entry's aTimer
        ; and jumps to an address if the timer is still
        ; nonzero afterwards.

      ; Created: 0.22
      ; Updated: 0.22
      rsHDMACodeJumpIfBitsUnset :?= address($82A615)
        ; Jumps to an address if the specified
        ; bits in the HDMA entry's aBitfield
        ; are not set.

      ; Created: 0.22
      ; Updated: 0.22
      rsHDMACodeJumpIfBitsSet :?= address($82A622)
        ; Jumps to an address if the specified
        ; bits in the HDMA entry's aBitfield
        ; are set.

      ; Created: 0.22
      ; Updated: 0.22
      rsHDMACodeSetTableBank :?= address($82A62F)
        ; Sets the bank byte of the HDMA entry's indirect table.

  .endweak

.endif ; GUARD_VOLTEDGE_HDMA_VALUES
