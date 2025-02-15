import java.util.Iterator;
import java.util.Comparator;

public class NLNode <T> {

    // Instance variables
    private NLNode<T> parent; // Unique node that hs a reference to this node
    private ListNodes<NLNode<T>> children; // List storing children of this node
    private T data; // Reference to data stored inside this node

    // Constructor that sets parent and data to null
    public NLNode() {
        // Sets parent and data to null
        parent = null;
        data = null;
        // Initializes children to empty ListNodes list
        children = new ListNodes<>();
    }

    // Constructor that sets parent to p and data to d
    public NLNode(T d, NLNode<T> p) {
        // Sets data to d and parent to p
        parent = p;
        data = d;
        // Initializes children to empty ListNodes list
        children = new ListNodes<>();
    }

    // Methods
    // Sets parent to p
    public void setParent(NLNode<T> p) {
        parent = p;
    }

    // Sets data to d
    public void setData(T d) {
        data = d;
    }

    // Returns parent
    public NLNode<T> getParent() {
        return parent;
    }

    // Returns data
    public T getData() {
        return data;
    }

    // Adds newChild to the list of children
    public void addChild(NLNode<T> newChild) {
        // Adds newChild into children list
        children.add(newChild);
    }

    // Returns an iterator of children from this node
    public Iterator<NLNode<T>> getChildren() {
        // Returns children as an iterator
        return children.getList();
    }

    // Sorts the iterator based on sorter
    public Iterator<NLNode<T>> getChildren(Comparator<NLNode<T>> sorter) {
        // Returns an iterator sorted by sorter
        return children.sortedList(sorter);
    }
}
