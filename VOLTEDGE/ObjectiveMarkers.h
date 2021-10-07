
GUARD_VOLTEDGE_OBJECTIVE_MARKERS :?= false
.if (!GUARD_VOLTEDGE_OBJECTIVE_MARKERS)
  GUARD_VOLTEDGE_OBJECTIVE_MARKERS := true

  VoltEdge_OBJECTIVE_MARKERS_Created = 0.17
  VoltEdge_OBJECTIVE_MARKERS_Updated = 0.17

  ; Created: 0.17
  ; Updated: 0.17
  ; Objective marker constants

    ObjectiveMarkerLeft  = 0
    ObjectiveMarkerRight = 2
    ObjectiveMarkerUp    = 4
    ObjectiveMarkerDown  = 6

    ObjectiveMarkerRed     = 1
    ObjectiveMarkerBlue    = 2
    ObjectiveMarkerUnknown = 3

  ; Objective marker helpers

    ; Created: 0.17
    ; Updated: 0.17
    structObjectiveMarkerEntryRAM .struct
      X      .word ?
      Y      .word ?
      Sprite .word ?
      Tile   .word ?
    .endstruct

    ; Created: 0.17
    ; Updated: 0.17
    structObjectiveMarkerEntry .struct Coordinates, Sprite
      .if type(\Coordinates) == type(?)
        .byte ?, ?
      .else
        .byte \Coordinates[0], \Coordinates[1]
      .endif
      .byte \Sprite
    .endstruct

    ; Created: 0.17
    ; Updated: 0.17
    structObjectiveMarkerArray .struct Color, EntryList
      .byte \Color
      .if type(\EntryList) != type(?)
        .for i in range(len(\EntryList))
          .dstruct structObjectiveMarkerEntry, \EntryList[i][0], \EntryList[i][1]
        .endfor
      .endif
      .byte 0
    .endstruct

.endif ; GUARD_VOLTEDGE_OBJECTIVE_MARKERS
