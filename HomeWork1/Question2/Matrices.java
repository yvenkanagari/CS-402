import java.util.Random;
public class Matrices {
    public static void main(String[] args) {

        int i,j,k;
        double sum=0;
        Random r=new Random();
        int[][] a=new int[200][300];
        double[][] b=new double[300][500];
        double[][] c=new double[200][500];

        long startTime = System.nanoTime();
		// Matrix a
        System.out.println("\n Matrix a:");
        for(i=0;i<200;i++) {
            for (j = 0; j < 300; j++) {
                a[i][j] = r.nextInt(100);
                System.out.print(a[i][j]+ "  ");
            }
            System.out.print("\n");
        }
		// Matrix b
        System.out.println("\n Matrix b:");
            for(i=0;i<300;i++)
            {
                for(j=0;j<500;j++)
                {
                    b[i][j]= r.nextDouble();
                    System.out.print(b[i][j]+ "  ");
                }
                System.out.print("\n");
        }

        // multiplying the two matrices
        for(i=0; i<200; i++)
        {
            for(j=0; j<500; j++)
            {
                sum = 0;
                for(k=0; k<300; k++)
                {
                    sum = sum + (a[i][k] * b[k][j]);
                }
                c[i][j] = sum;
            }
        }
		
        System.out.println("\nMultiplication Result of Two Matrices is:");
        for(i=0; i<200; i++)
        {
            for(j=0; j<500; j++)
            {
                System.out.print(c[i][j]+ "  ");
            }
            System.out.print("\n");
        }
		
        long endTime = System.nanoTime();
		
	    //Calculate Program Execution Time
        long duration = (endTime - startTime);
        double timeInSeconds = (double) duration / 1_000_000_000;
        System.out.print("\nExecution Time :"+ timeInSeconds + " Seconds");

    }
}
