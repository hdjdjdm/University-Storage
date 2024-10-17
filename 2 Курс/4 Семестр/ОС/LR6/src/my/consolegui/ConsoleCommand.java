package my.consolegui;

import my.User;

public class ConsoleCommand implements ICommand {
    private final String name;
    private final String description;
    private final String example;
    public ConsoleCommand(String name, String description, String example){
        this.name = name;
        this.description = description;
        this.example = example;
    }
    public String getName(){
        return name;
    }
    public String getDescription(){
        return description;
    }
    public String getExample(){
        return example;
    }

    @Override
    public void runCommand(String[] str) {}
}
