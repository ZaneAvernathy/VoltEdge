
GUARD_VOLTEDGE_TILESET_ANIMATIONS :?= false
.if (!GUARD_VOLTEDGE_TILESET_ANIMATIONS)
  GUARD_VOLTEDGE_TILESET_ANIMATIONS := true

  VoltEdge_TILESET_ANIMATIONS_Created = 0.09
  VoltEdge_TILESET_ANIMATIONS_Updated = 0.09

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

    ; TSA_FRAME yourFirstGraphicsFrame0, 0, 1
    ; TSA_FRAME yourSecondGraphicsFrame0, 64, 11

    ; TSA_FRAME yourFirstGraphicsFrame1, 0, 1
    ; TSA_FRAME yourSecondGraphicsFrame1, 64, 11

    ; etc.

    ; Created: 0.09
    ; Updated: 0.09
    TSA_FRAME .segment GraphicsPointer, StartTile, Framecount
      .long \GraphicsPointer
      .word (\StartTile + 640) * size(Tile4bpp)
      .byte \Framecount
    .endsegment

    ; Created: 0.09
    ; Updated: 0.09
    TSA_END .segment
      .long 0
    .endsegment

.endif ; GUARD_VOLTEDGE_TILESET_ANIMATIONS
