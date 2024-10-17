<%-- 
    Document   : error
    Created on : 12 июл. 2024 г., 10:30:46
    Author     : AMD
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <link rel="icon" href="images/icon.png" type="image/x-icon">
        <title>Ошибка</title>
    </head>
    
    <body>
        <h1>Ошибка!</h1>
        
        <%
            String errorMessage = request.getParameter("error");
            if (errorMessage != null) {
                out.println("<p>" + errorMessage + "</p>");
            }
        %>
        
        <form action='index.jsp'>
            <button>Вернуться назад</button>
        </form>
        
    </body>
</html>
