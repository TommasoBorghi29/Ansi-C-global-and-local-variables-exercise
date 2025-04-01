Hello everyone, here you can find an exercise written in ANSI C version 89/90, using global and local variables, functions, structures, and arrays of structures

📘 Global and Local Variables in C
🔹 Local Variables

    Declaration: inside a function or a block { }.

    Scope: only accessible within the function or block where declared.

    Lifetime: exists only during the execution of that function/block.

    Example:

    void function() {
        int x = 5; // local variable
    }

🔹 Global Variables

    Declaration: outside of all functions (typically at the top of the file).

    Scope: accessible from all functions in the same file (or other files using extern).

    Lifetime: exists for the entire duration of the program.

    Example:

    int y = 10; // global variable

    void function() {
        y = y + 1;
    }
