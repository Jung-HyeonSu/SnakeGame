
// TailCatchDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "TailCatch.h"
#include "TailCatchDlg.h"
#include "afxdialogex.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <string>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <random>
#include "Level.h"
#include "ExpDll.h"


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTailCatchDlg 대화 상자



CTailCatchDlg::CTailCatchDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAILCATCH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTailCatchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTailCatchDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_COMMAND(ID_GameStart, &CTailCatchDlg::OnGamestart)
	ON_COMMAND(ID_LEVEL, &CTailCatchDlg::OnLevel)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_EXP, &CTailCatchDlg::OnExp)
END_MESSAGE_MAP()


// CTailCatchDlg 메시지 처리기

BOOL CTailCatchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	SetDlgItemInt(IDC_STATIC, speedLevel);
	SetDlgItemInt(IDC_STATIC2, size);
	Head.SetRect(a, b, c, d);
	Body[0].SetRect(a + 15, b, c + 15, d);
	Body[1].SetRect(a + 30, b, c + 30, d);
	randFood();
	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTailCatchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTailCatchDlg::OnPaint()
{

	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	loadBMP();
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (i == 0 || i == 19 || j == 0 || j == 19) {
				dc.Rectangle(j * 15, i * 15, j * 15 + 15, i * 15 + 15);
			}
		}
	}

	dc.FillSolidRect(Head, RGB(0, 100, 0));
	for (int i = 0; i < size; i++) {
		dc.FillSolidRect(Body[i], RGB(50, 205, 50));
	}
	dc.FillSolidRect(food, RGB(220, 20, 60));
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTailCatchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTailCatchDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	HeadTopSave = Head.top;
	HeadBottomSave = Head.bottom;
	HeadLeftSave = Head.left;
	HeadRightSave = Head.right;

	if (Wcount == TRUE) {
		for (int i = 0; i < size; i++) {
			TailTopSave[i] = Body[i].top;
			TailBottomSave[i] = Body[i].bottom;
			TailLeftSave[i] = Body[i].left;
			TailRightSave[i] = Body[i].right;
			if (i != 0) {
				Body[i].top = TailTopSave[i - 1];
				Body[i].bottom = TailBottomSave[i - 1];
				Body[i].left = TailLeftSave[i - 1];
				Body[i].right = TailRightSave[i - 1];

			}
			if (i == 0) {
				Body[i].top = Head.top;
				Body[i].bottom = Head.bottom;
				Body[i].left = Head.left;
				Body[i].right = Head.right;
			}
		}
		Head.top -= 15;
		Head.bottom -= 15;
		if (Head.top == 0) { //벽과 충돌
			KillTimer(0);
			SnakeRewind();
			dead();
		}
	}
	else if (Acount == TRUE) {
		for (int i = 0; i < size; i++) {
			TailTopSave[i] = Body[i].top;
			TailBottomSave[i] = Body[i].bottom;
			TailLeftSave[i] = Body[i].left;
			TailRightSave[i] = Body[i].right;
			if (i != 0) {
				Body[i].top = TailTopSave[i - 1];
				Body[i].bottom = TailBottomSave[i - 1];
				Body[i].left = TailLeftSave[i - 1];
				Body[i].right = TailRightSave[i - 1];

			}
			if (i == 0) {
				Body[i].top = Head.top;
				Body[i].bottom = Head.bottom;
				Body[i].left = Head.left;
				Body[i].right = Head.right;
			}
		}
		Head.left -= 15;
		Head.right -= 15;

		if (Head.left == 0) { //벽과 충돌
			KillTimer(0);
			SnakeRewind();
			dead();
		}
	}
	else if (Scount == TRUE) {
		for (int i = 0; i < size; i++) {
			TailTopSave[i] = Body[i].top;
			TailBottomSave[i] = Body[i].bottom;
			TailLeftSave[i] = Body[i].left;
			TailRightSave[i] = Body[i].right;
			if (i != 0) {
				Body[i].top = TailTopSave[i - 1];
				Body[i].bottom = TailBottomSave[i - 1];
				Body[i].left = TailLeftSave[i - 1];
				Body[i].right = TailRightSave[i - 1];

			}
			if (i == 0) {
				Body[i].top = Head.top;
				Body[i].bottom = Head.bottom;
				Body[i].left = Head.left;
				Body[i].right = Head.right;
			}
		}
		Head.top += 15;
		Head.bottom += 15;

		if (Head.bottom == 300) { //벽과 충돌
			KillTimer(0);
			SnakeRewind();
			dead();
		}
	}
	else if (Dcount == TRUE) {
		for (int i = 0; i < size; i++) {
			TailTopSave[i] = Body[i].top;
			TailBottomSave[i] = Body[i].bottom;
			TailLeftSave[i] = Body[i].left;
			TailRightSave[i] = Body[i].right;
			if (i != 0) {
				Body[i].top = TailTopSave[i - 1];
				Body[i].bottom = TailBottomSave[i - 1];
				Body[i].left = TailLeftSave[i - 1];
				Body[i].right = TailRightSave[i - 1];

			}
			if (i == 0) {
				Body[i].top = Head.top;
				Body[i].bottom = Head.bottom;
				Body[i].left = Head.left;
				Body[i].right = Head.right;
			}
		}
		Head.left += 15;
		Head.right += 15;

		if (Head.right == 300) { // 벽과 충돌
			KillTimer(0);
			SnakeRewind();
			dead();
		}
	}

	for (int i = 0; i < size; i++) { // 몸통과 충돌
		if (Head.top == Body[i].top && Head.bottom == Body[i].bottom && 
			Head.left == Body[i].left && Head.right == Body[i].right) {
			KillTimer(0);
			SnakeRewind();
			dead();
		}
	}

	//먹이를 먹었을 때
	if (Head.top == food.top && Head.bottom == food.bottom && 
		Head.left == food.left && Head.right == food.right) {
		randFood(); 
		
		//몸통 늘리기
		size++;
		Body[size-1].SetRect(0, 0, 15, 15);
		Body[size - 1].top = TailTopSave[size - 2];
		Body[size - 1].bottom = TailBottomSave[size - 2];
		Body[size - 1].right = TailLeftSave[size - 2];
		Body[size - 1].left = TailRightSave[size - 2];

		KillTimer(0);
		if (speed > 50) {
			speed -= 10;
			speedLevel++;
		}
		SetDlgItemInt(IDC_STATIC, speedLevel);
		SetDlgItemInt(IDC_STATIC2, size);
		SetTimer(0, speed, NULL);
	}
	UpdateData(FALSE);
	Invalidate(1);
	return;
	CDialogEx::OnTimer(nIDEvent);
}


