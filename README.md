# minolog
**Features**
- Display personal bests, daily history, monthly history, and history per N games for [NullpoMino](https://github.com/nullpomino/nullpomino) replays.
- Export replay info to a JSON file.
- Historical charts (Python and matplotlib required).

**Program output**
```
------------------------
NullpoMino Replay Logger
Version 1.0
------------------------

--- Total Statistics ---                     --- 40 Lines Race Statistics ---
Time played: 486:53:53.72                    Time played: 383:09:31.97
Average time: 00:41.91                       Average time: 00:45.80
# of replays: 41828                          # of replays: 30118

Oldest: Feb. 21, 2015                        < 102 pieces dropped: 1590 (5.279%)
Recent: Jun. 21, 2018                        = 102 pieces dropped: 5255 (17.448%)
                                             = 103 pieces dropped: 5630 (18.693%)
                                             > 103 pieces dropped: 17643 (58.580%)

--- 40 Lines Race personal best history (51) ---
Time      PPS     Pieces  Finesse  Holds  Name                     Improvement
00:32.10  3.1481  102     16       2      2018_05_15_22_23_51.rep  -1.133
00:33.23  3.0406  102     0        5      2018_02_28_00_13_14.rep  -0.033
00:33.27  3.0075  101     0        1      2018_02_17_23_59_48.rep  -0.033
00:33.30  3.0646  103     24       0      2017_09_12_16_03_57.rep  -0.067
00:33.37  2.9985  101     23       0      2017_02_20_15_57_44.rep  -2.167
00:35.53  2.8437  102     49       0      2017_01_19_19_30_05.rep  -0.017
00:35.55  2.8143  101     26       3      2016_12_17_17_41_39.rep  -0.017
00:35.57  2.8129  101     27       0      2016_12_06_01_28_07.rep  -0.667
00:36.23  2.7888  102     36       3      2016_11_19_19_05_22.rep  -0.250
00:36.48  2.7422  101     31       0      2016_10_12_12_37_26.rep  -0.667

--- Finesse personal best history (21) ---
Time      PPS     Pieces  Finesse  Holds  Name                     Improvement
00:35.52  2.8451  102     16       0      2017_03_10_17_16_49.rep  -1.000
00:36.68  2.7545  102     17       0      2016_12_02_14_42_52.rep  -2.000
00:39.17  2.6054  103     19       1      2016_11_08_20_56_26.rep  -3.000
00:39.23  2.6009  103     22       2      2016_11_08_15_51_33.rep  -1.000
00:37.62  2.6862  102     23       0      2016_09_05_21_13_43.rep  -1.000
00:41.15  2.4554  102     24       1      2016_04_27_22_08_12.rep  -7.000
00:42.60  2.3718  102     31       3      2016_03_09_19_13_48.rep  -3.000
00:49.75  2.0710  104     34       11     2015_11_24_18_16_22.rep  -12.000
00:54.82  1.8431  102     46       11     2015_11_16_19_03_30.rep  -1.000
00:55.58  1.8716  105     47       13     2015_11_15_10_13_45.rep  -1.000

--- Statistics per 1000 completed 40 Lines Race replays (31) ---
Time      PPS     Pieces  Finesse  Holds  End date         To #    Difference
00:39.71  2.6339  105.26  43.84    4.86   Jun. 21, 2018    30118   -0.033
00:39.75  2.6289  105.09  41.78    4.00   Jun. 14, 2018    30000   -0.598
00:40.34  2.5805  104.78  24.74    4.77   May. 05, 2018    29000   +0.433
00:39.91  2.6099  104.81  0.00     4.29   Mar. 29, 2018    28000   -0.182
00:40.09  2.5977  104.79  26.45    4.14   Feb. 05, 2018    27000   -0.434
00:40.53  2.5709  104.84  41.49    4.34   Nov. 26, 2017    26000   +0.322
00:40.20  2.5848  104.61  41.41    3.97   Sep. 23, 2017    25000   +0.370
00:39.83  2.6051  104.47  41.59    3.57   Jul. 21, 2017    24000   -0.225
00:40.06  2.6000  104.86  44.31    2.85   Jun. 18, 2017    23000   -0.789
00:40.85  2.5499  104.86  46.03    3.04   Apr. 27, 2017    22000   +0.044

--- Monthly history of completed 40 Lines Race replays (39) ---
Time      PPS     Pieces  Finesse  Holds  Month      #     #/d     Difference
00:39.78  2.6214  104.94  43.10    4.66   Jun. 2018  314   14.95   -0.034
00:39.82  2.6245  105.11  41.29    4.03   May. 2018  957   30.87   -0.513
00:40.33  2.5819  104.80  23.43    4.74   Apr. 2018  796   26.53   +0.450
00:39.88  2.6118  104.80  0.00     4.21   Mar. 2018  663   21.39   -0.182
00:40.06  2.5984  104.76  0.00     4.50   Feb. 2018  462   17.11   -0.168
00:40.23  2.5828  104.60  5.46     4.05   Jan. 2018  367   14.68   +0.245
00:39.99  2.6100  104.98  43.52    4.04   Dec. 2017  436   15.03   -0.362
00:40.35  2.5798  104.73  42.35    4.54   Nov. 2017  645   21.50   -0.385
00:40.73  2.5587  104.88  40.82    4.14   Oct. 2017  373   13.81   +0.282
00:40.45  2.5762  104.86  41.93    4.33   Sep. 2017  459   15.83   +0.305

--- Daily history of completed 40 Lines Race replays (1053) ---
Time      PPS     Pieces  Finesse  Holds  Date             #       Difference
00:39.69  2.6544  106.00  46.55    3.95   Jun. 21, 2018    20      -0.762
00:40.46  2.5745  104.68  44.64    5.32   Jun. 20, 2018    25      +0.107
00:40.35  2.5712  104.67  35.33    6.00   Jun. 19, 2018    3       +0.736
00:39.61  2.5982  103.71  46.36    5.71   Jun. 18, 2018    14      -0.719
00:40.33  2.6125  105.88  44.63    5.25   Jun. 17, 2018    8       +0.753
00:39.58  2.6342  105.00  41.38    4.92   Jun. 16, 2018    13      +0.415
00:39.17  2.6834  105.90  41.90    4.60   Jun. 15, 2018    30      -0.029
00:39.19  2.6894  106.13  42.38    4.75   Jun. 14, 2018    16      -0.619
00:39.81  2.6470  105.92  45.67    5.92   Jun. 13, 2018    12      +0.184
00:39.63  2.6286  104.73  44.23    4.59   Jun. 12, 2018    22      -0.522

--- Today's completed 40 Lines Race replays (20) ---
Time      PPS     Pieces  Finesse  Holds  Name
00:37.82  2.6720  102     43       2      2018_06_21_20_43_26.rep
00:38.82  2.6804  105     38       11     2018_06_21_20_38_30.rep
00:37.33  2.7066  102     53       2      2018_06_21_20_37_34.rep
00:39.55  2.7066  108     51       1      2018_06_21_20_29_41.rep
00:39.08  2.6621  105     46       7      2018_06_21_20_23_12.rep
00:36.95  2.7617  103     40       0      2018_06_21_18_31_11.rep
00:38.55  2.7249  106     42       8      2018_06_21_18_29_11.rep
00:37.48  2.6957  102     38       1      2018_06_21_18_28_25.rep
00:41.98  2.5258  107     42       5      2018_06_21_18_27_22.rep
00:38.95  2.6969  106     44       3      2018_06_21_18_26_21.rep

0.59 seconds
Press 'ENTER' to update. Type 'cmds' for commands.
```

**Time per 1000 replays in seconds (aggregated)**
![Alt text](https://raw.githubusercontent.com/01mu/minolog/master/Figure_1.png "Title")

**Usage**
Run minolog.exe from your replays folder. The program will parse the .rep files in the same directory and write extracted data to replays.txt. Subsequent executions of minolog.exe will append this file with new .rep file data. 
