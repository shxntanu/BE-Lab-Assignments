#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

class Graph {
  int num_vertices;
  vector<vector<int>> adjMatrix;

public:
  Graph(int vertices) {
    this->num_vertices = vertices;
    this->adjMatrix.resize(num_vertices);
  }

  void add_edge(int u, int v) {
    adjMatrix[u].push_back(v);
    adjMatrix[v].push_back(u);
  }

  void parallel_bfs(int startVertex) {
    cout << "Parallel BFS of Graph from vertex " << startVertex
         << "is: " << endl;

    vector<bool> visited(num_vertices, false);
    queue<int> q;

#pragma omp critical
    {
      q.push(startVertex);
      visited[startVertex] = true;
    }

#pragma omp parallel
    {
      while (!q.empty()) {
        int node = -1;

#pragma omp critical
        {
          if (!q.empty()) {
            node = q.front();
            q.pop();
            cout << node;
          }
        }

        if (node == -1)
          break;

        vector<int> neighbours;
#pragma omp critical
        {
          neighbours = adjMatrix[node];
        }

        for (int n : neighbours) {
#pragma omp critical
          {
            if (!visited[n]) {
              visited[n] = true;
              q.push(n);
            }
          }
        }

        cout << endl;
      }
    }
  }

  void parallel_dfs(int startVertex) {
    cout << "Parallel BFS of Graph from vertex " << startVertex
         << "is: " << endl;

    vector<bool> visited(num_vertices, false);
    stack<int> s;

#pragma omp critical
    {
      s.push(startVertex);
      visited[startVertex] = true;
    }

#pragma omp parallel
    {
      while (!s.empty()) {
        int node = -1;

#pragma omp critical
        {
          if (!s.empty()) {
            node = s.top();
            s.pop();
            cout << node;
          }
        }

        if (node == -1)
          break;

        vector<int> neighbours;
#pragma omp critical
        {
          neighbours = adjMatrix[node];
        }

        for (int n : neighbours) {
#pragma omp critical
          {
            if (!visited[n]) {
              visited[n] = true;
              s.push(n);
            }
          }
        }

        cout << endl;
      }
    }
  }
};

int main() {
  Graph g = Graph(6);

  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(1, 3);
  g.add_edge(1, 4);
  g.add_edge(2, 4);
  g.add_edge(3, 5);
  g.add_edge(4, 5);

  g.parallel_bfs(0);
  g.parallel_dfs(0);

  return 0;
}

// Compile with: g++ -fopenmp -o graph parallel_bfs_graph.cpp
// Run with: ./graph