#include <iostream>
#include <vector>
#include <unordered_map>

#include "../shared/vec2.h"

#define EMPTY 0
#define WALL 1
#define EDGE -1
#define VISITED 2

/*
Pretty frustrating experience. Tried so hard to make something clever
work but couldn't quite figure it out. Had to resort to the naive
apporach, which took a couple of seconds to run, but only like 5
minutes to write. Oh well. Probably won't revisit this one to fix
up the clever solution.
*/

int vtoi(vec2& v) {
    return 1 << ((3 * v.y + v.x + 3) / 2);
}

template <class T>
class Map2D {
    
    private:
    int width;
    int height;
    std::vector<T> map;
    T edge_val;

    public:
    Map2D() {
        this->width = 0;
        this->height = 0;
    }

    Map2D(int width, int height, T default_val, T edge_val) {
        this->width = width;
        this->height = height;
        for(int y = 0; y < this->height; y++) {
            for(int x = 0; x < this->width; x++) {
                this->map.push_back(default_val);
            }
        }
        this->edge_val = edge_val;
    }

    Map2D(std::vector<std::string>& input, std::unordered_map<char, T>& defs, T default_val, T edge_val) {
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

    bool out_of_bounds(vec2 pos) {
        return (pos.x < 0 || pos.y < 0 || pos.x >= this->width || pos.y >= this->height);
    }

    T at(vec2 pos) {
        if(this->out_of_bounds(pos)) {
            return this->edge_val;
        }
        return this->map[pos.y * this->width + pos.x];
    }

    bool set(vec2 pos, T val) {
        if(this->out_of_bounds(pos)) {
            return false;
        }
        this->map[pos.y * this->width + pos.x] = val;
        return true;
    }

    std::vector<vec2> find(T val) {
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

    int count(T val) {
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

};

template <class T>
struct option {
    bool is_some;
    T val;
};

struct turn_point {
    vec2 pos, dir;
    turn_point* next;
    bool activated = false;
};

void activate(Map2D<int>& map, std::unordered_map<int, Map2D<turn_point*>>& tp_maps, Map2D<int>& danger_map, turn_point* tp) {
    if(tp->activated) {
        return;
    }
    //std::cout << "activated at ";
    //print_vec(tp->pos);
    tp->activated = true;
    auto dir = tp->dir;
    dir = rotate90(dir);
    auto risk_dir = rotate90(dir);
    auto risk_hash = vtoi(risk_dir);
    dir = rotate90(risk_dir);
    for(auto pos = tp->pos; map.at(pos) == EMPTY || map.at(pos) == VISITED; pos -= dir) {
        //std::cout << "set danger level " << risk_hash << " at ";
        //print_vec(pos);
        danger_map.set(pos, danger_map.at(pos) | risk_hash);
        auto chain = tp_maps[vtoi(dir)].at(pos);
        if(chain == NULL) {
            continue;
        }
        if(chain->activated) {
            continue;
        }
        activate(map, tp_maps, danger_map, chain);
    }
}

void propagate_activation(Map2D<int>& map, std::unordered_map<int, Map2D<turn_point*>>& tp_maps, Map2D<int>& danger_map, vec2 start, vec2 dir) {
    for(auto pos = start; map.at(pos) == EMPTY || map.at(pos) == VISITED; pos -= dir) {
        //std::cout << "set danger level " << risk_hash << " at ";
        //print_vec(pos);
        auto chain = tp_maps[vtoi(dir)].at(pos);
        if(chain == NULL) {
            continue;
        }
        if(chain->activated) {
            continue;
        }
        activate(map, tp_maps, danger_map, chain);
    }
}

bool progress(Map2D<int>& map, vec2& pos, vec2& dir) {
    int ahead = map.at(pos + dir);
    switch(ahead) {
        case EMPTY:
        case VISITED:
            pos = pos + dir;
            break;
        case WALL:
            dir = rotate90(dir);
            break;
        case EDGE:
            return false;
    }
    return true;
}

bool is_loop(Map2D<int>& map) {
    vec2 pos1 = map.find(VISITED)[0];
    vec2 dir1 {0, -1};
    vec2 pos2 = pos1;
    vec2 dir2 = dir1;
    while(true) {
        if(!progress(map, pos1, dir1)) {
            return false;
        }
        if(!progress(map, pos2, dir2)) {
            return false;
        }
        if(!progress(map, pos2, dir2)) {
            return false;
        }
        if(pos1 == pos2 && dir1 == dir2) {
            return true;
        }
    }
}

int main() {

    // read in input
    std::vector<std::string> input_map;
    for(std::string line; std::getline(std::cin, line);) {
        input_map.push_back(line);
    }
    int width = input_map[0].size();
    int height = input_map.size();
    std::unordered_map<char, int> defs;
    defs['#'] = WALL;
    defs['^'] = VISITED;
    Map2D map(input_map, defs, EMPTY, EDGE);

    // determine turn points
    std::vector<turn_point> tp_list;
    std::unordered_map<int, Map2D<turn_point*>> tp_maps;
    tp_maps[1] = Map2D<turn_point*>(width, height, NULL, NULL);
    tp_maps[2] = Map2D<turn_point*>(width, height, NULL, NULL);
    tp_maps[4] = Map2D<turn_point*>(width, height, NULL, NULL);
    tp_maps[8] = Map2D<turn_point*>(width, height, NULL, NULL);
    auto walls = map.find(WALL);
    for(auto wall = walls.begin(); wall != walls.end(); wall++) {
        vec2 dir { 1, 0 };
        for(int i = 0; i < 4; i++) {
            turn_point tp;
            tp.dir = dir;
            auto rotated = rotate90(dir);
            tp.pos = (*wall) + rotated;
            tp.next = NULL;
            if(!tp_maps[vtoi(dir)].out_of_bounds(tp.pos)) {
                tp_list.push_back(tp);
            }
            dir = rotate90(dir);
        }
    }
    for(auto tp = tp_list.begin(); tp != tp_list.end(); tp++) {
        //std::cout << "TP with dir " << vtoi(tp->dir) << " and pointer " << &*tp << " at ";
        //print_vec(tp->pos);
        tp_maps[vtoi(tp->dir)].set(tp->pos, &*tp);
    }

    // find successors for all turn points.
    std::cout << "searching for successors ..." << std::endl;
    for(auto tp = tp_list.begin(); tp != tp_list.end(); tp++) {
        vec2 dir = tp->dir;
        vec2 to_check_dir = rotate90(tp->dir);
        int to_check_hash = vtoi(to_check_dir);
        int i = 0;
        for(vec2 pos = tp->pos; !tp_maps[to_check_hash].out_of_bounds(pos); pos += dir) {
            if(tp_maps[to_check_hash].at(pos) == NULL) {
                continue;
            }
            tp->next = tp_maps[to_check_hash].at(pos);
            break;
        }
        /*
        std::cout << "tp with dir " << vtoi(tp->dir) << " at ";
        print_vec(tp->pos);
        if(tp->next == NULL) {
            std::cout << "leads nowhere" << std::endl;
        } else {
            std::cout << "leads to tp with dir " << vtoi(tp->next->dir) << " at ";
            print_vec(tp->next->pos);
        }
        */
    }

    Map2D<int> danger_map (width, height, 0, 0);
    // search for loops
    std::cout << "searching for loops ..." << std::endl;
    for(auto tp = tp_list.begin(); tp != tp_list.end(); tp++) {
        auto it1 = tp->next;
        if(it1 == NULL) {
            continue;
        }
        auto it2 = tp->next->next;
        if(it2 == NULL) {
            continue;
        }
        while(true) {
            if(it1 == it2) {
                //std::cout << "loop found!" << std::endl;
                activate(map, tp_maps, danger_map, it1);
                break;
            }
            it1 = it1->next;
            it2 = it2->next;
            if(it2 == NULL) {
                break;
            }
            it2 = it2->next;
            if(it2 == NULL) {
                break;
            }
        }
    }

    /*
    // traverse graph
    vec2 pos = map.find(VISITED)[0];
    vec2 dir {0, -1};
    propagate_activation(map, tp_maps, danger_map, pos, dir);
    Map2D<int> obstacle_map (width, height, EMPTY, EMPTY);
    for(int ahead = map.at(pos + dir); ahead != EDGE; ahead = map.at(pos + dir)) {
        if(auto tp = tp_maps[vtoi(dir)].at(pos); tp != NULL) {
            //std::cout << "possible TP at ";
            //print_vec(pos);
            activate(map, tp_maps, danger_map, tp);
        }
        if((danger_map.at(pos) & vtoi(dir)) > 0) {
            //std::cout << "possible danger spot at ";
            //print_vec(pos);
            if(map.at(pos + dir) == EMPTY) {
                obstacle_map.set(pos + dir, WALL);
            }
        }
        switch(ahead) {
            case EMPTY:
            case VISITED:
                pos = pos + dir;
                map.set(pos, VISITED);
                break;
            case WALL:
                dir = rotate90(dir);
                propagate_activation(map, tp_maps, danger_map, pos, dir);
                break;
        }
    }
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            if(map.at(vec2 {x, y}) == WALL) {
                std::cout << "#";
                continue;
            }
            if(obstacle_map.at(vec2 {x, y}) == WALL) {
                std::cout << "O";
                continue;
            }
            std::cout << ".";
        }
        std::cout << std::endl;
    }
    std::cout << map.find(VISITED).size() << ", " << obstacle_map.find(WALL).size() << std::endl;
    */

    // okay, spent so much time debugging this. let's do a naive approach instead.
    auto empties = map.find(EMPTY);
    int sum = 0;
    for(auto c = empties.begin(); c != empties.end(); c++) {
        map.set(*c, WALL);
        if(is_loop(map)) {
            sum++;
        }
        map.set(*c, EMPTY);
    }
    std::cout << sum << std::endl;

    return 0;
}