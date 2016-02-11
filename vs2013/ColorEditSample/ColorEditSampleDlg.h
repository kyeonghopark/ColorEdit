#pragma once

#include "ColorEdit.h"


class CColorEditSampleDlg : public CDialog {
 public:
  CColorEditSampleDlg();

 protected:
  BOOL OnInitDialog() override;

 private:
  ColorEdit id_edit_;
  ColorEdit pw_edit_;
};
