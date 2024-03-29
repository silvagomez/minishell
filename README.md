# Minishell

![bash](https://www.muylinux.com/wp-content/uploads/2018/11/bash.png)

## Subject
Shell should behave:
- [x] Display a prompt when waiting for a new command.
- [x] Have a working history.
- [ ] Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
- [x] Avoid using more than one global variable to indicate a received signal. Consider the implications: this approach ensures that your signal handler will not access your main data structures.

> [!WARNING]
> Be carefull. This global variable cannot provide any other
> information or data access than the number of a received signal.
> Therefore it is forbidden to use "norm" type structures in global.

- [x] Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
- [x] Handle ’ (single quote) which should prevent the shell from interpreting the meta- characters in the quoted sequence.
- [x] Handle " (double quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence except for $ (dollar sign).

Implement redirections:

- [x] < should redirect input.
- [x] > should redirect output.
- [x] << should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
- [x] >> should redirect output in append mode.
- [x] Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
- [x] Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
- [x] Handle $? which should expand to the exit status of the most recently executed foreground pipeline.

Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
<br>
In interactive mode:

- [ ] ctrl-C displays a new prompt on a new line.
- [ ] ctrl-D exits the shell.
- [ ] ctrl-\ does nothing.

Your shell must implement the following builtins:

- [ ] echo with option -n
- [ ] cd with only a relative or absolute path
- [ ] pwd with no options
- [ ] export with no options
- [ ] unset with no options
- [ ] env with no options or arguments
- [ ] exit with no options

The readline() function can cause memory leaks. You don’t have to fix them. But
that doesn’t mean your own code, yes the code you wrote, can have memory
leaks.

## Type of commit
```
feat: The new feature being added to a particular application
fix:  A bug fix (this correlates with PATCH in SemVer)
style:  Feature and updates related to styling
refactor:  Refactoring a specific section of the codebase
test:  Everything related to testing
docs:  Everything related to documentation
chore:  Regular code maintenance
special: For remember unused code
```
## Useful links
Learn git branching by playing [link.](https://learngitbranching.js.org/)
<br>
Write better commit messages [link.](https://medium.com/swlh/writing-better-commit-messages-9b0b6ff60c67)
<br>
Git branch commands [link.](https://github.com/Kunena/Kunena-Forum/wiki/Create-a-new-branch-with-git-and-manage-branches)
<br>
Blog codequoi [link.](https://www.codequoi.com/en/why-i-no-longer-write-articles-about-42-school-projects/)
