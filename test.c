#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

typedef struct Node {
    char *type;
    char *arguments;
    char *redirection;
    struct Node *left;
    struct Node *right;
} Node;

int execute_command(char *command, char *redirection) {
    pid_t pid = fork();
    if (pid == 0) {  // Child process
        if (redirection) {
            int fd = open(redirection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        execl("/bin/sh", "sh", "-c", command, (char *)NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {  // Parent process
        int status;
        waitpid(pid, &status, 0);
        return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    } else {
        perror("fork");
        return -1;
    }
}

int execute_pipe(char *left_command, char *right_command) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }

    pid_t left_pid = fork();
    if (left_pid == 0) {  // Left child process
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execl("/bin/sh", "sh", "-c", left_command, (char *)NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }

    pid_t right_pid = fork();
    if (right_pid == 0) {  // Right child process
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execl("/bin/sh", "sh", "-c", right_command, (char *)NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    int status;
    waitpid(left_pid, &status, 0);
    waitpid(right_pid, &status, 0);
    return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}

int execute_ast(Node *node) {
    if (strcmp(node->type, "AND") == 0) {
        int left_result = execute_ast(node->left);
        if (left_result == 0) {
            return execute_ast(node->right);
        } else {
            return left_result;
        }
    } else if (strcmp(node->type, "COMMAND") == 0) {
        return execute_command(node->arguments, node->redirection);
    } else if (strcmp(node->type, "PIPE") == 0) {
        return execute_pipe(node->left->arguments, node->right->arguments);
    }
    return -1;
}

int main() {
    Node command_ls = {"COMMAND", "ls -la", "out", NULL, NULL};
    Node command_cat = {"COMMAND", "cat out", NULL, NULL, NULL};
    Node command_wc = {"COMMAND", "wc -l", NULL, NULL, NULL};
    Node pipe_node = {"PIPE", NULL, NULL, &command_cat, &command_wc};
    Node and_node = {"AND", NULL, NULL, &command_ls, &pipe_node};

    int result = execute_ast(&and_node);
    printf("Execution result: %d\n", result);
    return result;
}
