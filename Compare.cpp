#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include "cmdline.cc"
#include "Complex.cpp"
#define ERR_NOPEN "Cannot open "
#define HELP "Program must be invoked: ./<Archive name> -f1 <file1> -f2 <file2> -f3 <output file>"
#define MSG_HEADER "test "
#define MSG_NOK "NOK "
#define MSG_OK "OK "
#define TOL_DEFAULT 1e-6

using namespace std;

static void opt_regression(string const &);
static void opt_input(string const &);
static void opt_help(string const &);


static option_t options[] = {
    {1, "r", "regression"   , "-", opt_regression , OPT_MANDATORY  },
    {1, "i", "input"   , "-", opt_input , OPT_DEFAULT  },
    {0, "h" , "help"    , NULL, opt_help   , OPT_DEFAULT    },
    {0, 0   ,   0       ,   0 ,      0     ,    0           },
};

static istream *ris = NULL;
static istream *is = NULL;
static ifstream rifs;
static ifstream ifs;
static double tol = TOL_DEFAULT;
static void
opt_regression(string const &arg)
{
    // Si el nombre del archivos es "-", usaremos la entrada
    // estandar. De lo contrario, abrimos un archivo en modo
    // de lectura.
    //
    if (arg == "-") {
        ris = &cin;
    } else {
        rifs.open(arg.c_str(), ios::in);
        ris = &rifs;
    }

    // Verificamos que el stream este OK.
    //
    if (!ris->good()) {
        cerr << ERR_NOPEN << arg << "." << endl;
        exit(1);
    }
}

static void
opt_input(string const &arg)
{
    // Si el nombre del archivos es "-", usaremos la entrada
    // estandar. De lo contrario, abrimos un archivo en modo
    // de lectura.
    //
    if (arg == "-") {
        is = &cin;
    } else {
        ifs.open(arg.c_str(), ios::in);
        is = &ifs;
    }

    // Verificamos que el stream este OK.
    //
    if (!is->good()) {
        cerr << ERR_NOPEN << arg << "." << endl;
        exit(1);
    }
}

static void
opt_help(string const &arg){
    cout << HELP << endl;
    exit(0);
}


int main(int argc, char* const argv[]){
    cmdline cmdl(options);
    cmdl.parse( argc, argv );
    Complex RegBuff, InBuff, diff;
    string regline, inputline;
    bool lerrors=false, gerrors = false;
    int i=0,j=0;
    while(!rifs.eof()&&!ifs.eof()){ //mientras no haya llegado al end of file.
        lerrors=false;
        getline(rifs, regline);
        getline(ifs, inputline);
        stringstream  regstream(regline);
        stringstream  instream(inputline);
        while(regstream>>RegBuff && instream>>InBuff){ // intento leer un Complex de cada archivo
            if(regstream.good() && instream.good()){
                diff=RegBuff-InBuff;
                cerr<<diff<<endl;
                cerr<<diff.Abs()<<endl;
                if(diff.Abs()>= tol){
                    lerrors=true;
                    gerrors=true;
                }
                j++;
            }
        }
        //once the entire line is tested
        //should test if line was not an empty line
        cout<<MSG_HEADER<<i+1<<": ";
        if(lerrors) cout<<MSG_NOK;
        else cout<< MSG_OK; 
        cout<<j<<" "<< tol << endl; 
        j=0;
        i++;
    }
    rifs.close();
    ifs.close();
    if (gerrors) return 1;
    else return 0;
}