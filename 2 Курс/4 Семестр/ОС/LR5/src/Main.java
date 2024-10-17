import resourcegraph.Node;
import resourcegraph.ResourceGraph;

import java.util.ArrayList;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        System.out.println("Deadlock resource graph");
        ArrayList<Node> nodes = new ArrayList<>();
        nodes.add(new Node("S")); // 0
        nodes.add(new Node("A")); // 1
        nodes.add(new Node("G")); // 2
        nodes.add(new Node("B")); // 3

        nodes.get(0).addDirectNode(nodes.get(2));
        nodes.get(1).addDirectNode(nodes.get(3));
        nodes.get(2).addDirectNode(nodes.get(1));
        nodes.get(3).addDirectNode(nodes.get(0));
        new ResourceGraph(nodes);
        System.out.println();

        System.out.println("Avoiding deadlock resource graph");
        ArrayList<Node> noCycleNodes = new ArrayList<>();
        noCycleNodes.add(new Node("S")); // 0
        noCycleNodes.add(new Node("A")); // 1
        noCycleNodes.add(new Node("L")); // 2
        noCycleNodes.add(new Node("G")); // 3
        noCycleNodes.add(new Node("B")); // 4

        noCycleNodes.get(2).addDirectNode(noCycleNodes.get(3));
        noCycleNodes.get(2).addDirectNode(noCycleNodes.get(4));
        noCycleNodes.get(3).addDirectNode(noCycleNodes.get(0));
        noCycleNodes.get(3).addDirectNode(noCycleNodes.get(1));
        noCycleNodes.get(4).addDirectNode(noCycleNodes.get(0));
        noCycleNodes.get(4).addDirectNode(noCycleNodes.get(1));

        new ResourceGraph(noCycleNodes);

        System.out.println("Avoid deadlock:");
        GirlLock girlLock = new GirlLock("Girl_Lock");
        BoyLock boyLock = new BoyLock("Boy_Lock");
        girlLock.start();
        boyLock.start();
        girlLock.join();
        boyLock.join();

        System.out.println("\nDeadlocked threads: ");
        Girl girl = new Girl("T1");
        Boy boy = new Boy("T2");
        girl.start();
        boy.start();
        girl.join();
        boy.join();
    }
}
