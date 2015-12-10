/*
    All work copied from, or inspired by, learnprolognow.org
*/

append([], L, L).
append([H|T], L2, [H|L3]) :- append(T, L2, L3).

accRev([H|T], A, R) :- accRev(T, [H|A], R).
accRev([], A, A).

rev(A, R) :- accRev(A, [], R).


