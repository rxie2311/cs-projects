public class DLPriorityQueue<T> implements PriorityQueueADT<T> {

    // Instance variables
    private DLinkedNode<T> front;
    private DLinkedNode<T> rear;
    private int count;

    // Creates an empty priority queue
    public DLPriorityQueue() {
        count = 0;
        front = null;
        rear = null;
    }

    // Adds a node to the queue
    public void add(T dataItem, double priority) {
        // New node with dataItem and priority stored in it
        DLinkedNode<T> newNode = new DLinkedNode<T>(dataItem, priority);
        DLinkedNode<T> curr = front;

        // Checking if queue is empty
        if(front == null) {
            // Sets both rear and front to the same node
            front = newNode;
            rear = newNode;
            // Adds a node to the count
            count++;

        // If queue is not empty
        } else {
            // While loop to add node into correct position based on prio
            while(curr != null) {
                // If newNode prio < curr prio and curr is the frontal node
                if(newNode.getPriority() < curr.getPriority() && curr == front) {
                    // Swaps the two nodes
                    curr.setPrev(newNode);
                    newNode.setNext(curr);
                    // Sets newNode as front
                    front = newNode;
                    // Updates count
                    count++;
                    // Breaks
                    break;
                // If newNode prio < curr prio and curr is not the front
                } else if(newNode.getPriority() < curr.getPriority()) {
                    // Swaps two nodes
                    newNode.setPrev(curr.getPrev());
                    newNode.setNext(curr);
                    curr.getPrev().setNext(newNode);
                    curr.setPrev(newNode);
                    // Updates count
                    count++;
                    // Breaks
                    break;
                // If curr next is null (meaning curr is rear)
                } else if(curr.getNext() == null) {
                    // Swaps the two nodes
                    curr.setNext(newNode);
                    newNode.setPrev(curr);
                    // Sets rear as newNode
                    rear = newNode;
                    // Sets newNode next as null
                    rear.setNext(null);
                    // Updates count
                    count++;
                    // Breaks
                    break;
                }
                // Updates curr in the loop to go through entire queue
                curr = curr.getNext();
            }
        }
    }

    // Changes the priority of dataItem to the new priority
    public void updatePriority(T dataItem, double newPriority) throws InvalidElementException {
        // Node curr to help run through the queue
        DLinkedNode<T> curr = front;
        // Boolean found that updates if dataItem is found in the queue
        boolean found = false;

        // While loop to help run through queue
        while(curr != null) {
            // If the loop finds the data item in the queue
            if(curr.getDataItem() == dataItem) {
                // Updates found as true
                found = true;
                // Sets new priority for node
                curr.setPriority(newPriority);
                // Breaks out to go and sort the queue
                break;
            }
            // Sets curr to the next node in queue
            curr = curr.getNext();
        }

        // If the item was not in the queue, throws exception and breaks out
        if(!found) {
            throw new InvalidElementException("Item was not found in queue.");
        }

        // Temp variable to help store swapped nodes
        DLinkedNode<T> temp;
        // Int variable to help determine which position the updated node is in
        int i = 3;

        // If both values around current are null
        if (curr.getNext() == null && curr.getPrev() == null) {
            i = 3; // Set i=3, skips while loop below

        // If only next node is null and prev node has a value
        } else if (curr.getNext() == null && curr.getPrev() != null) {
            if (curr.getPriority() < curr.getPrev().getPriority()) {
                i = 1; // Sets i=1 when curr prio is < than curr prev prio
            }

        // If only prev node is null and next node has a value
        } else if (curr.getPrev() == null && curr.getNext() != null) {
            if (curr.getPriority() > curr.getNext().getPriority()) {
                i = 2; // Sets i=2 when curr prio is > than curr next prio
            }

        // For every other scenario
        } else {
            // If curr prio is > than curr next prio
            if (curr.getPriority() > curr.getNext().getPriority()) {
                i = 2;

            // If curr prio is < than curr prev prio
            } else if (curr.getPriority() < curr.getPrev().getPriority()) {
                i = 1;
            }
        }

        // While loop to sort (skips if i=3)
        while(i < 3) {
            // If curr prio > than curr next prio
            if (i == 2) {
                // If curr prio is > than curr next prio
                if (curr.getPriority() > curr.getNext().getPriority()) {
                    // Saves curr next as temp
                    temp = curr.getNext();
                    // Checks if next is null
                    if (temp.getNext() == null) {
                        curr.setNext(null);
                        // Sets rear as curr
                        rear = curr;
                        // Breaks out using i=3
                        i = 3;
                    // Keeps going if next is not null
                    } else {
                        curr.setNext(temp.getNext());
                        curr.getNext().setPrev(curr);
                    }

                    // Set next next pointer to current
                    temp.setNext(curr);

                    // Set next previous pointer to current previous pointer
                    if (curr.getPrev() == null) {
                        front = temp;
                        temp.setPrev(null);
                    } else {
                        temp.setPrev(curr.getPrev());
                        temp.getPrev().setNext(temp);
                    }

                    // Set current previous pointer to next
                    curr.setPrev(temp);

                } else {
                    i = 3;
                }
            } else {
                // If prio of curr is < than prio of prev curr
                if (curr.getPriority() < curr.getPrev().getPriority()) {
                     temp = curr.getPrev();
                    // Set previous next pointer to current next pointer
                    if (curr.getNext() == null) {
                        temp.setNext(null);
                        rear = temp;
                    // Keeps going if next is not null
                    } else {
                        temp.setNext(curr.getNext());
                        temp.getNext().setPrev(temp);
                    }
                    // Set current next pointer to previous
                    curr.setNext(temp);

                    // Checks if prev is null
                     if (temp.getPrev() == null) {
                         curr.setPrev(null);
                         // Sets front as curr
                         front = curr;
                         // Breaks out using i=3
                         i = 3;
                     // Keeps going if prev is not null
                     } else {
                         curr.setPrev(temp.getPrev());
                         curr.getPrev().setNext(curr);
                     }
                    // Set previous previous pointer to current
                     temp.setPrev(curr);

                } else {
                    i = 3;
                }
            }

        }
    }

    // Removes and returns the data item at the front of the queue (smallest priority)
    public T removeMin() throws EmptyPriorityQueueException {
        // Taking the front most node for returning
        DLinkedNode<T> curr = front;

        // Checks if front is null
        if(curr != null) {
            // Sets front to the next node
            front = curr.getNext();
            // Updates count
            count-= 1;
            // Returns the dataItem in curr
            return curr.getDataItem();
        // If front is null (empty queue)
        } else {
            throw new EmptyPriorityQueueException("Queue is empty.");
        }
    }

    // Checks if the queue is empty
    public boolean isEmpty() {
        // Checks if front is null, returns true if it is
        if(front == null) {
            return true;
        // If front is not null: queue is not empty
        } else {
            return false;
        }
    }

    // Returns the queue size
    public int size() {
        // Returns count
        return count;
    }

    // Prints out the queue in string format
    public String toString() {
        // Sets curr to front to start at the front of the queue
        DLinkedNode<T> curr = front;
        // String to be updated in the loop
        String S = "";

        // Runs through the queue and counts the items inside
        while(curr != null) {
            S = S + curr.getDataItem();
            curr = curr.getNext();
        }

        // Returns the concatenated string at the end
        return S;
    }

    // Returns the rear of the queue
    public DLinkedNode<T> getRear() {
        return rear;
    }

}
