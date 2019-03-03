#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <string>
#include <vector>
#include <unordered_map>

#if MSVC
#include <windows.h>
#endif

using namespace std;

struct Scanner {
    int   Line;
    char* Start;
    char* Current;
    char* LinePos;
};

enum TokenTYPE {
    // Single-character tokens.
    TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE,
    TOKEN_LEFT_SQUARE_BRACE, TOKEN_RIGHT_SQUARE_BRACE,
    TOKEN_COMMA, TOKEN_DOT,
    TOKEN_SEMICOLON, TOKEN_SLASH, TOKEN_STAR, TOKEN_MODULO,

    TOKEN_XOR, TOKEN_NOT, TOKEN_BITWISE_AND, TOKEN_BITWISE_OR,
    TOKEN_QUESTION_MARK, TOKEN_COLON,

    // One or two character tokens.
    TOKEN_BANG, TOKEN_BANG_EQUAL,
    TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
    TOKEN_GREATER, TOKEN_GREATER_EQUAL,
    TOKEN_LESS, TOKEN_LESS_EQUAL,
    TOKEN_PLUS, TOKEN_PLUS_PLUS,
    TOKEN_MINUS, TOKEN_MINUS_MINUS,
    TOKEN_BITWISE_LEFT, TOKEN_BITWISE_RIGHT,
    TOKEN_LOGICAL_AND, TOKEN_LOGICAL_OR,

    TOKEN_PLUS_EQUAL, TOKEN_MINUS_EQUAL,
    TOKEN_BITWISE_LEFT_EQUAL, TOKEN_BITWISE_RIGHT_EQUAL,
    TOKEN_AND_EQUAL, TOKEN_OR_EQUAL, TOKEN_XOR_EQUAL, TOKEN_MODULO_EQUAL,
    TOKEN_STAR_EQUAL, TOKEN_SLASH_EQUAL,

    // Literals.
    TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_NUMBER, TOKEN_TYPE_NAME,

    // Keywords.
    TOKEN_DO, TOKEN_OBJECT, TOKEN_SKONLY, TOKEN_SUBCLASS,
    TOKEN_AND, TOKEN_CLASS, TOKEN_ELSE, TOKEN_FALSE,
    TOKEN_FOR, TOKEN_FUN, TOKEN_IF, TOKEN_NIL, TOKEN_OR,
    TOKEN_PRINT, TOKEN_RETURN, TOKEN_SUPER, TOKEN_THIS,
    TOKEN_TRUE, TOKEN_VAR, TOKEN_WHILE, TOKEN_ENUM,
    TOKEN_SWITCH, TOKEN_BREAK, TOKEN_DEFAULT, TOKEN_CASE,
    TOKEN_CONTINUE, TOKEN_EVENT,

    // HeaderReader token types.
    TOKEN_STRUCT, TOKEN_PUBLIC, TOKEN_PRIVATE, TOKEN_PROTECTED, TOKEN_LEFT_HOOK, TOKEN_RIGHT_HOOK,

    TOKEN_ERROR,
    TOKEN_EOF
};

struct Token {
    TokenTYPE Type;
    char*     Start;
    int       Length;
    int       Line;
    int       Pos;
};

struct Parser {
    Token Current;
    Token Previous;
    bool  HadError;
    bool  PanicMode;
};

struct Member {
    Token Type;
    Token Identifier;
    bool  IsPointer;
    bool  HasValue;
    Token Value;
};
struct Struct {
    Struct*                        BaseClass = NULL;
    Token                          Identifier;
    char*                          Alias = NULL;
    unordered_map<string, Member*> Members;
};
unordered_map<string, Struct*> StructTree;
vector<string> StructsToRemove;
vector<char*> Garbage;
int indent = 0;

void GarbageCollect() {
    for (int i = 0; i < Garbage.size(); i++)
        free(Garbage[i]);
    Garbage.clear();
}

// Printing
enum class PrintColor {
	Default = 0,
	Red,
	Yellow,
	Green,
	Purple,
};
void PrintHeader(FILE* f, const char* str, PrintColor col) {
	int color = 0;
	#if MSVC
		switch (col) {
			case PrintColor::Red: color = 4; break;
			case PrintColor::Yellow: color = 14; break;
			case PrintColor::Green: color = 2; break;
			case PrintColor::Purple: color = 5; break;
			default: color = 0xF; break;
		}
	    CONSOLE_SCREEN_BUFFER_INFO csbi;
	    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
	        SetConsoleTextAttribute(hStdOut, (csbi.wAttributes & 0xF0) | color);
	    }
	    fprintf(f, str);
    	SetConsoleTextAttribute(hStdOut, csbi.wAttributes);
    #else
		switch (col) {
			case PrintColor::Red: color = 91; break;
			case PrintColor::Yellow: color = 93; break;
			case PrintColor::Green: color = 92; break;
			case PrintColor::Purple: color = 95; break;
			default: color = 37; break;
		}
    	fprintf(f, "\x1b[1;%dm%s\x1b[0m", color, str);
    #endif
}
bool ReportError(int line, const char* string, ...) {
    va_list args;
    va_start(args, string);
    char message[1024];
    memset(message, 0, 1024);
    vsprintf(message, string, args);
    PrintHeader(stderr, "error: ", PrintColor::Red);
    if (line > 0)
        fprintf(stderr, "on line %d:\n    %s\n\n", line, message);
    else
        fprintf(stderr, "\n    %s\n\n", message);
    // fflush(stderr);
    exit(-1);
    return false;
}
bool ReportErrorPos(int line, int pos, const char* string, ...) {
    va_list args;
    va_start(args, string);
    char message[1024];
    memset(message, 0, 1024);
    vsprintf(message, string, args);
    PrintHeader(stderr, "error: ", PrintColor::Red);
    if (line > 0)
        fprintf(stderr, "on line %d, position %d:\n    %s\n\n", line, pos, message);
    else
        fprintf(stderr, "\n    %s\n\n", message);
    // fflush(stderr);
    exit(-1);
    return false;
}
// File IO
char* ReadFile(const char* path) {
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        ReportError(0, "Could not open file \"%s\".", path);
        exit(69);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* buffer = (char*)calloc(1, fileSize + 1);
    if (buffer == NULL) {
        ReportError(0, "Not enough memory to read \"%s\".", path);
        exit(69);
    }
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    if (bytesRead < fileSize) {
        ReportError(0, "Could not read file \"%s\".", path);
        exit(69);
    }
    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;
}
// Interpreting
Parser parser;
Scanner scanner;
Token MakeToken(TokenTYPE type) {
    Token token;
    token.Type = type;
    token.Start = scanner.Start;
    token.Length = (int)(scanner.Current - scanner.Start);
    token.Line = scanner.Line;
    token.Pos = scanner.Current - scanner.LinePos;

    return token;
}
Token MakeTokenRaw(TokenTYPE type, const char* message) {
    Token token;
    token.Type = type;
    token.Start = (char*)message;
    token.Length = (int)strlen(message);
    token.Line = 0;
    token.Pos = scanner.Current - scanner.LinePos;

    return token;
}
Token ErrorToken(const char* message) {
    Token token;
    token.Type = TOKEN_ERROR;
    token.Start = (char*)message;
    token.Length = (int)strlen(message);
    token.Line = scanner.Line;
    token.Pos = scanner.Current - scanner.LinePos;

    return token;
}
bool  IsEOF() {
    return *scanner.Current == 0;
}
bool  IsDigit(char c) {
    return c >= '0' && c <= '9';
}
bool  IsHexDigit(char c) {
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}
bool  IsAlpha(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}
bool  IsIdentifierStart(char c) {
    return IsAlpha(c) || c == '$' || c == '_';
}
bool  IsIdentifierBody(char c) {
    return IsIdentifierStart(c) || IsDigit(c);
}
bool  MatchChar(char expected) {
    if (IsEOF()) return false;
    if (*scanner.Current != expected) return false;

    scanner.Current++;
    return true;
}
char  AdvanceChar() {
    return *scanner.Current++;
    // scanner.Current++;
    // return *(scanner.Current - 1);
}
char  Peek() {
    return *scanner.Current;
}
char  PeekPrev() {
    return *(scanner.Current - 1);
}
char  PeekNext() {
    if (IsEOF()) return 0;
    return *(scanner.Current + 1);
}
// HACK: Whitespacing out '#', '~', and etc.
void  SkipWhitespace() {
    while (true) {
        char c = Peek();
        switch (c) {
            case ' ':
            case '#':
            case '~':
            case '\r':
            case '\t':
                AdvanceChar();
                break;

            case '\n':
                scanner.Line++;
                AdvanceChar();
                scanner.LinePos = scanner.Current;
                break;

            case '/':
                if (PeekNext() == '/') {
                    while (Peek() != '\n' && !IsEOF()) AdvanceChar();
                }
                else if (PeekNext() == '*') {
                    while ((PeekPrev() != '*' || Peek() != '/') && !IsEOF()) {
                        if (Peek() == '\n') {
                            scanner.Line++;
                            AdvanceChar();
                            scanner.LinePos = scanner.Current;
                        }
                        else {
                            AdvanceChar();
                        }
                    }
                    if (!IsEOF()) AdvanceChar();
                }
                else
                    return;
                break;

            default:
                return;
        }
    }
}

TokenTYPE CheckKeyword(int start, int length, const char* rest, TokenTYPE type) {
    if (scanner.Current - scanner.Start == start + length && memcmp(scanner.Start + start, rest, length) == 0)
        return type;

    return TOKEN_IDENTIFIER;
}
TokenTYPE IdentifierType() {
    switch (*scanner.Start) {
        case 'a': return CheckKeyword(1, 2, "nd", TOKEN_AND);
        case 'b': return CheckKeyword(1, 4, "reak", TOKEN_BREAK);
        case 'c':
            if (scanner.Current - scanner.Start > 1) {
                switch (*(scanner.Start + 1)) {
                    case 'a': return CheckKeyword(2, 2, "se", TOKEN_CASE);
                    case 'l': return CheckKeyword(2, 3, "ass", TOKEN_CLASS);
                    case 'o': return CheckKeyword(2, 6, "ntinue", TOKEN_CONTINUE);
                }
            }
            break;
        case 'd': return CheckKeyword(1, 1, "o", TOKEN_DO);
        case 'e':
            if (scanner.Current - scanner.Start > 1) {
                switch (*(scanner.Start + 1)) {
                    case 'l': return CheckKeyword(2, 2, "se", TOKEN_ELSE);
                    case 'n': return CheckKeyword(2, 2, "um", TOKEN_ENUM);
                    case 'v': return CheckKeyword(2, 3, "ent", TOKEN_EVENT);
                }
            }
        case 'f':
            if (scanner.Current - scanner.Start > 1) {
                switch (*(scanner.Start + 1)) {
                    case 'a': return CheckKeyword(2, 3, "lse", TOKEN_FALSE);
                    case 'o': return CheckKeyword(2, 1, "r", TOKEN_FOR);
                    case 'u': return CheckKeyword(2, 1, "n", TOKEN_FUN);
                }
            }
            break;
        case 'i': return CheckKeyword(1, 1, "f", TOKEN_IF);
        case 'n': return CheckKeyword(1, 2, "il", TOKEN_NIL);
        case 'o':
            if (scanner.Current - scanner.Start > 1) {
                switch (*(scanner.Start + 1)) {
                    case 'r': return TOKEN_OR;
                    case 'b': return CheckKeyword(2, 4, "ject", TOKEN_OBJECT);
                }
            }
            break;
        case 'p':
            if (scanner.Current - scanner.Start > 1) {
                switch (*(scanner.Start + 1)) {
                    case 'r':
                        if (scanner.Current - scanner.Start > 2) {
                            switch (*(scanner.Start + 2)) {
                                case 'i': return CheckKeyword(3, 4, "vate", TOKEN_PRIVATE);
                                case 'o': return CheckKeyword(3, 6, "tected", TOKEN_PROTECTED);
                            }
                        }
                        break;
                    case 'u': return CheckKeyword(2, 4, "blic", TOKEN_PUBLIC);
                }
            }
            break;
        case 'r': return CheckKeyword(1, 5, "eturn", TOKEN_RETURN);
        case 's':
            if (scanner.Current - scanner.Start > 1) {
                switch (*(scanner.Start + 1)) {
                    case 'k': return CheckKeyword(2, 4, "only", TOKEN_SKONLY);
                    case 't': return CheckKeyword(2, 4, "ruct", TOKEN_STRUCT);
                    case 'u':
                        if (scanner.Current - scanner.Start > 2) {
                            switch (*(scanner.Start + 2)) {
                                case 'b': return CheckKeyword(3, 5, "class", TOKEN_SUBCLASS);
                                case 'p': return CheckKeyword(3, 2, "er", TOKEN_SUPER);
                            }
                        }
                        break;
                    case 'w': return CheckKeyword(2, 4, "itch", TOKEN_SWITCH);
                }
            }
            break;
        case 't':
            if (scanner.Current - scanner.Start > 1) {
                switch (*(scanner.Start + 1)) {
                    case 'h': return CheckKeyword(2, 2, "is", TOKEN_THIS);
                    case 'r': return CheckKeyword(2, 2, "ue", TOKEN_TRUE);
                }
            }
            break;
        case 'v': return CheckKeyword(1, 2, "ar", TOKEN_VAR);
        case 'w': return CheckKeyword(1, 4, "hile", TOKEN_WHILE);
    }

    return TOKEN_IDENTIFIER;
}

