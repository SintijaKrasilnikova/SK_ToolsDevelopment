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
	int StringToWString(std::wstring& ws, const std::string& s);
	//void ModifyObjectDialogue(std::vector<SceneObject>* SceneGraph, int* Selection);	//passing in pointers to the data the class will operate on.

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void End();		//kill the dialogue
	afx_msg void OnSelectTexture();		//kill the dialogue
	//afx_msg void Select();	//Item has been selected

	//std::vector<SceneObject>* m_sceneGraph;
	std::vector<DisplayObject>* m_displayList;
	int m_currentSelectionID;
	std::string texPathWindow;

	ToolMain* m_ToolSystem;
	CWnd* pWnd;
	float newPosXFloat;
	float newPosYFloat;
	float newPosZFloat;

	float newRotXFloat;
	float newRotYFloat;
	float newRotZFloat;

	float newScaleXFloat;
	float newScaleYFloat;
	float newScaleZFloat;


	DECLARE_MESSAGE_MAP()
public:
	// Control variable for more efficient access of the listbox
	//CListBox m_listBox;
	virtual BOOL OnInitDialog() override;
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	//functions for changing the position
	afx_msg void OnXPosChanged();
	afx_msg void OnYPosChanged();
	afx_msg void OnZPosChanged();

	//functions for changing the rotation
	afx_msg void OnXRotChanged();
	afx_msg void OnYRotChanged();
	afx_msg void OnZRotChanged();

	//functions for changing the scale
	afx_msg void OnXScaleChanged();
	afx_msg void OnYScaleChanged();
	afx_msg void OnZScaleChanged();
};

INT_PTR CALLBACK ModifyObjectProc(HWND   hwndDlg, UINT   uMsg, WPARAM wParam, LPARAM lParam);
