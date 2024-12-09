#include <iostream>
#include <vector>

/*
Once again, pretty doable.
*/

struct file {
    long id, pos, size;
};

int main() {
    std::string input;
    std::getline(std::cin, input);
    long file_no = 0;
    bool is_file = true;
    std::vector<long> blocks;
    std::vector<file> files, gaps;
    for(auto c = input.begin(); c != input.end(); c++) {
        long len = *c - '0';
        long size = blocks.size();
        if(is_file) {
            files.push_back({file_no, size, len});
        } else {
            gaps.push_back({-1, size, len});
        }
        for(long i = 0; i < len; i++) {
            long block_id = is_file ? file_no : -1;
            blocks.push_back(block_id);
        }
        is_file = !is_file;
        if(is_file) {
            file_no++;
        }
    }
    for(auto it = blocks.begin(); it != blocks.end(); it++) {
        if(*it == -1) {
            while(*(blocks.end() - 1) == -1) {
                blocks.pop_back();
            }
            *it = *(blocks.end() - 1);
            blocks.pop_back();
        }
    }
    long sum = 0;
    for(long i = 0; i < blocks.size(); i++) {
        sum += i * blocks[i];
    }
    long sum2;
    while(files.size() >= 1) {
        auto file = files.end() - 1;
        for(auto gap = gaps.begin(); gap != gaps.end(); gap++) {
            if(gap->pos > file->pos) {
                break;
            }
            if(gap->size < file->size) {
                continue;
            }
            file->pos = gap->pos;
            gap->size -= file->size;
            gap->pos += file->size;
        }
        //std::cout << file->id << ": " << file->pos << std::endl;
        for(long i = 0; i < file->size; i++) {
            sum2 += file->id * (file->pos + i);
        }
        files.pop_back();
    }
    std::cout << sum << ", " << sum2 << std::endl;
}