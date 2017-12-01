#ifndef PRETTY_H
#define PRETTY_H

#include <stdio.h>
#include "ast.h"

int pretty_print(FILE *f, ASTNode *tree, int indent);

#endif
