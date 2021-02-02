# tinyC Language Reference

*tinyC* is a *C*-like language with much smaller subset of types (`int`, `char`, `double`, arrays and structs, function pointers and pointers) and limited set of features. 

The next sections detail the grammar of the language as well as its semantics. TinyC's semantics and grammar are simpler, which makes tinyC not a strict subset of C, any such instances are highlighted in the text below. 


    PROGRAM := { FUN_DECL | VAR_DECL ';' | STRUCT_DECL | FUNPTR_DECL }

A program is collection of function and variable declarations. Alternatively, `tinyC` supports a repl-like interface, where the main element is either a program, or a stetement:

    REPL := STATEMENT | PROGRAM




    FUN_DECL := TYPE_FUN_RET identifier '(' [ FUN_ARG { ',' FUN_ARG } ] ')' BLOCK_STMT
    FUN_ARG := TYPE identifier

### Statements

    STATEMENT := BLOCK_STMT | IF_STMT | SWITCH_STMT | WHILE_STMT | DO_WHILE_STMT | FOR_STMT | BREAK_STMT | CONTINUE_STMT | RETURN_STMT | EXPR_STMT

    BLOCK_STMT := '{' { STATEMENT } '}'

    IF_STMT := if '(' EXPR ')' STATEMENT [ else STATEMENT ]

    SWITCH_STMT := switch '(' EXPR ')' '{' { CASE_STMT } [ default ':' CASE_BODY } ] { CASE_STMT } '}'
    CASE_STMT := case integer_literal ':' CASE_BODY
    CASE_BODY := { STATEMENT }

    WHILE_STMT := while '(' EXPR ')' STATEMENT 
    DO_WHILE_STMT := do STATEMENT while '(' EXPR ')' ';'
    FOR_STMT := for '(' [ EXPR_OR_VAR_DECL ] ';' [ EXPR ] ';' [ EXPR ] ')' STATEMENT

    BREAK_STMT := break ';'
    CONTINUE_STMT := continue ';'

    RETURN_STMT := return [ EXPR ] ';'

    EXPR_STMT := EXPR_OR_VAR_DECL ';'

### Types

To keep the type declarations similar to those of `C` while keeping the grammar simple to parse, the type declarations grammar is a bit repetitive:

    TYPE := (int | double | char | identifier) { * }
         |= void * { * }

    TYPE_FUN_RET := TYPE | void

Pointers can point to either a plain type, an identifier representing a struct or function pointer type, or `void`. Pointers to pointers are allowed. 

### Type Declarations

    STRUCT_DECL := struct identifier [ '{' { TYPE identifier ';' } '}' ] ';'

Structured types must always be declared before they are used. Forward declarations are supported as well. 

    FUNPTR_DECL := typedef TYPE_FUN_RET '(' '*' identifier ')' '(' [ TYPE { ',' TYPE } ] ')' ';'

Function pointers must always be declared before they can be used. 


### Expressions

    F := integer | double | char | string | identifier | '(' EXPR ')' | E_CAST
    E_CAST := cast '<' TYPE '>' '(' EXPR ')'

    E_CALL_INDEX_MEMBER_POST := F { E_CALL | E_INDEX | E_MEMBER | E_POST }
    E_CALL := '(' [ EXPR { ',' EXPR } ] ')'
    E_INDEX := '[' EXPR ']'
    E_MEMBER := ('.' | '->') identifier 
    E_POST := '++' | '--'

    E_UNARY_PRE := { '+' | '-' | '!' | '~' | '++' | '--' } E_CALL_INDEX_MEMBER_POST

    E1 := E_UNARY_PRE { ('*' | '/' | '%' ) E_UNARY_PRE }
    E2 := E1 { ('+' | '-') E1 }
    E3 := E2 { ('<<' | '>>') E2 }
    E4 := E3 { ('<' | '<=' | '>' | '>=') E3 }
    E5 := E4 { ('==' | '!=') E4 }
    E6 := E5 { '&' E5 }
    E7 := E6 { '|' E6 }
    E8 := E7 { '&&' E7 }
    E9 := E8 { '||' E8 }

Basic arithmetic operators are supported in the same way they are in `c/c++` including their priority. All evaluate left to right (left associative). 

    E_ASSIGN := E9 [ '=' E_ASSIGN ]
             
Assignment operator. Note that assignment operator is right-to-left (right associative). 

    EXPR := E_ASSIGN { ',' E_ASSIGN }

Expressions can be separated by a comma, they will be evaluated left to right.

    VAR_DECL := TYPE identifier [ '=' E_ASSIGN ] { ',' identifier [ '=' E_ASSIGN ] }
    EXPR_OR_VAR_DECL := VAR_DECL
                     |= EXPR

Variable declaration must start with a type specification. Multiple variables of same type can be declared in single expression. Similarly to `c`, the initial value does not have to be supplied with the declaration. 

> Note that unlike `c`, `tinyc` makes the pointer part of the type declaration, i.e. `int * a, b, c` declares three variables of type `int*`.
