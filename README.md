# Klang 

## The symbol table




## Examples

```klang

type Day = $[enumerate(type: I), omit(lexeme.: value)] {
	sunday; monday; tuesday; thrusday; friday; saturday
};

type Pair(First_T, Second_T): Object = $omit(lexeme.: value) = {
	type Self_T = Pair(First_T, Second_T);

	first!: First_T;
	second!: Second_T;

	create!(first: First_T, second: Second_T): Self_T =
		Self_T { first, second };

	destroy!?() = {
		$compare First_T::Object =>
			.first.destroy();
		$compare Second_T::Object =>
			.second.destroy();
	};
};

type Number = I | N | R;

value add(pair: Pair(Number, Number)): .pair::Pair.First_T =
	first + second;

value execute(): I = {
	value sum: I = add(1, 2);
	return sum;
};
```
