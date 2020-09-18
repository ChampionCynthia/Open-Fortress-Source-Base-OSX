// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of the Map Info Panel
// Author(s): Ms
//

#include "cbase.h"
#include "of_mapinfomenu.h"
#include "vgui/ILocalize.h"

COFMapInfoMenu::COFMapInfoMenu( IViewPort* pViewPort ) : vgui::Frame( NULL, NULL )
{
	SetScheme( "ClientScheme" );
	SetTitleBarVisible( false );
	SetMinimizeButtonVisible( false );
	SetMaximizeButtonVisible( false );
	SetCloseButtonVisible( false );
	SetSizeable( false );
	SetMoveable( false );
	SetProportional( true );
	SetVisible( false );
	SetKeyBoardInputEnabled( true );
}

void COFMapInfoMenu::SetData( KeyValues* data )
{
}

//OFSTATUS: Complete
void COFMapInfoMenu::Reset()
{
	Update();
}

//OFSTATUS: Complete
void COFMapInfoMenu::Update()
{
	InvalidateLayout( false, true );
}

//OFSTATUS: Incomplete
void COFMapInfoMenu::ShowPanel( bool bShow )
{
	if ( IsVisible() != bShow )
	{
		if ( bShow )
		{
			InvalidateLayout( true, true );
			Activate();
			//CheckIntroState();
		}
		SetVisible( bShow );
	}
}

// OFSTATUS: INCOMPLETE, placeholder, not even sure if it should be here
const char* GetMapDisplayName( const char* map, bool unknown )
{
	return "2Fort";
}

// OFSTATUS: INCOMPLETE, placeholder, not even sure if it should be here
const char* GetMapType( const char* map )
{
	return "#Gametype_CTF";
}

// OFSTATUS: INCOMPLETE, this is supposed to load the mission briefing and pictures of the map
void COFMapInfoMenu::LoadMapPage()
{
}


// OFSTATUS: INCOMPLETE
void COFMapInfoMenu::ApplySchemeSettings( vgui::IScheme* pScheme )
{
	BaseClass::ApplySchemeSettings( pScheme );
	LoadControlSettings( "Resource/UI/MapInfoMenu.res" );
	SetMouseInputEnabled( true );
	//CheckIntroState();
	//CheckBackContinueButtons();

	char MapName[96];
	V_FileBase( engine->GetLevelName(), MapName, sizeof( MapName ) );
	V_strncpy( m_szMapName, MapName, sizeof( m_szMapName ) );
	V_strupr( m_szMapName );
	LoadMapPage();
	SetDialogVariable( "mapname", GetMapDisplayName( m_szMapName, false ) );
	SetDialogVariable( "gamemode", g_pVGuiLocalize->Find( GetMapType( m_szMapName ) ) );
}

// OFSTATUS: INCOMPLETE, this is supossed to do some arena checks and something related to the video intro
void COFMapInfoMenu::OnCommand( const char* command )
{
	if ( V_strcmp( command, "continue" ) == 0 )
	{
		engine->ClientCmd( "team_ui_setup" );
		Close();
	}
}