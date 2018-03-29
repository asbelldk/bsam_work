// WebcamDirectShow.h : Hauptheaderdatei f? die PROJECT_NAME-Anwendung

#pragma once

#ifndef __AFXWIN_H__
	#error "\"stdafx.h\" vor dieser Datei f? PCH einschlie?n"
#endif

#include "resource.h"		// Hauptsymbole


// CWebcamDirectShowApp:
// Siehe WebcamDirectShow.cpp f? die Implementierung dieser Klasse
//

class CWebcamDirectShowApp : public CWinApp
{
public:
	CWebcamDirectShowApp();


	public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CWebcamDirectShowApp theApp;