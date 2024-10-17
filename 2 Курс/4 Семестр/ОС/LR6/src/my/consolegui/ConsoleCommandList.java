package my.consolegui;

import javax.swing.*;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.stream.Stream;
import my.FileCheckGUI;


public class ConsoleCommandList {
    private static final Logger logger = Logger.getLogger(ConsoleCommandList.class.getName());
    private static ConsoleCommandList instance;
    private final JTextArea textArea;
    private final ArrayList<ConsoleCommand> commands = new ArrayList<>();
    private ConsoleCommandList(JTextArea textArea){
        this.textArea = textArea;

        ConsoleLog.configureLogging();
        logger.addHandler(ConsoleLog.getFileHandler());
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

        commands.add(new ConsoleCommand("find", "Find all files in directory", "find [dir]") {
            @Override
            public void runCommand(String[] str){
                if (str.length != 2){
                    textArea.append("Incorrect input arguments\n");
                    return;
                }

                File dir = new File(str[1]);
                if (!dir.isDirectory()) {
                    textArea.append("Not a directory: " + str[1] + "\n");
                    return;
                }
                if (!dir.exists()) {
                    textArea.append("Directory '" + str[1] + "' not found\n");
                    return;
                }

                File[] filesAndFolders = dir.listFiles();
                if (filesAndFolders != null) {
                    for (File file : filesAndFolders) {
                        textArea.append(file.getName() + "\n");
                    }
                } else {
                    textArea.append("No files or folders found.\n");
                }
            }
        });

        commands.add(new ConsoleCommand("exists", "Check if file or directory exists", "exists [path]") {
            @Override
            public void runCommand(String[] str) {
                if (str.length != 2) {
                    textArea.append("Incorrect input arguments\n");
                    return;
                }

                String path = str[1];
                File fileOrDir = new File(path);
                if (fileOrDir.exists()) {
                    textArea.append("File or directory '" + path + "' exists\n");
                } else {
                    textArea.append("File or directory '" + path + "' does not exist\n");
                }
            }
        });

        commands.add(new ConsoleCommand("size", "Display size of file", "size [dir]") {
           @Override
           public void runCommand(String[] str) {
               if (str.length != 2){
                   textArea.append("Incorrect input arguments\n");
                   return;
               }

               File dir = new File(str[1]);
               if (!dir.exists()) {
                   textArea.append("Directory '" + str[1] + "' not found\n");
                   return;
               }
               textArea.append(dir.length() + "\n");
           }
        });

        commands.add(new ConsoleCommand("delete", "Delete file or directory", "delete [dir]") {
            @Override
            public void runCommand(String[] str) {
                if (str.length < 2 || str.length > 3) {
                    textArea.append("Incorrect input arguments\n");
                    return;
                }

                boolean recursive = false;
                String targetPath;
                if (str.length == 3) {
                    if (!str[1].equals("-R")) {
                        textArea.append("Invalid flag\n");
                        return;
                    }
                    recursive = true;
                    targetPath = str[2];
                } else {
                    targetPath = str[1];
                }

                File fileOrDir = new File(targetPath);
                if (!fileOrDir.exists()) {
                    textArea.append("File or directory '" + targetPath + "' not found\n");
                    return;
                }

                if (recursive) {
                    deleteDirectory(fileOrDir);
                } else {
                    if (fileOrDir.delete()) {
                        logger.log(Level.INFO, FileCheckGUI.user.getLogin() + ": delete " + fileOrDir);
                        textArea.append(fileOrDir + " deleted\n");
                    } else {
                        textArea.append("Failed to delete " + fileOrDir + " If you need to delete directory, try 'delete -R [dir]'\n");
                    }
                }
            }

            private void deleteDirectory(File dir) {
                File[] files = dir.listFiles();
                if (files != null) {
                    for (File file : files) {
                        if (file.isDirectory()) {
                            deleteDirectory(file);
                        } else {
                            file.delete();
                        }
                    }
                }
                if (dir.delete()) {
                    logger.log(Level.INFO, FileCheckGUI.user.getLogin() + ": delete " + dir);
                    textArea.append(dir + " deleted\n");
                } else {
                    logger.log(Level.INFO, FileCheckGUI.user.getLogin() + ": try delete " + dir + ". Unsuccessfully");
                    textArea.append("Failed to delete " + dir + "\n");
                }
            }
        });

        commands.add(new ConsoleCommand("create", "Create file or directory", "create [file|dir] [name] [path]") {
            @Override
            public void runCommand(String[] str) {
                if (str.length < 3 || str.length > 4) {
                    textArea.append("Incorrect input arguments\n");
                    return;
                }

                String type = str[1].toLowerCase();
                String name = str[2];
                String path;

                if (str.length == 4) {
                    path = str[3];
                } else {
                    path = System.getProperty("user.dir");
                }

                File targetDirectory = new File(path);
                if (!targetDirectory.exists() || !targetDirectory.isDirectory()) {
                    textArea.append("Directory '" + path + "' not found\n");
                    return;
                }

                if (type.equals("file")) {
                    createFile(targetDirectory, name);
                } else if (type.equals("dir")) {
                    createDirectory(targetDirectory, name);
                } else {
                    textArea.append("Invalid type. Use 'file' or 'dir'\n");
                }
            }

            private void createFile(File directory, String name) {
                try {
                    File file = new File(directory, name);
                    if (file.createNewFile()) {
                        logger.log(Level.INFO, FileCheckGUI.user.getLogin() + ": create file " + name + " in directory " + directory.getAbsolutePath());
                        textArea.append("File '" + name + "' created in directory '" + directory.getAbsolutePath() + "'\n");
                    } else {
                        textArea.append("File '" + name + "' already exists in directory '" + directory.getAbsolutePath() + "'\n");
                    }
                } catch (IOException e) {
                    logger.log(Level.SEVERE, FileCheckGUI.user.getLogin() + ": Error creating file '" + name + "'", e);
                    textArea.append("Error creating file '" + name + "': " + e.getMessage() + "\n");
                }
            }


            private void createDirectory(File directory, String name) {
                File newDirectory = new File(directory, name);
                if (newDirectory.mkdir()) {
                    logger.log(Level.INFO, FileCheckGUI.user.getLogin() + ": create directory " + name + " in directory " + directory.getAbsolutePath());
                    textArea.append("Directory '" + name + "' created in directory '" + directory.getAbsolutePath() + "'\n");
                } else {
                    logger.log(Level.SEVERE, FileCheckGUI.user.getLogin() + ": Error creating directory " + name + " in directory " + directory);
                    textArea.append("Failed to create directory '" + name + "' in directory '" + directory.getAbsolutePath() + "'\n");
                }
            }
        });

        commands.add(new ConsoleCommand("rename", "Rename file or directory. Admin ONLY!", "rename [oldName] [newName] [path]") {
            @Override
            public void runCommand(String[] str) {
                if (!FileCheckGUI.user.isAdmin()) {
                    logger.log(Level.INFO, FileCheckGUI.user.getLogin() + ": try rename " + ". Unsuccessfully. No enough rules");
                    textArea.append("No rules for this");
                    return;
                }

                if (str.length < 3 || str.length > 4) {
                    textArea.append("Incorrect input arguments\n");
                    return;
                }

                String oldName = str[1];
                String newName = str[2];
                String path;

                if (str.length == 4) {
                    path = str[3];
                } else {
                    path = System.getProperty("user.dir");
                }

                File targetDirectory = new File(path);
                if (!targetDirectory.exists() || !targetDirectory.isDirectory()) {
                    textArea.append("Directory '" + path + "' not found\n");
                    return;
                }

                File oldFileOrDir = new File(targetDirectory, oldName);
                if (!oldFileOrDir.exists()) {
                    textArea.append("File or directory '" + oldName + "' not found in directory '" + path + "'\n");
                    return;
                }

                File newFileOrDir = new File(targetDirectory, newName);
                if (newFileOrDir.exists()) {
                    textArea.append("File or directory with name '" + newName + "' already exists in directory '" + path + "'\n");
                    return;
                }

                if (oldFileOrDir.renameTo(newFileOrDir)) {
                    logger.log(Level.INFO, FileCheckGUI.user.getLogin() + ": rename " + oldName  + " to " + newName);
                    textArea.append("Successfully renamed '" + oldName + "' to '" + newName + "' in directory '" + path + "'\n");
                } else {
                    logger.log(Level.SEVERE, FileCheckGUI.user.getLogin() + ": try rename " + oldName + ". Unsuccessfully");
                    textArea.append("Failed to rename '" + oldName + "' to '" + newName + "' in directory '" + path + "'\n");
                }
            }
        });

        commands.add(new ConsoleCommand("move", "Move file or directory", "move [source] [destination]") {
            @Override
            public void runCommand(String[] str) {
                if (str.length != 3) {
                    textArea.append("Incorrect input arguments\n");
                    return;
                }

                String sourcePath = str[1];
                String destinationPath = str[2];

                File sourceFileOrDir = new File(sourcePath);
                if (!sourceFileOrDir.exists()) {
                    textArea.append("Source file or directory '" + sourcePath + "' not found\n");
                    return;
                }

                File destinationDir = new File(destinationPath);
                if (!destinationDir.exists() || !destinationDir.isDirectory()) {
                    textArea.append("Destination directory '" + destinationPath + "' not found\n");
                    return;
                }

                File destinationFileOrDir = new File(destinationDir, sourceFileOrDir.getName());
                if (destinationFileOrDir.exists()) {
                    textArea.append("File or directory with name '" + sourceFileOrDir.getName() + "' already exists in destination directory\n");
                    return;
                }

                if (sourceFileOrDir.renameTo(destinationFileOrDir)) {
                    logger.log(Level.INFO, FileCheckGUI.user.getLogin() + ": move " + sourcePath + " to " + destinationPath);
                    textArea.append("Successfully moved '" + sourcePath + "' to '" + destinationPath + "'\n");
                } else {
                    logger.log(Level.SEVERE, FileCheckGUI.user.getLogin() + ": try move " + sourcePath + " to " + destinationPath + ". Unsuccessful");
                    textArea.append("Failed to move '" + sourcePath + "' to '" + destinationPath + "'\n");
                }
            }
        });

        commands.add(new ConsoleCommand("copy", "Copy file or directory", "copy [source] [destination]") {
            @Override
            public void runCommand(String[] str) {
                if (str.length != 3) {
                    textArea.append("Incorrect input arguments\n");
                    return;
                }

                String sourcePath = str[1];
                String destinationPath = str[2];

                File sourceFileOrDir = new File(sourcePath);
                if (!sourceFileOrDir.exists()) {
                    textArea.append("Source file or directory '" + sourcePath + "' not found\n");
                    return;
                }

                File destinationDir = new File(destinationPath);
                if (!destinationDir.exists() || !destinationDir.isDirectory()) {
                    textArea.append("Destination directory '" + destinationPath + "' not found\n");
                    return;
                }

                File destinationFileOrDir = new File(destinationDir, sourceFileOrDir.getName());
                if (destinationFileOrDir.exists()) {
                    textArea.append("File or directory with name '" + sourceFileOrDir.getName() + "' already exists in destination directory\n");
                    return;
                }

                try {
                    if (sourceFileOrDir.isDirectory()) {
                        copyDirectory(sourceFileOrDir, destinationFileOrDir);
                    } else {
                        copyFile(sourceFileOrDir, destinationFileOrDir);
                    }
                    logger.log(Level.INFO, FileCheckGUI.user.getLogin() + ": Successfully copied '" + sourcePath + "' to '" + destinationPath + "'");
                    textArea.append("Successfully copied '" + sourcePath + "' to '" + destinationPath + "'\n");
                } catch (IOException e) {
                    logger.log(Level.SEVERE, FileCheckGUI.user.getLogin() + ": Failed to copy '" + sourcePath + "' to '" + destinationPath + "'", e);
                    textArea.append("Failed to copy '" + sourcePath + "' to '" + destinationPath + "': " + e.getMessage() + "\n");
                }
            }

            private void copyFile(File sourceFile, File destinationFile) throws IOException {
                Files.copy(sourceFile.toPath(), destinationFile.toPath());
            }

            private void copyDirectory(File sourceDir, File destinationDir) throws IOException {
                try (Stream<Path> paths = Files.walk(sourceDir.toPath())) {
                    paths.forEach(sourcePath -> {
                        try {
                            Path destinationPath = destinationDir.toPath().resolve(sourceDir.toPath().relativize(sourcePath));
                            Files.copy(sourcePath, destinationPath);
                        } catch (IOException e) {
                            throw new RuntimeException(e);
                        }
                    });
                }
            }

        });


        commands.add(new ConsoleCommand("read", "Read contents of a file", "read [path]") {
            @Override
            public void runCommand(String[] str) {
                if (str.length != 2) {
                    textArea.append("Incorrect input arguments\n");
                    return;
                }

                String filePath = str[1];
                try {
                    String fileContent = readFile(filePath);
                    logger.log(Level.INFO, FileCheckGUI.user.getLogin() + ": Read contents of file '" + filePath + "'");
                    textArea.append("File contents:\n" + fileContent + "\n");
                } catch (IOException e) {
                    logger.log(Level.SEVERE, FileCheckGUI.user.getLogin() + ": Error reading file '" + filePath + "'", e);
                    textArea.append("Error reading file: " + e.getMessage() + "\n");
                }
            }

            private String readFile(String filePath) throws IOException {
                File file = new File(filePath);
                if (!file.exists() || !file.isFile()) {
                    throw new IOException("File not found: " + filePath);
                }
                StringBuilder content = new StringBuilder();
                try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
                    String line;
                    while ((line = reader.readLine()) != null) {
                        content.append(line).append("\n");
                    }
                }
                return content.toString();
            }
        });

        commands.add(new ConsoleCommand("write", "Write content to a file", "write [path] [content]") {
            @Override
            public void runCommand(String[] str) {
                if (str.length < 3) {
                    textArea.append("Incorrect input arguments\n");
                    return;
                }

                String filePath = str[1];
                StringBuilder content = new StringBuilder();
                for (int i = 2; i < str.length; i++) {
                    content.append(str[i]).append(" ");
                }
                try {
                    writeFile(filePath, content.toString().trim());
                    logger.log(Level.INFO, FileCheckGUI.user.getLogin() + ": Wrote content to file '" + filePath + "'");
                    textArea.append("Content written to file successfully\n");
                } catch (IOException e) {
                    logger.log(Level.SEVERE, FileCheckGUI.user.getLogin() + ": Error writing to file '" + filePath + "'", e);
                    textArea.append("Error writing to file: " + e.getMessage() + "\n");
                }
            }

            private void writeFile(String filePath, String content) throws IOException {
                File file = new File(filePath);
                if (!file.exists()) {
                    file.createNewFile();
                }
                try (BufferedWriter writer = new BufferedWriter(new FileWriter(file))) {
                    writer.write(content);
                }
            }
        });

    }
}
