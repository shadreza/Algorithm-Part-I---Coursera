import java.util.Scanner;
public class StackOfStrings{
    private int totalsize =0;
    private int usedsize = 0;
    String[] arrayofstrings;
    StackOfStrings(int size){
        totalsize=size;
        arrayofstrings = new String[size];
    }
    public void push(String s){
        if(usedsize>=totalsize){
            System.out.println("Stack is Full");
            return;
        }
        arrayofstrings[usedsize]=s;
        usedsize++;
        System.out.println("Successful");
    }
    public void pop(){
        if(usedsize<=0){
            System.out.println("Stack already empty");
            return;
        }
        arrayofstrings[usedsize-1]=null;
        usedsize--;
        System.out.println("Successful");
    }
    public void show(){
        for(int i=usedsize;i>0;i--){
            System.out.println(arrayofstrings[i-1]);
        }
    }
    public static void main(String[] args) {
        Scanner inp = new Scanner(System.in);
        System.out.println("Size?");
        int size = inp.nextInt();
        StackOfStrings s = new StackOfStrings(size);
        String ss = inp.next();
        while(!ss.equals("-1")){
            if(ss.equals("-")){
                s.pop();
            }
            else{
                s.push(ss);
            }
            s.show();
            ss=inp.next();
        }
    }
}
