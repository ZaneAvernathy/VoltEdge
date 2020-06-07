
GUARD_VOLTEDGE_VANILLA_ITEMS :?= false
.if (!GUARD_VOLTEDGE_VANILLA_ITEMS)
  GUARD_VOLTEDGE_VANILLA_ITEMS := true

  VoltEdge_Vanilla_Items_Created = 0.01
  VoltEdge_Vanilla_Items_Updated = 0.02

  ; This is a list of the items in
  ; vanilla FE5.

  ; If the names chosen here are not to your
  ; liking, feel free to find and replace them
  ; with the translation of your preference,
  ; but I advise you to be careful with batch
  ; find/replacing short names like "Hel" or
  ; names with parts that are common to other
  ; definitions, like "Sword" or "Torch", to avoid
  ; accidentally affecting other things.

  ; Some items have been given extra text to
  ; differentiate them from other items, such
  ; as "Torch" and "TorchStaff".

  ; Also, as a disclaimer, the names of these
  ; values, which are just variables that
  ; make referring to these items easier,
  ; do not actually change any text that
  ; appears in game.

  ; Created: 0.01
  ; Updated: 0.02
  IronSword       = $01
  SteelSword      = $02
  SilverSword     = $03
  SlimSword       = $04
  IronBlade       = $05
  KillingEdge     = $06
  PoisonSword     = $07
  BerserkSword    = $08
  SleepSword      = $09
  BeoBlade        = $0A
  BlessedSword    = $0B
  LoptyrsBlade    = $0C
  BragisBlade     = $0D
  LightBrand      = $0E
  BraveSword      = $0F
  SwordOfKings    = $10
  EarthSword      = $11
  WindSword       = $12
  FireBrand       = $13
  VoltEdge        = $14
  ParagonSword    = $15
  Armorslayer     = $16
  Rapier          = $17
  Shortsword      = $18
  Longsword       = $19
  Greatsword      = $1A
  MasterSword     = $1B
  DarkEdge        = $1C
  MareetasBlade   = $1D
  BrokenSword     = $1E
  IronLance       = $1F
  SteelLance      = $20
  SilverLance     = $21
  SlimLance       = $22
  PoisonSpear     = $23
  Wyrmlance       = $24
  DarkLance       = $25
  BraveLance      = $26
  ShortLance      = $27
  LongLance       = $28
  Greatlance      = $29
  Javelin         = $2A
  MasterLance     = $2B
  Horseslayer     = $2C
  KillerLance     = $2D
  GaeBolg         = $2E
  Gungnir         = $2F
  BrokenLance     = $30
  IronAxe         = $31
  PoisonAxe       = $32
  SteelAxe        = $33
  SilverAxe       = $34
  HandAxe         = $35
  Hammer          = $36
  KillerAxe       = $37
  Pugi            = $38
  BraveAxe        = $39
  DevilAxe        = $3A
  BattleAxe       = $3B
  Halberd         = $3C
  MasterAxe       = $3D
  BrokenAxe       = $3E
  IronBow         = $3F
  SteelBow        = $40
  SilverBow       = $41
  PoisonBow       = $42
  KillerBow       = $43
  BraveBow        = $44
  Shortbow        = $45
  Longbow         = $46
  Greatbow        = $47
  MasterBow       = $48
  Ballista        = $49
  IronBallista    = $4A
  KillerBallista  = $4B
  PoisonBallista  = $4C
  BrokenBow       = $4D
  Fire            = $4E
  Elfire          = $4F
  Bolganone       = $50
  Valflame        = $51
  Thunder         = $52
  Dimevolt        = $53
  Thoron          = $54
  Mjolnir         = $55
  Wind            = $56
  Grafcalibur     = $57
  Tornado         = $58
  Forseti         = $59
  Light           = $5A
  Nosferatu       = $5B
  Aura            = $5C
  Jormungand      = $5D
  Fenrir          = $5E
  Hel             = $5F
  Loptyr          = $60
  Meteor          = $61
  Bolting         = $62
  Blizzard        = $63
  Venin           = $64
  Stone           = $65
  ForsetiInfinite = $66
  DrainedTome     = $67
  Heal            = $68
  Mend            = $69
  Recover         = $6A
  Physic          = $6B
  Fortify         = $6C
  Rescue          = $6D
  Warp            = $6E
  Restore         = $6F
  SilenceStaff    = $70
  Sleep           = $71
  TorchStaff      = $72
  ReturnStaff     = $73
  Hammerne        = $74
  ThiefStaff      = $75
  Watch           = $76
  Berserk         = $77
  Unlock          = $78
  Ward            = $79
  Rewarp          = $7A
  Kia             = $7B
  DrainedStaff    = $7C
  LuckRing        = $7D
  LifeRing        = $7E
  SpeedRing       = $7F
  MagicRing       = $80
  StrengthRing    = $81
  BodyRing        = $82
  ShieldRing      = $83
  SkillRing       = $84
  LegRing         = $85
  KnightCrest     = $86
  MasterSeal      = $87
  ChestKey        = $88
  DoorKey         = $89
  BridgeKey       = $8A
  Lockpick        = $8B
  StaminaDrink    = $8C
  Vulnerary       = $8D
  PureWater       = $8E
  Torch           = $8F
  Antidote        = $90
  MemberCard      = $91
  OdosScroll      = $92
  BaldursScroll   = $93
  HezulsScroll    = $94
  DainsScroll     = $95
  NovasScroll     = $96
  NeirsScroll     = $97
  UllursScroll    = $98
  TordosScroll    = $99
  ValasScroll     = $9A
  CedsScroll      = $9B
  BragisScroll    = $9C
  HeimsScroll     = $9D
  ParagonManual   = $9E
  AssailManual    = $9F
  BargainManual   = $A0
  VantageManual   = $A1
  WrathManual     = $A2
  AdeptManual     = $A3
  MiracleManual   = $A4
  NihilManual     = $A5
  SolManual       = $A6
  LunaManual      = $A7

.endif ; GUARD_VOLTEDGE_VANILLA_ITEMS
