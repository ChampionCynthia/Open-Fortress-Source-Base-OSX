// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of ClassData
// Author(s): KaydemonLP
//

#include "cbase.h"
#include "of_building_info.h"
#include "filesystem.h"
#include "of_shareddefs.h"

// RE: Why are the names of these hardcoded?
// It seems so odd considering a lot of other things use an array - Kay

CObjectInfo g_ObjectInfos[] =
{
	CObjectInfo( "OBJ_DISPENSER" ),
	CObjectInfo( "OBJ_TELEPORTER" ),
	CObjectInfo( "OBJ_SENTRYGUN" ),
	CObjectInfo( "OBJ_ATTACHMENT_SAPPER" )
};

CObjectInfo::CObjectInfo( const char *pObjectName )
{
	m_szObjectName = pObjectName;
}

CObjectInfo::~CObjectInfo()
{
	delete[] (m_szClassName);
	delete[] (m_szStatusName);
	delete[] (m_szBuilderWeaponName);
	delete[] (m_szBuilderPlacementString);
	delete[] (m_szIconActive);
	delete[] (m_szIconInactive);
	delete[] (m_szIconMenu);
	delete[] (m_szViewmodel);
	delete[] (m_szPlayermodel);
	delete[] (m_szExplodeSound);
	delete[] (m_szUpgradeSound);
	delete[] (m_szExplodeEffect);
}

