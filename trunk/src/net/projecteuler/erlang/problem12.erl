%% File:   problem12.erl
%% Author: Brian Detweiler

-module(problem12).
-export([main/0]).
-export([triangle/1]).
-export([seive/1]).
-export([seive/4]).
-export([factor/1]).
-export([factor/3]).
-export([divisors/1]).
-export([multiply/2]).
%%-export([divisors/1]).

%% Self-contained main
main() -> 

    % Numbers =  lists:seq(1, 10),

    io:format("~s~n", ["Triangling..."]),
    %% multiply(2, [2, 2, 3]).

       divisors(192).

    %%lists:foreach(fun(Number) -> io:format("~p~n", [Number]) end, seive(2000000)).

    %% list_primes(3).

    %% is_prime([2], 3).
    %% divisors(triangle(4)).

%% 1 = 1: 1
%% 2 = 3: 1,3
%% 3 = 6: 1,2,3,6
%% 4 = 10: 1,2,5,10
%% 5 = 15: 1,3,5,15
%% 6 = 21: 1,3,7,21
%% 7 = 28: 1,2,4,7,14,28


%% Get the Nth triangle number
triangle(0) -> 0;
triangle(N) ->
    N + triangle(N - 1).

%% Stolen from http://stackoverflow.com/questions/146622/sieve-of-eratosthenes-in-erlang 
seive(Prime, Max, Primes, Integers) when Prime > Max ->
    lists:reverse([Prime|Primes]) ++ Integers;
seive(Prime, Max, Primes, Integers) ->
    [NewPrime|NewIntegers] = [ X || X <- Integers, X rem Prime =/= 0 ],
    seive(NewPrime, Max, [Prime|Primes], NewIntegers).

seive(N) ->
    seive(2, round(math:sqrt(N)), [], lists:seq(3, N, 2)). % skip odds


% Return FD ++ Factors, where FD is the prime factors of N >= the test
% divisor D.
factor(1) ->
    1;
factor(N) when is_integer(N), N > 1 ->
    factor(N, 2, []).

factor(N, D, Factors) ->
    if
        N < D * D -> 
            [N|Factors];
        0 =:= N rem D -> 
            factor(N div D, D, [D|Factors]);
        true -> 
            factor(N, D + 1, Factors)
    end.


divisors(N) -> 
    List = lists:reverse(factor(N)),
    Divisors = [1] ++ List ++ [N],
    gb_sets:to_list(gb_sets:from_list(lists:flatten(Divisors))).

%% divisors(Divisors, [First | Rest]) ->
    

multiply(_, []) ->
    [];
multiply(Multiplier, [First | Rest]) ->
    lists:flatten([Multiplier * First, multiply(Multiplier, Rest)]).


%List = [1, 2, 3, 2, 2, 4, 5, 5, 4, 6, 6, 5].
% UniqueList = gb_sets:to_list(gb_sets:from_list(List)).
   
