%% File:   problem48.erl
%% Author: Brian Detweiler

-module(problem48).
-export([example/0]).
-export([addPowers/2]).
-export([addPowers/3]).
-export([powr/2]).

%% Self-contained example
example() -> 

    Numbers =  lists:seq(1, 1000),
    
    io:format("~s~n", ["Adding..."]),

    addPowers(0, Numbers).

addPowers(Sum, []) ->
    Sum;
addPowers(Sum, [First | Rest]) ->
    addPowers(Sum, powr(First, First), Rest).

addPowers(Sum, Power, List) ->
    addPowers(Sum + Power, List).

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
