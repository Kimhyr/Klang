#include "Token.H"

Void Token::Destroy() {
    switch ($ ID) {
    case TokenID::IDENTIFIER:
        delete[] $ Value.Identifier;
        break;
    case TokenID::TEXT:
        delete[] $ Value.Text;
        break;
    default:
        return;
    }
}
