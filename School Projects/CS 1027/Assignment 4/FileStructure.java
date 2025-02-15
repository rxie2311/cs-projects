import java.util.Iterator;
import java.util.ArrayList;

public class FileStructure {

    // Instance variables
    private NLNode<FileObject> root; // Reference to root node

    // Constructor
    public FileStructure(String fileObjectName) throws FileObjectException {
        // New FileObject object represented by fileObjectName
        FileObject fileObj = new FileObject(fileObjectName);
        // Saves fileObj into root
        root = new NLNode<>();
        root.setData(fileObj);

        // Calls on recursive method, only recurse if directory name is root
        fileBuilder(root);
    }

    // Recursive method for constructor FileStructure
    private void fileBuilder(NLNode<FileObject> r) {
        // Recursive condition: If r is a directory
        if(r.getData().isDirectory()) {
            // New iterator object to store all directory files in r
            FileObject f = r.getData();
            Iterator<FileObject> i = f.directoryFiles();

            // Loops until child iterator has no more values
            while(i.hasNext()) {
                // New node object
                NLNode<FileObject> n = new NLNode<>();
                // Sets data of n as next directory file in iterator
                n.setData(i.next());
                // Sets n's parent to r
                n.setParent(r);
                // Sets n as r's child
                r.addChild(n);

                // Recurse but with n as the parameter until file name shows up
                fileBuilder(n);
            }
        }
    }

    // Returns the root variable
    public NLNode<FileObject> getRoot() {
        return root;
    }

    // Returns String iterator of all files of type specified
    public Iterator<String> filesOfType(String type) {
        // New array list to store all fileNames of the same type as parameter
        ArrayList<String> fileNames = new ArrayList<String>();
        // Calls on recursive method
        fileType(type, root, fileNames);

        // Returns fileNames as an iterator
        return fileNames.iterator();
    }

    // Recursive method for filesOfType
    private void fileType(String t, NLNode<FileObject> r, ArrayList<String> a) {
        // Base condition: If r is a file
        if(r.getData().isFile()) {
            // Sets data of r as a FileObject
            FileObject f = r.getData();

            // Checks if file name contains file type t
            if(f.getName().contains(t)) {
                // Adds to the array list if file name contains file type t
                a.add(f.getLongName());
            }

        // Recursive condition: If r is a directory
        } else if(r.getData().isDirectory()) {
            // Child iterator
            Iterator<NLNode<FileObject>> i = r.getChildren();

            // Loops until child iterator has no more values
            while(i.hasNext()) {
                // Sets n to the next child in the iterator
                NLNode<FileObject> n;
                n = i.next();

                // Recurse until r is a file name and no longer a directory name
                fileType(t, n, a);
            }
        }
    }

    // Looks for a file with the same name in File Structure
    public String findFile(String name) {
        // Returns result of recursion
       return find(name, root);
    }


    private String find(String s, NLNode<FileObject> r) {
        // Long file name string
        String t;
        // Base condition: If r is a file
        if(r.getData().isFile()) {
            // Root data saved as a FileObject
            FileObject f = r.getData();

            // If the name of file equals the name of file taken from s
            if(f.getName().equals(s)) {
                // Returns long name of file (file path)
                return f.getLongName();
            }

        // Recursive condition: If r is a directory
        } else if(r.getData().isDirectory()) {
            // Child iterator
            Iterator<NLNode<FileObject>> i = r.getChildren();

            // Loops until child iterator has no more values
            while(i.hasNext()) {
                // Sets n to the next child in the iterator
                NLNode<FileObject> n;
                n = i.next();

                // Generating long file name by adding each recursion into String t
                t = find(s, n);

                // If one match is found, stops recursion and returns
                if(!t.equals("")) {
                    // Returns to the start of the method
                    return t;
                }
            }
        }

        // If match is not found, return empty string
        return "";
    }


}
