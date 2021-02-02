#pragma once

#include "Pargon/Shim.h"

#include <chrono>
#include <regex>
#include <string>
#include <string_view>

namespace Pargon
{
	struct source_location // PENDING: Non-functional until the replacement in c++20
	{
		static constexpr source_location current() noexcept
		{
			return source_location();
		}

		constexpr source_location() noexcept
		{
		}

		constexpr const char* file_name() const noexcept
		{
			return "";
		}

		constexpr const char* function_name() const noexcept
		{
			return "";
		}

		constexpr std::uint_least32_t line() const noexcept
		{
			return 0;
		}

		constexpr std::uint_least32_t column() const noexcept
		{
			return 0;
		}
	};

	enum class LogEntryType : unsigned int
	{
		None = 0,
		General = 1,
		Debug = 1 << 1,
		Warning = 1 << 2,
		Error = 1 << 3,
		Fatal = 1 << 4,
		All = ~0u
	};

	auto operator|(LogEntryType left, LogEntryType right) -> LogEntryType;
	auto operator&(LogEntryType left, LogEntryType right) -> LogEntryType;

	struct LogEntry
	{
		std::string Message;
		std::string Category;
		LogEntryType Type;
		Pargon::source_location Location;
		std::chrono::time_point<std::chrono::system_clock> Timestamp;
		std::string_view Thread;
	};

	class Logger
	{
		LogEntryType _typeMask = LogEntryType::All;
		std::regex _categoryExpression = std::regex(".*");

	public:
		auto TypeMask() const -> LogEntryType;
		auto CategoryExpression() const -> const std::regex&;

		void SetFilter(LogEntryType typeMask, std::regex categoryExpression);
		virtual auto IsEnabledFor(const LogEntry& entry) const -> bool;
		virtual void Log(const LogEntry& entry) const = 0;

	private:
		template<typename... Ts> friend struct Log;

		static void Write(std::string&& message, std::string&& category, LogEntryType type, const source_location& location);
	};

	template<typename... Ts>
	struct Log
	{
		Log(std::string_view message, Ts&&... ts, const source_location& location = source_location::current());
		Log(LogEntryType type, std::string_view category, std::string_view message, Ts&&... ts, const source_location& location = source_location::current());
	};
	
	template<typename... Ts> Log(std::string_view message, Ts&&...) -> Log<Ts...>;
	template<typename... Ts> Log(LogEntryType type, std::string_view category, std::string_view message, Ts&&...) -> Log<Ts...>;

	void AddLogger(Logger* logger);
	void RemoveLogger(Logger* logger);
	
	void NameCurrentThread(std::string_view name);
	auto CurrentThreadName() -> std::string_view;
}

inline
auto Pargon::operator|(LogEntryType left, LogEntryType right) -> LogEntryType
{
	return static_cast<LogEntryType>(static_cast<unsigned int>(left) | static_cast<unsigned int>(right));
}

inline
auto Pargon::operator&(LogEntryType left, LogEntryType right) -> LogEntryType
{
	return static_cast<LogEntryType>(static_cast<unsigned int>(left) | static_cast<unsigned int>(right));
}

inline
auto Pargon::Logger::TypeMask() const -> LogEntryType
{
	return _typeMask;
}

inline
auto Pargon::Logger::CategoryExpression() const -> const std::regex&
{
	return _categoryExpression;
}

inline
void Pargon::Logger::SetFilter(LogEntryType typeMask, std::regex categoryExpression)
{
	_typeMask = typeMask;
	_categoryExpression = categoryExpression;
}

template<typename... Ts>
Pargon::Log<Ts...>::Log(std::string_view message, Ts&&... ts, const source_location& location)
{
	auto formatted = fmt::format(message, std::forward<Ts>(ts)...);
	Logger::Write(std::move(formatted), "", LogEntryType::General, location);
}

template<typename... Ts>
Pargon::Log<Ts...>::Log(LogEntryType type, std::string_view category, std::string_view message, Ts&&... ts, const source_location& location)
{
	auto formatted = fmt::format(message, std::forward<Ts>(ts)...);
	Logger::Write(std::move(formatted), std::string(category), type, location);
}
