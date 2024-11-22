#include "parser_rules.h"
#include "nodes/item.h"
#include "nodes/stmt.h"

ParserRules::ParserRules(ASTDriver& driver) : driver{driver} {}

P<AST::Crate> ParserRules::initItems(P<AST::Item> $1) {
    auto $$ = P<AST::Crate>(new AST::Crate{
      driver.create_node(),
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
      driver.create_node(),
      $1,
      std::move($2)
  });
}

P<AST::Block> ParserRules::initStatements(P<AST::Stmt> $1) {
  auto $$ = P<AST::Block>(new AST::Block {
    driver.create_node(),
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
    driver.create_node(),
    std::move($1)
  });
}
