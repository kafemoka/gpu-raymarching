#include "scanner.h"

Scanner::Scanner(std::vector<std::string>& _lines) : m_lines(_lines) {
    m_currentRow = 0;
    m_currentCol = 0;

    if(_lines.size() > 0) {
        m_currentLine = _lines[m_currentRow];
        readLookAhead();
    }
}

void Scanner::readLookAhead() {
    m_char = m_currentLine[m_currentCol];
}

char Scanner::peek() const {
    return m_char;
}

char Scanner::get() {
    if(isspace(peek())) {
        nextChar();
    }

    char old = peek();

    nextChar();

    return old;
}

void Scanner::nextChar() {
    if(isspace(peek())) {
        while(isspace(peek())) {
            m_currentCol++;
            readLookAhead();
        }
        m_currentCol--;
    }

    m_currentCol++;

    if(!isEOL()) {
        readLookAhead();
    } 
}

void Scanner::nextLine() {
    m_currentRow++;
    
    if(!isEOS()) {
        m_currentCol = 0;
        m_currentLine = m_lines[m_currentRow];
    }
}

int Scanner::getCurrentColumn() const {
    return m_currentCol;
}

int Scanner::getCurrentRow() const {
    return m_currentRow;
}

bool Scanner::isEOL() const {
    if(std::all_of(m_currentLine.begin() + m_currentCol, m_currentLine.end(), isspace)) {
        return true;
    }

    return m_currentLine.length() == 0 || m_currentCol == m_currentLine.length();
}

bool Scanner::isEOS() const {
    return m_currentRow == m_lines.size();
}

