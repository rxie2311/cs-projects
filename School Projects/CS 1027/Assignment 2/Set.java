public class Set<T> {

    // Instance variables
    LinearNode<T> setStart;

    // Constructor method
    public Set() {
        setStart = null;
    }

    // Adds a new node containing the given element
    public void add(T element) {
        // Creates a new node with the element set as the new node
        LinearNode<T> newnode = new LinearNode<T>(element);

        // Checks if the start of the linked list is null, meaning there is an empty list
        if(setStart == null) {
            // Sets the current node as the new start
            newnode.setNext(setStart);
            setStart = newnode;
        } else {
            // If the list is not empty, adds the node to the start of the list
            newnode.setNext(setStart.getNext());
            setStart.setNext(newnode);
        }
    }

    // Returns the length of the linked list
    public int getLength() {
        // Sets the current node at the start of the list
        LinearNode<T> curr = setStart;
        // Counter variable that will return the length
        int counter = 0;

        // While loop will not stop until it hits a null (meaning it has reached the end of the list)
        while(curr != null) {
            // Adds 1 to the counter
            counter++;
            // Sets the current node as the node after
            curr = curr.getNext();
        }

        // Returns the length of the list
        return counter;
    }

    // Gets the element in the list according to position given
    public T getElement(int i) {
        // Sets the current node at the start of the list
        LinearNode<T> curr = setStart;
        // Counter variable to check current position
        int counter = 0;

        // While loop will not stop until it hits a null (meaning it has reached the end of the list)
        while(curr != null) {
            // If the counter matches the position given
            if(counter == i) {
                // Returns the element in the node at given position
                return curr.getElement();
            }
            // If it does not find the correct position, adds 1 to position number
            counter++;
            // Sets the current node as the node after
            curr = curr.getNext();
        }

        // Returns null if the position was not found
        return null;
    }

    // Checks if the linked list contains a certain element
    public boolean contains(T element) {
        // Sets the current node at the start of the list
        LinearNode<T> curr = setStart;

        // While loop will not stop until it hits a null (meaning it has reached the end of the list)
        while(curr != null) {
            // If the current element in the node matches the given element
            if(curr.getElement() == element) {
                // Returns true
                return true;
            }

            // Sets the current node as the node after
            curr = curr.getNext();
        }

        // Returns false if the linked list does not contain the element given
        return false;
    }

    public String toString() {
        // Empty string to store the finished string
        String S = "";
        // Sets the current node at the start of the list
        LinearNode<T> curr = setStart;

        while(curr != null) {
            // Concatenates the previous S with the current element with a space added in between
            S = S + " " + curr.getElement();
            // Sets the current node as the node after
            curr = curr.getNext();
        }

        // Returns the string
        return S;
    }

}
