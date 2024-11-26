#include <iostream>
#include <sstream>
using namespace std;
class Graph
{
private:
    int n;
    int **adj;

public:
    Graph(int _n)
    {
        n = _n;
        adj = new int *[n];
        for (int i = 0; i < n; i++)
        {
            adj[i] = new int[n];
            for (int j = 0; j < n; j++)
                adj[i][j] = 0;
        }
    }

    void readGraph()
    {
        string line;
        for (int i = 0; i < n; i++)
        {
            getline(cin, line);
            istringstream stream(line);
            int row;
            int v;
            stream >> row;
            while (stream >> v)
                adj[row - 1][v - 1] = 1;
        }
    }
    int biggestIn()
    {
        int biggest = 0;
        for (int j = 0; j < n; j++)
        {
            int count = 0;
            for (int i = 0; i < n; i++)
                count += adj[i][j];
            if (count > biggest)
                biggest = count;
        }
        return biggest;
    }

    bool loop3()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (adj[i][j])
                {
                    int x = adj[i][j];
                    for (int k = 0; k < n; k++)
                    {
                        if (adj[j][k])
                        {
                            int y = adj[j][k];
                            if (adj[k][i])
                                return 1;
                        }
                    }
                }
            }
        }

        return 0;
    }
};

int main()
{
    int n;
    cin >> n;
    getchar();
    Graph g(n);
    g.readGraph();
    cout << g.biggestIn() << endl;
    cout << g.loop3();
}