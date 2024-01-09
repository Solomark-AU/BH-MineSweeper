#ifndef BASE
#define BASE
class Map
{
public:
    int length, width;
    // map:雷or非雷
    int map[1005][1005]; // dismap:显示出的内容
    // 0：未知 1-8已解锁的位置的数字 9：空白 10：标记
    int dismap[1005][1005];
};
#endif