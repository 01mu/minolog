# minolog
## Features
* Display personal bests, daily history, monthly history, and history per N games for [NullpoMino](https://github.com/nullpomino/nullpomino) replays.
* Export replay info to a JSON file.
* Historical graphs (Python and matplotlib required).
## Output
```
------------------------
NullpoMino Replay Logger
Version 1.0
------------------------

--- Total Statistics ---                     --- 40 Lines Race Statistics ---
Time played: 549:02:29.40                    Time played: 434:31:07.10
Average time: 00:41.09                       Average time: 00:44.82
# of replays: 48105                          # of replays: 34903

Oldest: Feb. 21, 2015                        < 102 pieces: 1834 (5.255%)
Recent: Dec. 16, 2018                        = 102 pieces: 6024 (17.259%)
                                             = 103 pieces: 6537 (18.729%)
                                             > 103 pieces: 20508 (58.757%)

--- 40 Lines Race personal best history (53) ---
Time      PPS     Pieces  Finesse  Holds  Name                     Improvement
00:29.90  3.3463  101     0        0      2018_07_29_17_16_53.rep  -2.100
00:32.00  3.1579  102     0        1      2018_07_29_17_15_34.rep  -0.100
00:32.10  3.1481  102     16       2      2018_05_15_22_23_51.rep  -1.133

--- Finesse personal best history (21) ---
Time      PPS     Pieces  Finesse  Holds  Name                     Improvement
00:35.52  2.8451  102     16       0      2017_03_10_17_16_49.rep  -1.000
00:36.68  2.7545  102     17       0      2016_12_02_14_42_52.rep  -2.000
00:39.17  2.6054  103     19       1      2016_11_08_20_56_26.rep  -3.000

--- Statistics per 250 completed 40 Lines Race replays (140) ---
Time      PPS     Pieces  Finesse  Holds  End date         To #    Difference
00:37.68  2.7882  105.67  0.00     3.22   Dec. 16, 2018    34903   -0.306
00:37.99  2.7693  105.75  0.00     5.24   Dec. 10, 2018    34750   -0.984
00:38.97  2.7151  106.23  0.00     4.69   Nov. 30, 2018    34500   +0.493

--- Monthly history of completed 40 Lines Race replays (45) ---
Time      PPS     Pieces  Finesse  Holds  Month      #     #/d     Difference
00:37.87  2.7765  105.72  0.00     4.47   Dec. 2018  403   25.19   -0.663
00:38.54  2.7259  105.61  0.00     4.73   Nov. 2018  1543  51.43   +0.116
00:38.42  2.7277  105.39  0.00     4.40   Oct. 2018  1088  35.10   -0.599

--- Daily history of completed 40 Lines Race replays (1206) ---
Time      PPS     Pieces  Finesse  Holds  Date             #       Difference
00:37.13  2.7966  104.67  0.00     4.00   Dec. 16, 2018    6       -1.306
00:38.43  2.7417  106.05  0.00     4.29   Dec. 15, 2018    21      +0.675
00:37.76  2.7870  105.84  0.00     3.48   Dec. 14, 2018    50      -0.315

--- Today's completed 40 Lines Race replays (6) ---
Time      PPS     Pieces  Finesse  Holds  Name
00:37.85  2.6960  103     0        2      2018_12_16_19_59_05.rep
00:35.98  2.9750  108     0        0      2018_12_16_14_44_05.rep
00:35.73  2.9678  107     0        3      2018_12_16_14_43_08.rep

0.28 seconds
Press 'ENTER' to update. Type 'cmds' for commands.
```
## Commands
* `pern 'count'`: set per N count
* `perdts 'count'`: set per days to show
* `pernts 'count'`: set per Ns to show
* `pbs 'count'`: set PBs to show
* `today 'count'`: set today's replays to show
* `old 'count'`: set old day's replays to show
* `month 'count'`: set monthly replays to show
* `finpb 'count'`: set finesse PBs to show
* `autoset 'seconds'`: set automatic update time
* `json`: make json file
* `graph-today`: display today graph
* `graph-pbs`: display pb graph
* `graph-pern`: display per n graph
* `auto`: enable automatic updating
## Time per 1000 replays in seconds (aggregated)
![Alt text](https://raw.githubusercontent.com/01mu/minolog/master/Figure_1.png "Title")
## Usage
### Linux
Build with `g++ -o ml src/minolog.cpp -Ofast` and move `ml` to NullpoMino's replay folder.
### Windows
Run minolog.exe from your replays folder. The program will parse the .rep files in the same directory and write extracted data to replays.txt. Subsequent executions of minolog.exe will append this file with new .rep file data. Type cmds for display limit, json, and graph commands.
