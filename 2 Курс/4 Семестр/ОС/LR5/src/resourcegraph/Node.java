package resourcegraph;

import java.util.ArrayList;

public class Node {
    String name;
    private final ArrayList<Node> direct = new ArrayList<>();
    public Node(String name) {
        this.name = name;
    }
    public void addDirectNode(Node node){
        direct.add(node);
    }
    public ArrayList<Node> getDirect() {
        return direct;
    }
}
