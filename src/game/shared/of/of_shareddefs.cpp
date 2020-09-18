// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: General definitions
// Author(s): ficool2, Fenteale, KaydemonLP, Ms
//

#include "cbase.h"
#include "of_shareddefs.h"

const char *g_aAmmoNames[] =
{
	"DUMMY AMMO", // This ammo is skipped
	"TF_AMMO_PRIMARY",
	"TF_AMMO_SECONDARY",
	"TF_AMMO_METAL",
	"TF_AMMO_GRENADES1",
	"TF_AMMO_GRENADES2",
	"TF_AMMO_GRENADES3"
};

const char *g_aTeamNames[] =
{
	"Unassigned",
	"Spectator",
	"Red",
	"Blue",
	"Mercenary"
};

const char* s_ValveMaps[][3] =
{
	"ctf_2fort", "2Fort", "#Gametype_CTF",
};

const char* s_CommunityMaps[][3] =
{
	"pl_borneo", "Borneo", "#Gametype_Escort",
};