#include <vector>
#include <iostream>
#include <unordered_map>

#include "vec2.h"
#include "map2d.h"

template <class T>
Map2D<T>::Map2D() {
    this->width = 0;
    this->height = 0;
}

template <class T>
Map2D<T>::Map2D(int width, int height, T default_val, T edge_val) {
    this->width = width;
    this->height = height;
    for(int y = 0; y < this->height; y++) {
        for(int x = 0; x < this->width; x++) {
            this->map.push_back(default_val);
        }
    }
    this->edge_val = edge_val;
}

template <class T>
Map2D<T>::Map2D(std::vector<std::string>& input, std::unordered_map<char, T>& defs, T default_val, T edge_val) {
    this->width = input[0].size();
    this->height = input.size();
    this->edge_val = edge_val;
    for(int y = 0; y < this->height; y++) {
        for(int x = 0; x < this->width; x++) {
            char key = input[y][x];
            auto it = defs.find(key);
            if(it != defs.end()) {
                this->map.push_back(it->second);
                continue;
            }
            this->map.push_back(default_val);
        }
    }
}

template <class T>
bool Map2D<T>::out_of_bounds(vec2 pos) {
    return (pos.x < 0 || pos.y < 0 || pos.x >= this->width || pos.y >= this->height);
}

template <class T>
T Map2D<T>::at(vec2 pos) {
    if(this->out_of_bounds(pos)) {
        return this->edge_val;
    }
    return this->map[pos.y * this->width + pos.x];
}

template <class T>
bool Map2D<T>::set(vec2 pos, T val) {
    if(this->out_of_bounds(pos)) {
        return false;
    }
    this->map[pos.y * this->width + pos.x] = val;
    return true;
}

template <class T>
std::vector<vec2> Map2D<T>::find(T val) {
    std::vector<vec2> res;
    for(int y = 0; y < this->height; y++) {
        for(int x = 0; x < this->width; x++) {
            if(this->at(vec2 {x, y}) == val) {
                res.push_back(vec2 {x, y});
            }
        }
    }
    return res;
}

template <class T>
int Map2D<T>::count(T val) {
    int sum = 0;
    for(int y = 0; y < this->height; y++) {
        for(int x = 0; x < this->width; x++) {
            if(this->at(vec2 {x, y}) == val) {
                sum++;
            }
        }
    }
    return sum;
}