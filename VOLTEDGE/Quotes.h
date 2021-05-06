
GUARD_VOLTEDGE_QUOTES :?= false
.if (!GUARD_VOLTEDGE_QUOTES)
  GUARD_VOLTEDGE_QUOTES := true

  VoltEdge_Quotes_Created = 0.03
  VoltEdge_Quotes_Updated = 0.07

  ; Quote table constants

    ; Created: 0.03
    ; Updated: 0.03
    ChapterAny = -1

  ; Quote table helpers

    ; Created: 0.03
    ; Updated: 0.07
    structQuoteEntry .struct Character, Chapter, Flag, DialoguePointer
      Character .word \Character
      Chapter .char \Chapter
      Flag .byte \Flag
      DialoguePointer .long \DialoguePointer
    .endstruct

    ; Created: 0.03
    ; Updated: 0.07
    END_QUOTE_TABLE .segment
      .word 0
    .endsegment

.endif ; GUARD_VOLTEDGE_QUOTES
