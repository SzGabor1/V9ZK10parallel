package Package;

import java.io.IOException;

import static Package.MatrixFileIO.readMatrix;
import static Package.MatrixFileIO.writeMatrix;

public class DetOfMatrixThread extends Thread {
    int num_of_matrices;

    public DetOfMatrixThread(int num_of_matrices) {
        this.num_of_matrices = num_of_matrices;
    }

    public void run()
    {
        System.out.println("Thread is running...");
        try {

            for(int i = 0; i < num_of_matrices; i++){

                System.out.println("Determinant of matrix "+i+" is: "+calculateDeterminant(readMatrix("matrix"+i+".txt")));

            }

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static int calculateDeterminant(int[][] matrix) {
        int det = 0;
        int n = matrix.length;

        if (n == 1) {
            det = matrix[0][0];
        } else if (n == 2) {
            det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        } else {
            for (int i = 0; i < n; i++) {
                int[][] submatrix = new int[n - 1][n - 1];

                for (int j = 1; j < n; j++) {
                    for (int k = 0; k < n; k++) {
                        if (k < i) {
                            submatrix[j - 1][k] = matrix[j][k];
                        } else if (k > i) {
                            submatrix[j - 1][k - 1] = matrix[j][k];
                        }
                    }
                }

                det += Math.pow(-1, i) * matrix[0][i] * calculateDeterminant(submatrix);
            }
        }

        return det;
    }

}
