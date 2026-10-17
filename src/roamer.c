#include "global.h"
#include "event_data.h"
#include "item.h"
#include "random.h"
#include "overworld.h"
#include "field_specials.h"
#include "constants/abilities.h"
#include "constants/items.h"
#include "constants/maps.h"
#include "constants/region_map_sections.h"

// Despite having a variable to track it, the roamer is
// hard-coded to only ever be in map group 3
#define ROAMER_MAP_GROUP 3

enum
{
    MAP_GRP, // map group
    MAP_NUM, // map number
};

#define ROAMER (&gSaveBlock1Ptr->roamer)
EWRAM_DATA u8 sLocationHistory[3][2] = {};
EWRAM_DATA u8 sRoamerLocation[2] = {};

#define ___ MAP_NUM(MAP_UNDEFINED) // For empty spots in the location table

// Note: There are two potential softlocks that can occur with this table if its maps are
//       changed in particular ways. They can be avoided by ensuring the following:
//       - There must be at least 2 location sets that start with a different map,
//         i.e. every location set cannot start with the same map. This is because of
//         the while loop in RoamerMoveToOtherLocationSet.
//       - Each location set must have at least 3 unique maps. This is because of
//         the while loop in RoamerMove. In this loop the first map in the set is
//         ignored, and an additional map is ignored if the roamer was there recently.
//       - Additionally, while not a softlock, it's worth noting that if for any
//         map in the location table there is not a location set that starts with
//         that map then the roamer will be significantly less likely to move away
//         from that map when it lands there.
static const u8 sRoamerLocations[][7] = {
    {MAP_NUM(MAP_ROUTE1), MAP_NUM(MAP_ROUTE2), MAP_NUM(MAP_ROUTE21_NORTH), MAP_NUM(MAP_ROUTE22), ___, ___, ___},
    {MAP_NUM(MAP_ROUTE2), MAP_NUM(MAP_ROUTE1), MAP_NUM(MAP_ROUTE3), MAP_NUM(MAP_ROUTE22), ___, ___, ___},
    {MAP_NUM(MAP_ROUTE3), MAP_NUM(MAP_ROUTE2), MAP_NUM(MAP_ROUTE4), ___, ___, ___, ___},
    {MAP_NUM(MAP_ROUTE4), MAP_NUM(MAP_ROUTE3), MAP_NUM(MAP_ROUTE5), MAP_NUM(MAP_ROUTE9), MAP_NUM(MAP_ROUTE24), ___, ___},
    {MAP_NUM(MAP_ROUTE5), MAP_NUM(MAP_ROUTE4), MAP_NUM(MAP_ROUTE6), MAP_NUM(MAP_ROUTE7), MAP_NUM(MAP_ROUTE8), MAP_NUM(MAP_ROUTE9), MAP_NUM(MAP_ROUTE24)},
    {MAP_NUM(MAP_ROUTE6), MAP_NUM(MAP_ROUTE5), MAP_NUM(MAP_ROUTE7), MAP_NUM(MAP_ROUTE8), MAP_NUM(MAP_ROUTE11), ___, ___},
    {MAP_NUM(MAP_ROUTE7), MAP_NUM(MAP_ROUTE5), MAP_NUM(MAP_ROUTE6), MAP_NUM(MAP_ROUTE8), MAP_NUM(MAP_ROUTE16), ___, ___},
    {MAP_NUM(MAP_ROUTE8), MAP_NUM(MAP_ROUTE5), MAP_NUM(MAP_ROUTE6), MAP_NUM(MAP_ROUTE7), MAP_NUM(MAP_ROUTE10), MAP_NUM(MAP_ROUTE12), ___},
    {MAP_NUM(MAP_ROUTE9), MAP_NUM(MAP_ROUTE4), MAP_NUM(MAP_ROUTE5), MAP_NUM(MAP_ROUTE10), MAP_NUM(MAP_ROUTE24), ___, ___},
    {MAP_NUM(MAP_ROUTE10), MAP_NUM(MAP_ROUTE8), MAP_NUM(MAP_ROUTE9), MAP_NUM(MAP_ROUTE12), ___, ___, ___},
    {MAP_NUM(MAP_ROUTE11), MAP_NUM(MAP_ROUTE6), MAP_NUM(MAP_ROUTE12), ___, ___, ___, ___},
    {MAP_NUM(MAP_ROUTE12), MAP_NUM(MAP_ROUTE10), MAP_NUM(MAP_ROUTE11), MAP_NUM(MAP_ROUTE13), ___, ___, ___},
    {MAP_NUM(MAP_ROUTE13), MAP_NUM(MAP_ROUTE12), MAP_NUM(MAP_ROUTE14), ___, ___, ___, ___},
    {MAP_NUM(MAP_ROUTE14), MAP_NUM(MAP_ROUTE13), MAP_NUM(MAP_ROUTE15), ___, ___, ___, ___},
    {MAP_NUM(MAP_ROUTE15), MAP_NUM(MAP_ROUTE14), MAP_NUM(MAP_ROUTE18), MAP_NUM(MAP_ROUTE19), ___, ___, ___},
    {MAP_NUM(MAP_ROUTE16), MAP_NUM(MAP_ROUTE7), MAP_NUM(MAP_ROUTE17), ___, ___, ___, ___},
    {MAP_NUM(MAP_ROUTE17), MAP_NUM(MAP_ROUTE16), MAP_NUM(MAP_ROUTE18), ___, ___, ___, ___},
    {MAP_NUM(MAP_ROUTE18), MAP_NUM(MAP_ROUTE15), MAP_NUM(MAP_ROUTE17), MAP_NUM(MAP_ROUTE19), ___, ___, ___},
    {MAP_NUM(MAP_ROUTE19), MAP_NUM(MAP_ROUTE15), MAP_NUM(MAP_ROUTE18), MAP_NUM(MAP_ROUTE20), ___, ___, ___},
    {MAP_NUM(MAP_ROUTE20), MAP_NUM(MAP_ROUTE19), MAP_NUM(MAP_ROUTE21_NORTH), ___, ___, ___, ___},
    {MAP_NUM(MAP_ROUTE21_NORTH), MAP_NUM(MAP_ROUTE1), MAP_NUM(MAP_ROUTE20), ___, ___, ___, ___},
    {MAP_NUM(MAP_ROUTE22), MAP_NUM(MAP_ROUTE1), MAP_NUM(MAP_ROUTE2), MAP_NUM(MAP_ROUTE23), ___, ___, ___},
    {MAP_NUM(MAP_ROUTE23), MAP_NUM(MAP_ROUTE22), MAP_NUM(MAP_ROUTE2), ___, ___, ___, ___},
    {MAP_NUM(MAP_ROUTE24), MAP_NUM(MAP_ROUTE4), MAP_NUM(MAP_ROUTE5), MAP_NUM(MAP_ROUTE9), ___, ___, ___},
    {MAP_NUM(MAP_ROUTE25), MAP_NUM(MAP_ROUTE24), MAP_NUM(MAP_ROUTE9), ___, ___, ___, ___},
    {___, ___, ___, ___, ___, ___, ___}
};

