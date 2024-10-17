import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

public class InputOutputControlGUI {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(InputOutputControlGUI::createAndShowGUI);
    }

    private static void createAndShowGUI() {
        JFrame frame = new JFrame("Input Output Control");
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JButton moveMouseButton = new JButton("Move Mouse");
        JButton pressKeyButton = new JButton("Press Key");
        JButton systemUptimeButton = new JButton("System Uptime");
        JButton soundDevicesButton = new JButton("Sound Devices");

        JTextArea outputTextArea = new JTextArea(10, 40);
        outputTextArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(outputTextArea);

        moveMouseButton.addActionListener(e -> moveMouse());
        pressKeyButton.addActionListener(e -> pressKey());
        systemUptimeButton.addActionListener(e -> showSystemUptime(outputTextArea));
        soundDevicesButton.addActionListener(e -> showSoundDevices(outputTextArea));

        JPanel buttonsPanel = new JPanel();
        buttonsPanel.add(moveMouseButton);
        buttonsPanel.add(pressKeyButton);
        buttonsPanel.add(systemUptimeButton);
        buttonsPanel.add(soundDevicesButton);

        JPanel contentPanel = new JPanel(new BorderLayout());
        contentPanel.add(buttonsPanel, BorderLayout.NORTH);
        contentPanel.add(scrollPane, BorderLayout.CENTER);

        frame.getContentPane().add(contentPanel);
        frame.pack();
        frame.setVisible(true);
    }

    private static void moveMouse() {
        try {
            Robot robot = new Robot();
            Point startPoint = MouseInfo.getPointerInfo().getLocation();
            robot.mouseMove(startPoint.x, startPoint.y);
            for (int i = 0; i < 100; i++) {
                startPoint = MouseInfo.getPointerInfo().getLocation();
                robot.mouseMove(startPoint.x + 10, startPoint.y + 10);
                Thread.sleep(100);
            }
        } catch (AWTException | InterruptedException ex) {
            ex.printStackTrace();
        }
    }

    private static void pressKey() {
        try {
            Robot robot = new Robot();
            robot.keyPress(KeyEvent.VK_A);
            Thread.sleep(1000);
            robot.keyRelease(KeyEvent.VK_A);
        } catch (AWTException | InterruptedException ex) {
            ex.printStackTrace();
        }
    }

    private static void showSystemUptime(JTextArea outputTextArea) {
        String uptimeInfo = executeCommand("uptime");
        outputTextArea.setText(uptimeInfo);
    }

    private static void showSoundDevices(JTextArea outputTextArea) {
        String soundDevicesInfo = executeCommand("aplay -l");
        outputTextArea.setText(soundDevicesInfo);
    }

    private static String executeCommand(String command) {
        StringBuilder output = new StringBuilder();
        try {
            Process process = new ProcessBuilder().command("bash", "-c", command).start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            process.waitFor();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
        return output.toString();
    }
}
