////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2016 RWS Inc, All Rights Reserved
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of version 2 of the GNU General Public License as published by
// the Free Software Foundation
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
//
// flagbase.h
// Project: Postal
//
//	History:
//	
//		06/30/97 BRH	Started this file to contain the base object for the
//							capture the flag mode.  When the flag meets the base, 
//							the game is complete.
//
//		07/12/97 BRH	Added m_u16FlagID to match flags with bases.
//
//		08/11/97 BRH	Added color variable which is loaded and saved.
//
////////////////////////////////////////////////////////////////////////////////
#ifndef FLAGBASE_H
#define FLAGBASE_H

#include "RSPiX.h"
#include "realm.h"
#include "Thing3d.h"

// CFlagbasebase is the base where the flag goes in capture the flag challenge levels
class CFlagbase : public CThing3d
{
//---------------------------------------------------------------------------
// Types, enums, etc.
//---------------------------------------------------------------------------
protected:

//---------------------------------------------------------------------------
// Variables
//---------------------------------------------------------------------------
public:
	CAnim3D*		m_panimCurBase;					// current animation for the base
	U16			m_u16FlagID;						// ID to match flag and base

protected:
	CAnim3D		m_animFlagWave;					// animation for the flag waving
	U16			m_u16Color;							// Color of base


	// Tracks file counter so we know when to load/save "common" data 
	static int16_t ms_sFileCount;

	// "Constant" values that we want to be able to tune using the editor
	static double ms_dInRange;				// In range to the base

	//---------------------------------------------------------------------------
	// Constructor(s) / destructor
	//---------------------------------------------------------------------------
protected:
	// Constructor
	CFlagbase(CRealm* pRealm) : CThing3d(pRealm, CFlagbaseID)
	{
		m_sSuspend = 0;
		m_dRot = 0;
		m_dX = m_dY = m_dZ = m_dVel = m_dAcc = 0;
		m_panimCur = NULL;
		m_sprite.m_pthing	= this;
		m_u16FlagID = 1;
		m_u16Color = 0;
	}

public:
	// Destructor
	~CFlagbase()
	{
		// Remove sprite from scene (this is safe even if it was already removed!)
		m_pRealm->m_scene.RemoveSprite(&m_sprite);
		m_pRealm->m_smashatorium.Remove(&m_smash);
		// Free resources
		FreeResources();
	}

//---------------------------------------------------------------------------
// Required static functions
//---------------------------------------------------------------------------
public:
	// Construct object
	// Returns 0 if successfull, non-zero otherwise
	// In:  Pointer to realm this object belongs to
	// Out: Pointer to new object
	static int16_t Construct(CRealm* pRealm, CThing** ppNew)	
	{
		int16_t sResult = 0;
		*ppNew = new CFlagbase(pRealm);
		if (*ppNew == 0)
		{
			sResult = -1;
			TRACE("CFlagbase::Construct(): Couldn't construct CFlagbase (that's a bad thing)\n");
		}
		return sResult;
	}

//---------------------------------------------------------------------------
// Required virtual functions (implimenting them as inlines doesn't pay!)
//---------------------------------------------------------------------------
public:
	// Load object (should call base class version!)
	
	// Returns 0 if successfull, non-zero otherwise
	// In:  File to load from
	// In:  True for edit mode, false otherwise
	// In:  File count (unique per file, never 0)
	// In:  Version of file format to load.
	int16_t Load(RFile* pFile, bool bEditMode, int16_t sFileCount, uint32_t ulFileVersion);

	// Save object (should call base class version!)

	// Returns 0 if successfull, non-zero otherwise
	// In:  File to save to
	// In:  File count (unique per file, never 0)
	int16_t Save(RFile* pFile, int16_t sFileCount);

	// Startup object
	// Returns 0 if successfull, non-zero otherwise
	int16_t Startup(void);

	// Shutdown object
	// Returns 0 if successfull, non-zero otherwise
	int16_t Shutdown(void);

	// Update object
	void Update(void);

	// Called by editor to init new object at specified position
	
	// Returns 0 if successfull, non-zero otherwise
	// In:  New x coord
	// In:  New y coord
	// In:  New z coord
	int16_t EditNew(int16_t sX, int16_t sY,	int16_t sZ);

	// Called by editor to modify object
	// Returns 0 if successfull, non-zero otherwise
	int16_t EditModify(void);

	// Called by editor to move object to specified position
	// Returns 0 if successfull, non-zero otherwise
	// In:  New x coord
	// In:  New y coord
	// In:  New z coord
	int16_t EditMove(int16_t sX, int16_t sY, int16_t sZ);

	// Give Edit a rectangle around this object
	void EditRect(RRect* pRect);

	// Called by editor to get the hotspot of an object in 2D.
	// (virtual (Overridden here)).

	// Returns nothiing.
	// Out: X coord of 2D hotspot relative to
	// EditRect() pos.
	// Out: Y coord of 2D hotspot relative to
	// EditRect() pos.
	void EditHotSpot(int16_t* psX, int16_t* psY);
							
//---------------------------------------------------------------------------
// Internal functions
//---------------------------------------------------------------------------
protected:
	// Get all required resources
	// Returns 0 if successfull, non-zero otherwise
	int16_t GetResources(void);
		
	// Free all resources
	// Returns 0 if successfull, non-zero otherwise
	int16_t FreeResources(void);

	// Initialize states, positions etc.
	int16_t Init(void);

	// Update the animation radius based on the current frame
	void UpdateRadius(void);

	// Message handling functions ////////////////////////////////////////////

	// Handles an Explosion_Message.
	// Override to implement additional functionality.
	// Call base class to get default functionality.
	
	// Returns nothing.
	// In:  Message to handle.
	virtual void OnExplosionMsg(Explosion_Message* pexplosionmsg);

	// Handles a Burn_Message.
	// Override to implement additional functionality.
	// Call base class to get default functionality.

	// Returns nothing
	// In:  Message to handle.
	virtual void OnBurnMsg(Burn_Message* pburnmsg);

};


#endif //FLAGBASE_H
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
