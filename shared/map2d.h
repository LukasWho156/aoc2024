#ifndef HEADER_GUARD_MAP2D
#define HEADER_GUARD_MAP2D

template <class T>
class Map2D {

    private:
    int width;
    int height;
    std::vector<T> map;
    T edge_val;

    public:
    Map2D();
    Map2D(int width, int height, T default_val, T edge_val);
    Map2D(std::vector<std::string>& input, std::unordered_map<char, T>& defs, T default_val, T edge_val);
    bool out_of_bounds(vec2 pos);
    T at(vec2 pos);
    bool set(vec2 pos, T val);
    std::vector<vec2> find(T val);
    int count(T val);

};

#include "map2d.cpp"

#endif