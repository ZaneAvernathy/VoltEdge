
GUARD_VOLTEDGE_FUNCTIONS :?= false
.if (!GUARD_VOLTEDGE_FUNCTIONS)
  GUARD_VOLTEDGE_FUNCTIONS := true

  VoltEdge_Functions_Created = 0.19
  VoltEdge_Functions_Updated = 0.23

  ; These library functions are intended to help with
  ; assembly-time things. They mimic similarly-named
  ; functions in higher-level languages like Python.

  ; Most are namespaced and must be accessed using the dot notation
  ; to avoid redefinition problems.

  .include "FUNCTIONS/General.h"
  .include "FUNCTIONS/Numbers.h"
  .include "FUNCTIONS/Operators.h"
  .include "FUNCTIONS/Strings.h"
  .include "FUNCTIONS/Iterables.h"
  .include "FUNCTIONS/Enumerations.h"

  .if (USE_UTF8)

    .include "FUNCTIONS/Unicode.h"
    .include "FUNCTIONS/CSV.h"

  .endif ; USE_UTF8

.endif ; GUARD_VOLTEDGE_FUNCTIONS
