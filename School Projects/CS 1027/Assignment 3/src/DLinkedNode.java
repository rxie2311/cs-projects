public class DLinkedNode<T> {

    // Instance variables
    private T dataItem;
    private double priority;
    private DLinkedNode<T> next;
    private DLinkedNode<T> prev;

    // Creates a node storing the given data item and priority
    public DLinkedNode(T data, double prio) {
        // New node with data and prio stored inside
        dataItem = data;
        priority = prio;
    }

    // Creates an empty node, with null dataItem and zero priority
    public DLinkedNode() {
        // Empty node with null and 0 inside
        dataItem = null;
        priority = 0;
    }

    // Getter methods:
    // Returns priority
    public double getPriority() {
        return priority;
    }

    // Returns data item
    public T getDataItem() {
        return dataItem;
    }

    // Returns prev
    public DLinkedNode<T> getPrev() {
        return prev;
    }

    // Returns next
    public DLinkedNode<T> getNext() {
        return next;
    }

    // Setter methods:
    // Sets data item
    public void setDataItem(T item) {
        dataItem = item;
    }

    // Sets priority
    public void setPriority(double item) {
        priority = item;
    }

    // Sets prev
    public void setPrev(DLinkedNode<T> item) {
        prev = item;
    }

    // Sets next
    public void setNext(DLinkedNode<T> item) {
        next = item;
    }

}
