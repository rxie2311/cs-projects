/*
 * Name: Raymond Xie
 * Student No: 251275727
 * Program Name: BinarySearchTree
 * Description: Creates the binary search tree
 */

public class BinarySearchTree {

    // Instance methods
    private BSTNode root;

    // Constructor method:
    public BinarySearchTree() {
        // Creates a leaf node as the root of the tree with null stored in it
        root = new BSTNode(null);
        root.setLeftChild(null);
        root.setRightChild(null);
    }

    // Getter methods:
    // Returns the root of the BST
    public BSTNode getRoot() {
        return root;
    }

    // Returns the node storing given key
    public BSTNode get(BSTNode r, Key k) {
        // Case 1: If root is null
        if(r.isLeaf()) {
            return null;
        }

        // Case 2: If key is the same as the key of the root node
        if(r.getRecord().getKey().compareTo(k) == 0) {
            return r;
        }

        // Case 3: If k is greater than root key
        if(r.getRecord().getKey().compareTo(k) == -1) {
            return get(r.getRightChild(), k);
        }

        // Case 4: If k is less than root key
        return get(r.getLeftChild(), k);
    }

    // Other methods:
    // Inserts a node into the tree
    public void insert(BSTNode r, Record d) throws DictionaryException {
        // Checks if tree is empty beforehand
        if(!r.isLeaf()) {
            // If the record is in the node
            if(r.getRecord().getKey().compareTo(d.getKey()) == 0) {
                // Throws exception if record is already in tree
                throw new DictionaryException("Tree already stores a record with the same key.");
            }
        }

        // If node is a leaf
        if(r.isLeaf()) {
            // Creates new node
            r.setRecord(d);
            // Creates two empty children nodes
            BSTNode left = new BSTNode(null);
            left.setParent(r);
            r.setLeftChild(left);

            BSTNode right = new BSTNode(null);
            right.setParent(r);
            r.setRightChild(right);

            return;
        }

        // Goes down the tree if root is not null
        // If d key is greater than r key (d key > r key)
        if(d.getKey().compareTo(r.getRecord().getKey()) == 1) {
            insert(r.getRightChild(), d);
        // If d key is less than r key (d key < r key)
        } else {
            insert(r.getLeftChild(), d);
        }
    }

