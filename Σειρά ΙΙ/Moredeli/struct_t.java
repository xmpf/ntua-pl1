/*  Author: Michalis Papadopoullos (03114702)
 *            < el14702 '@' mail.ntua.gr >
 *
 *   Notes: Custom class `struct_t`
 *                           -> cost (int)
 *                           -> x    (int)
 *                           -> y    (int)
 *                           -> path (String)
 *
 *   Data structure to use as the element-type
 *   of a PriorityQueue structure in `Moredeli.java` file
 *
 */
public class struct_t  {
    // members

    private int cost;
    private String path = "";
    private int x, // coordX
                y; // coordY


    // constructor
    public struct_t (int c, int X, int Y, String p) {
        this.cost = c;
        this.x = X;
        this.y = Y;
        this.path = this.path.concat(p);
    }

    // methods

    public int getX() { return this.x; }
    public int getY() { return this.y; }
    public int getCost() { return this.cost; }
    public String getPath() { return this.path; }
}
