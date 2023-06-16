/* Add10 for aarch64 (arm64) using Linux System Calls 
*
* compile with: as <source> -o name && ld name -o name.out && ./a.out && echo $?
*/

.text
.align 8				// Show we are 64bit
.global _start
.global add10

add10:
	// Adds ten to a provided number
	// X0 = long long int num
	add X0, X0, #10			// X0 = X0 + 10 (Add 10)
	ret

_start:
	//Print
	ldr X1, =string			// Load string into memory
	ldr X2, =len			// Load size of str in memory
	mov X0, #1			//Set X0 to stdout
	mov X8, #64			// Linux SysWrite (stdout, str, len)
	svc #0

	//Use add10 function
	mov X0, #5			// Make X0 5
	bl add10			// Call add10

	//Exit
	//Note: X0 holds our result, and is also the exit code we give Linux
	mov X8, #93			// Linux SysExit
	svc #0

.data
string:
	.ascii "Adding 10 to 5\nType 'echo $?' for result\n\0"
len = . - string

