#include "cbase.h"

class COFTeamSpawn : public CBaseEntity
{
public:
	DECLARE_CLASS(COFTeamSpawn, CBaseEntity);
	DECLARE_DATADESC();

	void Activate();
};