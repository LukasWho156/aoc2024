#ifndef HEADER_GUARD_VEC2
#define HEADER_GUARD_VEC2

struct vec2 {
    int x, y;
};

void print_vec(vec2& vec);
vec2 rotate90(vec2& vec);
vec2 operator+(vec2& v1, vec2& v2);
vec2 operator-(vec2& v1, vec2& v2);
void operator+=(vec2& v1, vec2& v2);
void operator-=(vec2& v1, vec2& v2);
bool operator==(vec2& v1, vec2& v2);

#endif