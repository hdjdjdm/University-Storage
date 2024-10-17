package resourcegraph;

import java.util.ArrayList;

public class TestGraph {
    public static void runTestGraph(){
        ArrayList<Node> nodes = new ArrayList<>();
        nodes.add(new Node("R")); // 0
        nodes.add(new Node("A")); // 1
        nodes.add(new Node("S")); // 2
        nodes.add(new Node("C")); // 3
        nodes.add(new Node("F")); // 4
        nodes.add(new Node("W")); // 5
        nodes.add(new Node("D")); // 6
        nodes.add(new Node("B")); // 7
        nodes.add(new Node("T")); // 8
        nodes.add(new Node("E")); // 9
        nodes.add(new Node("V")); // 10
        nodes.add(new Node("G")); // 11
        nodes.add(new Node("U")); // 12
        nodes.add(new Node("Z")); // 13

        nodes.get(0).addDirectNode(nodes.get(1));
        nodes.get(1).addDirectNode(nodes.get(2));
        nodes.get(3).addDirectNode(nodes.get(2));
        nodes.get(4).addDirectNode(nodes.get(2));
        nodes.get(5).addDirectNode(nodes.get(4));
        nodes.get(6).addDirectNode(nodes.get(2));
        nodes.get(6).addDirectNode(nodes.get(8));
        nodes.get(7).addDirectNode(nodes.get(8));
        nodes.get(8).addDirectNode(nodes.get(9));
        nodes.get(9).addDirectNode(nodes.get(10));
        nodes.get(10).addDirectNode(nodes.get(11));
        nodes.get(11).addDirectNode(nodes.get(12));
        nodes.get(12).addDirectNode(nodes.get(6));
        nodes.get(13).addDirectNode(nodes.get(8));

        new ResourceGraph(nodes);
    }
}
