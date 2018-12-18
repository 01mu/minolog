/*
* minolog
* github.com/01mu
*/

#ifndef ML_H_
#define ML_H_

#include <unistd.h>
#include <dirent.h>
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

struct rep
{
    bool big;

    string timestamp;
    string replay_name;
    string mode;
    string date;

    int frames;
    int minutes;
    int finesse;
    int goal_type;
    int n_piece_locked;
    int n_piece_move;
    int n_single;
    int n_double;
    int n_triple;
    int n_four;
    int n_lines;
    int n_piece_rotate;
    int n_hold_used;

    double seconds;
    double pieces_per_second;
    double kpt;
    double lines_per_minute;
    double pieces_per_minute;
};

struct per_n
{
    string end_date;

    int lower;

    double pieces_per_second;
    double n_piece_locked;
    double frames;
    double n_piece_rotate;
    double finesse;
    double n_hold_used;
    double difference;
};

struct pb
{
    string replay_name;

    int finesse;
    int n_hold_used;
    int n_piece_locked;

    double pieces_per_second;
    double difference;
    double frames;
};

struct finesse_pb
{
    string replay_name;

    int finesse;
    int n_hold_used;
    int n_piece_locked;
    int difference;

    double pieces_per_second;
    double frames;
};

struct today
{
    string replay_name;

    int finesse;
    int n_hold_used;
    int n_piece_locked;

    double pieces_per_second;
    double frames;
};

struct old_day
{
    string date;

    int size;

    double pieces_per_second;
    double difference;
    double frames;
    double finesse;
    double n_hold_used;
    double n_piece_locked;
};

struct month
{
    string month_str;

    int size;
    int day_count;

    double pieces_per_second;
    double difference;
    double frames;
    double finesse;
    double n_hold_used;
    double n_piece_locked;
};

double str_to_dec(string);

string to_int(int);
string to_float(double);
string num_to_month(string);
string month_date(string);
string output_time(double);
string convert_date();

void load_python_graph();
void make_graph_mode(char const *);
void set_display_limits();
void take_input();
void reset();
void update_piece_counts(int j);

vector<string> get_replay_names();
void check_for_stat(string to_string, rep & temp);
rep assign_from_replays(string);

void make_settings_file();
void make_replays_file();
void write_new_replays();
void make_json();

void display_header();

void output_pb_history(int);
void output_fin_pb_history(int);
void output_per_n(int, int, double, double);
void output_month_history(int);
void output_old_day_history(int);
void output_today_history(int);

void set_fin_pb_history(int, int &);
void set_pb_history(int, int &);
void set_per_n_history(int, int &, int &);
void set_today_history(int, int &);
void set_old_day_history(int, int &);
void set_month_history(int, int &);

void show_cmd_options();
void make_graph_pern();
void make_graph_pbs(string &);

#endif
