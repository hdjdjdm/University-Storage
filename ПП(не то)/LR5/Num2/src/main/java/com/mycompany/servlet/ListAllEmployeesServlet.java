/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.sql.DataSource;

/**
 *
 * @author AMD
 */
@WebServlet("/listAllEmployees")
public class ListAllEmployeesServlet extends HttpServlet {
    private DataSource dataSource;
    
    @Override
    public void init() throws ServletException {
            try {
                InitialContext ctx = new InitialContext();
                dataSource = (DataSource) ctx.lookup("java:comp/env/jdbc/MyDB");
            } catch (NamingException e) {
                throw new ServletException(e);
            }
    }
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        
        try (PrintWriter out = response.getWriter();
             Connection connection = dataSource.getConnection();
             Statement stmt = connection.createStatement()) {

            String query = "SELECT * FROM employees";
            ResultSet rs = stmt.executeQuery(query);

            while (rs.next()) {
                out.println("<p>ID: " + rs.getInt("id") + "</p>");
                out.println("<p>Имя: " + rs.getString("имя") + "</p>");
                out.println("<p>Фамилия: " + rs.getString("фамилия") + "</p>");
                out.println("<p>ID отдела: " + rs.getInt("отдел_id") + "</p>");
                out.println("<p>Должность: " + rs.getString("должность") + "</p>");
                out.println("<p>Зарплата: " + rs.getDouble("зарплата") + "</p>");
                out.println("<p>Дата найма: " + rs.getDate("дата_найма") + "</p>");
                out.println("<hr>");
            }
        } catch (SQLException e) {
            throw new ServletException(e);
        }
    }
}