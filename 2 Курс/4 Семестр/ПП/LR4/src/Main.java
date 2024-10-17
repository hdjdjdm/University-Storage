import java.io.*;
import java.util.*;

public class Main {
    public static Scanner scanner = new Scanner(System.in);
    public static ArrayList<Person> persons = new ArrayList<>();
    public static List<Student> students = new ArrayList<>();
    public static List<Teacher> teachers = new ArrayList<>();

    public static void main(String[] args){
        System.out.println("1.Create new base\n2.Load base");
        String choice;
        do {
            choice = scanner.nextLine();
            switch (choice){
                case "1":
                    createMassive();

                    System.out.println("\nSave as:\n1.Text\n2.Binary\n3.Serialize\n4.Dont save");
                    do {
                        String choice2 = scanner.nextLine();
                        switch (choice2){
                            case "1":
                                writeMassive("persons.txt");
                                break;
                            case "2":
                                outputMassive("persons.bin");
                                break;
                            case "3":
                                serialize("person.ser");
                                break;
                            case "4":
                                break;
                            default:
                                System.out.print("Invalid choice. Type only available values: ");
                                continue;
                        }
                        break;
                    } while (true);
                    break;
                case "2":
                    System.out.println("Load:\n1.Text\n2.Binary\n3.Deserialize");
                    do {
                        String choice2 = scanner.nextLine();
                        switch (choice2){
                            case "1":
                                readFrom("persons.txt");
                                break;
                            case "2":
                                inputFrom("persons.bin");
                                break;
                            case "3":
                                deserialize("person.ser");
                                break;
                            default:
                                System.out.print("Invalid choice. Type only available values: ");
                                continue;
                        }
                        break;
                    } while (true);
                    break;
                default:
                    System.out.print("Invalid choice. Type 1 or 2: ");
                    continue;
            }
            break;
        } while (true);

        splitPersons();

    }

    public static void createMassive() {
        int i = 1;
        do {
            System.out.println("Person " + i);
            System.out.print("Enter name: ");
            String name = scanner.nextLine();

            System.out.print("Enter age: ");
            String age = scanner.nextLine();

            System.out.print("Enter subjects (separated by ','): ");
            String input = scanner.nextLine();
            String[] subjectArray = input.split(",");
            ArrayList<String> subjects = new ArrayList<>(Arrays.asList(subjectArray));

            System.out.println("Choice type of person:\n1.Student\n2.Teacher");
            String choice;
            do {
                choice = scanner.nextLine();
                switch (choice) {
                    case "1":
                        try {
                            persons.add(new Student(name, age, subjects));
                        } catch (InvalidAgeException | InvalidSubjectException e) {
                            System.out.println(e.getMessage());
                            break;
                        }
                        i++;
                        break;
                    case "2":
                        try {
                            persons.add(new Teacher(name, age, subjects));
                        } catch (InvalidAgeException e) {
                            System.out.println(e.getMessage());
                            break;
                        }
                        i++;
                        break;
                    default:
                        System.out.print("Invalid choice. Type 1 or 2: ");
                        break;
                }
            } while (!choice.equals("1") && !choice.equals("2"));

            System.out.print("Add more? Type 1 if yes: ");
            String choice2 = scanner.nextLine();
            if (!Objects.equals(choice2, "1")){
                break;
            }
        } while (true);
    }

    public static void splitPersons(){
        for (Person person : persons){
            if (person instanceof Student){
                students.add((Student) person);
            } else if (person instanceof Teacher){
                teachers.add((Teacher) person);
            }
        }
        System.out.println("Students: ");
        for (Student student : students){
            System.out.println(student);
        }
        System.out.println();

        System.out.println("Teachers: ");
        for (Teacher teacher : teachers){
            System.out.println(teacher);
        }
        System.out.println();
    }

    public static void outputMassive(String filename) {
        try (DataOutputStream outputStream = new DataOutputStream(new FileOutputStream(filename))) {
            outputStream.writeInt(persons.size());
            for (Person person : persons) {
                IOUtils.outputPerson(person, outputStream);
            }
            System.out.println("\nFile successfully saved");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void inputFrom(String filename) {
        try (DataInputStream inputStream = new DataInputStream(new FileInputStream(filename))) {
            int numberOfPersons = inputStream.readInt();
            for (int i = 0; i < numberOfPersons; i++) {
                Person person = IOUtils.inputPerson(inputStream);
                persons.add(person);
            }
        } catch (IOException | ClassNotFoundException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }

    public static void writeMassive(String filename) {
        try (Writer writer = new FileWriter(filename)) {
            for (Person person : persons) {
                IOUtils.writePerson(person, writer);
            }
            System.out.println("\nFile successfully saved");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void readFrom(String filename){
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = reader.readLine()) != null) {
                Person person = IOUtils.readPerson(line);
                persons.add(person);
            }
        } catch (IOException | InvalidAgeException e) {
            throw new RuntimeException(e);
        }
    }

    public static void serialize(String filename){
        try {
            ObjectOutputStream out = new ObjectOutputStream( new FileOutputStream(filename));
            for (Person person : persons) {
                IOUtils.serializePerson(person, out);
            }
            out.close();
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public static void deserialize(String filename) {
        try {
            ObjectInputStream in = new ObjectInputStream(new FileInputStream(filename));
            while (true) {
                try {
                    persons.add(IOUtils.deserializePerson(in));
                } catch (EOFException e) {
                    break;
                }
            }
            in.close();
        } catch (IOException e) {
            System.out.println("Some error occurred!");
        } catch (ClassNotFoundException e) {
            System.out.println("Wrong object type");
        }
    }
}
