package lexer.ast;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class AbstractSyntaxTree {
	/*
	 * Usage:
	 * 
	    AbstractSyntaxTree ast = new AbstractSyntaxTree();
		int idOfMainNode = ast.createNode(0, "main");  // create the main node
		int idOfFirstNode = ast.createNode(1, "1st node of main");
		int idOfSecondNode = ast.createNode(1, "2st node of main");
		int lastNode = ast.createNode(idOfFirstNode, "node of 1st node of main");
		
		System.out.println("Main node:");
		System.out.println(ast.getChildren(0));
		System.out.println("\nMain node's children:");
		System.out.println(ast.getChildren(idOfMainNode));
		System.out.println("\nMain's 1st node's children:");
		System.out.println(ast.getChildren(idOfFirstNode));
		System.out.println("\nEmpty node of the main's second node:");
		System.out.println(ast.getChildren(idOfSecondNode));
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
