#pragma once


class CColorEditSampleApp : public CWinApp {
 public:
  CColorEditSampleApp();

 protected:
  BOOL InitInstance() override;
};


extern CColorEditSampleApp theApp;
