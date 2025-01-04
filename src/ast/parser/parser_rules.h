#pragma once
#include "../ast_node.h"
#include "../ast_driver.h"
#include "nodes/core.h"
#include "nodes/expr.h"
#include "nodes/item.h"
#include "nodes/stmt.h"
#include "nodes/type.h"
#include "util.h"
#include <vector>

class ASTDriver;

class ParserRules {
  private:
    ASTDriver& driver;
  public:
    ParserRules(ASTDriver& driver);

    P<AST::Crate> initItems(P<AST::Item> $1);
    P<AST::Crate> initItems();
    P<AST::Crate> addItem(P<AST::Crate> $1, P<AST::Item> $2);
    P<AST::Item> item(AST::ItemKind $1);

    P<AST::FnDef> functionDefinition(AST::Ident $1, P<AST::FnSig> $2, P<AST::Block> $3);

    P<AST::FnSig> functionSignature(Vec<P<AST::Param>> $1, P<AST::Ty> $2);

    P<AST::Block> initStatements(P<AST::Stmt> $1);
    P<AST::Block> initStatements();
    P<AST::Block> addStatement(P<AST::Block> $1, P<AST::Stmt> $2);
    P<AST::Stmt> statement(AST::StmtKind $1);

    P<AST::Semi> semi(P<AST::Expr> $1);

    P<AST::Let> let(P<AST::Pat> $1, P<AST::Ty> $2, AST::LocalKind $3);

    P<AST::Ret> ret(P<AST::Expr> $1);

    AST::Ident ident(std::string $1);
    AST::Path path(AST::Ident $1);

    AST::Break breakExpr();
    P<AST::If> ifExpr(P<AST::Expr> $1, P<AST::Block> $2, Opt<P<AST::Expr>> $3);
    P<AST::While> whileExpr(P<AST::Expr> $1, P<AST::Block> $2);
    P<AST::Loop> loopExpr(P<AST::Block> $2);

    Vec<P<AST::Expr>> initExprs(P<AST::Expr> $1);
    Vec<P<AST::Expr>> initExprs();
    Vec<P<AST::Expr>> addExpr(Vec<P<AST::Expr>> $1, P<AST::Expr> $2);
    P<AST::Expr> expr(AST::ExprKind $1);

    P<AST::Assign> assign(AST::Ident $1, P<AST::Expr> $2);

    AST::Lit lit(AST::LitKind $1);

    P<AST::Binary> binary(P<AST::Expr> $1, AST::BinOp $2, P<AST::Expr> $3);
    P<AST::Unary> unary(AST::UnOp $1, P<AST::Expr> $2);

    P<AST::Ty> ty(AST::TyKind $1);

    Vec<P<AST::Param>> initParams(P<AST::Param> $1);
    Vec<P<AST::Param>> initParams();
    Vec<P<AST::Param>> addParam(Vec<P<AST::Param>> $1, P<AST::Param> $2);

    P<AST::Param> param(P<AST::Pat> $1, P<AST::Ty> $2);

    P<AST::Pat> pat(AST::PatKind pat);

    P<AST::Call> call(AST::Path $1, Vec<P<AST::Expr>> $2);

    P<AST::Print> print(std::string $1);

    std::string str(std::string $1);
};
