/*
* Name: Raymond Xie
* Student No: 251275727
* Name: GraphNode
* Description: The GraphNode class that handles everything relating to the node
*/

public class GraphNode {

    // Instance variables
    private int name;
    private boolean mark;

    // Constructor method
    public GraphNode(int name) {
        // Sets name as the integer entered into the constructor
        this.name = name;
        // Sets mark to false by default
        this.mark = false;
    }

    // Setter methods
    // Sets the mark to the boolean value entered into the method
    public void mark(boolean mark) {
        this.mark = mark;
    }

    // Getter methods
    // Returns the mark of the node
    public boolean isMarked() {
        return mark;
    }

    // Returns the name of the node
    public int getName() {
        return name;
    }
}
