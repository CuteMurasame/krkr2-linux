//---------------------------------------------------------------------------
/*
	TVP2 ( T Visual Presenter 2 )  A script authoring tool
	Copyright (C) 2000 W.Dee <dee@kikyou.info> and contributors

	See details of license at "license.txt"
*/
//---------------------------------------------------------------------------
// Protection/DRM System Interface (Stub for Linux)
//---------------------------------------------------------------------------

#ifndef ProtectH
#define ProtectH

//---------------------------------------------------------------------------
// Protection system initialization
// This is a stub implementation for Linux builds
// The original protection system is platform-specific and not included
//---------------------------------------------------------------------------

inline bool TVPProtectInit(void)
{
	// No-op protection initialization for Linux
	// Always return true to allow system initialization to proceed
	return true;
}

inline void TVPUpdateLicense(void)
{
	// No-op license update for Linux
	// This function is called when protection initialization fails
}

//---------------------------------------------------------------------------
#endif
