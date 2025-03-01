#include <iostream>

#include <unistd.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <cstring>



int main() {

    int fd[2];  // fd[0] = read end, fd[1] = write end

    if (pipe(fd) == -1) {

        perror("pipe");

        return 1;

    }



    pid_t pid = fork();

    if (pid < 0) {

        perror("fork");

        return 1;

    }



    if (pid == 0) {  // Child process

        close(fd[0]); // Close unused read end

        dup2(fd[1], STDOUT_FILENO); // Redirect stdout to pipe

        close(fd[1]);



        execlp("ls", "ls", "-l", NULL); // Execute ls -l

        perror("execlp");

        return 1;

    } else {  // Parent process

        close(fd[1]); // Close unused write end



        char buffer[1024];

        ssize_t n;

        while ((n = read(fd[0], buffer, sizeof(buffer) - 1)) > 0) {

            buffer[n] = '\0'; // Null-terminate the string

            std::cout << buffer;

        }



        close(fd[0]);

        wait(NULL); // Wait for child process to finish

    }



    return 0;

}