%% File:   problem97.erl
%% Author: Brian Detweiler

-module(problem97).
-export([example/0]).
-export([getPowersOfTwo/1]).
-export([isPowerOfTwo/1]).
-export([addPowers/2]).
-export([addPowers/3]).
-export([powr/2]).

%% Self-contained example
example() -> 

    Numbers =  lists:seq(1, 8),
    
    io:format("~s~n", ["Executing..."]),

    getPowersOfTwo(Numbers).



    %% addPowers(0, Numbers).

getPowersOfTwo([]) ->
    0;
getPowersOfTwo([First | Rest]) ->
    if((First band (First - 1))) ->
        io:format("~c~s~n", [First, "is a power of two..."]),
        getPowersOfTwo(Rest);
    true ->
        getPowersOfTwo(Rest)
    end.
        
    

isPowerOfTwo(X) ->
    (X band (X - 1)).
        


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



