package resourcegraph;

import java.util.ArrayList;
import java.util.Objects;

public class ResourceGraph {
    private final ArrayList<Node> nodes;
    private final ArrayList<ArrayList<Integer>> cycleNodePatterns = new ArrayList<>();
    private final ArrayList<Integer> bufNodes = new ArrayList<>();
    private final int[][] matrix;
    private boolean cycleWasFound = false;
    public ResourceGraph(ArrayList<Node> nodes){
        this.nodes = nodes;
        matrix = new int[nodes.size()][nodes.size()];
        fillMatrix();
        writeMatrix();
        cycleSearch(0);
        writeCycles();
    }
    public void fillMatrix(){
        for (int i = 0; i < nodes.size(); i++){
            for (int j = 0; j < nodes.size(); j++){
                if (i != j){
                    for (var node : nodes.get(i).getDirect()){
                        if (node.equals(nodes.get(j))){
                            matrix[i][j] = 1;
                            break;
                        }
                    }
                }
                else{
                    matrix[i][j] = 0;
                }
            }
        }
    }
    public void cycleSearch(int startIndex){
        for (int i = startIndex; i < nodes.size(); i++){
            bufNodes.add(i);
            for (int j = 0; j < nodes.size(); j++){
                if (matrix[i][j] == 1){
                    if (checkRepeat()){
                        addCycle();
                        bufNodes.removeLast();
                        return;
                    }
                    cycleSearch(j);
                }
            }
            if (!bufNodes.isEmpty()){
                bufNodes.removeLast();
                if (!bufNodes.isEmpty())
                    return;
            }
        }
    }
    private boolean checkRepeat(){
        for (int i = 0; i < bufNodes.size()-1; i++){
            for (int j = i + 1; j < bufNodes.size(); j++){
                if (Objects.equals(bufNodes.get(i), bufNodes.get(j))){
                    // write all repeats: System.out.println(bufNodes);
                    return true;
                }
            }
        }
        return false;
    }
    private void addCycle(){
        if (!cycleWasFound || checkRepeatInCycles()){
            cycleNodePatterns.add((ArrayList<Integer>) bufNodes.clone());
            cycleWasFound = true;
        }
    }
    private boolean checkRepeatInCycles(){
        boolean canAdd = false;
        for (Integer bufNode : bufNodes) {
            for (var cycleNode : cycleNodePatterns){
                if (cycleNode.contains(bufNode)){
                    break;
                }
                else canAdd = true;
                return canAdd;
            }
        }
        return canAdd;
    }
    public void writeMatrix(){
        System.out.printf("%3s", " ");
        for (Node node : nodes) {
            System.out.printf("%2s ", node.name);
        }
        System.out.println();

        for (int i = 0; i < nodes.size(); i++){
            System.out.printf("%2s ", nodes.get(i).name);
            for (int j = 0; j < nodes.size(); j++){
                System.out.printf("%2s ", matrix[i][j]);
            }
            System.out.println();
        }
    }
    public void writeCycles(){
        System.out.println();
        if (cycleNodePatterns.isEmpty()) {
            System.out.println("No cycles found\n");
        }
        for (var cycleNode : cycleNodePatterns){
            for (var node : cycleNode){
                System.out.print(nodes.get(node).name + " ");
            }
            System.out.println();
        }
    }
}
