package Package;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class MatrixFileIO {

    // Method to read a matrix from a text file
    public static int[][] readMatrix(String fileName) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader(fileName));
        String line = reader.readLine(); // Read the first line
        String[] size = line.split("\\s+"); // Split the line into an array of strings
        int numRows = Integer.parseInt(size[0]);
        int numCols = Integer.parseInt(size[1]);
        int[][] matrix = new int[numRows][numCols];
        int row = 0;
        while ((line = reader.readLine()) != null) {
            String[] elements = line.split("\\s+");
            for (int col = 0; col < numCols; col++) {
                matrix[row][col] = Integer.parseInt(elements[col]);
            }
            row++;
        }
        reader.close();
        return matrix;
    }

    // Method to write a matrix to a text file
    public static void writeMatrix(String fileName, int[][] matrix) throws IOException {
        BufferedWriter writer = new BufferedWriter(new FileWriter(fileName));
        writer.write(matrix.length + " " + matrix[0].length + "\n");
        for (int[] row : matrix) {
            for (int col : row) {
                writer.write(col + " ");
            }
            writer.write("\n");
        }
        writer.close();
    }


}
