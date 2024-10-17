import java.util.ArrayList;

public interface Person{
    String getName();
    public void setName(String name);
    public int getAge();
    public void setAge(String age) throws InvalidAgeException;
    public ArrayList<String> getSubjects();
    public String getSubject(int id);
    public void setSubjects(ArrayList<String> subjects);
    public void setSubject(int id, String subject);
    public String nameAndFirstSubject();
}