void CTailCatchDlg::OnGamestart()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SetTimer(0, speed, NULL);
}

void CTailCatchDlg::SnakeRewind() // 뱀 이전상태로
{
	Head.top = HeadTopSave;
	Head.bottom = HeadBottomSave;
	Head.left = HeadLeftSave;
	Head.right = HeadRightSave;
	for (int i = 0; i < size; i++) {
		Body[i].top = TailTopSave[i];
		Body[i].bottom = TailBottomSave[i];
		Body[i].left = TailLeftSave[i];
		Body[i].right = TailRightSave[i];
	}
}

void CTailCatchDlg::dead()
{
	MessageBox(_T("게임오버 !"));
	BasicSnake();
}


BOOL CTailCatchDlg::PreTranslateMessage(MSG* pMsg) //키보드 입력받기
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam) {
		case VK_LEFT:
			if (Dcount == FALSE) {
				Acount = TRUE;
				Dcount = FALSE;
				Wcount = FALSE;
				Scount = FALSE;
			}
			break;
		case VK_RIGHT:
			if (Acount == FALSE) {
				Acount = FALSE;
				Dcount = TRUE;
				Wcount = FALSE;
				Scount = FALSE;
			}
			break;
		case VK_UP:
			if (Scount == FALSE) {
				Acount = FALSE;
				Dcount = FALSE;
				Wcount = TRUE;
				Scount = FALSE;
			}
			break;
		case VK_DOWN:
			if (Wcount == FALSE) {
				Acount = FALSE;
				Dcount = FALSE;
				Wcount = FALSE;
				Scount = TRUE;
			}
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CTailCatchDlg::BasicSnake() { //뱀 초기화
	Acount = TRUE;
	Dcount = FALSE;
	Wcount = FALSE;
	Scount = FALSE;

	Head.SetRect(a, b, c, d);
	for (int i = 0; i < size; i++) {
		Body[i].SetRect(0, 0, 0, 0);
	}
	if (level == 1) {
		speed = 200;
		speedLevel = 1;
		size = 2;
		Body[0].SetRect(a + 15, b, c + 15, d);
		Body[1].SetRect(a + 30, b, c + 30, d);
		SetDlgItemInt(IDC_STATIC, speedLevel);
		SetDlgItemInt(IDC_STATIC2, size);
		SetDlgItemText(IDC_STATIC3, _T("초급"));
	}
	else if (level == 2) {
		speed = 150;
		speedLevel = 6;
		size = 4;
		Body[0].SetRect(a + 15, b, c + 15, d);
		Body[1].SetRect(a + 30, b, c + 30, d);
		Body[2].SetRect(a + 45, b, c + 45, d);
		Body[3].SetRect(a + 60, b, c + 60, d);
		SetDlgItemInt(IDC_STATIC, speedLevel);
		SetDlgItemInt(IDC_STATIC2, size);
		SetDlgItemText(IDC_STATIC3, _T("중급"));
	}
	else {
		speed = 100;
		speedLevel = 11;
		size = 6;
		Body[0].SetRect(a + 15, b, c + 15, d);
		Body[1].SetRect(a + 30, b, c + 30, d);
		Body[2].SetRect(a + 45, b, c + 45, d);
		Body[3].SetRect(a + 60, b, c + 60, d);
		Body[4].SetRect(a + 75, b, c + 75, d);
		Body[5].SetRect(a + 90, b, c + 90, d);
		SetDlgItemInt(IDC_STATIC, speedLevel);
		SetDlgItemInt(IDC_STATIC2, size);
		SetDlgItemText(IDC_STATIC3, _T("고급"));

	}
	srand(time(NULL));
	randFood();
}


void CTailCatchDlg::OnLevel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	Level PopupDialog;
	if (PopupDialog.DoModal() == IDOK) {
		if (PopupDialog.m_lower ==TRUE) {
			level = 1;
			BasicSnake();
			MessageBox(_T("난이도가 [초급]으로 설정되었습니다."));
		}
		else if (PopupDialog.m_middle == TRUE) {
			level = 2;
			BasicSnake();
			MessageBox(_T("난이도가 [중급]으로 설정되었습니다."));
		}
		else if (PopupDialog.m_upper == TRUE) {
			level = 3;
			BasicSnake();
			MessageBox(_T("난이도가 [고급]으로 설정되었습니다."));
		}
		else {
			BasicSnake();
		}
	}
	UpdateData(FALSE);
	Invalidate(1);
}

void CTailCatchDlg::randFood() // 먹이
{
	while (1) {
		randTemp1 = (rand() % 18 + 1) * 15;
		randTemp2 = (rand() % 18 + 1) * 15;

		if (randTemp1 != a && randTemp2 != b)  { //머리와 먹이가 겹치지 않게하기
			food.SetRect(randTemp1, randTemp2, randTemp1 + 15, randTemp2 + 15);
			break;
		}
	}
}

void CTailCatchDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SetTimer(0, speed, NULL); //게임시작
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CTailCatchDlg::OnExp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ExpDll expdll;
	expdll.DoModal();
}

void CTailCatchDlg::loadBMP() {
	CClientDC dc(this);
	CDC MemDC; //비트맵
	MemDC.CreateCompatibleDC(&dc);
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BMP);
	CBitmap* oldBitmap = MemDC.SelectObject(&bitmap);
	dc.BitBlt(550, 30, 400, 400, &MemDC, 0, 0, SRCCOPY);
	dc.SelectObject(oldBitmap);
}