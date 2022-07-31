
GUARD_VOLTEDGE_PROCS :?= false
.if (!GUARD_VOLTEDGE_PROCS)
  GUARD_VOLTEDGE_PROCS := true

  VoltEdge_Procs_Created = 0.01
  VoltEdge_Procs_Updated = 0.21

  ; Useful vanilla proc routines

    .weak

      ; Created: 0.14
      ; Updated: 0.14
      rlProcEngineCreateProc :?= address($829BF1)
        ; Inputs:
        ;   lR44: long pointer to proc info
        ; Outputs:
        ;   Carry clear if successful,
        ;     set otherwise.
        ; Creates the specified proc.

      ; Created: 0.14
      ; Updated: 0.14
      rlEventEngineCreateProcAndSetActive :?= address($8C83E7)
        ; Inputs:
        ;   lR44: long pointer to proc info
        ; Creates the specified proc and flags
        ; the proc system as active within the
        ; event engine if the screen is not in
        ; forced blank. Called within events.

    .endweak

  ; Useful vanilla procs

    .weak

      ; Created: 0.14
      ; Updated: 0.21
      procChapterTitle :?= address($9A814C)
        ; Inputs:
        ;   aProcSystem.wInput1: long pointer to chapter title dialogue
        ; Creates the chapter title popup
        ; seen at the start of chapter events.

    .endweak

  ; Proc helpers

    ; Created: 0.01
    ; Updated: 0.21
    structProcInfo .struct Name, Init, OnCycle, Code
      Name
      .union
        .word $0000
        .enc "proc"
          .cdef " ~", 32
        .text \Name
      .endunion
      Init    .word <>\Init
      OnCycle .word <>\OnCycle
      Code    .word <>\Code
    .endstruct

.endif ; GUARD_VOLTEDGE_PROCS
