#include <Windows.h>
#include <dwmapi.h>
#include <vector>
#include <json/json.h>
#include <filesystem>
#include <functional>
#include <thread>
#include <utility>
#include <iostream>
namespace fs = std::filesystem;
#define MAX_BUFFER 2048


namespace kenobi {

	Json::Value read_json(const std::string& str);

	struct NamedPipe {
		HANDLE m_hpipe;
		std::wstring m_name;
		bool m_is_valid;
		const static std::wstring m_prefix;

		std::thread m_thread;
		NamedPipe() : m_hpipe(NULL), m_is_valid(false), m_thread() {};
		
		void operator=(NamedPipe&& other) noexcept {
			m_hpipe = other.m_hpipe;
			m_is_valid = other.m_is_valid;
			m_name = std::move(other.m_name);
			m_thread = std::move(other.m_thread);
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


			m_thread = std::move(std::thread(listen_thread, m_hpipe));
			return *this;
		}

		~NamedPipe() {
			DisconnectNamedPipe(m_hpipe);
		}

		void add_listener(void(*callback)) {

		}

		static void listen_thread(HANDLE hPipe) {
			char buffer[MAX_BUFFER];
			DWORD dwRead;
			while (hPipe != INVALID_HANDLE_VALUE)
			{

				std::cout << "hpipe :" << hPipe << std::endl;

				if (ConnectNamedPipe(hPipe, NULL) != FALSE)   // wait for someone to connect to the pipe
				{
					std::string json_str;
					//while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE)
					while (true)
					{

						int res = ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL);
						std::cout << "res : " << res << std::endl;
						buffer[dwRead] = '\0';
						std::cout << buffer << std::endl;
						if (res == 0){
							std::cout << "=========" << std::endl;
							std::cout << " breaked" << std::endl;
							break;
						}
						/*if (res == 0) {
							if (dwRead < MAX_BUFFER) {
								buffer[dwRead] = '\0';
								json_str += buffer;

							}
							else {
								json_str += buffer;
								json_str += '\0';
							}
							break;
						}
						json_str += buffer;*/

						std::cout << json_str << std::endl;
					/* add terminating zero */
					}
					json_str += '\0';

					/* do something with data in buffer */
					//std::cout << buffer << std::endl;
					std::cout << read_json(buffer) << std::endl;
				}
			}
		}

	};
	const std::wstring NamedPipe::m_prefix = L"\\\\.\\pipe\\";

	inline COLORREF make_RGB(int r, int g, int b) {
		return RGB((r), (g), (b));
	}


	Json::Value read_json(const std::string& str) {
		std::cout << str << "\ntested" << std::endl;
		Json::Value root;
		std::cin >> root;
		std::cout << root << std::endl;
		std::cout << "test end " << std::endl;
		return root;
	}






}