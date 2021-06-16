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
#include "GameUI/IGameUI.h"

class ClientModeOFNormal : public ClientModeShared 
{
	DECLARE_CLASS( ClientModeOFNormal, ClientModeShared );
public:

	ClientModeOFNormal();
	virtual ~ClientModeOFNormal();

	virtual void Init();
	virtual void InitViewport();
	virtual void Shutdown();
	virtual void LevelInit(const char *newmap);
	virtual float GetViewModelFOV();
	virtual bool ShouldDrawViewModel();
	virtual bool ShouldDrawCrosshair();

private:

	//CHudMenuEngyBuild *m_pEngyBuildMenu;
	//CHudMenuEngyDestroy *m_pEngyDestroyMenu;
	//CHudMenuSpyDisguise *m_pSpyDisguiseMenu;
	//CTFFreezePanel *m_pFreezePanel;
	//CIteamQuickSwitchPanel *m_pQuickSwitchPanel;
	IGameUI *m_pGameUI;

};


extern IClientMode *GetClientModeNormal();
extern ClientModeOFNormal* GetClientModeOFNormal();

#endif
