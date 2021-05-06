
GUARD_VOLTEDGE_PROCS :?= false
.if (!GUARD_VOLTEDGE_PROCS)
  GUARD_VOLTEDGE_PROCS := true

  VoltEdge_Procs_Created = 0.01
  VoltEdge_Procs_Updated = 0.07

  ; Proc helpers

    ; Created: 0.01
    ; Updated: 0.07
    structProcInfo .struct Name, Init, OnCycle, Code
      Name
      .union
        .word $0000
        .enc "none"
        .text \Name
      .endunion
      Init    .word <>\Init
      OnCycle .word <>\OnCycle
      Code    .word <>\Code
    .endstruct

.endif ; GUARD_VOLTEDGE_PROCS
