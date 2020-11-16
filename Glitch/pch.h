#pragma once

#include <vector> 
#include <iostream>
#include <math.h>
#include <thread>
#include <assert.h>
#include <chrono>
#include <future>
#include <string>
#include <memory>
#include <unordered_map>
#include <map>
#include <sstream>
#include <functional>
#include <type_traits>
#include <filesystem>
#include <algorithm>

#include "api.h"

#include <Engine\Events\Sound\SoundAttachEvent.h>
#include <Engine\Events\Sound\OnMusicStartEvent.h>
#include <Engine\Events\Sound\OnMusicStopEvent.h>
#include <Engine\Events\Window\WindowCloseEvent.h>

using namespace std;