#undef ___
#define NUM_LOCATION_SETS (ARRAY_COUNT(sRoamerLocations) - 1)
#define NUM_LOCATIONS_PER_SET (ARRAY_COUNT(sRoamerLocations[0]))

void ClearRoamerData(void)
{
    u32 i;
    *ROAMER = (struct Roamer){};
    sRoamerLocation[MAP_GRP] = 0;
    sRoamerLocation[MAP_NUM] = 0;
    for (i = 0; i < ARRAY_COUNT(sLocationHistory); i++)
    {
        sLocationHistory[i][MAP_GRP] = 0;
        sLocationHistory[i][MAP_NUM] = 0;
    }
}

#define GetRoamerSpecies() ({\
    u16 a;\
    switch (GetStarterSpecies())\
    {\
    default:\
        a = SPECIES_RAIKOU;\
        break;\
    case SPECIES_BULBASAUR:\
        a = SPECIES_ENTEI;\
        break;\
    case SPECIES_CHARMANDER:\
        a = SPECIES_SUICUNE;\
        break;\
    }\
    a;\
})

void CreateInitialRoamerMon(void)
{
    struct Pokemon * mon = &gEnemyParty[0];
    u16 species = GetRoamerSpecies();
    CreateMon(mon, species, 50, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
    ROAMER->species = species;
    ROAMER->level = 50;
    ROAMER->status = 0;
    ROAMER->active = TRUE;
    ROAMER->ivs = GetMonData(mon, MON_DATA_IVS);
    ROAMER->personality = GetMonData(mon, MON_DATA_PERSONALITY);
    ROAMER->hp = GetMonData(mon, MON_DATA_MAX_HP);
    ROAMER->cool = GetMonData(mon, MON_DATA_COOL);
    ROAMER->beauty = GetMonData(mon, MON_DATA_BEAUTY);
    ROAMER->cute = GetMonData(mon, MON_DATA_CUTE);
    ROAMER->smart = GetMonData(mon, MON_DATA_SMART);
    ROAMER->tough = GetMonData(mon, MON_DATA_TOUGH);
    sRoamerLocation[MAP_GRP] = ROAMER_MAP_GROUP;
    sRoamerLocation[MAP_NUM] = sRoamerLocations[Random() % NUM_LOCATION_SETS][0];
}

void InitRoamer(void)
{
    ClearRoamerData();
    CreateInitialRoamerMon();
}

void UpdateLocationHistoryForRoamer(void)
{
    sLocationHistory[2][MAP_GRP] = sLocationHistory[1][MAP_GRP];
    sLocationHistory[2][MAP_NUM] = sLocationHistory[1][MAP_NUM];

    sLocationHistory[1][MAP_GRP] = sLocationHistory[0][MAP_GRP];
    sLocationHistory[1][MAP_NUM] = sLocationHistory[0][MAP_NUM];

    sLocationHistory[0][MAP_GRP] = gSaveBlock1Ptr->location.mapGroup;
    sLocationHistory[0][MAP_NUM] = gSaveBlock1Ptr->location.mapNum;
}

void RoamerMoveToOtherLocationSet(void)
{
    u8 mapNum = 0;

    if (!ROAMER->active)
        return;

    sRoamerLocation[MAP_GRP] = ROAMER_MAP_GROUP;

    // Choose a location set that starts with a map
    // different from the roamer's current map
    while (1)
    {
        mapNum = sRoamerLocations[Random() % NUM_LOCATION_SETS][0];
        if (sRoamerLocation[MAP_NUM] != mapNum)
        {
            sRoamerLocation[MAP_NUM] = mapNum;
            return;
        }
    }
}


void RoamerMove(void)
{
    u8 locSet = 0;

    if ((Random() % 16) == 0)
    {
        RoamerMoveToOtherLocationSet();
    }
    else
    {
        if (!ROAMER->active)
            return;

        while (locSet < NUM_LOCATION_SETS)
        {
            // Find the location set that starts with the roamer's current map
            if (sRoamerLocation[MAP_NUM] == sRoamerLocations[locSet][0])
            {
                u8 mapNum;
                while (1)
                {
                    // Choose a new map (excluding the first) within this set
                    // Also exclude a map if the roamer was there 2 moves ago
                    mapNum = sRoamerLocations[locSet][(Random() % (NUM_LOCATIONS_PER_SET - 1)) + 1];
                    if (!(sLocationHistory[2][MAP_GRP] == ROAMER_MAP_GROUP
                       && sLocationHistory[2][MAP_NUM] == mapNum)
                       && mapNum != MAP_NUM(MAP_UNDEFINED))
                        break;
                }
                sRoamerLocation[MAP_NUM] = mapNum;
                return;
            }
            locSet++;
        }
    }
}

bool8 IsRoamerAt(u8 mapGroup, u8 mapNum)
{
    if (ROAMER->active && mapGroup == sRoamerLocation[MAP_GRP] && mapNum == sRoamerLocation[MAP_NUM])
        return TRUE;
    else
        return FALSE;
}

void CreateRoamerMonInstance(void)
{
    u32 status;
    u32 otid, personality, shinyValue;
    u16 rollsTotal = 1;
    u8 nature;
    struct Pokemon *mon = &gEnemyParty[0];

    ZeroEnemyPartyMons();
    otid = gSaveBlock2Ptr->playerTrainerId[0]
        | (gSaveBlock2Ptr->playerTrainerId[1] << 8)
        | (gSaveBlock2Ptr->playerTrainerId[2] << 16)
        | (gSaveBlock2Ptr->playerTrainerId[3] << 24);

    if (CheckBagHasItem(ITEM_SHINY_CHARM, 1))
        rollsTotal += SHINY_CHARM_ROLLS;
    if (CheckBagHasItem(ITEM_SHINY_CHARM, 2))
        rollsTotal += SHINY_CHARM_ROLLS / 2;
    if (FlagGet(FLAG_SYS_WHITE_FLUTE_ACTIVE) == TRUE
        || (!GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG)
        && (GetMonAbility(&gPlayerParty[0]) == ABILITY_ILLUMINATE || GetMonAbility(&gPlayerParty[0]) == ABILITY_ARENA_TRAP)))
        rollsTotal += WHITE_FLUTE_ABILITY_ROLLS;
    if (GET_SHINY_VALUE(otid, ROAMER->personality) >= SHINY_ODDS)
    {
        do
        {
            if (!GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG)
            && GetMonAbility(&gPlayerParty[0]) == ABILITY_SYNCHRONIZE
            && !(Random() % 2))
            {
                nature = GetMonData(&gPlayerParty[0], MON_DATA_PERSONALITY) % NUM_NATURES;
                do
                {
                    personality = Random32();
                }
                while (nature != personality % NUM_NATURES);
            }
            else
                personality = Random32();
            shinyValue = GET_SHINY_VALUE(otid, personality);
            if (rollsTotal > 0) rollsTotal--;
        } while(rollsTotal && shinyValue >= SHINY_ODDS);
        ROAMER->personality = personality;
    }
    CreateMonWithIVsPersonality(mon, ROAMER->species, ROAMER->level, ROAMER->ivs, ROAMER->personality);
