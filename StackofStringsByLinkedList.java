import java.util.Scanner;

 class StringOfStacks {
     class node{
         String s;
         node next;
     }
     private node head= new node();
     private node tail= new node();
     private int size = 0;
     public void push(String ss){
         size++;
         node tmp = new node();
         tmp.s=ss;
         if(size==1){
             head.next=tmp;
             tmp.next=tail;
             tail.next=null;
         }
         else{
             tmp.next=head.next;
             head.next=tmp;
         }
     }
     public void pop(){
         if(size>0){
             size--;
             head.next=head.next.next;
         }
     }
     public void show(){
         node i = head.next;
         while(i.next!=null){
             System.out.println(i.s);
             i=i.next;
         }
     }
     public static void main(String[] args) {
         StringOfStacks l = new StringOfStacks();
         System.out.println("if want ot terminate press -1 else give strings");
         Scanner inp = new Scanner(System.in);
         String s = inp.next();
         while(!s.equals("-1")){
             if(s.equals("-")){
                 l.pop();
             }
             else{
                 l.push(s);
             }
             l.show();
             s=inp.next();
         }
     }
 }
