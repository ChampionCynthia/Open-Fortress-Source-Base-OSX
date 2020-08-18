// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Clientside Manager
// Author(s): ficool2
//

#ifndef OF_CLIENTMODE_H
#define OF_CLIENTMODE_H
#ifdef _WIN32
#pragma once
#endif

#include "clientmode_shared.h"
#include "vgui/of_viewport.h"

class ClientModeOFNormal : public ClientModeShared 
{
	DECLARE_CLASS( ClientModeOFNormal, ClientModeShared );
	
public:
					ClientModeOFNormal();
	virtual			~ClientModeOFNormal();
	virtual void	InitViewport();
};


extern IClientMode *GetClientModeNormal();
extern ClientModeOFNormal* GetClientModeOFNormal();

#endif
