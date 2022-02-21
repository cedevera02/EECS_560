#ifndef MY_GRAPH
#define MY_GRAPH

#include <vector>
#include <list>
#include <string>
#include <iostream>


class NodeType
{
    public:
    NodeType() : city(""), ID(-1) {}
    NodeType(std::string cityName) : city(cityName), ID(-1) {}
    bool operator== (NodeType rhs){
        if (this->city == rhs.city){
            return true;
        }else{
            return false;
        }
    }
    std::string city;
    int ID;
};

class EdgeType
{
    public:
    EdgeType() : distance(-1), visited(false) {}
    EdgeType(int distance) : distance(distance), visited(false) {}

    int distance;
    bool visited;
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
            std::pair<EdgeType, NodeType> p2(f, node_map[id1]);
            m_graph[id1].push_back(p1);
            m_graph[id2].push_back(p2);
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
            for(int i = 0; i < m_graph[id2].size(); i++){
                if(m_graph[id2][i].second == node_map[id1]){
                    return true;
                }
            }
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
        for(int i = 0; i < m_graph[id2].size(); i++){
            if(m_graph[id2][i].second == node_map[id1]){
                return m_graph[id2][i].first;
            }
        }
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
            for(int i = 0; i < m_graph[id2].size(); i++){
                if(m_graph[id2][i].second == node_map[id1]){
                    m_graph[id2].erase(m_graph[id2].begin()+i);
                    return true;
                }
            }
        }
        return false;
    }

    private:
    std::vector< std::vector <std::pair<EdgeType, NodeType > > > m_graph;
    std::vector<NodeType> node_map;
};

#endif