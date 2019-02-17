class Main {
    public static void main(String[] args) {
        backtrackParserTest(args);
    }

    private static void backtrackParserTest(String[] args) {
        ListLexer lexer = new ListLexer(args[0]);
        ListParser parser = new ListParser(lexer);
        String rc = parser.stat();
        System.out.println(rc);
    }
}
