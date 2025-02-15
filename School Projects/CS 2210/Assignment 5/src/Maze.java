// Importing Java libraries to read files
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
// Importing Java libraries to create an iterator
import java.util.ArrayList;
import java.util.Iterator;

/*
 * Name: Raymond Xie
 * Student No: 251275727
 * Name: Maze
 * Description: The Maze class that creates the maze from files and solves the maze using the quickest path
 */

public class Maze {

    // Instance variables
    // Graph variable
    private Graph graph;
    // ArrayList to be turned into iterator holding the path to the maze
    private ArrayList<GraphNode> path = new ArrayList<>();
    // Other variables pertaining to the maze
    private int width, length, size, coins;
    // Reference variables to entrance and exit of maze
    private GraphNode entrance, exit;

    // Constructor method
    public Maze(String inputFile) throws MazeException {
        // Try-catch to read the file
        try {
            // Creating a new file reader
            File f = new File(inputFile);
            Scanner reader = new Scanner(f);

            // Ignores scale (first line of file)
            reader.nextLine();

            // Saving width, length, coins
            width = Integer.parseInt(reader.nextLine());
            length = Integer.parseInt(reader.nextLine());
            coins = Integer.parseInt(reader.nextLine());
            // Obtains size by multiplying length and width
            size = width * length;

            // Generating new graph using size as the boundaries
            graph = new Graph(size);

            // Temp variables
            // Stores the letter grid from the file
            char[][] temp = new char[(width*2)-1][(length*2)-1];
            // Stores the currently being read line
            String tempString;

            // Storing all the letters in the grid in the file into the temporary array
            for(int i=0; i<((length*2)-1); i++) {
                tempString = reader.nextLine();
                // Converts the String into a char array
                char[] tempChar = tempString.toCharArray();
                // Saves the char array elements into the correct positions in the temp array
                for(int j=0; j<((width*2)-1); j++) {
                    temp[j][i] = tempChar[j];
                }
            }

            // Double array to start adding edges where there are corridors/doors
            for(int i=0; i<length; i++) {
                for(int j=0; j<width; j++) {
                    // Check if node is an entrance
                    if(temp[2*j][2*i] == 's') {
                        // If node s is found, saves it as a reference to entrance
                        entrance = graph.getNode((i*width)+j);

                    // Check if node is an exit
                    } else if(temp[2*j][2*i] == 'x') {
                        // If node x is found, saves it as a reference to exit
                        exit = graph.getNode((i*width)+j);
                    }

                    // Check horizontal connections
                    if((2*j)+1 < (2*width)-1) {
                        // If the letter in between the two nodes is not a wall
                        if(temp[(2*j)+1][2*i] != 'w') {
                            // If the letter is c
                            if(temp[(2*j)+1][2*i] == 'c') {
                                // Insert corridor
                                graph.insertEdge(graph.getNode((i*width)+j), graph.getNode((i*width)+j+1), 0, "corridor");

                            // If it is a number
                            } else {
                                // Insert door
                                graph.insertEdge(graph.getNode((i*width)+j), graph.getNode((i*width)+j+1), Integer.parseInt(String.valueOf(temp[(2*j)+1][2*i])), "door");
                            }
                        }
                    }

                    // Check vertical connections
                    if((2*i)+1 < (2*length)-1) {
                        // If the letter in between the two nodes is not a wall
                        if(temp[2*j][(2*i)+1] != 'w') {
                            // If the letter is c
                            if(temp[2*j][(2*i)+1] == 'c') {
                                // Insert corridor
                                graph.insertEdge(graph.getNode((i*width)+j), graph.getNode(((i+1)*width)+j), 0, "corridor");

                            // If it is a number
                            } else {
                                // Insert door
                                graph.insertEdge(graph.getNode((i*width)+j), graph.getNode(((i+1)*width)+j), Integer.parseInt(String.valueOf(temp[2*j][(2*i)+1])), "door");
                            }
                        }
                    }
                }
            }

        // If any file related issue comes up
        } catch (FileNotFoundException e) {
            throw new MazeException("Error: Maze could not be generated due to file not found.");

        // If there was an error in adding edges to the graph
        } catch (GraphException e) {
            throw new MazeException("Error: Maze could not be generated due to a problem with inserting edges.");
        }
    }

    // Getter method
    // Returns graph, returns an error if graph is null
    public Graph getGraph() throws MazeException {
        // If the graph is null, throws error
        if(graph == null) {
            throw new MazeException("Error: Could not return graph because graph is null.");
        }

        // Returns graph if it is not null
        return graph;
    }

    // Solves the maze when called on
    public Iterator solve() throws GraphException {
        // curr node to cycle through the maze
        GraphNode curr = entrance;
        // end node to save exit node location
        GraphNode end = exit;
        // startingCoins variable to save the amount of coins to start with
        int startingCoins = coins;

        // Returns the result of the recursive method
        return navigate(curr, end, startingCoins);
    }

    // Private helper method
    // Recursion method to help solve the maze and find a path
    private Iterator navigate(GraphNode curr, GraphNode end, int coins) throws GraphException {
        // Adds the current node into the path ArrayList
        curr.mark(true);
        path.add(curr);

        // Checks if the curr node is at the end (exit)
        if(curr.getName() == end.getName()) {
            // Returns the iterator if the current node is at the exit
            return path.iterator();
        }

        // Creates an iterator to store all incident edges of the current node to loop through
        Iterator<GraphEdge> incidentEdges = graph.incidentEdges(curr);

        // While loop to loop through all incident edges of curr to decide on the node to jump to
        while(incidentEdges.hasNext()) {
            // Current corridor (edge) the loop is on
            GraphEdge currEdge = incidentEdges.next();
            // Setting the next node as the second endpoint of the edge as default (node may have been marked)
            GraphNode next = currEdge.secondEndpoint();
            // Saving current coin amount as a variable
            int currCoins = coins;

            // Checks if next is the same node as curr (if the current node is currently on the edge's second endpoint)
            if(next == curr) {
                // If next is the current node, then change it to the first endpoint of the edge to look for
                // more incident edges to go to next (labeled as discovery)
                next = currEdge.firstEndpoint();
            }

            // If the edge is a corridor type and not marked
            if(!next.isMarked() && currEdge.getLabel().equals("corridor")) {
                // Recurses through this edge
                Iterator currPath = navigate(next, end, currCoins);

                // If it does not return null, returns the iterator
                if(currPath != null) {
                    return currPath;
                }

            // If the edge is a door type and not marked
            } else if(!next.isMarked() && currEdge.getLabel().equals("door") && (currCoins - currEdge.getType()) >= 0) {
                // Subtracts the current coins from the door cost
                currCoins = currCoins - currEdge.getType();
                // Recurses through this edge
                Iterator currPath = navigate(next, end, currCoins);

                // If it does not return null, returns the iterator
                if(currPath != null) {
                    return currPath;
                }
            }
        }

        // If no path was found, removes from path ArrayList and de-marks it (backtracks)
        curr.mark(false);
        path.remove(curr);
        // Returns null afterwards
        return null;
    }
}
