//Program to create specific objects of the class based on given two arrays. (understanding inheritance and objects creation)
//if both values in the array are same, then create square class object
//if both values in the array are different, then create rectangle class object
///if one of the value in the array is 0, then create circle object


//Shape.java:
public abstract class Shape
{
protected int s1;
	public abstract double area();
}//end of Shape class


//Square.java:
public class Square extends Shape  //inherits Shape
{
	public Square(int s)
	{
		this.s1=s;
	}
	public double area()
	{
		return s1*s1;
	}
}//end of Square class



//Rectangle.java:
public class Rectangle extends Shape
{
	private int s2;
	public Rectangle(int s1, int s2)
	{
		this.s1=s1;
		this.s2=s2;
	}
	public double area()
	{
		return s1*s2;
	}
}//end of Rectangle class



//Circle.java:
public class Circle extends Shape
{
	public Circle(int r)
	{
		this.s1=r;
	}
	public double area()
	{
		return 3.14 * s1 * s1;
	}

}//end of Circle class



//driver class:
public class Main
{
	public static void main(String[] args)
	{
		int A[]= {10,22,9,8,4,5,33,7,9,12};
		int B[]= {14,0, 0,8,4,9,33,0,21,30};
		double[] result=new double[10];
		if(A.length != B.length)
			System.exit(0);
		Shape s[] = new Shape[10];
		for(int i=0;i<A.length;i++)
		{
			if(A[i] == B[i])
			{
				s[i]=(Shape) new Square(A[i]);
				result[i]=s[i].area();
			}
			else if(B[i] == 0)
			{
				s[i]= new Circle(A[i]);
				result[i]=s[i].area();
			}
			else
			{
				s[i]=new Rectangle(A[i],B[i]);
				result[i]=s[i].area();
			}
		}
		for(int i=0;i<A.length;i++)
			System.out.println(result[i]+" ");

	}//end of main

}//end of class
