
GUARD_VOLTEDGE_STATUSES :?= false
.if (!GUARD_VOLTEDGE_STATUSES)
  GUARD_VOLTEDGE_STATUSES := true

  VoltEdge_Statuses_Created = 0.01
  VoltEdge_Statuses_Updated = 0.02

  ; Created: 0.01
  ; Updated: 0.01
  ; Status constants

    StatusSleep   = bits($01)
    StatusBerserk = bits($02)
    StatusPoison  = bits($03)
    StatusSilence = bits($04)
    StatusPetrify = bits($05)

  ; Created: 0.01
  ; Updated: 0.01
  ; Unit state constants

    UnitStateDead         = bits($0001)
    UnitStateMapAnim      = bits($0002)
    UnitStateUnknown1     = bits($0004)
    UnitStateUnselectable = bits($0008)
    UnitStateRescued      = bits($0010)
    UnitStateRescuing     = bits($0020)
    UnitStateActing       = bits($0040)
    UnitStateGrayed       = bits($0080)
    UnitStateMovementStar = bits($0100)
    UnitStateMoved        = bits($0200)
    UnitStateInvisible    = bits($0400)
    UnitStateCaptured     = bits($0800)
    UnitStateUnknown2     = bits($1000)
    UnitStateUnknown3     = bits($2000)
    UnitStateUnknown4     = bits($4000)
    UnitStateUnknown5     = bits($8000)

.endif ; GUARD_VOLTEDGE_STATUSES
