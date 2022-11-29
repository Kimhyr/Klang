# KPLC (King's Programming Language Compiler)

## Examples

### Basic

`Basic.kpl`

```kpl
$[Entry]
procedure Initiate(
		    argc::Int32, argv::Ptr<Ptr<UInt8>>
) -> Int32 {
	  datum x?::Int32 = 7;
    datum arr::Array<4, UInt8> = c"Hi!\0";
	  x = 21 + 14;
	  return x;
}
```

```sh
$ kplc build ./Basic.kpl ./Basic.exe
$ ./Basic.exe
35
```
