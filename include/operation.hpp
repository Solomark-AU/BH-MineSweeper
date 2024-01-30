#ifndef OPERATION
#define OPERATION
#include "base.hpp"
#include <queue>
void update(int m, int n, Map M)
{
    struct point
    {
        int x, y;
    };
    std::queue<point> q;
    q.push(point{m, n});
    int move[10][2]{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    while (!q.empty())
    {
        int x = q.front().x, y = q.front().y;
        q.pop();
        for (int i = 0; i < 8; i++)
        {
            x = x + move[i][0];
            y = y + move[i][1];
            if (x > 0 && x <= M.length && y > 0 && y <= M.width && M.map[x][y] == 0 && M.dismap[x][y] == -1)
            {
                q.push(point{x, y});
                int numbers = 0;
                for (int j = 0; j < 8; j++)
                {
                    if (x + move[j][0] > 0 && x + move[j][0] <= M.length && y + move[j][1] > 0 && y + move[j][1] <= M.width && M.map[x + move[j][0]][y + move[j][1]] == 1)
                        numbers++;
                }
                M.dismap[x][y] = numbers;
            }
            x = x - move[i][0];
            y = y - move[i][1];
        }
    }
}
int sweep(int x, int y, Map m)
{
    if (x < 1 || x > m.length || y < 1 || y > m.width)
        return -1;
    if (m.map[x][y])
        return 0;
    update(x, y, m);
    return 1;
}
void print(int x, int y, Map m)
{
    for (int i = 1; i <= m.width; i++)
        std::cout << "-";
    std::cout << std::endl;
    for (int i = 1; i <= m.length; i++)
    {
        std::cout << "|";
        for (int j = 1; j <= m.width; j++)
        {
            if (m.dismap[i][j] == -1)
                std::cout << "#";
            else if (m.dismap[i][j] == 9)
                std::cout << "@";
            else if (m.dismap[i][j] == 0)
                std::cout << " ";
            else
                std::cout << m.dismap[i][j];
        }
        std::cout << "|";
        std::cout << std::endl;
    }
    for (int i = 1; i <= m.width; i++)
        std::cout << "-";
    std::cout << std::endl;
}
#endif