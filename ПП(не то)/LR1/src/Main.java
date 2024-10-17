import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;
import java.io.File;
import java.io.IOException;
import java.util.Scanner;

public class Main {
    public static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        Document document;
        do {
            System.out.print("Input filename: ");
            String inputfile = scanner.nextLine();
            document = openXML(inputfile);
        } while (document == null);

        if (checkXML(document)) {
            System.out.println("Found incorrect averages in document.");
            System.out.print("Output filename: ");
            String outputfile = scanner.nextLine();

            saveXML(document, outputfile);
            System.out.println("Document saved to " + outputfile);
        } else {
            System.out.println("Document's averages are correct!");
        }
    }

    public static Document openXML(String filename) {
        File file = new File(filename);
        if (!file.exists()) {
            System.out.println("Error 228: File not found!");
            return null;
        }

        if (file.length() == 0) {
            System.out.println("Error: File is empty!");
            return null;
        }

        try {
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document document = builder.parse(new File(filename));
            return document;
        } catch (SAXException e) {
            System.out.println("Error 1: The file is not valid XML document!");
        } catch (IOException e) {
            System.out.println("Error 2: IO error");
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public static void saveXML(Document document, String filename) {
        try {
            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            DOMSource source = new DOMSource(document);
            StreamResult result = new StreamResult(new File(filename));
            transformer.transform(source, result);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static boolean checkXML(Document document) {
        boolean needfix = false;
        Element root = document.getDocumentElement();
        NodeList studentList = root.getElementsByTagName("student");

        if (studentList.getLength() == 0) {
            System.out.println("Error 337: No student elements found!");
            return false;
        }

        for (int i = 0; i < studentList.getLength(); i++) {
            Element student = (Element) studentList.item(i);
            NodeList subjectList = student.getElementsByTagName("subject");

            if (subjectList.getLength() == 0) {
                System.out.println("Error 666: No subject elements found for student " + (i + 1) + "!");
                continue;
            }

            NodeList averageNodes = student.getElementsByTagName("average");
            if (averageNodes.getLength() == 0) {
                System.out.println("Warning: No average element found for student " + (i + 1) + "!");
                continue;
            }

            Element averageElement = (Element) averageNodes.item(0);
            double average = Double.parseDouble(averageElement.getTextContent());
            double trueaverage = calculateAverage(subjectList);
            if (average != trueaverage) {
                averageElement.setTextContent(String.valueOf(trueaverage));
                needfix = true;
            }
        }
        return needfix;
    }

    public static double calculateAverage(NodeList subjectList) {
        int sum = 0;
        int c = subjectList.getLength();
        for (int i = 0; i < c; i++) {
            Element subject = (Element) subjectList.item(i);
            int mark = Integer.parseInt(subject.getAttribute("mark"));
            sum += mark;
        }
        return (double) sum / c;
    }
}