#include "parser_rules.h"
#include "nodes/core.h"
#include "nodes/expr.h"
#include "nodes/item.h"
#include "nodes/stmt.h"
#include "nodes/type.h"
#include <spdlog/spdlog.h>

ParserRules::ParserRules(ASTDriver& driver) : driver{driver} {
}

P<AST::Crate> ParserRules::crate(Vec<P<AST::Item>> $1) {
  return P<AST::Crate>(new AST::Crate{
    .id = driver.create_node(),
    .items = std::move($1)
  });
}

Vec<P<AST::Item>> ParserRules::initItems() {
    auto $$ = Vec<P<AST::Item>>{};
    return $$;
}

Vec<P<AST::Item>> ParserRules::addItem(Vec<P<AST::Item>> $1, P<AST::Item> $2) {
  $1.push_back(std::move($2));
  return std::move($1);
}

P<AST::Item> ParserRules::item(AST::ItemKind $1) {
  return P<AST::Item>(new AST::Item{
    .id = driver.create_node(),
    .kind = std::move($1)
  });
}

P<AST::FnDef> ParserRules::functionDefinition(AST::Ident $1, P<AST::FnSig> $2,  P<AST::Block> $3) {
  return P<AST::FnDef>(new AST::FnDef{
      .id = driver.create_node(),
      .ident = $1,
      .signature  = std::move($2),
      .body = std::move($3)
  });
}

P<AST::FnSig> ParserRules::functionSignature(Vec<P<AST::Param>> $1, P<AST::Ty> $2) {
  return P<AST::FnSig>(new AST::FnSig {
    .id = driver.create_node(),
    .inputs = std::move($1),
    .output = std::move($2)
  });
}

P<AST::Block> ParserRules::initStatements() {
  auto $$ = P<AST::Block>(new AST::Block {
    .id = driver.create_node(),
    .statements{}
  });
  return std::move($$);
}

P<AST::Block> ParserRules::addStatement(P<AST::Block> $1, P<AST::Stmt> $2) {
  $1->statements.push_back(std::move($2));
  return std::move($1);
}

P<AST::Stmt> ParserRules::statement(AST::StmtKind $1) {
  return P<AST::Stmt>(new AST::Stmt{
    .id = driver.create_node(),
    .kind = std::move($1)
  });
}

P<AST::Ret> ParserRules::ret(Opt<P<AST::Expr>> $1) {
  if ($1.has_value()) {
    return P<AST::Ret>(new AST::Ret{
      .expr = std::move($1.value())
    }); 
  }
  else {
    return P<AST::Ret>(new AST::Ret{
      .expr = this->expr(this->lit(std::monostate{}))
    }); 
  }
}

P<AST::Semi> ParserRules::semi(P<AST::Expr> $1) {
  return P<AST::Semi>(new AST::Semi{
    .expr = std::move($1)
  });
}

P<AST::Assign> ParserRules::assign(AST::Ident $1, P<AST::Expr> $2) {
  return P<AST::Assign>(new AST::Assign {
    .id = driver.create_node(),
    .lhs = $1,
    .rhs = std::move($2)
  });
}


P<AST::Assign> ParserRules::opAssign(AST::Ident $1, AST::BinOp $2, P<AST::Expr> $3) {
  return P<AST::Assign>(new AST::Assign {
    .id = driver.create_node(),
    .lhs = $1,
    .rhs = this->expr(this->binary(
      this->expr(this->initPath(this->pathSegment($1))),
      $2,
      std::move($3)))
  });
}

P<AST::Let> ParserRules::let(P<AST::Pat> $1, P<AST::Ty> $2, AST::LocalKind $3, bool mut) {
  return P<AST::Let>(new AST::Let {
      .id = driver.create_node(),
      .pat = std::move($1),
      .ty = std::move($2),
      .kind = std::move($3),
      .mut = mut
  });
}

AST::Ident ParserRules::ident(std::string $1) {
  return AST::Ident {
    .identifier = std::move($1)
  };
}

AST::Path ParserRules::initPath(AST::PathSegment segment) {
  return AST::Path {
    .segments = std::vector<AST::PathSegment>{segment}
  };
}

AST::Path ParserRules::initPath() {
  return AST::Path {
    .segments = std::vector<AST::PathSegment>{}
  };
}

AST::Path ParserRules::addPathSegment(AST::Path $1, AST::PathSegment $2) {
  $1.segments.push_back($2);
  return $1;
}

AST::PathSegment ParserRules::pathSegment(AST::Ident $1) {
  return AST::PathSegment {
    .id = driver.create_node(),
    .ident = $1,
  };
}

