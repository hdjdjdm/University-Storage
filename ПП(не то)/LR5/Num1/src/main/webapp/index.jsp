<%-- 
    Document   : index
    Created on : 11 июл. 2024 г., 22:37:01
    Author     : AMD
--%>

<%@page import="java.net.URLEncoder"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <link rel="icon" href="images/icon.png" type="image/x-icon">
        <link rel="stylesheet" href="css/styles.css">
        <title>Калькулятор</title>
    </head>
    
    <body>
        <form method='post'>
            Число 1: <input type='text' name='number1' value='<%= request.getParameter("number1") != null ? request.getParameter("number1") : "" %>'><br>
            Число 2: <input type='text' name='number2' value='<%= request.getParameter("number2") != null ? request.getParameter("number2") : "" %>'><br>
            <input type='submit' name='operation' value='+'>
            <input type='submit' name='operation' value='-'>
            <input type='submit' name='operation' value='*'>
            <input type='submit' name='operation' value='/'>
        </form>
            
            <%
                String number1 = request.getParameter("number1");
                String number2 = request.getParameter("number2");
                String operation = request.getParameter("operation");
                if (number1 != null && number2 != null && operation != null) {
                    try {
                        double num1 = Double.parseDouble(number1);
                        double num2 = Double.parseDouble(number2);
                        double result = 0;
                        
                        switch (operation) {
                            case "+":
                                result = num1 + num2;
                                break;
                            case "-":
                                result = num1 - num2;
                                break;
                            case "*":
                                result = num1 * num2;
                                break;
                            case "/":
                                if (num2 != 0) {
                                    result = num1 / num2;
                                } else {
                                    throw new ArithmeticException("Деление на ноль запрещено.");
                                }
                                break;
                        }
                        out.println("<p>Результат: " + num1 + " " + operation + " " + num2 + " = " + result + "</p>");
                    } catch (NumberFormatException | ArithmeticException e) {
                        String errorMessage = e.getMessage();
                        response.sendRedirect("error.jsp?error=" + URLEncoder.encode(errorMessage, "UTF-8"));
                    }
                }
            %>
    </body>
</html>
