%% File:   tic_tac_toe.erl
%% Author: Brian Detweiler

-module(problem11).
-export([example/0]).
-export([mod/2]).
-export([print_board/1]).
-export([print_board/2]).
-export([find_winner/1]).
-export([moves_left/1]).
-export([rows/1]).
-export([rows/2]).
-export([cols/1]).
-export([cols/3]).
-export([diag/1]).
-export([diag/3]).
-export([list_len/1]).
-export([is_winrar/2]).
-export([build_column/2]).
-export([build_column/5]).
-export([build_diag_left/1]).
-export([build_diag_left/5]).
-export([build_diag_right/1]).
-export([build_diag_right/5]).



%% Self contained example
example() ->
    %% X wins by row
    Board0 = [8,  2,  22, 97, 38, 15, 0,  40, 0,  75, 4,  5,  7,  78, 52, 12, 50, 77, 91, 8,
              49, 49, 99, 40, 17, 81, 18, 57, 60, 87, 17, 40, 98, 43, 69, 48, 4,  56, 62, 0,
              81, 49, 31, 73, 55, 79, 14, 29, 93, 71, 40, 67, 53, 88, 30, 3,  49, 13, 36, 65,
              52, 70, 95, 23, 4,  60, 11, 42, 69, 24, 68, 56, 1,  32, 56, 71, 37, 2,  36, 91,
              22, 31, 16, 71, 51, 67, 63, 89, 41, 92, 36, 54, 22, 40, 40, 28, 66, 33, 13, 80,
              24, 47, 32, 60, 99, 3,  45, 2,  44, 75, 33, 53, 78, 36, 84, 20, 35, 17, 12, 50,
              32, 98, 81, 28, 64, 23, 67, 10, 26, 38, 40, 67, 59, 54, 70, 66, 18, 38, 64, 70,
              67, 26, 20, 68, 2,  62, 12, 20, 95, 63, 94, 39, 63, 8,  40, 91, 66, 49, 94, 21,
              24, 55, 58, 5,  66, 73, 99, 26, 97, 17, 78, 78, 96, 83, 14, 88, 34, 89, 63, 72,
              21, 36, 23, 9,  75, 0,  76, 44, 20, 45, 35, 14, 0,  61, 33, 97, 34, 31, 33, 95,
              78, 17, 53, 28, 22, 75, 31, 67, 15, 94, 3,  80, 4,  62, 16, 14, 9,  53, 56, 92,
              16, 39, 5,  42, 96, 35, 31, 47, 55, 58, 88, 24, 0,  17, 54, 24, 36, 29, 85, 57,
              86, 56, 0,  48, 35, 71, 89, 7,  5,  44, 44, 37, 44, 60, 21, 58, 51, 54, 17, 58,
              19, 80, 81, 68, 5,  94, 47, 69, 28, 73, 92, 13, 86, 52, 17, 77, 4,  89, 55, 40,
              4,  52, 8,  83, 97, 35, 99, 16, 7,  97, 57, 32, 16, 26, 26, 79, 33, 27, 98, 66,
              88, 36, 68, 87, 57, 62, 20, 72, 3,  46, 33, 67, 46, 55, 12, 32, 63, 93, 53, 69,
              4,  42, 16, 73, 38, 25, 39, 11, 24, 94, 72, 18, 8,  46, 29, 32, 40, 62, 76, 36,
              20, 69, 36, 41, 72, 30, 23, 88, 34, 62, 99, 69, 82, 67, 59, 85, 74, 4,  36, 16,
              20, 73, 35, 29, 78, 31, 90, 1,  74, 31, 49, 71, 48, 86, 81, 16, 23, 57, 5,  54,
              1,  70, 54, 71, 83, 51, 54, 69, 16, 92, 33, 48, 61, 43, 52, 1,  89, 19, 67, 48
             ],

    io:format("Game 0~n"),
    print_board(Board0).

print_board(Board) ->
    N = round(math:sqrt(list_len(Board))),
    print_board(Board, N).

print_board([], _) -> true;
print_board([First | Rest], N) ->
    Mod = mod(list_len(Rest), N),
    if Mod == 0 ->
        io:format("~10B ", [First]),
        io:format("~n");
    true ->
        if Mod == (N - 1) ->
            io:format("~10B", [First]);
        true ->
            io:format("~10B", [First])
        end
    end,
    print_board(Rest, N).


