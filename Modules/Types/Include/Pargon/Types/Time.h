#pragma once

#include <chrono>

namespace Pargon
{
	class StringReader;
	class StringWriter;

	class Time
	{
	public:
		static constexpr auto FromNanoseconds(long long nanoseconds) -> Time;
		static constexpr auto FromMicroseconds(long long microseconds) -> Time;
		static constexpr auto FromMilliseconds(long long milliseconds) -> Time;
		static constexpr auto FromSeconds(double seconds) -> Time;
		static constexpr auto FromMinutes(double minutes) -> Time;
		static constexpr auto FromHours(double hours) -> Time;

		constexpr auto InNanoseconds() const -> long long;
		constexpr auto InMicroseconds() const -> long long;
		constexpr auto InMilliseconds() const -> long long;
		constexpr auto InSeconds() const -> double;
		constexpr auto InMinutes() const -> double;
		constexpr auto InHours() const -> double;

		constexpr void SetNanoseconds(long long nanoseconds);
		constexpr void SetMicroseconds(long long microseconds);
		constexpr void SetMilliseconds(long long milliseconds);
		constexpr void SetSeconds(double seconds);
		constexpr void SetMinutes(double minutes);
		constexpr void SetHours(double hours);
		
		void ToString(StringWriter& writer) const;
		void FromString(StringReader& reader);

		constexpr auto operator+=(Time other) -> Time&;
		constexpr auto operator-=(Time other) -> Time&;

		constexpr auto operator==(Time other) const -> bool;
		constexpr auto operator!=(Time other) const -> bool;
		constexpr auto operator<(Time other) const -> bool;
		constexpr auto operator>(Time other) const -> bool;
		constexpr auto operator<=(Time other) const -> bool;
		constexpr auto operator>=(Time other) const -> bool;

		constexpr auto operator-() const -> Time;
		constexpr auto operator+(Time other) const -> Time;
		constexpr auto operator-(Time other) const -> Time;
		constexpr auto operator*(Time other) const -> Time;
		constexpr auto operator/(Time other) const -> Time;

	private:
		std::chrono::nanoseconds _nanoseconds = std::chrono::nanoseconds(0);
	};

	auto GetCurrentTime() -> Time;

	constexpr auto operator""_ns(unsigned long long nanoseconds) -> Time;
	constexpr auto operator""_us(unsigned long long microseconds) -> Time;
	constexpr auto operator""_ms(unsigned long long milliseconds) -> Time;
	constexpr auto operator""_sec(long double seconds) -> Time;
	constexpr auto operator""_min(long double minutes) -> Time;
	constexpr auto operator""_hr(long double hours) -> Time;
}

constexpr
auto Pargon::Time::FromNanoseconds(long long nanoseconds) -> Time
{
	Time time;
	time.SetNanoseconds(nanoseconds);
	return time;
}

constexpr
auto Pargon::Time::FromMicroseconds(long long microseconds) -> Time
{
	Time time;
	time.SetMicroseconds(microseconds);
	return time;
}

constexpr
auto Pargon::Time::FromMilliseconds(long long milliseconds) -> Time
{
	Time time;
	time.SetMilliseconds(milliseconds);
	return time;
}

constexpr
auto Pargon::Time::FromSeconds(double seconds) -> Time
{
	Time time;
	time.SetSeconds(seconds);
	return time;
}

constexpr
auto Pargon::Time::FromMinutes(double minutes) -> Time
{
	Time time;
	time.SetMinutes(minutes);
	return time;
}

constexpr
auto Pargon::Time::FromHours(double hours) -> Time
{
	Time time;
	time.SetHours(hours);
	return time;
}

constexpr
auto Pargon::Time::InNanoseconds() const -> long long
{
	return _nanoseconds.count();
}

constexpr
auto Pargon::Time::InMicroseconds() const -> long long
{
	return std::chrono::duration_cast<std::chrono::microseconds>(_nanoseconds).count();
}

constexpr
auto Pargon::Time::InMilliseconds() const -> long long
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(_nanoseconds).count();
}

constexpr
auto Pargon::Time::InSeconds() const -> double
{
	using seconds_duration = std::chrono::duration<double, std::ratio<1, 1>>;
	return std::chrono::duration_cast<seconds_duration>(_nanoseconds).count();
}

constexpr
auto Pargon::Time::InMinutes() const -> double
{
	using minutes_duration = std::chrono::duration<double, std::ratio<60, 1>>;
	return std::chrono::duration_cast<minutes_duration>(_nanoseconds).count();
}

