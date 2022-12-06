
GUARD_VOLTEDGE_FUNCTIONS_ITERABLES :?= false
.if (!GUARD_VOLTEDGE_FUNCTIONS_ITERABLES)
  GUARD_VOLTEDGE_FUNCTIONS_ITERABLES := true

  VoltEdge_Functions_Iterables_Created = 0.23
  VoltEdge_Functions_Iterables_Updated = 0.23

  ; These functions work with iterables: lists, tuples, and
  ; sometimes strings. They mostly try to mimic Python's itertools.

  iter .namespace

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

.endif ; GUARD_VOLTEDGE_FUNCTIONS_ITERABLES
