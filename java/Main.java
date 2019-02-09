class Main {
    public static void main(String[] args) {
        //lexerTest(args);
        parserTest(args);
    }

    private static void parserTest(String[] args) {
        ListLexer lexer = new ListLexer(args[0]);
        ListParser parser = new ListParser(lexer);
        boolean rc = parser.list();
        if (rc) System.out.println("list");
        else System.out.println("not list");
    }

    private static void lexerTest(String[] args) {
        ListLexer lexer = new ListLexer(args[0]);
        Token t = lexer.nextToken();
        while (t.type != Lexer.EOF_TYPE) {
            System.out.println(t);
            t = lexer.nextToken();
        }
        System.out.println(t);
    }
}
