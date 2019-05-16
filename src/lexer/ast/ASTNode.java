package lexer.ast;

public class ASTNode {
	
	private int parentID;
	private int nodeID;
	private String value;
	
	public ASTNode(int parentID, int nodeID, String value) {
		this.setParentID(parentID);
		this.setNodeID(nodeID);
		this.setValue(value);
	}

	public int getParentID() {
		return parentID;
	}

	public void setParentID(int parentID) {
		this.parentID = parentID;
	}

	public int getNodeID() {
		return nodeID;
	}

	public void setNodeID(int nodeID) {
		this.nodeID = nodeID;
	}

	public String getValue() {
		return value;
	}

	public void setValue(String value) {
		this.value = value;
	}
	
	public String toString() {
		return "\nParentID: " + this.parentID + ", NodeID: " + this.nodeID + ", Value: " + this.value;
	}
	
}
