
GUARD_VOLTEDGE_TERRAIN :?= false
.if (!GUARD_VOLTEDGE_TERRAIN)
  GUARD_VOLTEDGE_TERRAIN := true

  VoltEdge_Terrain_Created = 0.02
  VoltEdge_Terrain_Updated = 0.02

  ; Terrain macros

  ; Created: 0.02
  ; Updated: 0.02
  structTerrainEntry .struct MapEdge=?, Peak=?, Thicket=?, Cliff=?, Plains=?, Forest=?, Sea=?, River=?, Mountain=?, SandyLand=?, Castle=?, Fort=?, House1=?, Gate=?, Unknown1=?, Wasteland=?, Bridge=?, Lake=?, Village=?, Ruins=?, Unknown2=?, Unknown3=?, Convoy=?, Church1=?, House2=?, Road=?, Armory=?, Vendor=?, Arena=?, Floor=?, Unknown4=?, Throne=?, Door=?, Chest1=?, Exit=?, Pillar=?, Drawbridge=?, SecretShop=?, Unknown5=?, SandySoil=?, MagicFloor1=?, MagicFloor2=?, Church2=?, Chest2=?
    MapEdge     .char \MapEdge
    Peak        .char \Peak
    Thicket     .char \Thicket
    Cliff       .char \Cliff
    Plains      .char \Plains
    Forest      .char \Forest
    Sea         .char \Sea
    River       .char \River
    Mountain    .char \Mountain
    SandyLand   .char \SandyLand
    Castle      .char \Castle
    Fort        .char \Fort
    House1      .char \House1
    Gate        .char \Gate
    Unknown1    .char \Unknown1
    Wasteland   .char \Wasteland
    Bridge      .char \Bridge
    Lake        .char \Lake
    Village     .char \Village
    Ruins       .char \Ruins
    Unknown2    .char \Unknown2
    Unknown3    .char \Unknown3
    Convoy      .char \Convoy
    Church1     .char \Church1
    House2      .char \House2
    Road        .char \Road
    Armory      .char \Armory
    Vendor      .char \Vendor
    Arena       .char \Arena
    Floor       .char \Floor
    Unknown4    .char \Unknown4
    Throne      .char \Throne
    Door        .char \Door
    Chest1      .char \Chest1
    Exit        .char \Exit
    Pillar      .char \Pillar
    Drawbridge  .char \Drawbridge
    SecretShop  .char \SecretShop
    Unknown5    .char \Unknown5
    SandySoil   .char \SandySoil
    MagicFloor1 .char \MagicFloor1
    MagicFloor2 .char \MagicFloor2
    Church2     .char \Church2
    Chest2      .char \Chest2
  .ends

.endif ; GUARD_VOLTEDGE_TERRAIN
