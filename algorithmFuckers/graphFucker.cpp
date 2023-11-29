#include <iostream>
#include "vector"
#include "queue"
#include "algorithm"
#ifndef LONG_LONG_MAX
#define LONG_LONG_MAX 0x7fffffffffffffffLL
#endif


/**
 * @class AccodingSolution
 * @brief 用于执行特定次数的函数的类。
 */
class AccodingSolution{
public:
    static void DoSomethingNTimes(void (*Function)(void)){
        int dataCount;
        std::cin >> dataCount;
        for(int i = 0; i < dataCount; i++){
            Function();
        }
    }
};

/**
 * @author MCdeDaxia
 * @class Graph
 * @brief 用于表示图并执行图算法的类。内部使用邻接表表示边
 */
class Graph{
    public:
    /**
     * @class Vertex
     * @brief 图的顶点
    */
    class Vertex;

    /**
     * @class Edge
     * @brief 图的边
    */
    class Edge;
    
    private:
    std::vector<std::vector<long long>>* matrix;
    bool generateMatrix;

    void DFSTopologicalSortUtil(int current, std::vector<bool>& visited, std::vector<Vertex>& result){
        visited[current] = true;

        for(auto path : this->vertices[current].GetPaths()){
            if(!visited[path.GetDestinationIndex()]){
                DFSTopologicalSortUtil(path.GetDestinationIndex(), visited, result);
            }
        }
        
        result.push_back(this->vertices[current]);
    }

    void PrintPathRecursive(Graph::Vertex* vertex, std::string seperator){
        if(vertex->GetParent() != nullptr){
            PrintPathRecursive(vertex->GetParent(), seperator);
        }
        std::cout << vertex->GetIndex() << seperator;
    }

    void TryRelax(Edge& path){
        auto destination = &this->vertices[path.GetDestinationIndex()];
        auto from = &this->vertices[path.GetFrom()];
        auto newDistance = from->GetDistance() + path.GetWeight();
        if(destination->GetDistance() > newDistance){
            destination->SetDistance(newDistance);
            destination->SetParent(from);
        }
    }

    long long SafeAdd(long long a, long long b){
        return (a == LONG_LONG_MAX || b == LONG_LONG_MAX) ? LONG_LONG_MAX : (a + b);
    }

    public: class Vertex{
        private:
            int index;
            long long distance;
            Vertex* parent;
            bool visited;
            std::vector<Graph::Edge> paths;
        public:
            Vertex(int index) : index(index){
                this->distance = LONG_LONG_MAX;
                this->parent = nullptr;
                this->visited = false;
            }

            Vertex(){
                this->index = -1;
                this->distance = LONG_LONG_MAX;
                this->parent = nullptr;
                this->visited = false;
            }
            
            bool IsReachable(){
                return this->distance != LONG_LONG_MAX;
            }

            int GetIndex(){
                return this->index;
            }

            long long GetDistance(){
                return this->distance;
            }

            void SetDistance(long long distance){
                this->distance = distance;
            }

            bool IsVisited(){
                return this->visited;
            }

            void SetVisited(bool visited){
                this->visited = visited;
            }

            Vertex* GetParent(){
                return this->parent;
            }

            void SetParent(Vertex* parent){
                this->parent = parent;
            }

            void AddPath(const Graph::Edge& path){
                this->paths.push_back(path);
            }

            std::vector<Graph::Edge> GetPaths(){
                return this->paths;
            }

        public: struct CompareGreater{
            public: bool operator()(const Vertex* v1, const Vertex* v2){
                return v1->distance > v2->distance;
            }
        };
    };
    public: class Edge{
        private:
            int from;
            int to;
            int weight;
        public:
            int GetDestinationIndex(){
                return this->to;
            }

            int GetWeight(){
                return this->weight;
            }

            int GetFrom(){
                return this->from;
            }

            Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
    };

    public: std::vector<Vertex> vertices;
    public: std::vector<Edge> edges;

    /**
     * @brief 构造一个没有邻接矩阵的图对象
    */
    Graph(){
        this->generateMatrix = false;
    }

    /**
     * @brief 构造一个带邻接矩阵的图对象
     * @param matrixSize 邻接矩阵的边长
     * @attention 生成的邻接矩阵默认所有元素均为正无穷(INT_MAX)
    */
    Graph(int matrixSize){
        this->matrix = new std::vector<std::vector<long long>>(matrixSize, std::vector<long long>(matrixSize, LONG_LONG_MAX));
        this->generateMatrix = true;
    }

    bool HasMatrix(){
        return this->generateMatrix;
    }

