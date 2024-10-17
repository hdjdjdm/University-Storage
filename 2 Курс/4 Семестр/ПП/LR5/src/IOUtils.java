import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;

public class IOUtils {
//    public static void outputPerson(Person o, OutputStream out) throws IOException {
//        o.output(out);
//    }
//
//    public static Person inputPerson(InputStream in) throws IOException, ClassNotFoundException {
//        ObjectInputStream ois = new ObjectInputStream(in);
//            return (Person) ois.readObject();
//    }
//
//
//    public static void writePerson(Person o, Writer out) throws IOException {
//        o.write(out);
//    }
//
//    public static Person readPerson(String line) throws InvalidAgeException {
//        String[] parts = line.split(" ");
//        String className = parts[0];
//        String name = parts[1];
//        String age = parts[2];
//        ArrayList<String> subjects = new ArrayList<>(Arrays.asList(Arrays.copyOfRange(parts, 3, parts.length)));
//
//        switch (className) {
//            case "Student" -> {
//                return new Student(name, age, subjects);
//            }
//            case "Teacher" -> {
//                return new Teacher(name, age, subjects);
//            }
//            default -> {
//                System.out.println("Unavailable class");
//                return null;
//            }
//        }
//    }
//
//    public static void serializePerson(Person o, OutputStream out) throws IOException {
//        ObjectOutputStream oos = new ObjectOutputStream(out);
//            oos.writeObject(o);
//    }
//
//    public static Person deserializePerson(InputStream in) throws IOException, ClassNotFoundException {
//        ObjectInputStream ois = new ObjectInputStream(in);
//        return (Person) ois.readObject();
//    }

    public static synchronized MassiveInterface synchronizedInterface(MassiveInterface i) {
        return new SynchronizedMassive(i);
    }
}
