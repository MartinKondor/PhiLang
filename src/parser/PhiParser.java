package parser;

import java.util.List;

import lexer.Checker;
import lexer.ast.ASTNode;
import lexer.ast.AbstractSyntaxTree;

public class PhiParser {

    AbstractSyntaxTree ast;
    String previousASTNode;

    public PhiParser(AbstractSyntaxTree ast) {
        this.ast = ast;
        this.previousASTNode = "null";
    }
    
    public String executeASTNodes() {
        String outputs = "";
        for (ASTNode node : ast.getChildren(0)) {
            String output = executeASTNode(node);
            if (!output.isEmpty()) {
                outputs += output;
            }
        }
        return outputs;
    }

    public String executeASTNode(ASTNode node) {
         String nodeValue = node.getValue();
         
         /*
         * First check for statements and expressions
         *
         * If something is found then pervade the tree for the needed
         * values according to he value recognized.
         */
         if (nodeValue == "if") {
             /*
             * if's AST node structure:
             
                | Value    |   Type
                condition -> ASTNode
                body -> ASTNode
                elseif -> ASTNode (Optional. Has the same structure as if)
                else -> ASTNode (Optional. Has the same structure as if.
                              If elseif is before else then elseif's node would have it.)
             */
             return "if";
         }
         if (nodeValue == "for") {
             return "for";
         }
         if (nodeValue == "=") {
             /*
             * ='s AST node structure:
                
                leftSide = rightSide
                
                parent is the leftSide
                a child is the rightSide
             */
             if (this.previousASTNode == "=") {
                 // throw syntax error
                 // since "a = = b" is not correct
                 return "null";
             }
             // It can only have one children
             List<ASTNode> children = this.ast.getChildren(node.getNodeID());
             if (children.size() == 0) {
                 // throw syntax error
                 // since "a = " is not correct
                 return "null";
             }
             else if (children.size() > 1) {
                 // then the type is list
                 return "null";
             }
             return executeASTNode(children.get(0));
         }
	     if (nodeValue == "==") {
	         /*
	         * Same structure as in "="
	         */
             return this.ast.getNode(node.getParentID()).getValue() + " == " + executeASTNode(this.ast.getChildren(node.getNodeID()).get(0));
         }
	     if (nodeValue == "!=") {
	         /*
	         * Same structure as in "="
	         */
             return this.ast.getNode(node.getParentID()).getValue() + " != " + executeASTNode(this.ast.getChildren(node.getNodeID()).get(0));
         }
         if (nodeValue == "+=") {
	         /*
	         * Same structure as in "="
	         */
             return this.ast.getNode(node.getParentID()).getValue() + " + " +  executeASTNode(this.ast.getChildren(node.getNodeID()).get(0));
         }
         if (nodeValue == "-=") {
	         /*
	         * Same structure as in "="
	         */
             return this.ast.getNode(node.getParentID()).getValue() + " - " + executeASTNode(this.ast.getChildren(node.getNodeID()).get(0));
         }
	     if (nodeValue == "<") {
	         /*
	         * Same structure as in "="
	         */
	         String rightSide = executeASTNode(this.ast.getChildren(node.getNodeID()).get(0));
	         if (!Checker.isNumeric(rightSide)) {
	             // throw an error
	             return "null"; 
	         }
             return this.ast.getNode(node.getParentID()).getValue() + " < " + String.valueOf(Integer.parseInt(rightSide));
         }
	     if (nodeValue == "<=") {
	         /*
	         * Same structure as in "="
	         */
	         String rightSide = executeASTNode(this.ast.getChildren(node.getNodeID()).get(0));
	         if (!Checker.isNumeric(rightSide)) {
	             // throw an error
	             return "null"; 
	         }
             return this.ast.getNode(node.getParentID()).getValue() + " <= " + executeASTNode(this.ast.getChildren(node.getNodeID()).get(0));
         }
	     if (nodeValue == ">") {
	         /*
	         * Same structure as in "="
	         */
	         String rightSide = executeASTNode(this.ast.getChildren(node.getNodeID()).get(0));
	         if (!Checker.isNumeric(rightSide)) {
	             // throw an error
	             return "null"; 
	         }
             return this.ast.getNode(node.getParentID()).getValue() + " > " + executeASTNode(this.ast.getChildren(node.getNodeID()).get(0));
         }
         if (nodeValue == ">=") {
	         /*
	         * Same structure as in "="
	         */
	         String rightSide = executeASTNode(this.ast.getChildren(node.getNodeID()).get(0));
	         if (!Checker.isNumeric(rightSide)) {
	             // throw an error
	             return "null"; 
	         }
             return this.ast.getNode(node.getParentID()).getValue() + " >= " + executeASTNode(this.ast.getChildren(node.getNodeID()).get(0));
         }
	     if (nodeValue == "!=") {
	         /*
	         * Same structure as in "="
	         */
             return this.ast.getNode(node.getParentID()).getValue() + " != " + executeASTNode(this.ast.getChildren(node.getNodeID()).get(0));
         }
         
         if (Checker.isNumeric(nodeValue)) {
             return nodeValue;
         }
         if (Checker.isVariable(nodeValue)) {
             // Execute the right part of the equation
             // and save the variable
             // TODO
             return nodeValue + " will have the value of " + executeASTNode(ast.getChildren(node.getNodeID()).get(0)) + "\n";
         }
         
         return "null";
    }
	
}
