public class Command {
    private String name;
    private String description;
    private String example;

    public Command(String name, String description, String example) {
        this.name = name;
        this.description = description;
        this.example = example;
    }

    public String getName() {
        return name;
    }

    public String getDescription() {
        return description;
    }

    public String getExample() {
        return example;
    }
}
