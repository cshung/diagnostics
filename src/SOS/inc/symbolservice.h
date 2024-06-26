// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

#pragma once

#include <stdarg.h>
#include <unknwn.h>

typedef void (*WriteLineDelegate)(const char*);
typedef void (*SymbolFileCallbackDelegate)(void*, const char* moduleFileName, const char* symbolFilePath);

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// ISymbolService
///
/// Provides symbol related services to SOS.
/// </summary>
MIDL_INTERFACE("7EE88D46-F8B3-4645-AD3E-01FE7D4F70F1")
ISymbolService : public IUnknown
{
public:
    virtual bool STDMETHODCALLTYPE ParseSymbolPath(
        const char* windowsSymbolPath) = 0;

    virtual PVOID STDMETHODCALLTYPE LoadSymbolsForModule(
        LPCWSTR,
        BOOL,
        ULONG64,
        int,
        ULONG64,
        int) = 0;

    virtual void STDMETHODCALLTYPE Dispose(
        PVOID) = 0;

    virtual BOOL STDMETHODCALLTYPE ResolveSequencePoint(
        PVOID,
        const char*,
        unsigned int,
        unsigned int*,
        unsigned int*) = 0;

    virtual BOOL STDMETHODCALLTYPE GetLocalVariableName(
        PVOID,
        int,
        int,
        BSTR*) = 0;

    virtual BOOL STDMETHODCALLTYPE GetLineByILOffset(
        PVOID,
        mdMethodDef,
        ULONG64,
        ULONG *,
        BSTR*) = 0;

    virtual ULONG64 STDMETHODCALLTYPE GetExpressionValue(
        PCSTR) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetMetadataLocator(
        LPCWSTR imagePath,
        unsigned int imageTimestamp,
        unsigned int imageSize,
        GUID* mvid,
        unsigned int mdRva,
        unsigned int flags,
        unsigned int bufferSize,
        PVOID pMetadata,
        unsigned int* pMetadataSize) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetICorDebugMetadataLocator(
        LPCWSTR imagePath,
        unsigned int imageTimestamp,
        unsigned int imageSize,
        ULONG32 cchPathBuffer,
        ULONG32* pcchPathBuffer,
        WCHAR* pwszPathBuffer) = 0;
};

#ifdef __cplusplus
};
#endif
