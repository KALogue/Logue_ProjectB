Katie Logue and Adam Koropey
Project B

What we did:
Step 1: Created a printString function
Step 2: Created a readString function
Step 3: Created a readSector function
Steps 4 and 5: Created the hadleInterrrupt21() function to call the other functions.

How to verify:
Step 1: 
	Uncomment line:
		printString("Hello world\n");
	Run CompileOS.sh
	Run simulator
	
Step 2: 
	Uncomment lines:
		char line[80];
		printString("Enter a line: ");
		readString(line);
		printString(line);
	Run CompileOS.sh
	Run simulator

Step 3:
	Uncomment lines:
		char buffer[512];
		readSector(buffer, 30);
		printString(buffer);
	Run CompileOS.sh
	Run simulator

Steps 4 and 5:
	Uncomment line:
		char line[80];
		makeInterrupt21();
		interrupt(0x21,1,line,0,0);
		interrupt(0x21,0,line,0,0);
	Run CompileOS.sh
	Run simulator 
