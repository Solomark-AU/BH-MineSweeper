#include <iostream>
#include <string>
#include <time.h>

std::string get_FormatTime()
{
    time_t currentTime;
    time(&currentTime);
    tm *t_tm = localtime(&currentTime);
    char formatTime[64] = {0};
    snprintf(formatTime, 64, "%04d-%02d-%02d %02d:%02d:%02d",
             t_tm->tm_year + 1900,
             t_tm->tm_mon + 1,
             t_tm->tm_mday,
             t_tm->tm_hour,
             t_tm->tm_min,
             t_tm->tm_sec);
    return std::string(formatTime);
}


void report_Info(std::string info, int datas[], int len) {
    std::cout << "[Info](" << get_FormatTime() << ") " << info << " with datas -> ";
    for (int i = 0; i < len; i++)
        std::cout << datas[i] << ", ";
    std::cout << "\n";
}

void report_Warn(std::string warn, int datas[], int len) {
    std::cout << "[Warn](" << get_FormatTime() << ") " << warn << " with datas -> ";
    for (int i = 0; i < len; i++)
        std::cout << datas[i] << ", ";
    std::cout << "\n";
}

void report_Error(std::string error, int datas[], int len) {
    std::cout << "[Error](" << get_FormatTime() << ") " << error << " with datas -> ";
    for (int i = 0; i < len; i++)
        std::cout << datas[i] << ", ";
    std::cout << "\n";
}

