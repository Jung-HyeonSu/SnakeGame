#pragma once


// Level 대화 상자

class Level : public CDialog
{
	DECLARE_DYNAMIC(Level)

public:
	Level(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Level();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:

	DECLARE_MESSAGE_MAP()
public:

	BOOL m_lower = FALSE;
	BOOL m_middle = FALSE;
	BOOL m_upper = FALSE;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
};
