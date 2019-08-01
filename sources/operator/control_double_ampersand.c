/*
** EPITECH PROJECT, 2019
** control_double_ampersand.c
** File description:
** control double ampersand
*/

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_shell.h"

static int management_double_ampersand_son(variable_t *var, tree_t *tree)
{
    if (check_element_is_operator(tree->left))
        return (chose_good_operator(var, tree->left));
    else
        return (exec_arg(var, tree->left->data));
}

static int management_double_ampersand_parent(variable_t *var, tree_t *tree)
{
    if (check_element_is_operator(tree->right))
        return (chose_good_operator(var, tree->right));
    else
        return (exec_arg(var, tree->right->data));
}

static int management_double_ampersand(variable_t *var, tree_t *tree)
{
    pid_t pid;
    int wstatus = 0;

    if ((pid = fork()) == -1)
        return (display_error_fork(0, NULL));
    if (pid == 0) {
        wstatus = management_double_ampersand_son(var, tree);
        my_exit(var, my_itoa(wstatus, my_isneg(wstatus)), 0);
    } else {
        waitpid(pid, &wstatus, WUNTRACED | WCONTINUED);
        if (WEXITSTATUS(wstatus) == 0)
            wstatus = management_double_ampersand_parent(var, tree);
    }
    return (wstatus);
}

int control_double_ampersand(variable_t *var, tree_t *tree)
{
    if (tree == NULL)
        return (1);
    return (management_double_ampersand(var, tree));
}