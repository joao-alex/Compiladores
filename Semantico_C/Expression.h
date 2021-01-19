#ifndef Expression_H
#define Expression_H

typedef void * Expression;

Expression createExpression(int expType, Expression leftChild, Expression rightChild);

int getExpType(Expression e);

Expression getLeftChild(Expression e);

Expression getRightChild(Expression e);

#endif