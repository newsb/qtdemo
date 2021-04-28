#include "booleanparser.h"

Node *BooleanParser::parse(const QString &expr)
{
    //传入的布尔表达式的字符串保存下来，避免直接修改参数（这也是库的接口设计中常见的一个原则：不修改参数）
    in = expr;
    //将其中的空格全部去掉，并将 pos 设为 0。pos 就是我们在分析布尔表达式字符串时的当前字符位置，起始为 0。
    in.replace(" ", "");
    pos = 0;
    //创建了 Root 节点——布尔表达式的树状表达，显然需要有一个根节点，
    //所以我们在这里直接创建根节点，这个根节点就是一个完整的布尔表达式。
    Node *node = new Node(Node::Root);
    addChild(node, parseOrExpression());
    return node;
}
/*首先我们先来看看布尔表达式的文法：
 * BE→ BE OR BE
      | BE AND BE
      | NOT BE
      | (BE)
      | RE | true | false
    RE→ RE RELOP RE | (RE) | E
    E → E op E | -E | (E) | Identifier | Number
 *
 *
 *
 *
 */
Node *BooleanParser::parseOrExpression()
{
    Node *childNode = parseAndExpression();
    if (matchToken("||")) {
        Node *node = new Node(Node::OrExpression);
        addChild(node, childNode);
        while (matchToken("||")) {
            addToken(node, "||", Node::Operator);
            addChild(node, parseAndExpression());
        }
        return node;
    } else {
        return childNode;
    }
}

Node *BooleanParser::parseAndExpression()
{
    Node *childNode = parseNotExpression();
    if (matchToken("&&")) {
        Node *node = new Node(Node::AndExpression);
        addChild(node, childNode);
        while (matchToken("&&")) {
            addToken(node, "&&", Node::Operator);
            addChild(node, parseNotExpression());
        }
        return node;
    } else {
        return childNode;
    }
}

Node *BooleanParser::parseNotExpression()
{
    if (matchToken("!")) {
        Node *node = new Node(Node::NotExpression);
        while (matchToken("!"))
            addToken(node, "!", Node::Operator);
        addChild(node, parseAtom());
        return node;
    } else {
        return parseAtom();
    }
}

Node *BooleanParser::parseAtom()
{
    if (matchToken("(")) {
        Node *node = new Node(Node::Atom);
        addToken(node, "(", Node::Punctuator);
        addChild(node, parseOrExpression());
        addToken(node, ")", Node::Punctuator);
        return node;
    } else {
        return parseIdentifier();
    }
}

Node *BooleanParser::parseIdentifier()
{
    int startPos = pos;
    while (pos < in.length() && in[pos].isLetterOrNumber())
        ++pos;
    if (pos > startPos) {
        return new Node(Node::Identifier,
                        in.mid(startPos, pos - startPos));
    } else {
        return 0;
    }
}

void BooleanParser::addChild(Node *parent, Node *child)
{
    if (child) {
        parent->children += child;
        parent->str += child->str;
        child->parent = parent;
    }
}

void BooleanParser::addToken(Node *parent, const QString &str,
                             Node::Type type)
{
    if (in.mid(pos, str.length()) == str) {
        addChild(parent, new Node(type, str));
        pos += str.length();
    }
}

bool BooleanParser::matchToken(const QString &str) const
{
    return in.mid(pos, str.length()) == str;
}
