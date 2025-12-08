// MIT License
// 
// Copyright(c) 2016 William Barry
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#pragma once

#define NOMINMAX
#define _WINSOCKAPI_
#pragma comment(lib, "rpcrt4.lib")
#include <windows.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <map>
#include <assert.h>
#include <list>
#include <vector>
#include <queue>
#include <functional>
#include <memory>
#include <chrono>
#include <thread>
#include <fstream>
#include <math.h>
#include <random>

// Feel free to add more here!
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_rect.h>
#include <SDL_events.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "json.hpp"
#include "StandardTypes.h"
#include "TypeClass.h"
#include "EngineTime.h"
#include "Gameplay.h"
#include "Utility.h"

#include "Debug.h"


#define M_ASSERT(cond, cstr)                                                  \
    do {                                                                      \
      if (!(cond)) {                                                          \
        const char* _msg__ = (cstr);                                          \
        if (_msg__) {                                                         \
          OutputDebugStringA(_msg__);                                         \
          OutputDebugStringA("\n");                                           \
        }                                                                     \
        std::abort();                                                         \
      }                                                                       \
    } while (0)

#define DEBUG_LOG(indent, log) std::cout << std::setw(indent) << "" << log << std::endl;