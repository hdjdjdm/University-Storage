package my.consolegui;

import my.FileCheckGUI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

public class ConsoleGUI extends JFrame implements ActionListener {
    private static final Logger logger = Logger.getLogger(ConsoleGUI.class.getName());

    private JPanel panel;
    private JTextField textField;
    private static JTextArea textArea = new JTextArea(10, 30);
    private ArrayList<ConsoleCommand> commands = new ArrayList<>();
    private String[] commandFetch;

    public ConsoleGUI(){
        ConsoleLog.configureLogging();
        logger.addHandler(ConsoleLog.getFileHandler());

        setTitle("Terminal");
        setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
        setMinimumSize(new Dimension(720, 400));
        this.setLocationRelativeTo(null);


        panel = new JPanel(new BorderLayout());

        textArea.setEditable(false);

        textField = new JTextField(30);
        textField.setActionCommand("txtField");
        textField.addActionListener(this);

        panel.add(new JScrollPane(textArea), BorderLayout.CENTER);
        panel.add(textField, BorderLayout.SOUTH);

        getContentPane().add(panel);

        commands = ConsoleCommandList.getInstance(textArea).getCommands();

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowOpened(WindowEvent e) {
                textField.requestFocusInWindow();
            }
        });

        this.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getActionCommand().equals("txtField")){
            commandFetch = textField.getText().split(" ");
            textArea.append(textField.getText() + "\n");
            logger.log(Level.INFO, FileCheckGUI.user.getLogin() + ": " + textField.getText());

            textField.setText("");
            textField.setEditable(false);
            for (var item : commands){
                if (item.getName().equals(commandFetch[0])){
                    item.runCommand(commandFetch);
                    textField.setEditable(true);
                    return;
                }
            }
            textField.setEditable(true);
            textArea.append("Unknown command. Type 'help' to see list of commands.\n");
        }
    }
}
