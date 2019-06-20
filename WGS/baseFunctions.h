//
//  baseFunctions.h
//  WGS
//
//  Created by Yao Zhou on 2018/12/4.
//  Copyright © 2018 Yao Zhou. All rights reserved.
//

#ifndef baseFunctions_h
#define baseFunctions_h
#define TWO_BIT_MASK (3)
#define BITS_PER_BYTE (8)
#define BIG_ENOUGH (1024)
#include <vector>

using namespace std;
typedef long int  lint ;

inline void  LogLackArg( string  flag )
{
    cerr << "\t\tLack Argument for [ -"<<flag<<" ]"<<endl;
}

/*
 inline string add_Asuffix ( string path )
 {
 string ext =path.substr(path.rfind('.') ==string::npos ? path.length() : path.rfind('.') + 1);
 if (ext != "gz")
 {
 path=path+".gz" ;
 }
 return path ;
 }
 */

inline string &  replace_all(string &  str,const  string &  old_Avalue,const string &  new_Avalue)
{
    while(true)   {
        string::size_type  pos(0);
        if(   (pos=str.find(old_Avalue))!=string::npos   )
            str.replace(pos,old_Avalue.length(),new_Avalue);
        else   break;
    }
    return   str;
}

inline void split(const string& str,vector<string>& tokens,  const string& delimiters = " ")
{
    tokens.clear();
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string::size_type pos     = str.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos)
    {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}
inline bool depthTest(vector<double>  dep, const double  a, const double  b,double minDepth,double maxDepth, double depthSD){
    bool pass = false;
    double sum = 0.0, mean, standardDeviation = 0.0;
    int len = dep.size();
    for(int i = 0; i < len ; ++i){
        sum += dep[i];
    }
    if(sum < minDepth || sum > maxDepth){
        return false;
    }
    mean = sum/len;
    for(int i = 0; i < len ; ++i){
        standardDeviation += pow(dep[i] - mean, 2);
    }
    standardDeviation = sqrt(standardDeviation/(len-1));
    if(standardDeviation > depthSD | standardDeviation < 1.1){
        return false;
    }
//    cout << "sum is: " << sum << endl;
//    cout << "a is: " << a << endl;
//    cout << "b is: " << b << endl;
//    
    if((a + b*sum)>standardDeviation) pass = true;
    return pass;
}
inline vector <double> rpois(const int& rep, const double& mean,int s){
    vector <double> result;
    default_random_engine generator(s);
//    generator.seed(time(0));
//    cout << "mean value is: " << (int)mean << endl;
    poisson_distribution<int> distribution(mean);
    for (int i = 0; i < rep; ++i){
        
        result.push_back(distribution(generator));
        
    }
//    cout << result[0] << endl;
    return result;
}


inline vector <double> sum_sd(vector<double> &v){
    vector <double> result;
    double sum = std::accumulate(v.begin(), v.end(),0.0);
//    cout << "sum is: " << sum << endl;
    double mean = sum / v.size();
    double sq_sum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / v.size() - mean * mean);
    result.push_back(sum);
    result.push_back(stdev);
    return result;
}
inline map <int,vector<double>> depth_min_max(const int& sampleSize, const double& mean){
    // step1: randomly generate a vector with total depth and sd;
    map <int,vector<double>> depth_sd;
    vector <double> de;
//    cout << "mean input is: " << mean << endl;
    for (int i = 0; i < 100000; ++i){
        de.clear();
        vector<double> rp = rpois(sampleSize, mean,rand());
        vector <double> re = sum_sd(rp);
        if(depth_sd.count((int)re[0])==1){
            de = depth_sd[(int)re[0]];
        }
//        cout << "sum is: " << re[0] << " ;sd is: " << re[1] << endl;
        de.push_back(re[1]);
        depth_sd[(int)re[0]] = de;
    }
    
    map <int,vector<double>>::iterator it;
    map <int,vector<double>> depth_min_max;
    de.clear();
//    cout << "depth_sd size is: " << depth_sd.size() << endl;
    for (it=depth_sd.begin();it != depth_sd.end();it++){
        de = it->second;
        double sd_min = *min_element(de.begin(),de.end());
        double sd_max = *max_element(de.begin(),de.end());
        vector <double> sdm(2);
        sdm[0] = sd_min;
        sdm[1] = sd_max;
        depth_min_max[it->first] = sdm;
//        cout << "total depth is: " << it->first << endl;
//        cout << "min,max sd is: " << sd_min <<"; " << sd_max << endl;
    }
//    cout << "size is: " << depth_min_max.size() << endl;
    return depth_min_max;
}

