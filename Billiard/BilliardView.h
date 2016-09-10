
// BilliardView.h : CBilliardView 클래스의 인터페이스
//

#pragma once

#include <gl\GL.h>
#include <gl\glu.h>
#include <gl\glut.h>



class CBilliardView : public CView
{
protected: // serialization에서만 만들어집니다.
	CBilliardView();
	DECLARE_DYNCREATE(CBilliardView)
	
private:
	HGLRC m_hRC;
	HDC m_hDC;
	GLuint m_texName;
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	void GLResize(int cx, int cy);
	void GLinit(void);
	void GLRenderScene(void);

// 특성입니다.
public:
	CBilliardDoc* GetDocument() const;
	unsigned char *m_imageBuffer;
	int m_ResultImgSize[2];

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CBilliardView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // BilliardView.cpp의 디버그 버전
inline CBilliardDoc* CBilliardView::GetDocument() const
   { return reinterpret_cast<CBilliardDoc*>(m_pDocument); }
#endif

