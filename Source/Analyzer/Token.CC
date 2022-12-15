#include "Token.H"

Void Token::Destroy() {
    switch ($ ID) {
    case Token::IDENTIFIER:
        delete[] $ Value.Identifier;
        break;
    case Token::TEXT:
        delete[] $ Value.Text;
        break;
    default:
        return;
    }
}
