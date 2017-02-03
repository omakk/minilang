#ifndef AST_H
#define AST_H

enum ast_construct { 
                     CON_IDENT,   CON_FLOATLIT, CON_INTLIT, CON_STRLIT,
                     CON_OP_PLUS, CON_OP_MINUS, CON_OP_MUL, CON_OP_DIV,
                     CON_IF,      CON_IF_ELSE,  CON_WHILE,  CON_READ, 
                     CON_PRINT,   CON_DECL,     CON_ASSIGN
                   };

typedef struct ASTNode {
        enum ast_construct construct;
        union {
               char    *idval;
               int     intval;
               float floatval;
               char   *strval;
               struct { struct ASTNode *exp } printexp;
               struct { char *idval; char *type } decl;
               struct { char *idval; ASTNode *e } assign;
               struct { struct ASTNode *left; struct ASTNode *right } mulop;
               struct { struct ASTNode *left; struct ASTNode *right } divop; 
               struct { struct ASTNode *left; struct ASTNode *right } plusop; 
               struct { struct ASTNode *left; struct ASTNode *right } minusop; 
               struct { struct ASTNode *cond; struct ASTNode *while_body } whilebranch;
               struct { struct ASTNode *cond; struct ASTNode *if_body } ifbranch;
               struct { struct ASTNode *cond; struct ASTNode *if_body; struct ASTNode *else_body } ifelsebranch;
              } val;
} ASTNode;

ASTNode *make_ast_node_ident        ( char    *id                                         );
ASTNode *make_ast_node_read         ( char    *id                                         );
ASTNode *make_ast_node_strlit       ( char    *s                                          );
ASTNode *make_ast_node_intlit       ( int      i                                          );
ASTNode *make_ast_node_floatlit     ( float    f                                          );
ASTNode *make_ast_node_print        ( ASTNode *e                                          );
ASTNode *make_ast_node_decl         ( char    *id,   char    *type                        );
ASTNode *make_ast_node_assign       ( char    *id,   ASTNode *e                           );
ASTNode *make_ast_node_mulop        ( ASTNode *l,    ASTNode *r                           );
ASTNode *make_ast_node_divlop       ( ASTNode *l,    ASTNode *r                           );
ASTNode *make_ast_node_plusop       ( ASTNode *l,    ASTNode *r                           );
ASTNode *make_ast_node_minusop      ( ASTNode *l,    ASTNode *r                           );
ASTNode *make_ast_node_whilebranch  ( ASTNode *cond, ASTNode *while_body                  );
ASTNode *make_ast_node_ifbranch     ( ASTNode *cond, ASTNode *if_body                     );
ASTNode *make_ast_node_ifelsebranch ( ASTNode *cond, ASTNode *if_body, ASTNode *else_body );

#endif
