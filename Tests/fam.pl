male(bill).
male(sam).
male(peter).
male(jordan).
male(rob).

female(marry).
female(sarah).
female(christy).
female(val).
female(hillary).

parent(bill, sam).
parent(bill, peter).
parent(marry, jordan).
parent(marry, rob).

is_father(F) :- male(F), parent(F,_).
is_mother(M) :- female(M), parent(M,_).

siblings(A, B) :- parent(P, A), parent(P, B).
cousins(A, B) :- parent(P1, A), parent(P2, B), siblings(P1, P2).


