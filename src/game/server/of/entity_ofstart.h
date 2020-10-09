// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: 
// Author(s): MaartenS11
//
#pragma once

class COFTeamSpawn : public CBaseEntity
{
public:
	DECLARE_CLASS(COFTeamSpawn, CBaseEntity);
	DECLARE_DATADESC();

	void Activate();
};
