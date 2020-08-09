// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Player Movement
// Author(s): ficool2
//

#include "cbase.h"
#include "gamemovement.h"
#include "in_buttons.h"
#include "movevars_shared.h"

class COFGameMovement : public CGameMovement
{
public:
	DECLARE_CLASS( COFGameMovement, CGameMovement );

	COFGameMovement();
};

static COFGameMovement g_GameMovement;
IGameMovement *g_pGameMovement = ( IGameMovement * )&g_GameMovement;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR( CGameMovement, IGameMovement,INTERFACENAME_GAMEMOVEMENT, g_GameMovement );

