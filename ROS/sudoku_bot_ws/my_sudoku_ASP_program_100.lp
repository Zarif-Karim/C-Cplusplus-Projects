x(1..100).
y(1..100).
n(1..100).

{gridNumSol(X,Y,N): n(N)}=1 :- x(X) ,y(Y).

subgrid(X,Y,A,B) :- x(X), x(A), y(Y), y(B),(X-1)/10 == (A-1)/10, (Y-1)/10 == (B-1)/10.

:- gridNumSol(X,Y,N), gridNumSol(A,Y,N), X!=A.
:- gridNumSol(X,Y,N), gridNumSol(X,B,N), Y!=B.
:- gridNumSol(X,Y,V), gridNumSol(A,B,V), subgrid(X,Y,A,B), X != A, Y != B.

#show gridNumSol/3.