// The roamer's status field is u8, but SetMonData expects status to be u32, so will set the roamer's status
// using the status field and the following 3 bytes (cool, beauty, and cute).
#ifdef BUGFIX
    status = ROAMER->status;
    SetMonData(mon, MON_DATA_STATUS, &status);
#else
    SetMonData(mon, MON_DATA_STATUS, &ROAMER->status);
#endif
    SetMonData(mon, MON_DATA_HP, &ROAMER->hp);
    SetMonData(mon, MON_DATA_COOL, &ROAMER->cool);
    SetMonData(mon, MON_DATA_BEAUTY, &ROAMER->beauty);
    SetMonData(mon, MON_DATA_CUTE, &ROAMER->cute);
    SetMonData(mon, MON_DATA_SMART, &ROAMER->smart);
    SetMonData(mon, MON_DATA_TOUGH, &ROAMER->tough);
}

bool8 TryStartRoamerEncounter(void)
{
    if (IsRoamerAt(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum) == TRUE && (Random() % 4) == 0)
    {
        CreateRoamerMonInstance();
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
void UpdateRoamerHPStatus(struct Pokemon *mon)
{
    ROAMER->hp = GetMonData(mon, MON_DATA_HP);
    ROAMER->status = GetMonData(mon, MON_DATA_STATUS);

    RoamerMoveToOtherLocationSet();
}

void SetRoamerInactive(void)
{
    ROAMER->active = FALSE;
}

void ResetRoamerActive(void)
{
    struct Pokemon mon;

    CreateMonWithIVsPersonality(&mon, ROAMER->species, ROAMER->level, ROAMER->ivs, ROAMER->personality);
    ROAMER->hp = GetMonData(&mon, MON_DATA_MAX_HP);
    ROAMER->status = 0;
    ROAMER->active = TRUE;
    RoamerMoveToOtherLocationSet();
}

void GetRoamerLocation(u8 *mapGroup, u8 *mapNum)
{
    *mapGroup = sRoamerLocation[MAP_GRP];
    *mapNum = sRoamerLocation[MAP_NUM];
}

u16 GetRoamerLocationMapSectionId(void)
{
    if (!ROAMER->active)
        return MAPSEC_NONE;
    return Overworld_GetMapHeaderByGroupAndId(sRoamerLocation[MAP_GRP], sRoamerLocation[MAP_NUM])->regionMapSectionId;
}
