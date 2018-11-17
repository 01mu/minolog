/*
* minolog
* github.com/01mu
*/

#include "ml.h"

double str_to_dec(string a)
{
    return strtod(a.erase(0, a.find_first_of("=") + 1).c_str(), NULL);
}

string to_int(int a)
{
    int num = a;
    string res = "";

    ostringstream temp;
    temp << num;

    return temp.str();
}

string to_float(double a)
{
    double num = a;
    string res = "";

    ostringstream temp;
    temp << fixed << setprecision(3) << num;

    return temp.str();
}

string num_to_month(string a)
{
    string month;

    if(a == "01")
    {
        month = "Jan.";
    }
    else if(a == "02")
    {
        month = "Feb.";
    }
    else if(a == "03")
    {
        month = "Mar.";
    }
    else if(a == "04")
    {
        month = "Apr.";
    }
    else if(a == "05")
    {
        month = "May.";
    }
    else if(a == "06")
    {
        month = "Jun.";
    }
    else if(a == "07")
    {
        month = "Jul.";
    }
    else if(a == "08")
    {
        month = "Aug.";
    }
    else if(a == "09")
    {
        month = "Sep.";
    }
    else if(a == "10")
    {
        month = "Oct.";
    }
    else if(a == "11")
    {
        month = "Nov.";
    }
    else if(a == "12")
    {
        month = "Dec.";
    }

    return month;
}

string month_date(string a)
{
    return num_to_month(a.substr(5, 2)) +
        " " + a.substr(8, 2) + ", "
        + a.substr(0, 4);
}

string output_time(double n)
{
    char buffer[256] = "", buffer2[256] = "";
    int hours = 0, minutes = 0;
    double seconds = n / 60;

    while(seconds >= 60)
    {
        minutes++;
        seconds -= 60;
    }

    while(minutes >= 60)
    {
        hours++;
        minutes -= 60;
    }

    if(hours > 0)
    {
        sprintf(buffer, "%i:", hours);
    }

    strncat(buffer, buffer2, 256);

    if(minutes >= 10)
    {
        sprintf(buffer2, "%i:", minutes);
    }
    else
    {
        sprintf(buffer2, "0%i:", minutes);
    }

    strncat(buffer, buffer2, 256);

    if(seconds >= 10)
    {
        sprintf(buffer2, "%.2f", seconds);
    }
    else
    {
        sprintf(buffer2, "0%.2f", seconds);
    }

    strncat(buffer, buffer2, 256);

    return buffer;
}

string convert_date()
{
    time_t t = time(0);

    struct tm *now = localtime(&t);
    char buffer[256], buffer2[256];

    sprintf(buffer, "%i/",(now->tm_year + 1900));

    if((now->tm_mon + 1) > 9)
    {
        sprintf(buffer2, "%i/",(now->tm_mon + 1));
    }
    else
    {
        sprintf(buffer2, "0%i/",(now->tm_mon + 1));
    }

    strncat(buffer, buffer2, 256);

    if((now->tm_mday) > 9)
    {
        sprintf(buffer2, "%i",(now->tm_mday));
    }
    else
    {
        sprintf(buffer2, "0%i",(now->tm_mday));
    }

    strncat(buffer, buffer2, 256);

    return buffer;
}

vector<string> get_replay_names()
{
    #ifdef _WIN32
    char buffer[MAX_PATH];

    GetModuleFileName(NULL, buffer, MAX_PATH);
    string::size_type pos = string(buffer).find_last_of("\\/");

    string path = string(buffer).substr(0, pos);
    #endif

    #ifdef linux
    char buffer[255];
    getcwd(buffer, sizeof(buffer));

    string path = string(buffer) + "/";
    #endif

    vector<string> vector;

    DIR *dir;
    struct dirent *ent;

    if((dir = opendir(path.c_str())) != NULL)
    {
        while((ent = readdir(dir)) != NULL)
        {
            int len = (strlen(ent->d_name));

            #ifdef _WIN32
            if ((strlen(ent->d_name)) > 3 &&
                !strcmp(ent->d_name + strlen(ent->d_name) - 4, ".rep"))
            {
                vector.push_back(ent->d_name);
            }
            #endif

            #ifdef linux
            if(len > 3 && !strcmp(ent->d_name + len - 4, ".rep"))
            {
                vector.push_back(ent->d_name);
            }
            #endif
        }

        closedir(dir);
    }
    else
    {
        perror("");
    }

    return vector;
}

