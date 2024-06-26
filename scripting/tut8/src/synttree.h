#ifndef _SYNTTREE_H_
#define _SYNTTREE_H_

// The syntax tree node types
enum NodeType  {
   // Statements
   STMT_LIST,        // list of statements [left-part, right-part] (left-part may be another list)
   EMPTY_STMT,       // empty statement []
   EXPR_STMT,        // single expression as statement [expression]
   PRINT_STMT,       // print statement [expression]
   INPUT_STMT,       // input statement [variable]
   IFTHEN_STMT,      // if statement [cond, if-part]
   IFTHENELSE_STMT,  // if statement with else [cond, if-part, else-part]
   ERROR_STMT,       // error statement
   
   // Expressions
   EQUAL_EXPR,       // equality expression [op1, op2]
   ASSIGN_EXPR,      // assignment expression [variable, op2]
   CONCAT_EXPR,      // concatenation expression [op1, op2]
   IDENT_EXPR,       // identifier (link to symbol table)
   STR_EXPR,         // string constant (link to symbol table)

   COERCE_TO_STR     // coercion to string (from boolean)
};

enum DataType  {
   T_VOID,
   T_STRING,
   T_BOOL
};

const int MXCHILD = 3;   // max. number of children a tree node can have

class SymDesc;

// The syntax tree node class
class TreeNode  {
public:
   TreeNode (NodeType _type)   {type = _type; child[0] = NULL; child[1]=NULL; child[2]=NULL; Check();}
   TreeNode (NodeType _type, TreeNode *child1)   {type = _type; child[0] = child1; child[1]=NULL; child[2]=NULL; Check();}
   TreeNode (NodeType _type, TreeNode *child1, TreeNode *child2)   {type = _type; child[0] = child1; child[1]=child2; child[2]=NULL; Check();}
   TreeNode (NodeType _type, TreeNode *child1, TreeNode *child2, TreeNode *child3)  {type = _type; child[0] = child1; child[1]=child2; child[2]=child3; Check();}
   void Show ()  {Show(0);}    // Show the tree contents
   void Check ();              // Check the node for semantic errors
   int CoerceToString (int childno);  // Coerce a child to string type

   NodeType type;              // what type of node is it?
   SymDesc  *symbol;           // pointer to symbol, if applicable
   TreeNode *child[MXCHILD];   // pointers to children
   DataType rettype;           // the 'return' type of the node
private:
   void Show (int level);
};

typedef TreeNode *SyntTree;

#endif