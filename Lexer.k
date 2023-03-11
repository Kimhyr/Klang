type Lexeme_Value = C|String|N64|R64;

value lambda: [] -> T {
	
}



type Lexeme_Tag: I8 =
	undefined: I => -127, name, natural, real,
	string, object, p => 'P' + 3;

type Lexer {

function lex[self: @Self] {
label Restart =:
	loop #self.current =>
		#self.advance;
	#self.lexeme.start = #self.position;
	value tag: I8;
	compare #self.current::Lexeme {
		case .slosh {
			compare #self.peek == "\" {
				loop {
					#self.advance;
					compare #self.source.eof =>
						goto Return_EOT;
					compare #self.current != \"\13" =>
						jump Restart;
				}
			}
		}
		case .plus | .minus | .colon | .semicolon |
		.equal | .asterisk | .slash | .percent |
		.o_paren | .c_paren {
			tag #self.current;
			#self.advance;
		}
		case {
			compare #self.current {
				case is_alpha {
					value buf: std.stringbuf;
					loop {
						compare buf.view.length >= Lexeme.MAX_VALUE_LENGTH =>
							throw diagnose[Severity.error, #self.lexeme.start, buf.view,
										   Message.buffer_overflow["lex an identifier."]];
						buf.sputc[#self.current];
						#self.advance;
						compare #self.current == "_" | #self.current.is_digit =>
							escape;
					}
					value length: N = buf.view.length;
					compare buf.view {
						case Lexeme.String.literal_object =>
							tag = Lexeme.object;
						case {
							buf.sputc[0];
							compare len >= 1 & len <= 3 {
								compare buf.view.begin.0 {
									case "P" => tag = Lexeme.P;
									case "N" => tag = Lexeme.N;
									case "I" => tag = Lexeme.I;
									case "R" => tag = Lexeme.R;
									case => jump Lex_Name;
								}
								compare buf.view.begin.0 == 0 =>
									jump Finalize;
								compare buf.view.begin.1 + buf.view[2] {
									compare tag != Lexeme.R {
										case '8' => tag += 4;
										case '1' + '6' => tag += 3;
									}
									case '3' + '2' => tag += 2;
									case '6' + '4' => tag += 1;
									case => jump Lex_Name;
								}
								escape;
							}
						}
					label Lex_Name :=
						tag = Lexeme.name;
						#self.lexeme.value:String = buf.view;
						jump Finalize;
					}
				}
				case is_digit {
					tag 
				}
			}
		}
	}

}

}