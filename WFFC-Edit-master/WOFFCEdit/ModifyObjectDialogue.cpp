#include "ModifyObjectDialogue.h"

#include "resource.h"
#include "stdafx.h"


IMPLEMENT_DYNAMIC(ModifyObjectDialogue, CDialogEx)

//Message map.  Just like MFCMAIN.cpp.  This is where we catch button presses etc and point them to a handy dandy method.
BEGIN_MESSAGE_MAP(ModifyObjectDialogue, CDialogEx)
	ON_COMMAND(IDOK, &ModifyObjectDialogue::End)					//ok button
	ON_BN_CLICKED(IDOK, &ModifyObjectDialogue::OnBnClickedOk)
	//ON_LBN_SELCHANGE(IDC_LIST1, &ModifyObjectDialogue::Select)	//listbox
END_MESSAGE_MAP()

ModifyObjectDialogue::ModifyObjectDialogue(CWnd* pParent, std::vector<SceneObject>* SceneGraph)
{
}

ModifyObjectDialogue::ModifyObjectDialogue(CWnd* pParent)			//constructor used in modeless
	: CDialogEx(IDD_DIALOG2, pParent)
{
}


ModifyObjectDialogue::~ModifyObjectDialogue()
{
}

void ModifyObjectDialogue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void ModifyObjectDialogue::End()
{
	DestroyWindow();
}

BOOL ModifyObjectDialogue::OnInitDialog()
{
	return CDialogEx::OnInitDialog();
}

void ModifyObjectDialogue::PostNcDestroy()
{
	CDialogEx::PostNcDestroy();
}

void ModifyObjectDialogue::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

