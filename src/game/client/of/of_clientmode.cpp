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

ConVar default_fov( "default_fov", "90", FCVAR_CHEAT );

IClientMode *g_pClientMode = NULL;

class COFModeManager : public IVModeManager
{
public:
	virtual void	Init();
	virtual void	SwitchMode( bool commander, bool force ) {}
	virtual void	LevelInit( const char *newmap ) {}
	virtual void	LevelShutdown( void ) {}
	virtual void	ActivateMouse( bool isactive ) {}
};

static COFModeManager g_ModeManager;
IVModeManager *modemanager = ( IVModeManager * )&g_ModeManager;

void COFModeManager::Init()
{
	g_pClientMode = GetClientModeNormal();
	
	PanelMetaClassMgr()->LoadMetaClassDefinitionFile( "scripts/vgui_screens.txt" );
}

ClientModeOFNormal::ClientModeOFNormal()
{
}

ClientModeOFNormal::~ClientModeOFNormal()
{
}

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