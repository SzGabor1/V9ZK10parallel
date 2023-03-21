package Package;

import java.io.IOException;
import java.util.Random;
import static Package.MatrixFileIO.writeMatrix;

public class WriteMatrixThread extends Thread
{
    int num_of_matrices;
    int matrix_size;

    public WriteMatrixThread(int num_of_matrices, int matrixSize) {
    this.num_of_matrices = num_of_matrices;
    matrix_size = matrixSize;
    }

    public void run()
    {
        System.out.println("Thread is running...");
        try {

            for(int i = 0; i < num_of_matrices; i++){

                writeMatrix("matrix"+i+".txt", getMatrix(matrix_size));

            }

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }


    static int[][] getMatrix(int matrix_size){
        Random r=new Random();
        int[][] matrix=new int[matrix_size][matrix_size];
        for(int i=0;i<matrix_size;i++)
        {
            for(int j=0;j<matrix_size;j++)
            {
                matrix[i][j]=r.nextInt(200);
            }
        }
        return matrix;
    }
}