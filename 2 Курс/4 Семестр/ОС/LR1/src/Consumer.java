import java.util.concurrent.ArrayBlockingQueue;
import javax.swing.JTextArea;

public class Consumer implements Runnable {
    private volatile boolean running;
    private boolean paused;
    private ArrayBlockingQueue<Integer> buffer;
    private JTextArea outputArea;

    public Consumer(ArrayBlockingQueue<Integer> buffer, JTextArea outputArea) {
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
            try {
                synchronized (this) {
                    while (paused || buffer.isEmpty()) {
                        wait();
                    }
                }
                int data = buffer.take();
                outputArea.append("C: " + data + "\n");
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
