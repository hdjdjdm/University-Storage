package org.example;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.net.URL;
import java.sql.*;

public class Main extends JFrame {
    private JTable table;
    private JTextField queryfield;
    private JButton execquery, addbutton, deletebutton, updatebutton;
    private Connection connection;

    public Main() {
        init();

        connectToDatabase();
        updateTable();
    }

    private void init() {
        setTitle("САМУЛЕТЫ АХАХАХА");
        setMinimumSize(new Dimension(800, 600));
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel mainpanel = new JPanel();
        mainpanel.setLayout(new BorderLayout());

        JPanel querymenu = new JPanel();
        JLabel entertext = new JLabel("Введите id самолета для поиска:");
        queryfield = new JTextField(5);
        execquery = new JButton("Поиск");
        updatebutton = new JButton("Обновить");
        querymenu.add(entertext);
        querymenu.add(queryfield);
        querymenu.add(execquery);
        querymenu.add(updatebutton);

        JPanel editmenu = new JPanel();
        addbutton = new JButton("Добавить");
        deletebutton = new JButton("Удалить");
        editmenu.add(addbutton);
        editmenu.add(deletebutton);

        table = new JTable();
        JScrollPane scrollPane = new JScrollPane(table);

        mainpanel.add(querymenu, BorderLayout.NORTH);
        mainpanel.add(editmenu, BorderLayout.SOUTH);
        mainpanel.add(scrollPane, BorderLayout.CENTER);

        add(mainpanel);

        queryfield.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (!isNumeric(queryfield.getText())) {
                    JOptionPane.showMessageDialog(null, "Некорректное значение! Введите число.");
                    return;
                }
                search(queryfield.getText());
            }
        });

        execquery.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (!isNumeric(queryfield.getText())) {
                    JOptionPane.showMessageDialog(null, "Некорректное значение! Введите число.");
                    return;
                }
                search(queryfield.getText());
            }
        });

        updatebutton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                updateTable();
            }
        });

        addbutton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JTextField idField = new JTextField(5);
                JTextField modelField = new JTextField(25);
                JTextField capacityField = new JTextField(5);

                JPanel panel = new JPanel(new GridLayout(0, 2));
                panel.add(new JLabel("ID самолета:"));
                panel.add(idField);
                panel.add(new JLabel("Модель самолета:"));
                panel.add(modelField);
                panel.add(new JLabel("Вместимость:"));
                panel.add(capacityField);

                int result = JOptionPane.showConfirmDialog(null, panel, "Введите данные самолета", JOptionPane.OK_CANCEL_OPTION);
                if (result == JOptionPane.OK_OPTION) {
                    addRow(idField.getText(), modelField.getText(), capacityField.getText());
                }
            }
        });

        deletebutton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String id = JOptionPane.showInputDialog("Введите ID самолета для удаления:");
                if (id != null && isNumeric(id)) {
                    deleteRow(id);
                } else {
                    JOptionPane.showMessageDialog(null, "Некорректное значение! Введите число.");
                }
            }
        });
    }

    private void updateTable() {
        String query = "SELECT * FROM самолет";

        try (Statement stmt = connection.createStatement();
            ResultSet rs = stmt.executeQuery(query)) {
            ResultSetMetaData metaData = rs.getMetaData();
            int columnCount = metaData.getColumnCount();
            String[] columnNames = new String[columnCount];
            for (int i = 1; i <= columnCount; i++) {
                columnNames[i-1] = metaData.getColumnName(i);
            }

            DefaultTableModel tableModel = new DefaultTableModel(columnNames, 0);
            while (rs.next()) {
                Object[] row = new Object[columnCount];
                for (int i = 1; i <= columnCount; i++) {
                    row[i-1] = rs.getObject(i);
                }
                tableModel.addRow(row);
            }
            table.setModel(tableModel);

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void search(String ID) {
        String query = "SELECT * FROM самолет\n" +
                "WHERE ID_Самолета = " + ID;

        try (Statement stmt = connection.createStatement();
             ResultSet rs = stmt.executeQuery(query)) {
            ResultSetMetaData metaData = rs.getMetaData();
            int columnCount = metaData.getColumnCount();
            String[] columnNames = new String[columnCount];
            for (int i = 1; i <= columnCount; i++) {
                columnNames[i-1] = metaData.getColumnName(i);
            }

            DefaultTableModel tableModel = new DefaultTableModel(columnNames, 0);
            boolean hasRows = false;
            while (rs.next()) {
                hasRows = true;
                Object[] row = new Object[columnCount];
                for (int i = 1; i <= columnCount; i++) {
                    row[i-1] = rs.getObject(i);
                }
                tableModel.addRow(row);
            }
            if (!hasRows) {
                JOptionPane.showMessageDialog(this, "Нет данных для самолета с ID: " + ID, "Информация", JOptionPane.INFORMATION_MESSAGE);
                queryfield.setText("");
            } else {
                table.setModel(tableModel);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void addRow(String id, String model, String capacity) {
        if (!isNumeric(id) || !isNumeric(capacity)) {
            JOptionPane.showMessageDialog(this, "ID самолета и вместимость должны быть числами.", "Ошибка ввода", JOptionPane.ERROR_MESSAGE);
            return;
        }

        if (isIdExists(id)) {
            JOptionPane.showMessageDialog(this, "Самолет с ID " + id + " уже существует.", "Ошибка добавления", JOptionPane.ERROR_MESSAGE);
            return;
        }

        String query = "INSERT INTO самолет (ID_Самолета, Модель, Вместимость) VALUES (?, ?, ?)";
        try (PreparedStatement pstmt = connection.prepareStatement(query)) {
            pstmt.setString(1, id);
            pstmt.setString(2, model);
            pstmt.setString(3, capacity);
            pstmt.executeUpdate();
            updateTable();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void deleteRow(String id) {
        String query = "DELETE FROM самолет WHERE ID_Самолета = ?";
        try (PreparedStatement pstmt = connection.prepareStatement(query)) {
            pstmt.setString(1, id);
            int affectedRows = pstmt.executeUpdate();
            if (affectedRows == 0) {
                JOptionPane.showMessageDialog(this, "Самолет с ID " + id + " не найден.", "Информация", JOptionPane.INFORMATION_MESSAGE);
            } else {
                updateTable();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private boolean isIdExists(String id) {
        String query = "SELECT 1 FROM самолет WHERE ID_Самолета = ?";
        try (PreparedStatement pstmt = connection.prepareStatement(query)) {
            pstmt.setString(1, id);
            try (ResultSet rs = pstmt.executeQuery()) {
                return rs.next();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    private void connectToDatabase() {
        try {
            URL resourse = getClass().getClassLoader().getResource("lr4.db");
            if (resourse != null) {
                File databaseFile = new File(resourse.toURI());
                String url = "jdbc:sqlite:" + databaseFile.getAbsolutePath();
                connection = DriverManager.getConnection(url);
            } else {
                System.err.println("База не найдена!");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private boolean isNumeric(String s) {
        if (s == null || s.isEmpty()) {
            return false;
        }
        try {
            Integer.parseInt(s);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            Main main = new Main();
            main.setVisible(true);
        });
    }
}