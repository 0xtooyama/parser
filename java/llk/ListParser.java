public class ListParser extends Parser {
    public ListParser(Lexer input, int k) {
        super(input, k);
    }

    public boolean list() {
        boolean rc;
        rc = match(ListLexer.LBRACK); 
        if (!rc) return rc;
        rc = elements(); 
        if (!rc) return rc;
        rc = match(ListLexer.RBRACK);
        return rc;
    }

    boolean elements() {
        boolean rc;
        rc = element();
        while (LA(1) == ListLexer.COMMA) {
            match(ListLexer.COMMA); 
            rc = element();
        }
        return rc;
    }

    boolean element() {
        boolean rc;
        if (LA(1) == ListLexer.NAME && LA(2) == ListLexer.EQUALS) {
            rc = match(ListLexer.NAME);
            if (!rc) return rc;
            rc = match(ListLexer.EQUALS);
            if (!rc) return rc;
            rc = match(ListLexer.NAME);
        } else if (LA(1) == ListLexer.NAME) {
            rc = match(ListLexer.NAME);
        } else if (LA(1) == ListLexer.LBRACK) {
            rc = list();
        } else {
            rc = false;
            //throw new Error("expecting name or list; found " + lookahead);
        }
        return rc;
    }
}
