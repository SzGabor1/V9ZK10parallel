package Package;

import java.io.IOException;
import java.util.Random;

import static Package.MatrixFileIO.readMatrix;
import static Package.MatrixFileIO.writeMatrix;




public class Main {


    public static void main(String[] args) {




        int num_of_matrices = 10;

        int matrix_size = 2;




        try {

            WriteMatrixThread thread1=new WriteMatrixThread(num_of_matrices,matrix_size);
            PrintMatrixThread thread2=new PrintMatrixThread(num_of_matrices);
            DetOfMatrixThread thread3=new DetOfMatrixThread(num_of_matrices);

            thread1.start();
            thread2.start();
            try
            {
                thread1.join();
                thread2.join();
            }catch(Exception e){System.out.println(e);}
            thread3.start();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }


    }



}

