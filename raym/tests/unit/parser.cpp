#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "parser.h"
#include <iostream>

std::string raymShader = R"END(
    Sphere sphere(vec3(0.0, 0.0, 0.0), 10.0);
)END";

TEST_CASE("", "") {
    std::shared_ptr<Lexer> lexer(new Lexer());
    lexer->init(raymShader);
    Parser parser(lexer);
    auto ast = parser.parse();

    for(auto& node : ast->getRoot()->getChilds()) {
        auto stmt = std::static_pointer_cast<ASTDeclarationNode>(node);
        auto sphere = std::static_pointer_cast<ASTValueNode>(stmt->getChilds()[0]);
        REQUIRE(sphere->getValue() == "sphere");
    }
}

