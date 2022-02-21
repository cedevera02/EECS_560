#ifndef MY_GRAPH
#define MY_GRAPH

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <limits.h>
#include <bits/stdc++.h> 
#include <algorithm>  

using namespace std;

class NodeType
{
    public:
    NodeType() : city(""), ID(-1), visited(false), touched(false) {}
    NodeType(std::string cityName) : city(cityName), ID(-1), visited(false), touched(false) {}
    bool operator== (NodeType rhs){
        if (this->city == rhs.city){
            return true;
        }else{
            return false;
        }
    }
    std::string city;
    int ID;
    bool visited;
    bool touched;
};

class EdgeType
{
    public:
    EdgeType() : distance(-1), valid(false) {}
    EdgeType(int distance) : distance(distance), valid(false) {}

    int distance;
    bool valid;
    //int ID;
};

class myGraph
{
    public:
    myGraph()
    {
        //std::cout << m_graph.size();
        //std::cout << node_map.size();
        NodeType n;
        EdgeType e;
        node_map.push_back(n);
        std::vector<std::pair <EdgeType, NodeType> > v;
        m_graph.push_back(v);
        // std::vector< std::vector <NodeType> > m;
        // node_paths.push_back(m);
    }
    myGraph( const myGraph & rhs ) : m_graph(rhs.m_graph)
    {
        //m_graph = clone( rhs.m_graph );
    }
    myGraph( myGraph && rhs ): m_graph( rhs.m_graph)
    { }

    ~myGraph( )
    {
        m_graph.clear();
        node_map.clear();
        //makeEmpty();
    }


