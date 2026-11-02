 #include <set> 


struct Graph {
    struct Vertex {
        int id;
        int weight;
        std::set<Vertex> neighbors;

        Vertex(int id, int weight) : id(id), weight(weight) {}

        bool operator==(const Vertex& other) const {
            return id == other.id;
        }
    };

    struct Edge {
        Vertex* v1;
        Vertex* v2;
        int weight = v1->weight > v2->weight ? v1->weight - v2->weight : v2->weight - v1->weight;

        Edge(Vertex* v1, Vertex* v2) : v1(v1), v2(v2) {}

        bool operator==(const Edge& other) const {
            return (v1 == other.v1 && v2 == other.v2) ||
                (v1 == other.v2 && v2 == other.v1);
        }
    };

    std::set<Edge> edges;
    std::set<Vertex> vertices;
};