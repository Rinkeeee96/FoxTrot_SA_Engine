#pragma once
#include "Glitch/Core/Core.h"
#include "spdlog/spdlog.h"
#include <spdlog/fmt/ostr.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include <stdarg.h>   

namespace Glitch {
	/// @brief
	/// Log singleton class contains multiple loggers
	class GLITCH_API Log
	{
	public:
		static void Init();

		// TODO check wheter logging in this way is thread safe (Singleton shared pointer)
		// https://stackoverflow.com/questions/14482830/stdshared-ptr-thread-safety

		/// @brief
		/// Engine logger as a shared pointer, can be used to log in multiple classes within te engine
		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		/// @brief
		/// Client logger as a shared pointer, can be used to log in multiple classes within the game
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		void LogInfo(...);

	private:
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};
}

#define GL_CORE_ERROR(...)	::Glitch::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GL_CORE_WARN(...)	::Glitch::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GL_CORE_INFO(...)	::Glitch::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GL_CORE_TRACE(...)	::Glitch::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define GL_ERROR(...)	::Glitch::Log::GetClientLogger()->error(__VA_ARGS__)
#define GL_WARN(...)	::Glitch::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GL_INFO(...)	::Glitch::Log::GetClientLogger()->info(__VA_ARGS__)
#define GL_TRACE(...)	::Glitch::Log::GetClientLogger()->trace(__VA_ARGS__)

