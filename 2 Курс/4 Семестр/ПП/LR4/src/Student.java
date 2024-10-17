import java.io.*;
import java.util.ArrayList;
import java.util.Objects;

public class Student implements Person{
    private String name;
    private int age;
    private ArrayList<String> subjects;


    public Student(){
        this.name = "";
        this.age = 0;
        subjects = new ArrayList<>();
    }

    public Student(String name, String age, ArrayList<String> subjects) throws InvalidAgeException {
        if (subjects == null || subjects.isEmpty() || (subjects.size() == 1 && subjects.get(0).isEmpty())) {
            throw new InvalidSubjectException("Error: No subjects provided!");
        }
        try {
            this.name = name;
            int parsedAge = Integer.parseInt(age);
            if (parsedAge < 0) {
                throw new InvalidAgeException("Error: Negative age is not allowed!");
            }
            this.age = parsedAge;
        } catch (NumberFormatException e) {
            throw new InvalidAgeException("Error: Incorrect age!");
        }

        this.subjects = subjects;
    }

    @Override
    public String getName(){
        return name;
    }

    @Override
    public void setName(String name){
        this.name = name;
    }

    @Override
    public int getAge(){
        return age;
    }

    @Override
    public void setAge(String age) throws InvalidAgeException {
        try {
            int parsedAge = Integer.parseInt(age);
            if (parsedAge < 0) {
                throw new InvalidAgeException("Error: Negative age is not allowed!");
            }
            this.age = parsedAge;
        } catch (NumberFormatException e) {
            throw new InvalidAgeException("Error: Incorrect age!");
        }
    }

    @Override
    public ArrayList<String> getSubjects(){
        return subjects;
    }

    @Override
    public String getSubject(int id){
        return subjects.get(id);
    }

    @Override
    public void setSubjects(ArrayList<String> subjects) {
        if (subjects == null || subjects.isEmpty()) {
            throw new InvalidSubjectException("Error: No subjects provided!");
        }
        this.subjects = subjects;
    }

    @Override
    public void setSubject(int id, String subject){
        this.subjects.set(id, subject);
    }

    @Override
    public String nameAndFirstSubject(){
        return name + subjects.get(0);
    }

    @Override
    public String toString(){
        return "name= " + name + ",\tage= " + age + ",\tsubjects= " + subjects.toString();
    }

    @Override
    public boolean equals(Object obj){
        if(this == obj){
            return true;
        }
        if (obj == null || getClass() != obj.getClass()){
            return false;
        }
        Student student = (Student) obj;
        return age == student.age &&
                Objects.equals(name, student.name) &&
                subjects.equals(student.subjects);
    }

    @Override
    public int hashCode(){
        return 31 * Objects.hash(name, age) + subjects.hashCode();
    }

    @Override
    public void output(OutputStream out) throws IOException {
        ObjectOutputStream oos = new ObjectOutputStream(out);
        oos.writeObject(this);
    }

    @Override
    public void write(Writer out) throws IOException {
        BufferedWriter writer = new BufferedWriter(out);
        writer.write(this.getClass().getSimpleName() + " " + name + " " + age + " " + subjects.toString());
        writer.write(System.lineSeparator());
        writer.flush();
    }
}