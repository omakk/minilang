#ifndef AST_H
#define AST_H

enum ast_construct { 
        CON_IDENT,     CON_FLOATLIT,  CON_INTLIT,  CON_STRLIT,
        CON_BOP_PLUS,  CON_BOP_MINUS, CON_BOP_MUL, CON_BOP_DIV,
        CON_UOP_MINUS, CON_IF,        CON_IF_ELSE, CON_WHILE,
        CON_READ,      CON_PRINT,     CON_DECL,    CON_ASSIGN,
        CON_PROGRAM,   CON_STMTS
};

enum type {
        TINT, TFLOAT, TSTRING
};

const char *get_type(enum type type);
enum type make_type(const char *type);

typedef struct ASTNode {
        int lineno;
        enum ast_construct construct;
        union {
               char     *idval;
               int      intval;
               float  floatval;
               char    *strval;

               struct ASTNode *printexp;
               struct ASTNode *minusuop;
               struct ASTNode *readidval;

               struct { struct ASTNode *id;   struct ASTNode *e;          } assign;
               struct { struct ASTNode *stmt; struct ASTNode *stmts;      } stmts;
               struct { struct ASTNode *dcls; struct ASTNode *stmts;      } prog;
               struct { struct ASTNode *left; struct ASTNode *right;      } mulbop;
               struct { struct ASTNode *left; struct ASTNode *right;      } divbop;
               struct { struct ASTNode *left; struct ASTNode *right;      } plusbop;
               struct { struct ASTNode *left; struct ASTNode *right;      } minusbop;
               struct { struct ASTNode *cond; struct ASTNode *while_body; } whilebranch;
               struct { struct ASTNode *cond; struct ASTNode *if_body;    } ifbranch;
               struct { struct ASTNode *id;   enum type       type;    struct ASTNode *next;      } decl;
               struct { struct ASTNode *cond; struct ASTNode *if_body; struct ASTNode *else_body; } ifelsebranch;
        } val;
} ASTNode;

ASTNode *make_ast_node_ident        ( char    *id,                                          int lineno);
ASTNode *make_ast_node_read         ( char    *id,                                          int lineno);
ASTNode *make_ast_node_strlit       ( char    *s,                                           int lineno);
ASTNode *make_ast_node_intlit       ( int      i,                                           int lineno);
ASTNode *make_ast_node_floatlit     ( float    f,                                           int lineno);
ASTNode *make_ast_node_print        ( ASTNode *e,                                           int lineno);
ASTNode *make_ast_node_minusuop     ( ASTNode *e,                                           int lineno);
ASTNode *make_ast_node_decl         ( char    *id,   enum type type,                        int lineno);
ASTNode *make_ast_node_assign       ( char    *id,   ASTNode *e,                            int lineno);
ASTNode *make_ast_node_prog         ( ASTNode *dcls, ASTNode *stmts,                        int lineno);
ASTNode *make_ast_node_stmts        ( ASTNode *stmt, ASTNode *stmts,                        int lineno);
ASTNode *make_ast_node_mulbop       ( ASTNode *l,    ASTNode *r,                            int lineno);
ASTNode *make_ast_node_divbop       ( ASTNode *l,    ASTNode *r,                            int lineno);
ASTNode *make_ast_node_plusbop      ( ASTNode *l,    ASTNode *r,                            int lineno);
ASTNode *make_ast_node_minusbop     ( ASTNode *l,    ASTNode *r,                            int lineno);
ASTNode *make_ast_node_whilebranch  ( ASTNode *cond, ASTNode *while_body,                   int lineno);
ASTNode *make_ast_node_ifbranch     ( ASTNode *cond, ASTNode *if_body,                      int lineno);
ASTNode *make_ast_node_ifelsebranch ( ASTNode *cond, ASTNode *if_body, ASTNode *else_body,  int lineno);

ASTNode *prepend_dcl(ASTNode *dcl, ASTNode *dcls);

#endif
