
GUARD_VOLTEDGE_FUNCTIONS_STRINGS :?= false
.if (!GUARD_VOLTEDGE_FUNCTIONS_STRINGS)
  GUARD_VOLTEDGE_FUNCTIONS_STRINGS := true

  VoltEdge_Functions_Strings_Created = 0.23
  VoltEdge_Functions_Strings_Updated = 0.23

  ; These functions operate on strings. This is named `zstr`
  ; instead of `str` to avoid shadowing the builtin.

  zstr .namespace

    ; Created: 0.19
    ; Updated: 0.20
    ; center(String, Width, Fill=" ")

      ; Inputs:
        ; String: string to center
        ; Width: desired width in characters
        ; Fill: character to fill space width

      ; Outputs:
        ; A centered string

      ; Attempts to center a string within a given amount of space.
      ; Will return the string unchanged if it is longer than the given width.

      center .function String, Width, Fill=" "
        Return := String
        Len := len(String)
        .if (Len < Width)
          Pad := floor((float(Width) - Len) / 2)
          Left_Fill  := Fill x Pad
          Right_Fill := Fill x Pad
          Return := Left_Fill .. String .. Right_Fill
        .endif
      .endfunction Return

    ; Created: 0.19
    ; Updated: 0.19
    ; count(String, Substring, Start=0, Stop=?)

      ; Inputs:
        ; String: String to search
        ; Substring: String to look for within String
        ; Start: Optional starting index
        ; Stop: Optional stop index

      ; Outputs:
        ; Int count of times Substring was found in String[Start:Stop]

      ; Counts the number of times a substring is found within
      ; a string. Does not count overlapping substrings.

      count .function String, Substring, Start=0, Stop=?

        ; If Stop isn't given, set it to be the end of String.
        Stop := (Stop === ?) ? len(String) : Stop

        Count := 0
        Pos := Start

        ; Fetch the part of String that we're looking through.

        Region := String[Start:Stop]

        .while (Pos < len(Region))

          i := zstr.find(String, Substring, Pos, Stop)

          ; End early if we can't find any more occurences.
          .breakif (i == -1)

          Count += 1
          Pos += (i + len(Substring))
        .endwhile
      .endfunction Count

    ; Created: 0.19
    ; Updated: 0.19
    ; endswith(String, Suffix, Start=0, Stop=?)

      ; Inputs:
        ; String: String to search through
        ; Suffix: Suffix(es) to check for
        ; Start: Optional starting index
        ; Stop: Optional stop index

      ; Outputs:
        ; true if String[Start:Stop] ends with Suffix,
          ; false otherwise.

      ; Checks if a String ends with some Suffix, optionally
      ; only checking if a certain part of the String ends with it.

      ; Suffix can also be a list of strings to check for, instead of
      ; a single string.

      endswith .function String, Suffix, Start=0, Stop=?

        ; If Stop isn't given, set it to be the end of String.
        Stop := (Stop === ?) ? len(String) : Stop

        ; If we're looking for a single string, we need to wrap
        ; it into a list for the next step.

        .if (type(Suffix) != list)
          Suffix := [Suffix]
        .endif

        Return := false

        ; Fetch the part of String that we're looking through.

        Region := String[Start:Stop]

        .for Suf in Suffix

          ; We only care if the suffix isn't empty and that
          ; the suffix fits within the string.

          .if (len(Region) >= len(Suf)) && (len(Suf) != 0)

            .if (Region[-len(Suf):] == Suf)

              Return := true
              .break

            .endif
          .endif
        .endfor
      .endfunction Return

    ; Created: 0.19
    ; Updated: 0.19
    ; find(String, Substring, Start=0, Stop=?)

      ; Inputs:
        ; String: String to search through
        ; Substring: Substring to look for
        ; Start: Optional starting index
        ; Stop: Optional stop index

      ; Outputs:
        ; Index of found substring, -1 if not found.

      ; Checks for some Substring within a String. Returns
      ; the index of the first matching substring or -1 if
      ; the substring is not found.

      find .function String, Substring, Start=0, Stop=?

        ; If Stop isn't given, set it to be the end of String.
        Stop := (Stop === ?) ? len(String) : Stop

        ; Fetch the part of String that we're looking through.

        Region := String[Start:Stop]

        Len := len(Substring)

        Return := -1

        ; We can leverage the `in` operator to only
        ; do this step if we know that the Substring is in
        ; the Region.

        .if (Substring in Region)

          Pos := 0

          .while (Pos + Len) <= len(Region)

            .if (Region[Pos:Pos+Len] == Substring)

              Return := Pos
              .break

            .endif

            Pos += 1

          .endwhile
        .endif
      .endfunction Return

    ; Created: 0.19
    ; Updated: 0.19
    ; join(StringList, Separator="")

      ; Inputs:
        ; Stringlist: a list of strings to join
        ; Separator: the string that will go between the
          ; strings in Stringlist.

      ; Outputs:
        ; A new string

      ; Joins all of the strings in a list together into a
      ; single string, with Separator between each element.

      join .function StringList, Separator=""

        Return := ""

        ; We can return early if we have nothing to do.

        .if (len(StringList) != 0)

          ; By default, if we only have one string to join,
          ; we return that string.

          Return := StringList[0]

          .for String in StringList[1:]

            Return ..= Separator .. String

          .endfor
        .endif
      .endfunction Return

    ; Created: 0.19
    ; Updated: 0.19
    ; ljust(String, Width, Fill=" ")

      ; Inputs:
        ; String: string to pad
        ; Width: character width to pad to
        ; Fill: character to pad with

      ; Outputs:
        ; A new string

      ; Tries to left-justify a String within a given Width.
      ; If the string is longer than the given Width, returns the
      ; original string.

      ljust .sfunction String, Width, Fill=" ", (String .. (Fill x ((len(String) >= Width) ? 0 : Width - len(String))))

    ; Created: 0.19
    ; Updated: 0.19
    ; lstrip(String, StripChars=" ")

      ; Inputs:
        ; String: string to strip
        ; StripChars: combination of characters to strip

      ; Outputs:
        ; A new string

      ; Tries to strip any character(s) from the left side of
      ; a String that are found in StripChars. For example:

      ; zstr.lstrip("www.example.com", "cmowz.") = "example.com"

      ; It stops once it encounters a character not in StripChars.
      ; It defaults to removing spaces if StripChars is not specified.

      lstrip .function String, StripChars=" "
        .for Index, Character in iter.enumerate(String)
          .breakif !(Character in StripChars)
        .endfor
      .endfunction String[Index:]

    ; Created: 0.19
    ; Updated: 0.19
    ; partition(String, Separator)

      ; Inputs:
        ; String: string to split
        ; Separator: Separator to split string at

      ; Outputs:
        ; A 3-tuple containing:
          ; The part before the separator
          ; The separator
          ; The part after the separator

        ; If the separator isn't found, returns:
          ; The string itself
          ; An empty string
          ; An empty string

      ; Splits a String at the first occurance of some
      ; Separator and returns a 3-tuple of the result.

      partition .function String, Separator

        ; Set the default return value for if the Separator
        ; isn't found.

        ; The weird slicing here is so that the return values
        ; have the same type as the String, in case we passed
        ; in a byte string or something.

        Return := (String, String[0:0], String[0:0])

        Index := zstr.find(String, Separator)
        .if (Index != -1)
          Return := (String[:Index], Separator, String[Index+len(Separator):])
        .endif

      .endfunction Return

    ; Created: 0.19
    ; Updated: 0.19
    ; removeprefix(String, Prefix)

      ; Input:
        ; String: string to remove prefix from
        ; Prefix: prefix to remove

      ; Outputs:
        ; A new string

      ; Tries to remove a Prefix from a String.
      ; Returns the original String if it does not start
      ; with the Prefix.

      removeprefix .function String, Prefix
        Return := String
        .if (zstr.startswith(String, Prefix))
          Return := String[len(Prefix):]
        .endif
      .endfunction Return

    ; Created: 0.19
    ; Updated: 0.19
    ; removesuffix(String, Suffix)

      ; Inputs:
        ; String: String to remove suffix from
        ; Suffix: Suffix to remove

      ; Outputs:
        ; A new string

      ; Tries to remove a Suffix from a String.
      ; Returns the original String if it does not end
      ; with the Suffix.

      removesuffix .function String, Suffix
        Return := String
        .if (zstr.endswith(String, Suffix))
          Return := String[:-len(Suffix)]
        .endif
      .endfunction Return

    ; Created: 0.19
    ; Updated: 0.19
    ; replace(String, Old, New, Count=-1)

      ; Inputs:
        ; String: string to search through
        ; Old: Substring to be replaced by New
        ; New: Substring to replace Old
        ; Count: Optional number of replacements to make

      ; Outputs:
        ; A new string

      ; Tries to replace occurences of Old within a String
      ; with New. If Count is specified, only makes Count replacements.
      ; Otherwise, replaces all occurences of Old with New.

      ; If no occurences of Old are found or Count is 0, returns the
      ; original String.

      replace .function String, Old, New, Count=-1

        Return := String

        ; We can return early if we have nothing to do.

        .if (Old in String) && (Count != 0)

          Index := zstr.find(String, Old)
          Old_Len := len(Old)

          .while ((Index != -1) && (Count != 0))

            Return := Return[:Index] .. New .. Return[Index+Old_Len:]

            Index := zstr.find(Return, Old)
            Count -= 1
          .endwhile
        .endif
      .endfunction Return

    ; Created: 0.19
    ; Updated: 0.19
    ; rfind(String, Substring, Start=0, Stop=?)

      ; Inputs:
        ; String: String to search through
        ; Substring: Substring to look for
        ; Start: Optional starting index
        ; Stop: Optional stop index

      ; Outputs:
        ; Index of found substring, -1 if not found.

      ; Checks for some Substring within a String. Returns
      ; the index of the first matching substring or -1 if
      ; the substring is not found.

      ; This is different from zstr.find in that it searches from the right
      ; instead of from the left.

      rfind .function String, Substring, Start=0, Stop=?

        ; Instead of duplicating the zstr.find algorithm here,
        ; we're going to reverse the String and Substring and
        ; just use zstr.find.

        ; If Stop isn't given, set it to be the end of String.
        Stop := (Stop === ?) ? len(String) : Stop

        Reversed_Start := len(String) - Stop
        Reversed_Stop := len(String) - Start

        Return := zstr.find(iter.reversed(String), iter.reversed(Substring), Reversed_Start, Reversed_Stop)

        .if (Return != -1)

          Return := len(String) - Return - len(Substring)

        .endif

      .endfunction Return

    ; Created: 0.19
    ; Updated: 0.19
    ; rjust(String, Width, Fill=" ")

      ; Inputs:
        ; String: string to pad
        ; Width: character width to pad to
        ; Fill: character to pad with

      ; Outputs:
        ; A new string

      ; Tries to right-justify a String within a given Width.
      ; If the string is longer than the given Width, returns the
      ; original string.

      rjust .sfunction String, Width, Fill=" ", ((Fill x ((len(String) >= Width) ? 0 : Width - len(String))) .. String)

    ; Created: 0.19
    ; Updated: 0.19
    ; rpartition(String, Separator)

      ; Inputs:
        ; String: string to split
        ; Separator: Separator to split string at

      ; Outputs:
        ; A 3-tuple containing:
          ; The part before the separator
          ; The separator
          ; The part after the separator

        ; If the separator isn't found, returns:
          ; The string itself
          ; An empty string
          ; An empty string

      ; Splits a String at the first occurance of some
      ; Separator and returns a 3-tuple of the result.

      ; This is similar to zstr.partition except that it
      ; splits at the rightmost occurence of Separator.

      rpartition .function String, Separator

        ; Set the default return value for if the Separator
        ; isn't found.

        ; The weird slicing here is so that the return values
        ; have the same type as the String, in case we passed
        ; in a byte string or something.

        Return := (String, String[0:0], String[0:0])

        Index := zstr.rfind(String, Separator)
        .if (Index != -1)
          Return := (String[:Index], Separator, String[Index+len(Separator):])
        .endif

      .endfunction Return

    ; Created: 0.19
    ; Updated: 0.19
    ; rsplit(String, Separator, MaxSplit=-1)

      ; Inputs:
        ; String: String to split
        ; Separator: Optional Substring to split String at
        ; MaxSplit: Optional number of splits to make

      ; Outputs:
        ; A list of strings

      ; Tries to split a String at each occurence of
      ; Separator. If MaxSplit is specified and is not 0,
      ; splits MaxSplit times.

      ; If the Separator is not specified, defaults to splitting
      ; at spaces.

      ; This is similar to zstr.split except that it splits
      ; from the right.

      rsplit .function String, Separator=" ", MaxSplit=-1

        ; Instead of duplicating the zstr.split algorithm here,
        ; we'll reverse the String and Substring and leverage zstr.split.
        ; Then, we'll have to go and unreverse our results, if there are
        ; any.

        Splits := iter.reversed(zstr.split(iter.reversed(String), iter.reversed(Separator), MaxSplit))

        Return := []
        .for Split in Splits

           Return ..= [iter.reversed(Split)]

        .endfor

      .endfunction Return

    ; Created: 0.19
    ; Updated: 0.22
    ; rstrip(String, StripChars=" ")

      ; Inputs:
        ; String: string to strip
        ; StripChars: combination of characters to strip

      ; Outputs:
        ; A new string

      ; Tries to strip any character(s) from the left side of
      ; a String that are found in StripChars. For example:

      ; zstr.rstrip("www.example.com", "cmowz.") = "www.example"

      ; It stops once it encounters a character not in StripChars.
      ; It defaults to removing spaces if StripChars is not specified.

      ; This acts similarly to zstr.lstrip except that it strips from the
      ; right side.

      rstrip .function String, StripChars=" "
        .for Index, Character in iter.enumerate(iter.reversed(String))
          .breakif !(Character in StripChars)
        .endfor
        .if (Index == 0)
          Return := String
        .else
          Return := String[:-Index]
        .endif
      .endfunction Return

    ; Created: 0.19
    ; Updated: 0.19
    ; split(String, Separator, MaxSplit=-1)

      ; Inputs:
        ; String: String to split
        ; Separator: Optional Substring to split String at
        ; MaxSplit: Optional number of splits to make

      ; Outputs:
        ; A list of strings

      ; Tries to split a String at each occurence of
      ; Separator. If MaxSplit is specified and is not 0,
      ; splits MaxSplit times.

      ; If the Separator is not specified, defaults to splitting
      ; at spaces.

      split .function String, Separator=" ", MaxSplit=-1
        Return := []

        Parts := zstr.partition(String, Separator)

        Pos := 0
        Remaining := MaxSplit

        ; This is to keep the same type as the input String.

        Empty := String[0:0]

        ; Parts[1] is either the Separator or an empty string
        ; if there are no more Separators to find.

        .while (Parts[1] != Empty) && (Remaining != 0)

          ; Separator is in the current part of the
          ; string that we're looking though, so we know that
          ; zstr.partition's return is this type:

          Before     := Parts[0]
          _Separator := Parts[1]
          After      := Parts[2]

          Return ..= [Before]

          Pos += len(Before) + len(Separator)

          Parts := zstr.partition(String[Pos:], Separator)

          ; This is to respect MaxSplit.

          .if (Remaining != -1)
            Remaining -= 1
          .endif
        .endwhile

        ; Clean up any remaining stuff.
        Return ..= [String[Pos:]]

      .endfunction Return

    ; Created: 0.19
    ; Updated: 0.19
    ; strip(String, StripChars=" ")

      ; Inputs:
        ; String: string to strip
        ; StripChars: combination of characters to strip

      ; Outputs:
        ; A new string

      ; Strips any character found in StripChars from both
      ; sides of a string.

      ; If StripChars is not specified, defaults to stripping spaces.

      strip .sfunction String, StripChars=" ", (zstr.lstrip(zstr.rstrip(String, StripChars), StripChars))

    ; Created: 0.19
    ; Updated: 0.19
    ; startswith(String, Prefix, Start=0, Stop=?)

      ; Inputs:
        ; String: String to search through
        ; Prefix: Prefix(es) to check for
        ; Start: Optional starting index
        ; Stop: Optional stop index

      ; Outputs:
        ; true if String[Start:Stop] starts with Prefix,
          ; false otherwise.

      ; Checks if a String starts with some Prefix, optionally
      ; only checking if a certain part of the String starts with it.

      ; Prefix can also be a list of strings to check for, instead of
      ; a single string.

      startswith .function String, Prefix, Start=0, Stop=?

        ; If Stop isn't given, set it to be the end of String.
        Stop := (Stop === ?) ? len(String) : Stop

        ; If we're looking for a single string, we need to wrap
        ; it into a list for the next step.

        .if (type(Prefix) != list)
          Prefix := [Prefix]
        .endif

        Return := false

        ; Fetch the part of String that we're looking through.

        Region := String[Start:Stop]

        .for Pre in Prefix

          ; We only care if the suffix isn't empty and that
          ; the suffix fits within the string.

          .if (len(Region) >= len(Pre)) && (len(Pre) != 0)

            .if (Region[:len(Pre)] == Pre)

              Return := true
              .break

            .endif
          .endif
        .endfor
      .endfunction Return

    ; Created: 0.19
    ; Updated: 0.19
    ; zfill(String, Width)

      ; Inputs:
        ; String: String to pad
        ; Width: Number of characters to pad to

      ; Outputs:
        ; A new string

      ; Tries to pad a numeric String with zeroes.
      ; If the String is longer than the specified Width, the
      ; original String is returned.

      ; If the string starts with a sign character, the padding
      ; zeroes will be placed between it at the rest of the string.

      zfill .function String, Width

        Return := String

        ; We can return early if the string is larger than
        ; the requested Width.

        .if (Width > len(String))

          ; This is so that the type matches the original String.
          SignChar := String[0:0]

          Pos := 0

          .for Sign in "+-"

            ; Looping through both for simplicity, despite
            ; at most one being valid.

            .if (zstr.startswith(String, Sign))
              SignChar := Sign
              Pos += 1
            .endif

          .endfor

          ; Leveraging zstr.rjust to do the bulk of the work.

          Return := SignChar .. zstr.rjust(String[Pos:], Width - len(SignChar), "0")

        .endif

      .endfunction Return

    ; Created: 0.22
    ; Updated: 0.22
    ; to_int(String, Base=10)

      ; Inputs:
        ; String: string to convert
        ; Base: Numeric base

      ; Outputs:
        ; An int if able to be converted else ?

      ; Tries to convert a string representing a number into an int.
      ; A number in the form of the string can optionally begin with a sign,
      ; followed by an optional prefix, then the actual number.

      ; This function will return ? if it's unable to convert
      ; the text.

      ; Private helper values

      _to_int .namespace

        .enc "none"

        ; These are the valid digit characters that make up
        ; the body of a number.

          BinaryCharacters = "01"
          DecimalCharacters = (str(range(10)) .. ...)
          HexadecimalCharacters = DecimalCharacters .. "abcdefABCDEF"

          AllCharacters = BinaryCharacters .. DecimalCharacters .. HexadecimalCharacters

        ; These are the valid prefix substrings for
        ; each base.

          BinaryPrefixes = ["0b", "%"]
          DecimalPrefixes = []
          HexadecimalPrefixes = ["0x", "$"]

          AllPrefixes = BinaryPrefixes .. DecimalPrefixes .. HexadecimalPrefixes

        ; These are the numeric vlues, in decimal, of
        ; each digit character for all bases

          BinaryConversions = {"0": 0, "1": 1}
          DecimalConversions = {"0": 0, "1": 1, "2": 2, "3": 3, "4": 4, "5": 5, "6": 6, "7": 7, "8": 8, "9": 9}
          HexadecimalConversions = {"a": 10, "A": 10, "b": 11, "B": 11, "c": 12, "C": 12, "d": 13, "D": 13, "e": 14, "E": 14, "f": 15, "F": 15}

          AllConversions = BinaryConversions .. DecimalConversions .. HexadecimalConversions

        ; This dictionary gives the information needed for
        ; each base.

          ; {Base: (BodyCharacters, Prefixes)}
          BaseInfo = {2: (BinaryCharacters, BinaryPrefixes), 10: (DecimalCharacters, DecimalPrefixes), 16: (HexadecimalCharacters, HexadecimalPrefixes)}

      .endnamespace

      to_int .function String, Base=10

        .with zstr._to_int

        .cerror !(Base in [2, 10, 16]), "Can only convert numbers with a base of 2, 10, or 16."
        .cerror (len(String) == 0), "Cannot convert an empty string."

        ; Strip whitespace from string.

        String := zstr.strip(String)

        BaseChars := iter.fst(BaseInfo[Base])
        Prefixes  := iter.snd(BaseInfo[Base])

        Return     := ""
        Position   := 0
        isNegative := false

        ; Check for leading sign characters.

        .switch String[Position]

          .case "-"

            isNegative := true
            Position += 1

          .case "+"

            Position += 1

          .default

        .endswitch

        ; Now, check for prefixes

        .for Prefix in Prefixes

          .if (zstr.startswith(String[Position:], Prefix))

            Position += len(Prefix)
            .break

          .endif

        .endfor

        ; Now we can actually scan the numeric bits.

        .while (Position < len(String))

          Return *= Base

          Character := String[Position]

          .if !(Character in BaseChars)

            ;.error format("Illegal character '%c' for integer with base %d", Character, Base)
            Return := ?
            .break

          .else

            Return += AllConversions[Character]

          .endif

          Position += 1

        .endwhile

        .if (!(Return === ?) && isNegative)

          Return := -Return

        .endif ; (!(Return === ?) && isNegative)

        .endwith ; zstr._to_int

      .endfunction Return

  .endnamespace ; zstr

.endif ; GUARD_VOLTEDGE_FUNCTIONS_STRINGS
