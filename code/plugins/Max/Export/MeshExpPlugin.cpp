// file: MeshExpPlugin.cpp

#include "stdafx.h"
#pragma hdrstop

#include "MeshExpUtility.h"


//-------------------------------------------------------------------
// Class Descriptor

class MeshExpUtilityClassDesc : public ClassDesc 
{
public:
	int 			IsPublic()					{ return 1; }
	void *			Create( BOOL loading )		{ return &U; }
	const WCHAR *	ClassName()					{ return L"S.T.A.L.K.E.R. Export"; }
	SClass_ID		SuperClassID()				{ return UTILITY_CLASS_ID; }
	Class_ID 		ClassID()					{ return Class_ID(EXP_UTILITY_CLASSID,0); }
	const WCHAR* 	Category()					{ return L"S.T.A.L.K.E.R. Export";  }
};

MeshExpUtility U;
MeshExpUtilityClassDesc MeshExpUtilityClassDescCD;

//-------------------------------------------------------------------
// DLL interface
HINSTANCE hInstance;
int controlsInit = FALSE;


BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID lpvReserved) 
{
	hInstance = hinstDLL;  // Hang on to this DLL's instance handle.

	if (!controlsInit)
	{
		controlsInit = TRUE;
		Core._initialize("S.T.A.L.K.E.R.Plugin", ELogCallback, FALSE);
		Core.SetPluginMode();
		FS._initialize(CLocatorAPI::flScanAppRoot, NULL, "xray_path.ltx");
		FPU::m64r(); // ����� ����� ���� �� ��������� ���������� � 0

		MaxSDK::Util::UseLanguagePackLocale();
		DisableThreadLibraryCalls(hInstance);
		InitCommonControls();
		ELog.Msg(mtInformation, "S.T.A.L.K.E.R. Object Export (ver. %d.%02d)", EXPORTER_VERSION, EXPORTER_BUILD);
		ELog.Msg(mtInformation, "-------------------------------------------------------");
	}

	switch(fdwReason) 
	{

		case DLL_PROCESS_ATTACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;

		case DLL_PROCESS_DETACH:
			Core._destroy();
			break;
		}
	return(TRUE);
}



__declspec( dllexport ) const WCHAR *
LibDescription() { return L"S.T.A.L.K.E.R. Mesh Export utility"; }


__declspec( dllexport ) int LibNumberClasses() {
	return 1;
}


__declspec( dllexport ) ClassDesc* LibClassDesc(int i) {
	switch(i) {
		case 0: return &MeshExpUtilityClassDescCD;
		default: return 0;
	}
}

__declspec( dllexport ) ULONG LibVersion() 
{
	return VERSION_3DSMAX; 
}

__declspec( dllexport ) int LibInitialize(void)
{
	return 1;
}

__declspec( dllexport ) int LibShutdown(void)
{
	return 1;
}