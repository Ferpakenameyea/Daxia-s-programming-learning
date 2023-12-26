#include <iostream>
#include <vector>
#include <queue>

struct Vertex {
    std::vector<int> paths;
    int in;
    int out;
};

void TOPO(std::vector<Vertex>& graph, std::vector<int>& target) {
    std::queue<int>& queue = *new std::queue<int>();
    for(int i = 1; i <= graph.size(); i++) {
        if(graph[i].in == 0) {
            queue.push(i);
        }
    }

    while(!queue.empty()) {
        auto topI = queue.front();
        auto& top = graph[topI];
        queue.pop();
        target.push_back(topI);
        for(auto& p : top.paths) {
            graph[p].in--;
            if(graph[p].in == 0) {
                queue.push(p);
            }
        }
    }
    return;
}