inline bool depthFilter(vector<double>& dep,map <int,vector<double>>& depth_min_max){
    bool pass = true;
    vector <double> snp_sum_sd = sum_sd(dep);
    int sum = snp_sum_sd[0];
    double sdv = snp_sum_sd[1];
    if(depth_min_max.count(sum) == 0) return false;
    vector <double> sim_sd_m = depth_min_max[sum];
    double max_sd = sim_sd_m[1]*1.1;
    double min_sd = sim_sd_m[0];
    if(sdv > max_sd || sdv < min_sd ) pass = false;
    return pass;
}

inline double string2Double(std::string const& s){
        std::istringstream iss(s);
        double value;
    if (!(iss >> value)) throw std::runtime_error("invalid double: " + s);
        return value;
}
inline double string2Doubleabs(std::string const& s){
    std::istringstream iss(s);
    double value;
    if (!(iss >> value)) throw std::runtime_error("invalid double: " + s);
    if(value<0) value = -value;
    return value;
}

inline double string2Doublepos(std::string const& s){
    std::istringstream iss(s);
    double value;
    if (!(iss >> value)) throw std::runtime_error("invalid double: " + s);
    if(value<0) value = 0;
    return value;
}

inline int string2Int(std::string const& s){
    std::istringstream iss(s);
    lint value;
    if (!(iss >> value)) throw std::runtime_error("invalid int");
    return value;
}
inline string Int2String(int const& s){
    std::string out_string;
    std::stringstream ss;
    if (!(ss << s)) throw std::runtime_error("invalid string");
    out_string = ss.str();
    return out_string;
}
inline string Double2String(double const& s){
    std::string out_string;
    std::stringstream ss;
    if (!(ss << s)) throw std::runtime_error("invalid string");
    out_string = ss.str();
    return out_string;
}
inline double avg ( vector<double>& v )
{
    double return_value = 0.0;
    int n = v.size();
    
    for ( int i=0; i < n; i++)
    {
        return_value += v[i];
    }
    
    return ( return_value / n);
}
set <string> getSubgroup(string& inFile){
    set<string> names ;
    igzstream inf ((inFile.c_str()),ifstream::in);
    if(inf.fail()) throw std::runtime_error("invalid subgroup files!");
    string line;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        names.insert(line);
    }
    cout << "subgroup file readed! " << names.size() << " samples!" << endl;
    inf.close();
    return names;
}
set <string> getSubgroup(string& inFile,int pos){
    set<string> names ;
    igzstream inf ((inFile.c_str()),ifstream::in);
    if(inf.fail()) throw std::runtime_error("invalid subgroup files!");
    string line;
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        split(line,ll,"\t");
        names.insert(ll[pos]);
    }
    cout << "subgroup file readed! " << names.size() << " samples!" << endl;
    inf.close();
    return names;
}
double MAF(vector <string> & ll, vector<int> na){
    double maf = 0;
    double a = 0;
    double A = 0;
    for (int i = 0; i < na.size(); ++i){
        if(ll[na[i]][0]=='0'&&ll[na[i]][2]=='0'){
            a += 2;
        }else if(ll[na[i]][0]=='0'&&ll[na[i]][2]=='1'){
            a++;
            A++;
        }else if(ll[na[i]][0]=='1'&&ll[na[i]][2]=='1'){
            A += 2;
        }else {
            continue;
        }
    }
    maf = a/(a+A);
    if (maf>0.5) maf = 1 - maf;
    return maf;
}

