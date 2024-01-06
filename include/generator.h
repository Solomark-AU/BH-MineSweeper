#ifndef GENERATOR
#define GENERATOR
class Map
{
public:
    int length, width;
    int map[1005][1005];
};
Map generate(int, int, int);
#endif