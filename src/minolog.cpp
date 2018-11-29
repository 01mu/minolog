/*
* minolog
* github.com/01mu
*/

#include <unistd.h>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iomanip>
#include <string>
#include <climits>
#include <sstream>

#ifdef _WIN32
#include "lib/dirent.h"
#endif

using namespace std;

#include "lib/ml.cpp"

int main()
{
    clock_t t_start;

    int old_day_iter;
    int month_iter;
    int today_iter;
    int per_n_iter;
    int per_n_set;
    int pb_iter;
    int fin_iter;

    int goal;
    int lines;
    bool is_big;
    string mode;

    rep cur_rep;

    double reset_t;
    double end;

    cout.setf(std::ios::fixed, std::ios::floatfield);
    cout << setiosflags(ios::left);

    clock_t reset_start = clock();

    while(1)
    {
        replay_names = get_replay_names();

        t_start = clock();

        cout << "------------------------" << endl
            << "NullpoMino Replay Logger" << endl
            << "Version 1.0" << endl
            << "------------------------" << endl << endl;

        old_day_iter = 0;
        month_iter = 0;
        today_iter = 0;
        per_n_iter = 0;
        per_n_set = 0;
        pb_iter = 0;
        fin_iter = 0;

        reset_t = ((double) (clock() - reset_start) / CLOCKS_PER_SEC);

        make_settings_file();
        make_replays_file();

        for(int i = 0; i < replays.size(); i++)
        {
            cur_rep = replays[i];

            all_frames_sum += cur_rep.frames;
            num_all++;

            goal = cur_rep.goal_type;
            lines = cur_rep.n_lines;
            is_big = cur_rep.big;
            mode = cur_rep.mode;

            if(goal == TYPE40 && lines >= 40 && !is_big && mode == LINE_RACE)
            {
                num_40++;

                update_piece_counts(i);

                set_month_history(i, month_iter);
                set_old_day_history(i, old_day_iter);
                set_today_history(i, today_iter);
                set_per_n_history(i, per_n_set, per_n_iter);
                set_pb_history(i, pb_iter);
                set_fin_pb_history(i, fin_iter);
            }
        }

        set_display_limits();

        display_header();

        output_pb_history(pb_to_show);
        output_fin_pb_history(fin_pb_to_show);
        output_per_n(per_n_count, per_n_to_show, num_40, hundred_count);
        output_month_history(month_to_show);
        output_old_day_history(old_day_to_show);
        output_today_history(today_to_show);

        end = ((double) (clock() - t_start) / CLOCKS_PER_SEC);

        cout << endl << endl << end << " seconds";

        t_start = 0;

        if(auto_update == 1)
        {
            cout << " -auto updating-" << endl;

            while(reset_t < (double) auto_time)
            {
                reset_t = ((double) (clock() - reset_start) / CLOCKS_PER_SEC);
            }

            reset();
            reset_start = clock();
            reset_t = 0;
        }
        else
        {
            cout << endl;
            take_input();
            reset();
        }
    }

    return 0;
}
