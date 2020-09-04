import java.util.Scanner;
public class StackOfStrings{
    private int totalsize =0;
    private int usedsize = 0;
    String[] arrayofstrings;
    StackOfStrings(){
        totalsize=2;
        arrayofstrings = new String[2];
    }
    public void push(String s){
        if(usedsize>=totalsize){
            System.out.println("Stack is Full");
            return;
        }
        arrayofstrings[usedsize]=s;
        usedsize++;
        if(usedsize==totalsize){
            totalsize*=2;
            String[] tmp = new String[totalsize];
            for(int i=0;i<usedsize;i++){
                tmp[i]=arrayofstrings[i];
            }
            arrayofstrings=tmp;
        }
        System.out.println("Successful");
    }
    public void pop(){
        if(usedsize<=0){
            System.out.println("Stack already empty");
            return;
        }
        arrayofstrings[usedsize-1]=null;
        usedsize--;
        if(usedsize<=totalsize/4){
            totalsize/=2;
            String[] tmp = new String[totalsize];
            for(int i=0;i<usedsize;i++){
                tmp[i]=arrayofstrings[i];
            }
            arrayofstrings=tmp;
        }
        System.out.println("Successful");
    }
    public void show(){
        for(int i=usedsize;i>0;i--){
            System.out.println(arrayofstrings[i-1]);
        }
        System.out.println("Total "+totalsize+" Used "+usedsize);
    }
    public static void main(String[] args) {
        Scanner inp = new Scanner(System.in);
        StackOfStrings s = new StackOfStrings();
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
