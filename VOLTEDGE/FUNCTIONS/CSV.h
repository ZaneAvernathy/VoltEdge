
GUARD_VOLTEDGE_FUNCTIONS_CSV :?= false
.if (!GUARD_VOLTEDGE_FUNCTIONS_CSV)
  GUARD_VOLTEDGE_FUNCTIONS_CSV := true

  VoltEdge_Functions_CSV_Created = 0.23
  VoltEdge_Functions_CSV_Updated = 0.23

  ; These functions are for working with table files.

  csv .namespace

    ; Internal functions and helpers

      ; Created: 0.22
      ; Updated: 0.22
      ; _guess_type(Value)

        ; Inputs:
          ; Value: string

        ; Outputs:
          ; type of object that cell is most likely

        ; Guesses what type of 64tass object would best
        ; represent some Value.

        _guess_type .function Value

          ; Default to strings.

          GuessedType := str

          GuessedInt := zstr.to_int(Value)
          GuessedType := (GuessedInt === ?) ? GuessedType : int

        .endfunction GuessedType

    ; Public functions and helpers

      ; Public values

        ; Created: 0.22
        ; Updated: 0.22
        ; Line endings

          ; These are friendly names for the types
          ; of line endings recognized by the csv parser.

          .enc "none"

          Newline       = "{lf}"
          ReturnNewline = "{cr}{lf}"

      ; Public functions

        ; Created: 0.22
        ; Updated: 0.22
        ; parse(ByteString, Convert=true, Separator=?, LineEndings=?)

          ; Inputs:
            ; ByteString: A table in the form of a byte string,
              ; such as one given by binary() or x"".
            ; Convert: Enables or disables converting cell values
              ; into 64tass types. If false, all cells will be
              ; strings.
            ; Separator: If specified, this is a string that
              ; separates cells within the table.
            ; LineEndings: If specified, this is a string that
              ; separates lines within the table.

          ; Outputs:
            ; A list containing lists representing the
            ; rows for the table, with elements in those
            ; row lists eing the cells within the row.

          ; This function separates out a table (input as a string)
          ; into a list of values that can be used by 64tass.

          ; It attempts to parse cells that contain only numbers as
          ; numbers, otherwise the cell is treated as a string.

          ; Example usage:
          ; csv.parse(utf8.decode(binary("SomeFile.csv")))

          parse .function ByteString, Convert=true, Separator=?, LineEndings=?

            ; We originally pass the table in as a byte string
            ; despite needing it as a decoded UTF-8 string because
            ; 64tass will throw a fit if you try slicing/indexing a string
            ; that contains raw escape sequences.

            Raw := utf8.decode(ByteString, true)

            Processed := []

            ; Tables are required to end with a newline.
            ; If the `LineEndings` parameter wasn't specified,
            ; we'll use this to determine it.

            .if (LineEndings === ?)

              FoundEnding := ?

              .for Ending in sort([csv.Newline, csv.ReturnNewline])

                .if (zstr.endswith(Raw, Ending))

                  FoundEnding := Ending
                  .break

                .endif ; (zstr.endswith(Raw, Ending))

              .endfor

              .if (FoundEnding === ?)

                Error := format("Tables must end with a newline, got %s", Raw[-1])
                .error Error

              .endif

              LineEndings := FoundEnding

            .else ; (LineEndings === ?)

              .if !(zstr.endswith(Raw, LineEndings))

                Error := format("Table didn't end with expected line ending %s, got %s", LineEndings, Raw[-1])
                .error Error

              .endif ; (zstr.endswith(Raw, LineEndings))

            .endif ; (LineEndings === ?)

            ; Now that we know the line ending, try to figure out
            ; the cell separator, if not specified.

            Rows := zstr.split(Raw, LineEndings)[:-1]

            .if (Separator === ?)

              .if (len(Rows) == 0)

                .error "Cannot guess cell separator for an empty table."

              .endif

              PossibleSeparators := []

              ; We're going to score potential separators by
              ; trying to find the one with the most consistent
              ; number across the rows.

              ; I'll probably need to tweak this list sometime.

              .for Sepr in [",", "{tab}", ".", ";"]

                Counts := []
                .for Row in Rows

                  Counts ..= [zstr.count(Row, Sepr)]

                .endfor

                PossibleSeparators ..= [(Sepr, float(Counts + ...) / len(Counts))]

              .endfor

              .if !(any(bool(PossibleSeparators[:,1])))

                .error "Unable to determine table separator."

              .endif

              CurrentBest := PossibleSeparators[0]

              .for Sepr, Score in PossibleSeparators

                .if (frac(Score) < frac(iter.snd(CurrentBest)))

                  CurrentBest := (Sepr, Score)

                .endif

              .endfor

              Separator := iter.fst(CurrentBest)

            .endif

            ; Now that we know the separator, actually process the table.

            .for Row in Rows

              Temp := []

              .for Cell in zstr.split(Row, Separator)

                Value := Cell

                .if ((len(Cell) != 0) && Convert)

                  Cell := zstr.strip(Cell)

                  .switch csv._guess_type(Cell)

                    .case int

                      Value := zstr.to_int(Cell)

                  .endswitch

                .endif

                Temp ..= [Value]

              .endfor

              Processed ..= [Temp]

            .endfor

          .endfunction Processed

  .endnamespace ; csv

.endif ; GUARD_VOLTEDGE_FUNCTIONS_CSV
