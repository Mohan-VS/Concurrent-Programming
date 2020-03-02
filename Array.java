//program to find a sum of two values in an array which is key.
import java.util.Scanner;
public class ArrayWrite
{
	public int A[];
	public ArrayWrite(int n)
	{
		A=new int[n];
	}
	public void write()
	{
		Scanner sc=new Scanner(System.in);
		System.out.print("Enter elements: ");
		for(int i=0;i<A.length;i++)
		{
			A[i]=sc.nextInt();
		}
	}
	public void show()
	{
		for(int i=0;i<A.length;i++)
		{
			System.out.println(A[i]+" ");
		}
	}
	public int[] check_sum(int t, int[] A)
	{
		int[] R = new int[2];
		for(int i=0;i<A.length;i++)
		{
			for(int j=0;j<A.length;j++)
			{
				if(A[i]+A[j] == t)
				{
					R[0]=j;
					R[1]=i;
				}
			}	
		}
		return R;
	}//end of method check_sum
}//end of class



//Driver class

import java.util.Scanner;
public class First
{
	public static void main(String[] args)
	{
		Scanner sc=new Scanner(System.in);
		//declaring arrays for storing result
		int[] R1=new int[2];
		int[] R2=new int[2];
		System.out.print("Enter array size:");
		int len=sc.nextInt();
		ArrayWrite obj=new ArrayWrite(len);
		obj.write();
		System.out.print("Enter key:");
		int t = sc.nextInt();    //value of t 
		
		//System.out.println("Array values are ");  //printing array
		//obj.show();
		//calling method and storing result in array
		System.out.println("\nCalling method first time result is");
		R1 = obj.check_sum(t, obj.A);   
		System.out.println("Sum of "+ t +" in Array are of index ["+R1[0]+","+R1[1]+"]");
		
		System.out.print("Enter another key: ");
		int t1 = sc.nextInt();
		System.out.println("\nCalling method second time result is");
		R2 = obj.check_sum(t1, obj.A);  
		System.out.println("Sum of "+ t1 +" in Array are of index ["+R2[0]+","+R2[1]+"]");
	}//end of main
}//end of class
