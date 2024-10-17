import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class ProducerConsumerGUI extends JFrame {
    private JTextArea outputArea;
    private ArrayBlockingQueue<Integer> buffer;
    private int bufferSize;
    private List<Producer> producers;
    private List<Consumer> consumers;

    public ProducerConsumerGUI() {
        setTitle("Producer-Consumer");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(800, 400);
        setMinimumSize(new Dimension(800, 400));
        setLocationRelativeTo(null);

        JPanel panel = new JPanel(new BorderLayout());

        JButton startProducerButton = new JButton("Start Producer");
        JButton stopProducerButton = new JButton("Stop Producer");
        JButton startConsumerButton = new JButton("Start Consumer");
        JButton stopConsumerButton = new JButton("Stop Consumer");
        JButton setPriorityButton = new JButton("Set Priority");
        JButton openTerminalButton = new JButton("Open Terminal");

        outputArea = new JTextArea(10, 30);
        JScrollPane scrollPane = new JScrollPane(outputArea);
        outputArea.setEditable(false);

        JPanel buttonPanel = new JPanel(new GridLayout(2, 3));
        buttonPanel.add(startProducerButton);
        buttonPanel.add(startConsumerButton);
        buttonPanel.add(setPriorityButton);
        buttonPanel.add(stopProducerButton);
        buttonPanel.add(stopConsumerButton);
        buttonPanel.add(openTerminalButton);

        panel.add(buttonPanel, BorderLayout.NORTH);
        panel.add(scrollPane, BorderLayout.CENTER);

        add(panel);

        buffer = new ArrayBlockingQueue<>(1);
        producers = new ArrayList<>();
        consumers = new ArrayList<>();

        startBufferCalculationTask();

        startProducerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                startProducer();
            }
        });

        stopProducerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                stopLastProducer();
            }
        });

        startConsumerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                startConsumer();
            }
        });

        stopConsumerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                stopLastConsumer();
            }
        });

        setPriorityButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                setPriority();
            }
        });

        openTerminalButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                openTerminal();
            }
        });
    }

    private void startProducer() {
        Producer newProducer = new Producer(buffer, outputArea);
        producers.add(newProducer);
        Thread producerThread = new Thread(newProducer, "Producer" + (producers.size()));
        outputArea.append("Producer" + (producers.size()) + " started.\n");
        producerThread.start();
        outputArea.setCaretPosition(outputArea.getDocument().getLength());
    }

    private void stopLastProducer() {
        if (!producers.isEmpty()) {
            Producer lastProducer = producers.remove(producers.size() - 1);
            lastProducer.stop();
            outputArea.append("Producer" + (producers.size() + 1) + " stopped.\n");
            outputArea.setCaretPosition(outputArea.getDocument().getLength());
        }
    }

    private void startConsumer() {
        Consumer newConsumer = new Consumer(buffer, outputArea);
        consumers.add(newConsumer);
        Thread consumerThread = new Thread(newConsumer, "Consumer" + (consumers.size()));
        outputArea.append("Consumer" + (consumers.size()) + " started.\n");
        consumerThread.start();
        outputArea.setCaretPosition(outputArea.getDocument().getLength());
    }

    private void stopLastConsumer() {
        if (!consumers.isEmpty()) {
            Consumer lastConsumer = consumers.remove(consumers.size() - 1);
            lastConsumer.stop();
            outputArea.append("Consumer" + (consumers.size() + 1) + " stopped.\n");
            outputArea.setCaretPosition(outputArea.getDocument().getLength());
        }
    }

    private void setPriority() {
        Thread[] threads = new Thread[Thread.activeCount()];
        Thread.enumerate(threads);
        new SetPriorityWindow(threads).setVisible(true);
    }

    private void openTerminal() {
        new TerminalWindow(buffer, producers, consumers, outputArea, bufferSize).setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new ProducerConsumerGUI().setVisible(true);
            }
        });
    }

    private void startBufferCalculationTask() {
        ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(1);
        scheduler.scheduleAtFixedRate(() -> {
            int oldBufferSize = bufferSize;

            bufferSize = calculateBufferSize();

            if (buffer.size() != bufferSize) {
                List<Integer> tempBufferData = new ArrayList<>();
                buffer.drainTo(tempBufferData);
                buffer = new ArrayBlockingQueue<>(bufferSize);
                buffer.addAll(tempBufferData);
            }

            outputArea.append("Buffer size updated from " + oldBufferSize + " to: " + bufferSize + "\n");
        }, 0, 1, TimeUnit.MINUTES);
    }


    private int calculateBufferSize() {
        long currentTimeMillis = System.currentTimeMillis();
        long seconds = currentTimeMillis / 1000;
        long minutes = seconds / 60;
        return (int) minutes * 2;
    }
}
