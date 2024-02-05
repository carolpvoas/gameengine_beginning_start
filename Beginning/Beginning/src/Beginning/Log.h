#pragma once

#include "spdlog/spdlog.h"
#include <spdlog/fmt/ostr.h>

namespace Beginning {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define BG_CORE_TRACE(...)    ::Beginning::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BG_CORE_INFO(...)     ::Beginning::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BG_CORE_WARN(...)     ::Beginning::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BG_CORE_ERROR(...)    ::Beginning::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BG_CORE_CRITICAL(...) ::Beginning::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define BG_TRACE(...)         ::Beginning::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BG_INFO(...)          ::Beginning::Log::GetClientLogger()->info(__VA_ARGS__)
#define BG_WARN(...)          ::Beginning::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BG_ERROR(...)         ::Beginning::Log::GetClientLogger()->error(__VA_ARGS__)
#define BG_CRITICAL(...)      ::Beginning::Log::GetClientLogger()->critical(__VA_ARGS__)

