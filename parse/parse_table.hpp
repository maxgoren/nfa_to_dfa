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
	 {12,val, {LSQB, optneg, cclist, RSQB},"@mkCcl"}, 
	 {13,optneg, {NEGATE},""}, 
	 {14,optneg, {},""}, 
	 {15,cclist, {cclist, ccent},"@mkList"}, 
	 {16,cclist, {ccent},""}, 
	 {17,ccent, {LETTER, DASH, LETTER},"@mkCCLRange"}, 
	 {18,ccent, {LETTER},""}
};
static const int goTab_row_0[] = {4,catexpr, 6, regex, 7, repexpr, 5, val, 4};
static const int goTab_row_1[] = {1,optneg, 9};
static const int goTab_row_3[] = {4,catexpr, 6, regex, 10, repexpr, 5, val, 4};
static const int goTab_row_6[] = {2,repexpr, 14, val, 4};
static const int goTab_row_9[] = {2,ccent, 17, cclist, 18};
static const int goTab_row_15[] = {3,catexpr, 20, repexpr, 5, val, 4};
static const int goTab_row_18[] = {1,ccent, 22};

static const int *goTab[] = {
	 goTab_row_0, 	 goTab_row_1, 	 NULL, 	 goTab_row_3, 	 NULL, 
	 NULL, 	 goTab_row_6, 	 NULL, 	 NULL, 	 goTab_row_9, 
	 NULL, 	 NULL, 	 NULL, 	 NULL, 	 NULL, 
	 goTab_row_15, 	 NULL, 	 NULL, 	 goTab_row_18, 	 NULL, 
	 goTab_row_6, 	 NULL
};

static const int actTab_row_0[] = {3,LETTER, 2, LPAREN, 3, LSQB, 1};
static const int actTab_row_1[] = {2,LETTER, -14, NEGATE, 8};
static const int actTab_row_2[] = {9,KLEENE_PLUS, -11, KLEENE_STAR, -11, LETTER, -11, LPAREN, -11, LSQB, -11, OR, -11, QMARK, -11, RPAREN, -11, TK_EOI, -11};
static const int actTab_row_4[] = {9,KLEENE_PLUS, 12, KLEENE_STAR, 13, LETTER, -9, LPAREN, -9, LSQB, -9, OR, -9, QMARK, 11, RPAREN, -9, TK_EOI, -9};
static const int actTab_row_5[] = {6,LETTER, -5, LPAREN, -5, LSQB, -5, OR, -5, RPAREN, -5, TK_EOI, -5};
static const int actTab_row_6[] = {6,LETTER, 2, LPAREN, 3, LSQB, 1, OR, -3, RPAREN, -3, TK_EOI, -3};
static const int actTab_row_7[] = {2,DOLLARACCEPT, 0, OR, 15};
static const int actTab_row_8[] = {1,LETTER, -13};
static const int actTab_row_9[] = {1,LETTER, 16};
static const int actTab_row_10[] = {2,OR, 15, RPAREN, 19};
static const int actTab_row_11[] = {6,LETTER, -8, LPAREN, -8, LSQB, -8, OR, -8, RPAREN, -8, TK_EOI, -8};
static const int actTab_row_12[] = {6,LETTER, -7, LPAREN, -7, LSQB, -7, OR, -7, RPAREN, -7, TK_EOI, -7};
static const int actTab_row_13[] = {6,LETTER, -6, LPAREN, -6, LSQB, -6, OR, -6, RPAREN, -6, TK_EOI, -6};
static const int actTab_row_14[] = {6,LETTER, -4, LPAREN, -4, LSQB, -4, OR, -4, RPAREN, -4, TK_EOI, -4};
static const int actTab_row_16[] = {3,DASH, 21, LETTER, -18, RSQB, -18};
static const int actTab_row_17[] = {2,LETTER, -16, RSQB, -16};
static const int actTab_row_18[] = {2,LETTER, 16, RSQB, 23};
static const int actTab_row_19[] = {9,KLEENE_PLUS, -10, KLEENE_STAR, -10, LETTER, -10, LPAREN, -10, LSQB, -10, OR, -10, QMARK, -10, RPAREN, -10, TK_EOI, -10};
static const int actTab_row_20[] = {6,LETTER, 2, LPAREN, 3, LSQB, 1, OR, -2, RPAREN, -2, TK_EOI, -2};
static const int actTab_row_21[] = {1,LETTER, 24};
static const int actTab_row_22[] = {2,LETTER, -15, RSQB, -15};
static const int actTab_row_23[] = {9,KLEENE_PLUS, -12, KLEENE_STAR, -12, LETTER, -12, LPAREN, -12, LSQB, -12, OR, -12, QMARK, -12, RPAREN, -12, TK_EOI, -12};
static const int actTab_row_24[] = {2,LETTER, -17, RSQB, -17};

static const int *actTab[] = {
	 actTab_row_0, 	 actTab_row_1, 	 actTab_row_2, 	 actTab_row_0, 	 actTab_row_4, 
	 actTab_row_5, 	 actTab_row_6, 	 actTab_row_7, 	 actTab_row_8, 	 actTab_row_9, 
	 actTab_row_10, 	 actTab_row_11, 	 actTab_row_12, 	 actTab_row_13, 	 actTab_row_14, 
	 actTab_row_0, 	 actTab_row_16, 	 actTab_row_17, 	 actTab_row_18, 	 actTab_row_19, 
	 actTab_row_20, 	 actTab_row_21, 	 actTab_row_22, 	 actTab_row_23, 	 actTab_row_24

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
