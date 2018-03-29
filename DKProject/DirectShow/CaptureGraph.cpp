#include "stdafx.h"
#include  "CaptureGraph.h"

#ifndef __STREAMS__
#define __STREAMS__
#endif



extern struct  _capstuff 
{
    IVideoWindow			*pVW;
    IMediaEventEx			*pME;
    IAMVideoCompression		*pVC;
    IAMStreamConfig			*pVSC;      
    IBaseFilter				*pRender;
    IBaseFilter				*pVCap; 
    IGraphBuilder			*pFg;
    IMoniker				*rgpmVideoMenu[5];
    IMoniker				*pmVideo;
    BOOL					fCaptureGraphBuilt;
    BOOL fPreviewGraphBuilt;
    BOOL fCapturing;
    BOOL fPreviewing;
    WCHAR wachFriendlyName[120];
    double FrameRate;
	BOOL fUseFrameRate;
    BOOL fPreviewFaked;     
    int iNumVCapDevices;    // number of devices 
};	
	
extern CString strInfo[10];   // Infos into our Listbox
extern int iIndex;


HRESULT 
IMyCaptureGraphBuilder::SetFiltergraph( IGraphBuilder *pfg )
{
    return graphBuilder2_->SetFiltergraph( pfg );
}

HRESULT IMyCaptureGraphBuilder::FindInterface(const GUID *pCategory,
                                                  const GUID *pType,
                                                  IBaseFilter *pf,
                                                  REFIID riid,
                                                  void **ppint
                                                  )
{
    return graphBuilder2_->FindInterface( pCategory, pType, pf, riid, ppint );
}


HRESULT IMyCaptureGraphBuilder::GetFiltergraph( IGraphBuilder **ppfg )
{
    return graphBuilder2_->GetFiltergraph( ppfg );
}


HRESULT 
IMyCaptureGraphBuilder::RenderStream( const GUID *pCategory,
                                          const GUID *pType,
                                          IUnknown *pSource,
                                          IBaseFilter *pIntermediate,
                                          IBaseFilter *pSink)
{
    if( !pType ||  !::IsEqualGUID( MEDIATYPE_Stream, *pType ) )
    {
        return graphBuilder2_->RenderStream( pCategory, pType, pSource, 
                                             pIntermediate, pSink );
    }

 
    return S_OK;
}


//========================== utility =====================================
void IMonRelease(IMoniker *&pm)
{
    if(pm)
    {
        pm->Release();
        pm = 0;
    }
}
//=========================================================================


int EnumerateAllDevices()
{
    UINT    uIndex = 0;
    HRESULT hr;
   
     for(int i = 0; i < NUMELMS(gcap.rgpmVideoMenu); i++)
						IMonRelease(gcap.rgpmVideoMenu[i]);
    
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

    ICreateDevEnum *pDevEnum=0;
    hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
                          IID_ICreateDevEnum, (void**)&pDevEnum);
    if(hr != NOERROR)
    {
       strInfo[iIndex++].Format(TEXT("Error Creating Device Enumerator"));
       return -1;
    }

    IEnumMoniker *pEnum=0;
    hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnum, 0);
    if(hr != NOERROR)
    {
        strInfo[iIndex++].Format(TEXT("!!!  No webcam found !!!"));
        goto ENUM_EXIT;
    }
    
    pEnum->Reset();
    ULONG		uFetched;
    IMoniker	*pM;

    while(1)
    {
		hr = pEnum->Next(1, &pM, &uFetched);
		if(hr != S_OK) goto ENUM_EXIT;

        IPropertyBag *pBag=0;

        hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
        if(SUCCEEDED(hr))
        {
            VARIANT var;
            var.vt = VT_BSTR;
            hr = pBag->Read(L"FriendlyName", &var, NULL);
            if(hr == NOERROR)
            {
 				strInfo[uIndex].Format("%S", var.bstrVal);
                SysFreeString(var.bstrVal);

                ASSERT(gcap.rgpmVideoMenu[uIndex] == 0);
                gcap.rgpmVideoMenu[uIndex]        = pM;
                pM->AddRef();
            }
            pBag->Release();
        }
        pM->Release();
        uIndex++;
    }
    pEnum->Release();

ENUM_EXIT:
	pDevEnum->Release();
	return uIndex;
}


void StartThisDevice(IMoniker *pmVideo)  
{
     if(gcap.pmVideo != pmVideo)
    {
        if(pmVideo)
            pmVideo->AddRef();
     
        IMonRelease(gcap.pmVideo);
 
        gcap.pmVideo = pmVideo;

       if(gcap.fPreviewing) StopPreview();

        if(gcap.fCaptureGraphBuilt || gcap.fPreviewGraphBuilt)
            TearDownGraph();

		FreeCapFilters();
        if(InitCapFilters()== false) return;

        BuildPreviewGraph();
        StartPreview();                  
    }
}