AST::Break ParserRules::breakExpr() {
  return AST::Break {
    .id = driver.create_node()
  };
}

P<AST::If> ParserRules::ifExpr(P<AST::Expr> $1, P<AST::Block> $2, Opt<P<AST::Expr>> $3) {
  return P<AST::If>(new AST::If {
    .id = driver.create_node(),
    .cond = std::move($1),
    .then_block = std::move($2),
    .else_block = std::move($3)
  });
}

P<AST::While> ParserRules::whileExpr(P<AST::Expr> $1, P<AST::Block> $2) {
  return P<AST::While>(new AST::While {
    .id = driver.create_node(),
    .cond = std::move($1),
    .block = std::move($2)
  });
}

P<AST::Loop> ParserRules::loopExpr(P<AST::Block> $2) {
  return P<AST::Loop>(new AST::Loop {
    .id = driver.create_node(),
    .block = std::move($2)
  });
}

Vec<P<AST::Expr>> ParserRules::initExprs(P<AST::Expr> $1) {
  auto $$ = initExprs();
  $$.push_back(std::move($1));
  return std::move($$);
}
Vec<P<AST::Expr>> ParserRules::initExprs() {
  Vec<P<AST::Expr>> $$ = {};
  return std::move($$);
}
Vec<P<AST::Expr>> ParserRules::addExpr(Vec<P<AST::Expr>> $1, P<AST::Expr> $2) {
  $1.push_back(std::move($2));
  return std::move($1);
}

P<AST::Expr> ParserRules::expr(AST::ExprKind $1) {
  return P<AST::Expr>(new AST::Expr {
      .id = driver.create_node(),
      .kind = AST::ExprKind {
          std::move($1)
      }
  });
}

AST::Lit ParserRules::lit(AST::LitKind $1) {
  return AST::Lit {
    .id = driver.create_node(),
    .kind = std::move($1)
  };
}

P<AST::Binary> ParserRules::binary(P<AST::Expr> $1, AST::BinOp $2, P<AST::Expr> $3) {
  return P<AST::Binary>(new AST::Binary {
    .id = driver.create_node(),
    .op = $2,
    .lhs = std::move($1),
    .rhs = std::move($3)
  });
}
P<AST::Unary> ParserRules::unary(AST::UnOp $1, P<AST::Expr> $2) {
  return P<AST::Unary>(new AST::Unary {
    .id = driver.create_node(),
    .op = $1,
    .expr = std::move($2)
  });
}

P<AST::Ty> ParserRules::ty(AST::TyKind $1) {
  return P<AST::Ty>(new AST::Ty {
    .kind = std::move($1)
  });
}

Vec<P<AST::Param>> ParserRules::initParams(P<AST::Param> $1){
  auto $$ = initParams();
  $$.push_back(std::move($1));
  return $$;
}
Vec<P<AST::Param>> ParserRules::initParams(){
  auto $$ = Vec<P<AST::Param>>();
  return $$;
}
Vec<P<AST::Param>> ParserRules::addParam(Vec<P<AST::Param>> $1, P<AST::Param> $2){
  $1.push_back(std::move($2));
  return $1;
}
P<AST::Param> ParserRules::param(P<AST::Pat> $1, P<AST::Ty> $2, bool mut){
  return P<AST::Param>(new AST::Param {
    .id = driver.create_node(),
    .pat = std::move($1),
    .ty = std::move($2),
    .mut = mut
  });
}

P<AST::Pat> ParserRules::pat(AST::PatKind pat){
  return P<AST::Pat>(new AST::Pat {
    .kind = std::move(pat)
  });
}

P<AST::Call> ParserRules::call(AST::Path $1, Vec<P<AST::Expr>> $2){
  return P<AST::Call>(new AST::Call {
    .id = driver.create_node(),
    .path = std::move($1),
    .params = std::move($2)
  });
}

P<AST::Print> ParserRules::print(std::string $1) {
  AST::PrintKind kind;
  if ($1.size() > 2 && $1.front() == '{' && $1.back() == '}') {
    kind = {this->ident($1.substr(1, $1.size() - 2))};
  } else {
    kind = {$1};
  }
  return P<AST::Print>(new AST::Print {
    .id = driver.create_node(),
    .kind = std::move(kind)
  });
}

std::string ParserRules::str(std::string $1) {
  return $1.substr(1, $1.size() - 2);
}

P<AST::Mod> ParserRules::module(AST::Ident $1, Vec<P<AST::Item>> $2) {
  return P<AST::Mod>(new AST::Mod {
    .id = driver.create_node(),
    .ident = std::move($1),
    .items = std::move($2)
  });
}
