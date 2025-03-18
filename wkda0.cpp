// chag did most of this.
#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstdlib>

std::tm getFirstDayOfWeek(int year, int week)
{
    std::tm timeinfo = {};
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mday = 4; // January 4th is always in week 1
    timeinfo.tm_mon = 0;

    std::mktime(&timeinfo);
    int offset = (timeinfo.tm_wday == 0) ? 6 : timeinfo.tm_wday - 1;
    timeinfo.tm_mday -= offset; // Move back to Monday of week 1
    timeinfo.tm_mday += (week - 1) * 7; // Move to the requested week
    
    std::mktime(&timeinfo);
    return timeinfo;
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <year> <week>\n";
        return 1;
    }

    int year = std::atoi(argv[1]);
    int week = std::atoi(argv[2]);

    if (year < 1000 || year > 9999 || week < 1 || week > 53) {
        std::cerr << "Invalid input.\n";
        return 1;
    }

    std::tm result = getFirstDayOfWeek(year, week);
    std::cout << "The first day of week " << week << " in " << year << " is: " << std::put_time(&result, "%a %d %b %Y") << "\n";
    std::cout << "Using hte simple formatter %%c: " << week << " in " << year << " is: " << std::put_time(&result, "%c") << "\n";
    result+=3600;
    std::cout << "adding 3600 secs: " << week << " in " << year << " is: " << std::put_time(&result, "%c") << "\n";

    return 0;
}

