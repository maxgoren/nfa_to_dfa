#include <vector>
#include <map>
#include <set>
#include <functional>
using namespace std; 
enum NTSYMBOL {
	 DOLLARACCEPT,
catexpr, ccent, cclist, optneg, regex, repexpr, 
sp, val
};
struct Production {
	 int id;
	 int lhs;
	 vector<int> rhs;
	 string actsym;
 }; 

static const Production prod[] = {
 	 {0, 0, {}, ""},

	 {1,sp, {regex},""}, 
	 {2,regex, {regex, OR, catexpr},"@mkOr"}, 
	 {3,regex, {catexpr},""}, 
	 {4,catexpr, {catexpr, repexpr},"@mkConcat"}, 
	 {5,catexpr, {repexpr},""}, 
	 {6,repexpr, {val, KLEENE_STAR},"@mkKleene"}, 
	 {7,repexpr, {val, KLEENE_PLUS},"@mkKleene"}, 
	 {8,repexpr, {val, QMARK},"@mkOpt"}, 
	 {9,repexpr, {val},""}, 
	 {10,val, {LPAREN, regex, RPAREN},"@pass"}, 
	 {11,val, {LETTER},"@mkLeaf"}, 
	 {12,val, {PERIOD},"@mkLeaf"}, 
	 {13,val, {LSQB, optneg, cclist, RSQB},"@mkCcl"}, 
	 {14,optneg, {NEGATE},""}, 
	 {15,optneg, {},""}, 
	 {16,cclist, {cclist, ccent},"@mkList"}, 
	 {17,cclist, {ccent},""}, 
	 {18,ccent, {LETTER, DASH, LETTER},"@mkCCLRange"}, 
	 {19,ccent, {LETTER},""}
};
static const int goTab_row_0[] = {4,catexpr, 7, regex, 8, repexpr, 6, val, 5};
static const int goTab_row_1[] = {1,optneg, 10};
static const int goTab_row_4[] = {4,catexpr, 7, regex, 11, repexpr, 6, val, 5};
static const int goTab_row_7[] = {2,repexpr, 15, val, 5};
static const int goTab_row_10[] = {2,ccent, 18, cclist, 19};
static const int goTab_row_16[] = {3,catexpr, 21, repexpr, 6, val, 5};
static const int goTab_row_19[] = {1,ccent, 23};

static const int *goTab[] = {
	 goTab_row_0, 	 goTab_row_1, 	 NULL, 	 NULL, 	 goTab_row_4, 
	 NULL, 	 NULL, 	 goTab_row_7, 	 NULL, 	 NULL, 
	 goTab_row_10, 	 NULL, 	 NULL, 	 NULL, 	 NULL, 
	 NULL, 	 goTab_row_16, 	 NULL, 	 NULL, 	 goTab_row_19, 
	 NULL, 	 goTab_row_7, 	 NULL
};

