/*
* minolog
* github.com/01mu
*/

#include <iostream>
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

        cout << "----------------------------" << endl
            << "- minolog                  -" << endl
            << "- NullpoMino Replay Logger -" << endl
            << "----------------------------" << endl << endl;

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
                per_n_set++;

                update_piece_counts(i);

                if(set_month_history(i, month_iter))
                {
                    month_iter++;
                }

                if(set_old_day_history(i, old_day_iter))
                {
                    old_day_iter++;
                }

                if(set_today_history(i, today_iter))
                {
                    today_iter++;
                }

                if(set_per_n_history(i, per_n_set, per_n_iter))
                {
                    per_n_set = 0;
                    per_n_iter++;
                }

                if(set_pb_history(i, pb_iter))
                {
                    pb_iter++;
                }

                if(set_fin_pb_history(i, fin_iter))
                {
                    fin_iter++;
                }
            }
        }

        set_display_limits();
        display_header();

        if(bests.size() > 0)
        {
            output_pb_history();
        }

        if(finesse_bests.size() > 0)
        {
            output_fin_pb_history();
        }

        output_per_n();

        if(monthies.size() > 0)
        {
            output_month_history();
        }

        if(oldies.size() > 0)
        {
            output_old_day_history();
        }

        if(todaies.size() > 0)
        {
            output_today_history();
        }

        if(auto_update)
        {
            cout << endl << endl << "-auto updating-" << endl;

            while(reset_t < (double) auto_time)
            {
                reset_t = ((double) (clock() - reset_start) / CLOCKS_PER_SEC);
            }

            reset_start = clock();
            reset_t = 0;
        }
        else
        {
            cout << endl << endl;
            cout << "Press 'ENTER' to update. Type 'cmds' for commands.";
            cout << endl;

            take_input();
        }

        reset();
    }

    return 0;
}
