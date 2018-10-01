#pragma once

#include "afxdialogex.h"
#include "OnlineTetris.h"

// ConnectionDialog dialog

class ConnectingDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ConnectingDialog)

#define CONNECTING_TIMER 0
	
public:
	
	virtual ~ConnectingDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	void end();
	void wait();

	inline const bool getWaiting() { return m_waiting;	}

	static std::shared_ptr< ConnectingDialog> GetDialog()
	{
		static auto dlg = shared_ptr< ConnectingDialog>(new ConnectingDialog());
		return dlg;
	}

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONNECTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_connecting;
	
private:
	ConnectingDialog(CWnd* pParent = nullptr);   // standard constructor

	const string m_baseString;
	bool m_waiting;
	string m_connectingString;
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
};
