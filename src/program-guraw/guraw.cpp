//=============================================================================
// Gura Programming Language
// Copyright (C) 2011-2018 ypsitau
//=============================================================================
#include <gura.h>
#include <WindowsX.h>

static HINSTANCE g_hInst = nullptr;

namespace Gura {

const char *g_szTitle = "Gura Executable for Windows";
const char *g_msgUsage =
"usage: guraw [option] [file] [arg] ...\n"
"available options:\n"
"-h             print this help\n"
"-i module[,..] import module(s) before parsing\n"
"-I dir         specify a directory to search for modules\n"
"-c cmd         execute program from command line\n"
"-C dir         change directory before executing scripts\n"
"-v             print version string\n";

//-----------------------------------------------------------------------------
// ErrorWindow
//-----------------------------------------------------------------------------
class ErrorWindow {
private:
	enum {
		ID_FIRST = 1000,
		IDC_Label,
		IDC_Usage,
	};
private:
	HWND _hwndLabel;
	HWND _hwndUsage;
	HWND _hwndBtnOK;
public:
	inline ErrorWindow() {}
	LRESULT Show(const char *strErr);
private:
	LRESULT WndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProcStub(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
	void OnSize(HWND hwnd, UINT state, int cx, int cy);
	void OnChar(HWND hwnd, TCHAR ch, int cRepeat);
	void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
};

//-----------------------------------------------------------------------------
// Main entry
//-----------------------------------------------------------------------------
int MainW(int argc, const char *argv[])
{
	static const Option::Info optInfoTbl[] = {
		{ "help",			'h', Option::TYPE_Flag	},
		{ "import",			'i', Option::TYPE_Value	},
		{ "command",		'c', Option::TYPE_Value	},
		{ "directory",		'C', Option::TYPE_Value	},
		{ "quiet",			'q', Option::TYPE_Flag	},
		{ "version",		'v', Option::TYPE_Flag	},
	};
	Signal sig;
	AutoPtr<Environment> pEnv(new Environment(sig));
	Environment &env = *pEnv;
	if (!env.InitializeAsRoot(argc, argv, optInfoTbl, ArraySizeOf(optInfoTbl))) {
		sig.PrintSignal(*env.GetConsoleErr());
		return 1;
	}
	Option &opt = env.GetOption();
	if (opt.IsSet("version")) {
		ErrorWindow().Show(g_msgUsage);
		return 0;
	}
	if (opt.IsSet("help")) {
		ErrorWindow().Show(g_msgUsage);
		return 0;
	}
	if (opt.IsSet("directory") && !OAL::ChangeCurDir(opt.GetString("directory", ""))) {
		::MessageBox(nullptr,
			"failed to change the current directory",
			g_szTitle, MB_ICONERROR);
		return 1;
	}
	bool interactiveFlag = true;
	if (opt.IsSet("import")) {
		foreach_const (StringList, pModuleNames, opt.GetStringList("import")) {
			if (!env.ImportModules(pModuleNames->c_str(), false, false)) {
				ErrorWindow().Show(sig.GetError().MakeText().c_str());
				return 1;
			}
		}
	}
	if (opt.IsSet("command")) {
		foreach_const (StringList, pCmd, opt.GetStringList("command")) {
			const char *cmd = pCmd->c_str();
			if (::strcmp(cmd, "") == 0) continue;
			AutoPtr<Expr_Root> pExprRoot(new Expr_Root());
			ExprOwner &exprOwner = pExprRoot->GetExprOwner();
			if (!Parser(sig, SRCNAME_cmdline).ParseString(env, exprOwner, cmd, true)) {
				ErrorWindow().Show(sig.GetError().MakeText().c_str());
				return 1;
			}
			if (exprOwner.empty()) {
				ErrorWindow().Show("incomplete command");
			} else {
				Value result = pExprRoot->Exec(env);
				if (sig.IsSignalled()) {
					ErrorWindow().Show(sig.GetError().MakeText().c_str());
					return 1;
				} else if (result.IsValid()) {
					env.GetConsole()->Println(sig, result.ToString().c_str());
				}
			}
		}
		interactiveFlag = false;
	}
	const char *encoding = opt.GetString("coding", "utf-8");
	if (argc >= 2) {
		String sourceName = OAL::FromNativeString(argv[1]);
		AutoPtr<Expr_Root> pExprRoot(Parser(sig, sourceName).ParseStream(env,
												sourceName.c_str(), encoding));
		if (sig.IsSignalled()) {
			ErrorWindow().Show(sig.GetError().MakeText().c_str());
			return 1;
		}
		pExprRoot->Exec(env);
		if (sig.IsSignalled()) {
			ErrorWindow().Show(sig.GetError().MakeText().c_str());
			sig.ClearSignal();
		}
		interactiveFlag = false;
	}
	if (interactiveFlag) {
		ErrorWindow().Show(g_msgUsage);
	}
	return 0;
}

//-----------------------------------------------------------------------------
// ErrorWindow
//-----------------------------------------------------------------------------
LRESULT ErrorWindow::Show(const char *strErr)
{
	const char *lpClassName = "guraw";
	WNDCLASSEX wc;
	wc.cbSize			= sizeof(wc);
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= WndProcStub;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 32;
	wc.hInstance		= g_hInst;
	wc.hIcon			= ::LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor			= ::LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground	= reinterpret_cast<HBRUSH>(COLOR_3DFACE + 1);
	wc.lpszMenuName		= nullptr;
	wc.lpszClassName	= lpClassName;
	wc.hIconSm			= ::LoadIcon(nullptr, IDI_APPLICATION);
	::RegisterClassEx(&wc);
	HWND hwnd = ::CreateWindow(lpClassName, g_szTitle,
				WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
				540, 300, nullptr, nullptr, g_hInst, nullptr);
	::SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG>(this));
	do {
		_hwndLabel = ::CreateWindow("static", Version::GetBanner(false),
				WS_CHILD | WS_VISIBLE,
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				hwnd, reinterpret_cast<HMENU>(IDC_Label), g_hInst, nullptr);
		SetWindowFont(_hwndLabel, GetStockFont(DEFAULT_GUI_FONT), FALSE);
	} while (0);
	do {
		_hwndUsage = ::CreateWindow("edit", Replace(strErr, "\n", "\r\n", -1, false).c_str(),
				WS_CHILD | WS_VISIBLE | SS_SUNKEN | ES_MULTILINE,
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				hwnd, reinterpret_cast<HMENU>(IDC_Usage), g_hInst, nullptr);
		SetWindowFont(_hwndUsage, GetStockFont(ANSI_FIXED_FONT), FALSE);
	} while (0);
	do {
		_hwndBtnOK = ::CreateWindow("button", "OK",
				WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
				CW_USEDEFAULT, CW_USEDEFAULT, 80, 20,
				hwnd, reinterpret_cast<HMENU>(IDOK), g_hInst, nullptr);
		SetWindowFont(_hwndBtnOK, GetStockFont(DEFAULT_GUI_FONT), FALSE);
	} while (0);
	::ShowWindow(hwnd, SW_SHOW);
	::UpdateWindow(hwnd);
	MSG msg;
	while (::GetMessage(&msg, nullptr, 0, 0)) {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT ErrorWindow::WndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	switch (nMsg) {
	case WM_SIZE: HANDLE_WM_SIZE(hwnd, wParam, lParam, OnSize); break;
	case WM_CHAR: HANDLE_WM_CHAR(hwnd, wParam, lParam, OnChar); break;
	case WM_COMMAND: HANDLE_WM_COMMAND(hwnd, wParam, lParam, OnCommand); break;
	case WM_DESTROY: ::PostQuitMessage(0); return 0;
	}
	return ::DefWindowProc(hwnd, nMsg, wParam, lParam);
}

LRESULT CALLBACK ErrorWindow::WndProcStub(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	return reinterpret_cast<ErrorWindow *>(::GetWindowLongPtr(hwnd,
						GWLP_USERDATA))->WndProc(hwnd, nMsg, wParam, lParam);
}

void ErrorWindow::OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	RECT rcClient;
	RECT rcBtnOK;
	::GetClientRect(hwnd, &rcClient);
	const int htMgn = 4;
	const int htMgnTop = 8, htMgnBottom = 4;
	int y = htMgnTop;
	::GetWindowRect(_hwndBtnOK, &rcBtnOK);
	do {
		int x = 0;
		int cx = rcClient.right - rcClient.left;
		int cy = 20;
		::SetWindowPos(_hwndLabel, nullptr, x, y, cx, cy, SWP_NOZORDER);
		y += cy;
	} while (0);
	do {
		int x = 0;
		int cx = rcClient.right - rcClient.left;
		int cy = rcClient.bottom - ((rcBtnOK.bottom - rcBtnOK.top) + htMgn + htMgnBottom + y);
		::SetWindowPos(_hwndUsage, nullptr, x, y, cx, cy, SWP_NOZORDER);
		y += cy + htMgn;
	} while (0);
	do {
		int x = ((rcClient.right - rcClient.left) - (rcBtnOK.right - rcBtnOK.left)) / 2;
		::SetWindowPos(_hwndBtnOK, nullptr, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		y += cy;
	} while (0);
}

void ErrorWindow::OnChar(HWND hwnd, TCHAR ch, int cRepeat)
{
	if (ch == VK_ESCAPE) {
		::DestroyWindow(hwnd);
	} else if (ch == VK_RETURN) {
		::DestroyWindow(hwnd);
	}
}

void ErrorWindow::OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDOK) {
		::DestroyWindow(hwnd);
	}
}

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
											LPSTR lpCmdLine, int nCmdShow)
{
	g_hInst = hInstance;
	return Gura::MainW(__argc, const_cast<const char **>(__argv));
}
