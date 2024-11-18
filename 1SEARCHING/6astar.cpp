#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

struct Node {
    char id;
    int g;
    int h;
    Node* parent;
    Node(char id, int g, int h, Node* parent = nullptr) : id(id), g(g), h(h), parent(parent) {}
};

struct CompareNodes {
    bool operator()(const Node* a, const Node* b) {
        return a->g + a->h > b->g + b->h;
    }
};

vector<char> aStar(const unordered_map<char, vector<pair<char, int>>>& graph, const unordered_map<char, int>& h_values, char start, char goal) {
    priority_queue<Node*, vector<Node*>, CompareNodes> openSet;
    unordered_map<char, Node*> closedSet;
    Node* startNode = new Node(start, 0, h_values.at(start));
    openSet.push(startNode);
    while (!openSet.empty()) {
        Node* currentNode = openSet.top();
        openSet.pop();
        closedSet[currentNode->id] = currentNode;
        if (currentNode->id == goal) {
            vector<char> path;
            while (currentNode != nullptr) {
                path.push_back(currentNode->id);
                currentNode = currentNode->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }
        for (const auto& edge : graph.at(currentNode->id)) {
            char neighborId = edge.first;
            int edgeCost = edge.second;
            Node* neighbor = new Node(neighborId, currentNode->g + edgeCost, h_values.at(neighborId), currentNode);
            if (closedSet.find(neighbor->id) == closedSet.end()) {
                openSet.push(neighbor);
            }
        }
    }
    return vector<char>();
}

void printPath(const vector<char>& path) {
    for (char node : path) {
        cout << node << " ";
    }
    cout << endl;
}

void bfs(const unordered_map<char, vector<pair<char, int>>>& graph, vector<char>& ans, char start) {
    unordered_map<char, bool> visited;
    queue<char> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        char currentNode = q.front();
        q.pop();
        ans.push_back(currentNode);
        for (const auto& edge : graph.at(currentNode)) {
            char neighbor = edge.first;
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

void dfs(const unordered_map<char, vector<pair<char, int>>>& graph, vector<char>& ans, char start) {
    unordered_map<char, bool> visited;
    stack<char> s;
    s.push(start);
    while (!s.empty()) {
        char currentNode = s.top();
        s.pop();
        if (!visited[currentNode]) {
            visited[currentNode] = true;
            ans.push_back(currentNode);
            for (const auto& edge : graph.at(currentNode)) {
                char neighbor = edge.first;
                if (!visited[neighbor]) {
                    s.push(neighbor);
                }
            }
        }
    }
}

void beamSearch(const unordered_map<char, vector<pair<char, int>>>& graph, vector<char>& ans, char start, int beamWidth) {
    unordered_map<char, bool> visited;
    queue<char> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int count = 0;
        vector<pair<char, int>> levelNodes;
        while (!q.empty()) {
            char currentNode = q.front();
            q.pop();
            levelNodes.push_back({currentNode, 0});
            for (const auto& edge : graph.at(currentNode)) {
                char neighbor = edge.first;
                if (!visited[neighbor]) {
                    levelNodes.push_back({neighbor, edge.second});
                }
            }
        }
        sort(levelNodes.begin(), levelNodes.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
            return a.second < b.second;
        });
        for (const auto& node : levelNodes) {
            if (count < beamWidth) {
                q.push(node.first);
                visited[node.first] = true;
                count++;
            } else {
                break;
            }
        }
    }
    while (!q.empty()) {
        ans.push_back(q.front());
        q.pop();
    }
}

void ids(const unordered_map<char, vector<pair<char, int>>>& graph, char start, int maxDepth) {
    for (int depth = 0; depth <= maxDepth; ++depth) {
        unordered_map<char, bool> visited;
        stack<pair<char, int>> s;
        s.push({start, 0});
        vector<char> ans;
        while (!s.empty()) {
            auto [currentNode, currentDepth] = s.top();
            s.pop();
            if (currentDepth > depth) continue;
            if (!visited[currentNode]) {
                visited[currentNode] = true;
                ans.push_back(currentNode);
                for (const auto& edge : graph.at(currentNode)) {
                    char neighbor = edge.first;
                    if (!visited[neighbor]) {
                        s.push({neighbor, currentDepth + 1});
                    }
                }
            }
        }
        cout << "Depth " << depth << ": ";
        printPath(ans);
    }
}

int main() {
    int choice;
    cout << "Select Search Algorithm: \n";
    cout << "1. A* Search\n";
    cout << "2. Best First Search\n";
    cout << "3. Beam Search\n";
    cout << "4. Iterative Deepening Search\n";
    cout << "5. Breadth-First Search\n";
    cout << "6. Depth-First Search\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    unordered_map<char, vector<pair<char, int>>> graph = {
        {'A', {{'B', 6}, {'C', 3}, {'D', 1}}},
        {'B', {{'A', 6}, {'C', 2}, {'E', 3}, {'F', 4}}},
        {'C', {{'A', 3}, {'B', 2}, {'E', 4}, {'F', 5}}},
        {'D', {{'A', 1}, {'E', 7}, {'F', 8}, {'G', 9}}},
        {'E', {{'B', 3}, {'C', 4}, {'D', 7}, {'F', 6}, {'G', 9}, {'H', 9}}},
        {'F', {{'B', 4}, {'C', 5}, {'D', 8}, {'E', 6}, {'G', 8}, {'H', 9}}},
        {'G', {{'D', 9}, {'E', 9}, {'F', 8}, {'H', 11}, {'I', 12}, {'J', 14}}},
        {'H', {{'E', 9}, {'F', 9}, {'G', 11}, {'I', 14}, {'J', 15}}},
        {'I', {{'G', 12}, {'H', 14}}},
        {'J', {{'G', 14}, {'H', 15}}}
    };

    unordered_map<char, int> h_values = {
        {'A', 15}, {'B', 13}, {'C', 13}, {'D', 12}, {'E', 10},
        {'F', 9}, {'G', 7}, {'H', 6}, {'I', 5}, {'J', 0}
    };

    while (choice != 7) {
        switch (choice) {
            case 1: {
                char start, goal;
                cout << "Enter start node: ";
                cin >> start;
                cout << "Enter goal node: ";
                cin >> goal;
                vector<char> path = aStar(graph, h_values, start, goal);
                printPath(path);
                break;
            }
            case 2: {
                vector<char> ans;
                bfs(graph, ans, 'A');
                cout << "Best First Search Result: ";
                printPath(ans);
                break;
            }
            case 3: {
                vector<char> ans;
                int beamWidth = 2;
                beamSearch(graph, ans, 'A', beamWidth);
                cout << "Beam Search Result: ";
                printPath(ans);
                break;
            }
            case 4: {
                int maxDepth;
                cout << "Enter maximum depth: ";
                cin >> maxDepth;
                cout << "Iterative Deepening Search Result:\n";
                ids(graph, 'A', maxDepth);
                break;
            }
            case 5: {
                vector<char> ans;
                bfs(graph, ans, 'A');
                cout << "Breadth-First Search Result: ";
                printPath(ans);
                break;
            }
            case 6: {
                vector<char> ans;
                dfs(graph, ans, 'A');
                cout << "Depth-First Search Result: ";
                printPath(ans);
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
        cout << "Select Search Algorithm: \n";
        cout << "1. A* Search\n";
        cout << "2. Best First Search\n";
        cout << "3. Beam Search\n";
        cout << "4. Iterative Deepening Search\n";
        cout << "5. Breadth-First Search\n";
        cout << "6. Depth-First Search\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
    }

    return 0;
}
