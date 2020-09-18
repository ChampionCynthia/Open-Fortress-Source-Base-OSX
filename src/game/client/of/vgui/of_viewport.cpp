// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Clientside viewport
// Author(s): ficool2
//

#include "cbase.h"

#include <vgui_controls/Panel.h>
#include <vgui/ISurface.h>
#include <KeyValues.h>
#include <vgui/Cursor.h>
#include <vgui/IScheme.h>
#include <vgui/IVGui.h>
#include <vgui/ILocalize.h>
#include <vgui/VGUI.h>

#include "hud.h"

#include <baseviewport.h>
#include "of_viewport.h"
#include "of_textwindow.h"
#include "of_mapinfomenu.h"


void OFViewport::ApplySchemeSettings( vgui::IScheme *pScheme )
{
	BaseClass::ApplySchemeSettings( pScheme );

	gHUD.InitColors( pScheme );

	SetPaintBackgroundEnabled( false );
}

void OFViewport::CreateDefaultPanels( void )
{
	AddNewPanel( CreatePanelByName( "mapinfo" ), "mapinfo" );
	BaseClass::CreateDefaultPanels();
}

IViewPortPanel* OFViewport::CreatePanelByName( const char *szPanelName )
{
	IViewPortPanel* newpanel = NULL;

	if ( Q_strcmp( PANEL_INFO, szPanelName ) == 0 )
	{
		newpanel = new COFTextWindow( this );
	}
	else if ( Q_strcmp( "mapinfo", szPanelName ) == 0 )
	{
		newpanel = new COFMapInfoMenu( this );
	}
	else
	{
		newpanel = BaseClass::CreatePanelByName( szPanelName );
	}

	return newpanel; 
}