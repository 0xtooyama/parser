public class Parser {
    Lexer input;
    Token lookahead;

    public Parser(Lexer input) {
        this.input = input;
        consume();
    }

    public boolean match(int x) {
        if (lookahead.type == x) {
            consume();
            return true;
        } else {
            return false;
            //else throw new Error("expecting " + input.getTokenName(x) + "; found " + lookahead);
        }
    }

    public void consume() {
        lookahead = input.nextToken();
    }
}
