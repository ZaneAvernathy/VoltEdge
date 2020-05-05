
GUARD_VOLTEDGE_IO_REGISTERS :?= false
.if (!GUARD_VOLTEDGE_IO_REGISTERS)
  GUARD_VOLTEDGE_IO_REGISTERS := true

  VoltEdge.IORegisters .namespace

    Created = 0.01
    Updated = 0.01

  .endn

  ; Names, values, information, etc. are taken from fullsnes
  ; https://problemkaputt.de/fullsnes.htm

  ; These are the starting addresses of
  ; memory mapped I/O register groups.

  PPU_REG_BASE   = $002100
  APU_REG_BASE   = $002140
  WRAM_REG_BASE  = $002180
  JOY_REG_BASE   = $004016
  CPU_W_REG_BASE = $004200
  CPU_R_REG_BASE = $004210
  DMA_REG_BASE   = $004300

  .virtual PPU_REG_BASE

    ; Created: 0.01
    ; Updated: 0.01
    INIDISP .byte ? ; $002100

      ; This controls the screen's brightness
      ; and whether the PPU is in `Forced Blank`
      ; mode. Forced blanking causes a solid black
      ; screen and allows VRAM, OAM, and CGRAM
      ; to be freely accessed.

      ; Bitmasks:

      INIDISP_ForcedBlank = bits(%10000000)

        ; Setting this bit enables forced blanking
        ; and will turn the screen black.

      INIDISP_Unused      = bits(%01110000)

      INIDISP_Brightness  = bits(%00001111)

        ; 0-15, with 0 being black and 15 being
        ; full brightness.

      ; Helpers:

      INIDISP_Setting .function ForcedBlank=false, Brightness=0
      .endf bits((int(ForcedBlank) << 7) | (Brightness & INIDISP_Brightness))

        ; Example:
        ; lda #INIDISP_Setting(true, 0)  ; Screen off, brightness 0
        ; lda #INIDISP_Setting(false, 8) ; Screen on, half brightness

    ; Created: 0.01
    ; Updated: 0.01
    OBSEL .byte ? ; $002101

      ; This controls the size of objects (sprites),
      ; where in VRAM the graphics for objects start,
      ; and the gap between object tile graphics $0FF
      ; and $100.

      ; Bitmasks:

      OBSEL_Size = bits(%11100000)

        ; Determines the two sizes available to
        ; objects. Each object can select whether
        ; to use the smaller or larger size in their
        ; OAM data.

      OBSEL_Gap  = bits(%00011000)

        ; Normally, there are $2000 bytes between object
        ; tile $000 and object tile $100, which is the
        ; amount of space taken up by $100 tiles.
        ; This value adds ($2000 * value) to the normal $2000 gap.

      OBSEL_Base = bits(%00000111)

        ; This determines where in VRAM object tiles
        ; begin. The VRAM address is given by the
        ; formula ($4000 * value).

      ; Helpers:

      ObjSize8x8And16x16   = 0 << 5
      ObjSize8x8And32x32   = 1 << 5
      ObjSize8x8And64x64   = 2 << 5
      ObjSize16x16And32x32 = 3 << 5
      ObjSize16x16And64x64 = 4 << 5
      ObjSize32x32And64x64 = 5 << 5
      ObjSize16x32And32x64 = 6 << 5
      ObjSize16x32And32x32 = 7 << 5

      OBSEL_Size_Settings = [ObjSize8x8And16x16, ObjSize8x8And32x32, ObjSize8x8And64x64, ]

        ; Error messages

        OBSEL_VALUE_ERROR  := "Address of second object tile block ($%04X) must be at least $2000 bytes after first ($%04X)."
        OBSEL_BASE1_ERROR  := "Address of first object tile block ($%04X) must be a multiple of $4000."
        OBSEL_BASE2_ERROR  := "Address of second object tile block ($%04X) must be a multiple of $2000, "
        OBSEL_BASE2_ERROR ..= "and greater than or equal to the address of the first object tile block + $2000 ($%04X)."

      OBSEL_Setting .function Size=ObjSize8x8And16x16, Base1=$0000, Base2=$2000
        .if (Base2 < (Base1 + $2000))
          .error format(OBSEL_VALUE_ERROR, Base2, Base1)
        .endif
        .if ((Base1 & $3FFF) != 0)
          .error format(OBSEL_BASE1_ERROR, Base1)
        .endif
        .if ((Base2 & $1FFF) != 0)
          .error format(OBSEL_BASE2_ERROR, Base2, (Base1 + $2000))
        .endif
        Base := ((Base1 >> 14) & OBSEL_Base)
        Gap := (((Base2 - Base1 - $2000) >> 10) & OBSEL_Gap)
      .endf bits(Size | Base | Gap)

        ; Example:
        ; lda #OBSEL_Setting(ObjSize16x16And32x32, $0000, $4000)

    ; Created: 0.01
    ; Updated: 0.01
    OAMADD .word ? ; $002102

      ; This register has two purposes:
      ; It sets the target address for OAM reads/writes
      ; It sets which object has the highest priority

      ; Bitmasks:

      OAMADD_Priority = bits(%1000000000000000)

        ; Setting this bit causes the object number
        ; specified by OAMADD_Prio_Num to have the
        ; highest priority.

      OAMADD_Unused   = bits(%0111111000000000)

      OAMADD_Prio_Num = bits(%0000000011111110)

        ; This specifies which object has the highest
        ; priority when used with the OAMADD_Priority bit.

      OAMADD_Address  = bits(%0000000111111111)

        ; This is the address for reading/writing from/to
        ; OAM.

      ; Helpers:

      OAMADD_Priority_Setting .function Priority=true, Object
      .endf bits((int(Priority) << 15) | ((Object << 1) & OAMADD_Prio_Num))

      OAMADD_Setting .function Address
      .endf bits(Address & OAMADD_Address)

        ; Examples:

        ; lda #OAMADD_Setting($1FC)
        ; lda #OAMADD_Priority_Setting(true, 127)

    ; Created: 0.01
    ; Updated: 0.01
    OAMDATA .byte ? ; $002104

      ; This register is used to write data
      ; one byte at a time to OAM. Every write increments
      ; the write address automatically.

    ; Created: 0.01
    ; Updated: 0.01
    BGMODE .byte ? ; $002105

      ; This register determines the size of tiles
      ; for each background layer. Additionally, it
      ; determines the priority of BG3 in mode 1 and
      ; sets the BG mode.

      BGMODE_BG4_Size     = bits(%10000000)
      BGMODE_BG3_Size     = bits(%01000000)
      BGMODE_BG2_Size     = bits(%00100000)
      BGMODE_BG1_Size     = bits(%00010000)

        ; Setting these bits to true causes
        ; all tiles to be larger, usually
        ; 16x16 instead of the normal 8x8.

        ; Exceptions:

        ; Mode 5: 8x8 acts as 16x8
        ; Mode 6: tiles are fixed as 16x8
        ; Mode 7: tiles are fixed as 8x8

      BGMODE_BG3_Priority = bits(%00001000)

        ; Setting this bit will give BG3
        ; high priority while in Mode 1.

      BGMODE_Mode         = bits(%00000111)

        ; This determines the bit depth for
        ; background layers and specifies other
        ; special background formats.

      ; Helpers:

                   ; BG1   BG2   BG3  BG4  Notes

      BG_Mode0 = 0 ; 2bpp  2bpp  2bpp 2bpp 
      BG_Mode1 = 1 ; 4bpp  4bpp  2bpp ---  
      BG_Mode2 = 2 ; 4bpp  4bpp  OPT  ---  
      BG_Mode3 = 3 ; 8bpp  4bpp  ---  ---  
      BG_Mode4 = 4 ; 8bpp  2bpp  OPT  ---  
      BG_Mode5 = 5 ; 4bpp  2bpp  ---  ---  512px hires
      BG_Mode6 = 6 ; 4bpp  ---   OPT  ---  hires+OPT
      BG_Mode7 = 7 ; 8bpp  EXTBG ---  ---  rot/scaling

      BGMODE_Setting .function Mode, isBG1Large, isBG2Large, isBG3Large, isBG4Large, isBG3Priority
      .endf bits((int(isBG4Large) << 7) | (int(isBG3Large) << 6) | (int(isBG2Large) << 5) | (int(isBG1Large) << 4) | (int(isBG3Priority) << 3) | Mode)

        ; Example:
        ; lda #BGMODE_Setting(BG_Mode0, false, false, false, false, false)

    ; Created: 0.01
    ; Updated: 0.01
    MOSAIC .byte ? ; $002106

      ; Setting this will create a mosaic
      ; effect for the enabled backgrounds,
      ; where each pixel becomes a block of
      ; n+1 x n+1 pixels. Setting this value
      ; to 3, for example, will turn 8x8 tiles
      ; into large 4x4 tiles, pulling color data
      ; from every other pixel. Setting this
      ; value to 7 will create tiles that are
      ; full of the upper-leftmost color.

      ; Bitmasks:

      MOSAIC_Size       = bits(%11110000)

      MOSAIC_BG4_Enable = bits(%00001000)

      MOSAIC_BG3_Enable = bits(%00000100)

      MOSAIC_BG2_Enable = bits(%00000010)

      MOSAIC_BG1_Enable = bits(%00000001)

      ; Helpers:

      MOSAIC_Setting .function Size, BG1Enable, BG2Enable, BG3Enable, BG4Enable
      .endf bits((((Size - 1) << 4) & MOSAIC_Size) | (int(BG4Enable) << 3) | (int(BG3Enable) << 2) | (int(BG2Enable) << 1) | int(BG1Enable))

        ; Example:
        ; Turns BG1 tiles into solid 8x8 blocks of color
        ; lda #MOSAIC_Setting(8, true, false, false, false)

    ; Created: 0.01
    ; Updated: 0.01
    BG1SC .byte ? ; $002107
    BG2SC .byte ? ; $002108
    BG3SC .byte ? ; $002109
    BG4SC .byte ? ; $00210A

      ; These registers determine where in VRAM
      ; each background tilemap layer begins, along
      ; with the shape/size of the background.

      ; Bitmasks:

      BGSC_Address = bits(%11111100)

        ; This value is in $800-byte steps

      BGSC_Size = bits(%00000011)

        ; This determines the shape/size of the BG layer.

      ; Helpers:

      BGSC_32x32 = 0
      BGSC_64x32 = 1
      BGSC_32x64 = 2
      BGSC_64x64 = 3

      BGSC_Setting .function Address, Size
      .endf bits((((Address >> 11) << 2) & BGSC_Address) | (Size & BGSC_Size))

        ; Example:
        ; lda #BGSC_Setting($F800, BGSC_64x64)

    ; Created: 0.01
    ; Updated: 0.01
    BG12NBA .byte ? ; $00210B
    BG34NBA .byte ? ; $00210C

      ; These registers determine where in VRAM
      ; the tile graphics for each BG layer begin.

      ; Bitmasks:

      BG12NBA_BG2_Address = bits(%11110000)

      BG12NBA_BG1_Address = bits(%00001111)

      BG34NBA_BG4_Address = bits(%11110000)

      BG34NBA_BG3_Address = bits(%00001111)

        ; These values are in $2000 byte steps.

      ; Helpers:

      BG12NBA_Setting .function BG1Address, BG2Address
      .endf bits((((BG2Address >> 13) << 4) & BG12NBA_BG2_Address) | ((BG1Address >> 13) & BG12NBA_BG1_Address))

      BG34NBA_Setting .function BG3Address, BG4Address
      .endf bits((((BG4Address >> 13) << 4) & BG12NBA_BG4_Address) | ((BG3Address >> 13) & BG12NBA_BG3_Address))

        ; Example:
        ; lda #BG12NBA_Setting($0000, $2000)

    .union

    ; Created: 0.01
    ; Updated: 0.01
    BG1HOFS .byte ? ; $00210D
    M7HOFS .byte ? ; $00210D

    .endu

    .union

    ; Created: 0.01
    ; Updated: 0.01
    BG1VOFS .byte ? ; $00210E
    M7VOFS .byte ? ; $00210E

    .endu

    ; Created: 0.01
    ; Updated: 0.01
    BG2HOFS .byte ? ; $00210F
    BG2VOFS .byte ? ; $002110
    BG3HOFS .byte ? ; $002111
    BG3VOFS .byte ? ; $002112
    BG4HOFS .byte ? ; $002113
    BG4VOFS .byte ? ; $002114

      ; These register are actually 10-bits
      ; long, and must be written to twice:
      ; First write, lower 8 bits
      ; Second write, upper 2 bits

      ; Bitmasks for word-length buffers

      BGOFS_Unused = bits(%1111110000000000)

      BGOFS_Scroll = bits(%0000001111111111)

      ; Helpers for word-length buffers:

      BGOFS_Setting .function Scroll
      .endf bits(Scroll & BGOFS_Scroll)

        ; Example:
        ; lda #BGOFS_Setting(100)

    ; Created: 0.01
    ; Updated: 0.01
    VMAIN .byte ? ; $002115

      ; This register determines how the VRAM address
      ; is incremented after accesses.

      ; Bitmasks:

      VMAIN_IncrementMode = bits(%10000000)

        ; If this bit is set, address will
        ; increment after accessing the high byte
        ; of the word rather than the low byte.

      VMAIN_Unused        = bits(%01110000)

      VMAIN_Translation   = bits(%00001100)

        ; This value temporarily rotates the
        ; lower 8, 9, or 10 bits of the VRAM
        ; address on access by 3.

      VMAIN_Step          = bits(%00000011)

        ; This value determines how the VRAM
        ; address will be incremented after accesses.

      ; Helpers:

      VMAIN_TranslationNone  = 0
      VMAIN_Translation8Bit  = 1
      VMAIN_Translation9Bit  = 2
      VMAIN_Translation10Bit = 3

      VMAIN_Step1     = 0
      VMAIN_Step32    = 1
      VMAIN_Step128_1 = 2
      VMAIN_Step128_2 = 3

      VMAIN_Setting .function IncrementOnHighAccesses=false, Translation=VMAIN_TranslationNone, Step=VMAIN_Step1
      .endf bits((int(IncrementOnHighAccesses) << 7) | ((Translation << 2) & VMAIN_Translation) | (Step & VMAIN_Step))

        ; Example:
        ; ; Most VRAM DMA transfers use these settings
        ; lda #VMAIN_Setting(true, VMAIN_TranslationNone, VMAIN_Step1)

    ; Created: 0.01
    ; Updated: 0.01
    VMADD .word ? ; $002116

      ; This register controls the address
      ; of VRAM accesses.

      ; Helpers:

      VMADD_Setting .function Address
      .endf bits(Address >> 1)

        ; Example:
        ; lda #VMADD_Setting($A000)

    ; Created: 0.01
    ; Updated: 0.01
    VMDATA .word ? ; $002118

      ; This register is what is written to
      ; in order to write to the address given
      ; by VMADD.

    ; Created: 0.01
    ; Updated: 0.01
    M7SEL .byte ? ; $00211A

      ; This register determines how tiles
      ; outside the 128x128 tile area are drawn.
      ; It also sets whether the screen is H/V
      ; flipped.

      M7SEL_Screen         = bits(%11000000)

        ; This value determines how things
        ; outside of the 128x128 tilemap are rendered.

      M7SEL_Unused         = bits(%00111100)

      M7SEL_VerticalFlip   = bits(%00000010)

      M7SEL_HorizontalFlip = bits(%00000001)

        ; These bits flip the screen.

      ; Helpers:

      M7SEL_WrapWithin       = 0
      M7SEL_WrapWithin2      = 1 ; Same as 0
      M7SEL_OuterTransparent = 2
      M7SEL_OuterTile0       = 3

      M7SEL_Setting .function Screen, isVerticalFlipped, isHorzontalFlipped
      .endf bits(((Screen << 6) & M7SEL_Screen) | (int(isVerticalFlipped) << 1) | int(isHorzontalFlipped))

        ; Example:
        ; lda #M7SEL_Setting(M7SEL_OuterTile0, true, true)

    ; Created: 0.01
    ; Updated: 0.01
    M7A .byte ? ; $00211B
    M7B .byte ? ; $00211C
    M7C .byte ? ; $00211D
    M7D .byte ? ; $00211E

      ; These are rotation/scaling parameters
      ; for BG mode 7. They are actually 16-bit
      ; and must be written to twice.

      ; In modes 0-6 or mode 7 during VBlank
      ; M7A and M7B can be used as multiplication
      ; registers:

      ; M7A: 16-bit (8-bit write lower then upper) multiplicand
      ; M7B: 8-bit multiplier

      ; The result can be read instantly from MPY ($002134),
      ; unlike WRMPY.

    ; Created: 0.01
    ; Updated: 0.01
    M7X .byte ? ; $00211F
    M7Y .byte ? ; $002120

      ; These specify the center of rotation/scaling.
      ; They are actually 13-bit and must be written to
      ; twice.

    ; Created: 0.01
    ; Updated: 0.01
    CGADD .byte ? ; $002121

      ; This register is the address of CGRAM (palette)
      ; accesses. Instead of being an address, it is simply
      ; a color number.

      ; Helpers:

      CGADD_Setting .function Color
      .endf bits(Color)

    ; Created: 0.01
    ; Updated: 0.01
    CGDATA .byte ? ; $002122

      ; This is the register to read/write
      ; from/to CGRAM. It is automatically incremented
      ; on access and the upper/lower flipflop is reset
      ; on writing to CGADD.

    ; Created: 0.01
    ; Updated: 0.01
    W12SEL .byte ? ; $002123

      ; This register controls settings for
      ; the window masks for BG layers 1 and 2.

      ; Bitmasks:

      W12SEL_BG2_Window2Enable = bits(%10000000)
      W12SEL_BG2_Window2Invert = bits(%01000000)
      W12SEL_BG2_Window1Enable = bits(%00100000)
      W12SEL_BG2_Window1Invert = bits(%00010000)
      W12SEL_BG1_Window2Enable = bits(%00001000)
      W12SEL_BG1_Window2Invert = bits(%00000100)
      W12SEL_BG1_Window1Enable = bits(%00000010)
      W12SEL_BG1_Window1Invert = bits(%00000001)

      ; Helpers:

      W12SEL_Setting .function BG1Window1Enable=false, BG1Window1Invert=false, BG1Window2Enable=false, BG1Window2Invert=false, BG2Window1Enable=false, BG2Window1Invert=false, BG2Window2Enable=false, BG2Window2Invert=false
      .endf bits((int(BG2Window2Enable) << 7) | (int(BG2Window2Invert) << 6) | (int(BG2Window1Enable) << 5) | (int(BG2Window1Invert) << 4) | (int(BG1Window2Enable) << 3) | (int(BG1Window2Invert) << 2) | (int(BG1Window1Enable) << 1) | int(BG1Window1Invert))

        ; Example:
        ; lda #W12SEL_Setting(true, false, true, false, false, false, false, false)

    ; Created: 0.01
    ; Updated: 0.01
    W34SEL .byte ? ; $002124

      ; This register controls settings for
      ; the window masks for BG layers 3 and 4.

      ; Bitmasks:

      W34SEL_BG4_Window2Enable = bits(%10000000)
      W34SEL_BG4_Window2Invert = bits(%01000000)
      W34SEL_BG4_Window1Enable = bits(%00100000)
      W34SEL_BG4_Window1Invert = bits(%00010000)
      W34SEL_BG3_Window2Enable = bits(%00001000)
      W34SEL_BG3_Window2Invert = bits(%00000100)
      W34SEL_BG3_Window1Enable = bits(%00000010)
      W34SEL_BG3_Window1Invert = bits(%00000001)

      ; Helpers:

      W34SEL_Setting .function BG3Window1Enable=false, BG3Window1Invert=false, BG3Window2Enable=false, BG3Window2Invert=false, BG4Window1Enable=false, BG4Window1Invert=false, BG4Window2Enable=false, BG4Window2Invert=false
      .endf bits((int(BG4Window2Enable) << 7) | (int(BG4Window2Invert) << 6) | (int(BG4Window1Enable) << 5) | (int(BG4Window1Invert) << 4) | (int(BG3Window2Enable) << 3) | (int(BG3Window2Invert) << 2) | (int(BG3Window1Enable) << 1) | int(BG3Window1Invert))

        ; Example:
        ; lda #W34SEL_Setting(true, false, true, false, false, false, false, false)

    ; Created: 0.01
    ; Updated: 0.01
    WOBJSEL .byte ? ; $002125

      ; This register controls settings for
      ; the window masks for the object layer and math windows.

      ; Bitmasks:

      WOBJSEL_Math_Window2Enable = bits(%10000000)
      WOBJSEL_Math_Window2Invert = bits(%01000000)
      WOBJSEL_Math_Window1Enable = bits(%00100000)
      WOBJSEL_Math_Window1Invert = bits(%00010000)
      WOBJSEL_OBJ_Window2Enable  = bits(%00001000)
      WOBJSEL_OBJ_Window2Invert  = bits(%00000100)
      WOBJSEL_OBJ_Window1Enable  = bits(%00000010)
      WOBJSEL_OBJ_Window1Invert  = bits(%00000001)

      ; Helpers:

      WOBJSEL_Setting .function OBJWindow1Enable=false, OBJWindow1Invert=false, OBJWindow2Enable=false, OBJWindow2Invert=false, MathWindow1Enable=false, MathWindow1Invert=false, MathWindow2Enable=false, MathWindow2Invert=false
      .endf bits((int(MathWindow2Enable) << 7) | (int(MathWindow2Invert) << 6) | (int(MathWindow1Enable) << 5) | (int(MathWindow1Invert) << 4) | (int(OBJWindow2Enable) << 3) | (int(OBJWindow2Invert) << 2) | (int(OBJWindow1Enable) << 1) | int(OBJWindow1Invert))

        ; Example:
        ; lda #WOBJSEL_Setting(true, false, true, false, false, false, false, false)

    ; Created: 0.01
    ; Updated: 0.01
    WH0 .byte ? ; $002126

      ; This is the left boundary
      ; of the first window.

    ; Created: 0.01
    ; Updated: 0.01
    WH1 .byte ? ; $002127

      ; This is the right boundary
      ; of the first window.

    ; Created: 0.01
    ; Updated: 0.01
    WH2 .byte ? ; $002128

      ; This is the left boundary
      ; of the second window.

    ; Created: 0.01
    ; Updated: 0.01
    WH3 .byte ? ; $002129

      ; This is the right boundary
      ; of the second window.

    ; Created: 0.01
    ; Updated: 0.01
    WBGLOG .byte ? ; $00212A
    WOBJLOG .byte ? ; $00212B

      ; Thesr register determines how
      ; windows are merged for the purpose
      ; of window logic.

      ; Bitmasks:

      WBGLOG_BG4_Logic = bits(%11000000)
      WBGLOG_BG3_Logic = bits(%00110000)
      WBGLOG_BG2_Logic = bits(%00001100)
      WBGLOG_BG1_Logic = bits(%00000011)

      WOBJLOG_Unused     = bits(%11110000)
      WOBJLOG_Math_Logic = bits(%00001100)
      WOBJLOG_OBJ_Logic  = bits(%00000011)

        ; These values set the logic for each layer
        ; if both windows are enabled on that layer.

      ; Helpers:

      WLOG_ORR  = 0
      WLOG_AND  = 1
      WLOG_XOR  = 2
      WLOG_XNOR = 3

      WBGLOG_Setting .function BG1=WLOG_ORR, BG2=WLOG_ORR, BG3=WLOG_ORR, BG4=WLOG_ORR
      .endf bits(((BG4 << 6) & WBGLOG_BG4_Logic) | ((BG3 << 4) & WBGLOG_BG3_Logic) | ((BG2 << 2) & WBGLOG_BG2_Logic) | (BG1 & WBGLOG_BG1_Logic))

      WOBJLOG_Setting .function OBJ=WLOG_ORR, Math=WLOG_ORR
      .endf bits(((Math << 2) & WOBJLOG_Math_Logic) | (OBJ & WOBJLOG_OBJ_Logic))

    ; Created: 0.01
    ; Updated: 0.01
    TM .byte ? ; $00212C
    TS .byte ? ; $00212D
    TMW .byte ? ; $00212E
    TSW .byte ? ; $00212F

      ; TM enables main screen layers.
      ; TS enables subscreen layers.

      ; TMW disables main screen layers within windows.
      ; TSW disables subscreen layers within windows.

      ; Bitmasks:

      TM_Unused     = bits(%11100000)

      TM_OBJ_Enable = bits(%00010000)
      TM_BG4_Enable = bits(%00001000)
      TM_BG3_Enable = bits(%00000100)
      TM_BG2_Enable = bits(%00000010)
      TM_BG1_Enable = bits(%00000001)

        ; Setting these to zero will disable
        ; the main screen for that layer.

      TS_Unused     = bits(%11100000)

      TS_OBJ_Enable = bits(%00010000)
      TS_BG4_Enable = bits(%00001000)
      TS_BG3_Enable = bits(%00000100)
      TS_BG2_Enable = bits(%00000010)
      TS_BG1_Enable = bits(%00000001)

        ; Setting these to zero will disable
        ; the subscreen for that layer.

      TMW_Unused     = bits(%11100000)

      TMW_OBJ_Disable = bits(%00010000)
      TMW_BG4_Disable = bits(%00001000)
      TMW_BG3_Disable = bits(%00000100)
      TMW_BG2_Disable = bits(%00000010)
      TMW_BG1_Disable = bits(%00000001)

        ; Setting these to one will disable
        ; the main screen for that layer
        ; if it within the window area.

      TSW_Unused     = bits(%11100000)

      TSW_OBJ_Disable = bits(%00010000)
      TSW_BG4_Disable = bits(%00001000)
      TSW_BG3_Disable = bits(%00000100)
      TSW_BG2_Disable = bits(%00000010)
      TSW_BG1_Disable = bits(%00000001)

        ; Setting these to one will disable
        ; the subscreen for that layer
        ; if it within the window area.

      ; Helpers:

      T_Setting .function BG1, BG2, BG3, BG4, OBJ
      .endf bits((int(OBJ << 4)) | (int(BG4) << 3) | (int(BG3) << 2) | (int(BG2) << 1) | (int(BG1)))

        ; Example:
        ; lda #T_Setting(true, true, true, false, false)

    ; Created: 0.01
    ; Updated: 0.01
    CGWSEL .byte ? ; $002130

      ; This register controls part of
      ; color math logic.

      ; Bitmasks:

      CGWSEL_ForceBlack  = bits(%11000000)

        ; This value controls whether the
        ; main screen will be forced to be black.

      CGWSEL_MathEnable  = bits(%00110000)

        ; This value controls whether color
        ; math will be used.

      CGWSEL_Unused      = bits(%00001100)

      CGWSEL_SubScreen   = bits(%00000010)

        ; Setting this bit enables the subscreen.

      CGWSEL_DirectColor = bits(%00000001)

        ; Setting this bit will use Direct Color
        ; (256 colors) instead of palettes.

      ; Helpers:

      CGWSEL_BlackNever   = 0
      CGWSEL_BlackOutside = 1
      CGWSEL_BlackInside  = 2
      CGWSEL_BlackAlways  = 3

      CGWSEL_MathAlways  = 0
      CGWSEL_MathInside  = 1
      CGWSEL_MathOutside = 2
      CGWSEL_MathNever   = 3

      CGWSEL_Setting .function DirectColor, SubScreen, MathSetting, ForcedBlackSetting
      .endf bits(((ForcedBlackSetting << 6) & CGWSEL_ForceBlack) | ((MathSetting << 4) & CGWSEL_MathEnable) | (int(SubScreen) << 1) | (int(DirectColor)))

    ; Created: 0.01
    ; Updated: 0.01
    CGADSUB .byte ? ; $002131

      ; This register controls which
      ; operation is performed for color
      ; math and which layers have color
      ; math applied.

      ; Bitmasks:

      CGADSUB_Operation = bits(%10000000)

        ; When set, color math becomes main - sub
        ; instead of main + sub.

      CGADSUB_Divide    = bits(%01000000)

        ; When set, the intensity of color math
        ; is halved.

      CGADSUB_BackdropEnable = bits(%00100000)
      CGADSUB_OBJEnable      = bits(%00010000)
      CGADSUB_BG4Enable      = bits(%00001000)
      CGADSUB_BG3Enable      = bits(%00000100)
      CGADSUB_BG2Enable      = bits(%00000010)
      CGADSUB_BG1Enable      = bits(%00000001)

        ; When set, applies color math
        ; to the main screen on these layers.

        ; Objects using OBJ palettes 0-3 never have
        ; color math applied to them.

      ; Helpers:

      CGADSUB_Add      = 0
      CGADSUB_Subtract = 1

      CGADSUB_Setting .function Operation=CGADSUB_Add, Divide=false, BG1, BG2, BG3, BG4, OBJ, Backdrop
      .endf bits(((Operation << 7) & CGADSUB_Operation) | (int(Divide) << 6) | (int(Backdrop) << 5) | (int(OBJ) << 4) | (int(BG4) << 3) | (int(BG3) << 2) | (int(BG2) << 1) | (int(BG1)))

        ; Example:
        ; To set color math for just objects at half intensity:
        ; lda #CGADSUB_Setting(CGADSUB_Add, true, false, false, false, false, true, false)

    ; Created: 0.01
    ; Updated: 0.01
    COLDATA .byte ? ; $002132

      ; This register can set
      ; the RGB intensities of the backdrop.

      ; You may need to write to this
      ; register up to three times to set
      ; the intensities of each channel.

      ; Bitmasks:

      COLDATA_ApplyBlue  = bits(%10000000)
      COLDATA_ApplyGreen = bits(%01000000)
      COLDATA_ApplyRed   = bits(%00100000)

        ; When these bits are set, the
        ; intensity is applied to that
        ; channel. If the bit is unset,
        ; the intensity for that channel
        ; remains unchanged.

      COLDATA_Intensity  = bits(%00011111)

       ; This is the value that the specified
       ; channel(s) will be set to.

      ; Helpers:

      COLDATA_Setting .function Intensity, ApplyRed, ApplyGreen, ApplyBlue
      .endf bits((int(ApplyBlue) << 7) | (int(ApplyGreen) << 6) | (int(ApplyRed) << 5) | (Intensity & COLDATA_Intensity))

        ; Example:
        ; To set the backdrop to solid green,
        ; you could do:
        ; lda #COLDATA_Setting(0, true, false, true)
        ; sta COLDATA ; This sets red and blue to 0
        ; lda #COLDATA_Setting(31, false, true, false)
        ; sta COLDATA ; This sets green to 31

    ; Created: 0.01
    ; Updated: 0.01
    SETINI .byte ? ; $002133

      ; This register controls some
      ; misc. screen settings.

      ; Bitmasks:

      SETINI_EXTSync      = bits(%10000000)
      SETINI_EXTBG        = bits(%01000000)
      SETINI_Unused       = bits(%00110000)
      SETINI_PsuedoHires  = bits(%00001000)
      SETINI_Overscan     = bits(%00000100)
      SETINI_OBJInterlace = bits(%00000010)
      SETINI_Interlace    = bits(%00000001)

      ; Helpers:

      SETINI_Setting .function EXTSync, EXTBG, PsuedoHires, Overscan, OBJInterlace, Interlace
      .endf bits((int(EXTSync) << 7) | (int(EXTBG) << 6) | (int(PsuedoHires) << 3) | (int(Overscan) << 2) | (int(OBJInterlace) << 1) | (int(Interlace)))

    ; Created: 0.01
    ; Updated: 0.01
    MPY .long ? ; $002134

      ; This is the signed 24-bit result
      ; of multiplication when using
      ; M7A and M7B to multiply. Unlike
      ; RDMPY, the result can be read
      ; immediately.

    ; Created: 0.01
    ; Updated: 0.01
    SLHV .byte ? ; $002137

      ; Reading from this register will
      ; update the horizontal/vertical
      ; counter latches with the current
      ; horizontal/vertical positions.

      ; The value read from this register
      ; is garbage.

    ; Created: 0.01
    ; Updated: 0.01
    RDOAM .byte ? ; $002138

      ; This register is OAMDATA but
      ; for reading rather than writing.

    ; Created: 0.01
    ; Updated: 0.01
    RDVRAM .word ? ; $002139

      ; This is like VMDATA but for reading
      ; rather than writing.

    ; Created: 0.01
    ; Updated: 0.01
    RDCGRAM .byte ? ; $00213B

      ; This is like CGDATA but for reading
      ; rather than writing.

    ; Created: 0.01
    ; Updated: 0.01
    OPHCT .byte ? ; $00213C
    OPVCT .byte ? ; $00213D

      ; These 9-bit (read twice) registers
      ; are set with screen coordinates after
      ; certain events:

      ; Reads to SLHV
      ; WRIO bit 7 is unset
      ; Lightgun triggers

      ; The latch bit in STAT78 is set by these
      ; events, too.

    ; Created: 0.01
    ; Updated: 0.01
    STAT77 .byte ? ; $00213E

      ; This register contains some PPU1 status
      ; information and the PPU1 version.

      ; Bitmasks:

      STAT77_OBJ_TimeOverflow  = bits(%10000000)

        ; Set when there are more than 8*34
        ; object pixels on a scanline.

      STAT77_OBJ_RangeOverflow = bits(%01000000)

        ; Set whenever there are more than 32
        ; objects on a scanline.

      STAT77_Slave             = bits(%00100000)

        ; Set when slave else master?

      STAT77_Unused            = bits(%00010000)

      STAT77_Version           = bits(%00001111)

        ; This is the version number of the
        ; PPU1.

    ; Created: 0.01
    ; Updated: 0.01
    STAT78 .byte ? ; $00213F

      ; This register contains some PPU2 status
      ; information and the PPU2 version.

      ; Bitmasks:

      STAT78_InterlaceFrame = bits(%10000000)

        ; When set, interlace occurs on the second
        ; rather that the first frame.

      STAT78_HVLatch        = bits(%01000000)

        ; Set whenever the H/V counters have new
        ; data latched. Reading from this register
        ; clears this bit and resets the counter access
        ; flipflops.

      STAT78_Unused         = bits(%00100000)

      STAT78_Region         = bits(%00010000)

        ; 0 for NTSC, 1 for PAL.

      STAT78_Version        = bits(%00001111)

        ; This is the version number of the PPU2.

  .endv ; PPU_REG_BASE

  .virtual APU_REG_BASE

    ; Created: 0.01
    ; Updated: 0.01
    APU00 .byte ? ; $002140
    APU01 .byte ? ; $002141
    APU02 .byte ? ; $002142
    APU03 .byte ? ; $002143

      ; These registers are for
      ; communicating with the APU.

      ; Writing to them will send
      ; data to the corresponding
      ; CPUIO# register on the APU.

      ; Reading from them will also
      ; grab data from the corresponding
      ; register.

      ; These registers are mirrored
      ; another 15 times.

    ; Created: 0.01
    ; Updated: 0.01
    APUM .brept 15

      Mirror00 .byte ?
      Mirror01 .byte ?
      Mirror02 .byte ?
      Mirror03 .byte ?

    .next

  .endv ; APU_REG_BASE

  .virtual WRAM_REG_BASE

    ; Created: 0.01
    ; Updated: 0.01
    WMDATA .byte ? ; $002180

      ; Reads/writes to this register
      ; access the WRAM location pointed
      ; to by WMADD. The address is automatically
      ; incremented on access.

    ; Created: 0.01
    ; Updated: 0.01
    WMADD .long ? ; $002181

      ; This 17-bit register contains
      ; the address for accessing WRAM.

  .endv ; WRAM_REG_BASE

  .virtual JOY_REG_BASE

    .union

    ; Created: 0.01
    ; Updated: 0.01
    JOYWR .byte ? ; $004016

      ; Bitmasks:

      JOYWR_Unused = bits(%11111000)

      JOYWR_OUT2   = bits(%00000100)

      JOYWR_OUT1   = bits(%00000010)

      JOYWR_OUT0   = bits(%00000001)

    ; Created: 0.01
    ; Updated: 0.01
    JOYA .byte ? ; $004016

      ; Bitmasks:

      JOYA_Unused = bits(%11111100)

      JOYA_IN1    = bits(%00000010)

      JOYA_IN2    = bits(%00000001)

    .endu

    ; Created: 0.01
    ; Updated: 0.01
    JOYB .byte ? ; $004017

      ; Bitmasks:

      JOYB_Unused = bits(%11100000)

      JOYB_IN4    = bits(%00010000)
      JOYB_IN3    = bits(%00001000)
      JOYB_IN2    = bits(%00000100)
      JOYB_IN1    = bits(%00000010)
      JOYB_IN0    = bits(%00000001)

  .endv ; JOY_REG_BASE

  .virtual CPU_W_REG_BASE

    ; Created: 0.01
    ; Updated: 0.01
    NMITIMEN .byte ? ; $004200

      ; This register enables/disables
      ; interrupts and automatic joypad
      ; reading.

      NMITIMEN_VBlank    = bits(%10000000)

        ; Enables VBlank interrupts when set.

      NMITIMEN_Unused2   = bits(%01000000)

      NMITIMEN_VCountIRQ = bits(%00100000)
      NMITIMEN_HCountIRQ = bits(%00010000)

        ; Setting these causes an IRQ
        ; to trigger when screen drawing gets to
        ; the set positions of HTIME/VTIME.

      NMITIMEN_Unused1   = bits(%00001110)

      NMITIMEN_Joypad    = bits(%00000001)

        ; Setting this bit allows for
        ; automatic population of the JOY#
        ; registers.

      ; Helpers:

      NMITIMEN_Setting .function Joypad, VBlank, HCountIRQ, VCountIRQ
      .endf bits((int(VBlank) << 7) | (int(VCountIRQ) << 6) | (int(HCountIRQ) << 5) | (int(Joypad)))

        ; Example:
        ; To enable automatic joypad reading and VBlank:
        ; lda #NMITIMEN_Setting(true, true, false, false)

    ; Created: 0.01
    ; Updated: 0.01
    WRIO .byte ? ; $004201

      ; This register is the writable
      ; controller I/O port.

      ; Bitmasks:

      WRIO_IO       = bits(%11111111)

        ; According to fullsnes,
        ; all bits are used for I/O

      WRIO_Joy2Pin6 = bits(%10000000)

        ; Also lightgun input.

      WRIO_Joy1Pin6 = bits(%01000000)

      ; Helpers:

      WRIO_Setting .function Joy1Pin6, Joy2Pin6, IO
      .endf bits((int(Joy2Pin6) << 7) | (int(Joy1Pin6) << 6) | IO)

    ; Created: 0.01
    ; Updated: 0.01
    WRMPYA .byte ? ; $004202
    WRMPYB .byte ? ; $004203

      ; These two 8-bit registers are
      ; the multiplicand and multiplier
      ; for unsigned multiplication.

      ; After setting WRMPYB, wait 8 clock
      ; cycles before reading the 16-bit result
      ; from RDMPY.

    ; Created: 0.01
    ; Updated: 0.01
    WRDIVA .word ? ; $004204
    WRDIVB .byte ? ; $004206

      ; These are the 16-bit dividend and
      ; 8-bit divisor for unsigned division.

      ; After setting WRDIVB, wait 16 clock
      ; cycles before reading the results from
      ; RDDIV (quotient) and RDMPY (remainder).

      ; Division by zero results in RDDIV = $FFFF,
      ; RDMPY = WRDIVA.

    ; Created: 0.01
    ; Updated: 0.01
    HTIME .word ? ; $004207

      ; Writing to this 9-bit register sets
      ; the horizontal scanline counter.

      ; When screen drawing reaches the specified
      ; pixel, the TIMEUP_IRQ flag will be set.

      ; 0 is the leftmost pixel.

    ; Created: 0.01
    ; Updated: 0.01
    VTIME .word ? ; $004209

      ; Writing to this 9-bit register sets
      ; the vertical scanline counter.

      ; When screen drawing reaches the specified
      ; pixel, the TIMEUP_IRQ flag will be set.

      ; 0 is the topmost pixel.

    ; Created: 0.01
    ; Updated: 0.01
    MDMAEN .byte ? ; $00420B

      ; This register begins DMA transfers for
      ; selected channels. Before writing to this
      ; register, you should set the other DMA-related
      ; registers.

      ; Channels are transfered in the order 0..7.

      ; Helpers:

      MDMAEN_Setting .function ChannelList
      .endf bits((1 << ChannelList) | ...)

    ; Created: 0.01
    ; Updated: 0.01
    HDMAEN .byte ? ; $00420C

      ; This register is like MDMAEN but
      ; is instead for HDMA.

      ; Helpers:

      HMDMAEN_Setting .function ChannelList
      .endf bits((1 << ChannelList) | ...)

    ; Created: 0.01
    ; Updated: 0.01
    MEMSEL .byte ? ; $00420D

      ; This register sets the memory
      ; access speed for 80-BF:8000-FFFF
      ; and C0-FF:0000-FFFF from 2.68MHz
      ; to 3.58MHz.

      ; This should probably only be set
      ; on resetting the SNES. Games using
      ; this faster speed should indicated
      ; such in their cartridge header.

      ; Bitmasks:

      MEMSEL_Unused = bits(%11111110)

      MEMSEL_Fast   = bits(%00000001)

        ; 0 = 2.68MHz, 1 = 3.58MHz

      ; Helpers:

      MEMSEL_Setting .function Fast=true
      .endf bits(int(Fast))

  .endv ; CPU_W_REG_BASE

  .virtual CPU_R_REG_BASE

    ; Created: 0.01
    ; Updated: 0.01
    RDNMI .byte ? ; $004210

      ; This register is for reading
      ; and acknowledging NMI (VBlank)
      ; interrupts. It also contains
      ; the CPU's version number.

      ; Under most situations it's
      ; unnecessary to acknowledge
      ; VBlank interrupts, as the flag
      ; is automatically reset after VBlank.

      ; Bitmasks:

      RDNMI_NMI_Flag = bits(%10000000)

        ; This flag is set at the beginning
        ; of VBlank and is reset at the end.
        ; Reading this register resets the flag.
        ; The flag is set even if NMIs are disabled.

      RDNMI_Unused   = bits(%01110000)

      RDNMI_Version  = bits(%00001111)

        ; This is the CPU version.

    ; Created: 0.01
    ; Updated: 0.01
    TIMEUP .byte ? ; $004211

      ; This register's flag is set
      ; when a H/V counter IRQ is triggered.
      ; Reading resets the flag.

      ; Bitmasks:

      TIMEUP_IRQ    = bits(%10000000)

      TIMEUP_Unused = bits(%01111111)

    ; Created: 0.01
    ; Updated: 0.01
    HVBJOY .byte ? ; $004212

      ; This register contains flags for
      ; HBlank and VBlank, along with a
      ; flag for when the joypad is busy.

      ; Bitmasks:

      HVBJOY_VBlank     = bits(%10000000)
      HVBJOY_HBlank     = bits(%01000000)

        ; These flags are set during their
        ; respective blanking periods.

      HVBJOY_Unused     = bits(%00111110)

      HVBJOY_JoypadBusy = bits(%00000001)

        ; When this flag is set the joypad
        ; registers shouldn't be read from.

    ; Created: 0.01
    ; Updated: 0.01
    RDIO .byte ? ; $004213

      ; This register is the read-only
      ; joypad IO port.

    ; Created: 0.01
    ; Updated: 0.01
    RDDIV .word ? ; $004214

      ; This is the 16-bit unsigned
      ; quotient after division using
      ; WRDIVA/WRDIVB.

    ; Created: 0.01
    ; Updated: 0.01
    RDMPY .word ? ; $004216

      ; This is the 16-bit unsigned remainder
      ; or product after division or
      ; multiplication using WRDIVA/WRDIVB
      ; or WRMPYA/WRMPYB.

    ; Created: 0.01
    ; Updated: 0.01
    JOY1 .word ? ; $004218
    JOY2 .word ? ; $00421A
    JOY3 .word ? ; $00421C
    JOY4 .word ? ; $00421E

      ; These are populated with joypad inputs
      ; every frame if NMITIMEN_Joypad is set.

      ; Bitmasks:

      JOY_B      = bits(%1000000000000000)
      JOY_Y      = bits(%0100000000000000)
      JOY_Select = bits(%0010000000000000)
      JOY_Start  = bits(%0001000000000000)
      JOY_Up     = bits(%0000100000000000)
      JOY_Down   = bits(%0000010000000000)
      JOY_Left   = bits(%0000001000000000)
      JOY_Right  = bits(%0000000100000000)
      JOY_A      = bits(%0000000010000000)
      JOY_X      = bits(%0000000001000000)
      JOY_L      = bits(%0000000000100000)
      JOY_R      = bits(%0000000000010000)
      JOY_Unused = bits(%0000000000001111)

      ; Helpers:

      JOY_Directions = (JOY_Up | JOY_Down | JOY_Left | JOY_Right)
      JOY_Shoulders  = (JOY_L | JOY_R)
      JOY_ABXY       = (JOY_B | JOY_Y | JOY_A | JOY_X)
      JOY_All        = (JOY_Directions | JOY_Shoulders | JOY_ABXY | JOY_Select | JOY_Start)

  .endv ; CPU_R_REG_BASE

  .virtual DMA_REG_BASE

    ; Created: 0.01
    ; Updated: 0.01
    ; DMAPx definitions

      ; Bitmasks:

      DMAP_TransferDirection = bits(%10000000)

        ; When set, DMA transfers are IO -> CPU,
        ; otherwise transfers are CPU -> IO.

      DMAP_HDMADirect        = bits(%01000000)

        ; When set, indicates that HDMA is
        ; using an indirect table rather than
        ; a direct table. Only for use with HDMA.

      DMAP_Unused            = bits(%00100000)

      DMAP_DMAABusStep       = bits(%00011000)

        ; This determines but the A bus
        ; (CPU) address is changed after each
        ; transfer unit. Only for use with DMA.

      DMAP_TransferMode      = bits(%00000111)

        ; This sets how many bytes are transfered
        ; per unit and how they're transfered.

      ; Helpers:

      ; DMAP_TransferDirection

      DMAP_CPUToIO = 0
      DMAP_IOToCPU = 1

      ; DMAP_ABusStep

      DMAP_Increment = 0
      DMAP_Fixed1    = 1
      DMAP_Decrement = 2
      DMAP_Fixed2    = 3

                     ; Size $21xx Address       Purpose

      DMAP_Mode0 = 0 ; 1    xx                  WRAM
      DMAP_Mode1 = 1 ; 2    xx   xx+1           VRAM
      DMAP_Mode2 = 2 ; 2    xx   xx             OAM/CGRAM
      DMAP_Mode3 = 3 ; 4    xx   xx   xx+1 xx+1 BGnxOFS, M7x
      DMAP_Mode4 = 4 ; 4    xx   xx+1 xx+2 xx+3 BGnSC/window/APU
      DMAP_Mode5 = 5 ; 4    xx   xx+1 xx   xx+1 
      DMAP_Mode6 = 6 ; 2    Mode2               See Mode 2
      DMAP_Mode7 = 7 ; 4    Mode3               See Mode 3

      ; Helpers:

      DMAP_DMA_Setting .function Direction, Step, Mode
      .endf bits(((Direction << 7) & DMAP_TransferDirection) | ((Step << 3) & DMAP_DMAABusStep) | (Mode & DMAP_TransferMode))

        ; Example:
        ; For DMA to VRAM:
        ; lda #DMAP_DMA_Setting(DMAP_CPUToIO, DMAP_Increment, DMAP_Mode1)

      DMAP_HDMA_Setting .function Direction, Indirect=false, Mode
      .endf bits(((Direction << 7) & DMAP_TransferDirection) | (int(Indirect) << 6) | (Mode & DMAP_TransferMode))

    ; Created: 0.01
    ; Updated: 0.01
    ; DASx definitions

      ; Bitmasks:

      DAS_DMA_Unused = bits(%111111110000000000000000)
      DAS_DMA_Count  = bits(%000000000111111111111111)

        ; For DMA, this is a 16-bit counter
        ; with a setting of 0 meaning $10000.

      DAS_HDMA_Address = bits(%111111111111111111111111)

        ; This is the 24-bit address of data
        ; when in indirect mode. Unused in direct mode.

    ; Created: 0.01
    ; Updated: 0.01
    ; NTRLx definitions

      ; Helpers:

      NTRL_Setting .function Count, Repeat=false
      .endf bits((int(Repeat) << 7) | Count)

    ; Created: 0.01
    ; Updated: 0.01
    DMA_IO .brept 8

      DMAP .byte ? ; $0043x0

        ; This register contains multiple
        ; DMA parameters.

      BBAD .byte ? ; $0043x1

        ; This register selects which B bus
        ; IO port to use. Being only a byte,
        ; you write PPU_REG_BASE - port to here.

      A1 .long ? ; $0043x2

        ; This is the current DMA
        ; address (offset incremented,
        ; bank doesn't increment) or the
        ; table start address for HDMA.

      DAS .long ? ; $0043x5

        ; This register is the number
        ; of bytes to transfer for DMA
        ; or the address for indirect HDMA.

      A2A .word ? ; $0043x8

        ; This is the current table
        ; address for HDMA. The bank is
        ; taken from A1.

      NTRL .byte ? ; $0043xA

        ; For HDMA, if the repeat
        ; flag is set, transfers
        ; NTRL & !$80 units in the same
        ; number of lines.

        ; If the repeat flag is unset,
        ; transfers one unit and then pauses
        ; for NTRL - 1 lines.

      UNUSED .byte ? ; $0043xB

        ; This byte is both unused
        ; and unchanging. It's usable
        ; as a fast RAM location, I guess.

      .fill 3 ; $0043xC-$0043xE

      MIRR .byte ? ; $0043xF

        ; This is a mirror of UNUSED.

    .next

  .endv ; DMA_REG_BASE

.endif ; GUARD_VOLTEDGE_IO_REGISTERS
