//Abdirabi Mohamed moha1184
//Zakaria Hussein husse285
import java.util.*;
public class Game {
    static boolean play;
    static int n;
    static int xVar;
    static int yVar;
    static String power;

    public static void main(String[] args) {

        play = true; // while loop condition for ending game
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter debug mode? Enter Y/N: ");
        String debug = sc.nextLine();
        if (debug.equalsIgnoreCase("Y")){
            System.out.println("You have entered debug mode.");
        }
        else if (debug.equalsIgnoreCase("N")){
            System.out.println("You haven't entered debug mode.");
        }
        System.out.println("Choose Game Mode: \nbeginner, intermediate or advanced");
        String input = sc.nextLine();
        System.out.println("this is the " + input + " mode: ");
        if (input.equalsIgnoreCase("beginner")) {
            Board b1 = new Board(3);
            n = 3;
            while (play) { // runs until play = false
                System.out.print("Your remaining powerpoints: ");
                System.out.println(b1.powerPoints);
                repeat();
                    b1.turns(xVar, yVar, n, power);
                if(debug.equalsIgnoreCase("Y")) {
                    b1.print();
                }
                else if (debug.equalsIgnoreCase("N")){
                    b1.display(xVar,yVar, power);
                }
                            if (b1.boatRemain == 0) { // checks if there are any more boats
                                play = false; // ends the game
                                System.out.println("this game took " + b1.turns + " turns.");
                            } else {
                                continue;
                            }
            }
            //b1.print();
        }
        else if (input.equalsIgnoreCase("intermediate")) {
            Board b1 = new Board(6);
            n = 6;
            while (play) { // runs until play = false
                repeat();
                    b1.turns(xVar, yVar, n, power);
                if(debug.equalsIgnoreCase("Y")) {
                    b1.print();
                }
                else if (debug.equalsIgnoreCase("N")){
                    b1.display(xVar,yVar, power);
                }
                            if (b1.boatRemain == 0) { // checks if there are any more boats
                                play = false; // ends the game
                                System.out.println("this game took " + b1.turns + " turns.");
                            } else {
                                continue;
                            }
            }
            //b1.print();
        }
        else if (input.equalsIgnoreCase("advanced")) {
            Board b1 = new Board(9);
            n = 9;
            while (play) { // runs until play = false
                // drone asks for x y but values are not used
                repeat();
                    b1.turns(xVar, yVar, n, power);
                if(debug.equalsIgnoreCase("Y")) {
                    b1.print();
                }
                else if (debug.equalsIgnoreCase("N")){
                    b1.display(xVar,yVar, power);
                }
                            if (b1.boatRemain == 0) { // checks if there are any more boats
                                play = false; // ends the game
                                System.out.println("this game took " + b1.turns + " turns.");
                            } else {
                                continue;
                            }
            }
            //b1.print();
        }
    }
    public static void repeat() {
        Scanner sc2 = new Scanner(System.in);
        // keeps asking for new x, y values, and any powers
        System.out.println("Enter type of attack: (fire, missile, drone)");
        power = sc2.nextLine();
        System.out.println("Enter x coordinate: ");
        xVar = sc2.nextInt() - 1;
        //System.out.print("\n");
        System.out.println("Enter y coordinate: ");
        yVar = sc2.nextInt() - 1;
    }
    /*
    public static void runGame(int x, String debug){
        Board b1 = new Board(x);
        while (play) { // runs until play = false
            System.out.print("Your remaining powerpoints: ");
            System.out.println(b1.powerPoints);
            repeat();
            if(debug.equalsIgnoreCase("Y")) {
                b1.print();
            }
            else if (debug.equalsIgnoreCase("N")){
                b1.display(xVar,yVar);
            }
            b1.turns(xVar, yVar, n, power);
            if (b1.boatRemain == 0) { // checks if there are any more boats
                play = false; // ends the game
                System.out.println("this game took " + b1.turns + " turns.");
            } else {
                continue;
            }
        }
        //b1.print();
    }

     */
}