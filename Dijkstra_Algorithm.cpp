#include <bits/stdc++.h>
using namespace std;

class Graph
{
private:
    class Node
    {
    public:
        int id;
        vector<pair<Node *, int>> neighbors;
        int distance;

        Node(int _id) : id(_id), distance(INT_MAX) {}

        void addNeighbor(Node *neighbor, int weight)
        {
            neighbors.emplace_back(neighbor, weight);
        }
    };

    vector<Node *> nodes;

public:
    void addNode(int id)
    {
        nodes.push_back(new Node(id));
    }

    void addEdge(int from, int to, int weight)
    {
        Node *fromNode = getNodeById(from);
        Node *toNode = getNodeById(to);

        if (fromNode && toNode)
            fromNode->addNeighbor(toNode, weight);
    }

    void dijkstra(int startId)
    {
        Node *startNode = getNodeById(startId);

        if (!startNode)
        {
            cout << "Node not found in the graph." << endl;
            return;
        }

        priority_queue<pair<int, Node *>, vector<pair<int, Node *>>, greater<>> pq;

        startNode->distance = 0;
        pq.push({0, startNode});

        while (!pq.empty())
        {
            Node *current = pq.top().second;
            pq.pop();

            for (const auto &neighbor : current->neighbors)
            {
                int newDistance = current->distance + neighbor.second;

                if (newDistance < neighbor.first->distance)
                {
                    neighbor.first->distance = newDistance;
                    pq.push({newDistance, neighbor.first});
                }
            }
        }
    }
    void printShortestDistances(int startId)
    {
        cout << "Shortest distances from Node " << startId << ":" << endl;
        for (const auto &node : nodes)
        {
            cout << "To Node " << node->id << ": " << (node->distance == INT_MAX ? "INF" : to_string(node->distance)) << endl;
        }
    }

private:
    Node *getNodeById(int id)
    {
        for (const auto &node : nodes)
        {
            if (node->id == id)
            {
                return node;
            }
        }
        return nullptr;
    }
};

int main()
{
    Graph graph;

    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    graph.addNode(4);
    graph.addNode(5);

    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 4);
    graph.addEdge(2, 3, 2);
    graph.addEdge(2, 4, 5);
    graph.addEdge(3, 4, 1);
    graph.addEdge(4, 5, 3);
    graph.dijkstra(1);
    graph.printShortestDistances(1);

    return 0;
}
