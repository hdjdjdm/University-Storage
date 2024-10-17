import javax.swing.JTextArea;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ArrayBlockingQueue;

public class TerminalCommands {
    public static void cls(JTextArea outputArea) {
        outputArea.setText("");
    }

    public static void buffer(int buffersize, JTextArea outputArea) {
        outputArea.append("Buffer size is " + buffersize);
    }

    public static void find(JTextArea outputArea, String directory) {
        outputArea.append("Searching for files and folders in directory: " + directory + "\n");

        File dir = new File(directory);

        if (!dir.exists()) {
            outputArea.append("Directory not found: " + directory + "\n");
            return;
        }

        if (!dir.isDirectory()) {
            outputArea.append("Not a directory: " + directory + "\n");
            return;
        }

        File[] filesAndFolders = dir.listFiles();

        if (filesAndFolders != null) {
            for (File file : filesAndFolders) {
                outputArea.append(file.getName() + "\n");
            }
        } else {
            outputArea.append("No files or folders found.\n");
        }
    }

    public static void tlist(JTextArea outputArea) {
        Map<Thread, StackTraceElement[]> allThreads = Thread.getAllStackTraces();

        outputArea.append("List of active threads:\n");
        for (Thread thread : allThreads.keySet()) {
            outputArea.append("Thread ID: " + thread.threadId() +
                    ", Name: " + thread.getName() +
                    ", State: " + thread.getState() + "\n");
        }
        outputArea.append("Total active threads: " + allThreads.size() + "\n");
    }

    public static void tsetpriority(JTextArea outputArea, String target, int priority) {
        try {
            int targetId = Integer.parseInt(target);
            Thread thread = findThreadById(targetId);
            if (thread != null) {
                thread.setPriority(priority);
                outputArea.append("Priority set successfully for thread with ID " + targetId + "\n");
            } else {
                outputArea.append("Thread with ID " + targetId + " not found.\n");
            }
        } catch (NumberFormatException e) {
            Thread thread = findThreadByName(target);
            if (thread != null) {
                thread.setPriority(priority);
                outputArea.append("Priority set successfully for thread " + target + "\n");
            } else {
                outputArea.append("Thread " + target + " not found.\n");
            }
        }
    }

    public static void createProducer(ArrayBlockingQueue<Integer> buffer, List<Producer> producers, JTextArea outputArea, int priority) {
        Producer newProducer = new Producer(buffer, outputArea);
        producers.add(newProducer);
        Thread producerThread = new Thread(newProducer, "Producer" + producers.size());
        producerThread.setPriority(priority);
        outputArea.append("Producer" + producers.size() + " created with priority " + priority + ".\n");
        producerThread.start();
        outputArea.setCaretPosition(outputArea.getDocument().getLength());
    }

    public static void createConsumer(ArrayBlockingQueue<Integer> buffer, List<Consumer> consumers, JTextArea outputArea, int priority){
        Consumer newConsumer = new Consumer(buffer, outputArea);
        consumers.add(newConsumer);
        Thread consumerThread = new Thread(newConsumer, "Consumer" + consumers.size());
        consumerThread.setPriority(priority);
        outputArea.append("Consumer" + consumers.size() + " created with priority " + priority + ".\n");
        consumerThread.start();
        outputArea.setCaretPosition(outputArea.getDocument().getLength());
    }

    public static boolean tstop(JTextArea outputArea, String target) {
        try {
            long targetId = Long.parseLong(target);
            Thread threadById = findThreadById((int) targetId);
            if (threadById != null) {
                threadById.interrupt();
                outputArea.append("Thread with ID " + targetId + " stopped.\n");
                return true;
            } else {
                outputArea.append("Thread with ID " + targetId + " not found.\n");
                return false;
            }
        } catch (NumberFormatException e) {
            Thread threadByName = findThreadByName(target);
            if (threadByName != null) {
                threadByName.interrupt();
                outputArea.append("Thread with name \"" + target + "\" stopped.\n");
                return true;
            } else {
                outputArea.append("Thread with name \"" + target + "\" not found.\n");
                return false;
            }
        }
    }

