#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <sstream>
#include <ctime>
#include <memory>
#include <map>
#include <fstream>
#include <array>
#include <io.h>
#include <sstream>
#include <queue>
#include <algorithm>	// std::shuffle
#include <random>		// std::default_random_engine
#include <chrono>		// std::chrono::system_clock
#include <mutex>
#include "json.hpp"

using std::string;
using std::vector;
using std::map;
using std::cout;
using std::cin;
using std::endl;
using sstream = std::stringstream;
using json = nlohmann::json;