# mini-rust-compiler
## Supported Features
- Types:
  - Integer types: i8, i16, i32, i64
  - Float types: f32, f64
  - Boolean types: bool
  - String types: &str
  - Unit type: ()
- Literals:
  - Float
  - Integer
  - String
  - Boolean: true and false
  - Unit
- Variables and variable declarations
  - Let with or without a type
  - Let mut with or without a type
  - An expression to initialize the variable
  - Variables can be used as expressions
- Blocks:
  - With or without implicit return
- Functions
  - Functions can be initialized
  - With or without parameters
  - With or without a return type (default Unit)
  - Can be called -> functions can only call functions within the same Function scope, or in a higher function scope, not from other function scopes
- Grouped expressions using parentheses
- Operator expressions
  - Assignment: =, +=, -=, /=, *=, %=
  - Binary: +, -, /, *, %, ||, &&, ==, !=, <, <=, >, >=
  - Unary: +, -, !
- If, else if, else, while loops, loop
- Expression statements:
  - Block expressions do not require a ; at the end
  - Other expressions do, excep they are the last expression statement within a block, in which case they are implicitly returned
- Break, return
- Line comments
- Intermediate:
  - block comments
  - Strings
  - break
  - return
- Advanced:
  - Type inferencing:
    - Let statements without a type declaration are initially Variable to any other type
    - Variable Integer, or Float types can be inferred to Concrete Integer or Float types such as i8, i16, i32, i64 or f32, f64.
    - Literals' types are variable at first
    - Once a type has been inferred, the variable or expression cannot be converted to another type
  - Modules and nested functions:
    - Functions can be wrapped in modules, and functions can contain other functions
    - Functions can call functions from the same module, or call functions from other modules by excaping their module using `super::xyz()`




## TODO !!!
1. Make a nested map datastructure (NSTree) for Body tree and Types tree, it will have a template type T (for body, or type)
  - Tree structure:
    - SetPosition: sets current position in tree
    - Lookup: looks up a value by NS: `lookup("a::b::c")`
    - Insert: inserts a value by NS: `insert("b::c", value)` => inserts `a::b::c` if current pos is `a`
2. Make a visitor to generate the expanded types tree (every typename points to its actual type value, and not to another typename)
3. make a tree for all the bodies, every leaf will have the bodyId, which will point to a body in a body table
5. create TAST
  - expand all function calls to their body ID (from body tree)
  - expand all type names to their actual type (from types tree)

# Ideas
- Symbol table:
  - Will consist of a stack of scopes, each scope has a lookup table for the scope's symbols
  - When entering a scope => push new scope on stack
    - see RIBS: https://rustc-dev-guide.rust-lang.org/name-resolution.html#scopes-and-ribs
    - Different kinds of Ribs: FunctionRib, NormalRib, etc.
  - When reading symbol => iterate stack from top to bottom till symbol is found
  - Variables can be redeclared: `let mut a = 1; let mut a = "abc";` is OK
- Type checking
  - untyped AST => typed AST: `typecheck(ast)`
  - rustc_hir_analysis: https://doc.rust-lang.org/nightly/nightly-rustc/rustc_hir_analysis/index.html
- AST
  - Implement each node as a Node: Expr, VariableExpr, etc.
  - Node has a virtual method accept, which accepts a visitor
  - Visitor with lambda method to use visitor?
    -> visitor.visit(expr, (expr: VariableExpr) => {/* do something */})
    - https://lesleylai.info/en/ast-in-cpp-part-1-variant
- Everything is an expression (even assignments etc.), except for declarations.
- Functions are function definitions
- AST: https://doc.rust-lang.org/nightly/nightly-rustc/rustc_ast/ast/index.html
- HIR: https://doc.rust-lang.org/nightly/nightly-rustc/rustc_hir/hir/enum.ItemKind.html
  - HIR analysis: https://doc.rust-lang.org/nightly/nightly-rustc/rustc_hir_analysis/index.html
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
