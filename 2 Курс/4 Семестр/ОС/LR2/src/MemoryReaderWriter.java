import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class MemoryReaderWriter extends JFrame {
    private JTextField addressField;
    private JTextField dataField;
    private JTextField pidField;

    public MemoryReaderWriter() {
        initializeUI();
    }

    private void initializeUI() {
        setTitle("Memory Reader Writer");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(500, 200);
        setMinimumSize(new Dimension(500, 200));
        setLocationRelativeTo(null);

        JPanel mainPanel = new JPanel(new BorderLayout());

        JPanel inputPanel = new JPanel(new GridBagLayout());
        GridBagConstraints constraints = new GridBagConstraints();
        constraints.insets = new Insets(5, 5, 5, 5);

        JLabel addressLabel = new JLabel("Address:");
        addressField = new JTextField(20);
        JLabel dataLabel = new JLabel("Data:");
        dataField = new JTextField(20);
        JLabel pidLabel = new JLabel("PID:");
        pidField = new JTextField(10);

        constraints.gridx = 0;
        constraints.gridy = 0;
        inputPanel.add(addressLabel, constraints);

        constraints.gridy = 1;
        inputPanel.add(dataLabel, constraints);

        constraints.gridx = 1;
        constraints.gridy = 0;
        inputPanel.add(addressField, constraints);

        constraints.gridy = 1;
        inputPanel.add(dataField, constraints);

        constraints.gridx = 0;
        constraints.gridy = 2;
        inputPanel.add(pidLabel, constraints);

        constraints.gridx = 1;
        inputPanel.add(pidField, constraints);

        mainPanel.add(inputPanel, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel(new FlowLayout());
        JButton readButton = new JButton("Read");
        JButton writeButton = new JButton("Write");
        JButton openTerminalButton = new JButton("Open Terminal");
        JButton pageInfoButton = new JButton("Page Fault Info");

        readButton.addActionListener(e -> handleRead());
        writeButton.addActionListener(e -> handleWrite());
        openTerminalButton.addActionListener(e -> openTerminal());
        pageInfoButton.addActionListener(e -> showPageFaultInfo());

        buttonPanel.add(readButton);
        buttonPanel.add(writeButton);
        buttonPanel.add(openTerminalButton);
        buttonPanel.add(pageInfoButton);

        mainPanel.add(buttonPanel, BorderLayout.SOUTH);

        add(mainPanel);
    }

    private void handleRead() {
        String address = addressField.getText();
        int pid = Integer.parseInt(pidField.getText());
        MemoryTracer memory = new MemoryTracer(pid, address);
        String data = memory.read();
        dataField.setText(data);
    }

    private void handleWrite() {
        String address = addressField.getText();
        String data = dataField.getText();
        int pid = Integer.parseInt(pidField.getText());
        MemoryTracer memory = new MemoryTracer(pid, address);
        memory.write(data);
    }

    private void showPageFaultInfo() {
        JFrame pageFaultInfoFrame = new JFrame("Page Fault Info");
        pageFaultInfoFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        pageFaultInfoFrame.setSize(400, 200);
        pageFaultInfoFrame.setLocationRelativeTo(this);

        JTextArea pageFaultInfoText = new JTextArea();
        pageFaultInfoText.setEditable(false);

        try {
            Process process = Runtime.getRuntime().exec("sar -B 1 1");
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            pageFaultInfoText.setText(output.toString());
        } catch (IOException e) {
            e.printStackTrace();
            pageFaultInfoText.setText("Error executing sar command");
        }

        JScrollPane scrollPane = new JScrollPane(pageFaultInfoText);
        pageFaultInfoFrame.add(scrollPane);
        pageFaultInfoFrame.setVisible(true);
    }

    private void openTerminal() {
        ConsoleGUI terminalWindow = new ConsoleGUI();
        terminalWindow.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            MemoryReaderWriter memoryReaderWriter = new MemoryReaderWriter();
            memoryReaderWriter.setVisible(true);
        });
    }
}
