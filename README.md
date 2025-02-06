# Minishell

Made by [mariaserpa](https://github.com/mariaserpa) and [vados-sa](https://github.com/vados-sa).

## 📝 Overview  
Minishell is a **simple shell**, written in C, taking **bash** as reference, and developed as part of the 42 curriculum. This project deepened our understanding of **processes, file descriptors, and signal handling** while replicating essential shell features.
> **A Fun but Challenging Journey!**  
> This project was quite an adventure! Being our **first group project**, we had to figure out how to **divide tasks fairly**, collaborate efficiently, and debug together when things (inevitably) broke. Given its **size and complexity**, it pushed us to improve not only our technical skills but also our teamwork. In the end, our shell may not be perfect, but it **works**, and we’re incredibly proud of it.  
> Our very own **little bash**—built from scratch! 🚀🐚

## 🔧 Features  
- **Custom Shell Prompt**: Displays a prompt and waits for user commands.  
- **Command Execution**: Executes binaries based on the `PATH` variable, relative, or absolute paths.  
- **Built-in Commands**: Implements `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.  
- **Pipes (`|`)**: Supports command chaining via pipelines.  
- **Redirections (`<`, `>`, `<<`, `>>`)**: Handles input/output redirection and heredoc functionality.  
- **Environment Variables (`$VAR`)**: Expands and substitutes environment variables.  
- **Exit Status (`$?`)**: Stores the last executed command's exit status.  
- **Signal Handling**: Properly manages `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` interactions (both interactive and non-interactive mode). 
- **History Management**: Uses `readline` for command history storage.
- **Memory Management**: Ensures proper memory allocation and deallocation to prevent memory leaks, except for those caused by readline(). 

## 🚀 How to Run  
### **Compile after cloning**  
```bash
make
```
### **Run the program**
```bash
./minishell
```
### **Execute Commands**
**e.g.**:
```bash
minishell$ ls
```
```bash
minishell$ export VAR="As beautiful as a shell"
```
```bash
minishell$ echo $VAR
```
### **Exit minishell**
Press `Ctrl-D`

**or** 
```bash
minishell$ exit
```