    myGraph & operator=( const myGraph & rhs )
    {
        myGraph copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    myGraph & operator=( myGraph && rhs )
    {
        std::swap(m_graph, rhs.m_graph);

        return *this;
    }


    int addNode(const NodeType & n)
    {
        NodeType m(n.city);
        m.ID = node_map.size();
        node_map.push_back(m);
        std::vector < std::pair<EdgeType, NodeType> > li;
        m_graph.push_back(li);

        return m.ID;
    }
    NodeType  getNode (const int id)
    {
        return node_map[id];
    }
    bool addEdge(const EdgeType & e, const int id1, const int id2)
    {
        if (id1 > node_map.size() || id2 > node_map.size()){
            return false;
        }
        else{
            EdgeType f(e.distance);
            std::pair<EdgeType, NodeType> p1(f, node_map[id2]);
            //std::pair<EdgeType, NodeType> p2(f, node_map[id1]);
            m_graph[id1].push_back(p1);
            //m_graph[id2].push_back(p2);
            return true;
        }
    }
    bool isConnected(const int id1, const int id2)
    {
        if (id1 > node_map.size() || id2 > node_map.size()){
            return false;
        }else{
            for(int i = 0; i < m_graph[id1].size(); i++){
                if(m_graph[id1][i].second == node_map[id2]){
                    return true;
                }
            }
            // for(int i = 0; i < m_graph[id2].size(); i++){
            //     if(m_graph[id2][i].second == node_map[id1]){
            //         return true;
            //     }
            // }
        }
        return false;
    }
    EdgeType getEdge(const int id1, const int id2)
    {
        for(int i = 0; i < m_graph[id1].size(); i++){
            if(m_graph[id1][i].second == node_map[id2]){
                return m_graph[id1][i].first;
            }
        }
        // for(int i = 0; i < m_graph[id2].size(); i++){
        //     if(m_graph[id2][i].second == node_map[id1]){
        //         return m_graph[id2][i].first;
        //     }
        // }
    }
    int getDegree(const int id)
    {
        return m_graph[id].size();
    }
    bool deleteNode(const int id)
    {
        if(id > node_map.size()){
            return false;
        }else{
            m_graph[id].clear();
            NodeType m("");
            node_map[id] = m;
            return true;
        }
    }
    bool deleteEdge(const int id1, const int id2)
    {
        if (id1 > node_map.size() || id2 > node_map.size()){
            return false;
        }else{
            for(int i = 0; i < m_graph[id1].size(); i++){
                if(m_graph[id1][i].second == node_map[id2]){
                    m_graph[id1].erase(m_graph[id1].begin()+i);
                    return true;
                }
            }
            // for(int i = 0; i < m_graph[id2].size(); i++){
            //     if(m_graph[id2][i].second == node_map[id1]){
            //         m_graph[id2].erase(m_graph[id2].begin()+i);
            //         return true;
            //     }
            // }
        }
        return false;
    }

    void BFS(const int id, std::vector<std::string> & path)
    {
        for (int i = 1; i < node_map.size(); i++){
            node_map[i].visited = false;
            node_map[i].touched = false;
        }

        std::list<int> queue;
        int j = id;
        node_map[j].visited = true;
        queue.push_back(id);
    
        while(!queue.empty())
        {
            j = queue.front();
            path.push_back(node_map[j].city);
            queue.pop_front();
            std::vector<int> line;
            for (int i = 0; i < m_graph[j].size(); i++)
            {
                if (!node_map[m_graph[j][i].second.ID].visited)
                {
                    node_map[m_graph[j][i].second.ID].visited = true;
                    line.push_back(m_graph[j][i].second.ID);
                }
            }
            while(!line.empty()){
                int least = line[0];
                for(int i =0; i < line.size(); i++){
                    if (line[i] < least){
                        least = line[i];
                    }
                }
                queue.push_back(least);
                line.erase(std::remove(line.begin(), line.end(), least), line.end());
            }
        }
    }

    void DFS(const int id, std::vector<std::string> & path)
    {
        for (int i = 1; i < node_map.size(); i++){
            node_map[i].visited = false;
            node_map[i].touched = false;
        }

        std::list<int> queue;
        int j = id;
        //node_map[j].visited = true;
        queue.push_back(j);
    
        while(!queue.empty())
        {
            j = queue.front();
            queue.pop_front();
            std::vector<int> line;
            if(!node_map[j].visited){
                path.push_back(node_map[j].city);
                node_map[j].visited = true;
            }

            for (int i = m_graph[j].size()-1; i >= 0; i--)
            {
                if (!node_map[m_graph[j][i].second.ID].visited)
                {
                    line.push_back(m_graph[j][i].second.ID);
                }
            }

            while(!line.empty()){
                int most = line[0];
                for(int i =0; i < line.size(); i++){
                    if (line[i] > most){
                        most = line[i];
                    }
                }
                queue.push_front(most);
                line.erase(std::remove(line.begin(), line.end(), most), line.end());
            }
        }
    }

    int shortestPath(const int id1, const int id2, std::vector<std::string> & path)
    {
        for (int i = 1; i < node_map.size(); i++){
            node_map[i].visited = false;
            node_map[i].touched = false;
        }
        int dist[node_map.size()]; // The output array.  dist[i] will hold the shortest
        // distance from src to i

        for (int i = 0; i < node_map.size(); i++){
            dist[i] = INT_MAX;
        }

        //node_map[id1].visited = true;
        dist[id1] = 0;
        std::vector<NodeType> m;
        //m.push_back(node_map[id1]);
        for (int i = 0; i < node_map.size(); i++){
            node_paths.push_back(m);
        }
        node_paths[id1].push_back(node_map[id1]);
        // for (int i = 0; i < node_paths.size(); i++)
        // {
        //     std::cout << node_paths[i][0].city << " ";
        // }
        //std::cout << std::endl;
        for (int i = 1; i < node_map.size(); i++){
            int min = minDist(dist);
            //std::cout << "Min is: " << node_map[min].city << std::endl;
            node_map[min].visited = true;

            for (int j = 0; j < m_graph[min].size(); j++){
                if(!node_map[m_graph[min][j].second.ID].visited && dist[min] != INT_MAX && dist[min] + 
                    m_graph[min][j].first.distance < dist[m_graph[min][j].second.ID]){
                        node_paths[m_graph[min][j].second.ID] = node_paths[min];
                        //node_paths[m_graph[min][j].second.ID].push_back(node_map[min]);
                        node_paths[m_graph[min][j].second.ID].push_back(node_map[m_graph[min][j].second.ID]);

                        // for(int num = 1; num < node_paths[min].size(); num++){
                        //     node_paths[m_graph[min][j].second.ID].push_back(node_paths[min][i]);
                        // }
                        dist[m_graph[min][j].second.ID] = dist[min] + m_graph[min][j].first.distance;
                    //std::cout << "New dist at Node[" << m_graph[min][j].second.ID << "] is " <<  dist[m_graph[min][j].second.ID] << std::endl;
                    }
            }
        }

        for (int i = 0; i < node_paths[id2].size(); i++)
        {
            path.push_back(node_paths[id2][i].city);
        }
        return dist[id2];
    }

    void assembleFragments(std::vector<std::string> & fragments, std::string &assembly)
    {
        std::vector<std::string> copy = fragments;
        int n = copy.size();
        while (n != 1)
        {
            int min = INT_MAX, minStart, max = INT_MIN, l, k;
            std::string olstr;
            // for (int i = 0; i < fragments.size(); i++){
            //     NodeType n(fragments[i]);
            //     this->addNode(n);
            // }

            // for (int i = 1; i < node_map.size(); i++){
            //     for(int j = 1; j < node_map.size(); j++){
            //         if (i!=j){
            //             int len;
            //             std::string word;
            //             len = overLap(node_map[i].city, node_map[j].city, word);
            //             if (len != INT_MIN){
            //                 EdgeType e(len);
            //                 this->addEdge(e, i, j);
            //             }
            //         }
            //     }
            // }
    
            for (int i = 0; i < n; i++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    string str;
                    int s = overLap(copy[i], copy[j], str);
                    if (max < s)
                    {
                        max = s;
                        //std::cout<< copy[i] + " " + copy[j] <<< std::endl;
                        olstr.assign(str);
                        l = i, k = j;
                    }
                }
            }
            n--;
            if (max == INT_MIN) {
                //std::cout<< copy[0] + " " + copy[n] <<< std::endl;
                copy[0] += copy[n];
            }
            else {
                //std::cout<< copy[k] + " " + copy[l] <<< std::endl;
                copy[k] = copy[n];
                copy[l] = olstr;
            }
        }
        assembly = copy[0];
        return;
    }

