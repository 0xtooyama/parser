import java.util.List;
import java.util.ArrayList;
import java.lang.StringBuilder;

public class VectorNode extends ExprNode {
    public List<ExprNode> children = new ArrayList<ExprNode>();

    public VectorNode(Token t, List<ExprNode> elements) {
        super(t);
        children = elements;
    }

    public String toStringTree() {
        if (children.size() == 0) {
            return "";
        }

        StringBuilder buf = new StringBuilder();
        buf.append("(");
        for (ExprNode i : children) {
            buf.append(i.toString());
            buf.append(" ");
        }
        buf.append(")");
        return buf.toString();
    }
}
