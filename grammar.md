program → declaration\*

declaration → funcDecl
| varDecl
| classDecl

funcDecl → type IDENTIFIER '(' paramList? ')' block

paramList → param (',' param)\*
param → type IDENTIFIER

varDecl → type IDENTIFIER ('=' expression)? ';'

classDecl → 'class' IDENTIFIER '{' member\* '}'
member → accessSpec? (funcDecl | varDecl)
accessSpec → 'public' | 'private' | 'protected'

block → '{' statement\* '}'

statement → varDecl
| exprStmt
| ifStmt
| whileStmt
| returnStmt
| block

ifStmt → 'if' '(' expression ')' statement ('else' statement)?
whileStmt → 'while' '(' expression ')' statement
returnStmt → 'return' expression? ';'
exprStmt → expression ';'

expression → assignment
assignment → IDENTIFIER '=' assignment
| logical*or
logical_or → logical_and ('||' logical_and)*
logical*and → equality ('&&' equality)*
equality → comparison (('==' | '!=') comparison)_
comparison → term (('<' | '>' | '<=' | '>=') term)_
term → factor (('+' | '-') factor)_
factor → unary (('_' | '/') unary)\*
unary → ('!' | '-') unary
| primary
primary → INTEGER | FLOAT | STRING | BOOL
| IDENTIFIER
| IDENTIFIER '(' argList? ')'
| '(' expression ')'

type → 'int' | 'float' | 'bool' | 'void' | IDENTIFIER

- and ? are EBNF extensions — \* means zero or more, ? means optional. Pure BNF would use recursive rules instead.

Left recursion (e.g. term → term '+' factor) is deliberately avoided here because recursive descent can't handle it — hence the iterative ('+' factor)\* form instead.

Primary is the base case — it's where recursion bottoms out, which is why it handles literals and parenthesised expressions (which re-enter at the top).
