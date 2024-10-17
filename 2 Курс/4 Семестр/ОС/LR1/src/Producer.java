import java.util.concurrent.ArrayBlockingQueue;
import javax.swing.JTextArea;

public class Producer implements Runnable {
    private volatile boolean running;
    private boolean paused;
    private ArrayBlockingQueue<Integer> buffer;
    private JTextArea outputArea;

    public Producer(ArrayBlockingQueue<Integer> buffer, JTextArea outputArea) {
        this.buffer = buffer;
        this.outputArea = outputArea;
        this.running = true;
        this.paused = false;
    }

    public void pause() {
        paused = true;
    }

    public void resume() {
        paused = false;
        synchronized (this) {
            notify();
        }
    }

    @Override
    public void run() {
        while (running) {
            int data = (int) (Math.random() * 100);
            try {
                synchronized (this) {
                    while (paused) {
                        wait();
                    }
                }
                buffer.put(data);
                outputArea.append("P: " + data + "\n");
                outputArea.setCaretPosition(outputArea.getDocument().getLength());
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            }
        }
    }

    public void stop() {
        running = false;
    }
}
