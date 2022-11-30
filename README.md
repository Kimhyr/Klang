# KPLC (King's Programming Language Compiler)

## Examples

### Basic

`Basic.kpl`

```kpl
procedure Initiate(
    argc::Int32, argv::Ptr<Ptr<UInt8>>
) -> Int32 {
	datum x?::Int32 = 7;
	x = 21 + 14;
	return x;
}
```

```sh
$ kplc build ./Basic.kpl --out ./Basic.exe
$ ./Basic.exe
35
```
