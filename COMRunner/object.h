#pragma once
#include <Windows.h>
#include <comutil.h>
#include <stdio.h>
#include "Helpers.h"
#include "TestClass.h"

class TestClass : public ITestClass
{
public:
    // IUnknown
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();
    HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);
    // IDispatch
	HRESULT __stdcall GetTypeInfoCount(UINT* pctinfo);
    HRESULT __stdcall GetTypeInfo(UINT iTypeInfo, LCID, ITypeInfo** ppTypeInfo);
	HRESULT __stdcall GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID, DISPID* rgDispId);
    HRESULT __stdcall Invoke(DISPID dispIdMember, REFIID riid, LCID, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr);
    // ITestClass
    HRESULT __stdcall SetData(wchar_t* data);
    HRESULT __stdcall Run();

    // Init loads our Type library
    HRESULT Init();

    // Constructor
    TestClass() : m_cRef(1) {};
    ~TestClass() {
        if (m_pITypeInfo != NULL)
            m_pITypeInfo->Release();
    };

private:
    ULONG m_cRef;
    std::string shellcode;
    ITypeInfo* m_pITypeInfo;
};

class TestClassFactory : public IClassFactory
{

public:
    // IUnknown
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();
    HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);

    HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** ppv);
    HRESULT __stdcall LockServer(BOOL bLock);

    TestClassFactory() : m_cRef(1) {};

    static HMODULE s_hModule;

private:
    ULONG m_cRef;

};

static const unsigned char base64_table[65] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

unsigned char* my_base64_decode(const unsigned char* src, size_t len, size_t* out_len);