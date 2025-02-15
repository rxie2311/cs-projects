/*
 * Name: Raymond Xie
 * Student No: 251275727
 * Name: GraphEdge
 * Description: The GraphEdge class that handles everything relating to the edges that link nodes
 */

public class GraphEdge {

    // Instance variables
    // u represents first endpoint, v represents second endpoint (u,v)
    private GraphNode u, v;
    private int type;
    private String label;

    // Constructor method
    public GraphEdge(GraphNode u, GraphNode v, int type, String label) {
        // Sets two endpoints equal to u and v
        this.u = u;
        this.v = v;
        // Sets the type (the cost of the node)
        this.type = type;
        // Sets the label (if the node is either door or corridor)
        this.label = label;
    }

    // Getter methods
    // Returns the first endpoint of the node
    public GraphNode firstEndpoint() {
        return u;
    }

    // Returns the second endpoint of the node
    public GraphNode secondEndpoint() {
        return v;
    }

    // Returns the type of the node
    public int getType() {
        return type;
    }

    // Returns the label of the node
    public String getLabel() {
        return label;
    }

    // Setter methods
    // Sets the type of the node to the new type
    public void setType(int newType) {
        type = newType;
    }

    // Sets the label of the node to the new label
    public void setLabel(String newLabel) {
        label = newLabel;
    }
}
