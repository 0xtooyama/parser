import java.util.Map;
import java.util.HashMap;

public class ListParser extends Parser {
    private Map<Integer, Integer> list_memo;

    public ListParser(Lexer input) {
        super(input);
        list_memo = new HashMap<Integer, Integer>();
    }

    public void clearMemo() {
        list_memo.clear();
    }

    public String stat() {
        boolean rc;
        if (speculate_stat_alt1()) {
            list(); 
            try {
                match(Lexer.EOF_TYPE);
            } catch (Exception e) {
                return "not sentence";
            }
            return "list";
        } else if (speculate_stat_alt2()) {
            assign(); 
            try {
                match(Lexer.EOF_TYPE);
            } catch (Exception e) {
                return "not sentence";
            }
            return "assign";
        } else return "not sentence";
    }

    private boolean speculate_stat_alt1() {
System.out.println("[start] speculate_stat_alt1()");
        boolean success = true;
        mark();
        try {
            list();
            match(Lexer.EOF_TYPE);
        } catch (Exception e) {
            success = false;
        }
        release();
System.out.println("[end]   speculate_stat_alt1()");
        return success;
    }

    private boolean speculate_stat_alt2() {
System.out.println("[start] speculate_stat_alt2()");
        boolean success = true;
        mark();
        try {
            assign(); match(Lexer.EOF_TYPE);
        } catch (Exception e) {
            success = false;
        }
        release();
System.out.println("[end]   speculate_stat_alt2()");
        return success;
    }

    private boolean assign() {
        boolean rc;
        rc = list();
        if (!rc) return rc;
        try {
            rc = match(ListLexer.EQUALS);
        } catch (Exception e) {
            return false;
        }
        rc = list();
        return rc;
    }

    private boolean list() {
        boolean failed = false;
        int startTokenIndex = index();
        if (isSpeculating() && alreadyParsedRule(list_memo)) {
System.out.println("\tactivate packrat. skip=>" + p);
            return true;
        }
        boolean rc = _list();
        if (!rc) failed = true;
        if (isSpeculating()) {
System.out.println("\tmemo p=" + p);
            memoize(list_memo, startTokenIndex, failed);
        }
        return rc;
    }

    private boolean _list() {
System.out.println("\t[call]  _list()");
        boolean rc;
        try {
            rc = match(ListLexer.LBRACK); 
        } catch (Exception e) {
            return false;
        }
        rc = elements(); 
        if (!rc) return rc;
        try {
            rc = match(ListLexer.RBRACK);
        } catch (Exception e) {
            return false;
        }
        return rc;
    }

    private boolean elements() {
        boolean rc;
        rc = element();
        if (!rc) return rc;
        while (LA(1) == ListLexer.COMMA) {
            try {
                rc = match(ListLexer.COMMA); 
            } catch (Exception e) {
                return false;
            }
            rc = element();
        }
        return rc;
    }

    private boolean element() {
        boolean rc;
        if (LA(1) == ListLexer.NAME && LA(2) == ListLexer.EQUALS) {
            try {
                rc = match(ListLexer.NAME);
                rc = match(ListLexer.EQUALS);
                rc = match(ListLexer.NAME);
            } catch (Exception e) {
                return false;
            }
        } else if (LA(1) == ListLexer.NAME) {
            try {
                rc = match(ListLexer.NAME);
            } catch (Exception e) {
                return false;
            }
        } else if (LA(1) == ListLexer.LBRACK) {
            rc = list();
        } else {
            rc = false;
            //throw new Error("expecting name or list; found " + lookahead);
        }
        return rc;
    }
}
