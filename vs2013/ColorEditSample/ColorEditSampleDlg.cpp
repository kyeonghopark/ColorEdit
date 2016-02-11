#include "stdafx.h"
#include "ColorEditSampleDlg.h"

#include "Resource.h"


CColorEditSampleDlg::CColorEditSampleDlg()
    : CDialog(IDD_COLOREDITSAMPLE_DIALOG),
      id_edit_(),
      pw_edit_() {
}


BOOL CColorEditSampleDlg::OnInitDialog() {
  CDialog::OnInitDialog();

  CDC *dc = __super::GetDC();

  // icon
  HICON icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  SetIcon(icon, TRUE);
  SetIcon(icon, FALSE);

  // edit
  LOGFONT font;
  {
    CString font_name = _T("Tahoma");
    LONG font_size = 14;

    _tcsncpy_s(font.lfFaceName, font_name, LF_FACESIZE);
    {
      static const int kPhysicalPx = 72;
      int logicalPx = dc->GetDeviceCaps(LOGPIXELSY);
      font.lfHeight = font_size * 10 * (-1) * logicalPx / kPhysicalPx;
    }
    font.lfWidth = 0;
    font.lfEscapement = 0;
    font.lfOrientation = 0;
    font.lfWeight = FW_NORMAL;
    font.lfItalic = FALSE;
    font.lfUnderline = FALSE;
    font.lfStrikeOut = FALSE;
    font.lfCharSet = DEFAULT_CHARSET;
    font.lfOutPrecision = OUT_DEFAULT_PRECIS;
    font.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    font.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    font.lfQuality = DEFAULT_QUALITY;
  }

  CSize edit_size(320, 100);

  COLORREF text_color(RGB(0, 0, 128));
  COLORREF placeholder_color(RGB(128, 0, 0));
  COLORREF bg_color(RGB(64, 128, 128));
  COLORREF focus_text_color(RGB(0, 64, 255));
  COLORREF focus_placeholder_color(RGB(255, 64, 0));
  COLORREF focus_bg_color(RGB(128, 255, 255));

  LONG left_margin = 10;
  LONG right_margin = 10;

  CPoint id_pos(50, 50);
  id_edit_.CreateEdit(100,
                      this,
                      id_pos,
                      edit_size,
                      false,
                      _T(""),
                      _T("Id or email"),
                      &font,
                      text_color,
                      placeholder_color,
                      bg_color,
                      focus_text_color,
                      focus_placeholder_color,
                      focus_bg_color,
                      left_margin,
                      right_margin);

  CPoint pw_pos(50, 160);
  pw_edit_.CreateEdit(101,
                      this,
                      pw_pos,
                      edit_size,
                      true,
                      _T(""),
                      _T("Password"),
                      &font,
                      text_color,
                      placeholder_color,
                      bg_color,
                      focus_text_color,
                      focus_placeholder_color,
                      focus_bg_color,
                      left_margin,
                      right_margin);

  //
  __super::ReleaseDC(dc);
  return TRUE;
}
