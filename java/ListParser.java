public class ListParser extends Parser {
    public ListParser(Lexer input) {
        super(input);
    }

    public boolean list() {
        boolean rc;
        rc = match(ListLexer.LBRACK); 
        rc = elements(); 
        rc = match(ListLexer.RBRACK);
        return rc;
    }

    boolean elements() {
        boolean rc;
        rc = element();
        while (lookahead.type == ListLexer.COMMA) {
            rc = match(ListLexer.COMMA); 
            rc = element();
        }
        return rc;
    }

    boolean element() {
        boolean rc;
        if (lookahead.type == ListLexer.NAME) {
            rc = match(ListLexer.NAME);
        } else if (lookahead.type == ListLexer.LBRACK) {
            rc = list();
        } else {
            rc = false;
            //throw new Error("expecting name or list; found " + lookahead);
        }
        return rc;
    }
}
