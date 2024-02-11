
#include "Scanner.h"



// Description:  Util:  string + char
string operator+(string &lhs, char &rhs) {
    char c[2]; c[0] = rhs; c[1] = 0;
    return lhs+c;
}


// Description:  Display a Token
ostream &operator<<(ostream &os, Token &rhs) {
    if (rhs.tt == eof) os << "eof";
    else if (rhs.tt == errtok) os << "err";
    else if (rhs.tt == integer) os << rhs.val;
    else os << rhs.text;

    return os;
} 


// Description:  Constructor
Scanner::Scanner(istream &str) {
    this->str = &str;
    buf[0] = buf[1] = 0;
}


// Description:  Util:  Test for newline
int newl(char c) { return (c == '\n'); }


// Description:  Return the next token
Token Scanner::getnext() {
    Token ret; ret.text = "";
    if (buf[0] == 0) { buf[0] = str->get(); }


    // collapse whitespace
    while ((buf[0] ==' ')|| (buf[0] == 13)) {
        buf[0] = str->get(); 
        if(str->eof() || (buf[0] == '\n')) break;
    }


    // case 1: eof
    if (str->eof() || buf[0] == '\n') { ret.tt = eof; ret.text = ""; return ret; }


    // case 2: numerical-   [0-9]+
    if (isdigit(buf[0])) {
        ret.tt = integer; ret.text = buf;
        buf[0] = str->get();
        while (isdigit(buf[0])) {
            ret.text += buf;
            buf[0] = str->get();
        }
        ret.val = stod(ret.text, NULL);
        if (buf[0] == ' ' || (buf[0] == 13)) buf[0] = 0;
        return ret;
    }


    // case 3: symbol
    ret.text = buf; 
    if (buf[0] == '+') { ret.tt = pltok; buf[0] = 0; }
    else if (buf[0] == '-') { ret.tt = mitok; buf[0] = 0; }
    else if (buf[0] == '*') { ret.tt = asttok; buf[0] = 0; }
    else if (buf[0] == '/') { ret.tt = slashtok; buf[0] = 0; }
    else if (buf[0] == '(') { ret.tt = lptok; buf[0] = 0; }
    else if (buf[0] == ')') { ret.tt = rptok; buf[0] = 0; }
    else { ret.tt = errtok; buf[0] = 0; }
    return ret;
}


