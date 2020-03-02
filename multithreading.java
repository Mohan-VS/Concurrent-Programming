//multithreading used to find sum of two arrays in Java


import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
public class Second
{
	public static void main(String[] args)
	{
		//creating executor service and executing them
		ExecutorService es = Executors.newCachedThreadPool();
		Method m=new Method();
		es.execute(m);
		es.execute(m);
		es.execute(m);
		m.show();
		es.shutdown();
	}//end of main
}//end of class



//Method.java:
public class Method implements Runnable
{
//declaring and assigning values to arrays
	public int A[]={0,1,2,3,4,5,6,7,8,9};
	public int B[]={1,2,3,4,5,6,7,8,9,0};
	public int C[]=new int[10];
	@Override
	public void run()
	{
		add();
	}
	public synchronized void add()
	{
		for(int i=0;i<A.length; i++)
		{
			C[i]=A[i]+B[i];
		}
	}
public void show()
	{
		for(int i=0;i<C.length; i++)
		{
			System.out.println(C[i]+" ");
		}
	}//end of methods
}//end of class