    private:
    std::vector< std::vector <std::pair<EdgeType, NodeType > > > m_graph;
    std::vector<NodeType> node_map;
    std::vector< std::vector <NodeType> > node_paths;

    int minDist(int distance[]){
        int ret, min=INT_MAX;
        for (int i = 1; i < node_map.size(); i++){
            //std::cout << "\t\tCurrent dist: " << distance[i] << std::endl; 
            if(!node_map[i].visited && distance[i] <= min){
                min = distance[i];
                ret = i;
            }
        }
        return ret;
    }

    bool allVisited(){
        for (int i =1; i <= node_map.size(); i++){
            if (!node_map[i].visited)
                return false;
        }
        return true;
    }

    int overLap(std::string frag1, std::string frag2, std::string & conc)
    {
        int max = INT_MIN;
        int m = frag1.length();
        int n = frag2.length();
        for (int i = 1; i <= min(m, n); i++)
        {
            if (frag1.compare(m - i, i, frag2, 0, i) == 0)
            {
                if (max < i)
                {
                    max = i;
                    conc = frag1 + frag2.substr(i);
                }
            }
        }
        for (int i = 1; i <= min(m, n); i++)
        {
            if (frag1.compare(0, i, frag2, n - i, i) == 0)
            {
                if (max < i)
                {
                    max = i;
                    conc = frag2 + frag1.substr(i);
                }
            }
        }
    
        return max;
    }
    
};

#endif