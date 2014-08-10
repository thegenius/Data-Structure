/***************************************************
*  作者：汪蔚                                      *
*  更新：2014-07-13                                *
****************************************************/
#include <stdarg.h>
#include <stdio.h>

typedef int BevNodeInput;

class BevNode {
public:
	BevNode() 
		: first(nullptr), second(nullptr) {
	}
	BevNode(BevNode* op1) 
		: first(op1), second(nullptr) {
	}
	BevNode(BevNode* op1, BevNode* op2) 
		: first(op1), second(op2) {
	}
	~BevNode(){
		delete first;
		delete second;
	}

	//默认return true可以让action节点有了默认的行为
	virtual bool evaluate(BevNodeInput &input) {
		if (first != nullptr) {
			return first->evaluate(input);
		} else {
			return true;
		}
	};
	virtual int  doAction(BevNodeInput &input) {
		if (first->evaluate(input)) {
			if (second != nullptr) {
				return second->doAction(input);
			}
		} 
		return 1;
	};
public:
	BevNode* first;
	BevNode* second;
};

typedef BevNode BevCondition;
typedef BevNode BevAction;


/*******************************************
*    begin of     逻辑判断相关类           *  
********************************************/

class BevNodeConditionTRUE : public BevNode {
public:
	virtual bool evaluate(BevNodeInput& input) {
		return true;
	}
};

class BevNodeConditionFALSE : public BevNode {
public:
	virtual bool evaluate(BevNodeInput& input) {
		return false;
	}
};

class BevNodeConditionONE : public BevNode {
public:
	BevNodeConditionONE(BevNode* one) : BevNode(one){
	}
	virtual bool evaluate(BevNodeInput& input) {
		return first->evaluate(input);
	}
};

class BevNodeConditionNOT : public BevNode{
public:
	BevNodeConditionNOT(BevNode* one) : BevNode(one) {
	}
	virtual bool evaluate(BevNodeInput& input) {
		return !first->evaluate(input);
	}
};

class BevNodeConditionAND : public BevNode{
public:
	BevNodeConditionAND(BevNode* op1, BevNode* op2) 
		: BevNode(op1, op2) {
	}
	BevNodeConditionAND(BevNode* op1, BevNode* op2, BevNode* op3) 
		: BevNode(op1, new BevNodeConditionAND(op2, op3)) {
	}
	BevNodeConditionAND(BevNode* op1, BevNode* op2, BevNode* op3, BevNode* op4) 
		: BevNode(op1, new BevNodeConditionAND(op2, new BevNodeConditionAND(op3, op4))) {
	}
	BevNodeConditionAND(BevNode* op1, BevNode* op2, BevNode* op3, BevNode* op4, BevNode* op5) 
		: BevNode(op1, new BevNodeConditionAND(op2, new BevNodeConditionAND(op3, new BevNodeConditionAND(op4, op5)))) {
	}
	BevNodeConditionAND(BevNode* op1, BevNode* op2, BevNode* op3, BevNode* op4, BevNode* op5, BevNode* op6) 
		: BevNode(op1, new BevNodeConditionAND(op2, new BevNodeConditionAND(op3, new BevNodeConditionAND(op4, new BevNodeConditionAND(op5, op6))))) {
	}

	virtual bool evaluate(BevNodeInput& input) {
		return first->evaluate(input) && second->evaluate(input);
	}
};

class BevNodeConditionOR : public BevNode {
public:
	BevNodeConditionOR(BevNode* op1, BevNode* op2) 
		: BevNode(op1, op2) {
	}
	BevNodeConditionOR(BevNode* op1, BevNode* op2, BevNode* op3) 
		: BevNode(op1, new BevNodeConditionOR(op2, op3)) {
	}
	BevNodeConditionOR(BevNode* op1, BevNode* op2, BevNode* op3, BevNode* op4) 
		: BevNode(op1, new BevNodeConditionOR(op2, new BevNodeConditionOR(op3, op4))) {
	}
	BevNodeConditionOR(BevNode* op1, BevNode* op2, BevNode* op3, BevNode* op4, BevNode* op5) 
		: BevNode(op1, new BevNodeConditionOR(op2, new BevNodeConditionOR(op3, new BevNodeConditionOR(op4, op5)))) {
	}
	BevNodeConditionOR(BevNode* op1, BevNode* op2, BevNode* op3, BevNode* op4, BevNode* op5, BevNode* op6) 
		: BevNode(op1, new BevNodeConditionOR(op2, new BevNodeConditionOR(op3, new BevNodeConditionOR(op4, new BevNodeConditionOR(op5, op6))))) {
	}
	virtual bool evaluate(BevNodeInput& input) {
		return first->evaluate(input) || second->evaluate(input);
	}
};

