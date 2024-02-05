#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);

    // Check if both arguments are provided
    if (argc != 3) {
        syslog(LOG_ERR, "Usage: %s <writefile> <writestr>", argv[0]);
        closelog();
        exit(1);
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    // Create the directory path if it doesn't exist
    system("mkdir -p /tmp/aeld-data");

    // Write the content to the file
    FILE *file = fopen(writefile, "w");
    if (file == NULL) {
        syslog(LOG_ERR, "Error creating file: %s", writefile);
        printf("%s\n", writefile);
        closelog();
        exit(1);
    }
    fprintf(file, "%s\n", writestr);
    fclose(file);

    // Log the success message
    syslog(LOG_DEBUG, "Writing \"%s\" to \"%s\"", writestr, writefile);

    closelog();
    return 0;

    
}
