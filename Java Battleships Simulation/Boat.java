//Abdirabi Mohamed moha1184
//Zakaria Hussein husse285
public class Boat{

    int size;
    boolean orientation; // true = vertical
    Cell [] c;

    public Boat(int s, boolean orient, Cell [] b){
        size = s;
        orientation = orient;
        c = b;
    }
    public void setSize(int s){
        size = s;
    }
    public int getSize(){
        return size;
    }
    public void setOrientation(boolean orient){
        orientation = orient;
    }
    public boolean getOrientation(){
        return orientation;
    }
}