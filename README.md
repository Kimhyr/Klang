# KC (K/King Compiler)

## Examples

### Basic

`Basic.kpl`

```k
procedure Initiate(
		argc::Int32, argv::@@Nat8
) -> Int32 {
	datum value?::Int32 {7}
	value = 21 + 14;
	return value;
}
```

```sh
$ kc build ./Basic.kpl --out ./Basic.exe
$ ./Basic.exe
35
```