    public static void tinfo(JTextArea outputArea, String target) {
        try {
            long targetId = Long.parseLong(target);
            Thread thread = findThreadById((int) targetId);
            if (thread != null) {
                outputArea.append("Thread with ID " + targetId + ":\n");
                outputArea.append("Name: " + thread.getName() + "\n");
                outputArea.append("Priority: " + thread.getPriority() + "\n");
                outputArea.append("State: " + thread.getState() + "\n");
            } else {
                outputArea.append("Thread with ID " + targetId + " not found.\n");
            }
        } catch (NumberFormatException e) {
            Thread thread = findThreadByName(target);
            if (thread != null) {
                outputArea.append("Thread with name \"" + target + "\":\n");
                outputArea.append("ID: " + thread.threadId() + "\n");
                outputArea.append("Priority: " + thread.getPriority() + "\n");
                outputArea.append("State: " + thread.getState() + "\n");
            } else {
                outputArea.append("Thread with name \"" + target + "\" not found.\n");
            }
        }
    }

    private static Thread findThreadById(int id) {
        for (Thread thread : Thread.getAllStackTraces().keySet()) {
            if (thread.threadId() == id) {
                return thread;
            }
        }
        return null;
    }

    private static Thread findThreadByName(String name) {
        for (Thread thread : Thread.getAllStackTraces().keySet()) {
            if (thread.getName().equals(name)) {
                return thread;
            }
        }
        return null;
    }

    public static void plist(JTextArea outputArea) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("ps", "aux");
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                outputArea.append(line + "\n");
            }
            int exitCode = process.waitFor();
            outputArea.append("Process exited with code " + exitCode + "\n");
        } catch (IOException | InterruptedException e) {
            outputArea.append("Error listing processes.\n");
        }
    }

    public static void pinfo(JTextArea outputArea, String pid) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("ps", "-p", pid);
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                outputArea.append(line + "\n");
            }
            int exitCode = process.waitFor();
            outputArea.append("Process info command exited with code " + exitCode + "\n");
        } catch (IOException | InterruptedException e) {
            outputArea.append("Error getting process info.\n");
        }
    }

    public static void pstop(JTextArea outputArea, int pid) {
        try {
            ProcessBuilder pb = new ProcessBuilder("kill", "-9", Integer.toString(pid));
            Process process = pb.start();
            process.waitFor();
            outputArea.append("Process with PID " + pid + " stopped.\n");
        } catch (Exception e) {
            outputArea.append("Error stopping process: " + e.getMessage() + "\n");
        }
    }

    public static void ppause(JTextArea outputArea, int pid) {
        try {
            ProcessBuilder pb = new ProcessBuilder("kill", "-STOP", String.valueOf(pid));
            Process process = pb.start();
            process.waitFor();
            outputArea.append("Process with PID " + pid + " paused.\n");
        } catch (Exception e) {
            outputArea.append("Error pausing process: " + e.getMessage() + "\n");
        }
    }

    public static void presume(JTextArea outputArea, int pid) {
        try {
            ProcessBuilder pb = new ProcessBuilder("kill", "-CONT", String.valueOf(pid));
            Process process = pb.start();
            process.waitFor();
            outputArea.append("Process with PID " + pid + " resumed.\n");
        } catch (Exception e) {
            outputArea.append("Error resuming process: " + e.getMessage() + "\n");
        }
    }

    public static void commandslist(JTextArea outputArea) {
        CommandsList cm = new CommandsList();
        List<Command> commandslist = cm.getCommandList();
        for (Command command : commandslist){
            outputArea.append(command.getName() + ": " + command.getDescription() + ". Example: " + command.getExample() + "\n");
        }
    }

}
