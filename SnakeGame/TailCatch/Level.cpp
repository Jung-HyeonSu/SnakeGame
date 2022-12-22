// Level.cpp: 구현 파일
//

#include "pch.h"
#include "TailCatch.h"
#include "Level.h"
#include "afxdialogex.h"


// Level 대화 상자

IMPLEMENT_DYNAMIC(Level, CDialog)

Level::Level(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)

	, m_lower(FALSE)
	, m_middle(FALSE)
	, m_upper(FALSE)
{

}

Level::~Level()
{
}


BEGIN_MESSAGE_MAP(Level, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &Level::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &Level::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &Level::OnBnClickedRadio3)
END_MESSAGE_MAP()


// Level 메시지 처리기


void Level::OnBnClickedRadio1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_lower = TRUE;
	m_middle = FALSE;
	m_upper = FALSE;
}


void Level::OnBnClickedRadio2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_lower = FALSE;
	m_middle = TRUE;
	m_upper = FALSE;
}


void Level::OnBnClickedRadio3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_lower = FALSE;
	m_middle = FALSE;
	m_upper = TRUE;
}
