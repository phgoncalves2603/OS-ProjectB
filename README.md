# Pipe and Fork Simulation

## Objective
Simulate inter-process communication between a parent and child process using pipes and `fork()`. The child process runs the `ls -l` command, and the parent process reads the output from the pipe and prints it to the console.

## Challenges and Solutions
**Challenge 1:** I struggled initially with understanding how to set up inter-process communication between the parent and child process using pipes.

**Solution:** I implemented the `dup2()` function in the child process to redirect its `stdout` to the write end of the pipe. The parent then reads the output from the pipe.

**Challenge 2:** Handling the execution of the `ls -l` command in the child process was tricky at first.

**Solution:** I used `execlp()` to execute the `ls -l` command in the child process. This function replaces the current process with the command, which allows the child to run the desired program.

**Challenge 3:** There were issues with properly managing pipe closure and ensuring synchronization between the parent and child processes.

**Solution:** I made sure to close the unused ends of the pipe in both the parent and child processes to ensure proper communication. The parent process uses `read()` to fetch data from the pipe and `wait()` to ensure the child completes before the parent terminates.

## Outcomes
- The program successfully simulates inter-process communication where the child executes `ls -l` and sends the output to the parent through the pipe.
- The parent process reads from the pipe and outputs the result to the console.
- Gained a better understanding of `fork()`, pipes, and the use of `dup2()` and `execlp()` for process management.
