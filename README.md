# KC (K/King's Compiler)

The compiler still can't compile anything atm. 

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
