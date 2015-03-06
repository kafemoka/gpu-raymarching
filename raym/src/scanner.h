#pragma once

#include <string>
#include <vector>
#include <iostream>

class Scanner {

public:
    Scanner() {}
    Scanner(std::vector<std::string>& _lines);

    char peek() const;
    char get(bool _skipSpaces = false);
    int getCurrentColumn() const;
    int getCurrentRow() const;
    bool isEOL() const;
    bool isEOS() const;
    void nextLine();
    void nextChar(bool _skipSpaces = false);

private:
    void readLookAhead();

    int m_currentRow;
    int m_currentCol;
    char m_char;
    std::vector<std::string> m_lines;
    std::string m_currentLine;

};
