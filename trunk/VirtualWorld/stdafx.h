// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <atlbase.h>
#include <atltypes.h>
#include <atlstr.h>
#include <atlwin.h>
#include <atlapp.h>
#include <atlcrack.h>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <vector>
#include <map>

#include "Window/atlopengl.h"

#include <ThirdParty/assimp/cimport.h>
#include <ThirdParty/assimp/scene.h>
#include <ThirdParty/assimp/postprocess.h>
#include <ThirdParty/assimp/matrix4x4.h>
#include <ThirdParty/assimp/vector3.h>