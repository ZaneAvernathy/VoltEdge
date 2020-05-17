
GUARD_VOLTEDGE_LIBRARY_HELPERS :?= false
.if (!GUARD_VOLTEDGE_LIBRARY_HELPERS)
  GUARD_VOLTEDGE_LIBRARY_HELPERS := true

  VoltEdge_LibraryHelpers_Created = 0.01
  VoltEdge_LibraryHelpers_Updated = 0.02

  ; Library helper values

    .weak

      ; Created: 0.01
      ; Updated: 0.01
      ; WARNINGS

        ; This library uses this WARNINGS
        ; variable to enable library-specific
        ; warnings. Recognized values are:

        ; "None" - no warnings
        ; "Strict" - all warnings

        WARNINGS :?= "None"

      ; Created: 0.01
      ; Updated: 0.01
      ; None

        ; Sometimes it makes more sense
        ; to mark a value as "None" rather
        ; than zero.

        None = 0

      ; Helper values for size()

        ; Normally, size(byte), size(word), etc.
        ; give an error. These values are included
        ; here because it may be more clear to use
        ; something like "size(long)" than just "3".

        ; Created: 0.01
        ; Updated: 0.01
        byte .struct Value
          .byte \Value
        .ends

        ; Created: 0.01
        ; Updated: 0.01
        char .struct Value
          .char \Value
        .ends

        ; Created: 0.01
        ; Updated: 0.01
        word .struct Value
          .word \Value
        .ends

        ; Created: 0.01
        ; Updated: 0.01
        sint .struct Value
          .sint \Value
        .ends

        ; Created: 0.01
        ; Updated: 0.01
        addr .struct Value
          .addr \Value
        .ends

        ; Created: 0.01
        ; Updated: 0.01
        rta .struct Value
          .rta \Value
        .ends

        ; Created: 0.01
        ; Updated: 0.01
        long .struct Value
          .long \Value
        .ends

        ; Created: 0.01
        ; Updated: 0.01
        lint .struct Value
          .lint \Value
        .ends

        ; Created: 0.01
        ; Updated: 0.01
        dword .struct Value
          .dword \Value
        .ends

        ; Created: 0.01
        ; Updated: 0.01
        dint .struct Value
          .dint \Value
        .ends

        ; Although it seems unlikely that
        ; you'll ever need an 8-byte value,
        ; here is an unsigned and signed macro.

        ; Created: 0.01
        ; Updated: 0.01
        qword .struct Value
          .dword (narrow(\Value, size(dword))), (\Value >> (size(dword) * 8))
        .ends

        ; Created: 0.01
        ; Updated: 0.01
        qint .struct Value
          .dword (narrow(\Value, size(dint)))
          .dint (\Value >> (size(dint) * 8))
        .ends

      ; Created: 0.01
      ; Updated: 0.01
      ; Allegiances

        Player = $00
        Enemy  = $40
        NPC    = $80

        AllAllegiances = Player | Enemy | NPC

    .endweak

  ; Library helper macros

    ; Created: 0.01
    ; Updated: 0.01
    ; .warnhere

      ; Inputs:
        ; None

      ; Outputs:
        ; None

      ; Shorthand for throwing a
      ; warning with the current offset.
      ; Useful for debugging.

      warnhere .macro
        .warn format("$%06X", *)
      .endm

    ; Created: 0.01
    ; Updated: 0.01
    ; .checkfit Offset

      ; Inputs:
        ; Offset: offset of first byte of illegal space

      ; Outputs:
        ; Error if assembly offset enters illegal space
        ; Error contains assembly offset.

      ; Given some offset, throw an error if assembly
      ; passes that point. This is useful for
      ; inlined replacement code that needs
      ; to fit in a previously-occupied area.

      checkfit .macro Offset
        .cerror (* > \Offset), format("$%06X", *)
      .endm

    ; Created: 0.01
    ; Updated: 0.01
    ; mapped(Offset)

      ; Inputs:
        ; Offset: some offset to map

      ; Outputs:
        ; Memory-mapped pointer

      ; Given a raw offset to some point
      ; in the ROM image, return a pointer
      ; to it in the SNES (currently LoROM only)
      ; memory map.

      mapped .function Offset
        Return := ((Offset >> 15) << 16) | (Offset & $7FFF) | $8000
        .if ((Offset >= $7E0000) || (Offset < $400000))
          Return |= $800000
        .endif
      .endf address(Return)

    ; Created: 0.01
    ; Updated: 0.01
    ; narrow(Value, Length)

      ; Inputs:
        ; Value: Value to reduce in byte width
        ; Length: Target number of bytes

      ; Outputs:
        ; Byte-narrowed number

      ; Given some Value, binary AND it
      ; to strip it down to Length bytes long.
      ; To strip down to a specific number of bits,
      ; use narrowbits.

      ; Example:
      ; narrow($1234, 1) == $34

      narrow .function Value, Length
      .endf ((x"ff" x Length) & Value)

    ; Created: 0.01
    ; Updated: 0.01
    ; narrowbits(Value, Length)

      ; Inputs:
        ; Value: Value to reduce in bit width
        ; Length: Target number of bits

      ; Outputs:
        ; Bit-narrowed number

      ; Given some Value, binary AND it
      ; to strip it down to Length bits long.
      ; To strip down to a specific number of bytes,
      ; use narrow.

      ; Example:
      ; narrowbits(%10101, 3) = %101

      narrowbits .function Value, Length
      .endf bits((%1 x Length) & Value)

    ; Created: 0.01
    ; Updated: 0.01
    ; .crossbank "Filename"

      ; Inputs:
        ; Filename: binary file to include

      ; Outputs:
        ; .binary of Filename up to bank boundary
        ; Remaining length of bytes in -

      ; Given a Filename, binary include its data
      ; until a bank boundary is reached. If no
      ; boundary is reached, include the whole file.
      ; If a boundary is reached, store the length
      ; of the remaining bytes in the local label -
      ; This is useful for including compressed files,
      ; which may cross banks in vanilla FE5.

      ; Example:

      ; * := $007FF0
      ; .logical mapped($007FF0)
      ;
      ;   ; Include the first $10 bytes of a file.
      ;
      ;   g4bppcTestGraphics .crossbank "Test.4bpp.comp"
      ;
      ; .here
      ;
      ; * := $008000
      ; .logical mapped($008000)
      ;
      ;   ; Include the rest of it.
      ;
      ;   .binary "Test.4bpp.comp", -
      ;
      ; .here

      crossbank .segment Filename
        - := $10000 - (* & $FFFF)
        .binary \Filename, 0, -
      .endm

    ; Created: 0.01
    ; Updated: 0.01
    ; pack(Iterable, Width=2)

      ; Inputs:
        ; Iterable: A list or tuple of numbers
        ; Width: The intended size in bytes to pack each pair into

      ; Outputs:
        ; A list of packed values

      ; Given some Iterable of numbers,
      ; group them into pairs. If the size
      ; of the Iterable is uneven it is extended
      ; with a 0. These pairs are packed
      ; into numbers such that the first
      ; number in the pair occupies the lower
      ; half of the new number and the second
      ; number occupies the upper half of the
      ; new number. The Width parameter specifies
      ; the intended size of the output pairs.

      ; This is useful for packing coordinates
      ; into bytes or words.

      ; Example:

      ; .word pack([0, 1, 2, 3])

      ; is equivalent to

      ; .word [$0100, $0302] ; 00 01 02 03

      ; and

      ; .byte pack((1, 15, 3), 1)

      ; is equivalent to

      ; .byte ((15 << 4) | 1, 3)
      ; or
      ; .byte ($F1, $03)

      ; Notice that the numbers were packed into
      ; lo/hi nybbles rather than bytes.

      ; pack() can also be used to pack opcode parameters:

      ; lda #pack([8, 9]) ; equiv. to lda #$0908

      pack .function Iterable, Width=2
        Iterable := list(Iterable)
        .if ((len(Iterable) & 1) == 1)
          Iterable ..= [0]
        .endif
      .endf (Iterable[0::2] | (Iterable[1::2] << (4 * Width)))

.endif ; GUARD_VOLTEDGE_LIBRARY_HELPERS
