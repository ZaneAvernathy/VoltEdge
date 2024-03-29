
GUARD_VOLTEDGE_VANILLA_CHAPTERS :?= false
.if (!GUARD_VOLTEDGE_VANILLA_CHAPTERS)
  GUARD_VOLTEDGE_VANILLA_CHAPTERS := true

  VoltEdge_Vanilla_Chapters_Created = 0.01
  VoltEdge_Vanilla_Chapters_Updated = 0.20

  ; This is a list of the chapters in
  ; vanilla FE5.

  ; As a disclaimer, the names of these
  ; values, which are just variables that
  ; make referring to these chapters easier,
  ; do not actually change any text that
  ; appears in game.

  ; Created: 0.01
  ; Updated: 0.20
  Chapter01       = $00
  Chapter02       = $01
  Chapter02x      = $02
  Chapter03       = $03
  Chapter04       = $04
  Chapter04x      = $05
  Chapter05       = $06
  Chapter06       = $07
  Chapter07       = $08
  Chapter08       = $09
  Chapter08x      = $0A
  Chapter09       = $0B
  Chapter10       = $0C
  Chapter11       = $0D
  Chapter11x      = $0E
  Chapter12       = $0F
  Chapter12x      = $10
  Chapter13       = $11
  Chapter14       = $12
  Chapter14x      = $13
  Chapter15       = $14
  Chapter16A      = $15
  Chapter17A      = $16
  Chapter16B      = $17
  Chapter17B      = $18
  Chapter18       = $19
  Chapter19       = $1A
  Chapter20       = $1B
  Chapter21       = $1C
  Chapter21x      = $1D
  Chapter22       = $1E
  Chapter23       = $1F
  Chapter24       = $20
  Chapter24x      = $21
  ChapterFinal    = $22
  ChapterUnknown  = $23
  ChapterWorldMap = $24

.endif ; GUARD_VOLTEDGE_VANILLA_CHAPTERS
