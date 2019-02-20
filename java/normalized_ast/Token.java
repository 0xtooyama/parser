public class Token {
    public static int PLUS = 2;
    public static int INT = 1;

    public static String[] tokenNames = {"n/a", "<EOF>", "PLUS", "INT"};

    public int type;
    public String text;

    public Token(int type, String text) {
        this.type = type;
        this.text = text;
    }

    public String toString() {
        String tname = ListLexer.tokenNames[type];
        return text;
    }
}