double MAF(vector <string> & ll){
    double maf = 0;
    double a = 0;
    double A = 0;
    for (int i = 9; i < ll.size(); ++i){
        if(ll[i][0]=='0' && ll[i][2]=='0'){
            a += 2;
        }else if(ll[i][0]=='0' && ll[i][2]=='1'){
            a++;
            A++;
        }else if(ll[i][0]=='1' && ll[i][2]=='1'){
            A += 2;
        }else {
            continue;
        }
    }
    maf = a/(a+A);
    if (maf>0.5) maf = 1 - maf;
    return maf;
}
double ref(vector <string> & ll){
    double maf = 0;
    double a = 0;
    double A = 0;
    for (int i = 9; i < ll.size(); ++i){
        if(ll[i][0] == '0' && ll[i][2] == '0'){
            a += 2;
        }else if(ll[i][0] == '0' && ll[i][2] == '1'){
            a++;
            A++;
        }else if(ll[i][0]=='1' && ll[i][2]=='1'){
            A += 2;
        }else {
            continue;
        }
    }
    maf = a/(a+A);
    return maf;
}
double ref(vector <string> & ll, vector<int> na){
    double maf = 0;
    double a = 0;
    double A = 0;
    for (int i = 0; i < na.size(); ++i){
        if(ll[na[i]][0]=='0'&&ll[na[i]][2]=='0'){
            a += 2;
        }else if(ll[na[i]][0]=='0'&&ll[na[i]][2]=='1'){
            a++;
            A++;
        }else if(ll[na[i]][0]=='1'&&ll[na[i]][2]=='1'){
            A += 2;
        }else {
            continue;
        }
    }
    maf = a/(a+A);
    return maf;
}
vector <int> getPos(vector <string> & ll, set<string> na){
    vector<int> pos;
    for(int i = 9; i<ll.size();++i){
        if(na.count(ll[i])==1) pos.push_back(i);
    }
    return pos;
}
vector <int> getPos(vector <string> & ll, set<string> na,int start){
    vector<int> pos;
    for(int i = start; i<ll.size();++i){
        if(na.count(ll[i])==1) pos.push_back(i);
    }
    return pos;
}
int Random(int m, int n)
{
    int pos, dis;
//    srand((int)time(NULL));
    if(m == n)
    {
        return m;
    }
    else if(m > n)
    {
        pos = n;
        dis = m - n + 1;
        return rand() % dis + pos;
    }
    else
    {
        pos = m;
        dis = n - m + 1;
        return rand() % dis + pos;
    }
}
inline vector <int> sample(int rep,  int start,int end,int s){
    vector <int> result;
    default_random_engine generator(s);
    for (int i = 0; i < rep; ++i){
        result.push_back(Random(start, end));
        
    }
    //    cout << result[0] << endl;
    return result;
}
inline set<int> Sample(int rep,  int start,int end,int s){
    set <int> result;
    default_random_engine generator(s);
    for (int i = 0; i < rep*10; ++i){
        result.insert(Random(start, end));
        if(result.size()==rep) break;
    }
    //    cout << result[0] << endl;
    return result;
}

int getChr(string & file){
    vector<string> ll1,ll2;
    ll1.clear();
    split(file,ll1,".");
    split(ll1[0],ll2,"r");
    return string2Int(ll2[ll2.size()-1]);
}
string reverse_complementary(string & sequence){
    string rc = "";
    for (int i = sequence.length()-1; i > -1;--i){
        if(sequence[i]=='A' ||sequence[i]=='a' ){
            rc.append("T");
        }else if (sequence[i]=='T' ||sequence[i]=='t' ){
            rc.append("A");
        }else if (sequence[i]=='G' ||sequence[i]=='g' ){
            rc.append("C");
        }else if (sequence[i]=='C' ||sequence[i]=='c' ){
            rc.append("G");
        }else if (sequence[i]=='N' ||sequence[i]=='n' ){
            rc.append("N");
        }else {
            rc.append(sequence.substr(i,1));
        }
    }
    return rc;
}
bool increase (int i,int j) { return (i<j); }
bool decrease (int i,int j) { return (i>j); }


uint64_t encode(string original) {
    
    size_t length = original.length();
    
//    assert(length * 2 == sizeof(uint64_t) * BITS_PER_BYTE);
    uint64_t result = 0;
    
    for (size_t i = 0; i < length; i++) {
        result = (result << 2) | ((original[i] >> 1) & TWO_BIT_MASK);
    }
    
    return result;
}

void decode(uint64_t encoded, char *decoded, bool rna_flag) {
    
    int i = sizeof(uint64_t) * BITS_PER_BYTE / 2;
    
    for (decoded[i--] = '\0'; i >= 0; i--, encoded >>= 2) {
        
        unsigned char byte = encoded & TWO_BIT_MASK;
        
        if (byte == 2) {
            byte = (rna_flag) ? 'U' : 'T';
        } else {
            byte = 'A' | (byte << 1);
        }
        
        decoded[i] = byte;
    }
}
void parseFeatures(){
    
}

double radian (double d){
    const double PI  =3.141592653589793238463;
    return d * PI / 180.0;
}
#endif /* baseFunctions_h */
