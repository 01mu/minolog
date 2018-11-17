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
    cout.setf(std::ios::fixed, std::ios::floatfield);
    cout << setiosflags(ios::left);

    clock_t reset_start = clock();

    while(1)
    {
        replay_names = get_replay_names();

        clock_t tStart = clock();

        cout << "------------------------" << endl
            << "NullpoMino Replay Logger" << endl
            << "Version 1.0" << endl
            << "------------------------" << endl << endl;

        int old_day_iter = 0;
        int month_iter = 0;
        int today_iter = 0;
        int per_n_iter = 0;
        int per_n_set = 0;
        int pb_iter = 0;
        int fin_iter = 0;

        double end;
        double reset_t = ((double) (clock() - reset_start) / CLOCKS_PER_SEC);

        make_settings_file();
        make_replays_file();

        for(unsigned int j = 0; j < replays.size(); j++)
        {
            all_frames_sum += replays[j].frames;
            num_all++;

            int goal = replays[j].goal_type;
            int lines = replays[j].n_lines;
            bool is_big = replays[j].big;
            string mode = replays[j].mode;

            if(goal == TYPE40 && lines >= 40 && !is_big &&  mode == LINE_RACE)
            {
                num_40++;

                update_piece_counts(j);

                set_month_history(j, month_iter);
                set_old_day_history(j, old_day_iter);
                set_today_history(j, today_iter);
                set_per_n_history(j, per_n_set, per_n_iter);
                set_pb_history(j, pb_iter);
                set_fin_pb_history(j, fin_iter);
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

        end = ((double) (clock() - tStart) / CLOCKS_PER_SEC);

        cout << endl << endl << end << " seconds";
        tStart = 0;

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

            continue;
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
