public class Matrix {
    private double[][] data;
    private int rows;
    private int columns;

    public Matrix(double[][] data) {
        this.data = data;
        this.rows = data.length;
        this.columns = data[0].length;
    }

    public int getRows() {
        return rows;
    }

    public int getColumns() {
        return columns;
    }

    public double[][] getData() {
        return data;
    }

    public void printMatrix() {
        for (double[] row : data) {
            for (double value : row) {
                System.out.printf("%10.6f", value);
            }
            System.out.println();
        }
    }

    public Matrix transpose() {
        double[][] transposed = new double[columns][rows];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                transposed[j][i] = data[i][j];
            }
        }
        return new Matrix(transposed);
    }

    public Matrix multiply(Matrix other) {
        double[][] result = new double[rows][other.columns];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.columns; j++) {
                for (int k = 0; k < columns; k++) {
                    result[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return new Matrix(result);
    }

    public static Matrix identity(int size) {
        double[][] identity = new double[size][size];
        for (int i = 0; i < size; i++) {
            identity[i][i] = 1.0;
        }
        return new Matrix(identity);
    }
}