void LoadObjectInfos( IBaseFileSystem *pFileSystem )
{
	KeyValues *pObjectInfos = new KeyValues( "Object descriptions" );

	char *szFilepath = "scripts/objects.txt";

	if ( !pObjectInfos->LoadFromFile( pFileSystem, szFilepath, "GAME" ) )
	{
		// SpewFileInfo((IBaseFileSystem *)pIVar3,(char *)0x0,(char *)param_1,pKVar7);

		Error( "Can't open %s for object info.", szFilepath );
		pObjectInfos->deleteThis();
		return;
	}
	else 
	{
		for ( int i = 0; i < sizeof(g_ObjectInfos); i++ )
		{
			KeyValues *pObject = pObjectInfos->FindKey( g_ObjectInfos[i].m_szObjectName );
			if( !pObject ) 
			{
				// SpewFileInfo((IBaseFileSystem *)0x0,(char *)this,(char *)param_1,pKVar7);

				Error( "Missing section '%s' from %s.", g_ObjectInfos[i].m_szObjectName, szFilepath );

				pObject->deleteThis();
				return;
			}
			g_ObjectInfos[i].m_flBuildTime = pObject->GetFloat( "BuildTime", -999.0 );
			g_ObjectInfos[i].m_iMaxObjects = pObject->GetInt( "MaxObjects", -999 );
			g_ObjectInfos[i].m_iCost = pObject->GetInt( "Cost", -999 );
			g_ObjectInfos[i].m_flCostMultiplier = pObject->GetFloat( "CostMultiplier", -999.0 );
			g_ObjectInfos[i].m_flUpgradeDuration = pObject->GetFloat( "UpgradeDuration", -999.0 );
			g_ObjectInfos[i].m_iUpgradeCost = pObject->GetInt( "UpgradeCost", -999 );
			g_ObjectInfos[i].m_iMaxUpgradeLevel = pObject->GetInt( "MaxUpgradeLevel", -999 );
			g_ObjectInfos[i].m_iSlot = pObject->GetInt( "SelectionSlot", -999 );
			g_ObjectInfos[i].m_iBuildCount = pObject->GetInt( "BuildCount", -999 );
			g_ObjectInfos[i].m_iPosition = pObject->GetInt( "SelectionPosition", -999 );

			// RE: OH MY GOD - Kay
			if( g_ObjectInfos[i].m_flBuildTime == -999.0 
				&& g_ObjectInfos[i].m_flBuildTime == -999.0
				&& g_ObjectInfos[i].m_iMaxObjects == -999
				&& g_ObjectInfos[i].m_iCost == -999
				&& g_ObjectInfos[i].m_flCostMultiplier == -999.0
				&& g_ObjectInfos[i].m_flUpgradeDuration == -999.0
				&& g_ObjectInfos[i].m_iUpgradeCost == -999
				&& g_ObjectInfos[i].m_iMaxUpgradeLevel == -999
				&& g_ObjectInfos[i].m_iSlot == -999
				&& g_ObjectInfos[i].m_iBuildCount == -999
				&& g_ObjectInfos[i].m_iPosition == -999 )
			{
				// SpewFileInfo((IBaseFileSystem *)pIVar5,(char *)this,(char *)param_1,pKVar7);
				Error( "Missing data for object '%s' in %s.", g_ObjectInfos[i].m_szObjectName, szFilepath );
				pObject->deleteThis();
				return;
			}

			g_ObjectInfos[i].m_szClassName = ReadAndAllocStringValue( pObject,"ClassName", "scripts/objects.txt" );
			g_ObjectInfos[i].m_szStatusName = ReadAndAllocStringValue( pObject,"StatusName", "scripts/objects.txt" );
			g_ObjectInfos[i].m_szBuilderWeaponName = ReadAndAllocStringValue( pObject, "BuilderWeaponName", "scripts/objects.txt" );
			g_ObjectInfos[i].m_szBuilderPlacementString = ReadAndAllocStringValue( pObject, "BuilderPlacementString", "scripts/objects.txt" );
			g_ObjectInfos[i].m_bSolidToPlayerMovement = pObject->GetInt( "SolidToPlayerMovement", 0 ) != 0;
			g_ObjectInfos[i].m_szIconActive = ReadAndAllocStringValue( pObject, "IconActive", "scripts/objects.txt" );
			g_ObjectInfos[i].m_szIconInactive = ReadAndAllocStringValue( pObject, "IconInactive", "scripts/objects.txt" );
			g_ObjectInfos[i].m_szIconMenu = ReadAndAllocStringValue( pObject, "IconMenu", "scripts/objects.txt" );
			g_ObjectInfos[i].m_bUseItemInfo = 0 < pObject->GetInt( "UseItemInfo" );
			g_ObjectInfos[i].m_szViewmodel = ReadAndAllocStringValue( pObject,"Viewmodel","scripts/objects.txt" );
			g_ObjectInfos[i].m_szPlayermodel = ReadAndAllocStringValue( pObject,"Playermodel","scripts/objects.txt" );
			g_ObjectInfos[i].m_iDisplayPriority = pObject->GetInt( "DisplayPriority" );
			g_ObjectInfos[i].m_szHudStatusIcon = ReadAndAllocStringValue( pObject, "HudStatusIcon", "scripts/objects.txt" );
			g_ObjectInfos[i].m_bVisibleInWeaponSelection = 0 < pObject->GetInt( "VisibleInWeaponSelection", 1 );
			g_ObjectInfos[i].m_szExplodeSound = ReadAndAllocStringValue( pObject, "ExplodeSound", "scripts/objects.txt" );
			g_ObjectInfos[i].m_szUpgradeSound = ReadAndAllocStringValue( pObject, "UpgradeSound", "scripts/objects.txt" );
			g_ObjectInfos[i].m_szExplodeEffect = ReadAndAllocStringValue( pObject, "ExplodeEffect", "scripts/objects.txt" );
			g_ObjectInfos[i].m_bAutoswitchTo = 0 < pObject->GetInt( "autoswitchto" );
			g_ObjectInfos[i].m_iMetalToDropInGibs = pObject->GetInt( "MetalToDropInGibs" );
			g_ObjectInfos[i].m_bRequiresOwnBuilder = pObject->GetBool( "RequiresOwnBuilder" );
			KeyValues *pAltModes = pObject->FindKey( "AltModes" );
			if( pAltModes ) 
			{
				for( int y = 0; y < 3; y++ )
				{
					KeyValues *pMode = pObject->FindKey( Shared_VarArgs( "AltMode%d", y ) );
					if( pMode ) 
					{
						g_ObjectInfos[i].m_ObjectModes[y].m_szStatusName1 = ReadAndAllocStringValue( pMode, "StatusName", "scripts/objects.txt" );
						g_ObjectInfos[i].m_ObjectModes[y].m_szModelName1 = ReadAndAllocStringValue( pMode, "ModeName", "scripts/objects.txt" );
						g_ObjectInfos[i].m_ObjectModes[y].m_szIconMenu1 = ReadAndAllocStringValue( pMode, "IconMenu", "scripts/objects.txt" );
					
						g_ObjectInfos[i].m_iAltModeCount = y - 1;
					}
				}
			}
		}
	}
}