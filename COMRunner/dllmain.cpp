#include "object.h"


typedef HRESULT(__stdcall* _DllGetClassObject)(REFCLSID rclsid, REFIID riid, LPVOID* ppv);

UINT g_uThreadFinished;
extern UINT g_uThreadFinished;

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		TestClassFactory::s_hModule = hModule;
	}
	return TRUE;
}

STDAPI DllCanUnloadNow(void)
{
	return S_OK;
}
STDAPI DllRegisterServer(void)
{
	return S_OK;
}
STDAPI DllUnregisterServer(void)
{
	return S_OK;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	TestClassFactory* pFactory = new TestClassFactory();
	HRESULT hr = pFactory->QueryInterface(riid, ppv);
	pFactory->Release();
	return hr;
}
