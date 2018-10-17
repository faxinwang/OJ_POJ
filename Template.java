import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Template 
{
	static Scanner sc;
	static
	{
		try {
			sc = new Scanner(new File("./math/in.txt"));
		}catch(FileNotFoundException e){ sc = new Scanner(System.in); }
	}
	
	public static void main(String[] args) throws FileNotFoundException
	{
		
		
		
		
		
		sc.close();
	}

}
