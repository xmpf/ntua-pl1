/*  Author: Michalis Papadopoullos (03114702)
 *            < el14702 '@' mail.ntua.gr >
 *
 *  Programming Languages I - 2nd Exercise (#Moredeli)
 *   src/
 *      --/ Moredeli.java
 *      --/ struct_t.java
 *
 *   Invoke: java Moredeli <input-file>
 *
  \
  |    Todo:
  |       [-] Code optimizations (overhead on storing/computing path for each traversal)
  |       [-] Write comments according to `JavaDoc` manual
  |
  |
 */


// imports

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Scanner;
import java.util.Vector;

// main class
public class Moredeli {
    // members

    private static boolean DEBUG = false;
    private static Scanner sc; // scanner
    private static Vector<String> map; // map
    private static PriorityQueue<struct_t> pq;
    private static int[][] V; // adjacent costs
    private static int[] _src = new int[2],
                         _dst = new int[2];
    private static int COLS = 0,
                       ROWS = 0;

    // methods
    public static void init () {
        // initialization routine
        map = new Vector<String>(); // allocate space for Vector<String> :: `map`
        Comparator<struct_t> cmp = new Comparator<struct_t>() {
            @Override
            public int compare (struct_t a, struct_t b) {
                return (a.getCost() - b.getCost());
            }
        };
        pq = new PriorityQueue<struct_t>(cmp); // get space for our PriorityQueue

        parseInput (); // parse input from file given as argument
    }

    public static void parseInput () {
        // parse input from file
        while (sc.hasNext()) { // while not(EOF)
            map.add (sc.nextLine()); // push_back (line)
        }

        // create "protection-wall" for map
        // by surrounding map with 'X's
        // no need to check for bounds
        COLS = map.get(0).length(); // total columns
        ROWS = map.size();          // total rows
                                    // `map` ROWS x COLS => (ROWS+2) x (COLS + 2)
        /*
        Vector<String> map__ = new Vector<String>(); // temporary copy
        String wall = new String("");   // create new String object
        for (int i = 0; i < COLS + 2; i++) { wall = wall.concat("X"); } // construct wall string
        map__.add(wall); // insert first row
        for (int i = 0; i < ROWS; i++) { map__.add("X" + map.get(i) + "X"); } // foreach row append `X`

        COLS += 2; // due to wall
        ROWS += 2; // protection

        map.removeAllElements(); // remove all elements from previous vector
        map = map__; // change reference of `map` -> `map__`
        map.add(wall); // insert last row
        */
        if (DEBUG) printMap (); // print map (DEBUGGING)

        process(); // call processing routine
    }

    public static boolean checkXY (struct_t c) {
        if ( c.getX() == _dst[0] &&
             c.getY() == _dst[1] )
        { return true; }

        return false;
    }

    public static void process () { // processing routine
        V = new int[ROWS][COLS];
        // find `source` and `destination` nodes
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                V[i][j] = Integer.MAX_VALUE;
                char c = map.get(i).charAt(j);
                if ( c == 'S' ) {
                    _src[0] = i; // save row
                    _src[1] = j; // save column
                }
                else if ( c == 'E' ) { // found destination
                    _dst[0] = i; // save row
                    _dst[1] = j; // save column
                }}}

        solve(); // call solve routine
    }

    public static void printSolution (struct_t t) {
        System.out.println (t.getCost() + " " + t.getPath());
    }

    public static void possibleMoves (struct_t t) {
        String[] _dir = { "L", "R", "U", "D" }; // Step directions
        int[] _dx = {0, 0, -1, 1},  // offset
              _dy = {-1, 1, 0, 0},  // offset
              _dc = {2, 1, 3, 1};   // cost

        for (int i = 0; i < 4; i++) { // for all possible moves
            int x = t.getX() + _dx[i];
            int y = t.getY() + _dy[i];
            int steps = t.getCost() + _dc[i];

            if (x < 0 || x >= ROWS) { continue; }
            if (y < 0 || y >= COLS) { continue; }

            if ( map.get(x).charAt(y) != 'X') { // if accessible then
                if ( V[x][y] > steps ) { // add new path
                    pq.add(new struct_t( steps, x, y, t.getPath() + _dir[i] ));
                }
            }

        }
    }

    public static void solve() {
        pq.add(new struct_t(0, _src[0], _src[1], "")); // initial element

        while( !pq.isEmpty() ) { // while there is still something
            struct_t t = pq.poll(); // retrieve & remove `head`

            if ( checkXY(t) ) { // found `destination`
                printSolution (t); // print solution
                return; // and return
            }

            // check adjacent nodes
            if ( V[t.getX()][t.getY()] <= t.getCost() )
                continue;

            V[t.getX()][t.getY()] = t.getCost();
            possibleMoves (t);
        }
        System.out.println ("Not possible");
    }

    public static void printMap () { // for DEBUGGING purposes
        for (int i = 0; i < ROWS; i++) {
            System.out.println (map.get(i));
        }
        System.out.println(ROWS + "x" + COLS);
    }

    // Main
    public static void main (String args[]) {
        // wrong arguments
        if (args.length != 1) { throw new RuntimeException("Too many arguments\n"); }
        // assign file
        try { sc = new Scanner( new File(args[0]) ); }
        catch (FileNotFoundException f) { System.out.format("Error: %s\n", f.toString() ); }

        // init
        init ();

    }
}
