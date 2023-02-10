# Klang 

The compiler still can't compile anything atm. 

[ ] Analyzer
	[x] Lexer
	[ ] Parser
	[ ] Checkers
[ ] Synthesizer

## Examples

```klang
add(first: Int = 0, second: Int): Int
	= first + second;

execute(): Int = {
	first: Int = 21;
	second: Real = 14;
	return add(.first=first, .second=second);
}
```
