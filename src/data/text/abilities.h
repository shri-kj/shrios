// Stubbed ability names and descriptions.
#include "global.h"
#include "constants/abilities.h"
#include "constants/pokemon.h"

const u8 gAbilityNames[ABILITIES_COUNT][ABILITY_NAME_LENGTH + 1] =
{
    [ABILITY_NONE] = _("-"),
};

const u8 *const gAbilityDescriptionPointers[ABILITIES_COUNT] =
{
    [ABILITY_NONE] = NULL,
};
