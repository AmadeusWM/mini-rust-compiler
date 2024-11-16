# mini-rust-compiler
# Ideas
- Symbol table:
  - Will consist of a stack of scopes, each scope has a lookup table for the scope's symbols
  - When entering a scope => push new scope on stack
  - When reading symbol => iterate stack from top to bottom till symbol is found
  - Variables can be redeclared: `let mut a = 1; let mut a = "abc";` is OK
- Type inference
  - untyped AST => typed AST: `typecheck(ast)`
- AST
  - Implement each node as a Node: Expr, VariableExpr, etc.
  - Node has a virtual method accept, which accepts a visitor
  - Visitor with lambda method to use visitor?
    -> visitor.visit(expr, (expr: VariableExpr) => {/* do something */})
    - https://lesleylai.info/en/ast-in-cpp-part-1-variant
- Everything is an expression (even assignments etc.), except for declarations.
- Functions are function definitions
- MIR


# Resources
- Some rust scanne; https://github.com/mjehrhart/lexical_scanner/blob/master/src/enums/mod.rs
- Rust reference (tokens): https://doc.rust-lang.org/reference/tokens.html
- AST in cpp: https://lesleylai.info/en/ast-in-cpp-part-1-variant/
- AST rust impl: https://doc.rust-lang.org/beta/nightly-rustc/rustc_ast/ast/struct.Stmt.html
- Flex and bison cpp:
  - http://www.jonathanbeard.io/tutorials/FlexBisonC++
    - https://github.com/jonathan-beard/simple_wc_example
  - https://github.com/ezaquarii/bison-flex-cpp-example
  - https://github.com/bingmann/flex-bison-cpp-example/tree/master/src
- BISON docs: https://www.gnu.org/software/bison/manual/html_node/Concepts.html
- FLEX docs: https://westes.github.io/flex/manual/Cxx.html#Cxx
- https://blog.trailofbits.com/2024/05/02/the-life-and-times-of-an-abstract-syntax-tree/

- THE RUST COMPILER:
  - type inference: https://rustc-dev-guide.rust-lang.org/type-inference.html
