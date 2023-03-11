# Klang 

## Internals

### The symbol table

A hash table is very inefficient. Hashing requires an iteration over the entire
input's key; then, a look-up by indexing to the input's key's hash value; and,
finally, an iteration from the index until the input's key is equivalent to the
current key. The hash table is only efficient because it *gets close* to the
requested value, which \[the value] is always in a global scope (where all the
identifiers are). The efficiency of a hash table is also reliant on the size of
the table: the larger it is, the faster the look-up is. However, a hash table
would need to be very large to index a large amount of identifiers, and,
sometimes, some of the table's mass is bloat.

---

Modern programming languages have different scopes in which identifiers can be
placed to prevent ambiguity, and accept organization. So we can utilize
different scopes (the code blocks namespaces, structs, and procedures use) as
sets of identifiers to never have to iterate over every identifier, and
because, in many modern programming languages, identifier paths (from
namespaces and structs) makes it faster to find the requested value. After
talking about hash tables, someone would think to have hash tables with edges
connecting to other hash tables to represent nested scopee. Sure, this is okay,
but we can do better.

Programmers never use all the identifiers, and they use certain identifiers
more than others in different places. Because of this, we can organize the
identifiers by the behavior of the look-up times:
* identifiers in local scopes are usually looked at when they are defined, so
	we can organize them as first-in-first, also, because of scopes, we can
	destroy the identifiers inside the scope easily when leaving the scope to
	relieve space;
* identifiers in top scopes (the global scope and struct/class/et cetera
	scopes) are usually looked at arbitrarily, and the look-up times differ in
	different local scopes, so we can organize them as most-looked-first and
	reset the organization biases within the scope when exiting a local scope.

*Depending on the implementation, resetting the organization bias within a
scope may not reorganize the identifiers*.

---

We can further organize the connections between the identifiers by the type of
the identifiers. Values (variables, constants, et cetera) can be connected
within their scope, just like how structs and classes would too. Note that how
the type of an identifier is used may be ambigious to other types of
identifiers. For example, structs and classes are used in the same way.

---

With all of these factors, hashing an input's key may just be an overhead
because the size of an organized group (the connections of scopes and types)
may be less than the length of the identifier, and, because of how things are
organized, the time it takes to look up an identifier is greatly reduced to
the point where the hashing takes longer to compute at times. However,
sometimes an identifier may be looked up and would take a very long time, so
you could, at a certain point of the look-up, start a hash and look-up from
there.

There are other ways of implementing a symbol table--some of which are
definitely more efficient--, but this is how I came up and implemented mine.

## Examples

```klang
\\ `I` is the integer type.
\\ I is equavalent to the max size of an integer for a given CPU arch..
value my_value: I = 21 + 14;


\\ Data types:
type All_Types =
	V | T  | @T  |                   \\ No type, any type, and pointer type.
	I | I8 | I16 | I32 | I64 | \\ Integer number types.
	N | N8 | N16 | N32 | N64 | \\ Natural number types.
	R            | R32 | R64   \\ Real number types.

value ptr: @I = @my_value; \\ Get the address of `my_value`, then copy it to
                           \\ `ptr`.
#ptr += 1; \\ Dereference `ptr`, then copy an incremented value of `ptr` to the
           \\ value of `ptr`.

\\ A procedure:
value my_procedure(a: I, b: I): I = a + b;

value less -> V = {
	my_procedure(21, 14);
};

\\ A procedure that takes a procedure as a parameter.
value take_procedure(procedure: V): 


```
