import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SetPriorityWindow extends JFrame {
    private JLabel threadLabel;
    private JComboBox<String> threadComboBox;
    private JLabel priorityLabel;
    private JSlider prioritySlider;
    private JButton setPriorityButton;

    public SetPriorityWindow(Thread[] threads) {
        setTitle("Set Priority");
        setSize(300, 250);
        setMinimumSize(new Dimension(300, 250));
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        JPanel panel = new JPanel(new GridLayout(5, 1));

        threadLabel = new JLabel("Select Thread:");
        panel.add(threadLabel);

        threadComboBox = new JComboBox<>();
        for (Thread thread : threads) {
            threadComboBox.addItem(thread.getName() + " (Priority: " + thread.getPriority() + ")");
        }
        panel.add(threadComboBox);

        priorityLabel = new JLabel("Set Priority:");
        panel.add(priorityLabel);

        prioritySlider = new JSlider(JSlider.HORIZONTAL, Thread.MIN_PRIORITY, Thread.MAX_PRIORITY, Thread.NORM_PRIORITY);
        prioritySlider.setMajorTickSpacing(1);
        prioritySlider.setPaintTicks(true);
        prioritySlider.setPaintLabels(true);
        panel.add(prioritySlider);

        setPriorityButton = new JButton("Set Priority");
        panel.add(setPriorityButton);

        add(panel);

        setPriorityButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String selectedThreadName = (String) threadComboBox.getSelectedItem();
                for (Thread thread : threads) {
                    if (selectedThreadName.startsWith(thread.getName())) {
                        int priority = prioritySlider.getValue();
                        thread.setPriority(priority);
                        JOptionPane.showMessageDialog(SetPriorityWindow.this, "Priority of " + selectedThreadName + " set to " + priority, "Priority Set", JOptionPane.INFORMATION_MESSAGE);
                        return;
                    }
                }
            }
        });
    }
}
