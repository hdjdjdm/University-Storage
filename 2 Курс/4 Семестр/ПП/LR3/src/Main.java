import java.util.*;

public class Main {
    public static Scanner scanner = new Scanner(System.in);
    public static ArrayList<Person> persons = new ArrayList<>();
    public static List<Person> sameRes = new ArrayList<>();
    public static List<Student> students = new ArrayList<>();
    public static List<Teacher> teachers = new ArrayList<>();

    public static void main(String[] args){

        createMassive();
        printMassive();
        similarPersons();
        sameResult();
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

    public static void printMassive(){
        System.out.println("Information about all persons:");
        for (int i = 0; i < persons.size(); i++){
            System.out.println("Person " + (i+1) + ": " + persons.get(i));
        }
        System.out.println();
    }

    public static void similarPersons(){
        System.out.println("Similar: ");
        for (int i = 0; i < persons.size(); i++){
            for (int j = i + 1; j < persons.size(); j++){
                if (persons.get(i).equals(persons.get(j))){
                    System.out.println("Person " + (i+1) + ": " + persons.get(i));
                    System.out.println("Person " + (j+1) + ": " + persons.get(j));
                }
            }
        }
        System.out.println();
    }

    public static void sameResult(){
        for (int i = 0; i < persons.size(); i++){
            for (int j = i + 1; j < persons.size(); j++){
                if (Objects.equals(persons.get(i).nameAndFirstSubject(), persons.get(j).nameAndFirstSubject())){
                    if (!sameRes.contains(persons.get(i))) {
                        sameRes.add(persons.get(i));
                    }
                    if (!sameRes.contains(persons.get(j))) {
                        sameRes.add(persons.get(j));
                    }
                }
            }
        }
        System.out.println("Objects with same result of 'sameRes' method");
        for (Person person : sameRes){
            System.out.println(person);
        }
        System.out.println();
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
}
