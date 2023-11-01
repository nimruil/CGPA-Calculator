#ifndef _SUPPORTFUNCTIONS_H_
#define _SUPPORTFUNCTIONS_H_

#include <iostream>
#include <chrono>

std::string todaysDate() {
	std::time_t currentTime;
	std::tm localTime;
	std::time(&currentTime);
	localtime_s(&localTime, &currentTime);
	// Extract the year, month, and day
	int year = localTime.tm_year + 1900; // Years since 1900
	int month = localTime.tm_mon + 1;     // Month (0-11)
	int day = localTime.tm_mday;          // Day of the month
	int hour = localTime.tm_hour;           // Hour (0-23)
	int minute = localTime.tm_min;          // Minute (0-59)

	int dateInt{ day * 10000 + month * 100 + (year - 2000) };
	std::string date{ std::to_string(dateInt) + "_" + std::to_string(hour) + "_" + std::to_string(minute) };
	return date;
}
#endif
