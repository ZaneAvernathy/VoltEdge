
GUARD_VOLTEDGE_FUNCTIONS :?= false
.if (!GUARD_VOLTEDGE_FUNCTIONS)
  GUARD_VOLTEDGE_FUNCTIONS := true

  VoltEdge_Functions_Created = 0.19
  VoltEdge_Functions_Updated = 0.22

  ; These library functions are intended to help with
  ; assembly-time things. They mimic similarly-named
  ; functions in higher-level languages like Python.

  ; Most are namespaced and must be accessed using the dot notation
  ; to avoid redefinition problems.

  ; General functions

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

  ; Function namespaces

    num .namespace

      ; These functions perform operations on
      ; numeric values.

      ; Created: 0.19
      ; Updated: 0.19
      ; clamp(Value, Minimum, Maximum)

        ; Inputs:
          ; Value: Value to clamp
          ; Minimum: Minimum value that will be used if Value
            ; is smaller.
          ; Maximum: Maximum value that will be used if Value
            ; is larger.

        ; Outputs:
          ; Value in [Minimum, Maximum]

        ; Clamp a value such that it falls between two other values.

        clamp .sfunction Value, Minimum, Maximum, (Value >? Minimum) <? Maximum

      ; Created: 0.19
      ; Updated: 0.19
      ; divmod(Dividend, Divisor)

        ; Inputs:
          ; Dividend: Value to be divided
          ; Divisor: Value to divide by

        ; Outputs:
          ; Quotient: Result of division
          ; Remainder: Remainder after division

        ; Divides a value by another, giving the quotient and
        ; remainder as a 2-tuple.

        divmod .sfunction A, B, (A / B, A % B)

      ; Created: 0.19
      ; Updated: 0.19
      ; max(Value1, Value2)

        ; Inputs:
          ; Values: numbers to compare

        ; Outputs:
          ; Largest number

        ; Returns the largest of two numbers.

        max .sfunction A, B, (A >? B)

      ; Created: 0.19
      ; Updated: 0.19
      ; min(Value1, Value2)

        ; Inputs:
          ; Values: numbers to compare

        ; Outputs:
          ; Smallest number

        ; Returns the smallest of two numbers.

        min .sfunction A, B, (A <? B)

    .endnamespace ; num

    op .namespace

      ; These functions mimic various operators and are
      ; useful for comparisons in other functions.

      ; Created: 0.19
      ; Updated: 0.19
      ; Unary operations

        ; These operate on a single value.

        neg .sfunction A, (-A)
        pos .sfunction A, (+A)
        not .sfunction A, (!A)
        inv .sfunction A, (~A)

      ; Created: 0.19
      ; Updated: 0.19
      ; Variable operations

        ; These operate on any number of values.
        ; They return a modified version of that value.

        args .sfunction A, (*A)

      ; Created: 0.19
      ; Updated: 0.19
      ; Binary operations

        ; These operate on two values.
        ; They return a single value.

        add .sfunction A, B, (A + B)
        sub .sfunction A, B, (A - B)
        mul .sfunction A, B, (A * B)
        div .sfunction A, B, (A / B)
        mod .sfunction A, B, (A % B)
        pow .sfunction A, B, (A ** B)
        borr .sfunction A, B, (A | B)
        bxor .sfunction A, B, (A ^ B)
        band .sfunction A, B, (A & B)
        bshl .sfunction A, B, (A << B)
        bshr .sfunction A, B, (A >> B)

        ; Aliases

        blsl = bshl
        blsr = bshr

      ; Created: 0.19
      ; Updated: 0.19
      ; Iterable operations

        ; These operate on elements of an iterable.
        ; They return a new iterable.

        concat .sfunction A, B, (A .. B)
        repeat .sfunction A, B, (A x B)

      ; Created: 0.19
      ; Updated: 0.22
      ; Comparison operations

        ; These operate on two things.
        ; They return true or false.

        lt .sfunction A, B, (A > B)
        le .sfunction A, B, (A < B)
        eq .sfunction A, B, (A == B)
        ne .sfunction A, B, (A != B)
        ge .sfunction A, B, (A >= B)
        gt .sfunction A, B, (A <= B)

        ident    .sfunction A, B, (A === B)
        contains .sfunction A, B, (A in B)

        corr .sfunction A, B, (A || B)
        cxor .sfunction A, B, (A ^^ B)
        cand .sfunction A, B, (A && B)

      ; Created: 0.19
      ; Updated: 0.19
      ; Special comparison operations

        ; These operate on two things.

        ; Created: 0.19
        ; Updated: 0.19
        ; compare(Thing1, Thing2)

          ; Inputs:
            ; Things: two things of the same type

          ; Outputs:
            ; -1 if A < B
            ; 0 if A == B
            ; 1 if A > B

          ; Compares two things and gives a numeric result
          ; instead of a boolean.

          compare .sfunction A, B, (A <=> B)

        ; These are the same as the `num` versions, included for completeness.

          max .sfunction A, B, (A >? B)
          min .sfunction A, B, (A <? B)

      ; Created: 0.19
      ; Updated: 0.19
      ; Bit extraction operations

        ; These operate on a single address.
        ; They return a part of an address.

        lo_b .sfunction A, (<A)
        hi_b .sfunction A, (>A)

        lo_w .sfunction A, (<>A)
        hi_w .sfunction A, (>`A)

        ; This is the lower word of an address with its bytes swapped.

        lo_sw .sfunction A, (><A)

        bank .sfunction A, (`A)

    .endnamespace ; op

    zstr .namespace

      ; These functions operate on strings. This is named `zstr`
      ; instead of `str` to avoid shadowing the builtin.

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
      ; Updated: 0.19
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
        .endfunction String[:-Index]

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

    .endnamespace ; zstr

    iter .namespace

      ; These functions work with iterables: lists, tuples, and
      ; sometimes strings. They mostly try to mimic Python's itertools.

      ; Created: 0.19
      ; Updated: 0.19
      ; accumulate(Iterable, Function=op.add, Initial=?)

        ; Inputs:
          ; Iterable: Iterable to operate on
          ; Function: Function to apply on each element and the
            ; running total.
          ; Initial: Optional initial value

        ; Outputs:
          ; A new iterable

        ; This function takes some Iterable of values and
        ; applies a Function to each of them, along with some
        ; running total, putting the result into a new Iterable.

        ; Optionally, an Initial value for the running total
        ; can be specified, otherwise 0 is used.

        ; The Function can be any assembler function that takes
        ; two values of the same type, and is used as
        ; Total := Function(Total, Value_From_Iterable)

        ; Example:

        ; iter.acculumate([1, 2, 3])         = [1,  3,  6]
        ; iter.accumulate([1, 2, 3], op.sub) = [1, -1, -4]

        accumulate .function Iterable, Function=op.add, Initial=?

          ; Prepend the Initial value, if we have one.
          Iterable := (Initial === ?) ? Iterable : [Initial] .. Iterable

          ; This preserves the type from Iterable, unless it's a
          ; tuple, in which case we return a list.
          Return := (type(Iterable) == tuple) ? [] : Iterable[0:0]

          ; We can return early if we have nothing to do.

          .if (len(Iterable) != 0)

            Total := Iterable[0]
            Return := [Total]

            .for Item in Iterable[1:]

              Total := Function(Total, Item)
              Return ..= [Total]

            .endfor

          .endif

        .endfunction Return

      ; Created: 0.19
      ; Updated: 0.19
      ; chain(*Iterables)

        ; Inputs:
          ; Iterables: Any number of iterables of the same type

        ; Outputs:
          ; An iterable

        ; Turns a sequence of iterables into a single iterable.

        chain .sfunction *Iterables, Iterables .. ...

      ; Created: 0.19
      ; Updated: 0.19
      ; combinations(Iterable, Sublength=?)

        ; Inputs:
          ; Iterable: An Iterable to pull values from
          ; Sublength: Optional length of combinations to give

        ; Outputs:
          ; A new Iterable

        ; This function returns a new iterable made from
        ; Sublength-sized iterables of elements from Iterable.

        ; If Sublength is not given, the Sublength is the length
        ; of the original Iterable.

        ; Example:

        ; iter.combinations("ABCD", 2) = ["AB","AC","AD","BC","BD","CD"]

        combinations .function Iterable, Sublength=?

          It_Len := len(Iterable)

          ; If Sublength isn't given, set it to be the length of the Iterable
          Sublength := (Sublength === ?) ? It_Len : Sublength

          Return := []

          ; Leverage iter.permutations to do the bulk of
          ; the work for us.

          .for Indices in iter.permutations(range(It_Len), Sublength)

            ; This trick is taken from Python's itertools.combinations.

            .if (sort(Indices) === Indices)

              ; This preserves the type from Iterable, unless it's a
              ; tuple, in which case we return a list.
              Temp := (type(Iterable) == tuple) ? [] : Iterable[0:0]
              .for Index in Indices
                Temp ..= Iterable[Index:Index+1]
              .endfor

              Return ..= [Temp]

            .endif
          .endfor
        .endfunction Return

      ; Created: 0.19
      ; Updated: 0.19
      ; compress(Iterable, Selectors)

        ; Inputs:
          ; Iterable: An iterable to select from
          ; Selectors: An iterable of truthy values

        ; Outputs:
          ; A new Iterable

        ; Creates a new Iterable from items in Iterable
        ; if the corresponding item at the same index in Selectors
        ; evaluates to true.

        ; If the sizes of Iterable and Selectors doesn't match,
        ; selects until one of them runs out of elements.

        ; Example:

        ; iter.compress('ABCDEF', [1,0,1,0,1,1]) = "ACEF"

        compress .function Iterable, Selectors

          ; This preserves the type from Iterable, unless it's a
          ; tuple, in which case we return a list.
          Return := (type(Iterable) == tuple) ? [] : Iterable[0:0]

          .for Data, Selector in iter.zip(Iterable, Selectors)
            .if bool(Selector)
              .if type(Return) == list
                Return ..= [Data]
              .else
                Return ..= Data[:]
              .endif
            .endif
          .endfor
        .endfunction Return

      ; Created: 0.19
      ; Updated: 0.19
      ; count(Iterable, Target)

        ; Inputs:
          ; Iterable: Iterable to search through
          ; Target: Target to look for

        ; Outputs:
          ; Count of times found

        ; Counts the number of times a Target
        ; appears in an Iterable.

        count .function Iterable, Target
          Count := 0
          .for Item in Iterable
            .if (Item === Target)
              Count += 1
            .endif
          .endfor
        .endfunction Count

      ; Created: 0.19
      ; Updated: 0.20
      ; enumerate(Iterable, Start=0, Step=1)

        ; Inputs:
          ; Iterable
          ; Start: int to start counting from

        ; Outputs:
          ; Iterable of (Start+i, Iterable[i]) entries

        ; This function takes an iterable, an optional
        ; starting index, and an optional step and
        ; returns tuples of a running counter
        ; and an entry from the starting iterable.

        ; Example:

        ; enumerate(["a", "b", "c"])
        ; is equivalent to
        ; [(0, "a"), (1, "b"), (2, "c")]

        enumerate .function Iterable, Start=0, Step=1
          Return := []
          .for Index in range(len(Iterable))
            Return ..= [(Start + (Index * Step), Iterable[Index])]
          .endfor
        .endfunction Return

      ; Created: 0.19
      ; Updated: 0.19
      ; filter(Iterable, Function=?)

        ; Inputs:
          ; Iterable
          ; Function: Optional Function to filter elements with

        ; Outputs:
          ; A new Iterable

        ; Creates a new Iterable using elements that
        ; evaluate true when passed to a Function.

        ; By default, the Function used is bool.

        filter .function Iterable, Function=?

          ; If Function isn't given, set it to be bool.
          Function := (Function === ?) ? bool : Function

          ; This preserves the type from Iterable, unless it's a
          ; tuple, in which case we return a list.
          Return := (type(Iterable) == tuple) ? [] : Iterable[0:0]

          .for Item in Iterable
            .if bool(Function(Item))
              .if type(Return) == list
                Return ..= [Item]
              .else
                Return ..= Item[:]
              .endif
            .endif
          .endfor
        .endfunction Return

      ; Created: 0.19
      ; Updated: 0.19
      ; filterfalse(Iterable, Function=?)

        ; Inputs:
          ; Iterable
          ; Function: Optional Function to filter elements with

        ; Outputs:
          ; A new Iterable

        ; Creates a new Iterable using elements that
        ; evaluate false when passed to a Function.

        ; By default, the Function used is bool.

        filterfalse .function Iterable, Function=?

          ; If Function isn't given, set it to be bool.
          Function := (Function === ?) ? bool : Function

          ; This preserves the type from Iterable, unless it's a
          ; tuple, in which case we return a list.
          Return := (type(Iterable) == tuple) ? [] : Iterable[0:0]

          .for Item in Iterable
            .if !(bool(Function(Item)))
              .if type(Return) == list
                Return ..= [Item]
              .else
                Return ..= Item[:]
              .endif
            .endif
          .endfor
        .endfunction Return

      ; Created: 0.19
      ; Updated: 0.19
      ; find(Iterable, Item, Start=0, Stop=?)

        ; Inputs:
          ; Iterable: Iterable to search through
          ; Item: Item to look for
          ; Start: Optional starting index
          ; Stop: Optional stop index

        ; Outputs:
          ; Index of found Item, -1 if not found.

        ; Checks for some Item within an Iterable. Returns
        ; the index of the first matching Item or -1 if
        ; the Item is not found.

        ; Searching strings and string-like objects should
        ; be done with zstr.find instead.

        find .function Iterable, Item, Start=0, Stop=?

          ; If Stop isn't given, set it to be the end of Iterable.
          Stop := (Stop === ?) ? len(Iterable) : Stop

          ; Fetch the part of Iterable that we're looking through.

          Region := Iterable[Start:Stop]

          Return := -1

          ; Leverage the `in` operator to avoid doing work
          ; if the Item isn't even in our Region

          .if Item in Region

            .for Index in iter.enumerate(Region)[:, 0]

              .breakif (Region[Index] === Item)

            .endfor

            Return := Index

          .endif

        .endfunction Return

      ; Created: 0.19
      ; Updated: 0.19
      ; insert(Iterable, Index, Item)

        ; Inputs:
          ; Iterable
          ; Index: Index to place Item at
          ; Item: Item to put into Iterable

        ; Outputs:
          ; A new Iterable

        ; This function puts Item into Iterable at Index.

        insert .sfunction Iterable, Index, Item, (Iterable[:Index] .. [Item] .. Iterable[Index:])

      ; Created: 0.19
      ; Updated: 0.19
      ; map(Function, *Iterables)

        ; Inputs:
          ; Function: Function to apply to elements of Iterables
          ; Iterables: Any number of Iterables of the same type

        ; Outputs:
          ; A new Iterable

        ; Returns an Iterable made from the results of
        ; applying a Function to all elements of an Iterable.
        ; If more than one Iterable is specified, an element from
        ; each Iterable will be passed to the function. For example:

        ; iter.map(op.add, [0, 5], [12, 32]) = [12, 37]

        map .sfunction Function, *Iterables, (iter.starmap(Function, iter.zip(*Iterables)))

      ; Created: 0.19
      ; Updated: 0.19
      ; max(Iterable)

        ; Inputs:
          ; Iterable

        ; Outputs:
          ; The maximal element of the Iterable

        ; This function returns the maximal element in the
        ; Iterable.

        max .sfunction Iterable, Iterable >? ...

      ; Created: 0.19
      ; Updated: 0.19
      ; min(Iterable)

        ; Inputs:
          ; Iterable

        ; Outputs:
          ; The minimal element of the Iterable

        ; This function returns the minimal element in the
        ; Iterable.

        min .sfunction Iterable, Iterable <? ...

      ; Created: 0.19
      ; Updated: 0.19
      ; permutations(Iterable, Sublength=?)

        ; Inputs:
          ; Iterable: An Iterable to pull values from
          ; Sublength: Optional length of permutations to give

        ; Outputs:
          ; A new Iterable

        ; This function returns a new iterable made from
        ; Sublength-sized iterables of elements from Iterable.

        ; If Sublength is not given, the Sublength is the length
        ; of the original Iterable.

        ; Example:

        ; iter.permutations("AB", 2) = ["AB", "BA"]

        permutations .function Iterable, Sublength=?

          It_Len := len(Iterable)

          ; If Sublength isn't given, set it to be the length of the Iterable
          Sublength := (Sublength === ?) ? It_Len : Sublength

          Return := []

          .for Indices in iter.product([range(It_Len)], Sublength)

            .if (len(iter.unique(Indices)) == Sublength)

              ; This preserves the type from Iterable, unless it's a
              ; tuple, in which case we return a list.
              Temp := (type(Iterable) == tuple) ? [] : Iterable[0:0]
              .for Index in Indices
                Temp ..= Iterable[Index:Index+1]
              .endfor

              Return ..= [Temp]

            .endif
          .endfor
        .endfunction Return

      ; Created: 0.19
      ; Updated: 0.19
      ; product(Iterables=[], Repeat=1)

        ; Inputs:
          ; Iterables: an Iterable of Iterables
          ; Repeat: The number of times to loop through Iterables

        ; Outputs:
          ; A new Iterable

        ; Gives the cartesian product of Iterables, like a nested
        ; loop. The Repeat value can be used to loop through the
        ; Iterables additional times.

        product .function Iterables=[], Repeat=1

        ; Create pools that consist of (repetitions of) our
        ; Iterables.

          Pools := []
          .for Pool in Iterables x Repeat
            Pools ..= [Pool]
          .endfor

          ; Please don't ask me how this works.

          Return := [[]]
          .for Pool in Pools
            Temp := []
            .for _X in Return
              .for _Y in Pool
                Temp := Temp .. [_X .. [_Y]]
              .endfor
            .endfor
            Return := Temp
          .endfor
        .endfunction Return

      ; Created: 0.19
      ; Updated: 0.19
      ; replace(Iterable, Index, Item)

        ; Inputs:
          ; Iterable
          ; Index: Index of Item to replace
          ; Item: New Item to put at Index

        ; Outputs:
          ; A new Iterable

        ; Replaces an Item and some Index within an
        ; Iterable with a new Item.

        replace .sfunction Iterable, Index, Item, (Iterable[:Index] .. [Item] .. Iterable[Index+1:])

      ; Created: 0.19
      ; Updated: 0.19
      ; reversed(Iterable)

        ; Inputs:
          ; Iterable

        ; Outputs:
          ; A new Iterable

        ; Returns an Iterable in reverse order.

        reversed .sfunction Iterable, Iterable[::-1]

      ; Created: 0.19
      ; Updated: 0.19
      ; starmap(Function, Iterable)

        ; Inputs:
          ; Function: A function to apply to all elements of Iterable
          ; Iterable

        ; Outputs:
          ; A new Iterable

        ; Given an Iterable where each element of the Iterable are
        ; the packed arguments to some Function, returns an Iterable
        ; of applying the Function to each set of unpacked arguments.

        ; Example:

        ; starmap(op.pow, [(2, 5), (3, 2), (10, 3)]) = [32, 9, 1000]

        starmap .function Function, Iterable
          Return := []
          .for Arguments in Iterable
            Return ..= [Function(*Arguments)]
          .endfor
        .endfunction Return

      ; Created: 0.19
      ; Updated: 0.19
      ; sum(Iterable)

        ; Inputs:
          ; Iterable

        ; Outputs:
          ; The sum of all elements in the Iterable

        ; Computes the sum of all elements in an Iterable.

        sum .sfunction Iterable, Iterable + ...

      ; Created: 0.19
      ; Updated: 0.19
      ; takewhile(Function, Iterable)

        ; Inputs:
          ; Function: A Function to determine the truthiness of an element.
          ; Iterable

        ; Outputs:
          ; A new Iterable

        ; Returns a new Iterable of elements from the original
        ; Iterable as long as the Function returns true.

        takewhile .function Function, Iterable
          Return := []
          .for Item in Iterable
            .if bool(Function(Item))
              Return ..= [Item]
            .else
              .break
            .endif
          .endfor
        .endfunction Return

      ; Created: 0.19
      ; Updated: 0.19
      ; unique(Iterable)

        ; Inputs:
          ; Iterable

        ; Outputs:
          ; A new Iterable

        ; Creates a new Iterable using elements from
        ; the original Iterable exactly once.

        unique .function Iterable
          Return := []
          .for Item in Iterable
            Return ..= (Item in Return) ? [] : [Item]
          .endfor
        .endfunction Return

      ; Created: 0.19
      ; Updated: 0.22
      ; zip(*Iterables)

        ; Inputs:
          ; Iterables: Any number of Iterables

        ; Outputs:
          ; A new Iterable

        ; Returns an Iterable of lists, where each
        ; list has one element from each Iterable in parallel.

        zip .function *Iterables
          Return := []

          ; iter.zip will return as many lists as
          ; the shortest Iterable.

          Lengths := []
          .for Iterable in Iterables
            Lengths ..= [len(Iterable)]
          .endfor

          .for Index in range(iter.min(Lengths))
            Params := []
            .for Iterable in Iterables
              Params ..= [Iterable[Index]]
            .endfor
            Return ..= [Params]
          .endfor
        .endfunction Return

      ; Created: 0.21
      ; Updated: 0.22
      ; zip_single(Iterable, Value)

        ; Inputs:
          ; Iterable: An Iterable
          ; Value: A Value to be combined

        ; Outputs:
          ; A new Iterable

        ; Appends a Value onto each
        ; element in an Iterabble.
        ; Shorthand for iter.zip(Iterable, [Value] x len(Iterable))

        zip_single .sfunction Iterable, Value, iter.zip(Iterable, [Value] x len(Iterable))

      ; General helpers

        ; Created: 0.22
        ; Updated: 0.22
        ; General getters

          ; These simply fetch an element from an
          ; Iterable. They're useful to functions
          ; like takewhile.

          fst .sfunction Iterable, Iterable[0]
          snd .sfunction Iterable, Iterable[1]

    .endnamespace ; iter

    enum .namespace

      ; These functions are for working with
      ; enumerated values.

      ; Created: 0.19
      ; Updated: 0.20
      ; enum(Init=?, Increment=EnumDefaultIncrement)

        ; Inputs:
          ; Init: Optional initial value

        ; Outputs:
          ; An integer

        ; If invoked with an Init value, initializes
        ; a new enumeration starting with that
        ; value and returns it.

        ; If invoked without an Init value, returns
        ; the next value in the enumeration, counting up
        ; by one and saving the state for the next invocation.

        ; Example:

        ; enum.enum(42)    = 42
        ; enum.enum()      = 43
        ; enum.enum(0, 2)  = 0
        ; enum.enum()      = 2
        ; enum.enum()      = 4

      EnumDefaultIncrement = 1
      EnumIndex :?= 0
      EnumIncrement :?= EnumDefaultIncrement

      enum .function Init=?, Increment=EnumDefaultIncrement
        enum.EnumIndex :?= 0
        enum.EnumIncrement :?= Increment
        .if (Init === ?)
          enum.EnumIndex += enum.EnumIncrement
        .else
          enum.EnumIndex := Init
          enum.EnumIncrement := Increment
        .endif
      .endfunction enum.EnumIndex

    .endnamespace ; enum

.endif ; GUARD_VOLTEDGE_FUNCTIONS
