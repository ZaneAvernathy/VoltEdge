
GUARD_VOLTEDGE_EVENTS :?= false
.if (!GUARD_VOLTEDGE_EVENTS)
  GUARD_VOLTEDGE_EVENTS := true

  VoltEdge_Events_Created = 0.03
  VoltEdge_Events_Updated = 0.03

  ; Raw event codes

    .include "EVENTS/Conditions.h"
    .include "EVENTS/EndCodes.h"
    .include "EVENTS/Helpers.h"
    .include "EVENTS/Main.h"
    .include "EVENTS/Values.h"

.endif ; GUARD_VOLTEDGE_EVENTS
