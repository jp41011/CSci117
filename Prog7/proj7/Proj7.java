/**
 * Juan Pedraza - CSci 117 - Prog7
 * The purpose of this project is to practice concurrent programming with Java threads.
 * We will have:
 * 2 - serially reusable resources (SR)
 * 	- one with 3 units and the other with 2 units
 * 6 - concurrent process in the system that each will need to acquire
 * 1 unit of each SR to be able to accomplish its task, currently not task yet just acquire both SR
 * Once the process has acquired both SR it will then release the units.
 * 
 */
package proj7;

//import java.util.Scanner; // to get user input
import java.util.Vector;
import java.util.Random;

//import java.io.*; // read and write files

// Main project class hold the programs main method
public class Proj7 
{
	/**
	 * Main method that will create the 6 process threads and then start all of them.
	 */
	public static void main(String[] args) {
		
		// Create 2 Resources
		Resource1 r1 = new Resource1();
		Resource2 r2 = new Resource2();
		
		// vector to hold the threads of type process
		Vector<Process> threadVec = new Vector<Process>();	
		
		// loop to go through and create 6 process threads
		for(int i=1; i <= 6; i++)
		{	
			// create new process thread and add to the vector
			threadVec.add(new Process(i, r1, r2));
			//threadVec[i-1].start();
			threadVec.get(i-1).start(); // call start for the newly created thread
		}
		
	} // end of Main()

} // end of Proj7

/* Resource1 class
 * Will represent the 3 red pens
 */
class Resource1
{
	// resource name
	private static String name = "Red Pen(s)";
	// number of available resources
	private static int free = 3;
	
	// constructor - prints out message
	public Resource1()
	{
		//do something here
		System.out.println("Created Resource1");
		System.out.println("\tName: "+ Resource1.name);
		System.out.println("\tStock: " + Resource1.free);
	}
	
	/* function used to acquire a unit from this resource.
	 * Will reduce the number of free units by 1
	 * If not units are left to be acquired then will have the thread wait()
	 * unit a unit becomes available.
	*/
	public synchronized void acquire(int id)
	{
		if(free <= 0) // no free resource
		{
			// then have to wait until a resource becomes available
			try{
				System.out.println("+process_" + id + " waiting for " + Resource1.name);
				wait();
			}catch(InterruptedException e){
				System.out.println("Error: " + e.getMessage());
			}
		}
		// once it has been notified then acquire instance
		free--; // have to reduce free count
		System.out.println("process_" + id + " acquires " + Resource1.name);
		
	}
	
	/* Method used to release a unit from this resource
	 * This will increase the free unit count and will notify 
	 * any thread that may be waiting on that unit
	 */
	public synchronized void release(int id)
	{
		System.out.println("process_" + id + " releases " + Resource1.name);
		free++;
		notify();
	}
	
}
/* END Resource1 class */

/* Resource2 class
 * Example: 2 blue pens
 */
class Resource2
{
	// resource name
	private static String name = "Blue Pen(s)";
	// number of available resources
	private static int free = 2;

	
	// constructor - prints out message when instace created
	public Resource2()
	{
		//TODO
		System.out.println("Created Resource1");
		System.out.println("\tName: "+ Resource2.name);
		System.out.println("\tStock: " + Resource2.free);
	}
	
	/* function used to acquire a unit from this resource.
	 * Will reduce the number of free units by 1
	 * If not units are left to be acquired then will have the thread wait()
	 * unit a unit becomes available.
	*/
	public synchronized void acquire(int id)
	{
		if(free <= 0) // no free resource
		{
			// then have to wait until a resource becomes available
			try{
				System.out.println("+process_" + id + " waiting for " + Resource2.name);
				wait();
			}catch(InterruptedException e){
				System.out.println("Error: " + e.getMessage());
			}
		}
		// once it has been notified then acquire instance
		free--; // have to reduce free count
		System.out.println("process_" + id + " acquires " + Resource2.name);
		
	}
	
	/* Method used to release a unit from this resource
	 * This will increase the free unit count and will notify 
	 * any thread that may be waiting on that unit
	 */
	public synchronized void release(int id)
	{
		System.out.println("process_" + id + " releases " + Resource2.name);
		free++;
		notify();
	}
	
}
/* END - Resource2 */

/* Process class extends the Thread class so that we can have
 * concurrent process running at the same time.
 */
class Process extends Thread
{
	static Resource1 r1;
	static Resource2 r2;
	int id;
	
	/* constructor - takes in
	 * id: ID number to be assigned to the newly created instance
	 * r1: reference to the first Resource
	 * r2: reference to the second Resource
	 * both r1 and r2 are static across all instances of Process
	 */
	public Process(int id, Resource1 r1, Resource2 r2)
	{
		this.id = id;
		Process.r1 = r1;
		Process.r2 = r2;
		System.out.println("=== Thread for process_" + id + " created");
	}
	
	/* initial start function that will be called from the .start() 
	 * in main after the process thread is created
	 */
	public void run()
	{
		/*TODO
		 * acquire r1 and r2
		 * display process_i is working
		 * release r1 and r2
		 */
		
		// variables to be used for the random number generator
		final int min_rand = 100; // in miliseconds so 0.1 seconds
		final int max_rand = 3000; // in miliseconds so 3 sec
		
		System.out.println("** Started Process_" + this.id);
		
		// always sleep before trying to acquire ... just for this project so get different orders
		Random randGen = new Random();
		int sleepTime = randGen.nextInt(max_rand - min_rand + 1) + min_rand;
		//System.out.println("sleepTime: " + sleepTime);
		
		try{
			Thread.sleep(sleepTime);
		}catch(InterruptedException e){
			System.out.println("Error: " + e.getMessage());
		}
		// now actually try to acquire and instance of r1
		r1.acquire(this.id);
		
		//sleep first then try to acquire and instance of r2
		try{
			Thread.sleep(sleepTime);
		}catch(InterruptedException e){
			System.out.println("Error: " + e.getMessage());
		}
		//now actually try to acquire an instance of r2
		r2.acquire(this.id);
		
		// after both r1 and r2 have been acquired then "work"
		System.out.println("---- procces_" + this.id + " is working");
		
		//now have to sleep and release each resource
		//sleep first then try to acquire and instance of r2
		try{
			Thread.sleep(sleepTime);
		}catch(InterruptedException e){
			System.out.println("Error: " + e.getMessage());
		}
		r1.release(this.id);
		
		//sleep first then try to acquire and instance of r2
		try{
			Thread.sleep(sleepTime);
		}catch(InterruptedException e){
			System.out.println("Error: " + e.getMessage());
		}
		r2.release(this.id);
		
		System.out.println("** Finished Process_" + this.id);
	}
	
}
/* END - Process */
