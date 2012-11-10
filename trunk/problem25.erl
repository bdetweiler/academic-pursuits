%% File:   problem25.erl
%% Author: Brian Detweiler

-module(problem25).
-export([example/0]).
-export([fib/1]).
-export([powr/2]).

%% Self-contained example
example() -> 
    
    N = 1000,
    powr(2, 99).
    %% (1 / math:sqrt(5)) * (powr(((1 + trunc(math:sqrt(5))) / 2), N) - powr(((1 - trunc(math:sqrt(5))) / 2), N)).

fib(0) -> 1;
fib(1) -> 1;
fib(N) -> fib(N - 1) + fib(N - 2).


powr(N, P) ->
    if P /= 0 ->
        if P > 0 ->
            N * powr(N, P - 1);
        true ->
            1 / powr(N, -1 * P)
        end;
    true ->
        1
    end.
