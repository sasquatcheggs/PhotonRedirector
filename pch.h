#pragma once
#pragma once

// Define these before any includes to prevent conflicts
#define WIN32_LEAN_AND_MEAN
#define _WINSOCKAPI_  // Prevent windows.h from including winsock.h

// Windows headers in correct order
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// Standard library
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>

// Detours
#include <detours.h>

// Link libraries
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "detours.lib")