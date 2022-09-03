
GUARD_VOLTEDGE_PROCS :?= false
.if (!GUARD_VOLTEDGE_PROCS)
  GUARD_VOLTEDGE_PROCS := true

  VoltEdge_Procs_Created = 0.01
  VoltEdge_Procs_Updated = 0.22

  .include "PROCS/Values.h"
  .include "PROCS/Helpers.h"

.endif ; GUARD_VOLTEDGE_PROCS