constexpr
auto Pargon::Time::InHours() const -> double
{
	using hours_duration = std::chrono::duration<double, std::ratio<3600, 1>>;
	return std::chrono::duration_cast<hours_duration>(_nanoseconds).count();
}

constexpr
void Pargon::Time::SetNanoseconds(long long nanoseconds)
{
	_nanoseconds = std::chrono::nanoseconds(nanoseconds);
}

constexpr
void Pargon::Time::SetMicroseconds(long long microseconds)
{
	_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::microseconds(microseconds));
}

constexpr
void Pargon::Time::SetMilliseconds(long long milliseconds)
{
	_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds(milliseconds));
}

constexpr
void Pargon::Time::SetSeconds(double seconds)
{
	using seconds_duration = std::chrono::duration<double, std::ratio<1, 1>>;
	_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(seconds_duration(seconds));
}

constexpr
void Pargon::Time::SetMinutes(double minutes)
{
	using minutes_duration = std::chrono::duration<double, std::ratio<60, 1>>;
	_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(minutes_duration(minutes));
}

constexpr
void Pargon::Time::SetHours(double hours)
{
	using hours_duration = std::chrono::duration<double, std::ratio<3600, 1>>;
	_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(hours_duration(hours));
}

constexpr
auto Pargon::Time::operator+=(Time other) -> Time&
{
	_nanoseconds += other._nanoseconds;
	return *this;
}

constexpr
auto Pargon::Time::operator-=(Time other) -> Time&
{
	_nanoseconds -= other._nanoseconds;
	return *this;
}

constexpr
auto Pargon::Time::operator==(Time other) const -> bool
{
	return _nanoseconds == other._nanoseconds;
}

constexpr
auto Pargon::Time::operator!=(Time other) const -> bool
{
	return _nanoseconds != other._nanoseconds;
}

constexpr
auto Pargon::Time::operator<(Time other) const -> bool
{
	return _nanoseconds < other._nanoseconds;
}

constexpr
auto Pargon::Time::operator>(Time other) const -> bool
{
	return _nanoseconds > other._nanoseconds;
}

constexpr
auto Pargon::Time::operator<=(Time other) const -> bool
{
	return _nanoseconds <= other._nanoseconds;
}

constexpr
auto Pargon::Time::operator>=(Time other) const -> bool
{
	return _nanoseconds >= other._nanoseconds;
}

constexpr
auto Pargon::Time::operator-() const -> Time
{
	Time time;
	time._nanoseconds = -_nanoseconds;
	return time;
}

constexpr
auto Pargon::Time::operator+(Time other) const -> Time
{
	Time time;
	time._nanoseconds = _nanoseconds + other._nanoseconds;
	return time;
}

constexpr
auto Pargon::Time::operator-(Time other) const -> Time
{
	Time time;
	time._nanoseconds = _nanoseconds - other._nanoseconds;
	return time;
}

constexpr
auto Pargon::Time::operator*(Time other) const -> Time
{
	Time time;
	time._nanoseconds = std::chrono::nanoseconds(_nanoseconds.count() * other._nanoseconds.count());
	return time;
}

constexpr
auto Pargon::Time::operator/(Time other) const -> Time
{
	Time time;
	time._nanoseconds = std::chrono::nanoseconds(_nanoseconds.count() / other._nanoseconds.count());
	return time;
}

constexpr
auto Pargon::operator""_ns(unsigned long long nanoseconds) -> Time
{
	return Time::FromNanoseconds(static_cast<long long>(nanoseconds));
}

constexpr
auto Pargon::operator""_us(unsigned long long microseconds) -> Time
{
	return Time::FromMicroseconds(static_cast<long long>(microseconds));
}

constexpr
auto Pargon::operator""_ms(unsigned long long milliseconds) -> Time
{
	return Time::FromMilliseconds(static_cast<long long>(milliseconds));
}

constexpr
auto Pargon::operator""_sec(long double seconds) -> Time
{
	return Time::FromSeconds(static_cast<double>(seconds));
}

constexpr
auto Pargon::operator""_min(long double minutes) -> Time
{
	return Time::FromMinutes(static_cast<double>(minutes));
}

constexpr
auto Pargon::operator""_hr(long double hours) -> Time
{
	return Time::FromHours(static_cast<double>(hours));
}
