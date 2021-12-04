:- use_module(library(csv)).
:- use_module(library(clpfd)).

ex01_input(Xs) :- csv_read_file("../input/01", Rows, [functor(row), arity(1)]),
   maplist(unwrap, Rows, Xs).

unwrap(X,Y) :- X = row(Y).

ex01a([], 0).
ex01a([_], 0).
ex01a(Xs, Mask) :- Xs = [X0, X1 | XTail], X0 < X1, Mask #= 1 + Mask0, ex01a([X1 | XTail], Mask0).
ex01a(Xs, Mask) :- Xs = [_| XTail0], ex01a(XTail0, Mask).


ex01b([], 0).
ex01b([_], 0).
ex01b([_,_], 0).
ex01b([_,_,_], 0).
ex01b(Xs, Mask) :- Xs = [X0, X1, X2, X3 | XTail], X0 < X3, Mask #= 1 + Mask0, ex01b([X1, X2, X3 | XTail], Mask0).
ex01b(Xs, Mask) :- Xs = [_| XTail0], ex01b(XTail0, Mask).

ex01(C, D) :-
    % Rows = [199, 200, 208, 210, 200, 207, 240, 269, 260, 263],
    ex01_input(Rows),
    ex01a(Rows, C),
    ex01b(Rows, D).
