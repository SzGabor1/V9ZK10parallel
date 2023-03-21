package Package;

import java.io.IOException;

import static Package.MatrixFileIO.readMatrix;
import static Package.MatrixFileIO.writeMatrix;

public class PrintMatrixThread extends Thread {
    int num_of_matrices;
    PrintMatrixThread(int num_of_matrices) throws IOException {
        this.num_of_matrices=num_of_matrices;
    }


    public void run()
    {
        System.out.println("Thread is running...");
        try {

            for(int i = 0; i < num_of_matrices; i++){

                printMatrix(i);

            }

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }



  public void printMatrix(int i) throws IOException {

      System.out.printf("Matrix %d: %n", i);
          int[][] readMatrix = readMatrix("matrix"+i+".txt");
          for (int[] row : readMatrix) {
              for (int col : row) {
                  System.out.print(col + " ");
              }
              System.out.println();
          }

}
}