void check_for_stat(string to_string, rep & temp)
{
    if(to_string.compare(0, 17, "0.statistics.pps=") == 0)
    {
        temp.pieces_per_second = str_to_dec(to_string);
    }
    else if(to_string.compare(0, 28, "0.statistics.totalPieceMove=") == 0)
    {
        temp.n_piece_move = (int) str_to_dec(to_string);
    }
    else if(to_string.compare(0, 30, "0.statistics.totalPieceLocked=") == 0)
    {
        temp.n_piece_locked = (int) str_to_dec(to_string);
    }
    else if(to_string.compare(0, 24, "0.statistics.totalSingle") == 0)
    {
        temp.n_single = (int) str_to_dec(to_string);
    }
    else if(to_string.compare(0, 24, "0.statistics.totalDouble") == 0)
    {
        temp.n_double = (int) str_to_dec(to_string);
    }
    else if(to_string.compare(0, 24, "0.statistics.totalTriple") == 0)
    {
        temp.n_triple = (int) str_to_dec(to_string);
    }
    else if(to_string.compare(0, 22, "0.statistics.totalFour") == 0)
    {
        temp.n_four = (int) str_to_dec(to_string);
    }
    else if(to_string.compare(0, 17, "result.totallines") == 0)
    {
        temp.n_lines = (int) str_to_dec(to_string);
    }
    else if(to_string.compare(0, 21, "0.statistics.finesse=") == 0)
    {
        temp.finesse = (int) str_to_dec(to_string);
    }
    else if(to_string.compare(0, 14, "timestamp.gmt=") == 0)
    {
        temp.timestamp = to_string.erase(0,
            to_string.find_first_of("=") + 1).c_str();
    }
    else if(to_string.compare(0, 17, "0.statistics.kpt=") == 0)
    {
        temp.kpt = str_to_dec(to_string);
    }
    else if(to_string.compare(0, 17, "0.statistics.lpm=") == 0)
    {
        temp.lines_per_minute = str_to_dec(to_string);
    }
    else if(to_string.compare(0, 17, "0.statistics.ppm=") == 0)
    {
        temp.pieces_per_minute = str_to_dec(to_string);
    }
    else if(to_string.compare(0, 20, "linerace.goaltype.-1") == 0)
    {
        temp.goal_type = (int) str_to_dec(to_string);
    }
    else if(to_string.compare(0, 30, "0.statistics.totalPieceRotate=") == 0)
    {
        temp.n_piece_rotate = (int) str_to_dec(to_string);
    }
    else if(to_string.compare(0, 27, "0.statistics.totalHoldUsed=") == 0)
    {
        temp.n_hold_used = (int) str_to_dec(to_string);
    }
    else if(to_string.compare(0, 15, "timestamp.date=") == 0)
    {
        temp.date = to_string.erase(0,
            to_string.find_first_of("=") + 1).c_str();
    }

    if(to_string.compare(0, 12, "result.time=") == 0)
    {
        int minutes = 0;
        double seconds = (str_to_dec(to_string) / 60);

        temp.frames = (int) str_to_dec(to_string);

        while(seconds >= 60)
        {
            minutes++;
            seconds -= 60;
        }

        temp.minutes = minutes;
        temp.seconds = seconds;
    }

    if(to_string.compare(0, 10, "name.mode=") == 0)
    {
        to_string.erase(0, to_string.find_first_of("=") + 1);

        if(to_string == "MARATHON")
        {
            temp.mode = MARATHON;
        }
        else if(to_string == "LINE")
        {
            temp.mode = LINE_RACE;
        }
        else
        {
            temp.mode = OTHER;
        }
    }

    if(to_string.compare(0, 16, "linerace.big.-1=") == 0)
    {
        to_string.erase(0, to_string.find_first_of("=") + 1);

        if(to_string == "true")
        {
            temp.big = true;
        }
        else
        {
            temp.big = false;
        }
    }
}

rep assign_from_replays(string replay)
{
    rep temp;

    ifstream fin;

    const char* string_to_char = replay.c_str();

    fin.open(string_to_char);

    temp.replay_name = replay;
    temp.kpt = 0;
    temp.finesse = 0;

    char* q;

    while(!fin.eof())
    {
        char s[256];

        fin.getline(s, 256);
        q = strtok(s, " ");

        while(q != NULL)
        {
            string to_string(q);

            check_for_stat(to_string, temp);

            q = strtok(NULL, " ");
        }
    }

    return temp;
}

void make_settings_file()
{
    char* q;

    if(ifstream("minolog_settings"))
    {
        vector<int> thing;

        ifstream fin;
        fin.open("minolog_settings");

        while(!fin.eof())
        {
            char s[256];

            fin.getline(s, 256);
            q = strtok(s, " ");

            while(q != NULL)
            {
                string to_string(q);
                thing.push_back((int) strtod(q, NULL));

                q = strtok(NULL, " ");
            }
        }

        per_n_count = thing.at(1);
        per_n_to_show = thing.at(3);
        pb_to_show = thing.at(5);
        today_to_show = thing.at(7);
        old_day_to_show = thing.at(9);
        month_to_show = thing.at(11);
        fin_pb_to_show = thing.at(13);
        auto_time = thing.at(15);
    }
    else
    {
        FILE *p_file;
        p_file = fopen("minolog_settings", "w");

        if(p_file != NULL)
        {
            fprintf(p_file, "replays_per_n 500\nper_n_to_show 3\n"
                "pbs_to_show 3\ntoday_to_show 3\nold_day_to_show 3\n"
                "month_to_show 3\nfin_pb_to_show 3");
        }

        per_n_count = 500;
        per_n_to_show = 3;
        pb_to_show = 3;
        today_to_show = 3;
        old_day_to_show = 3;
        month_to_show = 3;
        fin_pb_to_show = 3;
        auto_time = 60;

        fclose(p_file);
    }
}

