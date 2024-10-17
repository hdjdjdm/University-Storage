package my;

import my.consolegui.ConsoleGUI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class FileCheckGUI extends JFrame implements ActionListener {
    public static User user;
    private JCheckBox checkBox;
    private JTextField diskField;
    private JTextArea logArea;

    public FileCheckGUI(User user) {
        FileCheckGUI.user = user;

        setTitle("File Checker");
        setMinimumSize(new Dimension(550, 320));
        this.setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        initComponents();

        setVisible(true);
    }

    private void initComponents() {
        JPanel panel = new JPanel();

        JPanel mainControls = new JPanel();
        JLabel diskLabel = new JLabel("Select Disk:");
        diskField = new JTextField(10);
        diskField.addActionListener(this);

        JButton checkButton = new JButton("Find");
        checkButton.addActionListener(this);

        JLabel checkLabel = new JLabel("Check:");
        checkBox = new JCheckBox();

        JButton terminalButton = new JButton("Open Terminal");
        terminalButton.addActionListener(e -> openTerminal());

        mainControls.add(diskLabel);
        mainControls.add(diskField);
        mainControls.add(checkButton);
        mainControls.add(terminalButton);
        mainControls.add(checkLabel);
        mainControls.add(checkBox);
        panel.add(mainControls);

        logArea = new JTextArea(14, 45);
        logArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(logArea);
        panel.add(scrollPane);

        JLabel loginLabel = new JLabel(user.getUserType() + ": " + user.getLogin());
        panel.add(loginLabel);

        setContentPane(panel);
    }

    public void actionPerformed(ActionEvent e) {
        if (!checkBox.isSelected()) {
            findDisc();
        } else {
            check();
        }
    }

    private void findDisc() {
        String disk = diskField.getText();
        if (disk.isEmpty()) {
            showMessage("Please enter a disk.");
            return;
        }

        File rootFolder = new File(disk);
        if (!rootFolder.exists() || !rootFolder.isDirectory()) {
            int choice = JOptionPane.showConfirmDialog(this, "Directory does not exist. Create it?", "Create Directory", JOptionPane.YES_NO_OPTION);
            if (choice == JOptionPane.YES_OPTION) {
                boolean created = rootFolder.mkdirs();
                if (!created) {
                    showMessage("Failed to create directory.");
                    return;
                }
            } else {
                return;
            }
        }
        displayFiles(rootFolder);
    }

    private void check() {
        if (checkBox.isSelected()) {
            File directory = new File(diskField.getText());
            if (!directory.exists() || !directory.isDirectory()) {
                showMessage("Please enter a valid directory.");
                checkBox.setSelected(false);
                return;
            }

            File[] subdirectories = directory.listFiles(File::isDirectory);
            if (subdirectories == null || subdirectories.length == 0) {
                showMessage("No subdirectories found in the directory.");
                return;
            }

            List<String> nonMatchingFiles = new ArrayList<>();

            for (File subdirectory : subdirectories) {
                String extension = subdirectory.getName();
                String[] files = subdirectory.list();
                if (files != null) {
                    for (String fileName : files) {
                        String[] parts = fileName.split("\\.");
                        if (parts.length > 1) {
                            String fileExtension = parts[parts.length - 1];
                            if (!Objects.equals(fileExtension, extension)) {
                                nonMatchingFiles.add(subdirectory.getAbsolutePath() + File.separator + fileName);
                            }
                        }
                    }
                }
            }

            if (nonMatchingFiles.isEmpty()) {
                showMessage("All files are in the right folders");
            } else {
                logArea.setText("");
                for (String file : nonMatchingFiles) {
                    logArea.append(file + "\n");
                }
                showMessage("Not all files are in the right folders\n");
            }
        }
    }


    private void displayFiles(File directory) {
        logArea.setText("");
        File[] files = directory.listFiles();
        if (files != null) {
            for (File file : files) {
                logArea.append(file.getName() + "\n");
            }
        }
    }

    private void showMessage(String message) {
        JOptionPane.showMessageDialog(this, message);
    }
    private void openTerminal() {
        SwingUtilities.invokeLater(ConsoleGUI::new);
    }
}
