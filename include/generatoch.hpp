#ifndef GENERARTOCH
#define GENERARTOCH
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <map>
#include <queue>
#include "expand.hpp"

class tileMap
{
public:
    tileMap(int LENGTH, int WIDTH, int MINES)
    {
        int report[3] = {LENGTH, WIDTH, MINES};
        report_Info("Map generator ready", report, 3);
        this->LENGTH = LENGTH, this->WIDTH = WIDTH, this->MINES = MINES;
        this->datas.resize(LENGTH);
        this->display.resize(LENGTH);
        this->tiles.resize(LENGTH);
        for (int i = 0; i < LENGTH; i++)
            this->datas[i].resize(WIDTH);
        for (int i = 0; i < LENGTH; i++)
            this->tiles[i].resize(WIDTH);
        for (int i = 0; i < LENGTH; i++)
            this->display[i].resize(WIDTH);
        std::default_random_engine e;
        std::uniform_int_distribution<int> disX(0, LENGTH - 1);
        std::uniform_int_distribution<int> disY(0, WIDTH - 1);
        while (MINES)
        {
            int x = disX(e);
            int y = disY(e);
            if (!this->datas[x][y])
            {
                this->datas[x][y] = true;
                MINES--;
            }
            int report[3] = {x, y, MINES};
            report_Info("Create a mine", report, 3);
        }
        for (int i = 0; i < LENGTH; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                int numbers = 0;
                if (this->datas[i][j])
                {
                    this->tiles[i][j] = -1;
                    continue;
                }
                if (i - 1 >= 0 && this->datas[i - 1][j])
                    numbers++;
                if (i + 1 <= LENGTH - 1 && this->datas[i + 1][j])
                    numbers++;
                if (j - 1 >= 0 && this->datas[i][j - 1])
                    numbers++;
                if (j + 1 <= WIDTH - 1 && this->datas[i][j + 1])
                    numbers++;
                if (i - 1 >= 0 && j - 1 >= 0 && this->datas[i - 1][j - 1])
                    numbers++;
                if (i - 1 >= 0 && j + 1 <= WIDTH - 1 && this->datas[i - 1][j + 1])
                    numbers++;
                if (i + 1 <= LENGTH - 1 && j - 1 >= 0 && this->datas[i + 1][j - 1])
                    numbers++;
                if (i + 1 <= LENGTH - 1 && j + 1 <= WIDTH - 1 && this->datas[i + 1][j + 1])
                    numbers++;
                this->tiles[i][j] = numbers;
            }
        }
        report_Info("Create the display arrays", {}, 0);
        report_Info("The map is generated", {}, 0);
        this->images[0] = '\0';
        this->images[1] = '1';
        this->images[2] = '2';
        this->images[3] = '3';
        this->images[4] = '4';
        this->images[5] = '5';
        this->images[6] = '6';
        this->images[7] = '7';
        this->images[8] = '8';
        this->images[-1] = '@'; // flags
        this->images[-2] = '?'; // uncertain
        report_Info("The map's display elements is ready", {}, 0);
        for (int i = 0; i < this->LENGTH; i++)
            for (int j = 0; j < this->WIDTH; j++)
                this->display[i][j] = '#';
    }
    //before has been updated into generator.hpp
    bool sweep(int x, int y)
    {
        if (x < 0 && x > this->LENGTH && y < 0 && y > this->WIDTH) {
            std::cout << "Error\n";
            return true;
        }
        if (this->datas[x][y])
            return false;
        else {
            this->datas[x][y] = -2;
            this->update();
            return true;
        }
    }

    void update()
    {
        for (int i = 0; i < LENGTH; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if (!this->tiles[i][j])
                {
                    std::queue<coordination> Q;
                    Q.push((coordination){i, j});
                    while (!Q.empty())
                    {
                        coordination top = Q.front();
                        Q.pop();
                        if (i - 1 >= 0 && !this->tiles[i - 1][j])
                        {
                            Q.push((coordination){i - 1, j});
                            this->datas[i - 1][j] = -2;
                        }
                        else if (this->datas[i - 1][j] == 1)
                            this->datas[i - 1][j] = -2;

                        if (i + 1 <= LENGTH - 1 && !this->tiles[i + 1][j])
                        {
                            Q.push((coordination){i + 1, j});
                            this->datas[i + 1][j] = -2;
                        }
                        else if (this->datas[i + 1][j] == 1)
                            this->datas[i + 1][j] = -2;
                        if (j - 1 >= 0 && !this->tiles[i][j - 1])
                        {
                            Q.push((coordination){i, j - 1});
                            this->datas[i][j - 1] = -2;
                        }
                        else if (this->datas[i][j - 1] == 1)
                            this->datas[i][j - 1] = -2;
                        if (j + 1 <= WIDTH - 1 && !this->tiles[i][j + 1])
                        {
                            Q.push((coordination){i, j + 1});
                            this->datas[i][j + 1] = -2;
                        }
                        else if (this->datas[i][j + 1] == 1)
                            this->datas[i][j + 1] = -2;
                        if (i - 1 >= 0 && j - 1 >= 0 && !this->tiles[i - 1][j - 1])
                        {
                            Q.push((coordination){i - 1, j - 1});
                            this->datas[i - 1][j - 1] = -2;
                        }
                        else if (this->datas[i - 1][j - 1] == 1)
                            this->datas[i - 1][j - 1] = -2;

                        if (i - 1 >= 0 && j + 1 <= WIDTH - 1 && !this->tiles[i - 1][j + 1])
                        {
                            Q.push((coordination){i - 1, j + 1});
                            this->datas[i - 1][j + 1] = -2;
                        }
                        else if (this->datas[i - 1][j + 1] == 1)
                            this->datas[i - 1][j + 1] = -2;

                        if (i + 1 <= LENGTH - 1 && j - 1 >= 0 && !this->tiles[i + 1][j - 1])
                        {
                            Q.push((coordination){i + 1, j - 1});
                            this->datas[i + 1][j - 1] = -2;
                        }
                        else if (this->datas[i + 1][j - 1] == 1)
                            this->datas[i + 1][j - 1] = -2;

                        if (i + 1 <= LENGTH - 1 && j + 1 <= WIDTH - 1 && !this->tiles[i + 1][j + 1])
                        {
                            Q.push((coordination){i + 1, j + 1});
                            this->datas[i + 1][j + 1] = -2;
                        }
                        else if (this->datas[i + 1][j + 1] == 1)
                            this->datas[i + 1][j + 1] = -2;
                    }
                }
            }
        }
        for (int i = 0; i < this->LENGTH; i++)
            for (int j = 0; j < this->WIDTH; j++)
                this->display[i][j] = this->images[this->tiles[i][j]];
    }

    void display_map()
    {
        for (int i = 0; i < this->LENGTH; i++)
        {
            for (int j = 0; j < this->WIDTH; j++)
                if (this->datas[i][j] == -2)
                    std::cout << display[i][j];
                else
                    std::cout << '#';
            std::cout << "\n";
        }
    }

private:
    int LENGTH, WIDTH, MINES;
    std::vector<std::vector<bool>> datas;
    std::vector<std::vector<int>> tiles;
    std::vector<std::vector<int>> display;
    std::map<int, char> images;
    struct coordination
    {
        int x, y;
    };
};

#endif