void make_replays_file()
{
    char* q;

    if(ifstream("minolog_replays"))
    {
        ifstream fin;
        fin.open("minolog_replays");

        int to_decimal;
        double to_float;

        int k = 0;

        while(!fin.eof())
        {
            int y = 0;

            char s[256];

            fin.getline(s, 256);
            q = strtok(s, " ");

            while(q != NULL)
            {
                to_decimal = (int) strtod(q, NULL);
                to_float = strtof(q, NULL);

                replays.resize(k + 1);

                switch(y)
                {
                    case 0:
                        replays[k].minutes = to_decimal;
                        break;
                    case 1:
                        replays[k].seconds = to_float;
                        break;
                    case 2:
                        replays[k].pieces_per_second = to_float;
                        break;
                    case 3:
                        replays[k].finesse = to_decimal;
                        break;
                    case 4:
                        replays[k].n_lines = to_decimal;
                        break;
                    case 5:
                        replays[k].n_piece_locked = to_decimal;
                        break;
                    case 6:
                        replays[k].n_piece_move = to_decimal;
                        break;
                    case 7:
                        replays[k].kpt = to_float;
                        break;
                    case 8:
                        replays[k].lines_per_minute = to_float;
                        break;
                    case 9:
                        replays[k].pieces_per_minute = to_float;
                        break;
                    case 10:
                        replays[k].n_piece_rotate = to_decimal;
                        break;
                    case 11:
                        replays[k].n_hold_used = to_decimal;
                        break;
                    case 12:
                        replays[k].n_single = to_decimal;
                        break;
                    case 13:
                        replays[k].n_double = to_decimal;
                        break;
                    case 14:
                        replays[k].n_triple = to_decimal;
                        break;
                    case 15:
                        replays[k].n_four = to_decimal;
                        break;
                    case 16:
                        replays[k].frames = to_decimal;
                        break;
                    case 17:
                        replays[k].timestamp = q;
                        break;
                    case 18:
                        replays[k].replay_name = q;
                        imported_replays.push_back(replays[k].replay_name);
                        break;
                    case 19:
                        replays[k].mode = q;
                        break;
                    case 20:
                        replays[k].goal_type = to_decimal;
                        break;
                    case 21:
                        replays[k].date = q;
                        break;
                    case 22:
                        replays[k].big = to_decimal;
                        break;
                }

                y++;
                q = strtok(NULL, " ");
            }

            k++;
        }

        fin.close();

        write_new_replays();
    }
    else
    {
        cout << "Scanning files..." << endl << endl;

        for(unsigned int j = 0; j < replay_names.size(); j++)
        {
            replays.push_back(assign_from_replays(replay_names.at(j)));
        }

        FILE *p_file;
        p_file = fopen("minolog_replays", "w");

        if(p_file != NULL)
        {
            for(unsigned int j = 0; j < replays.size(); j++)
            {
                rep replay = replays.at(j);

                fprintf(p_file, "%i %f %f %i %i %i %i %f %f %f %i %i %i "
                    "%i %i %i %i %s %s %s %i %s %i\n",
                    replay.minutes, replay.seconds, replay.pieces_per_second,
                    replay.finesse, replay.n_lines, replay.n_piece_locked,
                    replay.n_piece_move, replay.kpt, replay.lines_per_minute,
                    replay.pieces_per_minute, replay.n_piece_rotate,
                    replay.n_hold_used, replay.n_single, replay.n_double,
                    replay.n_triple, replay.n_four, replay.frames,
                    replay.timestamp.c_str(), replay.replay_name.c_str(),
                    replay.mode.c_str(), replay.goal_type, replay.date.c_str(),
                    replay.big);
            }

            fclose(p_file);
        }
    }
}

void write_new_replays()
{
    sort(imported_replays.begin(),
        imported_replays.begin() + imported_replays.size());

    sort(replay_names.begin(), replay_names.begin() + replay_names.size());

    set_difference(replay_names.begin(), replay_names.end(),
        imported_replays.begin(), imported_replays.end(),
        back_inserter(new_replays));

    unsigned int replays_size = replays.size();

    if(new_replays.size() > 0)
    {
        for(unsigned int j = 0; j < new_replays.size(); j++)
        {
            unsigned int to_begin = replays_size + j;
            rep replay;

            replays.push_back(assign_from_replays(new_replays.at(j)));
            replay = replays.at(to_begin);

            FILE *p_file;
            p_file = fopen("minolog_replays", "a");

            fprintf(p_file, "%i %f %f %i %i %i %i %f %f %f %i %i %i %i "
                "%i %i %i %s %s %s %i %s %i\n",
                replay.minutes, replay.seconds, replay.pieces_per_second,
                replay.finesse, replay.n_lines, replay.n_piece_locked,
                replay.n_piece_move, replay.kpt, replay.lines_per_minute,
                replay.pieces_per_minute, replay.n_piece_rotate,
                replay.n_hold_used, replay.n_single, replay.n_double,
                replay.n_triple, replay.n_four, replay.frames,
                replay.timestamp.c_str(), replay.replay_name.c_str(),
                replay.mode.c_str(), replay.goal_type, replay.date.c_str(),
                replay.big);

            fclose(p_file);
        }
    }
}

void make_json()
{
    FILE *p_file;
    p_file = fopen("minolog_json", "w");

    unsigned int replays_size = replays.size();

    fprintf(p_file, "[");

    for(unsigned int j = 0; j < replays_size; j++)
    {
        rep replay = replays.at(j);

        fprintf(p_file, "{\"minutes\":%i, \"seconds\":%f, "
            "\"pieces_per_second\": %f, \"finesse\": %i, \"n_lines\":%i, "
            "\"n_piece_locked\":%i, \"n_piece_move\": %i, \"kpt\": %f, "
            "\"lines_per_minute\": %f, \"pieces_per_minute\": %f, "
            "\"n_piece_rotate\":%i, \"n_hold_used\": %i, \"n_single\": %i, "
            "\"n_double\": %i, \"n_triple\": %i, \"n_four\": %i, "
            "\"frames\":%i, \"timestamp\": \"%s\", \"replay_name\": \"%s\", "
            "\"mode\": \"%s\", \"goal_type\": %i, \"date\": \"%s\", "
            "\"big\": %i}",
            replay.minutes, replay.seconds, replay.pieces_per_second,
            replay.finesse, replay.n_lines, replay.n_piece_locked,
            replay.n_piece_move, replay.kpt, replay.lines_per_minute,
            replay.pieces_per_minute, replay.n_piece_rotate,
            replay.n_hold_used, replay.n_single, replay.n_double,
            replay.n_triple, replay.n_four, replay.frames,
            replay.timestamp.c_str(), replay.replay_name.c_str(),
            replay.mode.c_str(), replay.goal_type, replay.date.c_str(),
            replay.big);

        if(j != replays_size - 1)
        {
            fprintf(p_file, ",\n");
        }
    }

    fprintf(p_file, "]");

    fclose(p_file);
}

