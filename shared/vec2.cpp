#ifndef HEADER_GUARD_VEC2
#define HEADER_GUARD_VEC2

#include <iostream>

struct vec2 {
    int x, y;
};

void print_vec(vec2& vec) {
    std::cout << vec.x << ", " << vec.y << std::endl;
}

vec2 rotate90(vec2& vec) {
    return vec2 { -vec.y, vec.x };
}

vec2 operator+(vec2& v1, vec2& v2) {
    return vec2 { v1.x + v2.x, v1.y + v2.y };
}

vec2 operator-(vec2& v1, vec2& v2) {
    return vec2 { v1.x - v2.x, v1.y - v2.y };
}

void operator+=(vec2& v1, vec2& v2) {
    v1.x += v2.x;
    v1.y += v2.y;
}

void operator-=(vec2& v1, vec2& v2) {
    v1.x -= v2.x;
    v1.y -= v2.y;
}

bool operator==(vec2& v1, vec2& v2) {
    return (v1.x == v2.x) && (v1.y == v2.y);
};

#endif