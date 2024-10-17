import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

public class GuessNumberGame extends JFrame {
    private JTextField minField, maxField;
    private JButton startButton;
    private JLabel guessLabel;
    private int min, max, guess;
    private JFrame secondFrame;
    private JRadioButton metalRadioButton, nimbusRadioButton, windowsRadioButton, motifRadioButton;

    public GuessNumberGame() {
        setTitle("Угадай число");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(400, 300);
        setMinimumSize(new Dimension(400, 300));
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(6, 2, 5, 5));

        panel.add(new JLabel("Минимальное значение:"));
        minField = new JTextField();
        panel.add(minField);

        panel.add(new JLabel("Максимальное значение:"));
        maxField = new JTextField();
        panel.add(maxField);

        startButton = new JButton("Начать игру");
        startButton.addActionListener(new StartButtonListener());
        panel.add(startButton);

        panel.add(new JLabel("Выберите тему оформления:"));

        metalRadioButton = new JRadioButton("Metal");
        metalRadioButton.setSelected(true);
        nimbusRadioButton = new JRadioButton("Nimbus");
        windowsRadioButton = new JRadioButton("Windows");
        motifRadioButton = new JRadioButton("Motif");

        ButtonGroup buttonGroup = new ButtonGroup();
        buttonGroup.add(metalRadioButton);
        buttonGroup.add(nimbusRadioButton);
        buttonGroup.add(windowsRadioButton);
        buttonGroup.add(motifRadioButton);

        ActionListener themeChangeListener = e -> {
            try {
                if (metalRadioButton.isSelected()) {
                    UIManager.setLookAndFeel("javax.swing.plaf.metal.MetalLookAndFeel");
                } else if (nimbusRadioButton.isSelected()) {
                    UIManager.setLookAndFeel("javax.swing.plaf.nimbus.NimbusLookAndFeel");
                } else if (windowsRadioButton.isSelected()) {
                    UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
                } else if (motifRadioButton.isSelected()) {
                    UIManager.setLookAndFeel("com.sun.java.swing.plaf.motif.MotifLookAndFeel");
                }
                SwingUtilities.updateComponentTreeUI(GuessNumberGame.this);
            } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | UnsupportedLookAndFeelException ex) {
                throw new RuntimeException(ex);
            }
        };

        metalRadioButton.addActionListener(themeChangeListener);
        nimbusRadioButton.addActionListener(themeChangeListener);
        windowsRadioButton.addActionListener(themeChangeListener);
        motifRadioButton.addActionListener(themeChangeListener);

        panel.add(metalRadioButton);
        panel.add(nimbusRadioButton);
        panel.add(windowsRadioButton);
        panel.add(motifRadioButton);

        add(panel);
    }

    private class StartButtonListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            try {
                min = Integer.parseInt(minField.getText());
                max = Integer.parseInt(maxField.getText());
                if (min > max) {
                    JOptionPane.showMessageDialog(null, "Минимальное значение должно быть меньше максимального!");
                    return;
                }
                guess = getRandomNumber(min, max);

                secondFrame = new JFrame();
                secondFrame.setTitle("Угадай число");
                secondFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                secondFrame.setSize(300, 150);
                secondFrame.setMinimumSize(new Dimension(300, 150));
                secondFrame.setLocationRelativeTo(null);

                JPanel panel = new JPanel();
                panel.setLayout(new GridLayout(2, 1));

                guessLabel = new JLabel("Предполагаемое число: " + guess);
                panel.add(guessLabel);

                JPanel buttonPanel = new JPanel();
                buttonPanel.setLayout(new FlowLayout());

                JButton higherButton = new JButton("Больше");
                higherButton.addActionListener(new HigherButtonListener());
                buttonPanel.add(higherButton);

                JButton lowerButton = new JButton("Меньше");
                lowerButton.addActionListener(new LowerButtonListener());
                buttonPanel.add(lowerButton);

                JButton correctButton = new JButton("Верно");
                correctButton.addActionListener(new CorrectButtonListener());
                buttonPanel.add(correctButton);

                panel.add(buttonPanel);

                secondFrame.add(panel);
                secondFrame.setVisible(true);

                startButton.setEnabled(false);
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(null, "Введите корректные значения!");
            }
        }
    }

    private int getRandomNumber(int min, int max) {
        Random random = new Random();
        return random.nextInt(max - min + 1) + min;
    }

    private class HigherButtonListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            if (guess == max) {
                JOptionPane.showMessageDialog(null, "Вы жульничаете!");
                secondFrame.dispose();
                startButton.setEnabled(true);
                return;
            }
            min = guess + 1;
            guess = getRandomNumber(min, max);
            guessLabel.setText("Предполагаемое число: " + guess);
            if (max == min) {
                JOptionPane.showMessageDialog(null, "Победа! Загаданное число: " + guess);
                secondFrame.dispose();
                startButton.setEnabled(true);
            }
        }
    }

    private class LowerButtonListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            if (guess == min) {
                JOptionPane.showMessageDialog(null, "Вы жульничаете!");
                secondFrame.dispose();
                startButton.setEnabled(true);
                return;
            }
            max = guess - 1;
            guess = getRandomNumber(min, max);
            guessLabel.setText("Предполагаемое число: " + guess);
            if (max == min) {
                JOptionPane.showMessageDialog(null, "Победа! Загаданное число: " + guess);
                secondFrame.dispose();
                startButton.setEnabled(true);
            }
        }
    }

    private class CorrectButtonListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            JOptionPane.showMessageDialog(null, "Победа! Загаданное число: " + guess);
            secondFrame.dispose();
            startButton.setEnabled(true);
        }
    }


    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            GuessNumberGame game = new GuessNumberGame();
            game.setVisible(true);
        });
    }
}