void output_pb_history(int pb_to_show)
{
    int size = bests.size();

    if(size > 0)
    {
        cout << "--- 40 Lines Race personal best history " << "("
             << size << ") ---" << endl;

        cout << setw(10) << "Time" << setw(8) << "PPS" << setw(8) << "Pieces"
            << setw(9) << "Finesse" << setw(7) << "Holds"
            << setw(25) << "Name" << "Improvement";

        for(int j = size - 1; j >= size - pb_to_show; j--)
        {
            cout << endl << setw(10) << output_time(bests[j].frames)
                << setw(8) << setprecision(4) << bests[j].pieces_per_second
                << setw(8) << bests[j].n_piece_locked
                << setw(9) << setprecision(2) << bests[j].finesse
                << setw(7) << bests[j].n_hold_used
                << setw(25) << bests[j].replay_name;

            if(j != 0)
            {
                cout << "-" + to_float(bests[j].difference / 60);
            }
        }
    }
}

void output_fin_pb_history(int fin_pb_to_show)
{
    int size = finesse_bests.size();

    if(size > 0)
    {
        cout << endl << endl << "--- Finesse personal best history "
            << "(" << size << ") ---" << endl;

        cout << setw(10) << "Time" << setw(8) << "PPS" << setw(8) << "Pieces"
            << setw(9) << "Finesse" << setw(7) << "Holds"
            << setw(25) << "Name" << "Improvement";

        for(int j = size - 1; j >= size - fin_pb_to_show; j--)
        {
            cout << endl << setw(10) << output_time(finesse_bests[j].frames)
                << setw(8) << setprecision(4)
                << finesse_bests[j].pieces_per_second
                << setw(8) << finesse_bests[j].n_piece_locked
                << setw(9) << setprecision(2) << finesse_bests[j].finesse
                << setw(7) << finesse_bests[j].n_hold_used
                << setw(25) << finesse_bests[j].replay_name;

            if(j != 0)
            {
                cout << "-" + to_float(finesse_bests[j].difference);
            }
        }
    }
}

void output_per_n(int per_n_count, int per_n_to_show, double num_40,
    double hundred_count)
{
    int size = stats.size();
    double diff = num_40 - hundred_count;

    cout << endl << endl << "--- Statistics per " << per_n_count
        << " completed 40 Lines Race replays (" << size << ") ---" << endl;

    cout << setw(10) << "Time" << setw(8) << "PPS" << setw(8) << "Pieces"
        << setw(9) << "Finesse" << setw(7) << "Holds" << setw(17)
        << "End date" << setw(8) << "To #" << "Difference";

    for(int j = size - 1; j >= size - per_n_to_show; j--)
    {
        if(j == size - 1 && num_40 - hundred_count != 0)
        {
            cout << endl << setw(10) << output_time(stats[j].frames / diff)
                << setw(8) << setprecision(4)
                << stats[j].pieces_per_second / diff
                << setw(8) << setprecision(2) << stats[j].n_piece_locked / diff
                << setw(9) << setprecision(2) << stats[j].finesse / diff
                << setw(7) << stats[j].n_hold_used / diff
                << setw(17) << month_date(stats[j].end_date)
                << setw(8) << stats[j].lower;

            if(j != 0)
            {
                if(stats[j - 1].frames /(per_n_count) > stats[j].frames / diff)
                {
                    cout << "-" + to_float(stats[j].difference / 60);
                }
                else
                {
                    cout << "+" + to_float(stats[j].difference / 60);
                }
            }
        }
        else
        {
            cout << endl << setw(10)
                << output_time(stats[j].frames / per_n_count)
                << setw(8) << setprecision(4)
                << stats[j].pieces_per_second / per_n_count
                << setw(8) << setprecision(2)
                << stats[j].n_piece_locked / per_n_count
                << setw(9) << setprecision(2)
                << stats[j].finesse / per_n_count
                << setw(7) << stats[j].n_hold_used / per_n_count
                << setw(17) << month_date(stats[j].end_date)
                << setw(8) << stats[j].lower;

            if(j != 0)
            {
                if(stats[j - 1].frames > stats[j].frames)
                {
                    cout << "-" + to_float(stats[j].difference / 60);
                }
                else
                {
                    cout << "+" + to_float(stats[j].difference / 60);
                }
            }
        }
    }
}

