ReadMsg.c reads hidden messages
WriteMsg.c writes hidden messages
reverseutility.c is a utility file.

To compile:
gcc -o write WriteMsg.c reverseutility.c
gcc -o read ReadMsg.c

To execute:
./write -i "image.ppm" -o "output.ppm" -m "message"
./read -i "output.ppm"

optional commands for both functions: 
	-v for verbose output (some debugging info and header file printed)
	-h prints a help screen explaining the program and commands
	
Current message limit is capped at 255 characters. This is done arbitrarily,
and is easily increased to a larger value by changing SIZE_SIZE in both files. 

Alternative file format suggestion: BMP. It consists of: 14 byte file header,
variable sized (min 12) DIB header, then pixel data.