class BevNodeConditionXOR : public BevNode {
public:
	BevNodeConditionXOR(BevNode* op1, BevNode* op2) 
		: BevNode(op1, op2) {
	}
	BevNodeConditionXOR(BevNode* op1, BevNode* op2, BevNode* op3) 
		: BevNode(op1, new BevNodeConditionXOR(op2, op3)) {
	}
	BevNodeConditionXOR(BevNode* op1, BevNode* op2, BevNode* op3, BevNode* op4) 
		: BevNode(op1, new BevNodeConditionXOR(op2, new BevNodeConditionXOR(op3, op4))) {
	}
	BevNodeConditionXOR(BevNode* op1, BevNode* op2, BevNode* op3, BevNode* op4, BevNode* op5) 
		: BevNode(op1, new BevNodeConditionXOR(op2, new BevNodeConditionXOR(op3, new BevNodeConditionXOR(op4, op5)))) {
	}
	BevNodeConditionXOR(BevNode* op1, BevNode* op2, BevNode* op3, BevNode* op4, BevNode* op5, BevNode* op6) 
		: BevNode(op1, new BevNodeConditionXOR(op2, new BevNodeConditionXOR(op3, new BevNodeConditionXOR(op4, new BevNodeConditionXOR(op5, op6))))) {
	}
	virtual bool evaluate(BevNodeInput& input) {
		return first->evaluate(input) ^ second->evaluate(input);
	}
};
/*****************************************
*    end of     逻辑判断相关类           *  
******************************************/



/*****************************************
*    begin of     控制选择节点           *  
******************************************/

typedef BevNode BevNodeSelectorONE;


class BevNodeSelectorAND : public BevNode {
public:	
	BevNodeSelectorAND(BevNode* op1, BevNode* op2) 
		: BevNode(op1, op2) {
	}
	BevNodeSelectorAND(BevNode* op1, BevNode* op2, BevNode* op3) 
		: BevNode(op1, new BevNodeSelectorAND(op2, op3)) {
	}
	BevNodeSelectorAND(BevNode* op1, BevNode* op2, BevNode* op3, BevNode* op4) 
		: BevNode(op1, new BevNodeSelectorAND(op2, new BevNodeSelectorAND(op3, op4))) {
	}
	BevNodeSelectorAND(BevNode* op1, BevNode* op2, BevNode* op3, BevNode* op4, BevNode* op5) 
		: BevNode(op1, new BevNodeSelectorAND(op2, new BevNodeSelectorAND(op3, new BevNodeSelectorAND(op4, op5)))) {
	}
	BevNodeSelectorAND(BevNode* op1, BevNode* op2, BevNode* op3, BevNode* op4, BevNode* op5, BevNode* op6) 
		: BevNode(op1, new BevNodeSelectorAND(op2, new BevNodeSelectorAND(op3, new BevNodeSelectorAND(op4, new BevNodeSelectorAND(op5, op6))))) {
	}
	int doAction(BevNodeInput &input) {
		int status = 0;
		if (first != nullptr) {
			status += first->doAction(input);
		}
		if (second != nullptr) {
			status += second->doAction(input);
		}
		return status;
	}
};

