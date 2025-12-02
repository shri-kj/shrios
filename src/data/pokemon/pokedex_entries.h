// Stubbed Pokédex entries.
#include "global.h"
#include "pokedex.h"
#include "constants/pokedex.h"

const struct PokedexEntry gPokedexEntries[NATIONAL_DEX_COUNT] =
{
    [0 ... (NATIONAL_DEX_COUNT - 1)] =
    {
        .categoryName = _("NONE"),
        .height = 0,
        .weight = 0,
        .description = gDummyPokedexText,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
    },
};
