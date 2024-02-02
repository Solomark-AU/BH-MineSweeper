#ifndef OPERATION
#define OPERATION
#include "base.hpp"
#include <queue>

bool check(int x, int y, Map *M)
{
    if (x > 0 && x <= M->length && y > 0 && y <= M->width)
        return true;
    return false;
}

void update(int m, int n, Map *M)
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
        if (M->dismap[x][y] != -1)
            continue;
        (M->opened_box_num)++;
        int numbers = 0;
        for (int j = 0; j < 8; j++)
        {
            if (check(x + move[j][0], y + move[j][1], M) && M->map[x + move[j][0]][y + move[j][1]] == 1)
                numbers++;
        }
        M->dismap[x][y] = numbers;
        if (numbers == 0)
        {
            for (int i = 0; i < 8; i++)
            {
                if (check(x + move[i][0], y + move[i][1], M) && M->map[x + move[i][0]][y + move[i][1]] == 0 && M->dismap[x + move[i][0]][y + move[i][1]] == -1)
                    q.push(point{x + move[i][0], y + move[i][1]});
            }
        }
    }
}

int sweep(int x, int y, Map *_map)
{
    if (_map->dismap[x][y] == 9)
    {
        std::cout << "OperationError: You can\'t sweep the flag.\n";
        return 1;
    }
    else if (_map->dismap[x][y] == 0)
    {
        std::cout << "OperationError: You can't sweep this position\n";
        return 1;
    }
    else if (_map->dismap[x][y] != -1)
    {
        int number = 0, move[10][2]{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
        for (int i = 0; i < 8; i++)
        {
            if (_map->dismap[x + move[i][0]][y + move[i][1]] == 9)
                number++;
        }
        if (number == _map->dismap[x][y])
        {
            for (int i = 0; i < 8; i++)
            {
                if (_map->dismap[x + move[i][0]][y + move[i][1]] == -1)
                {
                    int k = sweep(x + move[i][0], y + move[i][1], _map);
                    if (k != 1)
                        return k;
                }
            }
        }
        else
        {
            std::cout << "OperationError: You can't sweep this position\n"; 
        }
        return 1;
    }
    else
    {
        if (_map->map[x][y])
            return 0;
        update(x, y, _map);
        if (_map->safe_box_num == _map->opened_box_num)
            return 2;
        return 1;
    }
}

void display(Map *_map)
{
    std::cout << " ";
    for (int i = 1; i <= _map->width; i++)
        std::cout << "-";
    std::cout << "\n";
    for (int j = 1; j <= _map->width; j++)
    {
        std::cout << "|";
        for (int i = 1; i <= _map->length; i++)
        {
            if (_map->dismap[i][j] == -1)
                std::cout << "#";
            else if (_map->dismap[i][j] == 9)
                std::cout << "@";
            else if (_map->dismap[i][j] == 0)
                std::cout << " ";
            else
                std::cout << _map->dismap[i][j];
        }
        std::cout << "|\n";
    }
    std::cout << " ";
    for (int i = 1; i <= _map->width; i++)
        std::cout << "-";
    std::cout << "\n";
}

void flag(int x, int y, Map *_map)
{
    if (!check(x, y, _map))
    {
        std::cout << "ValueError: Your data is out of range.\n";
        return;
    }
    if (_map->dismap[x][y] != -1 && _map->dismap[x][y] != 9)
    {
        std::cout << "OperationError: Your operation is invaild.\n";
        return;
    }
    _map->dismap[x][y] = 8 - _map->dismap[x][y];
}
#endif