    // Removes a node from the tree
    public void remove(BSTNode r, Key k) throws DictionaryException {
        // Checks if current root node is a leaf
        if(r.isLeaf()) {
            // Throws exception if key is not found
            throw new DictionaryException("Key was not found in the tree.");
        }

        // If curr's key is equal to k
        if(r.getRecord().getKey().compareTo(k) == 0) {
            // Case 1: If both children of curr are leaves
            if(r.getLeftChild().isLeaf() && r.getRightChild().isLeaf()) {
                // Sets all to null
                r.setLeftChild(null);
                r.setRightChild(null);
                r.setRecord(null);

            // Case 2: If curr's left child is a leaf and curr's right child is not a leaf
            } else if(r.getLeftChild().isLeaf() && !r.getRightChild().isLeaf() && r.getParent() != null) {
                BSTNode parent = r.getParent();
                // If parent is smaller than curr, set curr's right child as the parent's right child
                if(parent.getRecord().getKey().compareTo(r.getRecord().getKey()) == -1) {
                    parent.setRightChild(r.getRightChild());
                    r.getRightChild().setParent(parent);

                // If parent is greater than curr, set curr's right child as the parent's left child
                } else if(parent.getRecord().getKey().compareTo(r.getRecord().getKey()) == 1) {
                    parent.setLeftChild(r.getRightChild());
                    r.getRightChild().setParent(parent);
                }

            // Case 3: If curr's left child is a leaf and curr's right child is not a leaf
            } else if(!r.getLeftChild().isLeaf() && r.getRightChild().isLeaf() && r.getParent() != null) {
                BSTNode parent = r.getParent();
                // If parent is smaller than curr, set curr's left child as the parent's right child
                if(parent.getRecord().getKey().compareTo(r.getRecord().getKey()) == -1) {
                    parent.setRightChild(r.getLeftChild());
                    r.getLeftChild().setParent(parent);

                // If parent is greater than curr, set curr's left child as the parent's left child
                } else if(parent.getRecord().getKey().compareTo(r.getRecord().getKey()) == 1) {
                    parent.setLeftChild(r.getLeftChild());
                    r.getLeftChild().setParent(parent);
                }

            // Case 4: If both children of curr are not leaves
            } else if(!r.getLeftChild().isLeaf() && !r.getRightChild().isLeaf() && r.getParent() != null) {
                BSTNode parent = r.getParent();
                // If parent is smaller than curr, set curr's left child as the parent's right child
                if(parent.getRecord().getKey().compareTo(r.getRecord().getKey()) == -1) {
                    parent.setRightChild(r.getLeftChild());
                    r.getLeftChild().setParent(parent);

                // If parent is greater than curr, set curr's left child as the parent's left child
                } else if(parent.getRecord().getKey().compareTo(r.getRecord().getKey()) == 1) {
                    parent.setLeftChild(r.getLeftChild());
                    r.getLeftChild().setParent(parent);
                }

                // Setting curr's right child at the bottom of the right branch of curr's left child
                BSTNode currLeft = r.getLeftChild();
                // While loop to get to the bottom of the rightmost branch
                while(!currLeft.getRightChild().isLeaf()) {
                    currLeft = currLeft.getRightChild();
                }
                // Sets the node at the bottom right as the new node to replace removed node
                currLeft.setRightChild(r.getRightChild());
                r.getRightChild().setParent(currLeft);

            // Case 5: If parent of curr is null and curr is the root
            } else if(r.getParent() == null) {
                // If left child exists, set as the new root and set right child at the bottom of the rightmost branch of the left child
                if(!r.getLeftChild().isLeaf()) {
                    root = r.getLeftChild();
                    r.getLeftChild().setParent(null);
                    // Setting curr's right child at the bottom of the right branch of curr's left child
                    BSTNode currLeft = r.getLeftChild().getRightChild();
                    // While loop to get to the bottom of the rightmost branch
                    while(!currLeft.getRightChild().isLeaf()) {
                        currLeft = currLeft.getRightChild();
                    }
                    // Sets the node at the bottom right as the new node to replace removed node
                    currLeft.setRightChild(r.getRightChild());
                    r.getRightChild().setParent(currLeft);

                // If the left child does not exist, set right child as the new root
                } else {
                    root = r.getRightChild();
                    r.getRightChild().setParent(null);
                }
            }

        // If curr's key is smaller than k, recurse with the right child as r
        } else if(r.getRecord().getKey().compareTo(k) == -1) {
            remove(r.getRightChild(), k);

        // If curr's key is greater than k, recurse with the left child as r
        } else if(r.getRecord().getKey().compareTo(k) == 1) {
            remove(r.getLeftChild(), k);
        }
    }

    // Returns the smallest key in the tree
    public BSTNode smallest(BSTNode r) {
        // If tree is empty (r is a leaf)
        if(r.isLeaf()) {
            // Returns null
            return null;

        // If there is only one node on the tree (if r is the only node)
        } else if(r.getLeftChild().isLeaf() && r.getRightChild().isLeaf()) {
            // Returns the only node (r)
            return r;

        // Every other scenario
        } else {
            // While loop to loop through the leftmost branch of the tree
            while(!r.getLeftChild().isLeaf()) {
                // Updates r until the left child of r's left child is a leaf
                r = r.getLeftChild();
            }
            // Returns r (now the smallest node on the leftmost branch)
            return r;
        }
    }

    // Returns the largest key in the tree
    public BSTNode largest(BSTNode r) {
        // If tree is empty (r is a leaf)
        if(r.isLeaf()) {
            // Returns null
            return null;

        // If there is only one node on the tree (if r is the only node)
        } else if(r.getLeftChild().isLeaf() && r.getRightChild().isLeaf()) {
            // Returns the only node (r)
            return r;

        // Every other scenario
        } else {
            // While loop to loop through the rightmost branch of the tree
            while(!r.getRightChild().isLeaf()) {
                // Updates r until the right child of r's right child is a leaf
                r = r.getRightChild();
            }
            // Returns r (now the largest node on the rightmost branch)
            return r;
        }
    }

