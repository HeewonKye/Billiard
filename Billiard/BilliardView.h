
// BilliardView.h : CBilliardView Ŭ������ �������̽�
//

#pragma once

#include <gl\GL.h>
#include <gl\glu.h>
#include <gl\glut.h>



class CBilliardView : public CView
{
protected: // serialization������ ��������ϴ�.
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

// Ư���Դϴ�.
public:
	CBilliardDoc* GetDocument() const;
	unsigned char *m_imageBuffer;
	int m_ResultImgSize[2];

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CBilliardView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // BilliardView.cpp�� ����� ����
inline CBilliardDoc* CBilliardView::GetDocument() const
   { return reinterpret_cast<CBilliardDoc*>(m_pDocument); }
#endif

