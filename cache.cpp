#include <iostream>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <fstream>

#define REPEAT20(x) x x x x x x x x x x x x x x x x x x x x

namespace {
    unsigned const INITIAL_SIZE_MEMORY = 1024;
    unsigned const FINAL_SIZE_MEMORY = 16 * 1024 * 1024;
    unsigned const NUM_REPEAT = 20 * 20 * 20;
    unsigned const NUM_CYCLES = 500;
}

struct Node {
	Node* next;
    Node() : next(NULL) {}
};

int getRandomValue(int i) {
    return std::rand()%i;
}

double secToNano(double value) {
    return value * 1000000000;
}

double byteToKilobyte(double value) {
    return value / 1024;
}

void linkNodes(Node* list, int n, bool random = false) {
    std::vector<int> indexes;

    for (int i=1; i < n; ++i) indexes.push_back(i);
	
    if (random) std::random_shuffle(indexes.begin(), indexes.end(), getRandomValue);

    for (int i=0; i < n; ++i) list[indexes[i]].next = &list[indexes[i+1]];
    list[indexes[n]].next = &list[indexes[0]];

}

double getAvgTimeAccess(Node* list) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    for (unsigned i = 0; i < NUM_CYCLES; i++) {
        REPEAT20(REPEAT20(REPEAT20( list = list->next; ))); // 8000 time
    }

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    return secToNano(elapsed_seconds.count() / (NUM_REPEAT * NUM_CYCLES));
}

int main() {
    std::srand(unsigned(std::time(0)));
    // clear file
    std::fstream in("cache.csv", std::ios::in);
    in.close();

    std::ofstream file("cache.csv");
    if (!file.is_open()) {
        std::cout << "File error: cache.csv";
        return 1;
    }
    file << "Memory,Time1,Time2\n";

    for (double size_memory = INITIAL_SIZE_MEMORY; size_memory < FINAL_SIZE_MEMORY; size_memory *= 1.1 ) {
        int num_nodes = size_memory / sizeof(Node);
        double size_memory_kb =  byteToKilobyte(size_memory);
        std::cout << size_memory_kb << "KB     ";
        file << size_memory_kb << ",";

        // Sequential list
        Node* list = new Node[num_nodes];
        linkNodes(list, num_nodes);
        double time = getAvgTimeAccess(list);
        std::cout << time << "     ";
        file << time << ",";
        free(list);

        // Random list
        list = new Node[num_nodes];
        linkNodes(list, num_nodes, true);
        time =  getAvgTimeAccess(list);
        std::cout << time << std::endl;
        file << time << "\n";
        free(list);
    }
    file.close();

	return 0;
}
