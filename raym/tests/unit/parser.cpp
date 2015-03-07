#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "parser.h"
#include <iostream>

std::string raymShader = R"END(

    Sphere sphere(vec3(0.0, 0.0, 0.0), 10.0);
    Cube cube(vec3(10.0, 20.0, 0.0));

)END";

TEST_CASE("[Checks arguments of constructed objects node]", "[Parser]") {
    std::shared_ptr<Lexer> lexer(new Lexer());

    lexer->init(raymShader);

    Parser parser(lexer);

    auto ast = parser.parse();

    auto sphereStmt = ast->getRoot()->getChilds()[0];
    auto cubeStmt = ast->getRoot()->getChilds()[1];

    auto stmt1 = std::static_pointer_cast<ASTDeclarationNode>(sphereStmt);
    auto sphere = std::static_pointer_cast<ASTValueNode>(stmt1->getChilds()[0]);
    auto arg1Sphere = std::static_pointer_cast<ASTValueNode>(stmt1->getChilds()[1]);
    auto arg2Sphere = std::static_pointer_cast<ASTValueNode>(stmt1->getChilds()[2]);

    auto stmt2 = std::static_pointer_cast<ASTDeclarationNode>(cubeStmt);
    auto cube = std::static_pointer_cast<ASTValueNode>(cubeStmt->getChilds()[0]);
    auto arg1Cube = std::static_pointer_cast<ASTValueNode>(stmt2->getChilds()[1]);

    REQUIRE(stmt1 != nullptr);
    REQUIRE(cubeStmt != nullptr);
    REQUIRE(sphere->getValue() == "sphere");
    REQUIRE(cube->getValue() == "cube");
    REQUIRE(arg1Sphere->getValue() == "vec3(0.0,0.0,0.0)");
    REQUIRE(arg2Sphere->getValue() == "10.0");
    REQUIRE(arg1Cube->getValue() == "vec3(10.0,20.0,0.0)");
}

