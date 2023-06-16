/* Hello World for aarch64 (arm64) using Linux System Calls 
* It is a good idea to use capital X for registers so you
* do not confuse it with hex.
*
* compile with: as <source> -o name && ld name -o name.out
*/

.text
.align 8				// Show we are 64bit
.global _start

_start:
	//Print
	ldr X1, =string			// Load string into memory
	ldr X2, =len			// Load size of str in memory
	mov X0, #1			//Set X0 to stdout
	mov X8, #64			// Linux SysWrite (stdout, str, len)
	svc #0
	
	//Exit
	eor X0, X0, X0			// Set exit code to zero by xor-ing itself
	mov X8, #93			// Linux SysExit
	svc #0

.data
string:
	.ascii "Hello, World.\n\0"
len = . - string

