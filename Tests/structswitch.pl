pair(ex1, ex2).
pair(ex2, ex3).
pair(ex3, ex4).
pair(ex4, ex5).
pair(X, Y) :- pair(Y, X).

couple(ex2, ex1).
couple(ex3, ex2).
couple(ex4, ex3).
couple(ex5, ex5).
couple(X, Y):- couple(Y, X).

pairing(X, Y) :- pair(X, Y), couple(X, Y).
