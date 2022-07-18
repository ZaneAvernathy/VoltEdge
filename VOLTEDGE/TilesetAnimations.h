
GUARD_VOLTEDGE_TILESET_ANIMATIONS :?= false
.if (!GUARD_VOLTEDGE_TILESET_ANIMATIONS)
  GUARD_VOLTEDGE_TILESET_ANIMATIONS := true

  VoltEdge_TILESET_ANIMATIONS_Created = 0.09
  VoltEdge_TILESET_ANIMATIONS_Updated = 0.21

  ; Tileset animation helpers

    ; Tileset animations are a list of
    ; TSA_FRAMEs terminated by a TSA_END.

    ; Each TSA_FRAME waits the specified
    ; number of frames before advancing to
    ; the next.

    ; Each 'frame' is a 64-tile snippet of
    ; tiles that are written to VRAM at the
    ; specified tile within the tileset image.

    ; Since the size is fixed, it's best to
    ; group your animated tiles together in
    ; your tileset graphics. If you need to
    ; copy more than one set of tiles per frame,
    ; set the framecounts of all but the
    ; last frame to 1, like:

    ; TSA_FRAME yourFirstGraphicsFrame0,   1, (0, 16)
    ; TSA_FRAME yourSecondGraphicsFrame0, 11, (0, 20)

    ; TSA_FRAME yourFirstGraphicsFrame1,   1, (0, 16)
    ; TSA_FRAME yourSecondGraphicsFrame1, 11, (0, 20)

    ; etc.

    ; Coordinates are from the start of the tileset graphics
    ; in VRAM.

    ; Created: 0.09
    ; Updated: 0.21
    TSA_FRAME .segment GraphicsPointer, Framecount, BaseCoordinates=()
      .long \GraphicsPointer
      .word TileToVRAM(C2I(\BaseCoordinates), VRAMToTile($5000, $0000))
      .byte \Framecount
    .endsegment

    ; Created: 0.09
    ; Updated: 0.09
    TSA_END .segment
      .long 0
    .endsegment

.endif ; GUARD_VOLTEDGE_TILESET_ANIMATIONS
