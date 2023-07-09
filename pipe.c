#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
int main() { 
    int pipefd1[2]; 
    int pipefd2[2]; 
    pid_t pid; 
    
    // Create the first pipe 
    if (pipe(pipefd1) == -1) { 
        perror("pipe"); 
        exit(EXIT_FAILURE); 
    } 
    
    // Fork the first child process (ls -l) 
    pid = fork(); 
    if (pid == -1) { 
        perror("fork"); 
        exit(EXIT_FAILURE); 
    } 
    
    if (pid == 0) { 
        // Child process 1 (ls -l) 
        // Close the read end of the first pipe 
        close(pipefd1[0]); 
        // Redirect stdout to the write end of the first pipe 
        dup2(pipefd1[1], STDOUT_FILENO); 
        // Close the write end of the first pipe 
        close(pipefd1[1]); 
        // Execute ls -l 
        execlp("ls", "ls", "-l", NULL); 
        // This code will only be reached if execlp fails 
        perror("execlp"); 
        exit(EXIT_FAILURE); 
    } 
    
    // Create the second pipe 
    if (pipe(pipefd2) == -1) { 
        perror("pipe"); 
        exit(EXIT_FAILURE); 
    } 
    
    // Fork the second child process (who) 
    pid = fork(); 
    if (pid == -1) { 
        perror("fork"); 
        exit(EXIT_FAILURE); 
    } 
    
    if (pid == 0) { 
        // Child process 2 (who) 
        // Close the read end of the first pipe 
        close(pipefd1[0]); 
        // Close the write end of the first pipe 
        close(pipefd1[1]); 
        // Close the read end of the second pipe 
        close(pipefd2[0]); 
        // Redirect stdout to the write end of the second pipe 
        dup2(pipefd2[1], STDOUT_FILENO); 
        // Close the write end of the second pipe 
        close(pipefd2[1]); 
        // Execute who 
        execlp("who", "who", NULL); 
        // This code will only be reached if execlp fails 
        perror("execlp"); 
        exit(EXIT_FAILURE); 
    } 
    
    // Close the write end of the first pipe 
    close(pipefd1[1]); 
    
    // Fork another child process 
    pid = fork(); 
    if (pid == -1) { 
        perror("fork"); 
        exit(EXIT_FAILURE); 
    } 
    
    if (pid == 0) { 
        // Child process 3 (grep .c$) 
        // Close the read end of the first pipe 
        close(pipefd1[0]); 
        // Close the read end of the second pipe 
        close(pipefd2[0]); 
        // Close the write end of the second pipe 
        close(pipefd2[1]); 
        // Redirect stdin to the read end of the first pipe 
        dup2(pipefd1[0], STDIN_FILENO); 
        // Execute grep .c$ 
        execlp("grep", "grep", ".c$", NULL); 
        // This code will only be reached if execlp fails 
        perror("execlp"); 
        exit(EXIT_FAILURE); 
    } 
    
    // Close the read end of the first pipe 
    close(pipefd1[0]); 
    // Close the read end of the second pipe 
    close(pipefd2[0]); 
    
    // Fork the fourth child process (sort) 
    pid = fork(); 
    if (pid == -1) { 
        perror("fork"); 
        exit(EXIT_FAILURE); 
    } 
    
    if (pid == 0) { 
        // Child process 4 (sort) 
        // Close the write end of the second pipe 
        close(pipefd2[1]); 
        // Redirect stdin to the read end of the second pipe 
        dup2(pipefd2[0], STDIN_FILENO); 
        // Close the read end of the second pipe 
        close(pipefd2[0]); 
        // Execute sort 
        execlp("sort", "sort", NULL); 
        // This code will only be reached if execlp fails 
        perror("execlp"); 
        exit(EXIT_FAILURE); 
    } 
    
    // Close the write end of the second pipe 
    close(pipefd2[1]); 
    
    // Wait for all child processes to finish 
    wait(NULL); 
    wait(NULL); 
    wait(NULL); 
    wait(NULL); 
    
    return 0;
}
