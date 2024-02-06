#include "systemcalls.h"



/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{
    int returnCode = system(cmd);
    return (returnCode == 0) ? true : false;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char *command[count + 1];
    int i;

    // Populate the command array
    for (i = 0; i < count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    // Fork a child process
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("Error forking process");
        return false;
    }
    else if (pid == 0)
    {
        // Child process: execute the command
        execv(command[0], command);
        perror("Error executing command");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process: wait for the child to complete
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            printf("Command executed successfully.\n");
            return true;
        }
        else
        {
            printf("Command execution failed.\n");
            return false;
        }
    }

    va_end(args);
}

/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char* outputfile, int count, ...) {
    va_list args;
    va_start(args, count);
    char* command[count + 1];
    int i;

    // Populate the command array
    for (i = 0; i < count; i++) {
        command[i] = va_arg(args, char*);
    }
    command[count] = NULL; // Null-terminate the array

    va_end(args);

    // Fork a child process
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Error while forking");
        return false;
    } else if (child_pid == 0) {
        // Child process
        int fd = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("Error opening output file");
            exit(EXIT_FAILURE);
        }

        // Redirect stdout to the specified file
        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("Error redirecting stdout");
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Execute the command
        execv(command[0], command);
        perror("In execv"); // Print an error message if execv fails
        close(fd);
        exit(EXIT_FAILURE); // Exit the child process
    } else {
        // Parent process
        int status;
        wait(&status); // Wait for the child process to complete
        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process terminated abnormally\n");
        }
        return true;
    }
}
