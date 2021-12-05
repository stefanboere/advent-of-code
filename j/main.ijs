readtable =: 3 : '>0 ". each cutopen toJ 1!:1 y'

ex01_example =: 199 200 208 210 200 207 240 269 260 263
ex01_input =: readtable (< '../input/01')

ex01a =: +/@(_1&}. < }.)
ex01b =: +/@(_3&}. < 3&}.)

ex01 =: (ex01a ex01_input);(ex01b ex01_input)

readtab =: 3 : 'cutopen each cutopen toJ 1!:1 y'

ex02_input =: readtab (< '../input/02')

ex02a_diff =: monad : 0
x=.".>}.>y
select. >{.>y
case. 'forward' do. 0, x
case. 'up' do. - x, 0
case. 'down' do. x, 0
end.
)

ex02b_diff =: dyad : 0
({.y + |.(y*x)),}.y+(|.x)
)

ex02_i =: >(ex02a_diff each ex02_input)
ex02a =: */+/ex02_i

ex02b =: ({.ex02b_diff/|.0 0,ex02_i) * (}.+/ex02_i)
ex02 =: ex02a,ex02b
