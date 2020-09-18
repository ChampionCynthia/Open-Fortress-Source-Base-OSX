// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of the MOTD Panel
// Author(s): Ms
//
#include "cbase.h"
#include "of_textwindow.h"
#include "input.h"

// OFSTATUS: INCOMPLETE, missing animation/keybinding maps, and CExRichText
COFTextWindow::COFTextWindow( IViewPort* pViewPort ) : BaseClass( pViewPort )
{
	m_bCustomSvr = false;

//	this_00 = ( CExRichText* )operator.new( 1792 );
//	CExRichText::CExRichText( this_00, ( Panel* )this, "TFTextMessage" );
//	*( CExRichText** )( this->data + 12 ) = this_00;

	SetProportional( true );
}

// OFSTATUS: COMPLETE
void COFTextWindow::ApplySchemeSettings( vgui::IScheme* pScheme )
{
	BaseClass::ApplySchemeSettings( pScheme );
	if ( m_bCustomSvr )
	{
		LoadControlSettings( "Resource/UI/TextWindowCustomServer.res" );
	}
	else
	{
		LoadControlSettings( "Resource/UI/TextWindow.res" );
	}
	SetMouseInputEnabled( true );
}

// OFSTATUS: COMPLETE
void COFTextWindow::SetData( KeyValues* data )
{
	m_bCustomSvr = data->GetBool( "customsvr" );
	InvalidateLayout( false, true );
	BaseClass::SetData( data );
}

// OFSTATUS: INCOMPLETE
void COFTextWindow::OnCommand( const char* command )
{
	BaseClass::OnCommand( command );
	if ( strcmp( command, "okay" ) == 0 && !m_bCustomSvr )
	{
		m_pViewPort->ShowPanel( "mapinfo", true );
	}
}

// OFSTATUS: INCOMPLETE
void COFTextWindow::OnThink()
{
	CBasePlayer* pLocalPlayer = CBasePlayer::GetLocalPlayer();
	if ( pLocalPlayer != NULL )
	{
	//	*( byte* )( pLocalPlayer + 3640 ) = *( byte* )( pLocalPlayer + 3640 ) | 8;
	}
	BaseClass::OnThink();
}

// OFSTATUS: COMPLETE
void COFTextWindow::PaintBackground()
{
	return;
}

// OFSTATUS: COMPLETE
void COFTextWindow::ShowPanel( bool bShow )
{
	if ( IsVisible() != bShow  ) 
	{
		InvalidateLayout( true, true );
		BaseClass::ShowPanel( bShow );
		if ( m_pViewPort != NULL )
		{
			m_pViewPort->ShowBackGround( false );
		}
	}
}

// OFSTATUS: COMPLETE
void COFTextWindow::OnKeyCodePressed( vgui::KeyCode code )
{
	if ( code == JOYSTICK_FIRST_BUTTON || code == 171 )
	{
		OnCommand( "okay" );
		return;
	}
	BaseClass::OnKeyCodePressed( code );
}
