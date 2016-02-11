#include "stdafx.h"
#include "ColorEditSample.h"

#include "ColorEditSampleDlg.h"


CColorEditSampleApp::CColorEditSampleApp() {
}


BOOL CColorEditSampleApp::InitInstance() {
  CWinApp::InitInstance();

  CColorEditSampleDlg dlg;
  m_pMainWnd = &dlg;
  dlg.DoModal();

  return FALSE;
}


CColorEditSampleApp theApp;
