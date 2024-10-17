package my.consolegui;

import java.util.logging.FileHandler;
import java.util.logging.SimpleFormatter;
import java.io.IOException;

public class ConsoleLog {
    private static FileHandler fileHandler;
    private static boolean isConfigured = false;

    public static synchronized void configureLogging() {
        if (!isConfigured) {
            try {
                fileHandler = new FileHandler("console_log.txt");
                fileHandler.setFormatter(new SimpleFormatter());
            } catch (IOException e) {
                e.printStackTrace();
            }
            isConfigured = true;
        }
    }

    public static FileHandler getFileHandler() {
        return fileHandler;
    }
}
