
GUARD_VOLTEDGE_EVENTS_ENDCODES :?= false
.if (!GUARD_VOLTEDGE_EVENTS_ENDCODES)
  GUARD_VOLTEDGE_EVENTS_ENDCODES := true

  VoltEdge_Events_EndCodes_Created = 0.03
  VoltEdge_Events_EndCodes_Updated = 0.03

  ; For event definition arrays and
  ; their individual event definitions.

    ; Created: 0.03
    ; Updated: 0.03
    END_DEFINITION .segment
      ; Ends an event condition definition.
      .char -1
    .endm

    ; Created: 0.03
    ; Updated: 0.03
    END_DEFINITION_ARRAY .segment
      ; Ends an event condition definition array.
      .sint -1
    .endm

  ; For events. The precise differences between
  ; each is unknown. Until these codes have better
  ; names and their uses are understood, each will list
  ; their vanilla uses.

    ; Created: 0.03
    ; Updated: 0.03
    END1 .segment
      ; Ends an event.
      ; Vanilla examples:
      ;   Chapter endings
      ;   World Map endings
      ;   Tile changes without dialogue
      ;   NPC retreat
      ;   AI/Leader changes
      ;   Checks for characters
      ;   Lara's talk with Pan and reclassing
      ;   Player loss
      ;   Counter modification
      ;   Mareeta's talk before gaining Astra
      ;   Linoan's promotion
      ;   Opening a randomized chest
      ;   End of the title screen demo
      ;   End of the quote handlers
      .char -1
    .endm

    ; Created: 0.03
    ; Updated: 0.03
    END2 .segment
      ; Ends an event.
      ; This is the most common end code.
      ; Vanilla examples:
      ;   Most things with dialogue
      ;   Unit loading
      ;   Events tied to chests
      ;   Some AI changes?
      ;   Player retreat
      ;   Sarah warping around in chapter 16B
      ;   Picking up hidden items
      ;   Stealth check in chapter 4
      .char -2
    .endm

    ; Created: 0.03
    ; Updated: 0.03
    END3 .segment
      ; Ends an event.
      ; Used to end chapter 1's opening.
      .char -3
    .endm

.endif ; GUARD_VOLTEDGE_EVENTS_ENDCODES