%% Judge, jury, and executioner
find_winner(List) ->
    WinRow = rows(List),
    WinCol = cols(List),
    WinDiag = diag(List),
    MovesLeft = moves_left(List),
    if WinRow == no_winner ->
        if WinCol == no_winner ->
            if WinDiag == no_winner ->
                if MovesLeft == 0 ->
                    cat;
                true ->
                    no_winner
                end;
            true ->
                WinDiag
            end;
        true ->
            WinCol
        end;
    true ->
        WinRow
    end.

%% Work through the rows of a board to see if there is a winner
rows(List, Largest) ->
    rows(List, round(math:sqrt(list_len(List))), Largest).
rows([], _) -> no_winner;
rows(List, Mod, Largest) -> 
    Winrar = is_winrar(lists:sublist(List, Mod), Largest),
    if Winrar ->
        lists:nth(1, List);
    true ->
        rows(lists:sublist(List, (Mod + 1), list_len(List) - (Mod - 1)), Mod)
    end.

%% Work through the columns of a board to see if there is a winner
cols(List) ->
    cols(List, 1, round(math:sqrt(list_len(List)))).
cols(List, Start, Mod, Largest) ->
    ColNum = mod(Start, (Mod + 1)),
    if ColNum == 0 ->
        no_winner;
    true ->
        Winrar = is_winrar(build_column(List, Start), Largest),
        if Winrar ->
            lists:nth(Start, List);
        true ->
            cols(List, (Start + 1), Mod)
        end
    end.
   

%% Initial element in column
build_column(List, Start) ->
    N = round(math:sqrt(list_len(List))),
    build_column(List, [], lists:nth(Start, List), Start, N).
%% Recursively build a column
build_column(List, Col, Element, CurrentPos, N) ->
    Size = list_len(List), 
    if (CurrentPos + N) > Size ->
        Col ++ [Element];
    true ->
        build_column(List, (Col ++ [Element]), lists:nth((N + CurrentPos), List), (N + CurrentPos), N)
    end.

%% Work through the columns of a board to see if there is a winner
diag(List) ->
    diag(List, 1, round(math:sqrt(list_len(List)))).
diag(List, Start, Mod, Largest) ->
    WinrarLeft = is_winrar(build_diag_left(List), Largest),
    if WinrarLeft ->
        lists:nth(Start, List);
    true ->
        WinrarRight = is_winrar(build_diag_right(List), Largest),
        if WinrarRight ->
            lists:nth(Mod, List);
        true ->
            no_winner
        end
    end.

%% Start at element 1, end at N
build_diag_left(List) ->
    N = round(math:sqrt(list_len(List))),
    build_diag_left(List, [], lists:nth(1, List), 1, N).
%% Recursively build a column
build_diag_left(List, Col, Element, CurrentPos, N) ->
    Size = list_len(List), 
    if (CurrentPos + N + 1) > Size ->
        Col ++ [Element];
    true ->
        build_diag_left(List, (Col ++ [Element]), lists:nth(N + 1 + CurrentPos, List), (N + 1 + CurrentPos), N)
    end.

%% top right element in diagonal
build_diag_right(List) ->
    N = round(math:sqrt(list_len(List))),
    build_diag_right(List, [], lists:nth(N, List), N, N).
%% Recursively build a column
build_diag_right(List, Col, Element, CurrentPos, N) ->
    Size = list_len(List), 
    if (CurrentPos + N) > Size ->
        Col ++ [Element];
    true ->
        build_diag_right(List, (Col ++ [Element]), lists:nth((N - 1 + CurrentPos), List), (N - 1 + CurrentPos), N)
    end.


%%%%%%%%%%%%%%%%%%%%%%%
%% Utility functions %%
%%%%%%%%%%%%%%%%%%%%%%%

%% Return the length of the list
list_len([]) -> 0;
list_len([_]) -> 1;
list_len([_ | Rest]) -> 1 + list_len(Rest).

mod(X, Y) when X > 0 -> X rem Y;
mod(X, Y) when X < 0 -> Y + X rem Y;
mod(0, _) -> 0.

moves_left(List) ->
    IsZ = fun(Z) -> Z == z end,
    ZList = lists:filter(IsZ, List),
    list_len(ZList).

%% Given a list, determine if all elements are the same (a winner)
is_winrar(List, Largest) ->
    IsX = fun(X) -> X == x end,
    IsO = fun(O) -> O == o end,
    XWin = lists:all(IsX, List),
    OWin = lists:all(IsO, List),

    if XWin ->
        true;
       OWin ->
        true;
    true ->
        false
    end.
