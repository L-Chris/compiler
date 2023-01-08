#include "util.h"

typedef char *string;
typedef struct A_stm_ *A_stm; // 指向语句结构的指针
typedef struct A_exp_ *A_exp; // 指向表达式结构的指针
typedef struct A_expList_ *A_expList; // 指向表达式列表结构的指针
typedef enum {A_plus,A_minus,A_times,A_div} A_binop; // 二元操作符枚举

// 语句结构
struct A_stm_ {
  enum {A_compoundStm, A_assignStm, A_printStm} kind; // 语句类型：符合语句、赋值语句、输出语句
  union {
    struct {A_stm stm1, stm2;} compound;
    struct {string id; A_exp exp;} assign;
    struct {A_expList exps;} print;
  } u;
};

// 表达式结构
struct A_exp_ {
  enum {A_idExp, A_numExp, A_opExp, A_eseqExp} kind; // 表达式类型：标识符表达式、数字表达式、操作符表达式、表达式序列
  union {
    string id;
    int num;
    struct {A_exp left; A_binop oper; A_exp right;} op;
    struct {A_stm stm; A_exp exp} esep;
  } u;
};

// 表达式列表结构
struct A_expList_ {
  enum {A_pairExpList, A_lastExpList} kind; //
  union {
    struct {A_exp head; A_expList tail;} pair;
    A_exp last;
  } u;
};

A_stm A_CompoundStm(A_stm stm1, A_stm stm2);
A_stm A_AssignStm(string id, A_exp exp);
A_stm A_PrintStm(A_expList exps);

// 复合语句结构的构造函数
A_stm A_CompoundStm(A_stm stm1, A_stm stm2) {
  A_stm s = checked_malloc(sizeof(*s));
  s->kind = A_compoundStm;
  s->u.compound.stm1 = stm1;
  s->u.compound.stm2 = stm2;
  return s;
}

// 赋值语句结构的构造函数
A_stm A_AssignStm(string id, A_exp exp) {
  A_stm s = checked_malloc(sizeof(*s));
  s->kind = A_assignStm;
  s->u.assign.id = id;
  s->u.assign.exp = exp;
  return s;
}

// 输出语句结构的构造函数
A_stm A_PrintStm(A_expList exps) {
  A_stm s = checked_malloc(sizeof(*s));
  s->kind = A_printStm;
  s->u.print.exps = exps;
  return s;
}

A_exp A_IdExp(string id);
A_exp A_NumExp(int num);
A_exp A_OpExp(A_exp left, A_binop oper, A_exp right);
A_exp A_EseqExp(A_stm stm, A_exp exp);

// 标识符表达式的构造函数
A_exp A_IdExp(string id) {
  A_exp s = checked_malloc(sizeof(*s));
  s->kind = A_idExp;
  s->u.id = id;
  return s;
}

// 数字表达式的构造函数
A_exp A_NumExp(int num) {
  A_exp s = checked_malloc(sizeof(*s));
  s->kind = A_numExp;
  s->u.num = num;
  return s;
}

// 操作符表达式的构造函数
A_exp A_OpExp(A_exp left, A_binop oper, A_exp right) {
  A_exp s = checked_malloc(sizeof(*s));
  s->kind = A_opExp;
  s->u.op.left = left;
  s->u.op.oper = oper;
  s->u.op.right = right;
  return s;
}

// 表达式序列的构造函数
A_exp A_EseqExp(A_stm stm, A_exp exp) {
  A_exp s = checked_malloc(sizeof(*s));
  s->kind = A_eseqExp;
  s->u.esep.stm = stm;
  s->u.esep.exp = exp;
  return s;
}
