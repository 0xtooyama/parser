import java.util.List;
import java.util.ArrayList;

public class AST {
    Token token;

    public AST() { ; }

    public AST(Token token) {
        this.token = token;
    }

    public AST(int tokenType) {
        this.token = new Token(tokenType, null);
    }

    public String toString() {
        return token.toString();
    }

    public String toStringTree() {
        return toString();
    }
}
