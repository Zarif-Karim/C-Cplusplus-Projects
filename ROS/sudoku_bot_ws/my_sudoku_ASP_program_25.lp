x(1..25).
y(1..25).
n(1..25).

{gridNumSol(X,Y,N): n(N)}=1 :- x(X) ,y(Y).

subgrid(X,Y,A,B) :- x(X), x(A), y(Y), y(B),(X-1)/5 == (A-1)/5, (Y-1)/5 == (B-1)/5.

:- gridNumSol(X,Y,N), gridNumSol(A,Y,N), X!=A.
:- gridNumSol(X,Y,N), gridNumSol(X,B,N), Y!=B.
:- gridNumSol(X,Y,V), gridNumSol(A,B,V), subgrid(X,Y,A,B), X != A, Y != B.

#show gridNumSol/3.