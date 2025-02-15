/*
 * Name: Raymond Xie
 * Student No: 251275727
 * Program Name: BSTNode
 * Description: Defines the nodes that are in the BST (Binary Search Tree)
 */

public class BSTNode {

    // Instance variables
    private Record record;
    private BSTNode left, right, parent;

    // Constructor method:
    public BSTNode(Record item) {
        record = item;
        parent = null;
        left = right = null;
    }

    // Getter methods:
    // Returns the record stored in the node
    public Record getRecord() {
        return record;
    }
    // Returns the left child
    public BSTNode getLeftChild() {
        return left;
    }
    // Returns the right child
    public BSTNode getRightChild() {
        return right;
    }
    // Returns the parent node
    public BSTNode getParent() {
        return parent;
    }

    // Setter methods:
    // Sets the record stored in the node
    public void setRecord(Record d) {
        record = d;
    }
    // Sets the left child
    public void setLeftChild(BSTNode u) {
        left = u;
    }
    // Sets the right child
    public void setRightChild(BSTNode u) {
        right = u;
    }
    // Sets the parent node
    public void setParent(BSTNode u) {
        parent = u;
    }

    // Other methods:
    // Determines if node is a leaf or not
    public boolean isLeaf() {
        // Returns if leaf or not
        return left == null && right == null;
    }

}
