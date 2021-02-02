#include "Pargon/Debugging/Log.h"

#include <mutex>

using namespace Pargon;
using namespace std::string_literals;

namespace
{
	thread_local std::string _threadName = "Unknown"s;

	struct LogData
	{
		std::mutex WriteGuard;
		std::vector<Logger*> Loggers;

		void AddLogger(Logger* logger)
		{
			std::scoped_lock lock(WriteGuard);

			Loggers.push_back(logger);
		}

		void RemoveLogger(Logger* logger)
		{
			std::scoped_lock lock(WriteGuard);

			auto location = std::find(Loggers.begin(), Loggers.end(), logger);

			if (location != Loggers.end())
				Loggers.erase(location);
		}

		void Write(const LogEntry& entry)
		{
			std::scoped_lock lock(WriteGuard);

			for (auto& logger : Loggers)
			{
				if (logger->IsEnabledFor(entry))
					logger->Log(entry);
			}
		}
	};

	auto LogData() -> struct LogData&
	{
		static struct LogData _data;
		return _data;
	}
}

auto Logger::IsEnabledFor(const LogEntry& entry) const -> bool
{
	auto categoryMatches = std::regex_match(entry.Category, _categoryExpression);
	auto typeMatches = (entry.Type & _typeMask) != LogEntryType::None;

	return categoryMatches && typeMatches;
}

void Logger::Write(std::string&& message, std::string&& category, LogEntryType type, const source_location& location)
{
	auto time = std::chrono::system_clock().now();

	LogData().Write({
		std::move(message),
		std::move(category),
		type,
		location,
		time,
		_threadName
	});
}

void Pargon::AddLogger(Logger* logger)
{
	LogData().AddLogger(logger);
}

void Pargon::RemoveLogger(Logger* logger)
{
	LogData().RemoveLogger(logger);
}

void Pargon::NameCurrentThread(std::string_view name)
{
	_threadName = name;
}

auto Pargon::CurrentThreadName() -> std::string_view
{
	return _threadName;
}
