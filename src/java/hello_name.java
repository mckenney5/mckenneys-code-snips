/*
 * JAVA (Requires Java Runtime Environment (jre)
 * Asks for the users name and says hi
 * compile: javac java.java
*/

import java.util.Scanner; // used for taking user input

public class java{
	public static void main(String args[]){
		// display prompt
		System.out.print("Enter your name: ");
		
		// get users name
		Scanner input = new Scanner(System.in);
		String name;
		name = input.nextLine();

		// say hello
		System.out.println("Hello " + name + "!");
	}
}
