#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <math.h>

using namespace std;

double getsecs(string time)
{
    int i = 0;
    for(; time[i] != 'm'; i++)
    {
    }

    double mins, secs;

    mins = atof(time.substr(0, i).c_str());
    secs = atof(time.substr(i + 1, time.length() - i - 2).c_str());

    return mins * 60 + secs;
}

void ms_print(double secs)
{
    int mins = 0;
    while(secs >= 60)
    {
        secs -= 60;
        mins++;
    }
    cout << mins << "m" << fixed << setprecision(3) << secs << "s";
}

int main()
{
    ifstream in("timestat.txt");
    int runs = 0;
    string type, real, user, sys;
    double real_sum = 0, user_sum = 0, sys_sum = 0, realsqr_sum = 0, usersqr_sum = 0, syssqr_sum = 0;
    while(in >> type >> real >> type >> user >> type >> sys)
    {
        real_sum += getsecs(real);
        realsqr_sum += getsecs(real) * getsecs(real);
        user_sum += getsecs(user);
        usersqr_sum += getsecs(user) * getsecs(user);
        sys_sum += getsecs(sys);
        syssqr_sum += getsecs(sys) * getsecs(sys);
        runs++;
    }

    double real_avg = real_sum/runs, user_avg = user_sum/runs, sys_avg = sys_sum/runs;
    double real_std_dev = sqrt(realsqr_sum/runs - real_avg * real_avg);
    double user_std_dev = sqrt(usersqr_sum/runs - user_avg * user_avg);
    double sys_std_dev = sqrt(syssqr_sum/runs - sys_avg * sys_avg);

    cout << "Number of runs: " << runs << "\n";
    cout << "Average time statistics\n";
    cout << "real "; ms_print(real_avg); cout << " user "; ms_print(user_avg); cout << " sys "; ms_print(sys_avg); cout << "\n";
    cout << "Standard deviation of time statistics\n";
    cout << "real "; ms_print(real_std_dev); cout << " user "; ms_print(user_std_dev); cout << " sys "; ms_print(sys_std_dev); cout << "\n";

    in.clear();
    in.seekg(0, ios::beg);

    int real_count = 0, user_count = 0, sys_count = 0;
    while(in >> type >> real >> type >> user >> type >> sys)
    {
        if((getsecs(real) > real_avg - real_std_dev) && (getsecs(real) < real_avg + real_std_dev))
        {
            real_count++;
        }
        if((getsecs(user) > user_avg - user_std_dev) && (getsecs(user) < user_avg + user_std_dev))
        {
            user_count++;
        }
        if((getsecs(sys) > sys_avg - sys_std_dev) && (getsecs(sys) < sys_avg + sys_std_dev))
        {
            sys_count++;
        }
    }

    cout << "Number of runs within average - standard deviation to average + standard deviation\n";
    cout << "real " << real_count << " user " << user_count << " sys " << sys_count << "\n";
    return 0;
}
