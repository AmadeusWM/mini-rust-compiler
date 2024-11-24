#include "parser_rules.h"
#include "nodes/core.h"
#include "nodes/expr.h"
#include "nodes/item.h"
#include "nodes/stmt.h"
#include <spdlog/spdlog.h>

ParserRules::ParserRules(ASTDriver& driver) : driver{driver} {
}

P<AST::Crate> ParserRules::initItems(P<AST::Item> $1) {
    auto $$ = P<AST::Crate>(new AST::Crate{
      .id = driver.create_node(),
    });
    $$->items.push_back(std::move($1));
    return $$;
}


P<AST::Crate> ParserRules::addItem(P<AST::Crate> $1, P<AST::Item> $2) {
  $1->items.push_back(std::move($2));
  return $1;
}

P<AST::Item> ParserRules::item(AST::ItemKind $1) {
  return P<AST::Item>(new AST::Item{
    .id = driver.create_node(),
    .kind = std::move($1)
  });
}

P<AST::FnDef> ParserRules::functionDefinition(AST::Ident $1, P<AST::Block> $2) {
  return P<AST::FnDef>(new AST::FnDef{
      .id = driver.create_node(),
      .ident = $1,
      .body = std::move($2)
  });
}

P<AST::Block> ParserRules::initStatements(P<AST::Stmt> $1) {
  auto $$ = initStatements();
  $$->statements.push_back(std::move($1));
  return std::move($$);
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

P<AST::Semi> ParserRules::semi(P<AST::Expr> $1) {
  return P<AST::Semi>(new AST::Semi{
    .expr = std::move($1)
  });
}

P<AST::Let> ParserRules::let(AST::Ident $1, AST::LocalKind $2) {
  return P<AST::Let>(new AST::Let {
      .id = driver.create_node(),
      .pat = AST::Pat($1),
      .kind = std::move($2)
  });
}

AST::Ident ParserRules::ident(std::string $1) {
  return AST::Ident {
    .identifier = std::move($1)
  };
}

AST::Path ParserRules::path(AST::Ident $1) {
  return AST::Path {
    .segments = std::vector<AST::PathSegment>{
      AST::PathSegment {
        .id = driver.create_node(),
        .ident = $1
      }
    }
  };
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
