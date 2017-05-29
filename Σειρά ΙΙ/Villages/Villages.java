/*
 * Programming Languages I - 2nd Exercise
 * Author: Michalis Papadopoullos (031-14702)
 *
 * Problem: #Villages
 * input:  N M K \n [u_i] <==> [u_j] (i != j)
 * output: minimum number of disjoint sets
 */

import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.File;

public class Villages {
    // members
    private static Scanner sc;
    private static int N,  // N < 1M : villages
                       M,  // M < 2M : total 2-way roads `a->b` and `a<-b` exist
                       K;  // K < 1M : new roads able to construct (max)

    private static UnionFindSets ufs; // our union-find structure

    // functions

    public static void init () { // Initialization routine
        N = sc.nextInt(); // read first integer
        M = sc.nextInt(); // read next
        K = sc.nextInt(); // read next

        ufs = new UnionFindSets(N); // create UnionFindSet object
                                    // of size (N + 1) --[ see internal definition of class

        parseInput(); // parse input from file into structure
    }

    public static void parseInput () { // Processing routine
        // processing...
        int   __src, // source_id
              __dst; // destination_id

        while (sc.hasNext()) { // while !EOF
            __src = sc.nextInt(); // get source_id
            __dst = sc.nextInt(); // get destination_id

            // unification process
            ufs.unify ( __src, __dst ); // path exists between `__src` and `__dst`
                                        // => update sets
        }
    }

    public static void main (String[] args) throws FileNotFoundException {
        // read from file { N, M, K }
        // N < 1M : villages
        // M < 2M : total 2-way roads `a->b` and `a<-b` exist
        // K < 1M : new roads able to construct (max)

        /*----------------------
            file.in:  7 2 2
                      1 2
                      6 5
            ==================
            file.out: 3
         ------------------------*/

        if (args.length != 1) { throw new RuntimeException("Wrong arguments\n"); }
        // set new FileReader, and parse input
        sc = new Scanner( new File ( args[0] ) );
        // input-file :: 1st argument

        init (); // initializing...

        int r = solve ();   // find solution...
        // print solution and exit
        System.out.println ( r );
    }

    public static int solve () {
        int res = ufs.getSets() - K;
        return (res > 0) ? res : 1;
    }

}
