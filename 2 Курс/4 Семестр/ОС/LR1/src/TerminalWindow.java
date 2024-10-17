import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.List;
import java.util.concurrent.ArrayBlockingQueue;

public class TerminalWindow extends JFrame {
    private ArrayBlockingQueue<Integer> buffer;
    private int buffersize;
    private List<Producer> producers;
    private List<Consumer> consumers;
    private JTextArea outputAreaMain;

    public TerminalWindow(ArrayBlockingQueue<Integer> buffer, List<Producer> producers, List<Consumer> consumers, JTextArea outputAreaMain, int buffersize) {
        this.buffer = buffer;
        this.producers = producers;
        this.consumers = consumers;
        this.outputAreaMain = outputAreaMain;
        this.buffersize = buffersize;

        setTitle("Terminal");
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setSize(500, 400);
        setMinimumSize(new Dimension(500, 400));
        setLocationRelativeTo(null);

        JPanel panel = new JPanel(new BorderLayout());

        JTextArea outputArea = new JTextArea(10, 30);
        outputArea.setEditable(false);
        JTextField commandField = new JTextField(20);
        JButton executeButton = new JButton("Execute");

        JPanel commandPanel = new JPanel(new BorderLayout());
        commandPanel.add(commandField, BorderLayout.CENTER);
        commandPanel.add(executeButton, BorderLayout.EAST);

        panel.add(new JScrollPane(outputArea), BorderLayout.CENTER);
        panel.add(commandPanel, BorderLayout.SOUTH);

        getContentPane().add(panel);

        commandField.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                executeButton.doClick();
            }
        });

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowOpened(WindowEvent e) {
                commandField.requestFocusInWindow();
            }
        });
        executeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String command = commandField.getText().trim();
                outputArea.append(command + "\n");
                commandField.setText("");
                if (command.isEmpty()) {
                    outputArea.append("Please enter a command.\n");
                    return;
                }

                String[] parts = command.split(" ", 2);
                String cmd = parts[0];
                String arg = parts.length > 1 ? parts[1] : null;

                switch (cmd) {
                    case "help":
                    case "?":
                        TerminalCommands.commandslist(outputArea);
                        break;
                    case "cls":
                        TerminalCommands.cls(outputArea);
                        break;
                    case "buffer":
                        TerminalCommands.buffer(buffersize, outputArea);
                        break;
                    case "find":
                        if (arg != null) {
                            TerminalCommands.find(outputArea, arg);
                        } else {
                            outputArea.append("Please specify a directory for the find command.\nExample: find <path>\n");
                        }
                        break;
                    case "tlist":
                        TerminalCommands.tlist(outputArea);
                        break;
                    case "tsetpriority":
                        if (arg != null) {
                            String[] args = arg.split(" ", 2);
                            if (args.length == 2) {
                                String target = args[0];
                                int priority;
                                try {
                                    priority = Integer.parseInt(args[1]);
                                    if (priority < 0 || priority > 10) {
                                        outputArea.append("Priority value must be between 0 and 10.\n");
                                        break;
                                    }
                                    TerminalCommands.tsetpriority(outputArea, target, priority);
                                } catch (NumberFormatException n) {
                                    outputArea.append("Invalid priority value.\n");
                                }
                            } else {
                                outputArea.append("Invalid arguments for tsetpriority command.\n");
                            }
                        } else {
                            outputArea.append("Please specify target and priority for the tsetpriority command.\nExample: tsetpriority <name/id> <priority>\n");
                        }
                        break;
                    case "create":
                        if (arg != null) {
                            String[] args = arg.split(" ", 2);
                            if (args.length >= 1 && args.length <= 2) {
                                String type = args[0];
                                int priority = 5;
                                if (args.length == 2) {
                                    try {
                                        priority = Integer.parseInt(args[1]);
                                        if (priority < 0 || priority > 10) {
                                            outputArea.append("Priority value must be between 0 and 10. Using default priority.\n");
                                            priority = 5;
                                        }
                                    } catch (NumberFormatException n) {
                                        outputArea.append("Invalid priority value. Using default priority.\n");
                                    }
                                }
                                if ("producer".equals(type)) {
                                    TerminalCommands.createProducer(buffer, producers, outputAreaMain, priority);
                                    outputArea.append("Producer" + producers.size() + " created with priority " + priority + ".\n");
                                } else if ("consumer".equals(type)) {
                                    TerminalCommands.createConsumer(buffer, consumers, outputAreaMain, priority);
                                    outputArea.append("Consumer" + consumers.size() + " created with priority " + priority + ".\n");

                                } else {
                                    outputArea.append("Invalid type. Please specify either 'producer' or 'consumer'.\n");
                                }
                            } else {
                                outputArea.append("Invalid arguments for create command.\n");
                            }
                        } else {
                            outputArea.append("Please specify type for the create command.\nExample: create <producer/consumer> <priority>\n");
                        }
                        break;
                    case "tstop":
                        if (arg != null) {
                            if (TerminalCommands.tstop(outputArea, arg)) {
                                outputAreaMain.append("Thread " + arg + " has been stopped.\n");
                            }
                        } else {
                            outputArea.append("Please specify the thread name or ID to stop.\nExample: tstop <name/id>\n");
                        }
                        break;
                    case "tinfo":
                        if (arg != null) {
                            TerminalCommands.tinfo(outputArea, arg);
                        } else {
                            outputArea.append("Please specify the thread name or ID to find.\nExample: tinfo <name/id>\n");
                        }
                        break;
                    case "plist":
                        TerminalCommands.plist(outputArea);
                        break;
                    case "pinfo":
                        if (arg != null) {
                            TerminalCommands.pinfo(outputArea, arg);
                        } else {
                            outputArea.append("Please specify the process PID.\nExample: pinfo <PID>");
                        }
                        break;
                    case "pstop":
                        if (arg != null) {
                            try {
                                int pid = Integer.parseInt(arg);
                                TerminalCommands.pstop(outputArea, pid);
                            } catch (NumberFormatException u) {
                                outputArea.append("Invalid PID. Please specify a valid process ID.\n");
                            }
                        } else {
                            outputArea.append("Please specify the process ID to stop.\n");
                        }
                        break;
                    case "ppause":
                        if (arg != null) {
                            try {
                                int pid = Integer.parseInt(arg);
                                TerminalCommands.ppause(outputArea, pid);
                            } catch (NumberFormatException n) {
                                outputArea.append("Invalid PID.\n");
                            }
                        } else {
                            outputArea.append("Please specify the PID of the process to pause.\n");
                        }
                        break;
                    case "presume":
                        if (arg != null) {
                            try {
                                int pid = Integer.parseInt(arg);
                                TerminalCommands.presume(outputArea, pid);
                            } catch (NumberFormatException n) {
                                outputArea.append("Invalid PID.\n");
                            }
                        } else {
                            outputArea.append("Please specify the PID of the process to resume.\n");
                        }
                        break;
                    default:
                        outputArea.append("Unknown command: " + cmd + "\nType 'help' to see command's list");
                }
                outputArea.setCaretPosition(outputArea.getDocument().getLength());
            }
        });

        setVisible(true);
    }
}
