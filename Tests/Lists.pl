/*
    All work copied from, or inspired by, learnprolognow.org
*/

append([], L, L).
append([H|T], L2, [H|L3]) :- append(T, L2, L3).

accRev([H|T], A, R) :- accRev(T, [H|A], R).
accRev([], A, A).

rev(A, R) :- accRev(A, [], R).

query(A) :- rev([a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w]).


