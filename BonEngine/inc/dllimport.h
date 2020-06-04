#pragma once

#if COMPILING_DLL
#define BON_DLLEXPORT __declspec(dllexport)
#else
#define BON_DLLEXPORT __declspec(dllimport)
#endif