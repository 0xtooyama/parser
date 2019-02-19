public abstract class ExprNode extends AST {
    public static final int tINVALID = 0;
    public static final int tINTEGER = 1;
    public static final int tVECTOR = 2;

    int evalType;

    public int getEvalType() { 
        return evalType; 
    }

    public ExprNode(Token payload) { 
        super(payload); 
    }

    public String toString() {
        if (evalType != tINVALID) {
            return super.toString() + "<type=" + (evalType == tINTEGER ? "tINTEGER" : "tVECTOR") + ">";
        }
        return super.toString();
    }
}
