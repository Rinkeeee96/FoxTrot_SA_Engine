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
#include <ctime>
#include "api.h"

#include "SceneManager/Objects/Button.h"
#include "Game/SaveGame/Savegame.h"

// also returns false when comparing null value to shared ptr
template<class T, class U>
bool compare_shared_ptr(const std::shared_ptr<T>& a, const std::shared_ptr<U>& b)
{
	if (a == b) return true;
	if (a && b) return *a == *b;
	return false;
}

using namespace std;
