
// TailCatchDlg.h: 헤더 파일
//

#pragma once


// CTailCatchDlg 대화 상자
class CTailCatchDlg : public CDialogEx
{
// 생성입니다.
public:
	CTailCatchDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAILCATCH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void SnakeRewind(); // 벽과 충돌시 뱀을 이동하기 전 초기화
	void dead();// 게임오버
	void BasicSnake(); // 뱀 초기상태로 초기화
	void randFood(); //음식을 랜덤으로 출현
public:
	CRect Head; // 뱀의 머리
	CRect Body[100]; //뱀의 몸통
	CRect food; // 먹이

	//뱀의 위치(반드시 15의 배수로 설정해야함)
	int a = 135;
	int b = 135;
	int c = 150;
	int d = 150;

	//int BasicSize = 2; //뱀의 초기상태 길이
	int size = 2; //뱀의 길이
	int level = 1; // 1=초급 2=중급 3=고급
	int speed = 200; //뱀의 속도
	int speedLevel = 1;

	// 꼬리의 이전상태 보관
	int TailTopSave[100] = { 0, };
	int TailBottomSave[100] = { 0, };
	int TailLeftSave[100] = { 0, };
	int TailRightSave[100] = { 0, };

	//머리의 이전상태를 보관
	int HeadTopSave;
	int HeadBottomSave;
	int HeadLeftSave;
	int HeadRightSave;

	//키보드 입력 확인
	BOOL Acount = TRUE;
	BOOL Dcount = FALSE;
	BOOL Wcount = FALSE;
	BOOL Scount = FALSE;

	//랜덤 값 저장
	int randTemp1;
	int randTemp2;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnGamestart();
	afx_msg void OnLevel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnExp();
	void loadBMP();
};
