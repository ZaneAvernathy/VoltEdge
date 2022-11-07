
GUARD_VOLTEDGE_HDMA :?= false
.if (!GUARD_VOLTEDGE_HDMA)
  GUARD_VOLTEDGE_HDMA := true

  VoltEdge_HDMA_Created = 0.22
  VoltEdge_HDMA_Updated = 0.22

  .include "HDMA/Values.h"
  .include "HDMA/Helpers.h"

.endif ; GUARD_VOLTEDGE_HDMA
