﻿#pragma once
#include "resource.h"

// ExpDll 대화 상자

class AFX_EXT_CLASS ExpDll : public CDialog
{
	DECLARE_DYNAMIC(ExpDll)

public:
	ExpDll(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ExpDll();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	//enum { IDD = IDD_ExpDll };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
