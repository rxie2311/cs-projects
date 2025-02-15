/*
 * Name: Raymond Xie
 * Student No: 251275727
 * Program Name: BSTDictionary
 * Description: Creates an ordered dictionary that uses a binary search tree to store values
 */

public class BSTDictionary implements BSTDictionaryADT {

    // Instance variables
    private BinarySearchTree tree;

    // Constructor method:
    public BSTDictionary() {
        // Creates a new binary search tree
        tree = new BinarySearchTree();
    }

    // Implemented methods:
    // Gets the record stored in node with key k in the dictionary
    public Record get(Key k) {
        BSTNode root = tree.getRoot();
        BSTNode result = tree.get(root, k);

        if(result != null) {
            return result.getRecord();
        } else {
            return null;
        }
    }

    // Puts a record into the dictionary
    public void put(Record d) throws DictionaryException {
        BSTNode root = tree.getRoot();
        tree.insert(root, d);
    }

    // Removes the node with key k from the dictionary
    public void remove(Key k) throws DictionaryException {
        BSTNode root = tree.getRoot();
        tree.remove(root, k);
    }

    // Finds the successor of key k in the dictionary
    public Record successor(Key k) {
        BSTNode root = tree.getRoot();
        BSTNode result = tree.successor(root, k);

        if(result != null) {
            return result.getRecord();
        } else {
            return null;
        }
    }

    // Finds the predecessor of key k in the dictionary
    public Record predecessor(Key k) {
        BSTNode root = tree.getRoot();
        BSTNode result = tree.predecessor(root, k);

        if(result != null) {
            return result.getRecord();
        } else {
            return null;
        }
    }

    // Finds the smallest node in the dictionary
    public Record smallest() {
        BSTNode root = tree.getRoot();
        BSTNode result = tree.smallest(root);

        if(result != null) {
            return result.getRecord();
        } else {
            return null;
        }
    }

    // Finds the largest node in the dictionary
    public Record largest() {
        BSTNode root = tree.getRoot();
        BSTNode result = tree.largest(root);

        if(result != null) {
            return result.getRecord();
        } else {
            return null;
        }
    }

}
