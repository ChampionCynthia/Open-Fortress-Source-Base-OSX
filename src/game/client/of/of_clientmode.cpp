// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Clientside Manager
// Author(s): ficool2
//

#include "cbase.h"
#include "hud.h"
#include "of_clientmode.h"
#include "cdll_client_int.h"
#include "iinput.h"
#include "ivmodemanager.h"
#include "ivrenderview.h"
#include "panelmetaclassmgr.h"
#include "hud_element_helper.h"
#include "GameUI/IGameUI.h"

extern ConVar v_viewmodel_fov;
extern ConVar r_drawviewmodel;
ConVar v_viewmodel_fov_demo("v_viewmodel_fov_demo", "90", FCVAR_CHEAT);
ConVar default_fov( "default_fov", "90", FCVAR_CHEAT );

// See interface.h/.cpp for specifics:  basically this ensures that we actually Sys_UnloadModule the dll and that we don't call Sys_LoadModule 
//  over and over again.
static CDllDemandLoader g_GameUI("GameUI");

IClientMode *g_pClientMode = NULL;

class COFModeManager : public IVModeManager
{
public:
	virtual void	Init();
	virtual void	SwitchMode( bool commander, bool force ) {}
	virtual void	LevelInit( const char *newmap ) {}
	virtual void	LevelShutdown( void );
	virtual void	ActivateMouse( bool isactive ) {}
};

static COFModeManager g_ModeManager;
IVModeManager *modemanager = ( IVModeManager * )&g_ModeManager;

void COFModeManager::Init()
{
	g_pClientMode = GetClientModeNormal();
	
	PanelMetaClassMgr()->LoadMetaClassDefinitionFile( "scripts/vgui_screens.txt" );
}

void COFModeManager::LevelShutdown()
{
	g_pClientMode->LevelShutdown();
}

ClientModeOFNormal::ClientModeOFNormal()
{
	//m_pEngyBuildMenu = NULL;
	//m_pEngyDestroyMenu = NULL;
	//m_pSpyDisguiseMenu = NULL;
	//m_pFreezePanel = NULL;
	//m_pQuickSwitchPanel = NULL;
	m_pGameUI = NULL;
}

ClientModeOFNormal::~ClientModeOFNormal()
{
}

// OFSTATUS: INCOMPLETE
void ClientModeOFNormal::Init()
{
	//m_pEngyBuildMenu = (CHudMenuEngyBuild *)GET_HUDELEMENT(CHudMenuEngyBuild);
	//Assert(m_pEngyBuildMenu);

	//m_pEngyDestroyMenu = (CHudMenuEngyDestroy *)GET_HUDELEMENT(CHudMenuEngyDestroy);
	//Assert(m_pEngyDestroyMenu);

	//m_pSpyDisguiseMenu = (CHudMenuSpyDisguise *)GET_HUDELEMENT(CHudMenuSpyDisguise);
	//Assert(m_pSpyDisguiseMenu);

	//m_pFreezePanel = (CTFFreezePanel *)GET_HUDELEMENT(CTFFreezePanel);
	//Assert(m_pFreezePanel);

	//m_pQuickSwitchPanel = (CIteamQuickSwitchPanel *)GET_HUDELEMENT(CIteamQuickSwitchPanel);
	//Assert(m_pQuickSwitchPanel);

	CreateInterfaceFn gameUIFactory = g_GameUI.GetFactory();
	if (gameUIFactory)
	{
		m_pGameUI = (IGameUI *)gameUIFactory(GAMEUI_INTERFACE_VERSION, NULL);
		if (m_pGameUI)
		{
			//COFStatsSummaryPanel *pOFStatsPanel = GStatsSummaryPanel();
			//pOFStatsPanel->InvalidateLayout(false, true);
			//pOFStatsPanel->SetVisible(false);
			//pOFStatsPanel->MakePopup(false, false);
			//m_pGameUI->SetLoadingBackgroundDialog(pOFStatsPanel->GetVPanel());

			//CHudMainMenuOverride *pPanel = gViewPortInterface->FindPanelByName("MainMenuOverride");
			//if (pPanel)
			//{}
		}
	}

	// buuuunch of stuff going on here...

	BaseClass::Init();
}

// OFSTATUS: INCOMPLETE
void DestroyStatsSummaryPanel()
{
	//if (g_pOFStatsSummaryPanel)
	//{
		//delete g_pOFStatsSummaryPanel;
		//g_pOFStatsSummaryPanel = NULL;
	//}
}

// OFSTATUS: COMPLETE
void ClientModeOFNormal::Shutdown()
{
	DestroyStatsSummaryPanel();
}

// OFSTATUS: COMPLETE
void ClientModeOFNormal::InitViewport()
{
	m_pViewport = new OFViewport();
	m_pViewport->Start( gameuifuncs, gameeventmanager );
}

ClientModeOFNormal g_ClientModeNormal;

IClientMode *GetClientModeNormal()
{
	return &g_ClientModeNormal;
}

ClientModeOFNormal* GetClientModeOFNormal()
{
	return static_cast< ClientModeOFNormal* >( GetClientModeNormal() );
}

// OFSTATUS: INCOMPLETE
void ClientModeOFNormal::LevelInit(const char *newmap)
{
	BaseClass::LevelInit(newmap);
	//field_0xF5 = 0
}

// OFSTATUS: COMPLETE
float ClientModeOFNormal::GetViewModelFOV()
{
	if (engine->IsPlayingDemo())
	{
		return v_viewmodel_fov_demo.GetFloat();
	}

	return v_viewmodel_fov.GetFloat();
}

// OFSTATUS: COMPLETE
bool ClientModeOFNormal::ShouldDrawViewModel()
{
	// OFTODO: requires cond system
	//COFPlayer *pOFPlayer = COFPlayer::GetLocalOFPlayer();
	//if (pOFPlayer && pOFPlayer->m_Shared.InCond(TF_COND_ZOOMED))
	//{
	//	return false;
	//}

	return r_drawviewmodel.GetBool();
}

// OFSTATUS: COMPLETE
bool ClientModeOFNormal::ShouldDrawCrosshair()
{
	// OFTODO: requires cond system
	//COFPlayer *pOFPlayer = COFPlayer::GetLocalOFPlayer();
	//if (pOFPlayer && pOFPlayer->m_Shared.InCond(TF_COND_ZOOMED))
	//{
	//	return false;
	//}

	return BaseClass::ShouldDrawCrosshair();
}