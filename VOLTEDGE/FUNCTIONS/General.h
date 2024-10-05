
GUARD_VOLTEDGE_FUNCTIONS_GENERAL :?= false
.if (!GUARD_VOLTEDGE_FUNCTIONS_GENERAL)
  GUARD_VOLTEDGE_FUNCTIONS_GENERAL := true

  VoltEdge_Functions_General_Created = 0.23
  VoltEdge_Functions_General_Updated = 0.23

  ; These are uncategorized functions.

  ; Created: 0.19
  ; Updated: 0.19
  ; print(*Things)

    ; Inputs:
      ; Any number of things

    ; Outputs:
      ; None

    ; This is just another way to use the .warn directive.

    print .function *Things
      .warn *Things
    .endfunction

  ; Bank boundary helpers

    ; These helpers are for crossing ROM bank
    ; boundaries when including compressed files.

    ; Example:

    ; * := $007FF0
    ; .logical mapped($007FF0)
    ;
    ;   ; Include the first $10 bytes of a file.
    ;
    ;   g4bppcTestGraphics .crossbank.start "TestFile.4bpp.comp"
    ;
    ; .endlogical
    ;
    ; * := $008000
    ; .logical mapped($008000)
    ;
    ;   ; Include the rest of it.
    ;
    ;   .crossbank.end
    ;
    ; .endlogical

    ; Created: 0.23
    ; Updated: 0.25

    crossbank .namespace

      Remainder := b""

      start .function Filename: binary, Address=None

        .if ( Address == None )
          Address := *
        .endif

        Remainder ::= Filename[$10000 - (Address & $FFFF):]
        .text Filename[:$10000 - (Address & $FFFF)]

      .endfunction

      end .segment

        .text crossbank.Remainder

      .endsegment

    .endnamespace ; crossbank

.endif ; GUARD_VOLTEDGE_FUNCTIONS_GENERAL
