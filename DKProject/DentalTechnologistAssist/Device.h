#pragma once

// Function pointer for the function that transforms the image.

typedef void(*IMAGE_TRANSFORM_FN)(
	BYTE*       pDest,
	LONG        lDestStride,
	const BYTE* pSrc,
	LONG        lSrcStride,
	DWORD       dwWidthInPixels,
	DWORD       dwHeightInPixels
	);


// DrawDevice class

class DrawDevice
{
private:

	HWND                    m_hwnd;
	HDC                     *phdc;
	IDirect3D9              *m_pD3D;
	IDirect3DDevice9        *m_pDevice;
	IDirect3DSwapChain9     *m_pSwapChain;

	D3DPRESENT_PARAMETERS   m_d3dpp;
	ID3DXSprite             *textSprite;
	// Format information
	D3DFORMAT               m_format;
	LONG                    m_lDefaultStride;
	MFRatio                 m_PixelAR;
	MFVideoInterlaceMode    m_interlace;
	RECT                    m_rcDest;       // Destination rectangle

											// Drawing
	IMAGE_TRANSFORM_FN      m_convertFn;    // Function to convert the video to RGB32

private:

	HRESULT TestCooperativeLevel();
	HRESULT SetConversionFunction(REFGUID subtype);
	HRESULT CreateSwapChains();
	void    UpdateDestinationRect();

public:
	bool saveframe;
	UINT                    m_width;
	UINT                    m_height;
	UINT                    width;
	UINT                    height;
	DrawDevice();
	virtual ~DrawDevice();

	HRESULT CreateDevice(HWND hwnd);
	HRESULT ResetDevice();
	void    DestroyDevice();

	HRESULT SetVideoType(IMFMediaType *pType);
	HRESULT DrawFrame(IMFMediaBuffer *pBuffer);

	// What video formats we accept
	BOOL     IsFormatSupported(REFGUID subtype) const;
	HRESULT  GetFormat(DWORD index, GUID *pSubtype)  const;

	// test code
	void TestDraw();
};
