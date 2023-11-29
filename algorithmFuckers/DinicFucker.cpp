#include <iostream>
#include <vector>
#include <queue>

#define private private:
#define public public:
#ifndef INT_MAX
#define INT_MAX 0x7fffffff
#endif
 
/**
 * @class Dinic
 * @brief 用于求解最大流问题的Dinic算法对象
*/
class Dinic{
    private struct Edge{
        public int to, capacity, flow, reverseIndex;
        public Edge(int to, int capacity, int flow, int reverseIndex){
            this->to = to;
            this->capacity = capacity;
            this->flow = flow;
            this->reverseIndex = reverseIndex;
        }
    };
 
    private std::vector<std::vector<Edge>> graph;
    private std::vector<int> levels;
    private std::vector<int> iterator;
    private int graphSize;
 
    private int FindFlowByDFS(int from, int to, int currentMinFlow){
        if(from == to){
            return currentMinFlow;
        }
 
        for(int& i = this->iterator[from]; i < this->graph[from].size(); i++){
            Edge& edge = graph[from][i];
            if(levels[edge.to] == levels[from] + 1 && edge.flow < edge.capacity){
                int flow = this->FindFlowByDFS(edge.to, to, std::min(currentMinFlow, edge.capacity - edge.flow));
                if(flow > 0){
                    edge.flow += flow;
                    graph[edge.to][edge.reverseIndex].flow -= flow;
                    return flow;
                }
            }
        }
        return 0;
    }
 
    private bool BuildLevelGraph(int from, int to){
        std::fill(levels.begin(), levels.end(), -1);
        levels[from] = 0;
        std::queue<int> queue;
        queue.push(from);
        while(!queue.empty()){
            int current = queue.front();
            queue.pop();
            for(const Edge& edge : graph[current]){
                if(levels[edge.to] == -1 && edge.flow < edge.capacity){
                    levels[edge.to] = levels[current] + 1;
                    queue.push(edge.to);
                }
            }
        }
        return levels[to] != -1;
    }
 
    public Dinic(int nodeCount) : graphSize(nodeCount), graph(nodeCount), levels(nodeCount), iterator(nodeCount) {}
    /**
     * @brief 获取该图的最大流
     * @param from 最大流的求解起点
     * @param to 最大流的求解终点
     * @return 最大流
    */
    public long long Solve(int from, int to){
        long long maxFlow = 0;
        while(this->BuildLevelGraph(from, to)){
            std::fill(this->iterator.begin(), this->iterator.end(), 0);
            int flow;
            while((flow = this->FindFlowByDFS(from, to, INT_MAX))){
                maxFlow += flow;
            }
        }
        return maxFlow;
    }
 
    /**
     * @brief 向Dinic目标图中加入一条从from到to的管道，最大流量为maxFlow
     * @param from 管道的起点（从0开始）
     * @param to 管道的终点（从0开始）
     * @param maxFlow 这条管道的最大流量
    */
    public void AddEdge(int from, int to, int maxFlow){
        this->graph[from].emplace_back(to, maxFlow, 0, graph[to].size());
        this->graph[to].emplace_back(from, 0, 0, graph[from].size() - 1);
    }
};
 
// 使用示例
void Function(){
    int vertexCount, edgeCount, source, sink;
    std::cin >> vertexCount >> edgeCount >> source >> sink;
    Dinic dinicSolver(vertexCount);
    for(int i = 0; i < edgeCount; i++){
        int from, to, maxCapacity;
        std::cin >> from >> to >> maxCapacity;
        dinicSolver.AddEdge(from - 1, to - 1, maxCapacity);
    }
    std::cout << dinicSolver.Solve(source - 1, sink - 1) << std::endl;
}