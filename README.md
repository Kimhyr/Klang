# KC (K/King's Compiler)

## Examples

```klang
\\ Cool type system.
\\ Functions are treated as variables.
add<NumT: [Nat, Int, Real]>(first: NumT = 0, second: NumT): NumT
	= first + second;

execute() -> Int = {
	first: Int = 21;
	second: Real = 14;
	\\ Cool
	return add(.first=first, .second=second);
}
```
