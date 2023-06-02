/* Writes a pattern to the frame buffer
 * Use on a TTY with './a.out <num>'
 * Linux only 
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if(argv[1] == NULL){
		fprintf(stderr, "Usage: '%s <number>'\n");
		return EXIT_FAILURE;
	}

	int row=0, col=0, width=0, height=0;
	unsigned int *data = NULL;
	
	//open the frame buffer
	int fd = open("/dev/fb0", O_RDWR);

	if(fd == -1) perror("fd open");

	struct fb_var_screeninfo screeninfo;
	if(ioctl(fd, FBIOGET_VSCREENINFO, &screeninfo)) perror("ioctl"); //control the screen
	int bytespp = screeninfo.bits_per_pixel / 8;
	
	width = screeninfo.xres;
	height = screeninfo.yres;
	
	//whats going to be written to the screen
	data = (unsigned int*) mmap(0, width * height * bytespp, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	
	//write data to the screen
	for(row = 0; row < height; row++)
		for(col = 0; col < width; col++)
			data[row * width + col] = (unsigned) atoi(argv[1]);

	//clean up
	usleep(1000000); //sleep for a little bit before fixing the screen
	munmap(data, width * height * bytespp);
	close(fd);
	return EXIT_SUCCESS;
}

