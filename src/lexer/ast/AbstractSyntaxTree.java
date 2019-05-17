package lexer.ast;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class AbstractSyntaxTree {
	/*
        Example for the code:
        a = 0
        b = 10
        
        if a < b
            a += 1
            print "Something"
        elseif a == b
            a -= 1
        else
            a -= b
        endif
        
        AbstractSyntaxTree ast = new AbstractSyntaxTree();
        ast.createNode(ast.createNode(ast.createNode(0, "a"), "="), "0");
        ast.createNode(ast.createNode(ast.createNode(0, "b"), "="), "10");
        int ifID = ast.createNode(0, "if");
        ast.createNode(ast.createNode(ast.createNode(ast.createNode(ifID, "condition"), "a"), "<"), "b");
        int ifBodyID = ast.createNode(ifID, "body");
        ast.createNode(ast.createNode(ast.createNode(ifBodyID, "a"), "+="), "1");
        ast.createNode(ast.createNode(ast.createNode(ifBodyID, "print"), "parameters"), "\"Something\"");
        int elseIfID = ast.createNode(ifID, "elseif");
        ast.createNode(ast.createNode(ast.createNode(ast.createNode(elseIfID, "condition"), "a"), "=="), "b");
        ast.createNode(ast.createNode(ast.createNode(ast.createNode(elseIfID, "body"), "a"), "-="), "1");
        ast.createNode(ast.createNode(ast.createNode(ast.createNode(ast.createNode(ifID, "else"), "body"), "a"), "-="), "b");
	*/
	
	private HashMap<Integer, ASTNode> container;
	private int lastUsedID;  // Just increased, never decreased
	
	public AbstractSyntaxTree() {
		this.container = new HashMap<Integer, ASTNode>();
		this.lastUsedID = 0;
	}
	
	public int getNewID() {
		this.lastUsedID += 1;
		return this.lastUsedID;
	}
	
	public int createNode(int parentID, String value) {
		int id = getNewID();
		createNode(parentID, id, value);
		return id;
	}
	
	public void createNode(int parentID, int nodeID, String value) {
		this.container.put(nodeID, new ASTNode(parentID, nodeID, value));
	}
	
	public List<ASTNode> getChildren(int parentID) {
		List<ASTNode> children = new ArrayList<ASTNode>();
		
		for (Object key : this.container.keySet().toArray()) {
			ASTNode currentNode = this.container.get(key);
			if (currentNode.getParentID() == parentID) {
				children.add(currentNode);
			}
		}
		
		return children;
	}
	
	public ASTNode getNode(int id) {
		return this.container.get(id);
	}
	
}
