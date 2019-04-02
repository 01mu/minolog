/*
* minolog
* github.com/01mu
*/

#include <iostream>
#include "lib/ml.cpp"

int main()
{
    clock_t t_start;

    double reset_t;

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

        reset_t = ((double) (clock() - reset_start) / CLOCKS_PER_SEC);

        if(ifstream("minolog_settings"))
        {
            open_settings_file();
        }
        else
        {
            new_settings_file();
        }

        if(ifstream("minolog_replays"))
        {
            open_replay_file();
            write_new_replays();
        }
        else
        {
            new_replay_file();
        }

        set_stats();
        set_display_limits();

        display_header();
        display_stats();

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
