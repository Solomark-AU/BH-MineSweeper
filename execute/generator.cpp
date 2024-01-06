#include "../include/generator.h"
#include <random>
#include <ctime>
Map generate(int length, int width, int num)
{
    Map m;
    m.length = length;
    m.width = width;
    bool map[length * width + 5];
    int area = length * width;
    for (int i = 1; i <= area; i++)
        map[i] = 0;
    if (num < area / 2)
    {
        for (int i = area - num + 1; i <= area; i++)
            map[i] = 1;
        for (int i = area - num + 1; i <= area; i++)
        {
            std::mt19937 random;
            random.seed(time(0));
            int pos = random() % (i - 1) + 1;
            std::swap(map[i], map[pos]);
        }
    }
    else
    {
        for (int i = 1; i <= num; i++)
            map[i] = 1;
        for (int i = num; i <= area; i++)
        {
            std::mt19937 random;
            random.seed(time(0));
            int pos = random() % (i - 1) + 1;
            std::swap(map[i], map[pos]);
        }
    }
    for (int i = 1; i <= length; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            if (map[(i - 1) * length + j])
                m.map[i][j] = 1;
            else
                m.map[i][j] = 0;
        }
    }
    return m;
}