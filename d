x: I = 0;
y: I = 1;
add[x: I, y: I]: I = x + y;
add[x, y] == 1 => x = 3;
y = add[x, y];
y == 3 => do_something;
y {
	. == 2 => do_something;
	. = 3;
	. == 3 => do_something_else;
} == 3 => {
	do_many_things;
}

1 + (T != F => F);
