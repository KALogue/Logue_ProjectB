//Kernel.c
//Katie Logue

void printString(char*);
void printChar(char);
void readString(char*);
void readSector(char*, int);

void main()
{
//	int start = 0xB800;
//	int offset = 0x0;
//	char* message = "Hello World";

//	char line[80];
//	printString("Enter a line: ");
//	readString(line);
//	printString(line);

//	char buffer[512];
//	readSector(buffer, 30);
//	printString(buffer);

	char line[80];
	makeInterrupt21();
	interrupt(0x21,1,line,0,0);
	interrupt(0x21,0,line,0,0);

//	while(*message != 0)
//	{
//		putInMemory(start, offset, *message);
//		offset++;
//		putInMemory(start, offset, 0x7);
//		offset++;
//		message++;
//	}

	while(1);

}

void printString(char* chars)
{
	int i = 0;
	while(chars[i] != 0x0)
	{
		char al = chars[i];
		char ah = 0xe;
		int ax = ah * 256 + al;
		interrupt(0x10, ax, 0, 0, 0);
		i++;
	}

}

void printChar(char c)
{
	char al = c;
	char ah = 0xe;
	int ax = ah * 256 + al;
	interrupt(0x10, ax, 0, 0, 0);
}

void readString(char* line)
{
	int i = 0;
	int input = 0;

	while(input != 0xd)
	{
		input = interrupt(0x16,0,0,0,0);

		if (input == 0x8) {
			if (i > 0) {
				printChar(0x8);
				printChar(' ');
				printChar(0x8);
				i--;
				line[i] = 0;
			}
		} else {
			printChar(input);
			line[i] = input;
			i++;

		}
	}

	line[i] = 0xa;
	line[i+1] = 0x0;
	printChar(0xa);
}

void readSector(char* buffer, int sector)
{
	int ah = 2; //read sector
	int al = 1; //number of sectors
	int ax = ah*256+al;
	int ch = 0; //track number
	int cl = sector + 1; //relative sector number
	int cx = ch*256+cl;
	int dh = 0; //head number
	char dl = 0x80; //device number
	int dx = dh*256+dl;

	interrupt(0x13,ax,buffer,cx,dx);

}

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
	if(ax == 0){
		printString(bx);
	}
	if(ax == 1){
		readString(bx);
	}
	if(ax == 2){
		readSector(bx,cx);
	}
	if(ax >= 3){
		printString("Error!");
	}
}
