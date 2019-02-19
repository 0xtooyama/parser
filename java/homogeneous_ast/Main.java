public class Main {
    public static void main(String[] args) {
        Token plus = new Token(Token.PLUS, "+");
        Token one = new Token(Token.INT, "1");
        Token two = new Token(Token.INT, "2");

        AST root = new AST(plus);
        root.addChild(new AST(one));
        root.addChild(new AST(two));
        System.out.println("1+2 tree: " + root.toStringTree());

        AST list = new AST();
        list.addChild(new AST(one));
        list.addChild(new AST(two));
        System.out.println("1 and 2 in list: " + list.toStringTree());
    }
}
