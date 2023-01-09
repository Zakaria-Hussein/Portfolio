//Abdirabi Mohamed moha1184
//Zakaria Hussein husse285
import java.util.*;
public class Board {
    Cell [][] a;
    Cell [][] a2; // for print
    Boat [] b;
    int nextEmpty;
    int boatRemain;
    int turns;
    int powerPoints;

    public Board(int n) {
        a = new Cell[n][n];
        a2 = new Cell[n][n];
        // Boat sizes for each game mode
        int[] beg = {2};
        int[] med = {2, 3, 4};
        int[] exp = {2, 3, 3, 4, 5};
        for (int i = 0; i < a[0].length; i++) {
            for (int j = 0; j < a[0].length; j++) {
                // initializes each cell on the board with row, col, and no boat status
                Cell c1 = new Cell(i, j, '-');
                a[i][j] = c1;
            }
        }
        // for print method
        for (int i = 0; i < a2[0].length; i++) {
            for (int j = 0; j < a2[0].length; j++) {
                // initializes each cell on the board with row, col, and no boat status
                Cell c1 = new Cell(i, j, ' ');
                a2[i][j] = c1;
            }
        }
        nextEmpty = 0;
        turns = 0;
        if (n == 3) {
            // keeps track of # of boats
            boatRemain = beg.length;
            powerPoints = 1;
            randomPlaceBoats(beg, n);
        }
        if (n == 6) {
            boatRemain = med.length;
            powerPoints = 3;
            randomPlaceBoats(med, n);
        }
        if (n == 9) {
            boatRemain = exp.length;
            powerPoints = 5;
            randomPlaceBoats(exp, n);
        }
    }
    public void randomPlaceBoats(int[] arr, int x){
        b = new Boat[arr.length];
        for (int i = 0; i < arr.length; i++) {
            // calls placeBoats for each boat in the given array
            placeBoats(arr[i], x);
        }
    }

    public void placeBoats(int s, int n){

            boolean t = false;
            Cell[] c1 = new Cell[s]; // Boat attribute Cell array
            while (t == false) {
                int way = (int) (Math.random() * 2); // way = orientation (horizontal/vertical)
                // 0 = horizontal
                // 1 = vertical
                if (way == 0) {
                    // chooses random x, y value within bounds depending on size of boat
                    int x = (int) (Math.random() * n);
                    int y = (int) (Math.random() * (n - s));
                    boolean ch = check(x,y,s, way); // checks if the boat will overlap with any others
                    if (ch == true) {
                        for (int j = 0; j < s; j++) {
                            a[x][y + j].setStatus('B');
                            c1[j] = a[x][y+j];
                            // changes the status of the cell to Boat present and add to the cell array
                        }
                        Boat b1 = new Boat(s, false, c1);
                        // creates Boat
                        // false = horizontal
                        b[nextEmpty] = b1; // adds boat to empty space in Boat array
                        nextEmpty++;
                    }
                    else{placeBoats(s,n);}
                    // if boat will overlap calls place boats again with same values
                    // to reroll the x, y values
                    t = true;// ends loop
                }
                else if (way == 1) {
                    int x = (int) (Math.random() * (n-s));
                    int y = (int) (Math.random() * n);
                    boolean ch = check(x,y,s, way);
                    if (ch == true) {
                        for (int j = 0; j < s; j++) {
                                a[x+j][y].setStatus('B');
                                c1[j] = a[x+j][y];
                            }
                        Boat b1 = new Boat(s, true, c1);
                        b[nextEmpty] = b1;
                        nextEmpty++;
                    }
                    else {placeBoats(s, n);}
                    t = true;
                }
            }
        }

        public boolean check(int x, int y, int size, int way) {
            boolean t = true;
            if (way == 0) {
                // checks if the space for the boat will be open
                for (int j = 0; j < size; j++) {
                    if (a[x][y + j].getStatus() != '-') {
                        t = false;
                    }
                }
            } else if (way == 1) {
                for (int j = 0; j < size; j++) {
                    if (a[x + j][y].getStatus() != '-') {
                        t = false;
                    }
                }
            }
            return t;// true if space is open
        }

        public void print(){
        // prints out each cell status
            for (int i = 0; i < a[0].length; i++) {
                for (int j = 0; j < a[0].length; j++) {
                    System.out.print(a[i][j].getStatus() + " | ");
                }
                System.out.print("\n");
            }
        }
    public void display(int x, int y, String power){
        // space character represents unknown value, don't know if boat is there or not.
        System.out.println("this is the display");
        // shows empty board and fills in status of cells that are hit
        a2[x][y].setStatus(a[x][y].getStatus());
        if (power.equals("fire")) {
            for (int i = 0; i < a2[0].length; i++) {
                for (int j = 0; j < a2[0].length; j++) {
                    System.out.print(a2[i][j].getStatus() + " | ");
                }
                System.out.print("\n");
            }
        }
        else if (power.equalsIgnoreCase("missile")) {
            for (int i = x - 1; i <= x + 1; i++) {
                for (int j = y - 1; j <= y + 1; j++) {
                    if (i >= 0 && i < Game.n - 1 && j >= 0 && j < Game.n) {
                        a2[i][j].setStatus(a[i][j].getStatus());
                    }
                }
            }
            for (int i = 0; i < a2[0].length; i++) {
                for (int j = 0; j < a2[0].length; j++) {
                    System.out.print(a2[i][j].getStatus() + " | ");
                }
                System.out.print("\n");
            }
        }
    }

