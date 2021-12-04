readtable =: 3 : '>0 ". each cutopen toJ 1!:1 y'

ex01_example =: 199 200 208 210 200 207 240 269 260 263
ex01_input =: readtable (< '../input/01')

ex01a =: +/@(_1&}. < }.)
ex01b =: +/@(_3&}. < 3&}.)

ex01 =: (ex01a ex01_input);(ex01b ex01_input)

