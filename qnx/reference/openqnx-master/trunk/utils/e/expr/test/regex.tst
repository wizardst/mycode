expr 'aaaaaa' : '(a*)\1\1(a*)\2\2\2'
expr 'aaaa' : '(a*)(a*)\1\2'
expr 'aaaa' : '(a*)\1(a*)\2\2'
expr 'aaaaaa' : '(a*)\1\1(a*)'
expr 'aaaaaa' : '(a*)\1\1(a*)\2'
expr 'aaaaaa' : '(a*)\1\1(a*)\2\2'
expr 'aaaaaa' : '(.*)\1\1(.*)\2\2\2'
expr 'aaaaaaa' : '(.*)\1\1(.*)\2\2\2'
expr 'aaaaaa' : '(.*)\1\1(.*)\2\2\2'
expr 'aaaaaaa' : '(.*)\1\1(.*)\2\2\2'
expr 'aaaaa' : '(.*)\1\1(.*)\2\2\2'
expr 'aaaaaa' : 'a*a*a*a*'
expr 'aaaaaa' : 'a*a*a*a*a*'
expr 'aaaaaa' : 'a*a*a*a*a*a*'
expr 'aaaaaa' : 'a*a*a*a*a*a*a*'
expr '' : '"'
expr 'abcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdf' : '(a.*bcde\|a.*cde\|a.*de\|a.*e)(a.*b\|a.*c\|a.*d\|a.*e)\1'
expr '' : ''
expr 'abc' : 'ab{0,0}c'
expr 'abbc' : 'ab{1,1}c'
expr 'abbbbbbbbc' : 'ab{3,7}c'
expr 'abbbbbbbbbc' : 'ab{3,7}c'
expr 'abbbbbbbbbbc' : 'ab{3,7}c'
expr 'abbbbbbbbbbbc' : 'ab{3,7}c'
expr 'bb' : 'b{2,7}'
expr '' : ''
expr 'b' : 'b{1,6}'
expr 'b' : 'b{2,7}'
expr 'ac' : 'ab{0,7}c'
expr 'abc' : 'ab{1,7}c'
expr 'abbc' : 'ab{2,7}c'
expr 'abbbc' : 'ab{3,7}c'
expr 'abbbbc' : 'ab{3,7}c'
expr 'abbbbbc' : 'ab{3,7}c'
expr 'abbbbbbc' : 'ab{3,7}c'
expr 'abbbbbbbc' : 'ab{3,7}c'
expr 'abbbbbbbbc' : 'ab{3,7}c'
expr 'abbc' : 'ab{3,7}c'
expr 'abc' : 'ab{3,7}c'
expr 'foo' : '[]][[.].]][[.right-square-bracket.]]	a]]]'
expr 'aaaaaa' : 'a*a*'
expr 'aaaaaa' : 'a*a*a*'
expr 'aaa' : '(.*)\1\1'
expr 'xc' : '(a\|b)*c\|(a\|ab)*c'
expr 'b' : '(a)*'
expr 'a' : '(..)*(...)*'
expr 'abc' : '(..)*(...)*'
expr 'xx' : '(.*)*\1'
expr '' : ''
expr '' : ''
expr '' : ''
expr 'a' : '^a$'
expr 'abc' : 'abc'
expr 'xbc' : 'abc'
expr 'axc' : 'abc'
expr 'abx' : 'abc'
expr 'xabcy' : 'abc'
expr 'ababc' : 'abc'
expr 'abc' : 'ab*c'
expr 'abc' : 'ab*bc'
expr 'abbc' : 'ab*bc'
expr 'abbbbc' : 'ab*bc'
expr 'abbc' : 'ab+bc'
expr 'abc' : 'ab+bc'
expr 'abq' : 'ab+bc'
expr 'abbbbc' : 'ab+bc'
expr 'abbc' : 'ab?bc'
expr 'abc' : 'ab?bc'
expr 'abbbbc' : 'ab?bc'
expr 'abc' : 'ab?c'
expr 'abc' : '^abc$'
expr 'abcc' : '^abc$'
expr 'abcc' : '^abc'
expr 'aabc' : '^abc$'
expr 'aabc' : 'abc$'
expr 'abc' : '^'
expr 'abc' : '$'
expr 'abc' : 'a.c'
expr 'axc' : 'a.c'
expr 'axyzc' : 'a.*c'
expr 'axyzd' : 'a.*c'
expr 'abc' : 'a[bc]d'
expr 'abd' : 'a[bc]d'
expr 'abd' : 'a[b-d]e'
expr 'ace' : 'a[b-d]e'
expr 'aac' : 'a[b-d]'
expr 'a-' : 'a[-b]'
expr 'a-' : 'a[b-]'
expr '-' : 'a[b-a]'
expr '-' : 'a[]b'
expr '-' : 'a['
expr 'a]' : 'a]'
expr 'a]b' : 'a[]]b'
expr 'aed' : 'a[^bc]d'
expr 'abd' : 'a[^bc]d'
expr 'adc' : 'a[^-b]c'
expr 'a-c' : 'a[^-b]c'
expr 'a]c' : 'a[^]b]c'
expr 'adc' : 'a[^]b]c'
expr 'abc' : 'ab\|cd'
expr 'abcd' : 'ab\|cd'
expr 'def' : '()ef'
expr '-' : '()*'
expr '-' : '*a'
expr '-' : '^*'
expr '-' : '$*'
expr '-' : '(*)b'
expr 'b' : '$b'
expr '-' : 'a\'
expr 'a(b' : 'a\(b'
expr 'ab' : 'a\(*b'
expr 'a((b' : 'a\(*b'
expr 'a\x' : 'a\x'
expr '-' : 'abc)'
expr '-' : '(abc'
expr 'abc' : '((a))'
expr 'abc' : '(a)b(c)'
expr 'aabbabc' : 'a+b+c'
expr '-' : 'a**'
expr '-' : 'a*?'
expr '-' : '(a*)*'
expr '-' : '(a*)+'
expr '-' : '(a\|)*'
expr '-' : '(a*\|b)*'
expr 'ab' : '(a+\|b)*'
expr 'ab' : '(a+\|b)+'
expr 'ab' : '(a+\|b)?'
expr 'cde' : '[^ab]*'
expr '-' : '(^)*'
expr '-' : '(ab\|)*'
expr '-' : ')('
expr '"' : 'a'
expr '"' : 'a'
expr '"' : 'a'
expr 'abbbcd' : '([abc])*d'
expr 'abcd' : '([abc])*bcd'
expr 'e' : 'a\|b\|c\|d\|e'
expr 'ef' : '(a\|b\|c\|d\|e)f'
expr '-' : '((a*\|b))*'
expr 'abcdefg' : 'abcd*efg'
expr 'xabyabbbz' : 'ab*'
expr 'xayabbbz' : 'ab*'
expr 'abcde' : '(ab\|cd)e'
expr 'hij' : '[abhgefdc]ij'
expr 'abcde' : '^(ab\|cd)e'
expr 'abcdef' : '(abc\|)ef'
expr 'abcd' : '(a\|b)c*d'
expr 'abc' : '(ab\|ab*)bc'
expr 'abc' : 'a([bc]*)c*'
expr 'abcd' : 'a([bc]*)(c*d)'
expr 'abcd' : 'a([bc]+)(c*d)'
expr 'abcd' : 'a([bc]*)(c+d)'
expr 'adcdcde' : 'a[bcd]*dcdcde'
expr 'adcdcde' : 'a[bcd]+dcdcde'
expr 'abc' : '(ab\|a)b*c'
expr 'abcd' : '((a)(b)c)(d)'
expr 'alpha' : '[A-Za-z_][A-Za-z0-9_]*'
expr 'abh' : '^a(bc+\|b[eh])g\|.h$'
expr 'effgz' : '(bc+d$\|ef*g.\|h?i(j\|k))'
expr 'ij' : '(bc+d$\|ef*g.\|h?i(j\|k))'
expr 'effg' : '(bc+d$\|ef*g.\|h?i(j\|k))'
expr 'bcdd' : '(bc+d$\|ef*g.\|h?i(j\|k))'
expr 'reffgz' : '(bc+d$\|ef*g.\|h?i(j\|k))'
expr '-' : '((((((((((a))))))))))'
expr 'a' : '(((((((((a)))))))))'
expr 'uh-uh' : 'multiple words of text'
expr 'multiple words, yeah' : 'multiple words'
expr 'abcde' : '(.*)c(.*)'
expr '(.*)\)' : '\((.*),'
expr 'ab' : '[k]'
expr 'abcd' : 'abcd'
expr 'abcd' : 'a(bc)d'
expr 'ac' : 'a[-]?c'
expr 'beriberi' : '(....).*\1'
expr 'Muammar Qaddafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Mo'\''ammar Gadhafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Muammar Kaddafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Muammar Qadhafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Moammar El Kadhafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Muammar Gadafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Mu'\''ammar al-Qadafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Moamer El Kazzafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Moamar al-Gaddafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Mu'\''ammar Al Qathafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Muammar Al Qathafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Mo'\''ammar el-Gadhafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Moamar El Kadhafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Muammar al-Qadhafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Mu'\''ammar al-Qadhdhafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Mu'\''ammar Qadafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Moamar Gaddafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Mu'\''ammar Qadhdhafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Muammar Khaddafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Muammar al-Khaddafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Mu'\''amar al-Kadafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Muammar Ghaddafy' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Muammar Ghadafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Muammar Ghaddafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Muamar Kaddafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Muammar Quathafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Muammar Gheddafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Muamar Al-Kaddafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Moammar Khadafy ' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Moammar Qudhafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Mu'\''ammar al-Qaddafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
expr 'Mulazim Awwal Mu'\''ammar Muhammad Abu Minyar al-Qadhafi' : 'M[ou]'\''?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]'
