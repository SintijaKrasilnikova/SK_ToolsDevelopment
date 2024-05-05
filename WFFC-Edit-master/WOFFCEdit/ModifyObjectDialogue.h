#pragma once

#include "afxwin.h"
#include <afxdialogex.h>
#include "ToolMain.h"

class ModifyObjectDialogue : public CDialogEx
{
	DECLARE_DYNAMIC(ModifyObjectDialogue)

public:
	ModifyObjectDialogue(CWnd* pParent, std::vector<SceneObject>* SceneGraph);   // modal // takes in out scenegraph in the constructor
	ModifyObjectDialogue(CWnd* pParent = NULL);
	virtual ~ModifyObjectDialogue();
	void SetToolsAndInfo(ToolMain* tool);
	void SetFieldInfo(std::vector<DisplayObject>* disList, ToolMain* tool);
	//void ModifyObjectDialogue(std::vector<SceneObject>* SceneGraph, int* Selection);	//passing in pointers to the data the class will operate on.

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void End();		//kill the dialogue
	afx_msg void Select();	//Item has been selected
	afx_msg void OnChangeXPos();	//Item has been selected

	//std::vector<SceneObject>* m_sceneGraph;
	std::vector<DisplayObject>* m_displayList;
	int m_currentSelectionID;

	ToolMain* m_ToolSystem;
	CWnd* pWnd;


	DECLARE_MESSAGE_MAP()
public:
	// Control variable for more efficient access of the listbox
	CListBox m_listBox;
	virtual BOOL OnInitDialog() override;
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedOk();

	//functions for changing the position
	afx_msg void OnXPosChanged();
	afx_msg void OnYPosChanged();
	afx_msg void OnZPosChanged();
	//afx_msg void OnLbnSelchangeList1();
};

INT_PTR CALLBACK ModifyObjectProc(HWND   hwndDlg, UINT   uMsg, WPARAM wParam, LPARAM lParam);
