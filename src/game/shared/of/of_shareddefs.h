// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: General definitions
// Author(s): ficool2, Fenteale, Kay
//

#include "shareddefs.h"

// OFSTATUS: INCOMPLETE  ( labeling )
enum OF_Collision_Group_t
{
	OF_COLLISION_GROUP_UNKNOWN20 = LAST_SHARED_COLLISION_GROUP,
	OF_COLLISION_GROUP_UNKNOWN21,
	OF_COLLISION_GROUP_UNKNOWN22,
	OF_COLLISION_GROUP_UNKNOWN23,
	// OFINFO: labelled as "TFCOLLISION_GROUP_ROCKETS" in public SDK code, shared/particlesystemquery.cpp
	OF_COLLISION_GROUP_ROCKETS,
	OF_COLLISION_GROUP_UNKNOWN25,
	OF_COLLISION_GROUP_PUMPKIN_BOMB,
	// OFINFO: this is called in FireRocket + FireArrow in CPointWeaponMimic, guessing its for projectiles?
	OF_COLLISION_GROUP_PROJECTILE,
};


// Sourced from sourcemod API
#define DMG_CRIT                DMG_ACID        // < Crits and minicrits
#define DMG_RADIUS_MAX          DMG_ENERGYBEAM  // < No damage falloff 
#define DMG_NOCLOSEDISTANCEMOD  DMG_POISON      // < Don't do damage falloff too close 
#define DMG_HALF_FALLOFF        DMG_RADIATION   // < 50% damage falloff
#define DMG_USEDISTANCEMOD      DMG_SLOWBURN    // < Do damage falloff 
#define DMG_IGNITE              DMG_PLASMA      // < Ignite victim 
#define DMG_USE_HITLOCATIONS    DMG_AIRBOAT     // < Do hit location damage (sniper rifle) 

#ifdef CLIENT_DLL
#define Shared_VarArgs VarArgs
#else
#define Shared_VarArgs UTIL_VarArgs
#endif

enum
{
	OF_TEAM_RED = FIRST_GAME_TEAM,
	OF_TEAM_BLUE,
	OF_TEAM_MERCENARY,

	OF_TEAM_COUNT
};

enum
{
	OF_WEAPON_MODE_PRIMARY = 0,
	OF_WEAPON_MODE_SECONDARY,
	OF_WEAPON_MODE_COUNT
};

enum
{
	OF_WEAPON_TYPE_PRIMARY = 0,
	OF_WEAPON_TYPE_SECONDARY,
	OF_WEAPON_TYPE_MELEE,
	OF_WEAPON_TYPE_GRENADE,
	OF_WEAPON_TYPE_BUILDING,
	OF_WEAPON_TYPE_PDA,
	OF_WEAPON_TYPE_ITEM1,
	OF_WEAPON_TYPE_ITEM2
};

// These values are approximate and gotten via limited testing
// using the override projectile type attribute in Live tf2
// couldn't get some of these to spawn, so for those i used the FireProjectile class as a reference
// however some i still couldnt figure out, those are marked as Unknown
// If you know a better way, feel free to update this
enum
{
	OF_PROJECTILE_TYPE_NONE = 0,		 // 0  "projectile_bullet"
	OF_PROJECTILE_TYPE_BULLET,           // 1  "projectile_bullet"
	OF_PROJECTILE_TYPE_ROCKET,           // 2  "projectile_rocket"
	OF_PROJECTILE_TYPE_PIPEBOMB,         // 3  "projectile_pipe"
	OF_PROJECTILE_TYPE_STICKYBOMB,       // 4  "projectile_pipe_remote"
	OF_PROJECTILE_TYPE_SYRINGE,          // 5  "projectile_syringe"
	OF_PROJECTILE_TYPE_FLARE,            // 6  "projectile_flare"
	OF_PROJECTILE_TYPE_JARATE,           // 7  "projectile_jar"
	OF_PROJECTILE_TYPE_ARROW,            // 8  "projectile_arrow"
	OF_PROJECTILE_TYPE_FLAMEROCKET,      // 9  Seems to be unused?
	OF_PROJECTILE_TYPE_MADMILK,          // 10 "projectile_jar_milk"
	OF_PROJECTILE_TYPE_CROSSBOW,         // 11 "projectile_healing_bolt"
	OF_PROJECTILE_TYPE_MANGLER,          // 12 "projectile_energy_ball"
	OF_PROJECTILE_TYPE_BISON,            // 13 "projectile_energy_ring" 
	OF_PROJECTILE_TYPE_STICKYJUMPER,     // 14 Defined only via items game
	OF_PROJECTILE_TYPE_CLEAVER,           // 15 "projectile_cleaver"
	OF_PROJECTILE_TYPE_UNKNOWN1,         // 16 
	OF_PROJECTILE_TYPE_CANNONBALL,       // 17 "projectile_cannonball"
	OF_PROJECTILE_TYPE_RANGER,           // 18 Defined only via items game
	OF_PROJECTILE_TYPE_ARROW_FESTIVE,    // 19 Defined only via items game
	OF_PROJECTILE_TYPE_UNKNOWN2,         // 20
	OF_PROJECTILE_TYPE_UNKNOWN3,         // 21
	OF_PROJECTILE_TYPE_JARATE_FESTIVE,   // 22 Defined only via items game
	OF_PROJECTILE_TYPE_CROSSBOW_FESTIVE, // 23 Defined only via items game
	OF_PROJECTILE_TYPE_JARATE_BREAD,     // 24 Defined only via items game
	OF_PROJECTILE_TYPE_MADMILK_BREAD,    // 25 Defined only via items game
	OF_PROJECTILE_TYPE_GRAPPLE,       	 // 26 "tf_projectile_grapplinghook"

	OF_PROJECTILE_TYPE_BALLOFFIRE,		 // 27? "tf_projectile_balloffire" Havent tried out projectile override in a while so these werent in my list
	OF_PROJECTILE_TYPE_GASPASSER,		 // 28? "projectile_jar_gas" 
	OF_PROJECTILE_TYPE_COUNT
};

extern const char *g_aWeaponModePrefix[OF_WEAPON_MODE_COUNT];
extern const char *g_aProjectileTypeNames[OF_PROJECTILE_TYPE_COUNT];

// Needs to match the array below
#define AMMONAME_FIRST 1
#define AMMONAME_LAST 7

//OFHACK: g_aAmmoNames should probably be an extern + defined somewhere but isn't
// (oh well, just bloats the exe a bit)

// No longer the case, did it properly and moved it to of_shareddefs.cpp now - Kay
extern const char *g_aAmmoNames[AMMONAME_LAST];
extern const char *g_aTeamNames[OF_TEAM_COUNT];

#define TF_DAMAGE_CRIT_MULTIPLIER	3
#define TF_GAMETYPE_ESCORT			3