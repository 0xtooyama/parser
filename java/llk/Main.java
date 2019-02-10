class Main {
    public static void main(String[] args) {
        lookaheadParserTest(args);
    }

    private static void lookaheadParserTest(String[] args) {
        ListLexer lexer = new ListLexer(args[0]);
        ListParser parser = new ListParser(lexer, 3);
        boolean rc = parser.list();
        if (rc) System.out.println("list");
        else System.out.println("not list");
    }
}
