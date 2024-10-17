package my;

import java.io.Serializable;
import java.util.Objects;

public class User implements Serializable {
    private String userType;
    protected String login;
    protected String password;
    public User(String userType, String login, String password){
        this.userType = userType;
        this.login = login;
        this.password = password;
    }

    public String getUserType(){
        return userType;
    }
    public String getLogin(){
        return login;
    }
    public String getPassword(){
        return password;
    }
    public boolean isAdmin() {
        return Objects.equals(getUserType(), "Admin");
    }

    @Override
    public String toString(){
        return "Type: " + userType + "\nLogin: " + login + "\nPassword " + password;
    }
}
