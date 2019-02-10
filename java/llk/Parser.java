public class Parser {
    Lexer input;
    Token[] lookahead;
    int p = 0;
    int k;

    public Parser(Lexer input, int k) {
        this.input = input;
        this.k = k;
        lookahead = new Token[k];
        for (int i = 0; i < k; i++) consume();
    }

    public boolean match(int x) {
        if (LA(1) == x) {
            consume();
            return true;
        } else {
            return false;
            //else throw new Error("expecting " + input.getTokenName(x) + "; found " + lookahead);
        }
    }

    public void consume() {
        lookahead[p] = input.nextToken();
        p = ++p % k;
    }

    public Token LT(int i) {
        return lookahead[(p + i - 1) % k];
    }

    public int LA(int i) {
        return LT(i).type;
    }
}
