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
	 {11,val, {CHAR},"@mkLeaf"}, 
	 {12,val, {PERIOD},"@mkLeaf"}, 
	 {13,val, {ESCAPE, CHAR},"@mkEscaped"}, 
	 {14,val, {LSQB, optneg, cclist, RSQB},"@mkCcl"}, 
	 {15,optneg, {NEGATE},""}, 
	 {16,optneg, {},""}, 
	 {17,cclist, {cclist, ccent},"@mkList"}, 
	 {18,cclist, {ccent},""}, 
	 {19,ccent, {CHAR, DASH, CHAR},"@mkCCLRange"}, 
	 {20,ccent, {CHAR},""}
};
static const int goTab_row_0[] = {4,catexpr, 8, regex, 9, repexpr, 7, val, 6};
static const int goTab_row_1[] = {1,optneg, 11};
static const int goTab_row_5[] = {4,catexpr, 8, regex, 13, repexpr, 7, val, 6};
static const int goTab_row_8[] = {2,repexpr, 17, val, 6};
static const int goTab_row_11[] = {2,ccent, 20, cclist, 21};
static const int goTab_row_18[] = {3,catexpr, 23, repexpr, 7, val, 6};
static const int goTab_row_21[] = {1,ccent, 25};

static const int *goTab[] = {
	 goTab_row_0, 	 goTab_row_1, 	 NULL, 	 NULL, 	 NULL, 
	 goTab_row_5, 	 NULL, 	 NULL, 	 goTab_row_8, 	 NULL, 
	 NULL, 	 goTab_row_11, 	 NULL, 	 NULL, 	 NULL, 
	 NULL, 	 NULL, 	 NULL, 	 goTab_row_18, 	 NULL, 
	 NULL, 	 goTab_row_21, 	 NULL, 	 goTab_row_8, 	 NULL

};

static const int actTab_row_0[] = {5,CHAR, 4, ESCAPE, 2, LPAREN, 5, LSQB, 1, PERIOD, 3};
static const int actTab_row_1[] = {2,CHAR, -16, NEGATE, 10};
static const int actTab_row_2[] = {1,CHAR, 12};
static const int actTab_row_3[] = {11,CHAR, -12, ESCAPE, -12, KLEENE_PLUS, -12, KLEENE_STAR, -12, LPAREN, -12, LSQB, -12, OR, -12, PERIOD, -12, QMARK, -12, RPAREN, -12, TK_EOI, -12};
static const int actTab_row_4[] = {11,CHAR, -11, ESCAPE, -11, KLEENE_PLUS, -11, KLEENE_STAR, -11, LPAREN, -11, LSQB, -11, OR, -11, PERIOD, -11, QMARK, -11, RPAREN, -11, TK_EOI, -11};
static const int actTab_row_6[] = {11,CHAR, -9, ESCAPE, -9, KLEENE_PLUS, 15, KLEENE_STAR, 16, LPAREN, -9, LSQB, -9, OR, -9, PERIOD, -9, QMARK, 14, RPAREN, -9, TK_EOI, -9};
static const int actTab_row_7[] = {8,CHAR, -5, ESCAPE, -5, LPAREN, -5, LSQB, -5, OR, -5, PERIOD, -5, RPAREN, -5, TK_EOI, -5};
static const int actTab_row_8[] = {8,CHAR, 4, ESCAPE, 2, LPAREN, 5, LSQB, 1, OR, -3, PERIOD, 3, RPAREN, -3, TK_EOI, -3};
static const int actTab_row_9[] = {2,DOLLARACCEPT, 0, OR, 18};
static const int actTab_row_10[] = {1,CHAR, -15};
static const int actTab_row_11[] = {1,CHAR, 19};
static const int actTab_row_12[] = {11,CHAR, -13, ESCAPE, -13, KLEENE_PLUS, -13, KLEENE_STAR, -13, LPAREN, -13, LSQB, -13, OR, -13, PERIOD, -13, QMARK, -13, RPAREN, -13, TK_EOI, -13};
static const int actTab_row_13[] = {2,OR, 18, RPAREN, 22};
static const int actTab_row_14[] = {8,CHAR, -8, ESCAPE, -8, LPAREN, -8, LSQB, -8, OR, -8, PERIOD, -8, RPAREN, -8, TK_EOI, -8};
static const int actTab_row_15[] = {8,CHAR, -7, ESCAPE, -7, LPAREN, -7, LSQB, -7, OR, -7, PERIOD, -7, RPAREN, -7, TK_EOI, -7};
static const int actTab_row_16[] = {8,CHAR, -6, ESCAPE, -6, LPAREN, -6, LSQB, -6, OR, -6, PERIOD, -6, RPAREN, -6, TK_EOI, -6};
static const int actTab_row_17[] = {8,CHAR, -4, ESCAPE, -4, LPAREN, -4, LSQB, -4, OR, -4, PERIOD, -4, RPAREN, -4, TK_EOI, -4};
static const int actTab_row_19[] = {3,CHAR, -20, DASH, 24, RSQB, -20};
static const int actTab_row_20[] = {2,CHAR, -18, RSQB, -18};
static const int actTab_row_21[] = {2,CHAR, 19, RSQB, 26};
static const int actTab_row_22[] = {11,CHAR, -10, ESCAPE, -10, KLEENE_PLUS, -10, KLEENE_STAR, -10, LPAREN, -10, LSQB, -10, OR, -10, PERIOD, -10, QMARK, -10, RPAREN, -10, TK_EOI, -10};
static const int actTab_row_23[] = {8,CHAR, 4, ESCAPE, 2, LPAREN, 5, LSQB, 1, OR, -2, PERIOD, 3, RPAREN, -2, TK_EOI, -2};
static const int actTab_row_24[] = {1,CHAR, 27};
static const int actTab_row_25[] = {2,CHAR, -17, RSQB, -17};
static const int actTab_row_26[] = {11,CHAR, -14, ESCAPE, -14, KLEENE_PLUS, -14, KLEENE_STAR, -14, LPAREN, -14, LSQB, -14, OR, -14, PERIOD, -14, QMARK, -14, RPAREN, -14, TK_EOI, -14};
static const int actTab_row_27[] = {2,CHAR, -19, RSQB, -19};

static const int *actTab[] = {
	 actTab_row_0, 	 actTab_row_1, 	 actTab_row_2, 	 actTab_row_3, 	 actTab_row_4, 
	 actTab_row_0, 	 actTab_row_6, 	 actTab_row_7, 	 actTab_row_8, 	 actTab_row_9, 
	 actTab_row_10, 	 actTab_row_11, 	 actTab_row_12, 	 actTab_row_13, 	 actTab_row_14, 
	 actTab_row_15, 	 actTab_row_16, 	 actTab_row_17, 	 actTab_row_0, 	 actTab_row_19, 
	 actTab_row_20, 	 actTab_row_21, 	 actTab_row_22, 	 actTab_row_23, 	 actTab_row_24, 
	 actTab_row_25, 	 actTab_row_26, 	 actTab_row_27
};

struct astnode;

static const map<string, function<astnode*(vector<astnode*>&)>> actions = {
	 {"mkCCLRange",mkCCLRange}, 
	 {"mkCcl",mkCcl}, 
	 {"mkConcat",mkConcat}, 
	 {"mkEscaped",mkEscaped}, 
	 {"mkKleene",mkKleene}, 
	 {"mkLeaf",mkLeaf}, 
	 {"mkList",mkList}, 
	 {"mkOpt",mkOpt}, 
	 {"mkOr",mkOr}, 
	 {"pass",pass}

};
