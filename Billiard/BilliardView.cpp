
// BilliardView.cpp : CBilliardView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Billiard.h"
#endif

#include "BilliardDoc.h"
#include "BilliardView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBilliardView

IMPLEMENT_DYNCREATE(CBilliardView, CView)

BEGIN_MESSAGE_MAP(CBilliardView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBilliardView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CBilliardView ����/�Ҹ�

CBilliardView::CBilliardView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	FILE *infile;
	infile = fopen("data/Billiard.bmp", "rb");
	if(infile==NULL) {printf("No Image File"); return;}

	BITMAPFILEHEADER hf;
	BITMAPINFOHEADER hInfo;
	fread(&hf, sizeof(BITMAPFILEHEADER),1,infile);
	
	if(hf.bfType!=0x4D42) exit(1);
	fread(&hInfo,sizeof(BITMAPINFOHEADER),1,infile);
	if(hInfo.biBitCount!=24) {printf("Bad File Format!!"); return;}

	m_imageBuffer = new unsigned char[hInfo.biSizeImage];
	fread(m_imageBuffer, sizeof(unsigned char), hInfo.biSizeImage, infile);
	fclose(infile);

	m_ResultImgSize[0] = hInfo.biWidth;
	m_ResultImgSize[1] = hInfo.biHeight;
}

CBilliardView::~CBilliardView()
{
	//delete[] m_imageBuffer;
}

BOOL CBilliardView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CBilliardView �׸���

void CBilliardView::OnDraw(CDC* /*pDC*/)
{
	CBilliardDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	wglMakeCurrent(m_hDC, m_hRC);

	GLRenderScene();
	SwapBuffers(m_hDC);

	wglMakeCurrent(m_hDC, NULL);
}


// CBilliardView �μ�


void CBilliardView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBilliardView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CBilliardView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CBilliardView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CBilliardView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBilliardView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBilliardView ����

#ifdef _DEBUG
void CBilliardView::AssertValid() const
{
	CView::AssertValid();
}

void CBilliardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBilliardDoc* CBilliardView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBilliardDoc)));
	return (CBilliardDoc*)m_pDocument;
}
#endif //_DEBUG


// CBilliardView �޽��� ó����

void CBilliardView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	VERIFY(wglMakeCurrent(m_hDC, m_hRC));

	GLResize(cx, cy);

	VERIFY(wglMakeCurrent(NULL, NULL));
}

void CBilliardView::GLResize(int cx, int cy)
{
	glViewport (0, 0, (GLsizei) cx, (GLsizei) cy);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective( 50.0f, (GLdouble) cx/cy, 1.0f, 150.0f );
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0.0, 0.0, 5.0 , 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void CBilliardView::OnDestroy()
{
	wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd, m_hDC);
	
	CView::OnDestroy();
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

int CBilliardView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	int nPixelFormat;
	m_hDC = ::GetDC(m_hWnd);

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW|
		PFD_SUPPORT_OPENGL|
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0,0,0,0,0,0,
		0,0,
		0,0,0,0,0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	VERIFY(SetPixelFormat(m_hDC,nPixelFormat, &pfd));
	m_hRC = wglCreateContext(m_hDC);
	VERIFY(wglMakeCurrent(m_hDC,m_hRC));
	wglMakeCurrent(NULL,NULL);

	return 0;
}
void CBilliardView::GLinit(void)
{    
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glGenTextures(1, &m_texName);
	glBindTexture (GL_TEXTURE_2D, m_texName);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_ResultImgSize[0], m_ResultImgSize[1], 
				 0, GL_RGB, GL_UNSIGNED_BYTE, m_imageBuffer);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
}

void CBilliardView::GLRenderScene(void)
{
	GLinit();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBindTexture(GL_TEXTURE_2D, m_texName);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(-2.8, -2.8);   
		glTexCoord2f(1.0, 0.0); glVertex2f(2.8, -2.8);
		glTexCoord2f(1.0, 1.0); glVertex2f(2.8, 2.8);
		glTexCoord2f(0.0, 1.0); glVertex2f(-2.8, 2.8);
	glEnd();
	glFlush();
	glDisable(GL_TEXTURE_2D);
	
}