    /**
     * @brief 向图中加入一条边
     * @param from 边的起始位置的序号（从0开始）
     * @param to 边的目标位置的序号（从0开始）
     * @param weight 边的权重
    */
    void AddEdge(int from, int to, long long weight){
        auto edge = Graph::Edge(from, to, weight);
        this->vertices[from].AddPath(edge);
        this->edges.push_back(edge);

        if(this->generateMatrix){
            (*this->matrix)[from][to] = std::min<long long>((*this->matrix)[from][to], weight);
        }
    }

    /**
     * @brief 向图中加入一条边
     * @param edge 边对象
    */
    void AddEdge(Graph::Edge edge){
        this->edges.push_back(edge);
        this->vertices[edge.GetFrom()].AddPath(edge);

        if(this->generateMatrix){
            (*this->matrix)[edge.GetFrom()][edge.GetDestinationIndex()] = std::min<double>(
                (*this->matrix)[edge.GetFrom()][edge.GetDestinationIndex()],
                edge.GetWeight()
            );
        }
    }

    /**
     * @brief 向图中加入一个顶点
     * @param vertex 加入的顶点对象
    */
    void AddVertex(const Vertex& vertex){
        this->vertices.push_back(vertex);
    }

    /**
     * @brief 重置图的寻路信息
    */
    void Reset(){
        for(int i = 0; i < this->vertices.size(); i++){
            this->vertices[i].SetDistance(LONG_LONG_MAX);
            this->vertices[i].SetParent(nullptr);
            this->vertices[i].SetVisited(false);
        }
    }

    /**
     * @brief 对寻路的图，给出从开始位置到目标位置的最短路径
     * @param destinationIndex 目标位置的序号（从0开始）
     * @param seperator 序号之间的分隔符，默认是"->"
    */
    void PrintPath(int destinationIndex, std::string seperator = "->"){
        auto destination = this->vertices[destinationIndex];
        if(!destination.IsReachable()){
            std::cout << "Unreachable" << std::endl;
            return;
        }
        if(destination.GetParent() != nullptr){
            PrintPathRecursive(destination.GetParent(), seperator);
        }
        std::cout << destination.GetIndex() << std::endl;
    }

    /**
     * @brief 对图进行迪杰斯特拉寻路
     * @param 寻路的起始位置的序号（从0开始）
     * @warning 不能处理带负权的图
    */
    void Dijkstra(int startIndex){
        std::priority_queue<Graph::Vertex*, std::vector<Graph::Vertex*>, Graph::Vertex::CompareGreater> heap;
        auto start = &this->vertices[startIndex];
        start->SetDistance(0);
        heap.push(start);
        while(heap.size() > 0){
            auto top = heap.top();
            heap.pop();
            if(top->IsVisited()){
                continue;
            }
            top->SetVisited(true);
            for(auto path : top->GetPaths()){
                auto destination = &this->vertices[path.GetDestinationIndex()];
                long long distanceThisWay = top->GetDistance() + path.GetWeight();
                if(distanceThisWay < destination->GetDistance()){
                    destination->SetDistance(distanceThisWay);
                    destination->SetParent(top);
                    heap.push(destination);
                }
            }
        }
    }

    /**
     * @brief 对图进行广度优先搜索寻路
     * @param 寻路的起始位置的序号（从0开始）
     * @warning 不能处理带权的图
    */
    void BFS(int startIndex){
        std::queue<Graph::Vertex*> verticesQueue;
        auto start = &this->vertices[startIndex];
        verticesQueue.push(start);
        start->SetDistance(0);

        while(verticesQueue.size() > 0){
            auto current = verticesQueue.front();
            verticesQueue.pop();
            current->SetVisited(true);

            for(auto path : current->GetPaths()){
                auto destination = &this->vertices[path.GetDestinationIndex()];
                if(destination->IsVisited()){
                    continue;
                }
                destination->SetDistance(current->GetDistance() + 1);
                destination->SetParent(current);
                verticesQueue.push(&this->vertices[path.GetDestinationIndex()]);
            }
        }
    }

    /**
     * @brief 对图进行深度优先搜索寻路
     * @param startIndex 寻路的起始位置的序号（从0开始）
     * @param depth 起始位置深度（默认为0，一般不要调整）
     * @warning DFS本身并不是一个求最短路径的方法，求得的路径只是一个可行路径，并不是一个最短路径
    */
    void DFS(int startIndex, int depth = 0){
        auto vertex = &this->vertices[startIndex];
        vertex->SetVisited(true);
        vertex->SetDistance(depth);
        for(auto path : vertex->GetPaths()){
            auto destination = &this->vertices[path.GetDestinationIndex()];
            if(destination->IsVisited()){
                continue;
            }
            destination->SetParent(&this->vertices[startIndex]);
            DFS(destination->GetIndex(), depth + 1);
        }
    }

