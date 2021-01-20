// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: General definitions
// Author(s): ficool2, Fenteale, KaydemonLP, Ms
//

#include "cbase.h"
#include "of_shareddefs.h"

const char *g_aWeaponModePrefix[] =
{
	"", // Primary parse doesnt use any prefixes
	"secondary_", // Primary parse doesnt use any prefixes
};

const char *g_aProjectileTypeNames[] =
{
	"projectile_none",
	"projectile_bullet",
	"projectile_rocket",
	"projectile_pipe",
	"projectile_pipe_remote",
	"projectile_syringe",
	"projectile_flare",
	"projectile_jar",
	"projectile_arrow",
	"projectile_flamerocket",
	"projectile_jar_milk",
	"projectile_healing_bolt",
	"projectile_energy_ball",
	"projectile_energy_ring",
	"projectile_stickyjumper",
	"projectile_cleaver",
	"projectile_unknown1",
	"projectile_cannonball",
	"projectile_ranger",
	"projectile_arrow_festive",
	"projectile_unknown2",
	"projectile_unknown3",
	"projectile_jarate_festive",
	"projectile_crossbow_festive",
	"projectile_jarate_bread",
	"projectile_madmilk_bread",
	"tf_projectile_grapplinghook",
	"tf_projectile_balloffire",
	"projectile_jar_gas",
};

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