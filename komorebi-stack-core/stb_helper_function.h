#include <Windows.h>
#include <dwmapi.h>
#include <vector>
#include <json/json.h>
#include <filesystem>
#include <functional>
#include <thread>
#include <utility>
#include <iostream>
//#include "komorebi_predefined.h"

#define WM_KOMOREBI_EVENT (WM_USER+1)


namespace fs = std::filesystem;
#define MAX_BUFFER 2048


namespace kenobi {

	Json::Value read_json(const std::string& str);

	struct NamedPipe {
		HANDLE m_hpipe;
		std::wstring m_name;
		bool m_is_valid;
		const static std::wstring m_prefix;
		HWND m_subscribed_window;

		std::thread m_thread;
		NamedPipe() : m_subscribed_window(NULL), m_hpipe(NULL), m_is_valid(false), m_thread() {};
		
		void operator=(NamedPipe&& other) noexcept {
			m_hpipe = other.m_hpipe;
			m_is_valid = other.m_is_valid;
			m_name = std::move(other.m_name);
			m_thread = std::move(other.m_thread);
			m_subscribed_window = other.m_subscribed_window;
		}
		//std::vector<std::function<std::string>> m_callback;
		std::wstring get_name() {
			return m_name;
		}
		NamedPipe& init(const std::wstring name) {
			m_name = name;
			m_hpipe = CreateNamedPipe((m_prefix + name).c_str(),
				PIPE_ACCESS_DUPLEX,
				PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,   // FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists...
				1,
				1024 * 16,
				1024 * 16,
				NMPWAIT_USE_DEFAULT_WAIT,
				NULL);

			return *this;
		}

		NamedPipe& set_subscribed_window(HWND w) {
			m_subscribed_window = w; 
		return *this; }
		NamedPipe& run() {
			m_thread = std::move(std::thread(listen_thread, m_hpipe, m_subscribed_window));
			return *this;
		};
		~NamedPipe() {
			DisconnectNamedPipe(m_hpipe);
		}

		void add_listener(void(*callback)) {

		}

		static void listen_thread(HANDLE hPipe, HWND subscribed_win) {
			char buffer[MAX_BUFFER];
			DWORD dwRead;
			static int ss= 0;
			while (hPipe != INVALID_HANDLE_VALUE)
			{

				std::cout << "hpipe :" << hPipe << std::endl;

				if (ConnectNamedPipe(hPipe, NULL) != FALSE)   // wait for someone to connect to the pipe
				{
					std::string json_str;
					int parentless = 0;
					while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE)
					{

						buffer[dwRead] = '\0';
						for (int i = 0; i < dwRead; i++) {
							switch (buffer[i]) {
							case '{':
								parentless++;
								break;
							case '}':
								parentless--;
								break;
							}
						}
						json_str += buffer;

						if (parentless == 0) {
							//std::cout << std::endl << std::endl<< ss << std::endl;
							Json::Value* t = new Json::Value(read_json(json_str));
							//std::cout << read_json(json_str) << std::endl;
							json_str.clear();
							ss++;
							PostMessageA(subscribed_win, WM_KOMOREBI_EVENT, reinterpret_cast<WPARAM>(t), reinterpret_cast<LPARAM>(nullptr));
							//break;
						}
						}
					ss++;
					//std::cout << ss << std::endl;
					//std::cout <<json_str << std::endl;
					/* do something with data in buffer */
					std::cout << buffer << std::endl;
					Json::Value root = read_json(json_str);
					root["encoding"] = "utf-8";
					root["indent"]["length"] = 4;
					root["indent"]["use_space"] = true;
					std::cout << root << std::endl;
				}
			}
		}

	};
	const std::wstring NamedPipe::m_prefix = L"\\\\.\\pipe\\";

	inline COLORREF make_RGB(int r, int g, int b) {
		return RGB((r), (g), (b));
	}


	Json::Value read_json(const std::string& str) {
		Json::Value root;
		Json::Reader s;
		s.parse(str, root);
		return root;
	}






}