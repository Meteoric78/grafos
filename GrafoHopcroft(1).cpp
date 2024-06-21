#include <bits/stdc++.h>

using namespace std;

void leituraGrafo(vector<vector<int>> &, int);
void escritaGrafo(const vector<vector<int>> &);
int hopcroftKarp(const vector<vector<int>> &G, int n);
bool bfs(const vector<vector<int>> &G, int n);
bool dfs(const vector<vector<int>> &G, int u);

const int NIL = 0;
const int INF = INT_MAX;

vector<int> parU, parV, dist;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> Grafo(n);
    leituraGrafo(Grafo, m);
    escritaGrafo(Grafo);

    int maxPares = hopcroftKarp(Grafo, n);

    cout << "Total Vértices: " << n << endl;
    cout << "Total Arestas: " << m << endl;
    cout << "Pares Maximos: " << maxPares << endl;

    return 0;
}

void leituraGrafo(vector<vector<int>> &G, int m)
{
    int a, b;
    while (m--)
    {
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
}

void escritaGrafo(const vector<vector<int>> &G)
{
    int n = G.size();
    cout << "Lista de Adjacência:" << endl;
    for (int u = 0; u < n; u++)
    {
        cout << u << ": ";
        for (auto v : G[u])
        {
            cout << v << " ";
        }
        cout << endl;
    }
}

bool bfs(const vector<vector<int>> &G, int n)
{
    queue<int> Q;
    for (int u = 0; u < n; ++u)
    {
        if (parU[u] == NIL)
        {
            dist[u] = 0;
            Q.push(u);
        }
        else
        {
            dist[u] = INF;
        }
    }
    dist[NIL] = INF;
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        if (dist[u] < dist[NIL])
        {
            for (int v : G[u])
            {
                if (dist[parV[v]] == INF)
                {
                    dist[parV[v]] = dist[u] + 1;
                    Q.push(parV[v]);
                }
            }
        }
    }
    return dist[NIL] != INF;
}

bool dfs(const vector<vector<int>> &G, int u)
{
    if (u != NIL)
    {
        for (int v : G[u])
        {
            if (dist[parV[v]] == dist[u] + 1)
            {
                if (dfs(G, parV[v]))
                {
                    parV[v] = u;
                    parU[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int hopcroftKarp(const vector<vector<int>> &G, int n)
{
    parU.assign(n, NIL);
    parV.assign(n, NIL);
    dist.assign(n, INF);

    int maxPares = 0;

    while (bfs(G, n))
    {
        for (int u = 0; u < n; ++u)
        {
            if (parU[u] == NIL && dfs(G, u))
                ++maxPares;
        }
    }

    return maxPares / 2;
}