void output_month_history(int month_to_show)
{
    int size = monthies.size();

    if(size > 0)
    {
        cout << endl << endl
            << "--- Monthly history of completed 40 Lines Race replays ("
            << monthies.size() << ") ---" << endl;

        cout << setw(10) << "Time" << setw(8) << "PPS" << setw(8)
            << "Pieces" << setw(9) << "Finesse" << setw(7) << "Holds"
            << setw(11) << "Month" << setw(6) << "#" << setw(8) << "#/d"
            << "Difference";

        for(int j = size - 1; j >= size - month_to_show; j--)
        {
            int month_size = monthies[j].size;

            cout << endl << setw(10)
                << output_time((monthies[j].frames / month_size))
                << setw(8) << setprecision(4)
                << monthies[j].pieces_per_second / month_size
                << setw(8) << setprecision(2)
                << monthies[j].n_piece_locked / month_size
                << setw(9) << setprecision(2)
                << monthies[j].finesse / month_size
                << setw(7) << monthies[j].n_hold_used / month_size
                << setw(11) << monthies[j].month_str
                << setw(6) << month_size
                << setw(8) <<(float)monthies[j].size / monthies[j].day_count;

            if(j != 0)
            {
                int previous_month_size = monthies[j - 1].size;

                if(monthies[j - 1].frames / previous_month_size
                    > monthies[j].frames / month_size)
                {
                    cout << "-" + to_float(monthies[j].difference / 60);
                }
                else
                {
                    cout << "+" + to_float(monthies[j].difference / 60);
                }
            }
        }
    }
}

void output_old_day_history(int old_day_to_show)
{
    int size = oldies.size();

    if(size > 0)
    {
        cout << endl << endl
            << "--- Daily history of completed 40 Lines Race replays ("
            << size << ") ---" << endl;

        cout << setw(10) << "Time" << setw(8) << "PPS" << setw(8) << "Pieces"
            << setw(9) << "Finesse" << setw(7) << "Holds" << setw(17) << "Date"
            << setw(8) << "#" << "Difference";

        for(int j = size - 1; j >= size - old_day_to_show; j--)
        {
            int day_size = oldies[j].size;

            cout << endl << setw(10)
                << output_time((oldies[j].frames / day_size))
                << setw(8) << setprecision(4)
                << oldies[j].pieces_per_second / day_size
                << setw(8) << setprecision(2)
                << oldies[j].n_piece_locked / day_size
                << setw(9) << setprecision(2)
                << oldies[j].finesse / day_size
                << setw(7) << oldies[j].n_hold_used / day_size
                << setw(17) << month_date(oldies[j].date)
                << setw(8) << day_size;

            if(j != 0)
            {
                int previous_day_size = oldies[j - 1].size;

                if(oldies[j - 1].frames /
                    previous_day_size > oldies[j].frames / day_size)
                {
                    cout << "-" + to_float(oldies[j].difference / 60);
                }
                else
                {
                    cout << "+" + to_float(oldies[j].difference / 60);
                }
            }
        }
    }
}

void output_today_history(int today_to_show)
{
    int size = todaies.size();

    if(size > 0)
    {
        cout << endl << endl << "--- Today's completed 40 Lines Race replays ("
            << size << ") ---" << endl;

        cout << setw(10) << "Time" << setw(8) << "PPS" << setw(8) << "Pieces"
            << setw(9) << "Finesse" << setw(7) << "Holds" << "Name";

        for(int j = size - 1; j >= size - today_to_show; j--)
        {
            cout << endl << setw(10) << output_time(todaies[j].frames)
                << setw(8) << setprecision(4) << todaies[j].pieces_per_second
                << setw(8) << todaies[j].n_piece_locked
                << setw(9) << setprecision(2) << todaies[j].finesse
                << setw(7) << todaies[j].n_hold_used
                << todaies[j].replay_name;
        }
    }
}

void load_python_graph()
{
    FILE* in = popen("python minolog.py", "r");
    pclose(in);
}

void make_graph_mode(char const * type)
{
    FILE *p_file;
    p_file = fopen("minolog_graph", "w");

    if(p_file != NULL)
    {
        fprintf(p_file, "%s", type);
    }

    fclose(p_file);
}

void set_display_limits()
{
    if(per_n_to_show <= 0 || per_n_to_show > (int) stats.size())
    {
        per_n_to_show = stats.size();
    }

    if(pb_to_show <= 0 || pb_to_show > (int) bests.size())
    {
        pb_to_show = bests.size();
    }

    if(old_day_to_show <= 0 || old_day_to_show > (int) oldies.size())
    {
        old_day_to_show = oldies.size();
    }

    if(month_to_show <= 0 || month_to_show > (int) monthies.size())
    {
        month_to_show = monthies.size();
    }

    if(fin_pb_to_show <= 0 || fin_pb_to_show > (int) finesse_bests.size())
    {
        fin_pb_to_show = finesse_bests.size();
    }

    if(today_to_show <= 0 || today_to_show > (int) todaies.size())
    {
        today_tag = today_to_show;
        today_to_show = todaies.size();
    }
    else
    {
        today_tag = today_to_show;
    }
}

