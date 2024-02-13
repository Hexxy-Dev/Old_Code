/*
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    int to;
    int weight;
    Edge(int _to, int _weight) : to(_to), weight(_weight) {}
};
class Graph {
public:
    int Nodes;
    vector<vector<Edge>> adj;
    Graph(int Nodes) : Nodes(Nodes), adj(Nodes) {}
    void add_edge(int from, int to, int cost) {
        adj[from].push_back(Edge(to, cost));
        adj[to].push_back(Edge(from, cost));
    }
};//*/



/*
#include <iostream>
#include <vector>
#include <queue>
#include <thread>

using namespace std;

const int INF = 1e9;

typedef pair<int, int> pii;

// Graph class to represent the non-directed graph
class Graph {
public:
    int V;
    vector<vector<pii>> adj;
    Graph(int V);
    void addEdge(int u, int v, int w);
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

// Bidirectional Dijkstra's algorithm
void bidirectionalDijkstra(Graph g, int s, int t, vector<int>& dist, vector<int>& dist_rev) {
    priority_queue<pii, vector<pii>, greater<pii>> pq, pq_rev;
    dist.assign(g.V, INF);
    dist_rev.assign(g.V, INF);
    dist[s] = 0;
    dist_rev[t] = 0;
    pq.push(make_pair(0, s));
    pq_rev.push(make_pair(0, t));

    while (!pq.empty() || !pq_rev.empty()) {
        if (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto neighbor : g.adj[u]) {
                int v = neighbor.first;
                int w = neighbor.second;

                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        if (!pq_rev.empty()) {
            int u = pq_rev.top().second;
            pq_rev.pop();

            for (auto neighbor : g.adj[u]) {
                int v = neighbor.first;
                int w = neighbor.second;

                if (dist_rev[v] > dist_rev[u] + w) {
                    dist_rev[v] = dist_rev[u] + w;
                    pq_rev.push(make_pair(dist_rev[v], v));
                }
            }
        }

        // Check if the two searches have met
        for (int i = 0; i < g.V; i++) {
            if (dist[i] + dist_rev[i] < dist[s] + dist_rev[s]) {
                dist[s] = dist[i];
                dist_rev[t] = dist_rev[i];
                break;
            }
        }
    }
}

int main() {
    int V, E, s, t;
    cin >> V >> E >> s >> t;
    Graph g(V);

    // Reading edges
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    vector<int> dist, dist_rev;
    //thread t1(bidirectionalDijkstra, g, s, t, ref(dist), ref(dist_rev));
    //thread t2(bidirectionalDijkstra, g, t, s, ref(dist_rev), ref(dist));
    //t1.join();
    //t2.join();
    bidirectionalDijkstra(g, s, t, dist, dist_rev);

    // Print the shortest path distance
    int shortestPath = dist[t];
    if (shortestPath == INF) {
        cout << "No path exists\n";
    }
    else {
        cout << shortestPath << "\n";
    }

    return 0;
}//*/



#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

const int INF = 1e9;

typedef pair<int, int> pii;
typedef pair<int, pii> ppi;

vector<vector<pii>> graph; // adjacency list representation of the graph
vector<int> dist_fw, dist_bw; // distances from the start and end nodes
priority_queue<pii, vector<pii>, greater<pii>> pq_fw, pq_bw; // min-heap for forward and backward search
mutex mtx_fw, mtx_bw; // mutexes for accessing priority queues and distances
condition_variable cv_fw, cv_bw; // condition variables for signaling the threads
bool done = false; // flag for stopping the threads

void Dijkstra(int source, priority_queue<pii, vector<pii>, greater<pii>>& pq, vector<int>& dist, mutex& mtx, condition_variable& cv) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&] { return done || !pq.empty(); }); // wait until a new node is added or done flag is set
        if (done) break;
        int u = pq.top().second;
        pq.pop();
        for (auto& e : graph[u]) {
            int v = e.first;
            int w = e.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
        lock.unlock();
        cv.notify_one(); // signal the other thread that a new node is added
    }
}

int BidirectionalDijkstra(int start, int end) {
    int n = graph.size();
    dist_fw.assign(n, INF);
    dist_bw.assign(n, INF);
    dist_fw[start] = 0;
    dist_bw[end] = 0;
    pq_fw.emplace(0, start);
    pq_bw.emplace(0, end);
    thread t1(Dijkstra, start, ref(pq_fw), ref(dist_fw), ref(mtx_fw), ref(cv_fw));
    thread t2(Dijkstra, end, ref(pq_bw), ref(dist_bw), ref(mtx_bw), ref(cv_bw));
    while (true) {
        // check if the two searches meet
        int meeting_point = -1;
        for (int u = 0; u < n; u++) {
            if (dist_fw[u] + dist_bw[u] < dist_fw[meeting_point] + dist_bw[meeting_point]) {
                meeting_point = u;
            }
        }
        if (meeting_point != -1) {
            t1.join();
            t2.join();
            return dist_fw[meeting_point] + dist_bw[meeting_point];
        }
        // add a new node to the search
        if (!pq_fw.empty() && !pq_bw.empty()) {
            if (pq_fw.top().first + dist_fw[pq_fw.top().second] < pq_bw.top().first + dist_bw[pq_bw.top().second]) {
                if (dist_fw[pq_fw.top().second] + dist_bw[pq_fw.top().second] < dist_fw[meeting_point] + dist_bw[meeting_point]) {
                    pq_fw.pop();
                    cv_bw.notify_one();
                }
                else {
                    done = true;
                    break;
                }
            }
            else {
                if (dist_bw[pq_bw.top().second] + dist_fw[pq_bw.top().second] < dist_fw[meeting_point] + dist_bw[meeting_point]) {
                    pq_bw.pop();
                    cv_fw.notify_one();
                }
                else {
                    done = true;
                    break;
                }
            }
        }
        else {
            done = true;
            break;
        }
    }
    t1.join();
    t2.join();
    return -1; // no path found
}

int main() {
    int n, m;
    cin >> n >> m;
    graph.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }
    int start, end;
    cin >> start >> end;
    int dist = BidirectionalDijkstra(start, end);
    if (dist == -1) {
        cout << "No path found" << endl;
    }
    else {
        cout << "Shortest path distance: " << dist << endl;
    }
    return 0;
}