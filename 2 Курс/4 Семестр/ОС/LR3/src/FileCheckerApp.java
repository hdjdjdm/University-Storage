import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.ArrayList;
import java.util.Objects;
import java.util.List;


public class FileCheckerApp extends JFrame implements ActionListener {
    private JButton checkButton, terminalButton;
    private JCheckBox checkBox;
    private JTextField diskField;
    private JTextArea logArea;

    public FileCheckerApp() {
        setTitle("File Checker");
        setMinimumSize(new Dimension(550, 300));
        this.setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        initComponents();

        setVisible(true);
    }

    private void initComponents() {
        JPanel panel = new JPanel();
        JLabel diskLabel = new JLabel("Select Disk:");
        diskField = new JTextField(10);
        checkButton = new JButton("Find");
        checkButton.addActionListener(this);

        JLabel checkLabel = new JLabel("Check:");
        checkBox = new JCheckBox();

        terminalButton = new JButton("Open Terminal");
        terminalButton.addActionListener(e -> openTerminal());

        logArea = new JTextArea(14, 36);
        logArea.setEditable(false);

        panel.add(diskLabel);
        panel.add(diskField);
        panel.add(checkButton);
        panel.add(terminalButton);
        panel.add(checkLabel);
        panel.add(checkBox);

        JScrollPane scrollPane = new JScrollPane(logArea);
        panel.add(scrollPane);

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

    private String getFileExtension(String fileName) {
        int dotIndex = fileName.lastIndexOf(".");
        if (dotIndex > 0 && dotIndex < fileName.length() - 1) {
            return fileName.substring(dotIndex + 1);
        }
        return null;
    }


    private void showMessage(String message) {
        JOptionPane.showMessageDialog(this, message);
    }

    private void openTerminal() {
        SwingUtilities.invokeLater(ConsoleGUI::new);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(FileCheckerApp::new);
    }
}
