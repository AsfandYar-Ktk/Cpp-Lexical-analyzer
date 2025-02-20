#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;
enum Asfand_Token
{
    IF,
    ELSE,
    WHILE,
    DO,
    FOR,
    BREAK,
    EXIT,
    DIGIT,
    VARIABLE,
    INT,
    STRING,
    FLOAT,
    COUT,
    OPR,
    CPR,
    SEMICLN,
    MAIN,
    EQUAL,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    OBR,
    CBR,
    OUTPUT_STR,
    RETURN,
    INCREMENT,
    DECREMENT,
    PLUS_EQUAL,
    MINUSEQUAL,
    COMMENT,
    OPSTREAM,
    INSTREAM,
    LESS_THAN,
    GREATER_THAN,
    COLON,
    OSQBR,
    CSQBR,
    COMMA,
    EQUALITY,
    GREATER_EQUAL,
    LESS_EQUAL
};
struct Token
{
    Asfand_Token token_var;
    string Token_name;
    int Token_value = NULL;
    int symbol_table_value = NULL;
    void Give_values(Asfand_Token token_var, string Token_name, int Token_value)
    {
        this->token_var = token_var;
        this->Token_name = Token_name;
        this->Token_value = Token_value;
    };
};
const int table_size = 50;
Token Symbol_table[table_size];
fstream NewFile;
Token Asfand_lexcial_analysis();
Token Asfand_search(string S_token, bool &present);
Token Asfand_make_entry(string S_token);
void display_table();
bool checkFlag = true;
bool check_equalto = false;
bool check_conditional_statement = false;
char chr;
void E();
void E_dash();
void T_dash();
void T();
void F();
void ignore_space();
Token global_token;
void E()
{
    T();
    E_dash();
}
void E_dash()
{
    global_token = Asfand_lexcial_analysis();
    if (global_token.Token_value == PLUS || global_token.Token_value == MINUS ||
        global_token.Token_value == MULTIPLY || global_token.Token_value == DIVIDE)
    {
        ignore_space();
        if (NewFile.eof())
        {
            checkFlag = false;
            return;
        }
        T();
        E_dash();
    }
    else
    {
        NewFile.putback(chr);
        return;
    }
}
void T()
{
    F();
    T_dash();
}
void T_dash()
{
    global_token = Asfand_lexcial_analysis();
    if (global_token.Token_value == PLUS || global_token.Token_value == MINUS ||
        global_token.Token_value == MULTIPLY || global_token.Token_value == DIVIDE)
    {
        ignore_space();
        if (NewFile.eof())
        {
            checkFlag = false;
            return;
        }
        F();
        T_dash();
    }
    else
    {
        NewFile.putback(chr);
        return;
    }
}
void F()
{
    global_token = Asfand_lexcial_analysis();
    if (global_token.Token_value == DIGIT || global_token.Token_value == VARIABLE)
    {
        ignore_space();
        if (NewFile.eof())
        {
            return;
        }
    }
    else if (chr == '(')
    {
        ignore_space();
        if (NewFile.eof())
        {
            checkFlag = false;
            return;
        }
        E();
        if (chr == ')')
        {
            ignore_space();
            if (NewFile.eof())
            {
                return;
            }
        }
        else
        {
            checkFlag = false;
        }
    }
    else
    {
        checkFlag = false;
        return;
    }
}
bool check_assignment()
{
    NewFile.putback(chr);
    global_token = Asfand_lexcial_analysis();
    if (global_token.Token_value == VARIABLE)
    {
        NewFile.get(chr);
        ignore_space();
        if (chr == '=')
        {
            E();
            if (checkFlag)
            {
                if (chr == ';')
                {
                    return true;
                }
                return false;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}
void ignore_space()
{
    while (isspace(chr) || chr == '\n' || chr == '\t')
    {
        NewFile.get(chr);
        if (NewFile.eof())
        {
            return;
        }
    }
}
bool statement()
{
    Token fun_tok;
    if (isalpha(chr))
    {
        NewFile.putback(chr);
        fun_tok = Asfand_lexcial_analysis();
        if (fun_tok.Token_value == IF)
        {
            NewFile.get(chr);
            ignore_space();
            if (chr == '(')
            {
                NewFile.get(chr);
                ignore_space();
                NewFile.putback(chr);
                global_token = Asfand_lexcial_analysis();
                if (global_token.Token_value == VARIABLE)
                {
                    NewFile.get(chr);
                    ignore_space();
                    if (chr == '=')
                    {
                        NewFile.get(chr);
                        ignore_space();
                        if (chr == '=')
                        {
                            NewFile.get(chr);
                            ignore_space();
                            if (isdigit(chr))
                            {
                                NewFile.get(chr);
                                ignore_space();
                                if (chr == ')')
                                {
                                    NewFile.get(chr);
                                    ignore_space();
                                    if (chr == '{')
                                    {
                                        do
                                        {
                                            NewFile.get(chr);
                                            ignore_space();
                                            if (chr ==
                                                '}')
                                            {
                                                break;
                                            }
                                        } while (statement());
                                        if (chr == '}')
                                        {
                                            NewFile.get(chr);
                                            ignore_space();
                                            if (NewFile.eof())
                                            {
                                                check_conditional_statement = true;
                                                return check_conditional_statement;
                                            }
                                            else if (chr == '}')
                                            {
                                                NewFile.putback(chr);
                                                check_conditional_statement = true;
                                                return check_conditional_statement;
                                            }
                                            else
                                            {
                                                NewFile.putback(chr);
                                                fun_tok = Asfand_lexcial_analysis();
                                                if (fun_tok.Token_value == ELSE)
                                                {
                                                    NewFile.get(chr);
                                                    ignore_space();
                                                    if (chr == '{')
                                                    {
                                                        do
                                                        {
                                                            NewFile.get(chr);
                                                            ignore_space();
                                                            if (chr == '}')
                                                            {
                                                                break;
                                                            }
                                                        } while (statement());
                                                        if (chr == '}')
                                                        {
                                                            NewFile.get(chr);
                                                            ignore_space();
                                                            if (NewFile.eof())
                                                            {
                                                                check_conditional_statement = true;
                                                                return check_conditional_statement;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else if (fun_tok.Token_value == VARIABLE)
        {
            checkFlag = true;
            NewFile.get(chr);
            ignore_space();
            if (chr == '=')
            {
                E();
                if (checkFlag)
                {
                    if (chr == ';')
                    {
                        NewFile.get(chr);
                        return true;
                    }
                    return false;
                }
                else
                {
                    return false;
                }
            }
        }
        else if (fun_tok.Token_value == WHILE)
        {
            NewFile.get(chr);
            ignore_space();
            if (chr == '(')
            {
                NewFile.get(chr);
                ignore_space();
                NewFile.putback(chr);
                global_token = Asfand_lexcial_analysis();
                if (global_token.Token_value == VARIABLE)
                {
                    NewFile.get(chr);
                    ignore_space();
                    if (chr == '=')
                    {
                        NewFile.get(chr);
                        ignore_space();
                        if (chr == '=')
                        {
                            NewFile.get(chr);
                            ignore_space();
                            if (isdigit(chr))
                            {
                                NewFile.get(chr);
                                ignore_space();
                                if (chr == ')')
                                {
                                    NewFile.get(chr);
                                    ignore_space();
                                    if (chr == '{')
                                    {
                                        NewFile.get(chr);
                                        if (!statement())
                                        {
                                            return false;
                                        }
                                        ignore_space();
                                        bool check =
                                            check_assignment();
                                        NewFile.get(chr);
                                        ignore_space();
                                        if (check)
                                        {
                                            NewFile.get(chr);
                                            ignore_space();
                                            if (chr ==
                                                '}')
                                            {
                                                NewFile.get(chr);
                                                ignore_space();
                                                if (NewFile.eof())
                                                {
                                                    check_conditional_statement = true;
                                                    return check_conditional_statement;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else if (fun_tok.Token_value == DO)
        {
            NewFile.get(chr);
            ignore_space();
            if (chr == '{')
            {
                NewFile.get(chr);
                ignore_space();
                bool check = check_assignment();
                NewFile.get(chr);
                ignore_space();
                if (check)
                {
                    NewFile.get(chr);
                    ignore_space();
                    if (chr == '}')
                    {
                        fun_tok = Asfand_lexcial_analysis();
                        if (fun_tok.Token_value == WHILE)
                        {
                            NewFile.get(chr);
                            ignore_space();
                            if (chr == '(')
                            {
                                NewFile.get(chr);
                                ignore_space();
                                NewFile.putback(chr);
                                global_token =
                                    Asfand_lexcial_analysis();
                                if (global_token.Token_value ==
                                    VARIABLE)
                                {
                                    NewFile.get(chr);
                                    ignore_space();
                                    if (chr == '=')
                                    {
                                        NewFile.get(chr);
                                        ignore_space();
                                        if (chr == '=')
                                        {
                                            NewFile.get(chr);
                                            ignore_space();
                                            if (isdigit(chr))
                                            {
                                                NewFile.get(chr);
                                                ignore_space();
                                                if (chr == ')')
                                                {
                                                    NewFile.get(chr);
                                                    ignore_space();
                                                    if (chr == ';')
                                                    {
                                                        check_conditional_statement = true;
                                                        return check_conditional_statement;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    check_conditional_statement = false;
    return check_conditional_statement;
}
int main()
{
    Token main_tok;
    NewFile.open("File.txt", ios::in);
    if (NewFile.is_open())
    {
        cout << " ~~> .: ( Recursive Descent Parser ) :. <~~" << endl;
        cout << "File Input: ";
        NewFile.get(chr);
        do
        {
            cout << chr;
            NewFile.get(chr);
        } while (!NewFile.eof());
        cout << endl
             << endl;
        NewFile.close();
        NewFile.open("File.txt", ios::in);
        NewFile.get(chr);
        bool statement_return = statement();
        // E();
        cout << endl
             << endl;
        if (statement_return)
        {
            cout << " ~~> .: ( String ACCEPTED ) :. <~~" << endl;
        }
        else
        {
            cout << " ~~> .: ( String REJECTED ) :. <~~" << endl;
        }
        NewFile.close();
        cout << "\n\n";
        /*NewFile.open("File.txt", ios::in);
        cout << "<<<<<<<<<<<Lexical analyzer>>>>>>>>>>>" << endl;
        if (NewFile.is_open())
        {
        do
        {
        main_tok = Asfand_lexcial_analysis();
        cout << main_tok.Token_name << endl;
        NewFile.get(chr);
        if (!NewFile.eof()) {
        NewFile.putback(chr);
        }
        } while (!NewFile.eof());
        }
        cout << "\n\n";
        display_table();*/
    }
    else
    {
        cout << "File not found..." << endl;
    }
    NewFile.close();
    return 0;
};
Token Asfand_lexcial_analysis()
{
    Token tok;
    bool present_in_table = true;
    do
    {
        NewFile.get(chr);
        if (isdigit(chr))
        {
            do
            {
                NewFile.get(chr);
            } while (isdigit(chr) && !NewFile.eof());
            NewFile.putback(chr);
            tok.Give_values(DIGIT, "Asfand_<DIGIT>", DIGIT);
            return tok;
        }
        else if (chr == ' ')
        {
            continue;
        }
        else if (chr == '*')
        {
            tok.Give_values(MULTIPLY, "Asfand_<multiply>", MULTIPLY);
            return tok;
        }
        else if (chr == ',')
        {
            tok.Give_values(COMMA, "Asfand_<comma>", COMMA);
            return tok;
        }
        else if (chr == '{')
        {
            tok.Give_values(OPR, "Asfand_<OPR>", OPR);
            return tok;
        }
        else if (chr == '}')
        {
            tok.Give_values(CPR, "Asfand_<CPR>", CPR);
            return tok;
        }
        else if (chr == '(')
        {
            tok.Give_values(OBR, "Asfand_<OBR>", OBR);
            return tok;
        }
        else if (chr == ')')
        {
            tok.Give_values(CBR, "Asfand<CBR>", CBR);
            return tok;
        }
        else if (chr == ';')
        {
            tok.Give_values(SEMICLN, "Asfand_<semicolon>", SEMICLN);
            return tok;
        }
        else if (chr == ':')
        {
            tok.Give_values(COLON, "Asfand_<colon>", COLON);
            return tok;
        }
        else if (chr == '[')
        {
            tok.Give_values(OSQBR, "Asfand_<osqbr>", OSQBR);
            return tok;
        }
        else if (chr == ']')
        {
            tok.Give_values(CSQBR, "Asfand_<csqbr>", CSQBR);
            return tok;
        }
        else if (chr == '"')
        {
            do
            {
                NewFile.get(chr);
            } while (chr != '"');
            tok.Give_values(OUTPUT_STR, "Asfand_<output string>", OUTPUT_STR);
            return tok;
        }
        else if (chr == '+')
        {
            chr = NewFile.get();
            if (chr == '+')
            {
                tok.Give_values(INCREMENT, "Asfand_<increment>", INCREMENT);
                return tok;
            }
            else if (chr == '=')
            {
                tok.Give_values(PLUS_EQUAL, "Asfand_<plus equal>",
                                PLUS_EQUAL);
                return tok;
            }
            else
            {
                NewFile.putback(chr);
                tok.Give_values(PLUS, "Asfand_<plus>", PLUS);
                return tok;
            }
        }
        else if (chr == '-')
        {
            chr = NewFile.get();
            if (chr == '-')
            {
                tok.Give_values(DECREMENT, "Asfand_<decrement>", DECREMENT);
                return tok;
            }
            else if (chr == '=')
            {
                tok.Give_values(MINUSEQUAL, "Asfand_<minus equal>",
                                MINUSEQUAL);
                return tok;
            }
            else
            {
                NewFile.putback(chr);
                tok.Give_values(MINUS, "Asfand_<minus>", MINUS);
                return tok;
            }
        }
        else if (chr == '<')
        {
            chr = NewFile.get();
            if (chr == '<')
            {
                tok.Give_values(OPSTREAM, "Asfand_<output stream>", OPSTREAM);
                return tok;
            }
            else if (chr == '=')
            {
                tok.Give_values(LESS_EQUAL, "Asfand_<less equal>",
                                LESS_EQUAL);
                return tok;
            }
            else
            {
                tok.Give_values(INSTREAM, "Asfand_<input stream>", INSTREAM);
                return tok;
            }
        }
        else if (chr == '>')
        {
            chr = NewFile.get();
            if (chr == '>')
            {
                tok.Give_values(INSTREAM, "Asfand_<input stream>", INSTREAM);
                return tok;
            }
            else if (chr == '=')
            {
                tok.Give_values(GREATER_EQUAL, "Asfand_<greater equal>",
                                GREATER_EQUAL);
                return tok;
            }
            else
            {
                tok.Give_values(GREATER_THAN, "Asfand_<greater than>",
                                GREATER_THAN);
                return tok;
            }
        }
        else if (chr == '=')
        {
            chr = NewFile.get();
            if (chr == '=')
            {
                tok.Give_values(EQUALITY, "Asfand_<equality>", EQUALITY);
                return tok;
            }
            else
            {
                NewFile.putback(chr);
                tok.Give_values(EQUAL, "Asfand_<equal>", EQUAL);
                return tok;
            }
        }
        else if (chr == '/')
        {
            NewFile.get(chr);
            if (chr == '/')
            {
                string s;
                do
                {
                    NewFile.get(chr);
                    if (chr != '\n')
                    {
                        s += chr;
                    }
                } while (chr != '\n');
                if (chr == '\n')
                {
                    NewFile.putback(chr);
                }
                tok.Give_values(COMMENT, "Asfand_<comment>_" + s, COMMENT);
                return tok;
            }
            else
            {
                NewFile.putback(chr);
                tok.Give_values(DIVIDE, "Asfand_<divide>", DIVIDE);
                return tok;
            }
        }
        else if (isalpha(chr))
        {
            string keyword;
            do
            {
                keyword += chr;
                NewFile.get(chr);
            } while (isalnum(chr));
            NewFile.putback(chr);
            if (keyword == "if")
            {
                tok.Give_values(IF, "Asfand_<keyword>_if", IF);
                return tok;
            }
            else if (keyword == "else")
            {
                tok.Give_values(ELSE, "Asfand_<keyword>_else", ELSE);
                return tok;
            }
            else if (keyword == "while")
            {
                tok.Give_values(WHILE, "Asfand_<keyword>_while", WHILE);
                return tok;
            }
            else if (keyword == "do")
            {
                tok.Give_values(DO, "Asfand_<keyword>_do", DO);
                return tok;
            }
            else if (keyword == "for")
            {
                tok.Give_values(FOR, "Asfand_<keyword>_for", FOR);
                return tok;
            }
            else if (keyword == "exit")
            {
                tok.Give_values(EXIT, "Asfand_<keyword>_break", EXIT);
                return tok;
            }
            else if (keyword == "break")
            {
                tok.Give_values(BREAK, "Asfand_<keyword>_exit", BREAK);
                return tok;
            }
            else if (keyword == "int")
            {
                tok.Give_values(INT, "Asfand_<keyword>_INT", INT);
                return tok;
            }
            else if (keyword == "string")
            {
                tok.Give_values(STRING, "Asfand_<keyword>_string", STRING);
                return tok;
            }
            else if (keyword == "float")
            {
                tok.Give_values(FLOAT, "Asfand_<keyword>_float", FLOAT);
                return tok;
            }
            else if (keyword == "cout")
            {
                tok.Give_values(COUT, "Asfand_<keyword>_cout", COUT);
                return tok;
            }
            else if (keyword == "main")
            {
                tok.Give_values(MAIN, "Asfand_<keyword>_main", MAIN);
                return tok;
            }
            else if (keyword == "return")
            {
                tok.Give_values(RETURN, "Asfand_<keyword>_return", RETURN);
                return tok;
            }
            else
            {
                Token catch_token;
                tok.Give_values(VARIABLE, "Asfand_<variable>_" + keyword,
                                VARIABLE);
                catch_token = Asfand_search(keyword, present_in_table);
                if (present_in_table == false)
                {
                    tok.symbol_table_value =
                        catch_token.symbol_table_value;
                    Asfand_make_entry(keyword);
                }
                return tok;
            }
        }
    } while (!NewFile.eof());
}
Token Asfand_search(string S_token, bool &present)
{
    Token return_token;
    for (int i = 0; i < table_size; i++)
    {
        if (S_token == Symbol_table[i].Token_name)
        {
            cout << "identifier already present in symbol table ----> " << S_token << endl;
            return_token = Symbol_table[i];
            return return_token;
        }
    }
    present = false;
    return return_token;
}
Token Asfand_make_entry(string S_token)
{
    Token return_token;
    for (int i = 0; i < table_size; i++)
    {
        if (Symbol_table[i].Token_name == "")
        {
            Symbol_table[i].symbol_table_value = i;
            cout << "Identifier added to symbol table ----> " << S_token << endl;
            Symbol_table[i].Token_name = S_token;
            return return_token = Symbol_table[i];
        }
    }
    cout << "symbol table is full" << endl;
}
void display_table()
{
    cout << "\n\n\t<<<<<<<<>>>>>>>>>" << endl;
    cout << "\t ~Symbol table~" << endl;
    cout << "\t<<<<<<<<>>>>>>>>>" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Identifier name \t Token value" << endl;
    for (int i = 0; i < table_size; i++)
    {
        if (Symbol_table[i].Token_name != "")
        {
            cout << "\t" << Symbol_table[i].Token_name << setw(20 - Symbol_table[i].Token_name.length()) << Symbol_table[i].symbol_table_value << endl;
        }
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}