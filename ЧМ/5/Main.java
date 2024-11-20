
public class Main {
    public static void main(String[] args) {
        double[][] matrix = {
                {0.070954, -0.00009936, 0.0037446, -0.000035194},
                {-35.012, 22.264, 25.177, -0.78859},
                {232.36, 147.75, 167.09, -52.335},
                {-0.016032, -0.002245, -0.084609, 0.0079521}
        };

        System.out.println("Решение методом Леверрье: ");
        LeVerrierSolver leVerrierSolver = new LeVerrierSolver(matrix);
        leVerrierSolver.printEigenvalues();
        System.out.println("==================================================\n");

        System.out.println("Решение методом Фадеева: ");
        FadeevSolver fadeevSolver = new FadeevSolver(matrix);
        fadeevSolver.printEigenvalues();
        System.out.println("==================================================\n");

        System.out.println("Решение методом Крылова: ");
        KrylovSolver krylovSolver = new KrylovSolver(matrix);
        krylovSolver.printEigenvalues();
    }
}