    public void turns(int x, int y, int n, String s){
        // named the fire method turns
        if (s.equalsIgnoreCase("fire")) {
            turns++; // keeps track of turns
            if (x < n && y < n) {
                if (a[x][y].getStatus() == '-') {
                    a[x][y].setStatus('M');
                    System.out.println("miss");
                } else if (a[x][y].getStatus() == 'B') {
                    a[x][y].setStatus('H');
                    System.out.println("hit");
                    boolean ch = checkSunk();
                    if (ch == false) {
                        System.out.println("sunk");
                        boatRemain--;
                        // if boat is sunk subtracts 1 from total boats
                    }
                }
                else { // applies penalty for choosing x,y values out of bounds
                    System.out.println("penalty");
                    turns += 2;
                }
            }
            else if (a[x][y].getStatus() == 'H' || a[x][y].getStatus() == 'M') {
                // if spot chosen has already been hit increase turns by 1 as penalty
                System.out.println("penalty");
                turns++;
            }
            //display(x, y);
        }
        else if (s.equalsIgnoreCase("missile")){
            missile(x, y, n);
        }
        else if (s.equalsIgnoreCase("drone")){
            turns++;
            drone(n);
        }
    }

    public void missile(int x, int y, int n) {
        if (powerPoints == 0) {
            System.out.println("no power points left");
            return;
        }
        else {
            turns++;
            powerPoints--;
            boolean hit = true;
            while (hit == true) {
                if (x < n && y < n) {
                    //updates 3x3 grid around x,y
                    for (int i = x - 1; i <= x + 1; i++) {
                        for (int j = y - 1; j <= y + 1; j++) {
                            if (i >= 0 && i < n && j >= 0 && j < n) {
                                turns--;
                                turns(i, j, n, "fire");
                            }
                        }
                    }
                } else {
                    System.out.println("Try again ");
                    Scanner sc2 = new Scanner(System.in);
                    System.out.println("Enter x coordinate: ");
                    x = sc2.nextInt();
                    System.out.println("Enter y coordinate: ");
                    y = sc2.nextInt();
                    missile(x, y, n);
                }
                hit = false;
            }
        }
    }
    public void drone(int n) {
        // drone asks for x y but values are not used
        if (powerPoints == 0) {
            System.out.println("no power points left");
            return;
        } else {
            Cell[][] a3 = new Cell[n][n];
            for (int i = 0; i < a3[0].length; i++) {
                for (int j = 0; j < a3[0].length; j++) {
                    // initializes each cell on the board with row, col, and no boat status
                    Cell c1 = new Cell(i, j, ' ');
                    a3[i][j] = c1;
                }
            }
            int rc = (int) (Math.random() * 2);
            if (rc == 0) { // row
                int x = (int) (Math.random() * n);
                for (int i = 0; i < a3[0].length; i++) {
                    for (int j = 0; j < a3[0].length; j++) {
                        a3[x][j].setStatus(a[x][j].getStatus());
                    }
                }
            } else if (rc == 1) { // col
                int y = (int) (Math.random() * n);
                for (int i = 0; i < a3[0].length; i++) {
                    for (int j = 0; j < a3[0].length; j++) {
                        a3[j][y].setStatus(a[j][y].getStatus());
                    }
                }
            }
            System.out.println("this is drone");
            for (int i = 0; i < a3[0].length; i++) {
                for (int j = 0; j < a3[0].length; j++) {
                    System.out.print(a3[i][j].getStatus() + " | ");
                }
                System.out.print("\n");
            }
            powerPoints--;
            System.out.println(powerPoints);
        }
    }

    public boolean checkSunk(){
        for (int i = 0; i < b.length; i++){
            int h = 0;
            if (b[i] == null){
                continue;// if boat is null moves to the next
            }

            for (int j = 0; j < b[i].c.length; j++){
                if (b[i].c[j].getStatus() == 'H'){
                    h++;
                    // h keeps track of the number of hit cells for each boat
                    if (h == b[i].getSize()) {
                        // if the boat is sunk h == size of the boat
                        b[i] = null;
                        return false;
                    }

                }
            }

        }
        return true;// false means boat sunk
    }
        }

