#include "stdafx.h"
#include "ColorEdit.h"


IMPLEMENT_DYNAMIC(ColorEdit, CEdit)


ColorEdit::ColorEdit()
    : placeholder_(_T("")),
      font_(),
      text_color_(0x00000000),
      placeholder_color_(0x00000000),
      bg_color_(0x00000000),
      focus_text_color_(0x00000000),
      focus_placeholder_color_(0x00000000),
      focus_bg_color_(0x00000000),
      bg_brush_(),
      focus_bg_brush_(),
      margin_(),
      paint_rect_(),
      paint_placeholder_rect_() {
}


ColorEdit::~ColorEdit() {
  if (focus_bg_brush_.GetSafeHandle()) {
    focus_bg_brush_.DeleteObject();
  }
  if (bg_brush_.GetSafeHandle()) {
    bg_brush_.DeleteObject();
  }
  if (font_.GetSafeHandle()) {
    font_.DeleteObject();
  }
}


BOOL ColorEdit::CreateEdit(UINT id,
                           CWnd *parent,
                           const CPoint &pos,
                           const CSize &sz,
                           bool is_password,
                           const CString &initial_text,
                           const CString &placeholder,
                           const LOGFONT *font,
                           COLORREF text_color,
                           COLORREF placeholder_color,
                           COLORREF bg_color,
                           COLORREF focus_text_color,
                           COLORREF focus_placeholder_color,
                           COLORREF focus_bg_color,
                           LONG left_margin,
                           LONG right_margin) {
  // create
  {
    DWORD style = WS_CHILD | WS_VISIBLE | WS_TABSTOP;
    if (is_password) {
      style |= ES_PASSWORD;
    }
    CRect rect(pos.x, pos.y, pos.x + sz.cx, pos.y + sz.cy);
    BOOL created = __super::Create(style, rect, parent, id);
    if (created == FALSE) {
      return FALSE;
    }
  }

  // after creation
  CDC *dc = __super::GetDC();

  // text
  __super::SetWindowText(initial_text);
  placeholder_ = placeholder;

  // font
  UINT text_height = 0;
  {
    font_.CreatePointFontIndirect(font);
    __super::SetFont(&font_);

    {
      CFont *prevFont = dc->SelectObject(&font_);
      TEXTMETRIC metric;
      dc->GetTextMetrics(&metric);
      text_height = metric.tmHeight + metric.tmExternalLeading;
      dc->SelectObject(prevFont);
    }
  }

  // text color
  {
    text_color_ = text_color;
    placeholder_color_ = placeholder_color;
    bg_color_ = bg_color;
    focus_text_color_ = focus_text_color;
    focus_placeholder_color_ = focus_placeholder_color;
    focus_bg_color_ = focus_bg_color;

    bg_brush_.CreateSolidBrush(bg_color_);
    focus_bg_brush_.CreateSolidBrush(focus_bg_color_);
  }

  // margin
  {
    // margin width
    margin_.left = left_margin;
    margin_.right = right_margin;
    __super::SetMargins(margin_.left, margin_.right);

    // margin height
    int gap = sz.cy - text_height;
    margin_.top = gap / 2;
    margin_.bottom = gap - margin_.top;
  }

  // paint rect
  {
    paint_rect_.SetRect(0, 0, sz.cx, sz.cy);
    paint_placeholder_rect_.SetRect(margin_.left,
                                    0,
                                    sz.cx - margin_.right,
                                    text_height);
  }

  //
  __super::ReleaseDC(dc);
  InvalidateAll();
  return TRUE;
}


BEGIN_MESSAGE_MAP(ColorEdit, CEdit)
  ON_WM_CTLCOLOR_REFLECT()
  ON_WM_PAINT()
  ON_WM_SETFOCUS()
  ON_WM_KILLFOCUS()
  ON_WM_KEYDOWN()
  ON_WM_KEYUP()
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONUP()
  ON_WM_NCCALCSIZE()
  ON_WM_NCPAINT()
  ON_WM_NCHITTEST()
END_MESSAGE_MAP()


HBRUSH ColorEdit::CtlColor(CDC* pDC, UINT /*nCtlColor*/) {
  COLORREF text_color = 0x00000000;
  COLORREF bg_color = 0x00000000;
  CBrush *bg_brush = NULL;

  if (IsFocused()) {
    text_color = (ShowsPlaceholder()) ? focus_placeholder_color_ :
                                        focus_text_color_;
    bg_color = focus_bg_color_;
    bg_brush = &focus_bg_brush_;
  } else {
    text_color = (ShowsPlaceholder()) ? placeholder_color_ :
                                        text_color_;
    bg_color = bg_color_;
    bg_brush = &bg_brush_;
  }

  pDC->SetTextColor(text_color);
  pDC->SetBkColor(bg_color);
  return (HBRUSH) bg_brush;
}


void ColorEdit::OnPaint() {
  if (ShowsPlaceholder()) {
    CPaintDC dc(this);
    CtlColor(&dc, CTLCOLOR_EDIT);
    CFont *prevFont = dc.SelectObject(&font_);
    dc.DrawText(placeholder_, paint_placeholder_rect_, NULL);
    dc.SelectObject(prevFont);
  } else {
    __super::OnPaint();
  }
}


void ColorEdit::OnSetFocus(CWnd* pOldWnd) {
  __super::OnSetFocus(pOldWnd);
  InvalidateAll();
}


void ColorEdit::OnKillFocus(CWnd* pNewWnd) {
  __super::OnKillFocus(pNewWnd);
  InvalidateAll();
}


void ColorEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
  __super::OnKeyDown(nChar, nRepCnt, nFlags);
}


void ColorEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
  __super::OnKeyUp(nChar, nRepCnt, nFlags);
  if (ShowsPlaceholder()) {
    Invalidate(FALSE);
  }
}


void ColorEdit::OnLButtonDown(UINT nFlags, CPoint point) {
  __super::OnLButtonDown(nFlags, point);
}


void ColorEdit::OnLButtonUp(UINT nFlags, CPoint point) {
  __super::OnLButtonUp(nFlags, point);
  if (ShowsPlaceholder()) {
    Invalidate(FALSE);
  }
}


void ColorEdit::OnNcCalcSize(BOOL /*bCalcValidRects*/,
                             NCCALCSIZE_PARAMS* lpncsp) {
  Default();

  RECT *rect = &lpncsp->rgrc[0];
  rect->top += margin_.top;
  rect->bottom -= margin_.bottom;
}


void ColorEdit::OnNcPaint() {
  Default();

  CWindowDC dc(this);
  CBrush *brush = NULL;
  if (IsFocused()) {
    brush = &focus_bg_brush_;
  } else {
    brush = &bg_brush_;
  }
  dc.FillRect(paint_rect_, brush);
}


LRESULT ColorEdit::OnNcHitTest(CPoint /*point*/) {
  return HTCLIENT;
}


bool ColorEdit::IsFocused() const {
  return (__super::GetFocus() == this);
}


bool ColorEdit::ShowsPlaceholder() const {
  return (__super::GetWindowTextLength() == 0);
}


void ColorEdit::InvalidateAll() {
  // invalidate non-client area
  static const UINT kFlags = SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE |
                             SWP_NOACTIVATE | SWP_NOZORDER;
  __super::SetWindowPos(NULL, 0, 0, 0, 0, kFlags);

  // invalidate client area
  Invalidate(FALSE);
}
