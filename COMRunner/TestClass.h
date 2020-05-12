

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Mon Jan 18 19:14:07 2038
 */
/* Compiler settings for TestClass.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __TestClass_h__
#define __TestClass_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITestClass_FWD_DEFINED__
#define __ITestClass_FWD_DEFINED__
typedef interface ITestClass ITestClass;

#endif 	/* __ITestClass_FWD_DEFINED__ */


#ifndef __TestClass_FWD_DEFINED__
#define __TestClass_FWD_DEFINED__

#ifdef __cplusplus
typedef class TestClass TestClass;
#else
typedef struct TestClass TestClass;
#endif /* __cplusplus */

#endif 	/* __TestClass_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ITestClass_INTERFACE_DEFINED__
#define __ITestClass_INTERFACE_DEFINED__

/* interface ITestClass */
/* [oleautomation][dual][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITestClass;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("67E11FF0-C068-4C48-A1F5-69A882E0E99A")
    ITestClass : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetData( 
            /* [in] */ BSTR data) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Run( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITestClassVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITestClass * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITestClass * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITestClass * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITestClass * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITestClass * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITestClass * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITestClass * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *SetData )( 
            ITestClass * This,
            /* [in] */ BSTR data);
        
        HRESULT ( STDMETHODCALLTYPE *Run )( 
            ITestClass * This);
        
        END_INTERFACE
    } ITestClassVtbl;

    interface ITestClass
    {
        CONST_VTBL struct ITestClassVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITestClass_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITestClass_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITestClass_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITestClass_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITestClass_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITestClass_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITestClass_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITestClass_SetData(This,data)	\
    ( (This)->lpVtbl -> SetData(This,data) ) 

#define ITestClass_Run(This)	\
    ( (This)->lpVtbl -> Run(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITestClass_INTERFACE_DEFINED__ */



#ifndef __TestClassLib_LIBRARY_DEFINED__
#define __TestClassLib_LIBRARY_DEFINED__

/* library TestClassLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_TestClassLib;

EXTERN_C const CLSID CLSID_TestClass;

#ifdef __cplusplus

class DECLSPEC_UUID("67E11FF2-C068-4C48-A1F5-69A882E0E99A")
TestClass;
#endif
#endif /* __TestClassLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


