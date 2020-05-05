
GUARD_VOLTEDGE_VANILLA_CHARACTERS :?= false
.if (!GUARD_VOLTEDGE_VANILLA_CHARACTERS)
  GUARD_VOLTEDGE_VANILLA_CHARACTERS := true

  VoltEdge.Vanilla.Characters .namespace

    Created = 0.01
    Updated = 0.01

  .endn

  ; This is a list of the characters
  ; in vanilla FE5. Many of the generic
  ; units are potentially mislabeled or
  ; are labeled inaccurately.

  ; If the names chosen here are not to your
  ; liking, feel free to find and replace them
  ; with the translation of your preference,
  ; but I advise you to be careful with batch
  ; find/replacing short names like "Pan" or
  ; names with parts that are common to other
  ; definitions, like "Hero" or "Manster", to avoid
  ; accidentally affecting other things.

  ; Also, as a disclaimer, the names of these
  ; values, which are just variables that
  ; make referring to these characters easier,
  ; do not actually change any text that
  ; appears in game.

  ; Created: 0.01
  ; Updated: 0.01
  Leif                  = $0001
  Finn                  = $0002
  Orsin                 = $0003
  Halvan                = $0004
  Eyvel                 = $0005
  Dagdar                = $0006
  Ralph                 = $0007
  Marty                 = $0008
  Ronan                 = $0009
  Miranda               = $000A
  Sapphie               = $000B
  Lara                  = $000C
  Brighton              = $000D
  Fergus                = $000E
  Eda                   = $000F
  Asvel                 = $0010
  Matria                = $0011
  Hicks                 = $0012
  Nanna                 = $0013
  Selphina              = $0014
  Dahlson               = $0015
  Callion               = $0016
  Shiva                 = $0017
  Pan                   = $0018
  Glade                 = $0019
  Kane                  = $001A
  Alba                  = $001B
  Robert                = $001C
  Fred                  = $001D
  Olwen                 = $001E
  CedChp23              = $001F
  Lithis                = $0020
  Karin                 = $0021
  Dean                  = $0022
  Shanam                = $0023
  Trude                 = $0024
  Tanya                 = $0025
  Linoan                = $0026
  Mischa                = $0027
  Salem                 = $0028
  Schroff               = $0029
  Mareeta               = $002A
  Tina                  = $002B
  GunterDialogue        = $002C
  Amalda                = $002D
  Conomore              = $002E
  Homer                 = $002F
  Dermott               = $0030
  Sarah                 = $0031
  Saias                 = $0032
  Raydrik               = $0033
  JuliusSaiasPortrait   = $0034
  Veld                  = $0035
  Weissmann             = $0036
  MansterArcher         = $0037
  Bakst                 = $0038
  Jabal                 = $0039
  LithisCrewPirate      = $003A
  LithisCrewHunter      = $003B
  LithisCrewWarrior     = $003C
  Lobos                 = $003D
  MansterArmoredBow     = $003E
  MansterThunderMage    = $003F
  MansterBishop1        = $0040
  Romeo                 = $0041
  Lucia                 = $0042
  Hubert                = $0043
  Cairpre               = $0044
  CedChp4x              = $0045
  Ishtar                = $0046
  ReinhardtDialogue     = $0047
  LithisCrewMyrmidon    = $0048
  Emily                 = $0049
  Muffy                 = $004A
  Vera                  = $004B
  Cliff                 = $004C
  Bowie                 = $004D
  Lina                  = $004E
  MercenaryMyrmidon1    = $004F
  Galzus                = $0050
  MansterCavalier       = $0051
  MansterPaladin        = $0052
  MansterBowKnight      = $0053
  MansterTroubadour     = $0054
  Eisenhowe             = $0055
  Hannibal              = $0056
  MansterAxeKnight      = $0057
  BanditBrigand1        = $0058
  BanditHunter          = $0059
  BanditWarrior         = $005A
  Rumaigh               = $005B
  Gomer                 = $005C
  Merloch               = $005D
  ThracianWyvernKnight1 = $005E
  ThracianMyrmidon      = $005F
  ThracianFighter       = $0060
  Altena                = $0061
  Travant               = $0062
  Largo                 = $0063
  MansterBallista       = $0064
  MansterArmoredAxe     = $0065
  Kempf                 = $0066
  Hortefeux             = $0067
  Rosa                  = $0068
  Sayla                 = $0069
  Peter                 = $006A
  Kolkho                = $006B
  Liszt                 = $006C
  Paulus                = $006D
  Baldach               = $006E
  ThracianArmoredLance  = $006F
  LeonsterLanceKnight   = $0070
  LeonsterBowKnight     = $0071
  Arion                 = $0072
  McCloy                = $0073
  Codha                 = $0074
  LoptyrianDarkMage1    = $0075
  Civilian1             = $0076
  ThiefEnemy1           = $0077
  MansterSniper         = $0078
  MercenaryCavalier     = $0079
  PriestEnemy           = $007A
  MercenaryMyrmidon2    = $007B
  Friege21stBallista    = $007C
  Schuper               = $007D
  Brooks                = $007E
  SilessiaPegasusRider1 = $007F
  Nicolov               = $0080
  Moore                 = $0081
  Mueller               = $0082
  Reinkoch              = $0083
  Parmann               = $0084
  Kant                  = $0085
  Gustav                = $0086
  DancerEnemy           = $0087
  SisterEnemy           = $0088
  Mannheim              = $0089
  Flavus                = $008A
  Seimtore              = $008B
  Zaumm                 = $008C
  Cohen                 = $008D
  Alphan                = $008E
  Orbis                 = $008F
  Farden                = $0090
  Coulter               = $0091
  Reinhardt             = $0092
  Nancy                 = $0093
  TahraCivilian1        = $0094
  TahraCivilian2        = $0095
  TahraCivilian3        = $0096
  TahraCivilian4        = $0097
  TahraCivilian5        = $0098
  TahraCivilian6        = $0099
  MercenaryMyrmidon3    = $009A
  FriegeBallista1       = $009B
  FriegeCavalier1       = $009C
  FriegeTroubadour1     = $009D
  FriegeArmoredBow1     = $009E
  FriegeArmoredLance1   = $009F
  FriegeArmoredAxe1     = $00A0
  FriegeArcher          = $00A1
  FriegeMage1           = $00A2
  RilkeKempfPortrait    = $00A3
  MansterArmoredLance   = $00A4
  Civilian2             = $00A5
  Civilian3             = $00A6
  Civilian4             = $00A7
  Civilian5             = $00A8
  Civilian6             = $00A9
  Civilian7             = $00AA
  MansterMage1          = $00AB
  MansterPriest1        = $00AC
  JuliusJuliaPortrait   = $00AD
  ManfroyMatriaPortrait = $00AE
  MansterMage2          = $00AF
  MansterMyrmidon       = $00B0
  PitfighterHero        = $00B1
  PitfighterWarrior     = $00B2
  PitfighterGeneral     = $00B3
  PitfighterSwordmaster = $00B4
  PitfighterBerserker   = $00B5
  MansterPriest2        = $00B6
  Bandole               = $00B7
  LoptyrianDarkDishop   = $00B8
  Truman                = $00B9
  MansterSoldier1       = $00BA
  BanditBerserker       = $00BB
  MercenaryMyrmidon4    = $00BC
  MagiSquadMyrmidon1    = $00BD
  MagiSquadFighter      = $00BE
  MagiSquadArcher       = $00BF
  MagiSquadMyrmidon2    = $00C0
  WyvernRiderEnemy      = $00C1
  BishopEnemy           = $00C2
  Dvorak                = $00C3
  MansterBishop2        = $00C4
  FriegeBallista2       = $00C5
  BanditBrigand2        = $00C6
  ThiefEnemy2           = $00C7
  ArcherEnemy1          = $00C8
  FriegeBishop1         = $00C9
  FriegeArmoredLance2   = $00CA
  FriegeArmoredBow2     = $00CB
  FriegeMage2           = $00CC
  BallistaEnemy         = $00CD
  FriegeArmoredAxe2     = $00CE
  Eichmann              = $00CF
  Zaille                = $00D0
  ArmoredSwordEnemy1    = $00D1
  SoldierEnemy          = $00D2
  FriegeBallista3       = $00D3
  Ilios                 = $00D4
  SilessiaPegasusRider2 = $00D5
  FriegeMageKnight1     = $00D6
  PaladinEnemy          = $00D7
  FriegeGreatKnight     = $00D8
  ArchKnightEnemy       = $00D9
  ArmoredSwordEnemy2    = $00DA
  FriegeSoldier1        = $00DB
  FriegeBowKnight1      = $00DC
  FriegeTroubadour2     = $00DD
  FriegeLanceKnight1    = $00DE
  FriegeCavalier2       = $00DF
  Civilian8             = $00E0
  MyrmidonEnemy1        = $00E1
  SwordmasterEnemy      = $00E2
  BerserkerEnemy1       = $00E3
  BerserkerEnemy2       = $00E4
  SilessiaPegasusRider3 = $00E5
  FriegeArmoredAxe3     = $00E6
  FriegeArmoredSword1   = $00E7
  FriegeArmoredLance3   = $00E8
  FriegeBallista4       = $00E9
  ArcherEnemy2          = $00EA
  MyrmidonEnemy2        = $00EB
  MyrmidonEnemy3        = $00EC
  Xavier                = $00ED
  XavierArmor1          = $00EE
  XavierArmor2          = $00EF
  XavierArmor3          = $00F0
  XavierArmor4          = $00F1
  XavierArmor5          = $00F2
  XavierArmor6          = $00F3
  XavierArmor7          = $00F4
  XavierArmor8          = $00F5
  Civilian9             = $00F6
  Civilian10            = $00F7
  Civilian11            = $00F8
  Civilian12            = $00F9
  Civilian13            = $00FA
  Civilian14            = $00FB
  Civilian15            = $00FC
  Civilian16            = $00FD
  FriegeSoldier2        = $00FE
  LeonsterSoldier       = $00FF
  FriegeBishop2         = $0100
  ResistanceMyrmidon1   = $0101
  Barath                = $0102
  FriegeGeneral1        = $0103
  FriegeArmoredSword2   = $0104
  FriegePriest1         = $0105
  FriegePoisonBallista  = $0106
  ThracianWyvernKnight2 = $0107
  FriegeMageKnight      = $0108
  FriegeArmoredAxe4     = $0109
  FriegeArchKnight1     = $010A
  FriegePaladin1        = $010B
  FriegeLanceKnight2    = $010C
  FriegeSniper          = $010D
  FriegeMyrmidon        = $010E
  FriegeBishop3         = $010F
  FriegeTroubadour3     = $0110
  FriegeMageKnight2     = $0111
  AlsterCavalier1       = $0112
  AlsterBowKnight       = $0113
  AlsterArchKnight      = $0114
  AlsterMageKnight      = $0115
  FriegePriest2         = $0116
  FriegeArchKnight2     = $0117
  FriegePaladin2        = $0118
  FriegeArmoredSword3   = $0119
  FriegeBowKnight2      = $011A
  Gelbenritter          = $011B
  FriegeGeneral2        = $011C
  MansterDukeKnight     = $011D
  MansterArchKnight     = $011E
  MansterGreatKnight    = $011F
  ThracianWyvernKnight3 = $0120
  Civilian17            = $0121
  Civilian18            = $0122
  Civilian19            = $0123
  Civilian20            = $0124
  Civilian21            = $0125
  Civilian22            = $0126
  Civilian23            = $0127
  Civilian24            = $0128
  Civilian25            = $0129
  Civilian26            = $012A
  Civilian27            = $012B
  Civilian28            = $012C
  Civilian29            = $012D
  Civilian30            = $012E
  Hero1                 = $012F
  Hero2                 = $0130
  Hero3                 = $0131
  SniperEnemy           = $0132
  Mus                   = $0133
  Tigris                = $0134
  TigrisDagdar          = $0135
  CanisSarah            = $0136
  Canis                 = $0137
  BovisGalzus           = $0138
  Bovis                 = $0139
  PorcusLithis          = $013A
  Porcus                = $013B
  DracoEyvel            = $013C
  Draco                 = $013D
  LoptyrianDarkMage     = $013E
  LoptyrianArmoredAxe   = $013F
  LoptyrianArmoredBow   = $0140
  LoptyrianArmoredLance = $0141
  MansterPoisonBallista = $0142
  RaydrikChl            = $0143
  MansterArmoredSword   = $0144
  MansterSoldier2       = $0145
  FriegeBallista5       = $0146
  ThracianArcher        = $0147
  ThracianBishop        = $0148
  ThracianWyvernRider   = $0149
  ThracianSoldier       = $014A
  AlsterCavalier2       = $014B
  PirateEnemy           = $014C
  ResistanceArcher1     = $014D
  ResistancePriest      = $014E
  ResistanceFighter     = $014F
  ResistanceArcher2     = $0150
  ResistanceMyrmidon2   = $0151
  AlsterCavalier3       = $0152
  MansterGeneral        = $0153
  LoptyrianDarkMage2    = $0154
  ThracianArmoredSword  = $0155
  Wolfe                 = $0156

.endif ; GUARD_VOLTEDGE_VANILLA_CHARACTERS
