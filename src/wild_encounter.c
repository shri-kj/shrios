#include "global.h"
#include "wild_encounter.h"
#include "event_data.h"
#include "constants/species.h"

void DisableWildEncounters(bool8 disabled)
{
    (void)disabled;
}

bool8 StandardWildEncounter(u16 curMetatileBehavior, u16 prevMetatileBehavior)
{
    (void)curMetatileBehavior;
    (void)prevMetatileBehavior;
    return FALSE;
}

bool8 SweetScentWildEncounter(void)
{
    return FALSE;
}

bool8 DoesCurrentMapHaveFishingMons(void)
{
    return FALSE;
}

void FishingWildEncounter(u8 rod)
{
    (void)rod;
    gSpecialVar_Result = FALSE;
}

u16 GetLocalWildMon(bool8 *isWaterMon)
{
    if (isWaterMon)
        *isWaterMon = FALSE;
    return SPECIES_NONE;
}

u16 GetLocalWaterMon(void)
{
    return SPECIES_NONE;
}

bool8 UpdateRepelCounter(void)
{
    return FALSE;
}
