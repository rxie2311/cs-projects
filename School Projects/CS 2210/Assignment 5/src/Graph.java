// Importing Java libraries for iterator method
import java.util.Iterator;
import java.util.ArrayList;

/*
 * Name: Raymond Xie
 * Student No: 251275727
 * Name: Graph
 * Description: The Graph class that handles everything relating to implementation of the graph
 */

public class Graph implements GraphADT {

    // Instance variables
    // Number of nodes inside the graph
    private int numNode;
    // Graph variable (The graph is an array that can store GraphNodes within it)
    private GraphNode[] graph;
    // Edge variable (The edge of the graph is a 2D array that can store Edges within (u,v))
    private GraphEdge[][] edges;

    // Constructor method
    public Graph(int n) {
        // Sets n as the number of nodes in the graph
        numNode = n;
        // Initializes the graph array to store n number of nodes inside
        graph = new GraphNode[n];
        // Initializes the edge 2D array to store nxn number of edges inside (adjacency matrix)
        edges = new GraphEdge[n][n];

        // Uses a for loop that ends at n-1 to store nodes with names from 0 to n-1 in the graph array
        for(int i=0; i<n; i++) {
            // Stores a new GraphNode for every loop
            graph[i] = new GraphNode(i);
        }
    }

    // Getter methods
    // Returns the node if it exists
    public GraphNode getNode(int name) throws GraphException {
        // If the name entered is smaller than 0 or greater than n-1
        if(name >= numNode || name < 0) {
            // Throws error b/c the node does not exist inside the graph
            throw new GraphException("Error: Node does not exist inside the graph.");
        }

        // If name entered is within the range of 0 - n-1 then returns the node at index name in graph array
        return graph[name];
    }

    // Returns the edge connecting nodes u and v if it exists
    public GraphEdge getEdge(GraphNode u, GraphNode v) throws GraphException {
        // If the names of either node inputted are smaller than 0 or greater than n-1 or
        // if there are no edges at (u,v) and (v,u) in the edge 2D array, then throws an error.
        if(u.getName() >= numNode || u.getName() < 0 || v.getName() >= numNode || v.getName() < 0 || edges[u.getName()][v.getName()] == null && edges[v.getName()][u.getName()] == null) {
            throw new GraphException("Error: Edge between two entered nodes does not exist.");
        }

        // If no exception was thrown, then returns the edge at (u,v) (and (v,u))
        return edges[u.getName()][v.getName()];
    }

    // Other methods
    // Inserts a new edge connecting points u and v, throws exception if node does not exist, or there is already an edge connecting the nodes
    public void insertEdge(GraphNode u, GraphNode v, int edgeType, String label) throws GraphException {
        // If the node names are not within the range of 0 - n-1, then it is impossible for them to be in the graph
        if(u.getName() >= numNode || u.getName() < 0 || v.getName() >= numNode || v.getName() < 0) {
            // Throws error b/c the node does not exist inside the graph
            throw new GraphException("Error: Node(s) are not in the graph, therefore a connecting edge cannot be inserted.");
        }

        // If no exception was thrown, adds the edge connecting nodes u and v to the edge 2D array
        // Connects (u,v) with an edge
        edges[u.getName()][v.getName()] = new GraphEdge(u, v, edgeType, label);
        // Connects (v,u) with an edge
        edges[v.getName()][u.getName()] = new GraphEdge(u, v, edgeType, label);
    }

    // Creates an iterator of all edges that have node u as one of the endpoints (iterator of all edges incident to u)
    public Iterator incidentEdges(GraphNode u) throws GraphException {
        // If node u is not within the range of 0 - n-1, then it is not in the graph
        if(u.getName() >= numNode || u.getName() < 0) {
            // Throws error b/c the node does not exist inside the graph
            throw new GraphException("Error: Node is not in the graph, therefore all incident edges could not be listed.");
        }

        // Creates a new ArrayList collection to store all incident edges
        ArrayList<GraphEdge> incident = new ArrayList<>();
        // For loop to loop through the row of node u and check all indexes in (u,i) for edges
        for(int i=0; i<edges[u.getName()].length; i++) {
            // If an edge is found, adds it to the ArrayList
            if(edges[u.getName()][i] != null) {
                incident.add(edges[u.getName()][i]);
            }
        }

        // Returns the converted ArrayList
        return incident.iterator();
    }

    // Checks if two nodes u and v have an edge connecting them (if u and v are adjacent)
    public boolean areAdjacent(GraphNode u, GraphNode v) throws GraphException {
        // If the node names are not within the range of 0 - n-1, then it is impossible for them to be in the graph
        if(u.getName() >= numNode || u.getName() < 0 || v.getName() >= numNode || v.getName() < 0) {
            throw new GraphException("Error: Node(s) are not in the graph, therefore the connecting edge does not exist.");

        // If the position (u,v) in the 2D edges array is not null (empty) then it means there is an edge there and u and v are adjacent (connected)
        } else if(edges[u.getName()][v.getName()] != null) {
            // Returns true
            return true;
        }

        // If no exception was thrown or true was not returned, then return false (u and v are not adjacent)
        return false;
    }
}
