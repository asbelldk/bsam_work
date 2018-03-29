

#pragma once

#include <DShow.h>
#include "smartptr.h"


#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) { if (x) x->Release(); x = NULL; }
#endif


int EnumerateAllDevices();

void TearDownGraph(void);
BOOL BuildPreviewGraph();

void StartThisDevice(IMoniker *pmVideo);
BOOL InitCapFilters();
void FreeCapFilters();
BOOL StopPreview();
BOOL StartPreview();
void IMonRelease(IMoniker *&pm);




class IMyCaptureGraphBuilder
{
public:
    IMyCaptureGraphBuilder()
    {
        VidPID_ = 0xE0;
        HRESULT hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, 
			IID_ICaptureGraphBuilder2, (void**)&graphBuilder2_ ); 
        ASSERT( S_OK == hr );
    }
   
    void ReleaseFilters( )
    {
        pVideoPin_.Release();
    }

public:
   STDMETHOD(FindInterface)(const GUID *pCategory,
                          const GUID *pType,
                          IBaseFilter *pf,
                          REFIID riid,
                          void **ppint
                          );

    STDMETHOD(GetFiltergraph)( IGraphBuilder **ppfg );


    STDMETHOD(RenderStream)( const GUID *pCategory,
                          const GUID *pType,
                          IUnknown *pSource,
                          IBaseFilter *pIntermediate,
                          IBaseFilter *pSink
                          );

    STDMETHOD(SetFiltergraph)( IGraphBuilder *pfg );



protected:
    SmartPtr<ICaptureGraphBuilder2> graphBuilder2_;
    ULONG   VidPID_; 
private:
     SmartPtr<IPin>   pVideoPin_;

};


