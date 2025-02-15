import java.io.FileNotFoundException;
import java.io.IOException;

public class FindShortestPath {

    // Instance variable
    private static int steps;

    private static void shortestWay(Dungeon d) {
        // Creating empty prio queue
        DLPriorityQueue queue = new DLPriorityQueue();
        // exitFound boolean
        boolean exitFound = false;
        // distanceChanged boolean
        boolean distanceChanged;
        // steps Instance variable
        steps = 0;

        // While loop that will continuously loop if queue is not empty and exit has not been found
        Hexagon curr = d.getStart();
        queue.add(curr, 0);
        curr.markEnqueued();
        // Adds 1 to steps since start of dungeon was added to queue
        steps++;

        // Loop to find the exit
        while(!queue.isEmpty() && !curr.isExit()) {

            // Marks the current chamber as dequeued
            curr = (Hexagon) queue.removeMin();
            curr.markDequeued();

            // If the current tile is the exit, breaks out of the loop
            if(curr.isExit()) {
                exitFound = true;
                // Counts the amount of steps
                while(curr != d.getStart()) {
                    steps++;
                    curr = curr.getPredecessor();
                }
                // Breaks out after counting
                break;
            }

            // Checks if current is a dragon tile
            if(curr.isDragon()) {
                continue;
            }

            // Checking neighbors (6 possibilities, no. 0-5)
            for(int i=0; i<6; i++) {

                // Sets neighbor
                Hexagon neighbor = curr.getNeighbour(i);
                // Updates distanceChanged to false
                distanceChanged = false;

                // Checks if neighboring tile is not null, a wall, a dragon, lava and a cacti
                if(neighbor != null && !neighbor.isWall() && !neighbor.isMarkedDequeued() && !neighbor.isDragon()) {
                    // Setting up D
                    int D = 1 + curr.getDistanceToStart();

                    // If D needs to be updated
                    if(neighbor.getDistanceToStart() > D) {
                        // Updating neighbor's distance
                        neighbor.setDistanceToStart(D);
                        // Setting current as neighbor's predecessor
                        neighbor.setPredecessor(curr);
                        // Variable that is true when distance was updated
                        distanceChanged = true;
                    }

                    // If neighbor's distance to start is greater than D and is enqueued
                    if(neighbor.isMarkedEnqueued() && distanceChanged) {
                        // Updating neighbor's prio in queue
                        queue.updatePriority(neighbor, neighbor.getDistanceToStart() + neighbor.getDistanceToExit(d));

                    // If neighbor is not enqueued
                    } else if(!neighbor.isMarkedEnqueued()) {
                        // Adding neighbor into queue
                        queue.add(neighbor, neighbor.getDistanceToStart() + neighbor.getDistanceToExit(d));
                        // Marking neighbor as enqueued
                        neighbor.markEnqueued();
                    }
                }
            }
        }

        // If exitFound is true
        if(exitFound) {
            // Uses instance variable to track amount of steps
            System.out.println("Path of length " + steps + " found");
        // If an exit was not found
        } else {
            System.out.println("No path found");
        }
    }

    // Main method
    public static void main(String args[]) {
        try {
            // If args has a length of less than 1 (no file names in there)
            if(args.length < 1) {
                throw new Exception("No input file specified.");
            }
            // Creates new Dungeon object using args[0]
            String dungeonFileName = args[0];
            Dungeon d = new Dungeon(dungeonFileName);

            // Calls on shortestWay method (private helper method)
            shortestWay(d);

        // Catches any error when the file is not found
        } catch(FileNotFoundException e) {
            System.out.println("The file in question was not found.");
        // Catches any invalid characters in files
        } catch(InvalidDungeonCharacterException e) {
            System.out.println("Inputted file contains an invalid character.");
        // Catches IO exceptions
        } catch(IOException e) {
            System.out.println("An input/output error occurred.");
        // Catches any other exceptions that may occur during the run time of the program
        } catch(Exception e) {
            System.out.println("An exception occurred: " + e);
        }
    }

}
