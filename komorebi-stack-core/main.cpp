#define __ADD_KOMOREBI_HEADER_IMPL__
#include "komorebi_predefined.h"

#include "stb_helper_function.h" // helper function
#include <map>
#include <fstream>
#pragma comment(lib, "Dwmapi.lib")




std::map<std::string, std::wstring> commands = {
	{"register", L"komorebic subscribe "},
};


const COLORREF MY_COLOR_KEY = RGB(255, 128, 0);
HWND cmdHanlde = NULL;
constexpr unsigned int timerIdWindowUpdate = 1;
constexpr unsigned int timerIdFrameColor = 2;
bool tick = false;
bool minimized = false;

#define KOMOREBIC_PATH "komorebic.exe state"
#define KEMOREBIC_CMD(cmd) system("komorebic.exe state"cmd) 

std::vector<int> workspace_layer; //incoude 
std::vector<HWND> g_wrapped_window_groups;
HWND kenobi_handle = NULL;
bool init();
LRESULT _loop_function(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);



typedef struct WindowComponents {
	std::vector<HWND> m_windows;
	std::vector<HWND> m_gizmo_handle_stack;
	std::map<HWND, int> gizmo_window_handle;
	int m_idx = -1;

	enum gizmo_type {SIMPLE, ICON};
	enum gizmo_align_type {LEFT, RIGHT, TOP, BOTTOM};
	
	enum gizmo_type m_gizmo_type = ICON; //default
	enum gizmo_align_type m_gizmo_align_type = LEFT; //default
	

	WNDCLASSEX m_wc;

	void init_gizmo_window() {
		WNDCLASSEX wc = {};
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpszClassName = L"kenobi_gizmo";
		wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpfnWndProc = _loop_function;
		
		RegisterClassEx(&wc);
		m_wc = wc;
	}

	void regist_window(HWND win_hwnd) {
		m_windows.push_back(win_hwnd);

	}
	void unregist_window(HWND hwnd) {

	}


	HWND _create_gizmo_view() {
		

		HWND hand = CreateWindowEx(
		    0,                              // Optional window styles.
		    m_wc.lpszClassName,                     // Window class
		    L"Learn to Program Windows",    // Window text
		    WS_OVERLAPPEDWINDOW,            // Window style

		    // Size and position
		    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		    NULL,       // Parent window    
		    NULL,       // Menu
		    NULL,  // Instance handle
		    //hInstance,  // Instance handle
		    NULL        // Additional application data
		);


		ShowWindow(hand, SW_SHOW);
		return hand;


	}

	void _draw_gizmo(const HWND front_win, const std::vector<HWND>& win_list) {
		//if (m_idx < m_gizmo_handle_stack.size() || m_idx > m_gizmo_handle_stack.size() - 1){
		//	m_gizmo_handle_stack.push_back(_create_gizmo_view());
		//}

		//m_idx++;
		const HWND handle = m_gizmo_handle_stack[m_idx];

		//draw


	}

	void _draw_reset() {
		m_idx = -1;
	}

	void set_gizmo_type(enum gizmo_type t) {
		m_gizmo_type = t;
	}

	void _draw_frame(HWND target) {
		{
			HWND hwnd = target;
			PAINTSTRUCT ps{};
			HDC hdc = BeginPaint(hwnd, &ps);

			RECT rc{}; GetClientRect(hwnd, &rc);
			HPEN hPen = CreatePen(PS_SOLID, 5, tick ? RGB(255, 128, 1) : RGB(255, 201, 14));
			HBRUSH hBrush = CreateSolidBrush(MY_COLOR_KEY);
			HGDIOBJ hOldPen = SelectObject(hdc, hPen);
			HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);

			Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

			if (hOldPen)
				SelectObject(hdc, hOldPen);
			if (hOldBrush)
				SelectObject(hdc, hOldBrush);
			if (hPen)
				DeleteObject(hPen);
			if (hBrush)
				DeleteObject(hBrush);

			EndPaint(hwnd, &ps);
		}
	}

	void _draw_stacked_window_gizmo(const Json::Value& json) {
		const int monitor_num = json.size();
		_draw_reset();
		for (int i = 0; i < monitor_num; i++) {
			for (const Json::Value& monitor_elem : json[i]["workspaces"]["elements"]) {
				for (const Json::Value& win : monitor_elem["containers"]["elements"]) {
					//[ {class, exe, hwnd, recct, title}, ... focus {class, exe, hwnd, recct, title}]
					// if there are stacked windows exists, size is bigger than 1.
					for (const Json::Value& win_elem : win["windows"]["elements"]) {
						const bool is_stacked = win_elem.size() > 1 ? true : false;
						bool container_visible = false;

						//int left, right, top, bottom;
						HWND front_window_hwnd;
						std::vector<HWND> hwnd_list;
						for (const Json::Value& specific_win : win_elem) {
							bool specific_win_visibility = specific_win["rect"]["left"] < 0 || specific_win["rect"]["top"] < 0;
							container_visible |= specific_win_visibility;
							HWND win_hwnd = String2HWND(specific_win["hwnd"]);
							if (specific_win_visibility)
								front_window_hwnd = win_hwnd;
							hwnd_list.push_back(win_hwnd);
						}

						if (container_visible) {
							if (is_stacked) {
								_draw_gizmo(front_window_hwnd, hwnd_list);
							}
						}
					}
				}
			}
		}
	}




	// hwnd : focused window hwnd that stacked.
	void update(Json::Value& json) { // when WIN_PAINT or get Signal(immediately)
		for (auto s : json.getMemberNames())
			std::cout << s << std::endl;
		//std::cout << json << std::endl;
		std::cout << json["event"]["type"] << std::endl;
		if (json[JsonKeyword::Event]["type"] == KomorebiEvent::StackWindow) {
			std::cout << json[JsonKeyword::Event] << std::endl;
		}

		_draw_stacked_window_gizmo(json["state"]["monitors"]["elements"]);

		
	/*	std::cout << "====update end=====" << std::endl;
		std::ofstream stream;
		stream.open("write.json", 'w');
		stream << json["state"]["monitors"]["elements"] << std::endl;
		stream.close();*/
		
		
	}

	// hwnd : stacked all windows hwnd that is visible.
	void fixed_update(WPARAM wp) { //WM_TIMER
		for (HWND hwnd : m_windows) {
			if (wp == timerIdWindowUpdate)
			{
				WINDOWPLACEMENT windowPlacement = { sizeof(WINDOWPLACEMENT), };
				if (::GetWindowPlacement(cmdHanlde, &windowPlacement))
				{
					if (windowPlacement.showCmd == SW_SHOWMINIMIZED
						|| !IsWindowVisible(cmdHanlde))
					{
						ShowWindow(hwnd, SW_HIDE);
						minimized = true;
					}
					else
					{
						RECT rect = {};
						DwmGetWindowAttribute(cmdHanlde, DWMWA_EXTENDED_FRAME_BOUNDS, &rect, sizeof(rect));
						MONITORINFO monInfo;
						monInfo.cbSize = sizeof(MONITORINFO);
						GetMonitorInfoW(MonitorFromWindow(cmdHanlde, MONITOR_DEFAULTTONEAREST), &monInfo);
						if (cmdHanlde != NULL && ::IsZoomed(cmdHanlde))
						{
							rect.left = monInfo.rcWork.left;
							rect.top = monInfo.rcWork.top;
							rect.bottom = monInfo.rcWork.bottom > rect.bottom ? rect.bottom : monInfo.rcWork.bottom;
							rect.right = monInfo.rcWork.right > rect.right ? rect.right : monInfo.rcWork.right;
						}
						if (minimized)
						{
							::SetWindowPos(hwnd, cmdHanlde, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
							minimized = false;
						}
						else
						{
							::SetWindowPos(cmdHanlde, hwnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
							::SetWindowPos(hwnd, 0, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
								SWP_SHOWWINDOW);
						}
					}
				}
			}
			else if (wp == timerIdFrameColor)
			{
				tick = !tick;
				::RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
			}
		}
	}
} Window;

struct GlobalContext {
	unsigned int m_border_size;
	COLORREF     m_frame_color;

	HWND m_hwnd; //this program handle.
	kenobi::NamedPipe m_named_pipe;
	Window m_win;

	void _init_main_window() {
		WNDCLASSEX wc = {};
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpszClassName = L"Kenobi";
		wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;

		wc.lpfnWndProc = _loop_function;

		RegisterClassEx(&wc);

		m_hwnd = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_LAYERED | WS_EX_TRANSPARENT, wc.lpszClassName, L"", WS_POPUP | WS_VISIBLE | WS_DISABLED,
			0, 0, 0, 0, nullptr, nullptr, nullptr, nullptr);
		::SetTimer(m_hwnd, timerIdWindowUpdate, 50, NULL);
		::SetTimer(m_hwnd, timerIdFrameColor, 500, NULL);
		SetLayeredWindowAttributes(m_hwnd, MY_COLOR_KEY, 255, LWA_COLORKEY);
		ShowWindow(m_hwnd, SW_SHOW);
	}
	void _init_gizmo_window() {
		
	}

	void init() {
		_init_main_window();
		_init_gizmo_window();

	}

	HWND get_handle() { return m_hwnd; }


} g_context;




INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, INT nCmdShow)
{


	init();
	//cmdHanlde = FindWindow(L"ConsoleWindowClass", L"C:\\WINDOWS\\system32\\cmd.exe");

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
#ifdef _DEBUG
void connect_console() {
	if (AllocConsole() == 0)
	{
		// Handle error here. Use ::GetLastError() to get the error.
	}

	// Redirect CRT standard input, output and error handles to the console window.
	FILE* pNewStdout = nullptr;
	FILE* pNewStderr = nullptr;
	FILE* pNewStdin = nullptr;

	::freopen_s(&pNewStdout, "CONOUT$", "w", stdout);
	::freopen_s(&pNewStderr, "CONOUT$", "w", stderr);
	::freopen_s(&pNewStdin, "CONIN$", "r", stdin);
}
#else
void connect_console() {

}

#endif // DEBUG

bool init() {

	connect_console();
	g_context.init();
	g_context.m_named_pipe = std::move(kenobi::NamedPipe().init(L"kenobipipe").set_subscribed_window(g_context.get_handle()).run());
	std::wstring command = commands["register"] + g_context.m_named_pipe.get_name();
	const std::string tmp_command(command.begin(), command.end());
	std::cout << tmp_command << std::endl;
	system(tmp_command.c_str());


	//HWND hand = CreateWindowEx(
	//    0,                              // Optional window styles.
	//    CLASS_NAME,                     // Window class
	//    L"Learn to Program Windows",    // Window text
	//    WS_OVERLAPPEDWINDOW,            // Window style

	//    // Size and position
	//    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

	//    NULL,       // Parent window    
	//    NULL,       // Menu
	//    hInstance,  // Instance handle
	//    NULL        // Additional application data
	//);
	

	//ShowWindow(hand, SW_SHOW);
	return true;
}


LRESULT _loop_function(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg)
	{
	case WM_KOMOREBI_EVENT: {

		Json::Value* j = reinterpret_cast<Json::Value*>(wp);
		g_context.m_win.update(*j);
		if (j != nullptr)
			delete j;
		break;
	}	
	case WM_PAINT:
		//g_context.m_win.repaint();
		break;
	case WM_TIMER:
	{
		g_context.m_win.fixed_update(wp);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProcW(hwnd, msg, wp, lp);
	}

	return 0;
}