void display_header()
{
    double pieces_sub_102_per = (pieces_sub_102 / num_40) * 100;
    double pieces_102_per = (pieces_102 / num_40) * 100;
    double pieces_103_per = (pieces_103 / num_40) * 100;
    double pieces_greater_103_per = (pieces_greater_103 / num_40) * 100;

    int last_pos = oldies.size() - 1;

    string first = month_date(oldies[0].date);
    string last = month_date(oldies[last_pos].date);

    cout << setw(45) << "--- Total Statistics ---"
        << "--- 40 Lines Race Statistics ---" << endl;
    cout << setw(45) << "Time played: " + output_time(all_frames_sum)
        << "Time played: " + output_time(_40_frames_sum) << endl;
    cout << setw(45) << "Average time: " + output_time(all_frames_sum / num_all)
        << "Average time: " + output_time(_40_frames_sum / num_40) << endl;
    cout << setw(45) << "# of replays: " + to_string((int) num_all)
        << "# of replays: " + to_string((int) num_40) << endl << endl;

    cout << setw(45) << "Oldest: " + first << "< 102 pieces: "
        + to_int(pieces_sub_102) << " ("
        << to_float(pieces_sub_102_per) << "%)" << endl;
    cout << setw(45) << "Recent: " + last << "= 102 pieces: "
        + to_int(pieces_102) << " ("
        << to_float(pieces_102_per) << "%)" << endl;
    cout << setw(45) << " " << "= 103 pieces: "
        + to_int(pieces_103) << " ("
        << to_float(pieces_103_per) << "%)" << endl;
    cout << setw(45) << " " << "> 103 pieces: "
        + to_int(pieces_greater_103) << " ("
        << to_float(pieces_greater_103_per) << "%)" << endl << endl;
}

void take_input()
{
    char * q;
    char input[256];

    string cmd;
    int value = 0;
    bool change_settings = 0;

    cout << "Press 'ENTER' to update. Type 'cmds' for commands." << endl;

    cin.getline(input, 256);

    q = strtok(input, " ");

    while(q != NULL)
    {
        if(strcmp(q, "cmds") == 0)
        {
            cout << endl << setw(20) << "pern 'count'"
                << ":: set per N count" << endl;
            cout << setw(20) << "perdts 'count'"
                << ":: set per days to show" << endl;
            cout << setw(20) << "pernts 'count'"
                << ":: set per Ns to show" << endl;
            cout << setw(20) << "pbs 'count'"
                << ":: set PBs to show" << endl;
            cout << setw(20) << "today 'count'"
                << ":: set today's replays to show" << endl;
            cout << setw(20) << "old 'count'"
                << ":: set old day's replays to show" << endl;
            cout << setw(20) << "month 'count'"
                << ":: set monthly replays to show" << endl;
            cout << setw(20) << "finpb 'count'"
                << ":: set finesse PBs to show" << endl;
            cout << setw(20) << "autoset 'seconds'"
                << ":: set automatic update time" << endl << endl;
            cout << setw(20) << "json"
                << ":: make json file" << endl << endl;
            cout << setw(20) << "graph-today"
                << ":: display today graph" << endl;
            cout << setw(20) << "graph-pbs"
                << ":: display pb graph" << endl;
            cout << setw(20) << "graph-pern"
                << ":: display per n graph" << endl << endl;
            cout << setw(20) << "auto"
                << ":: enable automatic updating" << endl;

            cin.getline(input, 256);
            q = strtok(input, " ");
        }
        else if((cmd == "graph-pern" || cmd == "graph-pbs" || cmd == "pern" ||
            cmd == "json" || cmd == "pernts" || cmd == "pbs" ||
            cmd == "today" || cmd == "old" || cmd == "month" ||
            cmd == "finpb" || cmd == "autoset")
            && strtod(q, NULL) > 0)
        {
            if(cmd == "graph-pern")
            {
                value = 1;
            }
            else if(cmd == "graph-pbs" || cmd == "graph-today")
            {
                value = 0;
            }
            else
            {
                value = (int) strtod(q, NULL);
            }

            break;
        }
        else if(strcmp(q, "graph-pern") == 0 || strcmp(q, "graph-pbs") == 0 ||
            strcmp(q, "graph-today") == 0 ||
            strcmp(q, "json") == 0 || strcmp(q, "pern") == 0 ||
            strcmp(q, "pernts") == 0 || strcmp(q, "pbs") == 0 ||
            strcmp(q, "today") == 0 || strcmp(q, "old") == 0 ||
            strcmp(q, "month") == 0 || strcmp(q, "finpb") == 0 ||
            strcmp(q, "autoset") == 0 || strcmp(q, "auto") == 0)
        {
            cmd = q;
            q = strtok(NULL, " ");
        }
        else
        {
            break;
        }
    }

    if(cmd == "pern")
    {
        per_n_count = value;
        change_settings = 1;
    }
    else if(cmd == "pernts")
    {
        per_n_to_show = value;
        change_settings = 1;
    }
    else if(cmd == "pbs")
    {
        pb_to_show = value;
        change_settings = 1;
    }
    else if(cmd == "today")
    {
        today_tag = value;
        change_settings = 1;
    }
    else if(cmd == "old")
    {
        old_day_to_show = value;
        change_settings = 1;
    }
    else if(cmd == "month")
    {
        month_to_show = value;
        change_settings = 1;
    }
    else if(cmd == "finpb")
    {
        fin_pb_to_show = value;
        change_settings = 1;
    }
    else if(cmd == "autoset")
    {
        auto_time = value;
        change_settings = 1;
    }
    else if(cmd == "graph-pern")
    {
        cout << endl << "Loading..." << endl << endl;

        int size = stats.size();
        double diff = num_40 - hundred_count;

        vector<per_n> to_output;

        for(int j = size - 1; j >= 0; j--)
        {
            per_n temp;

            if(j == size - 1 && num_40 - hundred_count != 0)
            {
                temp.frames = stats[j].frames / diff;
                temp.pieces_per_second = stats[j].pieces_per_second / diff;
                temp.n_piece_locked = stats[j].n_piece_locked / diff;
                temp.finesse = stats[j].finesse / diff;
                temp.n_hold_used = stats[j].n_hold_used / diff;
                temp.end_date = stats[j].end_date;
                temp.n_piece_rotate = stats[j].n_piece_rotate / diff;
                temp.lower = stats[j].lower;

                to_output.push_back(temp);
            }
            else
            {
                temp.frames = stats[j].frames / per_n_count;
                temp.pieces_per_second = stats[j].pieces_per_second /
                    per_n_count;
                temp.n_piece_locked = stats[j].n_piece_locked / per_n_count;
                temp.finesse = stats[j].finesse / per_n_count;
                temp.n_hold_used = stats[j].n_hold_used / per_n_count;
                temp.end_date = stats[j].end_date;
                temp.n_piece_rotate = stats[j].n_piece_rotate / per_n_count;
                temp.lower = stats[j].lower;

                to_output.push_back(temp);
            }
        }

        make_graph_mode("graph-pern");

        FILE *p_file;
        p_file = fopen("minolog_gdata", "w");

        int replays_size = to_output.size() - 1;

        fprintf(p_file, "[");

        for(int j = replays_size; j >= 0; j--)
        {
            per_n purn = to_output.at(j);

            char const * str = "{\"seconds\":%f, \"pieces_per_second\":%f, "
                "\"n_piece_locked\":%f, \"frames\":%f, \"n_piece_rotate\":%f, "
                "\"finesse\":%f, \"n_hold_used\":%f}";

            fprintf(p_file, str, purn.frames / 60, purn.pieces_per_second,
                purn.n_piece_locked, purn.frames, purn.n_piece_rotate,
                purn.finesse, purn.n_hold_used);

            if(j > 0)
            {
                fprintf(p_file, ",\n");
            }
        }

        fprintf(p_file, "]");

        fclose(p_file);

        cout << "Press 'ENTER' to update." << endl;

        load_python_graph();
    }
    else if(cmd == "graph-pbs" || cmd == "graph-today")
    {
        cout << endl << "Loading..." << endl << endl;

        make_graph_mode("graph-pbs");

        FILE *p_file;
        p_file = fopen("minolog_gdata", "w");

        unsigned int replays_size;

        if(cmd == "graph-pbs")
        {
            replays_size = bests.size();
        }
        else
        {
            replays_size = todaies.size();
        }

        fprintf(p_file, "[");

        for(unsigned int j = 0; j < replays_size; j++)
        {
            if(cmd == "graph-pbs")
            {
                pb peeb = bests.at(j);
                fprintf(p_file, "{\"seconds\":%f}", peeb.frames / 60);
            }
            else
            {
                today td = todaies.at(j);
                fprintf(p_file, "{\"seconds\":%f}", td.frames / 60);
            }


            if(j != replays_size - 1)
            {
                fprintf(p_file, ",\n");
            }
        }

        fprintf(p_file, "]");

        fclose(p_file);

        cout << "Press 'ENTER' to update." << endl;

        load_python_graph();
    }
    else if(cmd == "json")
    {
        make_json();
    }
    else if(cmd == "auto")
    {
        auto_update = 1;
    }

    if(change_settings == 1)
    {
        FILE *p_file;
        p_file = fopen("minolog_settings", "w");

        char const* output = "replays_per_n %i\nper_n_to_show %i"
        "\npbs_to_show %i\ntoday_to_show %i\nold_day_to_show %i"
        "\nmonth_to_show %i\nfin_pb_to_show %i\nauto_time %i";

        fprintf(p_file, output, per_n_count, per_n_to_show, pb_to_show,
            today_tag, old_day_to_show, month_to_show, fin_pb_to_show,
            auto_time);

        fclose(p_file);
    }
}

