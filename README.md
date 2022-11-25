# KPLC (King's Programming Language Compiler)

## Examples

### Basic

`Basic.kpl`

```kpl
procedure Initiate(
  argc::Int32, argv::@@UInt8
) -> Int32 {
  datum x?::Int32 = 7; \\ Question mark is the mutable operator.
  x = 21 + 14;
  return x;
}
```

```sh
$ kplc build ./Basic.kpl ./Basic.exe
$ ./Basic.exe
35
```
