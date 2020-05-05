
GUARD_VOLTEDGE_SKILLS :?= false
.if (!GUARD_VOLTEDGE_SKILLS)
  GUARD_VOLTEDGE_SKILLS := true

  VoltEdge.Skills .namespace

    Created = 0.01
    Updated = 0.01

  .endn

  ; Created: 0.01
  ; Updated: 0.01
  ; Skill constants

    Skill1Dance     = $01
    Skill1Steal     = $02
    Skill1Immortal  = $04
    Skill1Bargain   = $08
    Skill1Renewal   = $10
    Skill1Mount     = $20
    Skill1MountMove = $40
    Skill1Unknown   = $80

    Skill2Adept     = $01
    Skill2Charm     = $02
    Skill2Unknown   = $04
    Skill2Miracle   = $08
    Skill2Vantage   = $10
    Skill2Assail    = $20
    Skill2Pavise    = $40
    Skill2Nihil     = $80

    Skill3Wrath     = $01
    Skill3Astra     = $02
    Skill3Luna      = $04
    Skill3Sol       = $08
    Skill3Paragon   = $10
    Skill3Scroll    = $20
    Skill3Brave     = $40
    Skill3Immortal  = $80

.endif ; GUARD_VOLTEDGE_SKILLS
