
GUARD_VOLTEDGE :?= false
.if (!GUARD_VOLTEDGE)
  GUARD_VOLTEDGE := true

  VoltEdge_Version = 0.13

  .weak

    ; You can select vanilla FE5 definitions
    ; to use by defining these as true when
    ; including the library. Additionally,
    ; you can define USE_FE5_DEFINITIONS as true to
    ; use all vanilla definitions.

    ; You can also set USE_FE5_DEFINITIONS to true
    ; and toggle individual settings to false.

    USE_FE5_DEFINITIONS :?= false

    .if (USE_FE5_DEFINITIONS)

      USE_FE5_CHARACTERS :?= true
      USE_FE5_CHAPTERS   :?= true
      USE_FE5_CLASSES    :?= true
      USE_FE5_FLAGS      :?= true
      USE_FE5_ITEMS      :?= true

    .else

      USE_FE5_CHARACTERS :?= false
      USE_FE5_CHAPTERS   :?= false
      USE_FE5_CLASSES    :?= false
      USE_FE5_FLAGS      :?= false
      USE_FE5_ITEMS      :?= false

    .endif ; USE_FE5_DEFINITIONS

  .endweak

  ; SNES/Hardware definitions

    .include "VOLTEDGE/IORegisters.h"

  ; Library helpers

    .include "VOLTEDGE/LibraryHelpers.h"

  ; Vanilla definitions

    .if (USE_FE5_CHARACTERS)

      .include "VOLTEDGE/VANILLA/Characters.h"

    .endif ; USE_FE5_CHARACTERS

    .if (USE_FE5_CHAPTERS)

      .include "VOLTEDGE/VANILLA/Chapters.h"

    .endif ; USE_FE5_CHAPTERS

    .if (USE_FE5_CLASSES)

      .include "VOLTEDGE/VANILLA/Classes.h"

    .endif ; USE_FE5_CLASSES

    .if (USE_FE5_ITEMS)

      .include "VOLTEDGE/VANILLA/Items.h"

    .endif ; USE_FE5_ITEMS

    .if (USE_FE5_FLAGS)

      .include "VOLTEDGE/VANILLA/PermanentFlags.h"

    .endif ; USE_FE5_FLAGS

  ; Library definitions

    .include "VOLTEDGE/Characters.h"
    .include "VOLTEDGE/ChapterData.h"
    .include "VOLTEDGE/Classes.h"
    .include "VOLTEDGE/DMA.h"
    .include "VOLTEDGE/Events.h"
    .include "VOLTEDGE/Items.h"
    .include "VOLTEDGE/Palettes.h"
    .include "VOLTEDGE/Procs.h"
    .include "VOLTEDGE/Quotes.h"
    .include "VOLTEDGE/Save.h"
    .include "VOLTEDGE/Skills.h"
    .include "VOLTEDGE/Sprites.h"
    .include "VOLTEDGE/Statuses.h"
    .include "VOLTEDGE/TemporaryFlags.h"
    .include "VOLTEDGE/Terrain.h"
    .include "VOLTEDGE/Tiles.h"
    .include "VOLTEDGE/TilesetAnimations.h"

    .include "VOLTEDGE/SRAM.h"
    .include "VOLTEDGE/WRAM.h"

.endif ; GUARD_VOLTEDGE
