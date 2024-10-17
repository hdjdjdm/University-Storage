import java.util.ArrayList;
import java.util.List;

public class CommandsList {
    private static List<Command> commandList = new ArrayList<>();

    private void addCommands() {
        commandList.add(new Command("help / ?", "Shows this message", "help"));
        commandList.add(new Command("cls", "Clear terminal screen", "cls"));
        commandList.add(new Command("buffer", "Shows buffer size", "buffer"));
        commandList.add(new Command("find", "Searching for files and folders in directory", "find <path>"));
        commandList.add(new Command("tlist", "Shows thread's list", "tlist"));
        commandList.add(new Command("plist", "Shows process's list", "plist"));
        commandList.add(new Command("tinfo", "Shows info about current thread", "tinfo <name/id>"));
        commandList.add(new Command("pinfo", "Shows info about current process", "pinfo <name/id>"));
        commandList.add(new Command("tsetpriority", "Set priority for thread", "tsetpriority <name/id> <priority>"));
        commandList.add(new Command("psetpriority", "Set priority for process", "psetpriority <name/id> <priority>"));
        commandList.add(new Command("tstop", "Stop current thread", "tstop <name/id>"));
        commandList.add(new Command("pstop", "Stop current process", "pstop <name/id>"));
        commandList.add(new Command("create", "create producer's or consumer's thread", "create <producer/consumer> <priority>"));

    }

    public List<Command> getCommandList() {
        addCommands();
        return commandList;
    }
}