void reset()
{
    replays.clear();
    replay_names.clear();
    imported_replays.clear();
    new_replays.clear();
    oldies.clear();
    monthies.clear();
    todaies.clear();
    stats.clear();
    bests.clear();
    finesse_bests.clear();

    all_frames_sum = 0;
    _40_frames_sum = 0;

    num_all = 0;
    num_40 = 0;
    hundred_count = 0;

    pieces_sub_102 = 0;
    pieces_102 = 0;
    pieces_103 = 0;
    pieces_greater_103 = 0;

    lowest_finesse = INT_MAX;
    lowest_frames = INT_MAX;

    month_size = 0;
    day_count = 0;
    size_buf = 0;

    month_buf.clear();
    day_buf.clear();
    date_buf.clear();
}

void set_fin_pb_history(int j, int &finMark)
{
    if(replays[j].finesse < lowest_finesse && replays[j].finesse != 0)
    {
        finesse_pb temp;

        temp.frames = replays[j].frames;
        temp.pieces_per_second = replays[j].pieces_per_second;
        temp.n_hold_used = replays[j].n_hold_used;
        temp.replay_name = replays[j].replay_name;
        temp.finesse = replays[j].finesse;
        temp.n_piece_locked = replays[j].n_piece_locked;

        finesse_bests.push_back(temp);

        if(finMark == 0)
        {
            finesse_bests[finMark].difference = 0;
        }
        else
        {
            finesse_bests[finMark].difference =
                finesse_bests[finMark - 1].finesse -
                finesse_bests[finMark].finesse;
        }

        lowest_finesse = replays[j].finesse;
        finMark++;
    }
}

void set_pb_history(int j, int &u)
{
    if(replays[j].frames < lowest_frames)
    {
        pb temp;

        temp.frames = replays[j].frames;
        temp.pieces_per_second = replays[j].pieces_per_second;
        temp.n_hold_used = replays[j].n_hold_used;
        temp.replay_name = replays[j].replay_name;
        temp.finesse = replays[j].finesse;
        temp.n_piece_locked = replays[j].n_piece_locked;

        bests.push_back(temp);

        if(u == 0)
        {
            bests[u].difference = 0;
        }
        else
        {
            bests[u].difference = bests[u - 1].frames - bests[u].frames;
        }

        lowest_frames = replays[j].frames;
        u++;
    }
}

