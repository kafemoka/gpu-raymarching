#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "parser.h"
#include <iostream>


TEST_CASE("[Checks arguments of constructed objects node]", "[Parser]") {
    std::string raymShader = R"END(

        Sphere sphere(vec3(0.0, 0.0, 0.0), 10.0);
        Cube cube(vec3(10.0, 20.0, 0.0));

    )END";

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

    //std::cout << typeid(*sphereStmt.get()).name() << std::endl;

    REQUIRE(stmt1 != nullptr);
    REQUIRE(cubeStmt != nullptr);
    REQUIRE(sphere->getValue() == "sphere");
    REQUIRE(cube->getValue() == "cube");
    REQUIRE(arg1Sphere->getValue() == "vec3(0.0,0.0,0.0)");
    REQUIRE(arg2Sphere->getValue() == "10.0");
    REQUIRE(arg1Cube->getValue() == "vec3(10.0,20.0,0.0)");
}

TEST_CASE("[Checks that two symbols can't be defined by the same identifier]", "[Parser]") {
    std::string raymShader = R"END(
        Sphere identifier(vec3(0.0, 0.0, 0.0), 10.0);
        Cube identifier(vec3(0.0, 0.0, 0.0));
    )END";

    std::shared_ptr<Lexer> lexer(new Lexer());
    lexer->init(raymShader);
    Parser parser(lexer);

    auto ast = parser.parse();
    auto cubeStmt = ast->getRoot()->getChilds()[1];
    auto stmt = std::static_pointer_cast<ASTDeclarationNode>(cubeStmt);

    REQUIRE(stmt == nullptr);
    REQUIRE(parser.getErrors().front() == "Redefinition of symbol identifier");
}

TEST_CASE("[]", "[]") {
    std::string raymShader = R"END(

        Sphere sphere1(vec3(0.0, 0.0, 0.0), 10.0);
        Sphere sphere2(vec3(0.0, 0.0, 0.0), 5.0);
        Cube cube1(vec3(10.0, 20.0, 0.0));
        Cube cube2(vec3(0.0, 0.0, 0.0));

        Object o1 ;

        o1 = (sphere1 + sphere2) / cube1;

        Object o2 = o1 + (cube1 - cube2);

        raymarch(100.0, o2);

    )END";

    std::shared_ptr<Lexer> lexer(new Lexer());
    lexer->init(raymShader);
    Parser parser(lexer);

    auto ast = parser.parse();
    auto errors = parser.getErrors();

    REQUIRE(ast->getRoot()->getChilds().size() == 7);

    for(auto child : ast->getRoot()->getChilds()) {
        auto stmt = std::static_pointer_cast<ASTStatementNode>(child);
        REQUIRE(stmt != nullptr);
        if(stmt) {
            stmt->exec();
        }
    }

    while(errors.size() > 0) {
        std::cout << errors.front() << std::endl;
        errors.pop();
    }
}

