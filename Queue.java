import java.util.Scanner;

public class QueueOfStrings<Items> {    /// using generics
    public class node{
        Items s;
        node next=null;
        node prev=null;
    }
    private node head = new node();
    private node tail = new node();
    private int size=0;
    public void enqueue(Items st){
        node tmp = new node();
        tmp.s=st;
        if(size==0){
            head.next=tmp;
            tmp.next=tail;
            tmp.prev=head;
            tail.prev=tmp;
        }
        else{
            tmp.next=tail;
            tmp.prev=tail.prev;
            tail.prev.next=tmp;
            tail.prev=tmp;
        }
        size++;
    }
    public void dequeue(){
        if(size==0){
            System.out.println("Queue Already Empty");
        }
        else{
            node tmp = head.next;
            head.next.next.prev=head;
            head.next=head.next.next;
            tmp.s=null;
            tmp.next=null;
            tmp.prev=null;
            size--;
        }
    }
    public void show(){
        node it = head.next;
        for(int i=0;i<size;i++){
            System.out.println(it.s);
            it=it.next;
        }
    }
    public boolean IsEmpty(){
        if(size==0){
            return true;
        }
        else{
            return false;
        }
    }
    public int returnsize(){
        return size;
    }
    public static void main(String[] args) {
        QueueOfStrings q = new QueueOfStrings();
        Scanner inp = new Scanner(System.in);
        String in = inp.next();
        while(!in.equals("-1")){
            if(in.equals("-")){
                q.dequeue();
            }
            else{
                q.enqueue(in);
            }
            q.show();
            in =inp.next();
        }
    }
}