    // Returns the successor node of the node with the key k
    public BSTNode successor(BSTNode r, Key k) {
        // If tree is empty (r is a leaf)
        if(r.isLeaf() || (r.getLeftChild().isLeaf() && r.getRightChild().isLeaf())) {
            // Returns null
            return null;

        // Every other scenario
        } else {
            // BSTNode variable to cycle through the tree
            BSTNode curr = r;
            boolean keyFound = false;
            // While loop that will stop when curr's key matches key k
            while(!curr.isLeaf()) {
                // If k is found in the tree
                if(curr.getRecord().getKey().compareTo(k) == 0) {
                    keyFound = true;
                    break;
                }

                // If curr's key is smaller than k
                if(curr.getRecord().getKey().compareTo(k) == -1) {
                    curr = curr.getRightChild();

                // If curr's key is larger than k
                } else if(curr.getRecord().getKey().compareTo(k) == 1) {
                    curr = curr.getLeftChild();
                }
            }

            // If key was found in tree
            if(keyFound) {
                // If curr and curr's right child are both internal nodes
                if(!curr.isLeaf() && !curr.getRightChild().isLeaf()) {
                    // Call on smallest method to find the smallest child in rightmost branch
                    return smallest(curr.getRightChild());

                // If curr and curr's right child are not internal nodes, search up the branch for successor
                } else {
                    // While loop that loops while curr's parent is not null and curr is the right child of curr's parent
                    while(curr.getParent() != null && curr.getParent().getRightChild() == curr) {
                        curr =  curr.getParent();
                    }

                    // If curr is equal to the root (meaning curr's parent is null)
                    if(curr == r) {
                        // Returns null (no successor)
                        return null;
                    } else {
                        // Returns curr's parent (since curr is no longer the right child of its parent)
                        return curr.getParent();
                    }
                }

            }

            // If key k was not found in the tree
            return null;
        }
    }

    // Returns the predecessor node of the node with the key k
    public BSTNode predecessor(BSTNode r, Key k) {
        // If tree is empty (r is a leaf)
        if(r.isLeaf() || (r.getLeftChild().isLeaf() && r.getRightChild().isLeaf())) {
            // Returns null
            return null;

        // Every other scenario
        } else {
            // BSTNode variable to cycle through the tree
            BSTNode curr = r;
            boolean keyFound = false;
            // While loop that will stop when curr's key matches key k
            while(!curr.isLeaf()) {
                // If k is found in the tree
                if(curr.getRecord().getKey().compareTo(k) == 0) {
                    keyFound = true;
                    break;
                }

                // If curr's key is smaller than k
                if(curr.getRecord().getKey().compareTo(k) == -1) {
                    curr = curr.getRightChild();

                // If curr's key is larger than k
                } else if(curr.getRecord().getKey().compareTo(k) == 1) {
                    curr = curr.getLeftChild();
                }
            }

            // If key was found in tree
            if(keyFound) {
                // If curr and curr's left child are both internal nodes
                if(!curr.isLeaf() && !curr.getLeftChild().isLeaf()) {
                    // Call on smallest method to find the largest child in leftmost branch
                    return largest(curr.getLeftChild());

                // If curr and curr's right child are not internal nodes, search up the branch for successor
                } else {
                    // While loop that loops while curr's parent is not null and curr is the left child of curr's parent
                    while(curr.getParent() != null && curr.getParent().getLeftChild() == curr) {
                        curr =  curr.getParent();
                    }

                    // If curr is equal to the root (meaning curr's parent is null)
                    if(curr == r) {
                        // Returns null (no successor)
                        return null;
                    } else {
                        // Returns curr's parent (since curr is no longer the left child of its parent)
                        return curr.getParent();
                    }
                }

            }

            // If key k was not found in the tree
            return null;
        }
    }

}
