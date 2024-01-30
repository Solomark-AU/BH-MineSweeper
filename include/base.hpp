#ifndef BASE
#define BASE
#include "expand.hpp"
#include <iostream>
class Map
{
public:
    int length, width;
    // map:雷or非雷
    // 1->Mine   0->Not Mine
    int map[1005][1005];
    // dismap:显示出的内容
    // -1：未知 0:空白 1-8已解锁的位置的数字 9：标记
    int dismap[1005][1005];
};
#endif