void set_per_n_history(int j, int &n, int &k)
{
    _40_frames_sum += replays[j].frames;

    stats.resize(k + 1);

    n++;

    stats[k].end_date = replays[j].date;
    stats[k].lower = (int) num_40;
    stats[k].finesse += replays[j].finesse;
    stats[k].frames += replays[j].frames;
    stats[k].pieces_per_second += replays[j].pieces_per_second;
    stats[k].n_hold_used += replays[j].n_hold_used;
    stats[k].n_piece_rotate += replays[j].n_piece_rotate;
    stats[k].n_piece_locked += replays[j].n_piece_locked;

    if(k != 0)
    {
        if(stats[k - 1].frames / per_n_count >
            stats[k].frames / (num_40 - hundred_count))
        {
            stats[k].difference = stats[k - 1].frames /
                per_n_count - stats[k].frames /(num_40 - hundred_count);
        }
        else
        {
            stats[k].difference = stats[k].frames /
                (num_40 - hundred_count) - stats[k - 1].frames / per_n_count;
        }
    }

    if(n == per_n_count)
    {
        if(k != 0)
        {
            if(stats[k - 1].frames / per_n_count >
                stats[k].frames / per_n_count)
            {
                stats[k].difference = stats[k - 1].frames /
                    per_n_count - stats[k].frames / per_n_count;
            }
            else
            {
                stats[k].difference = stats[k].frames /
                    per_n_count - stats[k - 1].frames / per_n_count;
            }
        }

        n = 0;
        hundred_count += per_n_count;
        k++;
    }
}

void set_today_history(int j, int &s)
{
    if(replays[j].date == convert_date())
    {
        todaies.resize(s + 1);

        todaies[s].frames = replays[j].frames;
        todaies[s].pieces_per_second = replays[j].pieces_per_second;
        todaies[s].n_hold_used = replays[j].n_hold_used;
        todaies[s].replay_name = replays[j].replay_name;
        todaies[s].finesse = replays[j].finesse;
        todaies[s].n_piece_locked = replays[j].n_piece_locked;

        s++;
    }
}

void set_old_day_history(int j, int &d)
{
    if(replays[j].date != date_buf)
    {
        size_buf = 0;
        d++;
    }

    size_buf++;
    date_buf = replays[j].date;
    oldies.resize(d);

    oldies[d - 1].frames += replays[j].frames;
    oldies[d - 1].pieces_per_second += replays[j].pieces_per_second;
    oldies[d - 1].n_hold_used += replays[j].n_hold_used;
    oldies[d - 1].date = replays[j].date;
    oldies[d - 1].finesse += replays[j].finesse;
    oldies[d - 1].n_piece_locked += replays[j].n_piece_locked;
    oldies[d - 1].size = size_buf;

    if(d - 1 != 0)
    {
        if(oldies[d - 2].frames / oldies[d - 2].size
            > oldies[d - 1].frames / oldies[d - 1].size)
        {
            oldies[d - 1].difference =
                (oldies[d - 2].frames / oldies[d - 2].size) -
                (oldies[d - 1].frames / oldies[d - 1].size);
        }
        else
        {
            oldies[d - 1].difference =
                (oldies[d - 1].frames / oldies[d - 1].size) -
                (oldies[d - 2].frames / oldies[d - 2].size);
        }
    }
}

void set_month_history(int j, int &l)
{
    if(replays[j].date.substr(5, 2) != month_buf)
    {
        month_size = 0;
        l++;
        day_count = 0;
    }

    if((replays[j].date.substr(8, 2) != day_buf) && l != 0)
    {
        day_count++;
    }

    month_size++;
    month_buf = replays[j].date.substr(5, 2);
    day_buf = replays[j].date.substr(8, 2);
    monthies.resize(l);

    monthies[l - 1].day_count = day_count;
    monthies[l - 1].frames += replays[j].frames;
    monthies[l - 1].pieces_per_second += replays[j].pieces_per_second;
    monthies[l - 1].n_hold_used += replays[j].n_hold_used;
    monthies[l - 1].month_str = num_to_month(replays[j].date.substr(5, 2)) +
        " " + replays[j].date.substr(0, 4);
    monthies[l - 1].finesse += replays[j].finesse;
    monthies[l - 1].n_piece_locked += replays[j].n_piece_locked;
    monthies[l - 1].size = month_size;

    if(l - 1 != 0)
    {
        if(monthies[l - 2].frames / monthies[l - 2].size >
            monthies[l - 1].frames / monthies[l - 1].size)
        {
            monthies[l - 1].difference =
                (monthies[l - 2].frames / monthies[l - 2].size) -
                (monthies[l - 1].frames / monthies[l - 1].size);
        }
        else
        {
            monthies[l - 1].difference =
            (monthies[l - 1].frames / monthies[l - 1].size) -
            (monthies[l - 2].frames / monthies[l - 2].size);
        }
    }
}

void update_piece_counts(int j)
{
    if(replays[j].n_piece_locked < 102)
    {
        pieces_sub_102++;
    }
    else if(replays[j].n_piece_locked == 102)
    {
        pieces_102++;
    }
    else if(replays[j].n_piece_locked == 103)
    {
        pieces_103++;
    }
    else
    {
        pieces_greater_103++;
    }
}
