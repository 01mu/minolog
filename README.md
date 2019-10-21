# minolog
## Features
* Display personal bests, daily history, monthly history, and history per N games for [NullpoMino](https://github.com/nullpomino/nullpomino) replays.
* Export replay info to a JSON file.
* Historical graphs (Python and matplotlib required).
## Usage
### Commands
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
* `graph-pern`: display per n graph (See below)
* `auto`: enable automatic updating
### Time per 1000 replays in seconds (aggregated)
![Alt text](https://raw.githubusercontent.com/01mu/minolog/master/Figure_1.png "Title")
## Install
### Linux
Build with `g++ -o ml src/minolog.cpp -Ofast` and move `ml` to NullpoMino's replay folder.
### Windows
Run minolog.exe from your replays folder. The program will parse the .rep files in the same directory and write extracted data to replays.txt. Subsequent executions of minolog.exe will append this file with new .rep file data. Type cmds for display limit, json, and graph commands.