class BevNodeSelectorOR : public BevNode {
public:
	BevNodeSelectorOR(BevNode* op1, BevNode* op2) 
		: BevNode(op1, op2) {
	}
	BevNodeSelectorOR(BevNode* op1, BevNode* op2, BevNode* op3) 
		: BevNode(op1, new BevNodeSelectorOR(op2, op3)) {
	}
	BevNodeSelectorOR(BevNode* op1, BevNode* op2, BevNode* op3, BevNode* op4) 
		: BevNode(op1, new BevNodeSelectorOR(op2, new BevNodeSelectorOR(op3, op4))) {
	}
	BevNodeSelectorOR(BevNode* op1, BevNode* op2, BevNode* op3, BevNode* op4, BevNode* op5) 
		: BevNode(op1, new BevNodeSelectorOR(op2, new BevNodeSelectorOR(op3, new BevNodeSelectorOR(op4, op5)))) {
	}
	BevNodeSelectorOR(BevNode* op1, BevNode* op2, BevNode* op3, BevNode* op4, BevNode* op5, BevNode* op6) 
		: BevNode(op1, new BevNodeSelectorOR(op2, new BevNodeSelectorOR(op3, new BevNodeSelectorOR(op4, new BevNodeSelectorOR(op5, op6))))) {
	}
	int doAction(BevNodeInput &input) {
		int status = 0;
		if (first != nullptr) {
			status = first->doAction(input);
			if (status != 0) {
				status = second->doAction(input);
			}
		}
		return status;
	}
};
/*****************************************
*      end of     控制选择节点           *  
******************************************/


/********************************************************
*      定义条件condition(CDT)和定义action(ACT)的宏      *
*********************************************************/
#define CDT_DEF(_name, _body)         \
class _name : public BevCondition {        \
public:                                    \
	bool evaluate(BevNodeInput &input) {   \
		_body;                             \
	}                                      \
};

#define ACT_DEF(_name, _body)           \
class _name : public BevAction {        \
public:                                 \
	int doAction(BevNodeInput &input) { \
		_body;                          \
	}                                   \
};



/*******************************************
*                具体动作定义              *
********************************************/
CDT_DEF(isEven,              { return !(input&1);}                      );
CDT_DEF(inRange,             { return (input>=0) && (input<=100);}      );
CDT_DEF(isUnqualify,         { return (input<60);                }      );
CDT_DEF(isNormal,            { return (input>=60) && (input<=80);}      );
CDT_DEF(isExcellent,         { return input>80;                  }      );

ACT_DEF(doIsEven,      { printf("I am %d, I am even.\n",input);        return 0; }  );
ACT_DEF(doInRange,     { printf("I am in range.\n");    return 0; }  );
ACT_DEF(doIsUnqualify, { printf("I am unqualified.\n"); return 0; }  );
ACT_DEF(doIsNormal,    { printf("I am normal.\n");      return 0; }  );
ACT_DEF(doIsExcellent, { printf("I am excellent.\n");   return 0; }  );


ACT_DEF(BevNodeAction1, { printf("I am action 1\n"); return 0; }  );
ACT_DEF(BevNodeAction2, { printf("I am action 2\n"); return 0; }  );
ACT_DEF(BevNodeAction3, { printf("I am action 3\n"); return 0; }  );
ACT_DEF(BevNodeAction4, { printf("I am action 4\n"); return 0; }  );
ACT_DEF(BevNodeAction5, { printf("I am action 5\n"); return 0; }  );
ACT_DEF(BevNodeAction6, { printf("I am action 6\n"); return 0; }  );


/*********************************************
*             测试代码                       *
**********************************************/
//int _tmain(int argc, char* argv[]) {
//	//*/
//	BevNode behaviorTree(
//		new BevNodeConditionTRUE,
//
//		new BevNodeSelectorAND(
//			new BevNode(
//				new isUnqualify,
//				new doIsUnqualify),
//
//			new BevNode(
//				new inRange, 
//				new doInRange),
//
//			new BevNode(
//				new isEven, 
//				new doIsEven),
//
//			new BevNode(
//				new isNormal, 
//				new doIsNormal),
//
//			new BevNode(
//				new isExcellent, 
//				new doIsExcellent)));
//	//*/
//
//	int input = 82;
//	behaviorTree.doAction(input);
//	getchar();
//
//	return 0;
//}

