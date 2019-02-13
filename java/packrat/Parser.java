import java.util.List;
import java.util.ArrayList;
import java.util.Map;

public abstract class Parser {
    Lexer input;
    List<Integer> markers;
    List<Token> lookahead;
    int p = 0;
    public static final int FAILED = -1;

    public Parser(Lexer input) {
        this.input = input;
        markers = new ArrayList<Integer>();
        lookahead = new ArrayList<Token>();
        sync(1);
    }

    public boolean match(int x) throws Exception {
        if (LA(1) == x) {
            consume();
            return true;
        } else {
            throw new Exception("error");
            //return false;
            //else throw new Error("expecting " + input.getTokenName(x) + "; found " + lookahead);
        }
    }

    public void consume() {
        p++;
        if (p == lookahead.size() && !isSpeculating()) {
            p = 0;
            lookahead.clear();
            clearMemo();
        }
        sync(1);
    }

    public void sync(int i) {
        if (p + i - 1 > lookahead.size() - 1) {
            int n = (p + i - 1) - (lookahead.size() - 1);
            fill(n);
        }
    }

    public void fill(int n) {
        for (int i = 0; i < n; i++) {
            lookahead.add(input.nextToken());
        }
    }

    public Token LT(int i) {
        sync(i);
        return lookahead.get(p + i - 1);
    }

    public int LA(int i) {
        return LT(i).type;
    }

    public int mark() {
        markers.add(p);
        return p;
    }

    public void release() {
        int marker = markers.get(markers.size() - 1);
        markers.remove(markers.size() - 1);
        seek(marker);
    }

    public void seek(int marker) {
        p = marker;
    }

    public boolean isSpeculating() {
        return markers.size() > 0;
    }

    public boolean alreadyParsedRule(Map<Integer, Integer> memoization) {
        Integer memoI = memoization.get(index());
        if (memoI == null) return false;
        int memo = memoI.intValue();
        if (memo == FAILED) return false;
        seek(memo);
        return true;
    }

    public void memoize(Map<Integer, Integer> memoization, int startTokenIndex, boolean failed) {
        int stopTokenIndex = failed ? FAILED : index();
        memoization.put(startTokenIndex, stopTokenIndex);
    }

    public int index() {return p;}

    public abstract void clearMemo();
}
