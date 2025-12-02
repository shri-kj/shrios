// Stubbed trainer table.
#include "global.h"
#include "constants/trainers.h"
#include "data.h"

const struct Trainer gTrainers[TRAINERS_COUNT] =
{
    [TRAINER_NONE] =
    {
        .partyFlags = 0,
        .partySize = 0,
        .trainerClass = 0,
        .encounterMusic_gender = 0,
        .trainerPic = 0,
        .trainerName = _("-"),
        .items = {0},
        .doubleBattle = FALSE,
        .aiFlags = 0,
        .party = { .NoItemDefaultMoves = gTrainerParty_Single },
    },
};
