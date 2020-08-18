// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Root Panel of VGUI elements
// Author(s): ficool2
//

#include "cbase.h"
#include "vgui_int.h"
#include "ienginevgui.h"
#include "of_rootpanel.h"
#include "vgui/IVGui.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

C_OFRootPanel *g_pRootPanel = NULL;

void VGUI_CreateClientDLLRootPanel( void )
{
	g_pRootPanel = new C_OFRootPanel( enginevgui->GetPanel( PANEL_CLIENTDLL ) );
}

void VGUI_DestroyClientDLLRootPanel( void )
{
	delete g_pRootPanel;
	g_pRootPanel = NULL;
}

vgui::VPANEL VGui_GetClientDLLRootPanel( void )
{
	return g_pRootPanel->GetVPanel();
}

C_OFRootPanel::C_OFRootPanel( vgui::VPANEL parent )
	: BaseClass( NULL, "OF Root Panel" )
{
	SetParent( parent );
	SetPaintEnabled( false );
	SetPaintBorderEnabled( false );
	SetPaintBackgroundEnabled( false );

	// This panel does post child painting
	SetPostChildPaintEnabled( true );

	// Make it screen sized
	SetBounds( 0, 0, ScreenWidth(), ScreenHeight() );

	// Ask for OnTick messages
	vgui::ivgui()->AddTickSignal( GetVPanel() );
}

C_OFRootPanel::~C_OFRootPanel( void )
{
}