static const int actTab_row_0[] = {4,LETTER, 3, LPAREN, 4, LSQB, 1, PERIOD, 2};
static const int actTab_row_1[] = {2,LETTER, -15, NEGATE, 9};
static const int actTab_row_2[] = {10,KLEENE_PLUS, -12, KLEENE_STAR, -12, LETTER, -12, LPAREN, -12, LSQB, -12, OR, -12, PERIOD, -12, QMARK, -12, RPAREN, -12, TK_EOI, -12};
static const int actTab_row_3[] = {10,KLEENE_PLUS, -11, KLEENE_STAR, -11, LETTER, -11, LPAREN, -11, LSQB, -11, OR, -11, PERIOD, -11, QMARK, -11, RPAREN, -11, TK_EOI, -11};
static const int actTab_row_5[] = {10,KLEENE_PLUS, 13, KLEENE_STAR, 14, LETTER, -9, LPAREN, -9, LSQB, -9, OR, -9, PERIOD, -9, QMARK, 12, RPAREN, -9, TK_EOI, -9};
static const int actTab_row_6[] = {7,LETTER, -5, LPAREN, -5, LSQB, -5, OR, -5, PERIOD, -5, RPAREN, -5, TK_EOI, -5};
static const int actTab_row_7[] = {7,LETTER, 3, LPAREN, 4, LSQB, 1, OR, -3, PERIOD, 2, RPAREN, -3, TK_EOI, -3};
static const int actTab_row_8[] = {2,DOLLARACCEPT, 0, OR, 16};
static const int actTab_row_9[] = {1,LETTER, -14};
static const int actTab_row_10[] = {1,LETTER, 17};
static const int actTab_row_11[] = {2,OR, 16, RPAREN, 20};
static const int actTab_row_12[] = {7,LETTER, -8, LPAREN, -8, LSQB, -8, OR, -8, PERIOD, -8, RPAREN, -8, TK_EOI, -8};
static const int actTab_row_13[] = {7,LETTER, -7, LPAREN, -7, LSQB, -7, OR, -7, PERIOD, -7, RPAREN, -7, TK_EOI, -7};
static const int actTab_row_14[] = {7,LETTER, -6, LPAREN, -6, LSQB, -6, OR, -6, PERIOD, -6, RPAREN, -6, TK_EOI, -6};
static const int actTab_row_15[] = {7,LETTER, -4, LPAREN, -4, LSQB, -4, OR, -4, PERIOD, -4, RPAREN, -4, TK_EOI, -4};
static const int actTab_row_17[] = {3,DASH, 22, LETTER, -19, RSQB, -19};
static const int actTab_row_18[] = {2,LETTER, -17, RSQB, -17};
static const int actTab_row_19[] = {2,LETTER, 17, RSQB, 24};
static const int actTab_row_20[] = {10,KLEENE_PLUS, -10, KLEENE_STAR, -10, LETTER, -10, LPAREN, -10, LSQB, -10, OR, -10, PERIOD, -10, QMARK, -10, RPAREN, -10, TK_EOI, -10};
static const int actTab_row_21[] = {7,LETTER, 3, LPAREN, 4, LSQB, 1, OR, -2, PERIOD, 2, RPAREN, -2, TK_EOI, -2};
static const int actTab_row_22[] = {1,LETTER, 25};
static const int actTab_row_23[] = {2,LETTER, -16, RSQB, -16};
static const int actTab_row_24[] = {10,KLEENE_PLUS, -13, KLEENE_STAR, -13, LETTER, -13, LPAREN, -13, LSQB, -13, OR, -13, PERIOD, -13, QMARK, -13, RPAREN, -13, TK_EOI, -13};
static const int actTab_row_25[] = {2,LETTER, -18, RSQB, -18};

static const int *actTab[] = {
	 actTab_row_0, 	 actTab_row_1, 	 actTab_row_2, 	 actTab_row_3, 	 actTab_row_0, 
	 actTab_row_5, 	 actTab_row_6, 	 actTab_row_7, 	 actTab_row_8, 	 actTab_row_9, 
	 actTab_row_10, 	 actTab_row_11, 	 actTab_row_12, 	 actTab_row_13, 	 actTab_row_14, 
	 actTab_row_15, 	 actTab_row_0, 	 actTab_row_17, 	 actTab_row_18, 	 actTab_row_19, 
	 actTab_row_20, 	 actTab_row_21, 	 actTab_row_22, 	 actTab_row_23, 	 actTab_row_24, 
	 actTab_row_25
};

struct astnode;

static const map<string, function<astnode*(vector<astnode*>&)>> actions = {
	 {"mkCCLRange",mkCCLRange}, 
	 {"mkCcl",mkCcl}, 
	 {"mkConcat",mkConcat}, 
	 {"mkKleene",mkKleene}, 
	 {"mkLeaf",mkLeaf}, 
	 {"mkList",mkList}, 
	 {"mkOpt",mkOpt}, 
	 {"mkOr",mkOr}, 
	 {"pass",pass}

};
