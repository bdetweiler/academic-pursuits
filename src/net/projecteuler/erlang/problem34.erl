%% File:   problem20.erl
%% Author: Brian Detweiler

-module(problem34).
-export([example/0]).
-export([factorial/2]).

%% Self-contained example
example() -> 

    Numbers = lists:seq(1, 4),

    io:format("~s~n", ["factorial-ing..."]),
    factorial(1, Numbers).

factorial(CurNum, []) -> CurNum;
factorial(CurNum, [First | Rest]) -> factorial(CurNum * First, Rest).
