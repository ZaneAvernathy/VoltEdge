
GUARD_VOLTEDGE_PROCS_VALUES :?= false
.if (!GUARD_VOLTEDGE_PROCS_VALUES)
  GUARD_VOLTEDGE_PROCS_VALUES := true

  VoltEdge_Procs_Values_Created = 0.22
  VoltEdge_Procs_Values_Updated = 0.22

  .weak

    ; These are useful vanilla proc system functions.

      ; Created: 0.14
      ; Updated: 0.22
      rlProcEngineCreateProc :?= address($829BF1)
        ; Inputs:
        ;   lR44: long pointer to proc info
        ; Outputs:
        ;   Carry clear if successful,
        ;     set otherwise.
        ; Creates the specified proc.

      ; Created: 0.22
      ; Updated: 0.22
      rlProcEngineCreateProcByOffset :?= address($829C99)
        ; Inputs:
        ;   A: offset into aProcSystem
        ;   lR44: long pointer to proc info
        ; Outputs:
        ;   Carry clear if successful,
        ;     set otherwise.
        ; Creates the specified proc in the specified
        ; slot. Fails if there is already a proc in the slot.

      ; Created: 0.22
      ; Updated: 0.22
      rlProcEngineFreeProcByOffset :?= address($829CB8)
        ; Inputs:
        ;   A: offset into aProcSystem
        ; Outputs:
        ;   Carry clear if successful,
        ;     set otherwise.
        ; Disables the proc in the specified slot. Returns
        ; carry set if there wasn't a proc in the slot.

      ; Created: 0.22
      ; Updated: 0.22
      rlProcEngineFindProc :?= address($829CEC)
        ; Inputs:
        ;   lR44: long pointer to proc info
        ; Outputs:
        ;   X: offset of proc in aProcSystem if found
        ;   Carry set if the proc is found,
        ;     clear otherwise.
        ; Checks if a specific proc exists in aProcSystem
        ; and returns its offset if it does.

      ; Created: 0.22
      ; Updated: 0.22
      rlProcEngineFreeProc :?= address($829D11)
        ; Inputs:
        ;   X: offset into aProcSystem
        ; Disables the proc in the specified slot.

      ; Created: 0.14
      ; Updated: 0.22
      rlEventEngineCreateProcAndSetActive :?= address($8C83E7)
        ; Inputs:
        ;   lR44: long pointer to proc info
        ; Creates the specified proc and flags
        ; the proc system as active within the
        ; event engine if the screen is not in
        ; forced blank. Called within events.

    ; These are usesful vanilla procs.

      ; Created: 0.14
      ; Updated: 0.22
      procChapterTitle :?= address($9A814C)
        ; Inputs:
        ;   aProcSystem.wInput1: long pointer to chapter title dialogue
        ; Creates the chapter title popup
        ; seen at the start of chapter events.

    ; These are internal proc system functions that
    ; are used by proc code.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeEnd :?= address($829DB7)
        ; Ends a proc code routine and stops
        ; the proc's code from being executed
        ; every cycle.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeHaltSleep :?= address($829DC5)
        ; Causes proc code execution to stall until
        ; something else changes the proc's code
        ; offset. This variant also sets the proc's
        ; aHeaderSleepTimer to 1, causing code execution
        ; to pause for a cycle.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeHalt :?= address($829DCB)
        ; Causes proc code execution to stall until
        ; something else changes the proc's code
        ; offset.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeCall :?= address($829DD3)
        ; Calls a native assembly function.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeCallWithArgs :?= address($829DEE)
        ; Calls a native assembly function with
        ; a variable number of arguments.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeSetOnCycle :?= address($829E19)
        ; Sets the proc's OnCycle routine
        ; to a function within the same bank as the
        ; proc info.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeJump :?= address($829E2B)
        ; Jumps to an address.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeSetUnknownTimer :?= address($829E30)
        ; Sets a proc's aHeaderUnknownTimer.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeJumpWhileUnknownTimer :?= address($829E39)
        ; Decrements a proc's aHeaderUnknownTimer
        ; and jumps to an address if the timer is still
        ; nonzero afterwards.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeJumpIfBitsUnset :?= address($829E41)
        ; Jumps to an address if the specified
        ; bits in the proc's aHeaderBitfield
        ; are not set.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeJumpIfBitsSet :?= address($829E4E)
        ; Jumps to an address if the specified
        ; bits in the proc's aHeaderBitfield
        ; are set.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeJumpIfRoutineTrue :?= address($829E77)
        ; Jumps to an address if a called routine
        ; returns carry set.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeJumpIfRoutineFalse :?= address($829E9B)
        ; Jumps to an address if a called routine
        ; returns carry clear.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeCreateProc :?= address($829EBF)
        ; Creates a proc.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeFreeProc :?= address($829ED5)
        ; Frees a proc.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeDeleteHDMAArrayEntry :?= address($829EF1)
        ; Deletes an HDMA array entry.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeHaltWhile :?= address($829F0D)
        ; Causes proc code execution to stall
        ; while a specified proc is active.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeCreateHDMAArrayEntry :?= address($829F33)
        ; Creates an HDMA array entry.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeHaltWhileActiveSprite :?= address($829F49)
        ; Causes proc code execution to stall
        ; while a specified active sprite is active.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodePlaySoundEffect :?= address($829F6F)
        ; Plays a sound effect.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodePlayExtendedSoundEffect :?= address($829F7D)
        ; Plays an extended sound effect.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodePlaySoundEffectPannedByCoordinates :?= address($829F8B)
        ; Plays a sound effect, panned
        ; to match the horizontal position
        ; of some coordinates.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodePlayExtendedSoundEffectPannedByCoordinates :?= address($829FAF)
        ; Plays an extended sound effect, panned
        ; to match the horizontal position
        ; of some coordinates.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodePlaySoundEffectPannedByRoutine :?= address($829FD3)
        ; Plays a sound effect, panned
        ; to match the horizontal position
        ; determined by some routine,

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodePlayExtendedSoundEffectPannedByRoutine :?= address($829FFB)
        ; Plays an extended sound effect, panned
        ; to match the horizontal position
        ; determined by some routine.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodePlaySong :?= address($82A023)
        ; Plays a specified song.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeHaltUntilSongPlaying :?= address($82A02C)
        ; Causes proc code execution to stall
        ; until the current requested song is playing.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeSongFadeOut :?= address($82A040)
        ; Fades out music into silence with
        ; a given speed.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeHaltWhileDecompressing :?= address($82A04A)
        ; Causes proc code execution to stall
        ; while bDecompressionArrayFlag is nonzero.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeBranchAndLink :?= address($82A05E)
        ; Jumps to an address and sets the
        ; proc's name to be a return address.
        ; Called proc code should end with
        ; rsProcCodeReturn.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeReturn :?= address($82A06B)
        ; Returns proc code execution to the address
        ; stored in the proc's name field.
        ; Used with proc code called with
        ; rsProcCodeBranchAndLink.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeHaltUntilButtonsNewPressed :?= address($82A070)
        ; Causes proc code execution to stall
        ; until the specified buttons are pressed
        ; at the same time.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeHaltUntilButtonsNewPressedOrTime :?= address($82A09A)
        ; Causes proc code execution to stall
        ; until the specified buttons are pressed
        ; at the same time or until the proc's
        ; aHeaderUnknownTimer ticks down to zero.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeJumpIfButtons :?= address($82A0B9)
        ; Jumps to an address if the specified buttons
        ; are pressed at the same time.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeDecompress :?= address($82A0CA)
        ; Decompresses something to some
        ; location.

      ; Created: 0.22
      ; Updated: 0.22
      rsProcCodeDMA :?= address($82A0ED)
        ; DMAs something to VRAM.

  .endweak

.endif ; GUARD_VOLTEDGE_PROCS_VALUES
