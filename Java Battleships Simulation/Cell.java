//Abdirabi Mohamed moha1184
//Zakaria Hussein husse285
public class Cell{

    private int row;
    private int col;
    private char status;


    public Cell(int r, int c, char st){
        row = r;
        col = c;
        status = st;
    }
    public void setStatus(char c){
        status = c;
    }
    public char getStatus(){
        return status;
    }
    public void setRow(int r){
        row = r;
    }
    public int getRow(){
        return row;
    }
    public void setCol(int c){
        col = c;
    }
    public int getCol(){
        return col;
    }
}