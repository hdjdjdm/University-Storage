package my;

import javax.swing.*;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

public class Main {

    public static void main(String[] args) throws Exception {
        SwingUtilities.invokeLater(() -> new AuthGUI());

        ArrayList<User> list = new ArrayList<>();
        list.add(new User("Admin", "Admin", "admin")); //mypassword
        list.add(new User("User", "user1", "111"));

        try (var oos = new ObjectOutputStream(new FileOutputStream("Users.dat"))){
            oos.writeObject(list);
        } catch (Exception ex){
            System.out.println(ex.getMessage());
        }
    }
}

