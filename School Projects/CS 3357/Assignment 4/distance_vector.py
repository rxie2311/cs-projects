# Author: Raymond Xie
# Student No: 251275727
# Description: A program that uses Bellman-Ford to calculate the shortest path to each node.

import sys


# Method to calculate the distance between each of the nodes using Bellman-Ford
def calc_distance(N, edges, starting_node):
    # Initializing distance vector of size N, setting all items in it to infinity because algorithm has not started yet
    distances = [float('inf')] * N
    # Setting index starting_node as 0 because the node does not have a path to itself
    distances[starting_node] = 0

    # Relaxing all the edges in the graph, i represents the current relaxation
    for i in range(N):
        # Cycling through all the nodes row by row
        for u in range(N):
            # Cycling through all the nodes column by column
            for v in range(N):
                # Making sure path between current node and node u exists and path between node u and v also exists
                if distances[u] != float('inf') and edges[u][v] != float('inf'):
                    # Then checks if the path between current node and u and the path between u and v added together is
                    # less than the path between the current node and node v
                    if distances[u] + edges[u][v] < distances[v]:
                        # If it is currently the Nth relaxation, then there is a negative cycle
                        if i == N - 1:
                            # If there is a negative cycle, then returns None
                            return None

                        # If path from curr node to node u and the edge between u and v is shorter than the path from
                        # curr node to node v, then updates the shortest distance to node v with the shorter path
                        distances[v] = distances[u] + edges[u][v]

    # Returns the distance vector at the end of the method
    return distances


# Main method
def main():
    # Takes in the input and splits the input when there is a newline character
    userInput = sys.stdin.read().splitlines()
    # Since the first line is the size of the graph, takes the first line and stores it into a size variable
    N = int(userInput[0])

    # Temporary array variable to save all user input inside to be turned into a NxN matrix
    graph = []
    # Converting all the numbers in the user input into int and "f" into float('inf') (positive infinity)
    # Ignores index 0 since that was the size of the graph
    for i in range(1, len(userInput)):
        # Temp variable to store current index of userInput
        temp = userInput[i]

        # If temp == "f", then add positive infinity to the temp array
        if temp == "f":
            graph.append(float('inf'))
        # If temp != "f", then turn the string into an int and add the int to the temp array
        else:
            graph.append(int(temp))

    # Array to store arrays (representing nodes) with edges to the other nodes inside
    edges = []
    # Array to store the weights of the edges to the other nodes for the current node
    node_edges = []
    # Creating an NxN matrix of edges
    for i in range(len(graph)):
        # Adds the current index i of array graph into node_edges
        node_edges.append(graph[i])

        # Checks if i is divisible by N, if it is then it means all the edges to the other nodes have been saved for
        # the current node i
        if (i+1) % N == 0:
            # Appends a copy of node_edges to edges and clears node_edges
            edges.append(list(node_edges))
            node_edges.clear()

    # For each of the nodes (N nodes total), creates a distance vector for each one by using calc_distance
    for node in range(N):
        # Calls on calc_distance to generate the shortest distances between node and all the other nodes in the graph
        distance = calc_distance(N, edges, node)

        # If distance is None, it means there was a negative cycle, so sets all distances to None and prints it out
        if distance is None:
            print(f"Node {node}: [" + "None, " * (N-1) + "None" + "]")
        # If distance returns a not None array, then prints it out
        else:
            print(f"Node {node}: {distance}")


# Running the main method
if __name__ == "__main__":
    main()
