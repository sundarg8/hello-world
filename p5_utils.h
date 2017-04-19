
int printTime();
int printHour();
int pre_run(int argc, char *argv[]);
int post_run();
int nlfl(char *str);

int pf_tz();
int pf_ts();
float pf_te();
float pf_tt();
int pf_ts_th(long tid);
float pf_te_th(long tid);

#define NL printf("\n")
#define NLFL(str) \
    cout << ">>>  " << __FUNCTION__ <<":" <<  __LINE__ <<  "  <<<   " << str << "\n"
#define ct(str) cout << str << "\n"
#define cts(str) cout << str
