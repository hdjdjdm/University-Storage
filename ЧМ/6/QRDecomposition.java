public class QRDecomposition {
    private static final double EPSILON = 0.0001;

    public void findEigenvaluesAndEigenvectors(Matrix matrix) {
        int n = matrix.getRows();
        Matrix A = matrix;
        Matrix QTotal = Matrix.identity(n);

        for (int iteration = 0; iteration < 100; iteration++) {
            QRResult qrResult = decomposeQR(A);
            Matrix Q = qrResult.getQ();
            Matrix R = qrResult.getR();

            A = R.multiply(Q);
            QTotal = QTotal.multiply(Q);

            if (hasConverged(A)) {
                System.out.println("Собственные значения:");
                for (int i = 0; i < n; i++) {
                    System.out.printf("λ%d = %.5f%n", i + 1, A.getData()[i][i]);
                }
                System.out.println("==================================================");

                System.out.println("Матрица Q");
                Q.printMatrix();
                System.out.println("==================================================");

                System.out.println("Матрица R");
                R.printMatrix();
                System.out.println("==================================================");

                System.out.println("Собственные значения:");
                QTotal.printMatrix();
                System.out.println("==================================================");

                System.out.println("Собственные векторы:");
                QTotal.printMatrix();
                return;
            }
        }

        System.out.println("Не удалось найти собственные значения за заданное количество итераций.");
    }

    private QRResult decomposeQR(Matrix A) {
        int n = A.getRows();
        double[][] qData = new double[n][n];
        double[][] rData = new double[n][n];

        for (int j = 0; j < n; j++) {
            double[] v = new double[n];
            for (int i = 0; i < n; i++) {
                v[i] = A.getData()[i][j];
            }

            for (int i = 0; i < j; i++) {
                double r_ij = 0;
                for (int k = 0; k < n; k++) {
                    r_ij += qData[k][i] * v[k];
                }
                rData[i][j] = r_ij;
                for (int k = 0; k < n; k++) {
                    v[k] -= r_ij * qData[k][i];
                }
            }

            double r_jj = 0;
            for (int k = 0; k < n; k++) {
                r_jj += v[k] * v[k];
            }
            r_jj = Math.sqrt(r_jj);
            rData[j][j] = r_jj;

            for (int k = 0; k < n; k++) {
                qData[k][j] = v[k] / r_jj;
            }
        }

        Matrix Q = new Matrix(qData);
        Matrix R = new Matrix(rData);

        return new QRResult(Q, R);
    }

    private boolean hasConverged(Matrix A) {
        for (int i = 0; i < A.getRows() - 1; i++) {
            if (Math.abs(A.getData()[i + 1][i]) > EPSILON) {
                return false;
            }
        }
        return true;
    }

    private static class QRResult {
        private Matrix Q;
        private Matrix R;

        public QRResult(Matrix Q, Matrix R) {
            this.Q = Q;
            this.R = R;
        }

        public Matrix getQ() {
            return Q;
        }

        public Matrix getR() {
            return R;
        }
    }
}
