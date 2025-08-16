// windows / stl includes.
#include <Windows.h>
#include <cstdint>
#include <intrin.h>
#include <xmmintrin.h>
#include <array>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <chrono>
#include <thread>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <deque>
#include <functional>
#include <map>
#include <shlobj.h>
#include <filesystem>
#include <streambuf>

#define LOG( fmt, ... ) std::printf( fmt, ##__VA_ARGS__ )
#define LOGW( fmt, ... ) std::wprintf( fmt, ##__VA_ARGS__ )

inline uint64_t baseAddr = 0x0;
inline uint64_t baseSize = 0x0;

// imgui includes.
#define IMGUI_DEFINE_MATH_OPERATORS
#include "..\lib\imgui\imgui.h"
#include "..\lib\imgui\backends\imgui_impl_dx11.h"
#include "..\lib\imgui\backends\imgui_impl_win32.h"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

// other includes.
#include "memory\memory.h"

#include "game\sdk.hpp"

#include "utils\utils.hpp"

#include "features\features.hpp"

#include "core\core.hpp"

#include "gui\menu.hpp"