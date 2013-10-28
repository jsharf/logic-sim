#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct gate;
struct reg;
struct add;

typedef struct gate* gate_t;
typedef struct reg* reg_t;
typedef struct add* add_t;
typedef int bool;

bool set(reg_t a, int val);
int val(reg_t a);
bool evaluate(gate_t a);
gate_t constant_gate(bool val);
add_t create_adder(bool ina, bool inb, bool carryin);
void clean_gates(gate_t a);
void clean_adder(add_t a);

enum gate_type
{
	AND, //and two operands
	NAND,
	OR,
	NOR,
	CONST,
	XOR
};

struct gate
{
	int type; //type of gate
	//for gates with operands
	union
	{
		gate_t operand[2];
		bool val;
	} u;
};

struct reg
{
	char upper;
	char lower;
};

struct add
{
	gate_t root;//gate to evaluate for output
	gate_t carryout; //gate to eval for carry out
	gate_t ina;
	gate_t inb;
	gate_t carryin;
};
//stores lower 16 bits of val into reg
//returns false if overflow
bool set(reg_t a, int val)
{
	int val2= val & 0xFFFF;
	a->upper = val2 >> 8;
	a->lower = val2&0xFF;
	return val2 == val;
}

int val(reg_t a)
{
	return a->upper<<8 | a->lower;
}

bool evaluate(gate_t a)
{
	if(a->type == CONST)
		return (a->u.val);
	bool ab = evaluate(a->u.operand[0]) && evaluate(a->u.operand[1]);
	if(a->type == AND)
		return ab;
	if(a->type == NAND)
		return !ab;
	int aorb = evaluate(a->u.operand[0]) || evaluate(a->u.operand[1]);
	if(a->type == OR)
		return aorb;
	if(a->type == NOR)
		return !aorb;
	bool axorb = evaluate(a->u.operand[0]) ^ evaluate(a->u.operand[1]);
	if(a->type == XOR)
		return axorb;
}

void clean_gates(gate_t a)
{
	if(a->type == CONST)
	{
		free(a);
		return;
	}
	else
	{
		clean_gates(a->u.operand[0]);
		clean_gates(a->u.operand[1]);
		free(a);
		return;
	}
}

void clean_adder(add_t a)
{
	clean_gates(a->root);
	free(a);
}

gate_t constant_gate(bool val)
{
	gate_t c = malloc(sizeof(struct gate));
	c->type = CONST;
	c->u.val = val;
	return c;
}

add_t create_adder(bool ina, bool inb, bool carryin)
{
	//create logic to calculate output
	gate_t a = malloc(sizeof(struct gate));
	a->type = XOR;
	gate_t b = malloc(sizeof(struct gate));
	b->type = XOR;
	a->u.operand[0] = b;
	gate_t c = malloc(sizeof(struct gate));
	c->type = CONST;
	c->u.val = carryin;
	a->u.operand[1] = c;
	
	gate_t op1 = malloc(sizeof(struct gate));
	op1->type = CONST;
	op1->u.val = ina;
	b->u.operand[0] = op1;

	gate_t op2 = malloc(sizeof(struct gate));
	op2->type = CONST;
	op2->u.val = inb;
	b->u.operand[1] = op2;

	//store output logic into adder struct
	add_t adder = malloc(sizeof(struct add));
	adder->root = a;
	adder->ina = op1;
	adder->inb = op2;
	adder->carryin = c;

	//create logic to calculate carry out
	gate_t one = malloc(sizeof(struct gate));
	one->type = AND;
	one->u.operand[0] = op1;
	one->u.operand[1] = op2;

	gate_t two = malloc(sizeof(struct gate));
	two->type = AND;
	two->u.operand[0] = op1;
	two->u.operand[1] = c;

	gate_t three = malloc(sizeof(struct gate));
	three->type = AND;
	three->u.operand[0] = op2;
	three->u.operand[1] = c;


	gate_t or1 = malloc(sizeof(struct gate));
	or1->type = OR;
	or1->u.operand[0] = one;
	or1->u.operand[1] = two;
	gate_t or2 = malloc(sizeof(struct gate));
	or2->type = OR;
	or2->u.operand[0] = or1;
	or2->u.operand[1] = three;
	adder->carryout = or2;
	
	return adder;
}

int main()
{
	add_t test = create_adder(1, 1, 0);
	assert(evaluate(test->root) == 0);
	assert(evaluate(test->carryout) == 1);
	clean_adder(test);
}
