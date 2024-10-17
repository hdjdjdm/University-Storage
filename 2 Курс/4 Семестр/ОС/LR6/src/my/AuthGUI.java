package my;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;

public class AuthGUI extends JFrame implements ActionListener {
    JPanel userPanel;
    JLabel stateLabel;
    JButton loginBtn, regBtn;
    JTextField loginField;
    JPasswordField passwordField;
    private static final Logger logger = Logger.getLogger(AuthGUI.class.getName());

    public AuthGUI() {
        configureLogging();

        setTitle("Authorization");
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setMinimumSize(new Dimension(220, 150));

        initComponents();

        pack();
        setVisible(true);
    }

    private void configureLogging() {
        try {
            FileHandler fileHandler = new FileHandler("auth_log.txt");
            fileHandler.setFormatter(new SimpleFormatter());

            logger.addHandler(fileHandler);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    private void initComponents(){
        userPanel = new JPanel();
        userPanel.setPreferredSize(new Dimension(100, 150));

        JLabel usernameLabel = new JLabel("Username:");
        usernameLabel.setPreferredSize(new Dimension(100, 20));
        userPanel.add(usernameLabel);

        loginField = new JTextField();
        loginField.setPreferredSize(new Dimension(100, 30));
        userPanel.add(loginField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setPreferredSize(new Dimension(100, 20));
        userPanel.add(passwordLabel);

        passwordField = new JPasswordField();
        passwordField.setPreferredSize(new Dimension(100, 30));
        userPanel.add(passwordField);

        loginBtn = new JButton("Log in");
        loginBtn.setPreferredSize(new Dimension(100, 30));
        loginBtn.addActionListener(this);
        userPanel.add(loginBtn);

        regBtn = new JButton("Register");
        regBtn.setPreferredSize(new Dimension(100, 30));
        regBtn.addActionListener(this);
        userPanel.add(regBtn);

        stateLabel = new JLabel("");
        stateLabel.setPreferredSize(new Dimension(100, 20));
        userPanel.add(stateLabel);

        add(userPanel);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getActionCommand().equals("Log in")){
            stateLabel.setText("");

            ArrayList<User> usersList;
            String username = loginField.getText();
            String password = new String(passwordField.getPassword());

            try (var ois = new ObjectInputStream(new FileInputStream("Users.dat"))){
                boolean successfull = false;
                usersList = (ArrayList<User>) ois.readObject();
                for (var user : usersList){
                    if (user.getLogin().equals(username)){
                        if (user.getPassword().equals(password)){
                            if (user.getUserType().equals("Admin")){
                                String result = JOptionPane.showInputDialog(getContentPane(),
                                        "Write keystore password",
                                        "Keystore",
                                        JOptionPane.WARNING_MESSAGE);
                                if (CertificateAuthentication.authenticate(
                                        "sert/kaka.cer",
                                        "sert/kaka.p12",
                                        result)){
                                    successfull = true;
                                    logger.log(Level.INFO, "Successfully login to admin " + username);
                                    setVisible(false);
                                    SwingUtilities.invokeLater(() -> new FileCheckGUI(user));
                                }
                                else {
                                    logger.log(Level.INFO, "Unsuccessfully attempt to login as admin " + username + ". Incorrect keystore password");
                                    JOptionPane.showMessageDialog(null, "Incorrect keystore password. ", "Login Error", JOptionPane.ERROR_MESSAGE);

                                }
                            } else {
                                successfull = true;
                                logger.log(Level.INFO, "Successfully login to " + username);
                                setVisible(false);
                                SwingUtilities.invokeLater(() -> new FileCheckGUI(user));
                            }
                        }
                        else {
                            logger.log(Level.INFO, "Unsuccessfully attempt to login as " + username + ". Entered password: " + password);
                            JOptionPane.showMessageDialog(null, "Incorrect password. Please try again.", "Login Error", JOptionPane.ERROR_MESSAGE);
                        }
                    }
                }
                if (!successfull) {
                    logger.log(Level.INFO, "Incorrect login");
                    JOptionPane.showMessageDialog(null, "Incorrect login. Please try again.", "Login Error", JOptionPane.ERROR_MESSAGE);
                }
            } catch (Exception ex){
                logger.log(Level.SEVERE, "Error during login process", ex);
                System.out.println(ex.getMessage());
            }
        }
        else if (e.getActionCommand().equals("Register")){
            String username = loginField.getText().trim();
            String password = new String(passwordField.getPassword());

            if (username.isEmpty() || password.isEmpty()) {
                JOptionPane.showMessageDialog(null, "Empty login or password", "Login Error", JOptionPane.ERROR_MESSAGE);
                return;
            }

            stateLabel.setText("");
            ArrayList<User> usersList;
            boolean flag = true;

            try (var ois = new ObjectInputStream(new FileInputStream("Users.dat"))){
                usersList = (ArrayList<User>) ois.readObject();
                for (var user : usersList){
                    if (user.getLogin().equals(username)){
                        flag = false;
                        break;
                    }
                }
            } catch (Exception ex){
                System.out.println(ex.getMessage());
                logger.log(Level.SEVERE, "Failed to read users data file: " + ex.getMessage(), ex);
                return;
            }

            if (flag){
                try (var oos = new ObjectOutputStream(new FileOutputStream("Users.dat"))){
                    usersList.add(new User("User", username, password));
                    oos.writeObject(usersList);
                    stateLabel.setText("Add user");
                    logger.log(Level.INFO, "Registered new user. Username: " + username + "\tPassword: " + password);
                } catch (Exception ex){
                    logger.log(Level.SEVERE, "Failed to register new user: " + ex.getMessage(), ex);
                }
            } else {
                stateLabel.setText("Can't add user");
                logger.log(Level.INFO, "Failed to register new user. Username:  " + username + " (already exists)");
                JOptionPane.showMessageDialog(null, "Failed to register new user. Username:  " + username + " (already exists)", "Login Error", JOptionPane.ERROR_MESSAGE);
            }
        }
    }
}
