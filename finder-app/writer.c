#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>


int main(int argc,char *args[]){    
    
    FILE *fptr;
    // check for valid arguments
    if(argc!=3)
    {
        printf("Usage : ./writer <filepath> <string> \n");
        return 1;
    }    
    
    // Open a log at user level
    openlog("writer", LOG_PID, LOG_USER);
    
    const char *strPath = args[1];
    printf("strPath: %s \n",args[1]);
    const char *strWrite = args[2];
    printf("strWrite: %s \n",args[2]);

    // Open a file in writing mode
    fptr = fopen(strPath, "w");    

    if (fptr == NULL) {
        // update the log with error status
        syslog(LOG_ERR, "Error: Failed to open file '%s' for writing.", strWrite);
        perror("fopen");
        exit(1);
    }

    // Write the given string to the file
    fprintf(fptr, strWrite);

    // update the log with write status
    syslog(LOG_DEBUG, "Success: Writing '%s' to '%s'", strWrite, strPath);
    printf("Success: Writing '%s' to '%s' \n", strWrite, strPath);

    // Close the file
    fclose(fptr);
    
    // close the log
    closelog();

    exit(0);
}