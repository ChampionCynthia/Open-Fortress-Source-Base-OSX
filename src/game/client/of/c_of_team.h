// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose:
// Author(s): Ms
#pragma once
#include "c_team.h"

class C_OFTeam : public C_Team
{
public:
	DECLARE_CLASS( C_OFTeam, C_Team );
	DECLARE_CLIENTCLASS()

	C_OFTeam();
	~C_OFTeam();

	virtual void ClientThink() override;
};