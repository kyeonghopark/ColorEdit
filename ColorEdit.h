#pragma once

#include "afxwin.h"


class ColorEdit : public CEdit {
  DECLARE_DYNAMIC(ColorEdit)

 public:
  ColorEdit();
  virtual ~ColorEdit();

  BOOL CreateEdit(UINT id,
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
                  LONG right_margin);

 protected:
  DECLARE_MESSAGE_MAP()
  afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
  afx_msg void OnPaint();
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnKillFocus(CWnd* pNewWnd);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
  afx_msg void OnNcPaint();
  afx_msg LRESULT OnNcHitTest(CPoint point);

 private:
   bool IsFocused() const;
   bool ShowsPlaceholder() const;

   void InvalidateAll();

  CString placeholder_;
  CFont font_;

  COLORREF text_color_;
  COLORREF placeholder_color_;
  COLORREF bg_color_;
  COLORREF focus_text_color_;
  COLORREF focus_placeholder_color_;
  COLORREF focus_bg_color_;
  CBrush bg_brush_;
  CBrush focus_bg_brush_;

  CRect margin_;
  CRect paint_rect_;
  CRect paint_placeholder_rect_;
};