    /**
     * @brief 对图进行贝尔曼福德寻路，这种寻路算法可以处理带负权边/带环路的图
     * @param startIndex 寻路的起始位置的序号（从0开始）
    */
    void BellmanFord(int startIndex){
        this->vertices[startIndex].SetDistance(0);
        for(int i = 0; i < this->vertices.size(); i++){
            for(auto path : this->edges){
                this->TryRelax(path);
            }
        }
    }

    /**
     * @brief 对图进行拓扑排序
     * @warning 此方法不会改变图本身，只会返回排序的结果
     * @return 排序的结果
    */
    std::vector<Vertex> DFSTopologicalSort(){
        std::vector<Vertex> result;
        std::vector<bool> visited(this->vertices.size(), false);

        for(int i = 0; i < this->vertices.size(); i++){
            if(!visited[i]){
                DFSTopologicalSortUtil(i, visited, result);
            }
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    /**
     * @brief 对图进行Floyd-Warshall寻路
     * @warning 对于没有生成邻接矩阵的图无效，返回的矩阵是堆上创建的实例，注意内存管理
     * @param distanceMatrix 对外返回的距离矩阵（d_ij矩阵）
     * @param pathMatrix 对外返回的路线矩阵（PI矩阵）
    */
    void FloydWarshall(std::vector<std::vector<long long>>*& distanceMatrix, std::vector<std::vector<int>>*& pathMatrix){
        if(!this->generateMatrix){
            throw NoMatrixException();
        }
        int n = this->matrix->size();
        auto matrix_k = new std::vector<std::vector<long long>>(this->vertices.size(), std::vector<long long>(this->vertices.size(), LONG_LONG_MAX));
        auto matrix_km1 = new std::vector<std::vector<long long>>(this->matrix->begin(), this->matrix->end());
        auto PI_k = new std::vector<std::vector<int>>(this->vertices.size(), std::vector<int>(this->vertices.size(), -1));
        auto PI_km1 = new std::vector<std::vector<int>>(this->vertices.size(), std::vector<int>(this->vertices.size(), -1));

        for(int i = 0; i < n; i++){
            (*matrix_km1)[i][i] = 0;
        }

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                (*PI_km1)[i][j] = ((*this->matrix)[i][j] == LONG_LONG_MAX || i == j) ? -1 : i;
            }
        }
        
        for(int k = 0; k < n; k++){
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if((*matrix_km1)[i][j] > SafeAdd((*matrix_km1)[i][k], (*matrix_km1)[k][j])){
                        (*matrix_k)[i][j] = SafeAdd((*matrix_km1)[i][k], (*matrix_km1)[k][j]);
                        (*PI_k)[i][j] = (*PI_km1)[k][j];
                    }else{
                        (*matrix_k)[i][j] = (*matrix_km1)[i][j];
                        (*PI_k)[i][j] = (*PI_km1)[i][j];
                    }
                }
            }

            if(k != n - 1){
                std::swap(matrix_k, matrix_km1);    
                std::swap(PI_k, PI_km1);
            }
        }

        delete matrix_km1;
        delete PI_km1;
        distanceMatrix = matrix_k;
        pathMatrix = PI_k;
    }

    /**
     * @class NoMatrixException
     * @brief 对没有生成邻接矩阵的图进行需要邻接矩阵操作时产生的异常
    */
    class NoMatrixException : public std::exception{
        public:
        const char* what() const noexcept override {
            return "Illegal operation to a graph without a matrix";
        }
    };
};


int main() {
    int vertexCount, edgeCount;
    std::cin >> vertexCount >> edgeCount;
    Graph graph(vertexCount);
    for(int i = 0; i < vertexCount; i++){
        graph.AddVertex(Graph::Vertex(i));
    }

    for(int i = 0; i < edgeCount; i++){
        int from, to;
        long long weight;
        std::cin >> from >> to >> weight;
        graph.AddEdge(Graph::Edge(from - 1, to - 1, weight));
    }
    std::vector<std::vector<long long>>* disMatrix;
    std::vector<std::vector<int>>* piMatrix;
    graph.FloydWarshall(disMatrix, piMatrix);
    int askCount;
    std::cin >> askCount;
    for(int i = 0; i < askCount; i++){
        int from, to;
        std::cin >> from >> to;
        auto res = (*disMatrix)[from - 1][to - 1];
        if(res == LONG_LONG_MAX){
            res = -1;
        }
        std::cout << res << '\n';
    }
    delete disMatrix;
    delete piMatrix;
}