Token StringToken() {
    while (Peek() != '"' && !IsEOF()) {
        bool lineBreak = Peek() == '\n';

        AdvanceChar();

        if (lineBreak) {
            scanner.Line++;
            scanner.LinePos = scanner.Current;
        }
    }

    if (IsEOF()) return ErrorToken("Unterminated string.");

    // The closing double-quote.
    AdvanceChar();
    return MakeToken(TOKEN_STRING);
}
Token NumberToken() {
    if (*scanner.Start == '0' && (Peek() == 'x' || Peek() == 'X')) {
        AdvanceChar(); // x
        while (IsHexDigit(Peek()))
            AdvanceChar();
        return MakeToken(TOKEN_NUMBER);
    }

    while (IsDigit(Peek()))
        AdvanceChar();

    // Look for a fractional part.
    if (Peek() == '.' && IsDigit(PeekNext())) {
        // Consume the "."
        AdvanceChar();

        while (IsDigit(Peek()))
            AdvanceChar();
    }

    return MakeToken(TOKEN_NUMBER);
}
Token IdentifierToken() {
    while (IsIdentifierBody(Peek()))
        AdvanceChar();

    return MakeToken(IdentifierType());
}

Token ScanToken() {
    SkipWhitespace();

    scanner.Start = scanner.Current;

    if (IsEOF()) return MakeToken(TOKEN_EOF);

    char c = AdvanceChar();

    if (IsDigit(c)) return NumberToken();
    if (IsIdentifierStart(c)) return IdentifierToken();

    switch (c) {
        case '(': return MakeToken(TOKEN_LEFT_PAREN);
        case ')': return MakeToken(TOKEN_RIGHT_PAREN);
        case '{': return MakeToken(TOKEN_LEFT_BRACE);
        case '}': return MakeToken(TOKEN_RIGHT_BRACE);
        case '[': return MakeToken(TOKEN_LEFT_SQUARE_BRACE);
        case ']': return MakeToken(TOKEN_RIGHT_SQUARE_BRACE);
        case ';': return MakeToken(TOKEN_SEMICOLON);
        case ',': return MakeToken(TOKEN_COMMA);
        case '.': return MakeToken(TOKEN_DOT);
        case ':': return MakeToken(TOKEN_COLON);
        case '?': return MakeToken(TOKEN_QUESTION_MARK);
        // Two-char punctuations
        case '!': return MakeToken(MatchChar('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
        case '=': return MakeToken(MatchChar('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
        case '<': return MakeToken(MatchChar('<') ? (MatchChar('=') ? TOKEN_BITWISE_LEFT_EQUAL : TOKEN_BITWISE_LEFT) : MatchChar('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
        case '>': return MakeToken(MatchChar('>') ? (MatchChar('=') ? TOKEN_BITWISE_RIGHT_EQUAL : TOKEN_BITWISE_RIGHT) : MatchChar('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
        case '%': return MakeToken(MatchChar('=') ? TOKEN_MODULO_EQUAL : TOKEN_MODULO);

        case '+': return MakeToken(MatchChar('+') ? TOKEN_PLUS_PLUS : MatchChar('=') ? TOKEN_PLUS_EQUAL : TOKEN_PLUS);
        case '-': return MakeToken(MatchChar('-') ? TOKEN_MINUS_MINUS : MatchChar('=') ? TOKEN_MINUS_EQUAL : TOKEN_MINUS);
        case '*': return MakeToken(MatchChar('=') ? TOKEN_STAR_EQUAL : TOKEN_STAR);
        case '/': return MakeToken(MatchChar('=') ? TOKEN_SLASH_EQUAL : TOKEN_SLASH);

        case '&': return MakeToken(MatchChar('&') ? TOKEN_LOGICAL_AND : MatchChar('=') ? TOKEN_AND_EQUAL : TOKEN_BITWISE_AND);
        case '|': return MakeToken(MatchChar('|') ? TOKEN_LOGICAL_OR  : MatchChar('=') ? TOKEN_OR_EQUAL  : TOKEN_BITWISE_OR);
        case '^': return MakeToken(MatchChar('=') ? TOKEN_XOR_EQUAL  : TOKEN_XOR);
        // String
        case '"': return StringToken();
    }

    return ErrorToken("Unexpected character.");
}

void ErrorAt(Token* token, const char* message) {
    // Synchronize();
    if (parser.PanicMode) return;
    parser.PanicMode = true;

    if (token->Type == TOKEN_EOF)
        ReportError(token->Line, " at end: %s", message);
    else if (token->Type == TOKEN_ERROR)
        ReportErrorPos(token->Line, token->Pos, "%s", message);
    else
        ReportErrorPos(token->Line, token->Pos, " at '%.*s': %s", token->Length, token->Start, message);

    parser.HadError = true;
}
void Error(const char* message) {
    ErrorAt(&parser.Previous, message);
}
void ErrorAtCurrent(const char* message) {
    ErrorAt(&parser.Current, message);
}

Member* MakeMember(Struct* str, const char* type, const char* label, bool pointer) {
    Member* mt = new Member();
    mt->Type = MakeTokenRaw(TOKEN_TYPE_NAME, type);
    mt->Identifier = MakeTokenRaw(TOKEN_IDENTIFIER, label);
    mt->IsPointer = pointer;
    if (str)
        str->Members[string(label)] = mt;
    return mt;
}
Struct* MakeStruct(const char* label) {
    Struct* mt = new Struct();
    mt->Identifier = MakeTokenRaw(TOKEN_IDENTIFIER, label);
    mt->Alias = (char*)label;
    StructTree[string(label)] = mt;
    return mt;
}
Struct* MakeStructAlias(const char* label, const char* alias) {
    Struct* mt = new Struct();
    mt->Identifier = MakeTokenRaw(TOKEN_IDENTIFIER, label);
    mt->Alias = (char*)alias;
    StructTree[string(mt->Alias)] = mt;
    return mt;
}

void  Advance() {
    parser.Previous = parser.Current;

    while (true) {
        parser.Current = ScanToken();
        if (parser.Current.Type != TOKEN_ERROR)
            break;

        ErrorAtCurrent(parser.Current.Start);
    }
}
Token NextToken() {
    Advance();
    return parser.Previous;
}
Token PeekToken() {
    return parser.Current;
}
Token PrevToken() {
    return parser.Previous;
}
bool  Match(TokenTYPE expected) {
    if (parser.Current.Type == TOKEN_EOF) return false;
    if (parser.Current.Type != expected) return false;

    Advance();
    return true;
}
bool  Check(TokenTYPE expected) {
    if (parser.Current.Type == TOKEN_EOF) return false;
    if (parser.Current.Type != expected) return false;
    return true;
}
void  Consume(TokenTYPE type, const char* message) {
    if (parser.Current.Type == type) {
        Advance();
        return;
    }

    ErrorAtCurrent(message);
}

void Synchronize() {
    Advance();

    while (!IsEOF()) {
        if (PrevToken().Type == TOKEN_SEMICOLON) return;

        switch (PeekToken().Type) {
            case TOKEN_ENUM:
            case TOKEN_IF:
            case TOKEN_WHILE:
            case TOKEN_DO:
            case TOKEN_FOR:
            case TOKEN_SWITCH:
            case TOKEN_CASE:
            case TOKEN_DEFAULT:
            case TOKEN_RETURN:
            case TOKEN_BREAK:
            case TOKEN_CONTINUE:
            case TOKEN_VAR:
            case TOKEN_EVENT:
                return;
            default:
                break;
        }

        Advance();
    }

    parser.PanicMode = false;
}

#define Panic(returnMe) if (parser.PanicMode) { Synchronize(); return returnMe; }

char* currentSubClass = NULL;

struct Environment {
	Environment* 				   Enclosing = NULL;
	unordered_map<string, Member*> Values;
	Environment() { }
	Environment(Environment* enc) { Enclosing = enc; }

	void Define(Member* member) {
        Values[string(member->Identifier.Start, member->Identifier.Length)] = member;
	}
	Member* GetMemberOfStruct(string type, string property) {
		if (StructTree.count(type))
            if (StructTree[type]->Members.count(property))
		         return StructTree[type]->Members[property];

        if (StructTree.count(type))
            if (StructTree[type]->BaseClass)
                return GetMemberOfStruct(string(StructTree[type]->BaseClass->Identifier.Start, StructTree[type]->BaseClass->Identifier.Length), property);

		return NULL;
	}
	bool IsStruct(string type) {
        return StructTree.count(type) > 0;
	}
	Member* Get(string label) {
		if (Values.count(label))
			return Values[label];

		if (Enclosing)
            return Enclosing->Get(label);

        if (currentSubClass)
            return GetMemberOfStruct(currentSubClass, label);

        return GetMemberOfStruct("Object", label);
	}
};

enum ExprType {
    EXPR_UNK,

    EXPR_GET,
    EXPR_CALL,
    EXPR_UNARY,
    EXPR_BINARY,
    EXPR_SUFFIX,
    EXPR_LITERAL,
    EXPR_TERNARY,
    EXPR_GROUPING,
    EXPR_ARRAYFETCH,
    EXPR_ASSIGNMENT,
    EXPR_IDENTIFIER,
};
struct Expr {
    int   Pos;
    int   Line;
    bool  Checked = false;
    char* ParentType = NULL;
    enum ExprType ExprType = EXPR_UNK;
    virtual char* Print() { return NULL; };
};
struct GetExpr : Expr {
    Expr* Object = NULL;
    Expr* Property = NULL;

    int GetType = 0;
    // 0: Normal member access
    // 1: Pointer access
    // 2: Scope access

    GetExpr() { ExprType = EXPR_GET; }
    GetExpr(Expr* o, Expr* p) { Object = o; Property = p; Pos = o->Pos; Line = o->Line; ExprType = EXPR_GET; }

    char* Print() {
        string str;
        if (Object)
            str += Object->Print();

        switch (GetType) {
            case 0:
                str += ".";
                break;
            case 1:
                str += "->";
                break;
            case 2:
                str += "::";
                break;
        }

        if (Property)
            str += Property->Print();

        const char* src = str.c_str();
        char* meme = (char*)calloc(1, strlen(src) + 1);
        sprintf(meme, "%s", src);
        Garbage.push_back(meme);
        return meme;
    };
};
struct CallExpr : Expr {
    Expr* Identifier = NULL;
    vector<Expr*> Arguments;

    CallExpr() { ExprType = EXPR_CALL; }
    CallExpr(Expr* e) { Identifier = e; Pos = e->Pos; Line = e->Line; ExprType = EXPR_CALL; }

    char* Print() {
        string str;
        if (Identifier)
            str += Identifier->Print();
        str += "(";
        for (int i = 0; i < Arguments.size(); i++) {
            if (i != 0)
                str += ", ";
            if (Arguments[i])
                str += Arguments[i]->Print();
        }
        str += ")";

        const char* src = str.c_str();
        char* meme = (char*)calloc(1, strlen(src) + 1);
        sprintf(meme, "%s", src);
        Garbage.push_back(meme);
        return meme;
    };
};
struct UnaryExpr : Expr {
    Token Operator;
    Expr* Right = NULL;

    UnaryExpr() { ExprType = EXPR_UNARY; }
    UnaryExpr(Token o, Expr* r) { Operator = o; Right = r; ExprType = EXPR_UNARY; }

    char* Print() {
        string str;

        if (Operator.Start) {
            char* meme2 = (char*)calloc(1, Operator.Length + 1);
            strncpy(meme2, Operator.Start, Operator.Length);
            meme2[Operator.Length] = 0;
            str += meme2;
            Garbage.push_back(meme2);
        }

        if (Right)
            str += Right->Print();

        const char* src = str.c_str();
        char* meme = (char*)calloc(1, strlen(src) + 1);
        sprintf(meme, "%s", src);
        Garbage.push_back(meme);
        return meme;
    };
};
struct BinaryExpr : Expr {
    Expr* Left = NULL;
    Token Operator;
    Expr* Right = NULL;

    BinaryExpr() { ExprType = EXPR_BINARY; }
    BinaryExpr(Expr* l, Token o, Expr* r) { Left = l; Operator = o; Right = r; ExprType = EXPR_BINARY; }

    char* Print() {
        string str;
        if (Left)
            str += Left->Print();

        if (Operator.Start) {
            str += " ";
            char* meme2 = (char*)calloc(1, Operator.Length + 1);
            strncpy(meme2, Operator.Start, Operator.Length);
            meme2[Operator.Length] = 0;
            str += meme2;
            Garbage.push_back(meme2);
            str += " ";
        }

        if (Right)
            str += Right->Print();

        const char* src = str.c_str();
        char* meme = (char*)calloc(1, strlen(src) + 1);
        sprintf(meme, "%s", src);
        Garbage.push_back(meme);
        return meme;
    };
};
struct SuffixExpr : Expr {
    Expr* Left = NULL;
    Token Operator;

    SuffixExpr() { ExprType = EXPR_SUFFIX; }
    SuffixExpr(Expr* l, Token o) { Left = l; Operator = o; ExprType = EXPR_SUFFIX; }

    char* Print() {
        string str;
        if (Left)
            str += Left->Print();

        if (Operator.Start) {
            char* meme2 = (char*)calloc(1, Operator.Length + 1);
            strncpy(meme2, Operator.Start, Operator.Length);
            meme2[Operator.Length] = 0;
            str += meme2;
            Garbage.push_back(meme2);
        }

        const char* src = str.c_str();
        char* meme = (char*)calloc(1, strlen(src) + 1);
        sprintf(meme, "%s", src);
        Garbage.push_back(meme);
        return meme;
    };
};
struct LiteralExpr : Expr {
    Token Value;

    LiteralExpr() { ExprType = EXPR_LITERAL; }
    LiteralExpr(Token v) { Value = v; Pos = Value.Pos; Line = Value.Line; ExprType = EXPR_LITERAL; }

    char* Print() {
		char* meme = (char*)calloc(1, Value.Length + 1);
		strncpy(meme, Value.Start, Value.Length);
        meme[Value.Length] = 0;
		Garbage.push_back(meme);
		return meme;
	};
};
struct TernaryExpr : Expr {
    Expr* Condition = NULL;
    Expr* True = NULL;
    Expr* False = NULL;

    TernaryExpr() { ExprType = EXPR_TERNARY; }
    TernaryExpr(Expr* c, Expr* t, Expr* f) { Condition = c; True = t; False = f; ExprType = EXPR_TERNARY; }

    char* Print() {
        string str;
        if (Condition)
            str += Condition->Print();
        str += " ? ";
        if (True)
            str += True->Print();
        str += " : ";
        if (False)
            str += False->Print();

        const char* src = str.c_str();
        char* meme = (char*)calloc(1, strlen(src) + 1);
        sprintf(meme, "%s", src);
        Garbage.push_back(meme);
        return meme;
    };
};
struct GroupingExpr : Expr {
    Expr* Group = NULL;

    GroupingExpr() { ExprType = EXPR_GROUPING; }
    GroupingExpr(Expr* g) { Group = g; ExprType = EXPR_GROUPING; }

    char* Print() {
        string str;
        str += "(";
        if (Group)
            str += Group->Print();
        str += ")";

        const char* src = str.c_str();
        char* meme = (char*)calloc(1, strlen(src) + 1);
        sprintf(meme, "%s", src);
        Garbage.push_back(meme);
        return meme;
    };
};
struct ArrayFetchExpr : Expr {
    Expr* Object = NULL;
    Expr* Where = NULL;

    ArrayFetchExpr() { ExprType = EXPR_ARRAYFETCH; }
    ArrayFetchExpr(Expr* o, Expr* p) { Object = o; Where = p; ExprType = EXPR_ARRAYFETCH; }

    char* Print() {
        string str;
        if (Object)
            str += Object->Print();

        str += "[";
        if (Where)
            str += Where->Print();
        str += "]";

        const char* src = str.c_str();
        char* meme = (char*)calloc(1, strlen(src) + 1);
        sprintf(meme, "%s", src);
        Garbage.push_back(meme);
        return meme;
    };
};
struct AssignmentExpr : Expr {
    Expr* Left = NULL;
    Token Operator;
    Expr* Right = NULL;

    AssignmentExpr() { ExprType = EXPR_ASSIGNMENT; }
    AssignmentExpr(Expr* l, Token o, Expr* r) { Left = l; Operator = o; Right = r; ExprType = EXPR_ASSIGNMENT; }

    char* Print() {
        string str;
        if (Left)
            str += Left->Print();
        if (Operator.Start) {
            str += " ";
            char* meme2 = (char*)calloc(1, Operator.Length + 1);
            strncpy(meme2, Operator.Start, Operator.Length);
            meme2[Operator.Length] = 0;
            str += meme2;
            Garbage.push_back(meme2);
            str += " ";
        }
        if (Right)
            str += Right->Print();

        const char* src = str.c_str();
        char* meme = (char*)calloc(1, strlen(src) + 1);
        sprintf(meme, "%s", src);
        Garbage.push_back(meme);
        return meme;
    };
};
struct IdentifierExpr : Expr {
    Token Value;

    IdentifierExpr() { ExprType = EXPR_IDENTIFIER; }
    IdentifierExpr(Token v) { Value = v; Pos = Value.Pos; Line = Value.Line; ExprType = EXPR_IDENTIFIER; }

    char* Print() {
        char* meme = (char*)calloc(1, Value.Length + 1);
		strncpy(meme, Value.Start, Value.Length);
        meme[Value.Length] = 0;
		Garbage.push_back(meme);
		return meme;
	};
};

Expr* GetExpression();
Expr* GetSubscript();
Expr* GetPrimary() {
    if (Match(TOKEN_FALSE))  return new LiteralExpr(parser.Previous);
    if (Match(TOKEN_TRUE))   return new LiteralExpr(parser.Previous);
    if (Match(TOKEN_NIL))    return new LiteralExpr(parser.Previous);

    if (Match(TOKEN_NUMBER)) return new LiteralExpr(parser.Previous);
    if (Match(TOKEN_STRING)) return new LiteralExpr(parser.Previous);

    if (Match(TOKEN_LEFT_PAREN)) {
        Expr* expr = GetExpression();
        Consume(TOKEN_RIGHT_PAREN, "Expected ')' after expression.");
        return new GroupingExpr(expr);
    }

    return new IdentifierExpr(NextToken());
}
Expr* GetCall() {
    Expr* expr = GetPrimary();

    while (true) {
        if (Match(TOKEN_LEFT_PAREN)) {
            CallExpr* cExpr = new CallExpr(expr);

            if (PeekToken().Type != TOKEN_RIGHT_PAREN) {
                do {
                    cExpr->Arguments.push_back(GetExpression());
                }
                while (Match(TOKEN_COMMA));
            }

            Consume(TOKEN_RIGHT_PAREN, "Expected ')' at end of function arguments.");
            return cExpr;
            // return here to disallow function()()
        }
        else if (Match(TOKEN_DOT)) {
            // Consume(TOKEN_IDENTIFIER, "Expected property name after '.'.");
            expr = new GetExpr(expr, GetCall());
            // return new GetExpr(expr, PrevToken());
        }
        else if (Match(TOKEN_LEFT_SQUARE_BRACE)) {
            expr = new ArrayFetchExpr(expr, GetExpression());

			Consume(TOKEN_RIGHT_SQUARE_BRACE, "Expected ']' at end of array subscript identifier.");
        }
        else
            break;
    }

    return expr;
}
Expr* GetSuffix() {
    Expr* expr = GetCall();
    if (Match(TOKEN_PLUS_PLUS) ||
        Match(TOKEN_MINUS_MINUS)) {
        expr = new SuffixExpr(expr, PrevToken());
    }
    return expr;
}
Expr* GetUnary() {
    if (Match(TOKEN_BANG) ||
        Match(TOKEN_NOT) ||
        Match(TOKEN_PLUS) ||
        Match(TOKEN_MINUS) ||
        Match(TOKEN_PLUS_PLUS) ||
        Match(TOKEN_MINUS_MINUS)) {
        Token oper = PrevToken();
        Expr* right = GetUnary();
        return new UnaryExpr(oper, right);
    }

    return GetSuffix();
}
Expr* GetMultiplication() {
    Expr* expr = GetUnary();

    while (Match(TOKEN_SLASH)
        || Match(TOKEN_STAR)
        || Match(TOKEN_MODULO)) {
        Token oper = PrevToken();
        Expr* right = GetUnary();
        expr = new BinaryExpr(expr, oper, right);
    }

    return expr;
}
Expr* GetAddition() {
    Expr* expr = GetMultiplication();

    while (Match(TOKEN_PLUS)
        || Match(TOKEN_MINUS)) {
        Token oper = PrevToken();
        Expr* right = GetMultiplication();
        expr = new BinaryExpr(expr, oper, right);
    }

    return expr;
}
Expr* GetBitwise() {
    Expr* expr = GetAddition();

    while (Match(TOKEN_BITWISE_LEFT)
        || Match(TOKEN_BITWISE_RIGHT)) {
        Token oper = PrevToken();
        Expr* right = GetAddition();
        expr = new BinaryExpr(expr, oper, right);
    }

    return expr;
}
Expr* GetComparison() {
    Expr* expr = GetBitwise();

    while (Match(TOKEN_EQUAL_EQUAL)
        || Match(TOKEN_BANG_EQUAL)
        || Match(TOKEN_LESS)
        || Match(TOKEN_LESS_EQUAL)
        || Match(TOKEN_GREATER)
        || Match(TOKEN_GREATER_EQUAL)) {
        Token oper = PrevToken();
        Expr* right = GetBitwise();
        expr = new BinaryExpr(expr, oper, right);
    }

    return expr;
}
Expr* GetBitwiseAND() {
    Expr* expr = GetComparison();

    while (Match(TOKEN_BITWISE_AND)) {
        Token oper = PrevToken();
        Expr* right = GetComparison();
        expr = new BinaryExpr(expr, oper, right);
    }

    return expr;
}
Expr* GetBitwiseXOR() {
    Expr* expr = GetBitwiseAND();

    while (Match(TOKEN_XOR)) {
        Token oper = PrevToken();
        Expr* right = GetBitwiseAND();
        expr = new BinaryExpr(expr, oper, right);
    }

    return expr;
}
Expr* GetBitwiseOR() {
    Expr* expr = GetBitwiseXOR();

    while (Match(TOKEN_BITWISE_OR)) {
        Token oper = PrevToken();
        Expr* right = GetBitwiseXOR();
        expr = new BinaryExpr(expr, oper, right);
    }

    return expr;
}
Expr* GetLogicalAND() {
    Expr* expr = GetBitwiseOR();

    while (Match(TOKEN_AND) || Match(TOKEN_LOGICAL_AND)) {
        Token oper = PrevToken();
        Expr* right = GetBitwiseOR();
        expr = new BinaryExpr(expr, oper, right);
    }

    return expr;
}
Expr* GetLogicalOR() {
    Expr* expr = GetLogicalAND();

    while (Match(TOKEN_OR) || Match(TOKEN_LOGICAL_OR)) {
        Token oper = PrevToken();
        Expr* right = GetLogicalAND();
        expr = new BinaryExpr(expr, oper, right);
    }

    return expr;
}
Expr* GetTernary() {
    Expr* expr = GetLogicalOR();
    while (Match(TOKEN_QUESTION_MARK)) {
        Expr* tru = GetLogicalOR();
        Consume(TOKEN_COLON, "Expected ':' after expression.");
        Expr* fal = GetLogicalOR();
        expr = new TernaryExpr(expr, tru, fal);
    }

    return expr;
}
Expr* GetAssignment() {
	Expr* expr = GetTernary();
    if (Match(TOKEN_EQUAL) ||
        Match(TOKEN_AND_EQUAL) ||
        Match(TOKEN_OR_EQUAL) ||
        Match(TOKEN_XOR_EQUAL) ||
        Match(TOKEN_BITWISE_LEFT_EQUAL) ||
        Match(TOKEN_BITWISE_RIGHT_EQUAL) ||
        Match(TOKEN_STAR_EQUAL) ||
        Match(TOKEN_MODULO_EQUAL) ||
        Match(TOKEN_SLASH_EQUAL) ||
        Match(TOKEN_PLUS_EQUAL) ||
        Match(TOKEN_MINUS_EQUAL)) {
		Token oper = PrevToken();
		Expr* right = GetTernary();
		expr = new AssignmentExpr(expr, oper, right);
	}
	return expr;
}
Expr* GetExpression() {
    return GetAssignment();
}

bool ValidateExpr(Expr* e, Environment* env) {
    switch (e->ExprType) {
        case EXPR_GET: {
            GetExpr* expr = (GetExpr*)e;

            if (expr->Property->ExprType != EXPR_GET &&
                expr->Property->ExprType != EXPR_CALL &&
                expr->Property->ExprType != EXPR_ARRAYFETCH &&
                expr->Property->ExprType != EXPR_IDENTIFIER)
                return ReportErrorPos(e->Line, e->Pos, "Invalid property '%s'. (%d)", expr->Property->Print(), expr->Property->ExprType);

            char* str = expr->Object->Print();
            expr->Object->ParentType = expr->ParentType;
            if (expr->Object->ExprType == EXPR_ARRAYFETCH) {
                ArrayFetchExpr* a = (ArrayFetchExpr*)expr->Object;
                str = a->Object->Print();
                a->ParentType = expr->ParentType;
            }
            else if (expr->Object->ExprType == EXPR_CALL) {
                CallExpr* a = (CallExpr*)expr->Object;
                str = a->Identifier->Print();
                a->ParentType = expr->ParentType;
            }

            // printf(">>>> For \x1b[91m%s\x1b[m, Object is '\x1b[96m%s\x1b[m.\x1b[91m%s\x1b[m', property is '\x1b[91m%s\x1b[m'.\n", expr->Print(), expr->ParentType ? expr->ParentType : "this", expr->Object->Print(), expr->Property->Print());
            // printf("%s\n", str);

            Member* mem = env->Get(str);
            if (mem) {
                expr->GetType = mem->IsPointer;

                char* perm = (char*)calloc(1, mem->Type.Length + 1);
                memcpy(perm, mem->Type.Start, mem->Type.Length);
                Garbage.push_back(perm);

                expr->Property->ParentType = perm;
                // printf("Type of object is '\x1b[93m%s\x1b[m%s', property is '\x1b[93m%s\x1b[m'.\n", expr->Property->ParentType, expr->GetType ? "*" : "", expr->Property->Print());
            }
            else if (env->IsStruct(str)) {
                expr->GetType = 2;

                expr->Property->ParentType = str;
                // printf("Type (enum) of object is '\x1b[93m%s\x1b[m', property is '\x1b[93m%s\x1b[m'.\n", expr->Property->ParentType, expr->Property->Print());

                /*
                if (expr->Property->ExprType == EXPR_IDENTIFIER) {
                    char* str2 = expr->Property->Print();
                    mem = env->GetMemberOfStruct(str, str2);
                    if (!mem) {
                        return ReportErrorPos(e->Line, e->Pos, "Use of undeclared identifier '%s' in enum '%s'.", str2, str);
                    }
                }
                else if (expr->Property->ExprType == EXPR_ARRAYFETCH) {
                    ArrayFetchExpr* a = (ArrayFetchExpr*)expr->Property;

                    char* str2 = a->Object->Print();
                    mem = env->GetMemberOfStruct(str, str2);
                    if (!mem) {
                        return ReportErrorPos(e->Line, e->Pos, "Use of undeclared identifier '%s' in enum '%s'.", str2, str);
                    }
                }
                else if (expr->Property->ExprType == EXPR_GET) {
                    GetExpr* a = (GetExpr*)expr->Property;

                    char* str2 = a->Object->Print();
                    mem = env->GetMemberOfStruct(str, str2);
                    string typestr = string(mem->Type.Start, mem->Type.Length);
                }
                expr->Property->Checked = true;
                //*/
            }
            else if (expr->ParentType != NULL && (mem = env->GetMemberOfStruct(expr->ParentType, str))) {
                expr->GetType = mem->IsPointer;

                char* parStr = (char*)calloc(1, mem->Type.Length + 1);
                memcpy(parStr, mem->Type.Start, mem->Type.Length);
                Garbage.push_back(parStr);

                expr->Property->ParentType = parStr;
                // printf("Type (sub) of object is '\x1b[93m%s\x1b[m', property is '\x1b[93m%s\x1b[m'.\n", expr->Property->ParentType, expr->Property->Print());
            }
            else {
                return ReportErrorPos(e->Line, e->Pos, "Use of undeclared property '%s'.", str);
            }

            return ValidateExpr(expr->Object, env) && ValidateExpr(expr->Property, env);
            break;
        }
        case EXPR_CALL: {
            CallExpr* expr = (CallExpr*)e;
            // Environment* subEnv = new Environment(env); // for things with block statements
            for (int i = 0; i < expr->Arguments.size(); i++) {
                if (!ValidateExpr(expr->Arguments[i], env))
                    return false;
            }
            // return ValidateExpr(expr->Identifier, env);
            // Don't validate identifier until we have Struct parsing
            break;
        }
        case EXPR_UNARY: {
            UnaryExpr* expr = (UnaryExpr*)e;
            return ValidateExpr(expr->Right, env);
            break;
        }
        case EXPR_BINARY: {
            BinaryExpr* expr = (BinaryExpr*)e;
            return ValidateExpr(expr->Left, env) && ValidateExpr(expr->Right, env);
            break;
        }
        case EXPR_SUFFIX: {
            SuffixExpr* expr = (SuffixExpr*)e;
            return ValidateExpr(expr->Left, env);
            break;
        }
        case EXPR_TERNARY: {
            TernaryExpr* expr = (TernaryExpr*)e;
            return ValidateExpr(expr->Condition, env) && ValidateExpr(expr->True, env) && ValidateExpr(expr->False, env);
            break;
        }
        case EXPR_GROUPING: {
            GroupingExpr* expr = (GroupingExpr*)e;
            return ValidateExpr(expr->Group, env);
            break;
        }
        case EXPR_LITERAL: {
            break;
        }
        case EXPR_ARRAYFETCH: {
            ArrayFetchExpr* expr = (ArrayFetchExpr*)e;
            return ValidateExpr(expr->Where, env);
            break;
        }
        case EXPR_ASSIGNMENT: {
            AssignmentExpr* expr = (AssignmentExpr*)e;
            if (!expr->Left)
                return ReportErrorPos(e->Line, e->Pos, "Expected mutable value on left-side of assignment.");
            if (!expr->Right)
                return ReportErrorPos(e->Line, e->Pos, "Expected value on right-side of assignment.");
            if (expr->Left->ExprType != EXPR_GET &&
                expr->Left->ExprType != EXPR_ARRAYFETCH &&
                expr->Left->ExprType != EXPR_IDENTIFIER)
                return ReportErrorPos(e->Line, e->Pos, "Invalid expression on left-side of assignment.");

            return ValidateExpr(expr->Left, env) && ValidateExpr(expr->Right, env);
        }
        case EXPR_IDENTIFIER: {
            IdentifierExpr* expr = (IdentifierExpr*)e;
            char* str = expr->Print();
            Member* mem = env->Get(str);
            if (mem) {

            }
            else if (env->IsStruct(str)) {

            }
            else if (expr->ParentType != NULL && (mem = env->GetMemberOfStruct(expr->ParentType, str))) {

            }
            else {
                if (!strncmp(str, "Obj_", 4))
                    return true;

                if (expr->ParentType != NULL)
                    return ReportErrorPos(e->Line, e->Pos, "Use of undeclared identifier '%s' in type '%s'.", str, expr->ParentType);

                return ReportErrorPos(e->Line, e->Pos, "Use of undeclared identifier '%s'.", str);
            }
            break;
        }
        default: {
            ReportErrorPos(e->Line, e->Pos, "Unexpected expression type during validation. %d", e->ExprType);
            return false;
        }
    }
    return true;
}

bool IsPointerType(char* str) {
    return
        !strcmp(str, "int") ||
        !strcmp(str, "char") ||
        !strcmp(str, "short") ||
        !strcmp(str, "long") ||
        !strcmp(str, "double") ||
        !strcmp(str, "float") ||
        !strcmp(str, "bool") ||

        !strcmp(str, "Sint8") ||
        !strcmp(str, "Sint16") ||
        !strcmp(str, "Sint32") ||
        !strcmp(str, "Sint64") ||

        !strcmp(str, "Uint8") ||
        !strcmp(str, "Uint16") ||
        !strcmp(str, "Uint32") ||
        !strcmp(str, "Uint64") ||

        !strcmp(str, "int8_t") ||
        !strcmp(str, "int16_t") ||
        !strcmp(str, "int32_t") ||
        !strcmp(str, "int64_t") ||
        !strcmp(str, "uint8_t") ||
        !strcmp(str, "uint16_t") ||
        !strcmp(str, "uint32_t") ||
        !strcmp(str, "uint64_t");
}

enum StmtType {
    STMT_UNK,

    STMT_EXPRESSION,
    STMT_BLOCK,
    STMT_IF,
    STMT_WHILE,
    STMT_DOWHILE,
    STMT_FOR,
    STMT_SWITCH,
    STMT_CASE,
    STMT_DEFAULT,
    STMT_RETURN,
    STMT_BREAK,
    STMT_CONTINUE,
    STMT_VARINIT,
    STMT_VARDECL,
    STMT_EVENT,
};
struct Stmt {
    int Pos;
    int Line;
	enum StmtType StmtType = STMT_UNK;
	virtual char* Print() { return NULL; };
};
struct ExpressionStmt : Stmt {
	Expr* Expression = NULL;
	ExpressionStmt(Expr* expr) { Expression = expr; StmtType = STMT_EXPRESSION; }

	char* Print() {
		string str = "";
		if (Expression)
			str += Expression->Print();
		str += ";\n";

		const char* src = str.c_str();
		char* meme = (char*)calloc(1, strlen(src) + 1);
		sprintf(meme, "%s", src);
		Garbage.push_back(meme);
		return meme;
	};
};
struct BlockStmt : Stmt {
	vector<Stmt*> Declarations;
	BlockStmt() { StmtType = STMT_BLOCK; }

	char* Print() {
		string str;

		str += "{\n";

		indent++;

		for (int i = 0; i < Declarations.size(); i++) {
			for (int d = 0; d <= indent; d++)
				str += "    ";

			if (Declarations[i])
				str += Declarations[i]->Print();
		}

		for (int d = 0; d < indent; d++)
			str += "    ";
		str += "}\n";

		indent--;

		const char* src = str.c_str();
		char* meme = (char*)calloc(1, strlen(src) + 1);
		sprintf(meme, "%s", src);
		Garbage.push_back(meme);
		return meme;
	}
};
struct IfStmt : Stmt {
	Expr*         Conditional = NULL;
	Stmt*         ThenStmt = NULL;
	Stmt*         ElseStmt = NULL;
	IfStmt() { StmtType = STMT_IF; }

	char* Print() {
		string str;

		str += "if (";
		if (Conditional)
			str += Conditional->Print();
		str += ") ";

		if (ThenStmt)
			str += ThenStmt->Print();

		if (ElseStmt) {
			for (int d = 0; d <= indent; d++)
				str += "    ";

			str += "else ";
			str += ElseStmt->Print();
		}
		else str += "\n";

		const char* src = str.c_str();
		char* meme = (char*)calloc(1, strlen(src) + 1);
		sprintf(meme, "%s", src);
		Garbage.push_back(meme);
		return meme;
	}
};
struct WhileStmt : Stmt {
	Expr*         Conditional = NULL;
	Stmt*         BodyStmt = NULL;
	WhileStmt() { StmtType = STMT_WHILE; }

	char* Print() {
		string str;

		str += "while (";
		if (Conditional)
			str += Conditional->Print();
		str += ") ";

		if (BodyStmt)
			str += BodyStmt->Print();

		str += "\n";

		const char* src = str.c_str();
		char* meme = (char*)calloc(1, strlen(src) + 1);
		sprintf(meme, "%s", src);
		Garbage.push_back(meme);
		return meme;
	}
};
struct DoWhileStmt : Stmt {
	Expr*         Conditional = NULL;
	Stmt*         BodyStmt = NULL;
	DoWhileStmt() { StmtType = STMT_DOWHILE; }

	char* Print() {
		string str;

		str += "do ";
		if (BodyStmt)
			str += BodyStmt->Print();
		str += "\n";

		str += "while (";
		if (Conditional)
			str += Conditional->Print();
		str += ");\n";

		const char* src = str.c_str();
		char* meme = (char*)calloc(1, strlen(src) + 1);
		sprintf(meme, "%s", src);
		Garbage.push_back(meme);
		return meme;
	}
};
struct ForStmt : Stmt {
	Stmt*         InitializerStmt = NULL;
	Expr*         ConditionalExpr = NULL;
	Expr*         IncrementExpr = NULL;
	Stmt*         BodyStmt = NULL;
	ForStmt() { StmtType = STMT_FOR; }

	char* Print() {
		string str;

		str += "for (";

		if (InitializerStmt) {
			str += InitializerStmt->Print();
		}
		str += ";";

		if (ConditionalExpr) {
			str += " ";
			str += ConditionalExpr->Print();
		}
		str += ";";

		if (IncrementExpr) {
			str += " ";
			str += IncrementExpr->Print();
		}

		str += ")\n";
		if (BodyStmt)
			str += BodyStmt->Print();
		if (BodyStmt && BodyStmt->StmtType != 2)
			str += "\n";

		const char* src = str.c_str();
		char* meme = (char*)calloc(1, strlen(src) + 1);
		sprintf(meme, "%s", src);
		Garbage.push_back(meme);
		return meme;
	}
};
struct SwitchStmt : Stmt {
	Expr*         Expression = NULL;
	vector<Stmt*> Declarations;
	SwitchStmt() { StmtType = STMT_SWITCH; }

	char* Print() {
		string str;

		str += "switch (";
		if (Expression)
			str += Expression->Print();
		str += ") {\n";

		indent++;

		for (int i = 0; i < Declarations.size(); i++) {
			for (int d = 0; d <= indent; d++)
				str += "    ";

			if (Declarations[i])
				str += Declarations[i]->Print();

			if (Declarations[i]->StmtType == 4)
				indent++;
			if (Declarations[i]->StmtType == 6)
				indent--;
		}

		for (int d = 0; d < indent; d++)
			str += "    ";
		str += "}\n\n";

		indent--;

		const char* src = str.c_str();
		char* meme = (char*)calloc(1, strlen(src) + 1);
		sprintf(meme, "%s", src);
		Garbage.push_back(meme);
		return meme;
	}
};
struct CaseStmt : Stmt {
	Expr*         Expression = NULL;
	CaseStmt(Expr* ast) { Expression = ast; StmtType = STMT_CASE; }

	char* Print() {
		string str;

		str += "case ";
		if (Expression)
			str += Expression->Print();
		str += ":\n";

		const char* src = str.c_str();
		char* meme = (char*)calloc(1, strlen(src) + 1);
		sprintf(meme, "%s", src);
		Garbage.push_back(meme);
		return meme;
	}
};
struct DefaultStmt : Stmt {
	DefaultStmt() { StmtType = STMT_DEFAULT; }

	char* Print() {
		const char* src = "default:\n";
		char* meme = (char*)calloc(1, strlen(src) + 1);
		sprintf(meme, "%s", src);
		Garbage.push_back(meme);
		return meme;
	}
};
struct ReturnStmt : Stmt {
	Expr*         Expression = NULL;
	ReturnStmt(Expr* ast) { Expression = ast; StmtType = STMT_RETURN; }

	char* Print() {
		string str;

		str += "return";
		if (Expression) {
			str += " ";
			str += Expression->Print();
		}
		str += ";\n";

		const char* src = str.c_str();
		char* meme = (char*)calloc(1, strlen(src) + 1);
		sprintf(meme, "%s", src);
		Garbage.push_back(meme);
		return meme;
	}
};
struct BreakStmt : Stmt {
	BreakStmt() { StmtType = STMT_BREAK; }

	char* Print() {
		const char* src = "break;\n";
		char* meme = (char*)calloc(1, strlen(src) + 1);
		sprintf(meme, "%s", src);
		Garbage.push_back(meme);
		return meme;
	}
};
struct ContinueStmt : Stmt {
	ContinueStmt() { StmtType = STMT_CONTINUE; }

	char* Print() {
		const char* src = "continue;\n";
		char* meme = (char*)calloc(1, strlen(src) + 1);
		sprintf(meme, "%s", src);
		Garbage.push_back(meme);
		return meme;
	}
};
struct VariableInit : Stmt {
	Expr* Identifier = NULL; // [a-zA-Z_][a-zA-Z_0-9]*
	Expr* Type = NULL;
    int   Pointer = 0;
	VariableInit(Expr* iden, Expr* type) { Identifier = iden; Type = type; StmtType = STMT_VARINIT; }

	char* Print() {
		string str;
        string type_str;
        if (Type->ExprType != EXPR_ARRAYFETCH)
            type_str += Type->Print();
        else
            type_str += ((ArrayFetchExpr*)Type)->Object->Print();

        for (int i = 0; i < Pointer; i++)
            type_str += "*";

        str += type_str;
        str += " ";
        str += Identifier->Print();
        if (Type->ExprType == EXPR_ARRAYFETCH) {
            str += "[";
            str += ((ArrayFetchExpr*)Type)->Where->Print();
            str += "]";
        }

		const char* src = str.c_str();
        char* meme = (char*)calloc(1, strlen(src) + 1);
        sprintf(meme, "%s", src);
        Garbage.push_back(meme);
        return meme;
	}
};
struct VariableDecl : Stmt {
	Expr* Identifier = NULL;
	Expr* Type = NULL;
	Expr* Value = NULL;
	bool  Portable = false;
    int   Pointer = 0;
	VariableDecl(Expr* iden, Expr* type, Expr* val) { Identifier = iden; Type = type; Value = val; StmtType = STMT_VARDECL; }

	char* Print() {
		string str;
        string type_str;
        if (Type->ExprType != EXPR_ARRAYFETCH)
            type_str += Type->Print();
        else
            type_str += ((ArrayFetchExpr*)Type)->Object->Print();

        for (int i = 0; i < Pointer; i++)
            type_str += "*";

        str += type_str;
        str += " ";
        str += Identifier->Print();
        if (Type->ExprType == EXPR_ARRAYFETCH) {
            str += "[";
            str += ((ArrayFetchExpr*)Type)->Where->Print();
            str += "]";
        }

		if (Value) {
			str += " = ";
			str += Value->Print();
		}
		if (!Portable)
			str += ";\n";

		const char* src = str.c_str();
        char* meme = (char*)calloc(1, strlen(src) + 1);
        sprintf(meme, "%s", src);
        Garbage.push_back(meme);
        return meme;
	}
};
struct EventStmt : Stmt {
	Expr* Label = NULL;
    Expr* Type = NULL;

    char* ObjName = NULL;

    vector<VariableInit*> Parameters;
	vector<Stmt*>         Statements;

    EventStmt() { StmtType = STMT_EVENT; }

	char* Print();
};

bool ValidateStmt(Stmt* s, Environment* env) {
    switch (s->StmtType) {
        case STMT_BLOCK: {
            BlockStmt* stmt = (BlockStmt*)s;

            Environment* subEnv = new Environment(env);
            for (int i = 0; i < stmt->Declarations.size(); i++) {
                if (!ValidateStmt(stmt->Declarations[i], subEnv))
                    return false;
            }
            break;
        }
        case STMT_IF: {
            IfStmt* stmt = (IfStmt*)s;
            Environment* subEnv = new Environment(env);
            if (stmt->ElseStmt) {
                if (!ValidateStmt(stmt->ElseStmt, subEnv))
                    return false;

                delete subEnv;
                subEnv = new Environment(env);
            }
            return ValidateExpr(stmt->Conditional, env) && ValidateStmt(stmt->ThenStmt, subEnv);
        }
        case STMT_WHILE: {
            WhileStmt* stmt = (WhileStmt*)s;
            Environment* subEnv = new Environment(env);
            return ValidateExpr(stmt->Conditional, env) && ValidateStmt(stmt->BodyStmt, subEnv);
        }
        case STMT_DOWHILE: {
            DoWhileStmt* stmt = (DoWhileStmt*)s;
            Environment* subEnv = new Environment(env);
            return ValidateExpr(stmt->Conditional, env) && ValidateStmt(stmt->BodyStmt, subEnv);
        }
        case STMT_FOR: {
            ForStmt* stmt = (ForStmt*)s;
            Environment* subEnv = new Environment(env);
            Environment* subSubEnv = new Environment(subEnv);
            return ValidateStmt(stmt->InitializerStmt, subEnv)
                && ValidateExpr(stmt->ConditionalExpr, subEnv)
                && ValidateExpr(stmt->IncrementExpr, subEnv)
                && ValidateStmt(stmt->BodyStmt, subSubEnv);
        }
        case STMT_SWITCH: {
            SwitchStmt* stmt = (SwitchStmt*)s;
            if (!ValidateExpr(stmt->Expression, env))
                return false;

            Environment* subEnv = new Environment(env);
            for (int i = 0; i < stmt->Declarations.size(); i++) {
                if (!ValidateStmt(stmt->Declarations[i], subEnv))
                    return false;
            }
            break;
        }
        case STMT_CASE: {
            CaseStmt* stmt = (CaseStmt*)s;
            return ValidateExpr(stmt->Expression, env);
        }
        case STMT_DEFAULT:
            break;
        case STMT_RETURN: {
            ReturnStmt* stmt = (ReturnStmt*)s;
            if (!stmt->Expression)
                break;

            return ValidateExpr(stmt->Expression, env);
        }
        case STMT_BREAK:
        case STMT_CONTINUE:
            break;
        case STMT_EVENT: {
            EventStmt* stmt = (EventStmt*)s;
            if (!stmt->Label)
                return ReportError(0, "Expected label for event.");
            if (stmt->Label->ExprType != EXPR_IDENTIFIER)
                return ReportError(0, "Expected identifier for event name.");

            if (stmt->Type && stmt->Type->ExprType != EXPR_IDENTIFIER)
                return ReportError(0, "Expected identifier for event type.");

            Environment* eventEnv = new Environment(env);
            for (int i = 0; i < stmt->Parameters.size(); i++) {
                if (!ValidateStmt(stmt->Parameters[i], eventEnv))
                    return false;

                eventEnv->Define(MakeMember(NULL, stmt->Parameters[i]->Type->Print(), stmt->Parameters[i]->Identifier->Print(), false));
            }
            for (int i = 0; i < stmt->Statements.size(); i++) {
                ValidateStmt(stmt->Statements[i], eventEnv);
            }
            break;
        }
        case STMT_VARINIT: {
            VariableInit* stmt = (VariableInit*)s;
            bool isPoint = true;
            char* str = stmt->Type->Print();
            if (stmt->Type->ExprType == EXPR_ARRAYFETCH)
                str = ((ArrayFetchExpr*)stmt->Type)->Object->Print();
            if (IsPointerType(str))
                isPoint = false;

            stmt->Pointer = isPoint;

            env->Define(MakeMember(NULL, str, stmt->Identifier->Print(), isPoint));
            return true;
        }
        case STMT_VARDECL: {
            VariableDecl* stmt = (VariableDecl*)s;
            bool isPoint = true;
            char* str = stmt->Type->Print();
            if (stmt->Type->ExprType == EXPR_ARRAYFETCH)
                str = ((ArrayFetchExpr*)stmt->Type)->Object->Print();
            if (IsPointerType(str))
                isPoint = false;

            stmt->Pointer = isPoint;

            env->Define(MakeMember(NULL, str, stmt->Identifier->Print(), isPoint));
            if (stmt->Value)
                return ValidateExpr(stmt->Value, env);
            break;
        }
        case STMT_EXPRESSION: {
            ExpressionStmt* stmt = (ExpressionStmt*)s;
            ValidateExpr(stmt->Expression, env);
            break;
        }
        default: {
            ReportError(0, "Unexpected statement type during validation. %d", s->StmtType);
            return false;
        }
    }
    return true;
}

// struct VariableInit;
// struct EventStmt;
struct IObject {
    char* Label = NULL;
    char* SubClass = NULL;
    int   ID = -1;
    bool  SKOnly = false;

    vector<VariableInit*> Variables;
    vector<EventStmt*> Events; // make sure to add ObjName for each one added

    unordered_map<string, Struct*> Enums;

    bool Validate() {
        Environment* env = new Environment();
        currentSubClass = SubClass;

        // Constants
        env->Define(MakeMember(NULL, "void", "NULL", true));
        env->Define(MakeMember(NULL, "int", "IE_NOFLIP", false));
        env->Define(MakeMember(NULL, "int", "IE_FLIPX", false));
        env->Define(MakeMember(NULL, "int", "IE_FLIPY", false));
        // Keywords
        if (SubClass)
            env->Define(MakeMember(NULL, SubClass, "this", true));
        else
            env->Define(MakeMember(NULL, "Object", "this", true));

        for (int i = 0; i < Variables.size(); i++) {
            if (!ValidateStmt(Variables[i], env))
                return false;
        }

        for (int i = 0; i < Events.size(); i++)
            ValidateStmt(Events[i], env);

        return true;
    };

    char* PrintCPP() {
        string str;

        char iddd[16];
        memset(iddd, 0, 16);
        sprintf(iddd, "0x%02X", ID);

        str += "// Object ID: ";
        str += iddd;
        str += "\n";

        str += "// Object Name: ";
        str += Label;
        str += ".cpp";
        str += "\n";
        str += "\n";

        str += "#include \"";
        str += Label;
        str += ".h\"\n";
        str += "\n";
        str += "typedef IMath Math;\n";
        str += "\n";

        for (int i = 0; i < Events.size(); i++) {
			Events[i]->ObjName = Label;
            str += Events[i]->Print();
        }

		const char* src = str.c_str();
        char* meme = (char*)calloc(1, strlen(src) + 1);
        sprintf(meme, "%s", src);
        Garbage.push_back(meme);
        return meme;
    }
    char* PrintH() {
        string str;
        string upper(Label);
        std::transform(upper.begin(), upper.end(), upper.begin(), [](unsigned char c) -> unsigned char { return ::toupper(c); });

        str += "#ifndef ";
        str += upper;
        str += "_H";
        str += "\n";
        str += "#define ";
        str += upper;
        str += "_H";
        str += "\n";
        str += "\n";

        str += "class ";
        str += Label;
        str += ";";
        str += "\n";
        str += "\n";
        str += "#include <Utils/Standard.h>\n\n";
        str += "#include <Engine/IApp.h>\n";
        str += "#include <Engine/ISprite.h>\n\n";
        str += "#include <Game/Object.h>\n";
        str += "#include <Game/LevelScene.h>\n";
        str += "#include <Game/Objects/Gen/ObjectListing.h>\n";
        str += "\n";
        str += "class ";
        str += Label;
        if (SubClass) {
            str += ": public ";
            str += SubClass;
        }
        else {
            str += ": public Object";
        }
        str += " {\n";

        str += "public:";
        str += "    \n";
        for (unordered_map<string, Struct*>::iterator it = Enums.begin(); it != Enums.end(); it++) {
            str += "    enum ";
            str += it->second->Alias;
            str += " {\n";
            for (unordered_map<string, Member*>::iterator itm = it->second->Members.begin(); itm != it->second->Members.end(); itm++) {
                str += "        ";
                str += string(itm->second->Identifier.Start, itm->second->Identifier.Length);
                str += " = ";
                str += string(itm->second->Value.Start, itm->second->Value.Length);
                str += ",\n";
            }
            str += "    };\n";
        }
        str += "    \n";

        for (int i = 0; i < Variables.size(); i++) {
            str += "    ";

            str += Variables[i]->Print();
            str += ";\n";
        }

        str += "    \n";

        for (int i = 0; i < Events.size(); i++) {
            str += "    ";
            if (Events[i]->Type)
                str += Events[i]->Type->Print();
            else
                str += "void";

            str += " ";
            str += Events[i]->Label->Print();
            str += "(";
            for (int d = 0; d < Events[i]->Parameters.size(); d++) {
                if (d != 0)
                    str += ", ";
                str += Events[i]->Parameters[d]->Type->Print();
                str += " ";
                str += Events[i]->Parameters[d]->Identifier->Print();
            }
            str += ");\n";
        }

        str += "};\n\n";


        str += "#endif /* ";
        str += upper;
        str += "_H */";
        str += "\n";

		const char* src = str.c_str();
        char* meme = (char*)calloc(1, strlen(src) + 1);
        sprintf(meme, "%s", src);
        Garbage.push_back(meme);
        return meme;
    }
};

IObject* currentObj = NULL;

char* EventStmt::Print() {
    string str;
    if (Type)
        str += Type->Print();
    else
        str += "void";

    indent = 0;

    str += " ";
    str += ObjName;

    str += "::";

    str += Label->Print();
    str += "(";
    for (int i = 0; i < Parameters.size(); i++) {
        if (i != 0)
            str += ", ";
        str += Parameters[i]->Type->Print();
        str += " ";
        str += Parameters[i]->Identifier->Print();
    }
    str += ") {\n";

    if (!strcmp(Label->Print(), "Create")) {
        for (int d = 0; d <= indent; d++)
            str += "    ";

        if (currentObj->SubClass) {
            str += currentObj->SubClass;
            str += "::Create();\n";
        }
        else {
            str += "Object::Create();\n";
        }
        // TODO: have it add the others
    }

    for (int i = 0; i < Statements.size(); i++) {
        for (int d = 0; d <= indent; d++)
            str += "    ";

        if (Statements[i])
            str += Statements[i]->Print();
    }

    if (!strcmp(Label->Print(), "Update")) {
        for (int d = 0; d <= indent; d++)
            str += "    ";
        str += "Object::Update();\n";
    }
    else if (!strcmp(Label->Print(), "Render")) {
        for (int d = 0; d <= indent; d++)
            str += "    ";
        // str += "Object::Render(CamX, CamY);\n";
    }

    for (int d = 0; d < indent; d++)
        str += "    ";
    str += "}\n\n";

    const char* src = str.c_str();
    char* meme = (char*)calloc(1, strlen(src) + 1);
    sprintf(meme, "%s", src);
    Garbage.push_back(meme);
    return meme;
}

Stmt* GetStatement();

Stmt* GetVariableInitialization() {
	Expr* label = GetExpression();

	Expr* type = NULL;
	if (Match(TOKEN_COLON))
		type = GetExpression();
	else
		type = new IdentifierExpr(MakeTokenRaw(TOKEN_TYPE_NAME, "int"));

	return new VariableInit(label, type);
}
Stmt* GetVariableDeclaration() {
	Expr* label = GetExpression();

	Expr* type = NULL;
	if (Match(TOKEN_COLON))
		type = GetTernary();

	Expr* expr = NULL;
	if (Match(TOKEN_EQUAL))
		expr = GetExpression();

	Consume(TOKEN_SEMICOLON, "Expected ';' after variable declaration.");
	return new VariableDecl(label, type, expr);
}
Stmt* GetObjectIDDeclaration() {
    Token token = PeekToken();
	Expr* id = GetExpression();

    if (id->ExprType != EXPR_LITERAL) {
        ReportErrorPos(token.Line, token.Pos, "Expected constant number after 'object' keyword.");
        return NULL;
    }
    else if (((LiteralExpr*)id)->Value.Type != TOKEN_NUMBER) {
        ReportErrorPos(token.Line, token.Pos, "Expected constant number after 'object' keyword.");
        return NULL;
    }

	char* strID = id->Print();
	if (strstr(strID, "x"))
		currentObj->ID = strtoul(strID, NULL, 16);
	else if (strstr(strID, "X"))
		currentObj->ID = strtoul(strID, NULL, 16);
	else if (strstr(strID, "."))
		strtod(strID, NULL);
	else
		currentObj->ID = strtoul(strID, NULL, 10);


	Consume(TOKEN_SEMICOLON, "Expected ';' after object ID declaration.");
	return NULL;
}
Stmt* GetSubclassDeclaration() {
    Token token = NextToken();
    if (token.Type != TOKEN_IDENTIFIER) {
        ReportErrorPos(token.Line, token.Pos, "Expected identifier after 'subclass' keyword.");
        return NULL;
    }
    char* copy = (char*)calloc(1, token.Length + 1);
    strncpy(copy, token.Start, token.Length);
    copy[token.Length] = 0;
	currentObj->SubClass = copy;

	Consume(TOKEN_SEMICOLON, "Expected ';' after subclass declaration.");
	return NULL;
}
Stmt* GetEventDeclaration() {
	EventStmt* stmt = new EventStmt();

	stmt->Label = GetPrimary();
    Consume(TOKEN_LEFT_PAREN, "Expected '(' after 'event'.");
	if (!Match(TOKEN_RIGHT_PAREN)) {
		while (true) {
			Match(TOKEN_VAR);
			stmt->Parameters.push_back((VariableInit*)GetVariableInitialization());
			if (!Match(TOKEN_COMMA))
				break;
		}
		Consume(TOKEN_RIGHT_PAREN, "Expected ')' after event parameters.");
	}
	// Return type
	if (Match(TOKEN_COLON))
		stmt->Type = GetExpression();
	else
		stmt->Type = new IdentifierExpr(MakeTokenRaw(TOKEN_TYPE_NAME, "void"));

	Consume(TOKEN_LEFT_BRACE, "Expected '{' at start of event block.");
	while (PeekToken().Type != TOKEN_RIGHT_BRACE) {
		stmt->Statements.push_back(GetStatement());
	}
	Consume(TOKEN_RIGHT_BRACE, "Expected '}' at end of event block.");

	return stmt;
}
Stmt* GetEnumDeclaration() {
	Expr* label = NULL;
	if (!Match(TOKEN_LEFT_BRACE)) {
		label = GetPrimary();
		Consume(TOKEN_LEFT_BRACE, "Expected '{' after enum label.");
	}

    if (!label || label->ExprType != EXPR_IDENTIFIER) {
        ReportErrorPos(PrevToken().Line, PrevToken().Pos, "Expected identifier for enum label.");
        return NULL;
    }

    char* stre = label->Print();
    Struct* strEnum = MakeStruct(stre);
    StructsToRemove.push_back(stre);

    currentObj->Enums[string(stre)] = strEnum;

	int lastValue = 0;
	while (PeekToken().Type != TOKEN_RIGHT_BRACE) {
		Expr* enumLabel = GetPrimary();

        if (!enumLabel || enumLabel->ExprType != EXPR_IDENTIFIER) {
            ReportErrorPos(PrevToken().Line, PrevToken().Pos, "Expected identifier for enum value label.");
            return NULL;
        }

        Token enumValue;
		if (Match(TOKEN_EQUAL))
			enumValue = PeekToken();
		else {
            char* stre = (char*)calloc(1, 64);
            sprintf(stre, "%d", lastValue);
			lastValue++;
            enumValue = MakeTokenRaw(TOKEN_NUMBER, stre);
        }

        Member* mem = MakeMember(strEnum, "int", enumLabel->Print(), false);
        mem->Value = enumValue;

		Match(TOKEN_COMMA); // , is optional
	}
	Consume(TOKEN_RIGHT_BRACE, "Expected '}' after enum block.");
	return NULL;
}
Stmt* GetSKOnlyDeclaration() {
	// Expr* skonly = GetPrimary();
    currentObj->SKOnly = true; //!strcmp(skonly->Print(), "true");
	// GetPrimary();
	Consume(TOKEN_SEMICOLON, "Expected ';' after 'skonly' declaration.");
	return NULL;
}

Stmt* GetExpressionStatement() {
	Expr* expr = GetExpression();
	Consume(TOKEN_SEMICOLON, "Expected ';' after expression.");
	return new ExpressionStmt(expr);
}
Stmt* GetIfStatement() {
	IfStmt* stmt = new IfStmt();
	Consume(TOKEN_LEFT_PAREN, "Expected '(' after 'if'.");
	stmt->Conditional = GetExpression();
	Consume(TOKEN_RIGHT_PAREN, "Expected ')' after condition.");
	stmt->ThenStmt = GetStatement();
	if (Match(TOKEN_ELSE)) {
		stmt->ElseStmt = GetStatement();
    }
	return stmt;
}
Stmt* GetDoWhileStatement() {
	DoWhileStmt* stmt = new DoWhileStmt();
	stmt->BodyStmt = GetStatement();
	Consume(TOKEN_WHILE, "Expected 'while' after 'do' statement.");
	Consume(TOKEN_LEFT_PAREN, "Expected '(' after 'while'.");
	stmt->Conditional = GetExpression();
	Consume(TOKEN_RIGHT_PAREN, "Expected ')' after condition.");
	Consume(TOKEN_SEMICOLON, "Expected ';' after while clause.");
	return stmt;
}
Stmt* GetSwitchStatement() {
	SwitchStmt* stmt = new SwitchStmt();
	Consume(TOKEN_LEFT_PAREN, "Expected '(' after 'switch'.");
	stmt->Expression = GetExpression();
	Consume(TOKEN_RIGHT_PAREN, "Expected ')' after comparison value.");

	Consume(TOKEN_LEFT_BRACE, "Expected '{' at start of switch block.");
	while (PeekToken().Type != TOKEN_RIGHT_BRACE) {
		stmt->Declarations.push_back(GetStatement());
	}
	Consume(TOKEN_RIGHT_BRACE, "Expected '}' at end of switch block.");

	return stmt;
}
Stmt* GetWhileStatement() {
	WhileStmt* stmt = new WhileStmt();
	Consume(TOKEN_LEFT_PAREN, "Expected '(' after 'while'.");
	stmt->Conditional = GetExpression();
	Consume(TOKEN_RIGHT_PAREN, "Expected ')' after condition.");
	stmt->BodyStmt = GetStatement();
	return stmt;
}
Stmt* GetForStatement() {
	ForStmt* stmt = new ForStmt();
	Consume(TOKEN_LEFT_PAREN, "Expected '(' after 'for'.");

	stmt->InitializerStmt = NULL;
	if (Match(TOKEN_VAR)) {
		stmt->InitializerStmt = GetVariableDeclaration();
        ((VariableDecl*)stmt->InitializerStmt)->Portable = true;
	}
	else if (!Match(TOKEN_SEMICOLON)) {
		stmt->InitializerStmt = new ExpressionStmt(GetExpression());
	}

	stmt->ConditionalExpr = NULL;
	if (!Match(TOKEN_SEMICOLON)) {
		stmt->ConditionalExpr = GetExpression();
        Consume(TOKEN_SEMICOLON, "Expected ';' after conditional statement.");
	}

	stmt->IncrementExpr = NULL;
	if (!Match(TOKEN_RIGHT_PAREN)) {
		stmt->IncrementExpr = GetExpression();
        Consume(TOKEN_RIGHT_PAREN, "Expected ')' after for clauses.");
	}

	stmt->BodyStmt = GetStatement();
	return stmt;
}
Stmt* GetFromStatement() {
	Consume(TOKEN_LEFT_PAREN, "Expected '(' after 'from'.");
	// Stmt* var = GetVariableDeclaration();
	GetVariableDeclaration();
	// Consume(s, "->", "expected '->' after variable declaration.");
	// Expr* endExpr = GetExpression();
	GetExpressionStatement();
	Consume(TOKEN_RIGHT_PAREN, "Expected ')' after condition.");
	// Stmt* fromblock = GetStatement();
	GetStatement();
	return NULL;
}
Stmt* GetBlockStatement() {
	BlockStmt* stmt = new BlockStmt();
	while (PeekToken().Type != TOKEN_RIGHT_BRACE) {
		stmt->Declarations.push_back(GetStatement());
	}
	Consume(TOKEN_RIGHT_BRACE, "Expected '}' after block statement.");
	return stmt;
}
Stmt* GetReturnStatement() {
	Expr* value = NULL;
	if (!Match(TOKEN_SEMICOLON)) {
		value = GetExpression();
		Consume(TOKEN_SEMICOLON, "Expected ';' after return value.");
	}
	return new ReturnStmt(value);
}
Stmt* GetBreakStatement() {
	Consume(TOKEN_SEMICOLON, "Expected ';' after break;");
	return new BreakStmt();
}
Stmt* GetContinueStatement() {
	Consume(TOKEN_SEMICOLON, "Expected ';' after continue;");
	return new ContinueStmt();
}
Stmt* GetCaseStatement() {
	Expr* value = GetExpression();
	Consume(TOKEN_COLON, "Expected ':' after case value.");
	return new CaseStmt(value);
}
Stmt* GetDefaultStatement() {
	Consume(TOKEN_COLON, "Expected ':' after default statement.");
	return new DefaultStmt();
}
Stmt* GetStatement() {
	if (Match(TOKEN_IF))
		return GetIfStatement();
	else if (Match(TOKEN_DO))
		return GetDoWhileStatement();
	else if (Match(TOKEN_FOR))
		return GetForStatement();
	else if (Match(TOKEN_VAR))
		return GetVariableDeclaration();
	// else if (Match(s, "from"))
	// 	return GetFromStatement();
	else if (Match(TOKEN_WHILE))
		return GetWhileStatement();
	else if (Match(TOKEN_RETURN))
		return GetReturnStatement();
	else if (Match(TOKEN_SWITCH))
		return GetSwitchStatement();
	else if (Match(TOKEN_CASE))
		return GetCaseStatement();
	else if (Match(TOKEN_DEFAULT))
		return GetDefaultStatement();
	else if (Match(TOKEN_BREAK))
		return GetBreakStatement();
	else if (Match(TOKEN_CONTINUE))
		return GetContinueStatement();
	else if (Match(TOKEN_LEFT_BRACE))
		return GetBlockStatement();
    else if (Check(TOKEN_IDENTIFIER) || Check(TOKEN_THIS))
        return GetExpressionStatement();

	else if (Match(TOKEN_ELSE)) {
        Token token = PrevToken();
    	ReportErrorPos(token.Line, token.Pos, "Unexpected statement '%.*s'.", token.Length, token.Start);
		// s->Rewind();
		// ReportError(s->Line(), "unexpected statement '%s'.", s->Next());
		return NULL;
	}

    Token token = PeekToken();
    ReportErrorPos(token.Line, token.Pos, "Unexpected statement '%.*s'.", token.Length, token.Start);

	return NULL;
}

Stmt* GetDeclaration() {
	if (Match(TOKEN_VAR)) { // globals
		VariableInit* stmt = (VariableInit*)GetVariableInitialization();
		Consume(TOKEN_SEMICOLON, "Expected ';' after variable initialization.");
		currentObj->Variables.push_back(stmt);
		return stmt;
	}
	else if (Match(TOKEN_OBJECT))
		return GetObjectIDDeclaration();
	else if (Match(TOKEN_SUBCLASS))
		return GetSubclassDeclaration();
	else if (Match(TOKEN_SKONLY))
		return GetSKOnlyDeclaration();
	else if (Match(TOKEN_ENUM))
		return GetEnumDeclaration();
	else if (Match(TOKEN_EVENT)) {
		EventStmt* stmt = (EventStmt*)GetEventDeclaration();
		currentObj->Events.push_back(stmt);
		return stmt;
	}

    Token token = NextToken();
    Stmt* stmt = GetStatement();
    if (!stmt)
	   ReportErrorPos(token.Line, token.Pos, "Unexpected declaration '%.*s'.", token.Length, token.Start);
	return stmt;
}

bool printOut = false;
void ScanForStructs(char* source) {
    scanner.Line = 1;
    scanner.Start = source;
    scanner.Current = source;
    scanner.LinePos = source;

    parser.HadError = false;
    parser.PanicMode = false;

    while (true) {
        Advance();
        if (PeekToken().Type == TOKEN_EOF)
            break;

        switch (NextToken().Type) {
            case TOKEN_ENUM: {
                if (!Match(TOKEN_CLASS))
                    break;

                Token label = NextToken();

                if (!Match(TOKEN_LEFT_BRACE))
                    break;

                // printf("enum %.*s;\n", label.Length, label.Start);

                char* stre = (char*)calloc(1, label.Length + 1);
                memcpy(stre, label.Start, label.Length);
                Garbage.push_back(stre);

                Struct* strEnum = MakeStruct(stre);
                while (PeekToken().Type != TOKEN_RIGHT_BRACE) {
                    switch (NextToken().Type) {
                        case TOKEN_IDENTIFIER: {
                            Token name = PrevToken();

                            if (Match(TOKEN_EQUAL)) {
                                NextToken(); // Value
                                Match(TOKEN_COMMA);
                            }

                            char* strd = (char*)calloc(1, name.Length + 1);
                            memcpy(strd, name.Start, name.Length);
                            Garbage.push_back(strd);

                            MakeMember(strEnum, "int", strd, false);

                            // printf("    %.*s;\n", name.Length, name.Start);
                        }
                        default: break;
                    }
                }
                Match(TOKEN_RIGHT_BRACE);
                break;
            }
            case TOKEN_CLASS:
            case TOKEN_STRUCT: {
                TokenTYPE tt = PrevToken().Type;

                Token label = NextToken();

                if (Check(TOKEN_SEMICOLON))
                    break; // we don't need "class Name;"

                char* stre = (char*)calloc(1, label.Length + 1);
                memcpy(stre, label.Start, label.Length);
                Garbage.push_back(stre);

                Struct* strStruct = NULL;
                if (!memcmp(label.Start, "IMath", label.Length)) {
                    strStruct = MakeStructAlias(stre, (char*)"Math");
                }
                else {
                    strStruct = MakeStruct(stre);
                }

                if (Match(TOKEN_COLON)) {
                    Token parent = NextToken();
                    if (parent.Type == TOKEN_PUBLIC ||
                        parent.Type == TOKEN_PRIVATE ||
                        parent.Type == TOKEN_PROTECTED)
                        parent = NextToken();

                    string str(parent.Start, parent.Length);
                    if (StructTree.count(str))
                        strStruct->BaseClass = StructTree[str];
                }

                if (!Match(TOKEN_LEFT_BRACE))
                    break;

                if (printOut)
                    printf("struct %.*s;\n", label.Length, label.Start);

                bool canget = tt != TOKEN_CLASS;
                while (PeekToken().Type != TOKEN_RIGHT_BRACE) {
                    switch (NextToken().Type) {
                        case TOKEN_PUBLIC:
                            canget = true;
                            Match(TOKEN_COLON);
                            break;
                        case TOKEN_PRIVATE:
                        case TOKEN_PROTECTED:
                            canget = false;
                            Match(TOKEN_COLON);
                            break;

                        case TOKEN_STRUCT: {
                            while (PeekToken().Type != TOKEN_RIGHT_BRACE) {
                                Advance();
                            }
                            Match(TOKEN_RIGHT_BRACE);
                        }

                        case TOKEN_ENUM: {
                            Match(TOKEN_IDENTIFIER);

                            if (!Match(TOKEN_LEFT_BRACE))
                                break;

                            // printf("enum %.*s;\n", label.Length, label.Start);
                            while (PeekToken().Type != TOKEN_RIGHT_BRACE) {
                                switch (NextToken().Type) {
                                    case TOKEN_IDENTIFIER: {
                                        Token name = PrevToken();

                                        if (Match(TOKEN_EQUAL)) {
                                            NextToken(); // Value
                                            Match(TOKEN_COMMA);
                                        }

                                        char* strd = (char*)calloc(1, name.Length + 1);
                                        memcpy(strd, name.Start, name.Length);
                                        Garbage.push_back(strd);

                                        MakeMember(strStruct, "int", strd, false);
                                    }
                                    default: break;
                                }
                            }
                            Match(TOKEN_RIGHT_BRACE);
                            break;
                        }

                        case TOKEN_IDENTIFIER: {
                            int isPointer = 0;
                            Token type = PrevToken();
                            if (!memcmp(type.Start, "virtual", type.Length) && memcmp(PeekToken().Start, label.Start, PeekToken().Length)) {
                                Advance();
                                type = PrevToken();
                            }
                            else if (!memcmp(type.Start, "static", type.Length) && memcmp(PeekToken().Start, label.Start, PeekToken().Length)) {
                                Advance();
                                type = PrevToken();
                            }
                            else if (!memcmp(type.Start, "const", type.Length) && memcmp(PeekToken().Start, label.Start, PeekToken().Length)) {
                                Advance();
                                type = PrevToken();
                            }
                            else if (!memcmp(type.Start, "unsigned", type.Length) && memcmp(PeekToken().Start, label.Start, PeekToken().Length)) {
                                Advance();
                                type = PrevToken();
                            }
                            else if (!memcmp(type.Start, "vector", type.Length) && memcmp(PeekToken().Start, label.Start, PeekToken().Length)) {
                                Match(TOKEN_LESS);
                                type = PeekToken();
                                while (!Match(TOKEN_GREATER))
                                    Advance();
                            }

                            if (Match(TOKEN_LESS)) {
                                while (!Match(TOKEN_GREATER))
                                    Advance();
                            }

                            Match(TOKEN_BITWISE_AND);

                            while (Match(TOKEN_STAR))
                                isPointer++;
                            Token name = type;
                            if (memcmp(type.Start, label.Start, type.Length))
                                name = NextToken();

                            if (Match(TOKEN_EQUAL)) {
                                while (!Match(TOKEN_SEMICOLON))
                                    Advance();
                            }
                            else if (Match(TOKEN_LEFT_PAREN)) {
                                while (!Match(TOKEN_RIGHT_PAREN))
                                    Advance();

                                if (!Match(TOKEN_SEMICOLON))
                                    while (PrevToken().Type != TOKEN_RIGHT_BRACE || PeekToken().Type != TOKEN_SEMICOLON)
                                        Advance();
                            }
                            Match(TOKEN_SEMICOLON);

                            if (canget) {
                                char* strt = (char*)calloc(1, type.Length + 1);
                                memcpy(strt, type.Start, type.Length);
                                Garbage.push_back(strt);

                                char* strd = (char*)calloc(1, name.Length + 1);
                                memcpy(strd, name.Start, name.Length);
                                Garbage.push_back(strd);

                                MakeMember(strStruct, strt, strd, isPointer);

                                if (printOut)
                                    printf("    %.*s %.*s;\n", type.Length, type.Start, name.Length, name.Start);
                            }
                            break;
                        }

                        default:
                            break;
                    }
            	}

                Match(TOKEN_RIGHT_BRACE);
                // Match(TOKEN_SEMICOLON); // next loop consumes the token anyway
            }
            default: {
                // printf("token %.*s\n", PeekToken().Length, PeekToken().Start);
                break;
            }
        }
    }

    free(source);
}

void InitAll() {
    StructTree.clear();
#if MSVC
    ScanForStructs(ReadFile("../../ImpostorEngine2/source/Game/LevelSceneExt.h"));
    ScanForStructs(ReadFile("../../ImpostorEngine2/gen/Engine/IScene.h"));
    ScanForStructs(ReadFile("../../ImpostorEngine2/gen/Game/LevelScene.h"));
    ScanForStructs(ReadFile("../../ImpostorEngine2/gen/Game/Sound.h"));
    ScanForStructs(ReadFile("../../ImpostorEngine2/gen/Engine/IMath.h"));
    ScanForStructs(ReadFile("../../ImpostorEngine2/gen/Engine/IAudio.h"));
    ScanForStructs(ReadFile("../../ImpostorEngine2/gen/Engine/IGraphics.h"));
    ScanForStructs(ReadFile("../../ImpostorEngine2/source/Engine/IHeader.hh")); // for Animation structs
    ScanForStructs(ReadFile("../../ImpostorEngine2/gen/Engine/ISprite.h"));
    ScanForStructs(ReadFile("../../ImpostorEngine2/gen/Engine/IApp.h"));
    ScanForStructs(ReadFile("../../ImpostorEngine2/source/Game/Player.h"));
    ScanForStructs(ReadFile("../../ImpostorEngine2/source/Game/Object.h"));
	ScanForStructs(ReadFile("../../ImpostorEngine2/gen/Game/SaveGame.h"));
#else
	ScanForStructs(ReadFile("/Users/justin/Sonic3Mixed/ImpostorEngine2/source/Game/LevelSceneExt.h"));
	ScanForStructs(ReadFile("/Users/justin/Sonic3Mixed/ImpostorEngine2/gen/Engine/IScene.h"));
	ScanForStructs(ReadFile("/Users/justin/Sonic3Mixed/ImpostorEngine2/gen/Game/LevelScene.h"));
	ScanForStructs(ReadFile("/Users/justin/Sonic3Mixed/ImpostorEngine2/gen/Game/Sound.h"));
	ScanForStructs(ReadFile("/Users/justin/Sonic3Mixed/ImpostorEngine2/gen/Engine/IMath.h"));
	ScanForStructs(ReadFile("/Users/justin/Sonic3Mixed/ImpostorEngine2/gen/Engine/IAudio.h"));
	ScanForStructs(ReadFile("/Users/justin/Sonic3Mixed/ImpostorEngine2/gen/Engine/IGraphics.h"));
	ScanForStructs(ReadFile("/Users/justin/Sonic3Mixed/ImpostorEngine2/source/Engine/IHeader.hh")); // for Animation structs
	ScanForStructs(ReadFile("/Users/justin/Sonic3Mixed/ImpostorEngine2/gen/Engine/ISprite.h"));
	ScanForStructs(ReadFile("/Users/justin/Sonic3Mixed/ImpostorEngine2/gen/Engine/IApp.h"));
	ScanForStructs(ReadFile("/Users/justin/Sonic3Mixed/ImpostorEngine2/source/Game/Player.h"));
	ScanForStructs(ReadFile("/Users/justin/Sonic3Mixed/ImpostorEngine2/source/Game/Object.h"));
	ScanForStructs(ReadFile("/Users/justin/Sonic3Mixed/ImpostorEngine2/gen/Game/SaveGame.h"));
#endif
}

int ParseIScript(char* filename, char* outputname, char* objectname) {
    char* source = ReadFile(filename);
    if (!source)
        return -1;
    scanner.Line = 1;
    scanner.Start = source;
    scanner.Current = source;
    scanner.LinePos = source;

    parser.HadError = false;
    parser.PanicMode = false;

    currentObj = new IObject();
    currentObj->Label = objectname;

    Advance();
    while (true) {
        if (PeekToken().Type == TOKEN_EOF)
            break;

        GetDeclaration();
    }
    if (!currentObj->Validate())
        return -1;

    char* out;
    FILE* outf;
    string str;

    str = outputname;
    str += "cpp";
    outf = fopen(str.c_str(), "wb");
    if (!outf) {
        PrintHeader(stderr, "error: ", PrintColor::Red);
        fprintf(stderr, "Could not open file for write: %s (is parent folder missing?)\n", str.c_str());
        fflush(stderr);
        exit(-1);
    }
    out = currentObj->PrintCPP();
    fprintf(outf, "%s", out);
    fclose(outf);

    str = outputname;
    str += "h";
    outf = fopen(str.c_str(), "wb");
    if (!outf) {
        PrintHeader(stderr, "error: ", PrintColor::Red);
        fprintf(stderr, "Could not open file for write: %s (is parent folder missing?)\n", str.c_str());
        fflush(stderr);
        exit(-1);
    }
    out = currentObj->PrintH();
    fprintf(outf, "%s", out);
    fclose(outf);

    for (int i = 0; i < StructsToRemove.size(); i++)
        StructTree.erase(StructTree.find(StructsToRemove[i]));
    StructsToRemove.clear();

    return currentObj->ID;
}
/*
int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("No source code path!\n");
        printf("Usage:\n");
        printf("    %s [options] path\n", argv[0]);
        return 0;
    }

    char finalpath[256];
    #if WIN32
        _fullpath(finalpath, argv[1], 256);
    #else
        realpath(argv[1], finalpath);
    #endif

    InitAll();
    ParseIScript((char*)"/Users/Justin/Sonic3Mixed/ImpostorEngine2/source/Game/Objects/Common/Monitor.obj", (char*)"Monitor.", (char*)"Monitor");
}
*/
