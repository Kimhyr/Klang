# KC (K/King's Compiler)

## Examples

```klang
add<NumT: [Nat, Int, Real]>(
	first: NumT = 0, second: NumT): NumT = {
	return first + second;
}

execute() -> Int = {
	return add(21, 14);
}
```
