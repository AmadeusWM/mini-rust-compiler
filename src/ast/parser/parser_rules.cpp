#include "parser_rules.h"
#include "nodes/item.h"
#include "nodes/stmt.h"

ParserRules::ParserRules(ASTDriver& driver) : driver{driver} {}

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
    driver.create_node(),
    std::move($1)
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
  auto $$ = P<AST::Block>(new AST::Block {
    .id = driver.create_node(),
  });
  $$->statements.push_back(std::move($1));
  return $$;
}

P<AST::Block> ParserRules::addStatement(P<AST::Block> $1, P<AST::Stmt> $2) {
  $1->statements.push_back(std::move($2));
  return $1;
}

P<AST::Stmt> ParserRules::statement(AST::StmtKind $1) {
  return P<AST::Stmt>(new AST::Stmt{
    .id = driver.create_node(),
    .kind = std::move($1)
  });
}

P<AST::Let> ParserRules::letStatement(AST::Ident $1, AST::LocalKind $2) {
  return P<AST::Let>(new AST::Let {
      .id = driver.create_node(),
      .pat = AST::Pat($1),
      .kind = std::move($2)
  });
}
