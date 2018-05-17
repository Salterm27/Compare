#include <iostream>
#include "cmdline.cc"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include "Complex.cpp"
#define ERR_NOPEN "Cannot open "
#define HELP "Program must be invoked: ./<Archive name> -f1 <file1> -f2 <file2> -f3 <output file>"
#define MSG_ERRORS "Errors Detected. For more information use an output file."
#define MSG_NERRORS "No errors detected."
#define MSK_NOK "NOK"
#define TOL 0.1

using namespace std;

static void opt_input1(string const &);
static void opt_input2(string const &);
static void opt_output(string const &);
static void opt_help(string const &);


static option_t options[] = {
    {1, "f1", "file1", NULL, opt_input1, OPT_MANDATORY},
    {1, "f2", "file2", NULL, opt_input2, OPT_MANDATORY},
    {1, "o", "output", NULL, opt_output, OPT_DEFAULT},
    {0 ,"h", "help" , NULL, opt_help, OPT_DEFAULT},
    {0,0,0,0,0,0},
};

static istream *is1 = 0;
static istream *is2 = 0;
static ostream *oss = 0;
static ifstream ifs1;
static ifstream ifs2;
static ofstream ofs;

static void
opt_input1(string const &arg)
{
    // Si el nombre del archivos es "-", usaremos la entrada
    // estandar. De lo contrario, abrimos un archivo en modo
    // de lectura.
    //
    if (arg == "-") {
        is1 = &cin;
    } else {
        ifs1.open(arg.c_str(), ios::in);
        is1 = &ifs1;
    }

    // Verificamos que el stream este OK.
    //
    if (!is1->good()) {
        cerr << ERR_NOPEN << arg << "." << endl;
        exit(1);
    }
}

static void
opt_input2(string const &arg)
{
    // Si el nombre del archivos es "-", usaremos la entrada
    // estandar. De lo contrario, abrimos un archivo en modo
    // de lectura.
    //
    if (arg == "-") {
        is2 = &cin;
    } else {
        ifs2.open(arg.c_str(), ios::in);
        is2 = &ifs2;
    }

    // Verificamos que el stream este OK.
    //
    if (!is2->good()) {
        cerr << ERR_NOPEN << arg << "." << endl;
        exit(1);
        exit(1);
    }
}


static void
opt_output(string const &arg)
{
    // Si el nombre del archivos es "-", usaremos la salida
    // estandar. De lo contrario, abrimos un archivo en modo
    // de escritura.
    //
    if (arg == "-") {
        oss = &cout;
    } else {
        ofs.open(arg.c_str(), ios::out);
        oss = &ofs;
    }

    // Verificamos que el stream este OK.
    //
    if (!oss->good()) {
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
    cmdl.parse(argc,argv);
    Complex CplxBuff1;
    Complex CplxBuff2;
    string line1;
    string line2;
    bool errors = false;
    int i=0,j=0;
    while(!ifs1.eof()&&!ifs2.eof()){ //mientras no haya llegado al end of file.
        getline(ifs1, line1);
        getline(ifs2, line2);
        stringstream  lstream1(line1);
        stringstream  lstream2(line2);
        while(lstream1>>CplxBuff1 && lstream2>>CplxBuff2){ // intento leer un Complex de cada archivo
            if(lstream1.good() && lstream2.good()){
                
                if(abs(CplxBuff1.GetRe()-CplxBuff2.GetRe())>(TOL*max(CplxBuff1.GetRe(),CplxBuff2.GetRe())) || abs(CplxBuff1.GetIm()-CplxBuff2.GetIm())>(TOL*max(CplxBuff1.GetIm(),CplxBuff2.GetIm()))){
                    ofs<<i<<" "<<j<<" "<<MSK_NOK<< endl;
                    errors=true;
                }
                j++;
            }
        }
        j=0;
        i++;
    }
    if (!errors) cout<<MSG_NERRORS<<endl;
    else cout<<MSG_ERRORS<<endl;
    ofs.close();
    ifs1.close();
    ifs2.close();
    return 0;
}