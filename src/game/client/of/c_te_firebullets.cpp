//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#include "cbase.h"
#include "of_fx_shared.h"
#include "of_shareddefs.h"
#include "c_of_player.h"
#include "c_basetempentity.h"
#include "of_weapon_base_gun.h"
#include <cliententitylist.h>


class C_TEFireBullets : public C_BaseTempEntity
{
public:
	DECLARE_CLASS( C_TEFireBullets, C_BaseTempEntity );
	DECLARE_CLIENTCLASS();

	virtual void	PostDataUpdate( DataUpdateType_t updateType );

public:
	int		m_iPlayer;
	Vector	m_vecOrigin;
	QAngle	m_vecAngles;
	int		m_iWeaponID;
	int		m_iMode;
	int		m_iSeed;
	float	m_flSpread;
};


void C_TEFireBullets::PostDataUpdate( DataUpdateType_t updateType )
{
	// Create the effect.
	
	m_vecAngles.z = 0;
	
	C_OFPlayer *pPlayer = dynamic_cast<C_OFPlayer*>( UTIL_PlayerByIndex(m_iPlayer+1));
	if( !pPlayer )
		return;

	C_OFWeaponBaseGun *pWeapon = dynamic_cast<C_OFWeaponBaseGun*> (pPlayer->GetActiveOFWeapon());
	if( !pWeapon )
		return;

	FX_FireBullets(						
		pWeapon,
		m_iPlayer+1,
		m_vecOrigin,
		m_vecAngles,
		m_iWeaponID,
		m_iMode,
		m_iSeed,
		m_flSpread,
		pWeapon->GetProjectileDamage(),
		false);
										  	

}


IMPLEMENT_CLIENTCLASS_EVENT( C_TEFireBullets, DT_TEFireBullets, CTEFireBullets );


BEGIN_RECV_TABLE_NOBASE(C_TEFireBullets, DT_TEFireBullets)
	RecvPropVector( RECVINFO( m_vecOrigin ) ),
	RecvPropFloat( RECVINFO( m_vecAngles[0] ) ),
	RecvPropFloat( RECVINFO( m_vecAngles[1] ) ),
	RecvPropInt( RECVINFO( m_iWeaponID ) ),
	RecvPropInt( RECVINFO( m_iMode ) ), 
	RecvPropInt( RECVINFO( m_iSeed ) ),
	RecvPropInt( RECVINFO( m_iPlayer ) ),
	RecvPropFloat( RECVINFO( m_flSpread ) ),
END_RECV_TABLE()