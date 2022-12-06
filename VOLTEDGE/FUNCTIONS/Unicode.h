
GUARD_VOLTEDGE_FUNCTIONS_UNICODE :?= false
.if (!GUARD_VOLTEDGE_FUNCTIONS_UNICODE)
  GUARD_VOLTEDGE_FUNCTIONS_UNICODE := true

  VoltEdge_Functions_Unicode_Created = 0.23
  VoltEdge_Functions_Unicode_Updated = 0.23

  ; These functions are for working with UTF-8 encoded text.
  ; TODO: There's a lot that needs to be done here, like:
  ;   64tass string -> encoded UTF-8
  ;   better errors
  ;   better validation
  ;   surrogate replacement?

  utf8 .namespace

    ; Internal helper functions

      ; Created: 0.22
      ; Updated: 0.22
      ; _get_byte_count(Value, Shift=0)

        ; Inputs:
          ; Value: An 8-bit number that begins a multibyte UTF-8 character
          ; Shift: A running value representing how many bits into the
            ; Value we are.

        ; Outputs:
          ; The number of bytes that make up the multibyte character

        ; This function gets the number of bytes in a multibyte character.

        _get_byte_count .function Value, Shift=0

          ; I'd like to write this as
          ; _get_byte_count .sfunction Value, Shift=0, ((Value << Shift) & $80 == 0 ? Shift : utf8._get_byte_count(Value, Shift + 1))
          ; but 64tass evaluates both halves of the ... ? ... : ...
          ; and recurses infinitely.

          .if (((Value << Shift) & $80) == 0)

            Return := Shift

          .else

            Return := utf8._get_byte_count(Value, Shift + 1)

          .endif

        .endfunction Return

      ; Created: 0.22
      ; Updated: 0.22
      ; _is_continuation(Value)

        ; Inputs:
          ; Value: An 8-bit number that might be part of a multiyte character

        ; Outputs:
          ; true if part of a multibyte character else false

        _is_continuation .sfunction Value, ((Value & $C0) == $80)

    ; Public values

      ; Created: 0.22
      ; Updated: 0.22
      ; Control code translation dictionary

        ; Note: this requires the "none" encoding to be used and the `-a` flag
        ; passed when running 64tass.

        ; If you try to slice/index a string containing raw control codes,
        ; like <0A> (newline) or <0D> (carriage return), 64tass will error
        ; about being unable to encode them in the "none" encoding. This
        ; dictionary maps those unencodable raw values into 64tass' builtin
        ; escape sequences for them.

        .enc "none"

        ControlTranslations = {x"09": "{tab}", x"0A": "{lf}", x"0D": "{cr}"}

    ; Public functions

      ; Created: 0.22
      ; Updated: 0.22
      ; decode(Filename, TranslateControls=false)

        ; Inputs:
          ; Filename: file to decode
          ; TranslateControls: Flag whether control codes like <0A> (newline)
            ; should be translated into 64tass' "none" encoding equivalents,
            ; i.e. "{lf}". This will allow strings with these characters
            ; to be worked with more easily but may cause problems due to
            ; their different lexigraphical length.

        ; Outputs:
          ; a 64tass string

        ; Decodes a UTF-8 encoded file
        ; into a 64tass string. Throws a very basic error if
        ; the data passed happens to have invalid characters, so
        ; it's up to the user to ensure that their text is valid.

        ; For example:
        ; utf8.decode("foo.txt")

        decode .sfunction Filename: binary, TranslateControls=false, decode_bytestring(Filename, TranslateControls)

      ; Created: 0.22
      ; Updated: 0.22
      ; decode_bytestring(ByteString, TranslateControls=false)

        ; Inputs:
          ; ByteString: data to decode in the form of a byte string
          ; TranslateControls: Flag whether control codes like <0A> (newline)
            ; should be translated into 64tass' "none" encoding equivalents,
            ; i.e. "{lf}". This will allow strings with these characters
            ; to be worked with more easily but may cause problems due to
            ; their different lexigraphical length.

        ; Outputs:
          ; a 64tass string

        ; Decodes a UTF-8 byte string (from something like binary() or x"")
        ; into a 64tass string. Throws a very basic error if
        ; the data passed happens to have invalid characters, so
        ; it's up to the user to ensure that their text is valid.

        ; For example:
        ; utf8.decode_bytestring(x"E79BB4") -> "直"
        ; utf8.decode_bytestring(binary("foo.txt"))

        decode_bytestring .function ByteString, TranslateControls=false

          .cerror !validate(ByteString), "Cannot decode, data malformed."

          Return   := ""
          Position := 0

          .while (Position < len(ByteString))

            New := decode_char(ByteString, Position, TranslateControls)

            Return   ..= iter.fst(New)
            Position  += iter.snd(New)

          .endwhile

        .endfunction Return

      ; Created: 0.22
      ; Updated: 0.22
      ; decode_char(ByteString, Position=0, TranslateControls=false)

        ; Inputs:
          ; ByteString: data to decode in the form of a byte string
          ; Position: The current position to decode a character
            ; from the ByteString at.
          ; TranslateControls: Flag whether control codes like <0A> (newline)
            ; should be translated into 64tass' "none" encoding equivalents,
            ; i.e. "{lf}". This will allow strings with these characters
            ; to be worked with more easily but may cause problems due to
            ; their different lexigraphical length.

        ; Outputs:
          ; A tuple containing the character as a string and
            ; a number for how many bytes the character took up.

        ; This is mostly an internal function for decode()
        ; but may be useful outside of it.

        ; This function decodes a single UTF-8 character from
        ; a byte string.

        decode_char .function ByteString, Position=0, TranslateControls=false

          .enc "none"

          ; This is mostly for if this is called on its own.

          .cerror (len(ByteString[Position:]) == 0), "Cannot decode empty data."

          StartByte := ByteString[Position]

          .if (StartByte < $80)

            ; Single byte, ASCII

            Accumulator  := StartByte
            Displacement := 1

            .if (TranslateControls && (Accumulator in utf8.ControlTranslations))

              Return := utf8.ControlTranslations[Accumulator]

            .else

              Return := format("%c", Accumulator)

            .endif

          .else

            ; Multibyte

            Displacement := utf8._get_byte_count(StartByte)

            .if (len(ByteString[Position:]) < Displacement)

              Missing := (Displacement - len(ByteString[Position:]))
              Error   := format("Unable to decode multibyte sequence at $%02X, got %d/%d bytes.", Position, Missing, Displacement)
              .error Error

            .endif

            Accumulator := StartByte & ($7F >> Displacement)

            .for i = 1, i < Displacement, i += 1

              Accumulator := (Accumulator << 6) | (ByteString[Position + i] & $7F)

            .endfor

            Return := format("%c", Accumulator)

          .endif

        .endfunction (Return, Displacement)

      ; Created: 0.22
      ; Updated: 0.22
      ; validate(ByteString)

        ; Inputs:
          ; ByteString: data to check in the form of a byte string

        ; Outputs:
          ; true if data is entirely valid UTF-8 characters else false

        ; This function checks if a byte string contains only
        ; nonbroken UTF-8 characters, although this really only
        ; means that it ensures that multibyte sequences follow
        ; the expected scheme.

        validate .function ByteString

          Return   := true
          Position := 0

          .while ((Position < len(ByteString)) && (Return === true))

            New := validate_char(ByteString, Position)

            Return   := iter.fst(New)
            Position += iter.snd(New)

          .endwhile

        .endfunction Return

      ; Created: 0.22
      ; Updated: 0.22
      ; validate_char(ByteString, Position=0)

        ; Inputs:
          ; ByteString: data to check in the form of a byte string
          ; Position: The current position to check a character
            ; from the ByteString at.

        ; Outputs:
          ; A tuple containing whether the character was valid and
            ; a number for how many bytes the character took up.

        ; This is mostly an internal function for validate()
        ; but may be useful outside of it.

        ; This function checks a single UTF-8 character from
        ; a byte string. An invalid character's size should be ignored.

        validate_char .function ByteString, Position=0

          ; This is mostly for if this is called on its own.

          .cerror (len(ByteString[Position:]) == 0), "Cannot validate empty data."

          Return := false
          Size   := 0

          StartByte := ByteString[Position]

          .if (StartByte < $80)

            ; Single byte, ASCII
            ; These are always valid.

            Return := true
            Size   := 1

          .else

            ; Multibyte

            Size := utf8._get_byte_count(StartByte)

            .if (len(ByteString[Position:]) < Size)

              ; Incomplete sequence

              Return := false

            .else

              Return := all(utf8._is_continuation(ByteString[Position+1:Position+Size]))

            .endif

          .endif

        .endfunction (Return, Size)

  .endnamespace ; utf8

.endif ; GUARD_VOLTEDGE_FUNCTIONS_UNICODE
