#ifndef AST_H
#define AST_H

enum ast_construct { 
                     CON_IDENT,     CON_FLOATLIT,  CON_INTLIT,  CON_STRLIT,
                     CON_BOP_PLUS,  CON_BOP_MINUS, CON_BOP_MUL, CON_BOP_DIV,
                     CON_UOP_MINUS, CON_IF,        CON_IF_ELSE, CON_WHILE,
                     CON_READ,      CON_PRINT,     CON_DECL,    CON_ASSIGN,
                     CON_PROGRAM,   CON_DCLS,      CON_STMTS
                   };

typedef struct ASTNode {
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
               struct { struct ASTNode *id;   char           *type;       } decl;
               struct { struct ASTNode *dcl;  struct ASTNode *dcls;       } dcls;
               struct { struct ASTNode *stmt; struct ASTNode *stmts;      } stmts;
               struct { struct ASTNode *dcls; struct ASTNode *stmts;      } prog;
               struct { struct ASTNode *left; struct ASTNode *right;      } mulbop;
               struct { struct ASTNode *left; struct ASTNode *right;      } divbop; 
               struct { struct ASTNode *left; struct ASTNode *right;      } plusbop; 
               struct { struct ASTNode *left; struct ASTNode *right;      } minusbop; 
               struct { struct ASTNode *cond; struct ASTNode *while_body; } whilebranch;
               struct { struct ASTNode *cond; struct ASTNode *if_body;    } ifbranch;

               struct { struct ASTNode *cond; struct ASTNode *if_body; struct ASTNode *else_body; } ifelsebranch;
        } val;
} ASTNode;

ASTNode *make_ast_node_ident        ( char    *id                                         );
ASTNode *make_ast_node_read         ( char    *id                                         );
ASTNode *make_ast_node_strlit       ( char    *s                                          );
ASTNode *make_ast_node_intlit       ( int      i                                          );
ASTNode *make_ast_node_floatlit     ( float    f                                          );
ASTNode *make_ast_node_print        ( ASTNode *e                                          );
ASTNode *make_ast_node_minusuop     ( ASTNode *e                                          );
ASTNode *make_ast_node_decl         ( char    *id,   char    *type                        );
ASTNode *make_ast_node_assign       ( char    *id,   ASTNode *e                           );
ASTNode *make_ast_node_prog         ( ASTNode *dcls, ASTNode *stmts                       );
ASTNode *make_ast_node_dcls         ( ASTNode *dcl,  ASTNode *dcls                        );
ASTNode *make_ast_node_stmts        ( ASTNode *stmt, ASTNode *stmts                       );
ASTNode *make_ast_node_mulbop       ( ASTNode *l,    ASTNode *r                           );
ASTNode *make_ast_node_divbop       ( ASTNode *l,    ASTNode *r                           );
ASTNode *make_ast_node_plusbop      ( ASTNode *l,    ASTNode *r                           );
ASTNode *make_ast_node_minusbop     ( ASTNode *l,    ASTNode *r                           );
ASTNode *make_ast_node_whilebranch  ( ASTNode *cond, ASTNode *while_body                  );
ASTNode *make_ast_node_ifbranch     ( ASTNode *cond, ASTNode *if_body                     );
ASTNode *make_ast_node_ifelsebranch ( ASTNode *cond, ASTNode *if_body, ASTNode *else_body );

#endif
