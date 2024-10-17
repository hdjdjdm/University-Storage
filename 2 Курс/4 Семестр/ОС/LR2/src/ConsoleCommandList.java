import com.sun.management.OperatingSystemMXBean;
import javax.swing.JTextArea;
import java.io.*;
import java.util.ArrayList;
import java.lang.management.ManagementFactory;

public class ConsoleCommandList {
    private static ConsoleCommandList instance;
    private final JTextArea textArea;
    private final ArrayList<ConsoleCommand> commands = new ArrayList<>();
    OperatingSystemMXBean osBean = (OperatingSystemMXBean) ManagementFactory.getOperatingSystemMXBean();

    private ConsoleCommandList(JTextArea textArea){
        this.textArea = textArea;
        addCommands();
    }
    public static ConsoleCommandList getInstance(JTextArea textArea){
        if (instance == null)
            instance = new ConsoleCommandList(textArea);
        return instance;
    }
    public ArrayList<ConsoleCommand> getCommands(){
        return commands;
    }
    private void addCommands(){
        commands.add(new ConsoleCommand("cls", "Clear console", "cls") {
            @Override
            public void runCommand(String[] str){
                textArea.setText("");
            }
        });

        commands.add(new ConsoleCommand("help", "Display help", "help [command]") {
            @Override
            public void runCommand(String[] str) {
                if (str.length == 1) {
                    for (ConsoleCommand command : commands) {
                        textArea.append(String.format("%-8s\t %-38s\tsignature: %-16s\n", command.getName(), command.getDescription(), command.getExample()));
                    }
                } else if (str.length == 2) {
                    String commandName = str[1];
                    boolean found = false;
                    for (ConsoleCommand command : commands) {
                        if (command.getName().equals(commandName)) {
                            textArea.append(command.getDescription() + "\n");
                            textArea.append("Usage: " + command.getExample() + "\n");
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        textArea.append("Command '" + commandName + "' not found\n");
                    }
                } else {
                    textArea.append("Incorrect input arguments\n");
                }
            }
        });

        commands.add(new ConsoleCommand("read", "Read data from memory", "read [pid] [address]") {
            @Override
            public void runCommand(String[] str) {
                if (str.length == 3) {
                    try {
                        int pid = Integer.parseInt(str[1]);
                        String address = str[2];
                        MemoryTracer memory = new MemoryTracer(pid, address);
                        String data = memory.read();
                        textArea.append("Data read from memory: " + data + "\n");
                    } catch (NumberFormatException e) {
                        textArea.append("Invalid pid format\n");
                    } catch (Exception e) {
                        textArea.append("Failed to read data from memory: " + e.getMessage() + "\n");
                    }
                } else {
                    textArea.append("Incorrect input arguments\n");
                }
            }
        });


        commands.add(new ConsoleCommand("write", "Write data to memory", "write [pid] [address] [data]") {
            @Override
            public void runCommand(String[] str) {
                if (str.length == 4) {
                    try {
                        int pid = Integer.parseInt(str[1]);
                        String address = str[2];
                        String data = str[3];
                        MemoryTracer memory = new MemoryTracer(pid, address);
                        memory.write(data);
                        textArea.append("Data written to memory successfully\n");
                    } catch (NumberFormatException e) {
                        textArea.append("Invalid pid format\n");
                    } catch (Exception e) {
                        textArea.append("Failed to write data to memory: " + e.getMessage() + "\n");
                    }
                } else {
                    textArea.append("Incorrect input arguments\n");
                }
            }
        });

        commands.add(new ConsoleCommand("pagefault", "Display page fault information", "pagefault") {
            @Override
            public void runCommand(String[] str) {
                try {
                    Process process = Runtime.getRuntime().exec("sar -B 1 1");
                    BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                    StringBuilder output = new StringBuilder();
                    String line;
                    while ((line = reader.readLine()) != null) {
                        output.append(line).append("\n");
                    }
                    textArea.append(output + "\n");
                } catch (IOException e) {
                    e.printStackTrace();
                    textArea.append("Error executing sar command\n");
                }
            }
        });

        commands.add(new ConsoleCommand("pmap", "Display process memory map", "pmap [pid]") {
            @Override
            public void runCommand(String[] str) {
                if (str.length == 2) {
                    try {
                        String pid = str[1];
                        Process process = Runtime.getRuntime().exec("pmap " + pid);
                        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                        StringBuilder output = new StringBuilder();
                        String line;
                        while ((line = reader.readLine()) != null) {
                            output.append(line).append("\n");
                        }
                        textArea.append(output + "\n");
                    } catch (IOException e) {
                        e.printStackTrace();
                        textArea.append("Error executing pmap command\n");
                    }
                } else {
                    textArea.append("Incorrect input arguments\n");
                }
            }
        });

        commands.add(new ConsoleCommand("vmstat", "Display virtual memory statistics", "vmstat") {
            @Override
            public void runCommand(String[] str) {
                if (str.length == 1) {
                    try {
                        Process process = Runtime.getRuntime().exec("vmstat");
                        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                        StringBuilder output = new StringBuilder();
                        String line;
                        while ((line = reader.readLine()) != null) {
                            output.append(line).append("\n");
                        }
                        textArea.append(output + "\n");
                    } catch (IOException e) {
                        e.printStackTrace();
                        textArea.append("Error executing vmstat command\n");
                    }
                } else {
                    textArea.append("Incorrect input arguments\n");
                }
            }
        });

        commands.add(new ConsoleCommand("top", "Display system processes", "top") {
            @Override
            public void runCommand(String[] str) {
                if (str.length == 1) {
                    try {
                        Process process = Runtime.getRuntime().exec("top");
                        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                        StringBuilder output = new StringBuilder();
                        String line;
                        while ((line = reader.readLine()) != null) {
                            output.append(line).append("\n");
                        }
                        textArea.append(output + "\n");
                    } catch (IOException e) {
                        e.printStackTrace();
                        textArea.append("Error executing top command\n");
                    }
                } else {
                    textArea.append("Incorrect input arguments\n");
                }
            }
        });

        commands.add(new ConsoleCommand("ipcs", "Display information about IPC facilities", "ipcs -m") {
            @Override
            public void runCommand(String[] str) {
                if (str.length == 2 && str[1].equals("-m")) {
                    try {
                        Process process = Runtime.getRuntime().exec("ipcs -m");
                        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                        StringBuilder output = new StringBuilder();
                        String line;
                        while ((line = reader.readLine()) != null) {
                            output.append(line).append("\n");
                        }
                        textArea.append(output + "\n");
                    } catch (IOException e) {
                        e.printStackTrace();
                        textArea.append("Error executing ipcs -m command\n");
                    }
                } else {
                    textArea.append("Incorrect input arguments. Usage: ipcs -m\n");
                }
            }
        });

        commands.add(new ConsoleCommand("freemem", "Display the amount of free physical memory", "freemem") {
            @Override
            public void runCommand(String[] str) {
                long freeMemory = osBean.getFreePhysicalMemorySize();
                textArea.append("Free Physical Memory: " + freeMemory + " bytes\n");
            }
        });

        commands.add(new ConsoleCommand("totalmem", "Display the amount of physical memory", "totalmem") {
            @Override
            public void runCommand(String[] str) {
                long totalMemory = osBean.getTotalPhysicalMemorySize();
                textArea.append("Total Physical Memory: " + totalMemory + " bytes\n");
            }
        });

        commands.add(new ConsoleCommand("gc", "Explicitly run garbage collection", "gc") {
            @Override
            public void runCommand(String[] str) {
                System.gc();
                textArea.append("Garbage collection executed\n");
            }
        });

        commands.add(new ConsoleCommand("swap", "Display swap usage summary", "swap") {
            @Override
            public void runCommand(String[] str) {
                try {
                    Process process = Runtime.getRuntime().exec("swapon --show");
                    BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                    StringBuilder output = new StringBuilder();
                    String line;
                    while ((line = reader.readLine()) != null) {
                        output.append(line).append("\n");
                    }
                    textArea.append(output + "\n");
                } catch (IOException e) {
                    e.printStackTrace();
                    textArea.append("Error executing swap command\n");
                }
            }
        });

    }
}
