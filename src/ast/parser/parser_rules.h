#pragma once
#include "../ast_node.h"
#include "../ast_driver.h"
#include "nodes/core.h"
#include "nodes/expr.h"
#include "nodes/item.h"
#include "nodes/stmt.h"
#include "util.h"
#include <vector>

class ASTDriver;

class ParserRules {
  private:
    ASTDriver& driver;
  public:
    ParserRules(ASTDriver& driver);

    P<AST::Crate> initItems(P<AST::Item> $1);
    P<AST::Crate> addItem(P<AST::Crate> $1, P<AST::Item> $2);
    P<AST::Item> item(AST::ItemKind $1);

    P<AST::FnDef> functionDefinition(AST::Ident $1, P<AST::Block> $2);

    P<AST::Block> initStatements(P<AST::Stmt> $1);
    P<AST::Block> initStatements();
    P<AST::Block> addStatement(P<AST::Block> $1, P<AST::Stmt> $2);
    P<AST::Stmt> statement(AST::StmtKind $1);
    P<AST::Semi> semi(P<AST::Expr> $1);

    P<AST::Let> let(AST::Ident $1, AST::LocalKind $2);

    AST::Ident ident(std::string $1);
    AST::Path path(AST::Ident $1);

    P<AST::Expr> expr(AST::ExprKind $1);

    AST::Lit lit(AST::LitKind $1);

    P<AST::Binary> binary(P<AST::Expr> $1, AST::BinOp $2, P<AST::Expr> $3);
};
