//
//  FileFunctions.h
//  WGS
//
//  Created by Yao Zhou on 2018/12/4.
//  Copyright © 2018 Yao Zhou. All rights reserved.
//

#ifndef FileFunctions_h
#define FileFunctions_h
using namespace std;
//void nrerror(char error_text[]);
int Read_VCF_IN(parameter *para, vcf *inVCF)
{
    
    igzstream VCFIN ((para->inFile).c_str(),ifstream::in);
    
    if (VCFIN.fail())
    {
        cerr << "open VCF File IN File error: " << (para->inFile) << endl;
        return  0;
    }
        
    vector<string> inf ;
    vector<string> header;
    
    // read header
    while(!VCFIN.eof()){
        string  line ;
        getline(VCFIN,line);
        if (line.length()<=0 )  {
            continue  ;
        }else if ( line[0] == '#' && line[1] == '#' )  {
            header.push_back(line);
            continue  ;
        }else if ( line[0] == '#' && line[1] != '#' ){
            header.push_back(line);
            inf.clear();
            split(line,inf,"\t");
            if  ( inf[0]  != "#CHROM"){
                continue  ;
            }
            break ;
        }else if ( line[0] != '#' && line[1] != '#' ){
            cerr<<"wrong Line : "<<line<<endl;
            cerr<<"VCF Header same thing wrong, can find sample info before site info"<<endl;
            cerr<<"VCF Header sample info Flag : [  #CHROM  ] "<<endl;
            return  0;
            break;
        }
    }
    int BadSite=0 ;
    int Asample=inf.size();
    int SampleNum=(Asample-9);
    
    // creat map for interested SNPs
    vector<string> Alt ;
    vector<string> Btmp  ;
    int  Base_len ;
    long int Site ;
    int Het_count=0;
    int Miss_count=0;
    int BaseConut=0;
    char best_base='N';
    char sed_base='N';
    int Max=0;
    int SeD=0;
    map <char,int>  :: iterator it ;
    int ERA=0;
    vector<char>  genotype ;
    vector<BaseType>  genotypeVE ;
    
//    while(!VCFIN.eof()){
//        string  line ;
//        getline(VCFIN,line);
//        if (line.length()<=0)  { continue  ; }
//        istringstream isoneLine (line,istringstream::in);
//        for (int iik=0 ; iik<Asample ; iik++){
//            isoneLine >> inf[iik];
//        }
//        Base_len=inf[3].length();
//        Alt.clear();
//        split(inf[4],Alt,",");
//        for (int ii=0 ; ii<Alt.size() ;ii++){
//            if (Alt[ii].length()>Base_len){
//                Base_len=Alt[ii].length();
//            }
//        }
//        if (Base_len>1){
//            BadIndelSite++;
//            continue ;
//        }
//        map <char,int > Count ;
//        Het_count=0;
//        Miss_count=0;
//        for (int jj=9 ; jj< Asample ;jj++ ){
//            Btmp.clear();
//            split(inf[jj], Btmp,":");
//            string Genotype=Btmp[0];
//            if ( Genotype[0] == '.' ){
//                Miss_count++ ;
//            } else{
//              if  (Genotype[0] != Genotype[2] )
//                        {
//                            Het_count++;
//                        }
//                        Count[Genotype[0]]++;
//                        Count[Genotype[2]]++;
//                    }
//                }
//
//                if ( ( (Miss_count*1.0/SampleNum)  >(para_18->Miss)  )  )
//                {
//                    continue ;
//                }
//
//                if ( ( (Het_count*1.0/SampleNum)  >(para_18->Het) )  )
//                {
//                    continue ;
//                }
//
//                BaseConut=0;
//                best_base='N';
//                sed_base='N';
//                Max=0;
//                SeD=0;
//
//                for ( it=Count.begin(); it!=Count.end(); it++ )
//                {
//                    if ( (it->first ) == 'N' )
//                    {
//                        continue ;
//                    }
//                    else if ((it->second)  > Max )
//                    {
//                        SeD=Max;
//                        sed_base=best_base;
//                        Max=(it->second);
//                        best_base=it->first;
//                    }
//                    else if ( (it->second)  >= SeD )
//                    {
//                        SeD=(it->second);
//                        sed_base=it->first;
//                    }
//                    BaseConut++;
//                }
//                if (BaseConut==1 || BaseConut >2 )
//                {
//                    BadSite++;
//                    continue ;
//                }
//
//                if ( (SeD*1.0/(SeD+Max))  < (para_18->MAF) )
//                {
//                    continue ;
//                }
//
//                genotype.clear();
//
//                for (int jj=9 ; jj< Asample ;jj++ )
//                {
//                    Btmp.clear();
//                    split(inf[jj], Btmp,":");
//                    string Genotype=Btmp[0];
//                    if (  Genotype[0] == '.' )
//                    {
//                        genotype.push_back('N');
//                        genotype.push_back('N');
//                    }
//                    else
//                    {
//                        if  (Genotype[0] != Genotype[2] )
//                        {
//                            genotype.push_back(best_base);
//                            genotype.push_back(sed_base);
//                        }
//                        else
//                        {
//                            genotype.push_back(Genotype[0]);
//                            genotype.push_back(Genotype[2]);
//                        }
//                    }
//                }
//
//
//
//                genotypeVE.clear();
//
//                BaseType  TypeA;
//
//                ERA=genotype.size();
//
//                for (int hh=0 ; hh<ERA ;hh++)
//                {
//
//                    if (genotype[hh] == best_base  )
//                    {
//                        TypeA.Value=0;
//                    }
//                    else if (genotype[hh] == sed_base )
//                    {
//                        TypeA.Value=1;
//                    }
//                    else
//                    {
//                        TypeA.Value=2;
//                    }
//                    genotypeVE.push_back(TypeA);
//                }
//
//
//
//
//
//                istringstream isone (inf[1],istringstream::in);
//                isone>> Site ;
//
//
//                map <string,map <int, vector <BaseType> > >  :: iterator itSNP=SNPList.find(inf[0]);
//
//                if (itSNP == SNPList.end())
//                {
//                    map <int, vector <BaseType> > DD;
//                    DD[Site]=genotypeVE;
//                    SNPList.insert(map <string,map <int,vector <BaseType> > > ::value_type(inf[0],DD));
//                    Flag_for_pro++;
//                }
//                else
//                {
//                    (itSNP->second).insert(map <int, vector <BaseType> >  :: value_type(Site,genotypeVE)) ;
//                    Flag_for_pro++;
//                }
//            }
//
//
//
//        }
//        else
//        {
//
//            string OUT_VCFTMP=(para->InStr2)+".vcf.filter.gz";
//            ogzstream OUTVCFFF ((OUT_VCFTMP).c_str());
//
//            while(!VCFIN.eof())
//            {
//                string  line ;
//                getline(VCFIN,line);
//                if (line.length()<=0 || line[0] == '#' )  { continue  ; }
//                int Site ;
//                //inf.clear();            split(line,inf," \t");
//                istringstream isoneLine (line,istringstream::in);
//                for (int iik=0 ; iik<Asample ; iik++)
//                {
//                    isoneLine>>inf[iik];
//                }
//                Base_len=inf[3].length();
//                Alt.clear();
//                split(inf[4],Alt,",");
//                for (int ii=0 ; ii<Alt.size() ;ii++)
//                {
//                    if (Alt[ii].length()>Base_len)
//                    {
//                        Base_len=Alt[ii].length();
//                    }
//                }
//
//                if (Base_len>1)
//                {
//                    BadIndelSite++;
//                    continue ;
//                }
//
//                map <char,int > Count;
//                Het_count=0;
//                Miss_count=0;
//
//                for (int jj=9 ; jj< Asample ;jj++)
//                {
//                    Btmp.clear();
//                    split(inf[jj], Btmp,":");
//                    string Genotype=Btmp[0];
//                    if (  Genotype[0]  == '.' )
//                    {
//                        Miss_count++ ;
//                    }
//                    else
//                    {
//                        if  (Genotype[0] != Genotype[2] )
//                        {
//                            Het_count++;
//                        }
//                        Count[Genotype[0]]++;
//                        Count[Genotype[2]]++;
//                    }
//                }
//
//                //            int SampleNum=(Asample-9);
//                if ( ( (Miss_count*1.0/SampleNum)  >(para_18->Miss)  )  )
//                {
//                    continue ;
//                }
//
//                if ( ( (Het_count*1.0/SampleNum)  >(para_18->Het) ) )
//                {
//                    continue ;
//                }
//
//                BaseConut=0;
//                best_base='N';
//                sed_base='N';
//                Max=0;
//                SeD=0;
//
//                for ( it=Count.begin(); it!=Count.end(); it++ )
//                {
//                    if ( (it->first ) == 'N' )
//                    {
//                        continue ;
//                    }
//                    else if ((it->second)  > Max )
//                    {
//                        SeD=Max;
//                        sed_base=best_base;
//                        Max=(it->second);
//                        best_base=it->first;
//                    }
//                    else if ( (it->second)  >= SeD )
//                    {
//                        SeD=(it->second);
//                        sed_base=it->first;
//                    }
//                    BaseConut++;
//                }
//                if (BaseConut==1 || BaseConut >2 )
//                {
//                    BadSite++;
//                    continue ;
//                }
//
//                //if ( (  (1-(Max*1.0/(SeD+Max)))  < (para_18->MAF) )  )
//                if ( (SeD*1.0/(SeD+Max))  < (para_18->MAF) )
//                {
//                    continue ;
//                }
//
//
//                genotype.clear();
//                for (int jj=9 ; jj< Asample ;jj++ )
//                {
//                    Btmp.clear();
//                    split(inf[jj], Btmp,":");
//                    string Genotype=Btmp[0];
//                    if (  Genotype[0] == '.' )
//                    {
//                        genotype.push_back('N');
//                        genotype.push_back('N');
//                    }
//                    else
//                    {
//                        if  (Genotype[0] != Genotype[2] )
//                        {
//                            genotype.push_back(best_base);
//                            genotype.push_back(sed_base);
//                        }
//                        else
//                        {
//                            genotype.push_back(Genotype[0]);
//                            genotype.push_back(Genotype[2]);
//                        }
//                    }
//                }
//
//
//
//                //vector<BaseType>  genotypeVE ;
//                genotypeVE.clear();
//
//                BaseType  TypeA;
//
//                ERA=genotype.size();
//                for (int hh=0 ; hh<ERA ;hh++)
//                {
//                    if (genotype[hh] == best_base  )
//                    {
//                        TypeA.Value=0;
//                    }
//                    else if (genotype[hh] == sed_base )
//                    {
//                        TypeA.Value=1;
//                    }
//                    else
//                    {
//                        TypeA.Value=2;
//                    }
//                    genotypeVE.push_back(TypeA);
//                }
//
//
//                istringstream isone (inf[1],istringstream::in);
//                isone>> Site ;
//
//
//                map <string,map <int, vector <BaseType> > >  :: iterator itSNP=SNPList.find(inf[0]);
//                if (itSNP == SNPList.end())
//                {
//                    map <int, vector <BaseType> > DD;
//                    DD[Site]=genotypeVE;
//                    SNPList.insert(map <string,map <int,vector <BaseType> > > ::value_type(inf[0],DD));
//                    Flag_for_pro++;
//                }
//                else
//                {
//                    (itSNP->second).insert(map <int, vector <BaseType> >  :: value_type(Site,genotypeVE)) ;
//                    Flag_for_pro++;
//                }
//
//                OUTVCFFF<<line<<"\n";
//
//            }
//
//
//            OUTVCFFF.close();
//
//        }
//        VCFIN.close();
//
//        if(BadIndelSite!=0)
//        {
//            cout<<"warning skip Indel site, there are total skip Indel sites number is : "<<BadIndelSite<<endl;
//        }
//        if (BadSite!=0)
//        {
//            cout<<"Warning skip non bi-allelic(Singleton/ThreeMulti allelic) site, and total skip allelic sites number is :"<<BadSite<<endl;
//        }

        return 1;
}

int Read_depth_IN(parameter *para){
    igzstream inf ((para->inFile).c_str(),ifstream::in);
    if (inf.fail())
    {
        cerr << "open depth File IN File error: " << (para->inFile) << endl;
        return  0;
    }
   
    string outDepth =(para -> outFile);
    ofstream ouf ((outDepth).c_str());
    if((!ouf.good())){
        cerr << "open OUT File error: " << outDepth << endl;
        return  0;
    }
    vector<string> ll ;
    string line;
    vector<string> ge ;
    while(!inf.eof()){
        getline(inf,line);
        if (line.length() < 1  ) continue;
        if(line[0] == '#') continue;
        ll.clear();
        split(line,ll," \t");
        vector<string> l1;
        int sum = 0;
        for (int i = 9; i < ll.size();i++){
            l1.clear();
            split(ll[i],l1,":");
            ge.clear();
            if(l1[1][0] == '.') continue;
            split(l1[1],ge,",");
            
//            cout << ge[0] << endl;
            sum += string2Int(ge[0]);
            sum += string2Int(ge[1]);
        }
        ouf << ll[0] << "\t" << ll[1] << "\t" << sum << "\n";
    }
    ouf.close();
    return 1;
}
int DepthFilter(parameter *para){
    string input1 = (para->inFile);
    igzstream inf (input1.c_str(),ifstream::in);
    string outFile =(para -> outFile);
    ofstream  ouf((outFile).c_str());
    string line;
    vector < string >  ll;
    int minDepth = (para -> minDepth) -1 ;
    int maxDepth = (para -> maxDepth) + 1;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0]== '#') {
            ouf << line << "\n";
            continue;
        }
        split(line,ll," \t");
        int sum = 0;
        vector<string> dp;
        for (int i = 9; i < ll.size(); i++){
            split(ll[i],dp,":");
//            cout << dp[2] << endl;
//            if(isdigit(dp[2][0]) != 0) continue;
            if(dp[2] == ".") continue;
            sum += string2Int(dp[2]);
        }
        if(sum > minDepth & sum < maxDepth){
            ouf << line << "\n";
        }
    }
    ouf.close();
    return 0;
}
int DepthFilterDP(parameter *para){
    string input = (para->inFile);
    igzstream inf (input.c_str(),ifstream::in);
    string outFile =(para -> outFile);
    ofstream  ouf((outFile).c_str());
    string line;
    vector < string >  ll;
    int minDepth = (para -> minDepth) -1 ;
    int maxDepth = (para -> maxDepth) + 1;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0]== '#') {
            ouf << line << "\n";
            continue;
        }
        split(line,ll," \t");
        int sum = 0;
        vector<string> dp;
        for (int i = 9; i < ll.size(); i++){
            split(ll[i],dp,":");
            if(dp[1] == ".") continue;
            sum += string2Int(dp[1]);
        }
        if(sum > minDepth & sum < maxDepth){
            ouf << line << "\n";
        }
    }
    ouf.close();
    return 0;
}
int inDel_len(parameter *para){
    string input = (para->inFile);
    igzstream inf (input.c_str(),ifstream::in);
    string outFile =(para -> outFile);
    ofstream  ouf((outFile).c_str());
    string line;
    vector < string >  ll;
    int len = (para->maxLength);
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0]== '#') {
            ouf << line << "\n";
            continue;
        }
        split(line,ll," \t");
        if (ll[3].length() > len || ll[4].length() > len ){
            continue;
        }
        ouf << line << "\n";
    }
    return 0;
    
}
int SVfilter_reads(parameter *para){
    string input = (para->inFile);
    igzstream inf (input.c_str(),ifstream::in);
    string outFile =(para -> outFile);
    ofstream  ouf((outFile).c_str());
    string line;
    vector < string >  ll;
    // LEN
    //
    set<string> cs;
    cs.insert("DUP");
    cs.insert("DUP:TANDEM");
    cs.insert("DUP:INT");
    cs.insert("INS");
    cs.insert("CNV");
    cs.insert("DEL");
    int maxLength = (para->maxLength);
    int sum = 0, passed = 0;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0]== '#') {
            ouf << line << "\n";
            continue;
        }
        sum++;
        
        split(line,ll,"\t");
        
        if (ll[6] != "PASS") continue;
        string info = ll[7];
        string gt = ll[9];
        string format = ll[8];
        ll.clear();
        split(info,ll,";");
        string type;
        int len = 100;
        if (format == "CN"){
            if (ll[ll.size()-1] == "SHADOWED") continue;
            for (int i = 0; i < ll.size(); i++){
                vector<string> tmp;
                if (ll[i].substr(0,5)=="SVLEN"){
                    string svlen = ll[i];
                    split(svlen,tmp,"=");
                    len = abs(string2Int(tmp[1]));
                }
                if (len>50){
                    ouf << line << "\n";
                }
            }
            continue;
        }
        for (int i = 0; i < ll.size(); i++){
            vector<string> tmp;
            if (ll[i].substr(0,5)=="SVLEN"){
                string svlen = ll[i];
                split(svlen,tmp,"=");
                len = abs(string2Int(tmp[1]));
            }else if (ll[i].substr(0,6)=="SVTYPE"){
                string svlen = ll[i];
                split(svlen,tmp,"=");
                type = tmp[1];
            }
        }
        split(format,ll,":");
        int dpp =1;
        for (int i =0; i < ll.size(); i++){
            if (ll[i] == "DP") dpp = i;
        }
        split(gt,ll,":");
        
        int dp = 10;
        if (ll[1] == "."){
            dp = 10;
        }else{
            dp = string2Int(ll[dpp]);
        }
        if (dp < 4) continue;
        
        if (type == "DEL"){
            if ( len > 50 && len < 100000){
                ouf << line << "\n";
                passed ++;
            }
        }else if (cs.count(type) == 1){
            if ( len > 50 && len < maxLength){
                ouf << line << "\n";
                passed ++;
            }
        }else{
            if ( len > 50 && len < 10000000){
                ouf << line << "\n";
                passed ++;
            }
        }
        
    }
    ouf.close();
    return 0;
}
int SVfilter_long(parameter *para){
    string input = (para->inFile);
    igzstream inf (input.c_str(),ifstream::in);
    string outFile =(para -> outFile);
    ofstream  ouf((outFile).c_str());
    string line;
    vector < string >  ll;
    // LEN
    //
    set<string> cs;
    cs.insert("DUP");
    cs.insert("DUP:TANDEM");
    cs.insert("DUP:INT");
    cs.insert("INS");
    cs.insert("CNV");
    cs.insert("DEL");
    int maxLength = (para->maxLength);
    int sum = 0, passed = 0;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0]== '#') {
            ouf << line << "\n";
            continue;
        }
        sum++;
        
        split(line,ll,"\t");
        
        if (ll[6] != "PASS") continue;
        string info = ll[7];
        string gt = ll[9];
        string format = ll[8];
        ll.clear();
        split(info,ll,";");
        string type;
        int len = 100;
        if (format == "CN"){
            if (ll[ll.size()-1] == "SHADOWED") continue;
            for (int i = 0; i < ll.size(); i++){
                vector<string> tmp;
                if (ll[i].substr(0,5)=="SVLEN"){
                    string svlen = ll[i];
                    split(svlen,tmp,"=");
                    len = abs(string2Int(tmp[1]));
                }
                if (len>50){
//                    ouf << line << "\n";
                }
            }
            continue;
        }
        for (int i = 0; i < ll.size(); i++){
            vector<string> tmp;
            if (ll[i].substr(0,5)=="SVLEN"){
                string svlen = ll[i];
                split(svlen,tmp,"=");
                len = abs(string2Int(tmp[1]));
            }else if (ll[i].substr(0,6)=="SVTYPE"){
                string svlen = ll[i];
                split(svlen,tmp,"=");
                type = tmp[1];
            }
        }
        
        
        if (type == "INS"){
            if ( len > 20000 && len < 100000){
                ouf << line << "\n";
                passed ++;
            }
        }
        
    }
    ouf.close();
    return 0;
}
int mergeSVs(parameter *para){
    string input = (para->inFile);
    string input2 = (para->inFile2);
    igzstream inf (input.c_str(),ifstream::in);
    igzstream inf2 (input2.c_str(),ifstream::in);
    string outFile =(para -> outFile);
    ofstream  ouf((outFile).c_str());
    string line;
    vector < string >  ll;
    set<char> bases;
    bases.insert('A');
    bases.insert('T');
    bases.insert('G');
    bases.insert('C');
    bases.insert('N');
   
    while (!inf.eof()){
        getline(inf,line);
        if (line.length() < 1 ) continue;
        bool write = true;
        if (line.substr(0,2) == "##") {
            ouf << line << "\n";
        }else if (line.substr(0,2) == "#C"){
            split(line,ll,"\t");
            ouf << ll[0];
            for (int i = 1; i< 10; i++){
                ouf << "\t" << ll[i];
            }
            ouf << "\n";
        }else{
            split(line,ll,"\t");
            string ref = ll[3];
            string alt = ll[4];
            ref.append(alt);
            for (int i = 0; i < ref.length(); i++){
                if (bases.count(ref[i]) == 0) {
                    write = false;
                }
            }
            if(write){
                split(line,ll,"\t");
                ouf << ll[0];
                for (int i = 1; i< 10; i++){
                    ouf << "\t" << ll[i];
                }
                ouf << "\n";
            }
        }
    }
    while (!inf2.eof()){
        getline(inf2,line);
        if (line.length() < 1 ) continue;
        if(line[0] == '#') continue;
        ouf << line << "\n";
    }
    ouf.close();
    return 0;
}
int svmu(parameter *para){
    string input = (para->inFile);
    igzstream inf (input.c_str(),ifstream::in);
    string outFile =(para -> outFile);
    ofstream  ouf((outFile).c_str());
    string line;
    vector < string >  ll;
//    cout << "runing.." <<endl;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if (line[0] == 'R') continue;
        split(line,ll,"\t");
        if (ll.size() != 11) continue;
        if(string2Int(ll[1]) > string2Int(ll[2])) {
            string tmp = ll[2];
            ll[2] = ll[1];
            ll[1] = tmp;
        }
        ouf << ll[0];
        for(int i = 1; i< ll.size(); i++){
            ouf << "\t" << ll[i];
        }
        ouf << "\n";
    }
    ouf.close();
    return 0;
}
int bed2vcf(parameter *para){
    string input = (para->inFile);
    string input2 = (para->inFile2); // reference fasta
    string input3 = (para->inFile3); // query fasta
    igzstream inf (input.c_str(),ifstream::in);
    igzstream inf2 (input2.c_str(),ifstream::in);
    igzstream inf3 (input3.c_str(),ifstream::in);
    string outFile =(para -> outFile);
    ofstream  ouf((outFile).c_str());
    string line;
    vector < string >  ll;
    map<string,string> ref;
    map<string,string> query;
    string chr = "";
    string seq = "";
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        if(line[0] == '>'){
            if (seq != "") {
                ref.insert(pair<string,string>(chr,seq));
            }
            chr = line.substr(1,line.length()-1);
            seq="";
            continue;
        }
        seq.append(line);
    }
    ref.insert(pair<string,string>(chr,seq));
    cout << "Reference genome readed!, chromosome number is:\t" << ref.size() << endl;
    chr = "";
    seq = "";
    while(!inf3.eof()){
        getline(inf3,line);
        if(line.length() < 1) continue;
        if(line[0] == '>'){
            if (seq != "") {
                query.insert(pair<string,string>(chr,seq));
            }
            chr = line.substr(1,line.length()-1);
            seq = "";
            continue;
        }
        seq.append(line);
    }
    query.insert(pair<string,string>(chr,seq));
    cout << "Query genome readed!, chromosome number is:\t" << query.size() << endl;
    ouf << "##fileformat=VCFv4.2\n##source=WGS\n##ALT=<ID=DEL,Description=\"Deletion\">\n##ALT=<ID=DUP,Description=\"Duplication\">\n##ALT=<ID=INV,Description=\"Inversion\">\n##ALT=<ID=BND,Description=\"Translocation\">\n##ALT=<ID=INS,Description=\"Insertion\">\n##INFO=<ID=CHR2,Number=1,Type=String,Description=\"Chromosome for END coordinate in case of a translocation\">\n##INFO=<ID=END,Number=1,Type=Integer,Description=\"End position of the structural variant\">\n##INFO=<ID=IMPRECISE,Number=0,Type=Flag,Description=\"Imprecise structural variation\">\n##INFO=<ID=PRECISE,Number=0,Type=Flag,Description=\"Precise structural variation\">\n##INFO=<ID=SVLEN,Number=1,Type=Float,Description=\"Length of the SV\">\n##INFO=<ID=SVMETHOD,Number=1,Type=String,Description=\"Vector of samples supporting the SV.\">\n##INFO=<ID=SVTYPE,Number=1,Type=String,Description=\"Type of the SV.\">\n##INFO=<ID=STRANDS,Number=1,Type=String,Description=\"Indicating the direction of the reads with respect to the type and breakpoint.\">##FORMAT=<ID=GT,Number=1,Type=String,Description=\"Genotype\">\n#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\tFORMAT\tSample\n" ;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '#') continue;
        split(line,ll,"\t");
        string qinf = ll[9];
        vector<string> tmp;
        split(qinf,tmp,":-");
        string info="IMPRECISE;SVTYPE=";
//        cout << line << endl;
        string kr = ll[0];
        string kq = tmp[0];
//        cout << qinf << endl;
        int ks = string2Int(ll[1])-1;
        int ke = string2Int(ll[2]);
        int rs = string2Int(tmp[1])-1;
        int re = string2Int(tmp[2]);
//        cout << "test1.." << endl;
        string seqr = ref[kr].substr(ks,ke-ks) ;
        string seqq = query[kq].substr(rs,re-rs);
//        if(tmp[2] == "-") {
//            string seqqr = reverse_complementary(seqq);
//            seqq = seqqr;
//        }
        string ref;
        string alt;
        if(ll[6] == "Insertion"){
            info.append("INS;END=");
            info.append(ll[2]);
            info.append(";SVLEN=");
            info.append(ll[4]);
            ref = "N";
            alt = seqq;
        }else if (ll[6] == "Deletion"){
            info.append("DEL;END=");
            info.append(ll[2]);
            info.append(";SVLEN=-");
            info.append(ll[4]);
            ref = seqr;
            alt = "N";
        }else{
            continue;
        }
        int len = string2Int(ll[4]);
        if (len < 51 || len > 100000) continue;
        ouf << ll[0] << "\t";
        ouf << string2Int(ll[1])  << "\t";
        ouf << ll[3] << "\t";
        ouf << ref << "\t";
        ouf << alt << "\t";
        ouf << "." << "\t";
        ouf << "PASS" << "\t";
        ouf << info << "\t";
        ouf << "GT\t";
        ouf << "./.\n";
    }
    ouf.close();
    return 0;
}
int calTotalDP(parameter *para){
    string input = (para->inFile);
    igzstream inf (input.c_str(),ifstream::in);
    string outFile =(para -> outFile);
    ofstream  ouf((outFile).c_str());
    string line;
    vector < string >  ll;
    
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0]== '#') {
            ouf << line << "\n";
            continue;
        }
        split(line,ll," \t");
        int sum = 0;
        vector<string> dp;
        for (int i = 9; i < ll.size(); i++){
            split(ll[i],dp,":");
            if(dp[1] == ".") continue;
            sum += string2Int(dp[1]);
        }
        ouf << ll[0] << "\t" << ll[1] << "\t" << sum << "\n";
    }
    ouf.close();
    return 0;
}
int modifyGenome(parameter *para){
    string input1 = (para->inFile);
    igzstream inf (input1.c_str(),ifstream::in);
    string outFile =(para -> outFile);
    ofstream  ouf((outFile).c_str());
    string line;
    
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '>') {
            if(string2Int(line.substr(1,line.length()-1)) < 10){
                ouf <<  ">chr0" << line.substr(1,1) << "\n";
            }else{
                 ouf <<  ">chr" << line.substr(1,2) << "\n";
            }
           
        }else{
            ouf << line << "\n";
        }
    }
    ouf.close();
    return 0;
}
int modifyPAF(parameter *para){
    string input1 = (para->inFile);
    igzstream inf (input1.c_str(),ifstream::in);
    string outFile =(para -> outFile);
    ofstream  ouf((outFile).c_str());
    string line;
    map<string,string> chr;
    chr.insert(pair<string,string>("chr0","chr00"));
    chr.insert(pair<string,string>("chr1","chr01"));
    chr.insert(pair<string,string>("chr2","chr02"));
    chr.insert(pair<string,string>("chr3","chr03"));
    chr.insert(pair<string,string>("chr4","chr04"));
    chr.insert(pair<string,string>("chr5","chr05"));
    chr.insert(pair<string,string>("chr6","chr06"));
    chr.insert(pair<string,string>("chr7","chr07"));
    chr.insert(pair<string,string>("chr8","chr08"));
    chr.insert(pair<string,string>("chr9","chr09"));
    chr.insert(pair<string,string>("chr10","chr10"));
    chr.insert(pair<string,string>("chr11","chr11"));
    chr.insert(pair<string,string>("chr12","chr12"));
    
//    chr.insert(pair<string,string>("Chr00","seq00"));
//    chr.insert(pair<string,string>("Chr01","seq01"));
//    chr.insert(pair<string,string>("Chr02","seq02"));
//    chr.insert(pair<string,string>("Chr03","seq03"));
//    chr.insert(pair<string,string>("Chr04","seq04"));
//    chr.insert(pair<string,string>("Chr05","seq05"));
//    chr.insert(pair<string,string>("Chr06","seq06"));
//    chr.insert(pair<string,string>("Chr07","seq07"));
//    chr.insert(pair<string,string>("Chr08","seq08"));
//    chr.insert(pair<string,string>("Chr09","seq09"));
//    chr.insert(pair<string,string>("Chr10","seq10"));
//    chr.insert(pair<string,string>("Chr11","seq11"));
//    chr.insert(pair<string,string>("Chr12","seq12"));
    
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        string c = chr[ll[5]];
//        string c1 = chr[ll[0]];
        ll[5] = c;
//        ll[0] = c1;
        ouf << ll[0];
        for (int i = 1; i < ll.size(); ++i){
            ouf << "\t" << ll[i] ;
        }
        ouf << "\n";
    }
    ouf.close();
    
    return 0;
}
int C2VCF(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    igzstream inf (input1.c_str(),ifstream::in);
    igzstream inf2 (input2.c_str(),ifstream::in);
    string outFile =(para -> outFile);
    ofstream  ouf((outFile).c_str());
    string line;
    set<string> pos;
    vector<string> ll;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        if(line[0] == '#') continue;
        ll.clear();
        split(line,ll,"\t");
        pos.insert(ll[1]);
    }
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        if(pos.count(ll[1]) == 1) {
            ouf << line << "\t" << "red" << "\n";
        }else{
            ouf << line << "\t" << "gray" << "\n";
        }
    }
    ouf.close();
    
    return 0;
}
int toFastaRef(parameter *para){
    string input1 = (para->inFile); //vcf file
    igzstream inf (input1.c_str(),ifstream::in);
    string input2 = (para->inFile2); // genome file
    igzstream inf2 (input2.c_str(),ifstream::in);
    string input3 = (para->inFile3); // synteny site file
    igzstream inf3 (input3.c_str(),ifstream::in);
    map<string,string> snp;
    string outFile =(para -> outFile);
    ofstream  ouf((outFile).c_str());
    string line;
    vector < string >  ll;
    string chr = (para->chr);
    
// store the vcf site
    string var="";
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[1] == 'C'){
            ouf << line << "\n";
            ll.clear();
            split(line,ll,"\t");
            var=".\t.\t.\tGT:AD:GL";
            for (int i = 9; i < ll.size();++i){
                var = var + "\t" + "0/0:10:100,0";
            }
            continue;
        }
        if(line[0] == '#'){
            ouf << line << "\n";
            continue;
        }
        ll.clear();
        split(line,ll,"\t");
        if(ll[0] != chr) continue;
        snp.insert(pair<string,string>(ll[1],line));
    }
    cout << "vcf parsed!" << endl;
// store the genome
    bool write = false;
    string seq ="";
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1 ) continue;
        if(line[0]=='>'){
            string c = ">" + chr;
            if(line == c){
                write = true;
            }else{
                write = false;
            }
            continue;
        }
        if(write){
            seq.append(line);
        }else{
            continue;
        }
    }
    cout << "genome file parsed!" << endl;
    while(!inf3.eof()){
        getline(inf3,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        if(ll[0] != chr) continue;
        if(snp.count(ll[1]) == 1){
            ouf << snp[ll[1]] << "\n";
        }else{
            ouf << chr << "\t" << ll[1]  << "\t.\t" << seq.substr(string2Int(ll[1])-1,1)
            << "\t" << seq.substr(string2Int(ll[1])-1,1) << "\t" << var << "\n";
        }
    }
    ouf.close();
    return 0;
}
int getsynteny(parameter *para){
    igzstream inf ((para->inFile).c_str(),ifstream::in);
    string outDepth =(para -> outFile);
    ogzstream ouf ((outDepth).c_str());
    set<string> synteny;
    vector<string> ll ;
    string line;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1 ) continue;
        ll.clear();
        split(line,ll," \t");
        if(string2Int(ll[2]) == 1 | string2Int(ll[2]) == 2){
            ouf << line << "\n";
        }
    }
    ouf.close();
    return 1;
}

int divided2synteny(parameter *para){
    igzstream inf ((para->inFile).c_str(),ifstream::in);
    igzstream inf2 ((para->inFile2).c_str(),ifstream::in);
    string outDepth =(para -> outFile);
    ogzstream ouf1 ((outDepth+".syn.txt.gz").c_str());
    ogzstream ouf2 ((outDepth+".unsyn.txt.gz").c_str());
    set<string> synteny;
    vector<string> ll ;
    string line;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1 ) continue;
        ll.clear();
        split(line,ll," \t");
        synteny.insert(ll[1]);
    }

    while(!inf.eof()){
        getline(inf,line);
        if (line.length() < 1  ) continue;
        if(line[0] == '#') continue;
        ll.clear();
        split(line,ll," \t");
        if(synteny.count(ll[1]) == 1){
            ouf1 << line << "\n";
        }else{
            ouf2 << line << "\n";
        }
    }
    ouf1.close();
    ouf2.close();
    return 1;
}

int checkNumber(parameter *para){
    igzstream inf ((para->inFile).c_str(),ifstream::in);
    igzstream inf2 ((para->inFile2).c_str(),ifstream::in);
    string prefix = (para->suffix);
    set<string> genes;
    vector<string> ll ;
    string line;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1 ) continue;
        genes.insert(prefix + "|" + line);
    }
    int num = 0;
    while(!inf.eof()){
        getline(inf,line);
        if (line.length() < 1  ) continue;
        if(line[0] == '#') continue;
        ll.clear();
        split(line,ll," \t");
        if(genes.count(ll[0])==1) num++;
    }
    cout <<"Number is: " << num << endl;
    return 1;
}

int siteDepth(parameter *para){
    igzstream DepthIN ((para->inFile).c_str(),ifstream::in);
    igzstream SampleList ((para->subPop).c_str(),ifstream::in);
    igzstream allSample ((para->inFile2).c_str(),ifstream::in);
    if (DepthIN.fail())
    {
        cerr << "open depth File IN File error: " << (para->inFile) << endl;
        return  0;
    }
    if (SampleList.fail())
    {
        cerr << "open sub-samples File IN File error: " << (para->subPop) << endl;
        return  0;
    }
    if (allSample.fail())
    {
        cerr << "open total samples File IN File error: " << (para->inFile2) << endl;
        return  0;
    }
    string outDepth =(para -> outFile)+".depth.passed.gz";
    ogzstream OUT ((outDepth).c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outDepth << endl;
        return  0;
    }
    // prepare the total sample list
    vector< string > sampleVetor;
    while(!allSample.eof())
    {
        string  line ;
        getline(allSample,line);
        if (line.length() <= 0 || line[0] == '#' )  { continue  ; }
        sampleVetor.push_back(line.substr(0,4));
    }
    allSample.close();
    
    //prepare the subpop site
    vector<int> sampleSite;
    int A = sampleVetor.size() ;
    while(!SampleList.eof()){
        string  line ;
        getline(SampleList,line);
        
        if (line.length() <= 0 || line[0] == '#' )  { continue  ; }
        for (int ii = 0 ; ii< A ; ii++){
            if(line == sampleVetor[ii]){
                sampleSite.push_back(ii+2); // get the sample position
            }
        }
    }
    
    if(sampleSite.size() ==0){
        cerr << "sub-sample size is 0! Stopped!" << endl;
        return 0;
    }
    
    // get the sample depth
    vector<string> inf ;
    map <string,map <int, vector <int> > > depthList;
    int subSize = sampleSite.size();
    
//    cout << subSize << endl;
    int passedSNP = 0;
    while(!DepthIN.eof()){
        string line;
        getline(DepthIN,line);
        if (line.length() <= 0  )  { continue  ; }
        inf.clear();
        split(line,inf,"\t");
        vector <int> dep ;
        dep.clear();
        
        int sumDepth = 0;
        for (int iik = 0 ; iik < subSize ; iik++){
            string d = inf[sampleSite[iik]];
            int pos = atoi(d.c_str());
            dep.push_back(pos);
            sumDepth += pos;
        }
        double mind = para->minDepth ;
        double maxd = para->maxDepth ;
        if(sumDepth> mind & sumDepth < maxd){
            passedSNP++;
            OUT << "rs" << inf[0] << "_" << inf[1] << "\n";
        }else{
            continue;
        }
//        cout << sumDepth << endl;
        
//        dep.push_back(sumDepth);
//        map <string,map <int, vector <int> > >  :: iterator it = depthList.find(inf[0]);
//        int pos = atoi(inf[1].c_str());
//        if (it == depthList.end()){
//            map <int, vector <int> > DD;
//            DD[pos] = dep;
//            depthList.insert(map <string,map <int,vector <int> > > ::value_type(inf[0],DD));
////            cout << dep[dep.size()-1] << endl;
//        }else{
////            cout << dep[dep.size()-1] << endl;
//            (it -> second).insert(map <int, vector <int> >  :: value_type(pos,dep)) ;
//        }
    }
    OUT.close();
    cout << "Passed SNP is: " << passedSNP << endl;
//    (inDepth->depthList) = depthList;
    return 1;
}
inline int outDepthFile(parameter *para, depth *inDepth){
    string outDepth =(para -> outFile)+".depth.passed.gz";
    ogzstream OUT ((outDepth).c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outDepth << endl;
        return  0;
    }
    
    map <string, map <int, vector <int> > > depthList = (inDepth->depthList);
    map <string, map <int, vector <int> > >  :: iterator it;
    double minDepth = (para->minDepth);
    double maxDepth = (para->maxDepth);
//    cout << "....." << it->first << " ...." << endl;
    for (it = depthList.begin();  it!=depthList.end();   ++it) {
//        cout << it->first << endl;
        map <int, vector <int> > ::iterator itt;
        map <int, vector <int> > depthVector = (it->second);
        for (itt = depthVector.begin();  itt!=depthVector.end();   ++itt) {
//            cout << itt->first << endl;
            vector<int> dep = itt->second;
            int len = dep.size() - 1;
            if((dep[len] > minDepth) & (dep[len] < maxDepth)){
//                cout << itt->first << endl;
                int pos = itt->first;
                OUT << "rs" << it->first <<"_" << pos << "\n";
            }
        }
    }
    OUT.close();
    return 1;
}

int toBedold (parameter *para){
    cout << "toBed..." << endl;
    igzstream DepthIN ((para->inFile).c_str(),ifstream::in);
    if (DepthIN.fail())
    {
        cerr << "open depth File IN File error: " << (para->inFile) << endl;
        return  0;
    }
    string outDepth = (para -> outFile)+".bed";
    ofstream OUT ;
    OUT.open(outDepth.c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outDepth << endl;
        return  0;
    }
    vector<string> inf ;
    int begin = 0;
    int end = 0;
    bool start = true;
    int pre = 0;
    string chr;
    while(!DepthIN.eof()){
        string line;
        getline(DepthIN,line);
        if (line.length() <= 0  )  { continue  ; }
        inf.clear();
        split(line,inf,"_");
        chr = inf[0].substr(2);
        if(start) {
            begin = atoi(inf[1].c_str()) - 1 ;
            pre = begin;
            start = false;
        }
        end = atoi(inf[1].c_str());
        if((end - pre) > 20){
            int len = (pre -begin );
            if( len > 150){
                OUT << chr << "\t" << begin << "\t" << pre << "\t" << len << "\n";
            }
            start = true;
        }
        pre = end;
    }
    if(!start){
        int len = (end - begin);
        if(len > 150){
            OUT << chr << "\t" << begin << "\t" << end << "\t" << len << "\n";
        }
    }
    OUT.close();
    return 1;
}

int Depth2Bed(parameter *para){
    int binSize = para->size;
    igzstream inF ((para->inFile).c_str(),ifstream::in);
    if(inF.fail()){
        cerr << "Open file error: " << (para->inFile) << endl;
        return 0;
    }
    ofstream ouf ((para -> outFile).c_str());
    if(ouf.fail()){
        cerr << "Couldn't open outFile" << endl;
        return 0;
    }
    string line;
    vector < string > ll;
    lint startPos = 1;
    lint count = 0;
    int BinRound = 1;
    lint endPos = 1;
    while(!inF.eof()){
        getline(inF, line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll,"\t");
        startPos = string2Int(ll[1]);
        
        while(string2Int(ll[1]) > BinRound*binSize){
            endPos = BinRound*binSize;
            startPos = (BinRound-1)*binSize +1;
            ouf << ll[0] << "\t" << startPos << "\t" << endPos << "\t" << count << "\n" ;
            ++BinRound;
            count = 0;
        }
        ++count;
    }
    if(count > 0){
        endPos = string2Int(ll[1])+1;
        startPos = (BinRound-1)*binSize +1;
        ouf << ll[0] << "\t" << startPos << "\t" << endPos << "\t" << count << "\n" ;
    }
    inF.close();
    ouf.close();
    return 1;
}

int Pos2Bed(parameter *para){
    igzstream inF ((para->inFile).c_str(),ifstream::in);
    if(inF.fail()){
        cerr << "Open file error: " << (para->inFile) << endl;
        return 0;
    }
    ofstream ouf ((para -> outFile).c_str());
    if(ouf.fail()){
        cerr << "Couldn't open outFile" << endl;
        return 0;
    }
    string line;
    vector < string > ll;
    lint startPos = 1;
    lint endPos = 1;
    int startPosN = 0;
    string chr = "";
    bool first = true;
    bool next = false;
    while(!inF.eof()){
        getline(inF, line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll,"\t");
        startPosN = string2Int(ll[1]);
        string chrN = ll[0];
        if (first||next) {
            startPos = startPosN;
            endPos = startPos;
            first = false;
            next = false;
            continue;
        }
        if(chr != chrN){
            if( (endPos - startPos) > 1000 ){
                ouf << chr << "\t" << startPos << "\t" << endPos << "\n";
            }
            first = true;
        }else{
            if((startPosN - endPos) > 500){
                if((endPos - startPos) > 1000){
                     ouf << chr << "\t" << startPos << "\t" << endPos  << "\n";
                }
                next = true;
            }else{
                next = false;
            }
        }
        chr = chrN;
        endPos = startPosN;
    }
    if((endPos - startPos) > 100){
        ouf << chr << "\t" << startPos << "\t" << endPos  << "\n";
        next = true;
    }
    ouf.close();
    return 1;
}


int getUnMapped(parameter *para){
    igzstream inf ((para->inFile).c_str(),ifstream::in);
    ofstream ouf ((para->outFile).c_str());
    vector<string> ll;
    string line;
    string chrPre = "";
    int startPre = 0,start = 0;
    int end = 0;
    bool next = true;
    bool write = false;
    bool first = true;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        int tmp =  string2Int(ll[2]);
        if(ll[0]!=chrPre){
            if(write){
                ouf << ll[0] << "\t" << start-1 << "\t" << end << "\n";
                write = false;
                next = true;
                first = true;
                start = 0;
                end = 0;
            }
        }
        chrPre = ll[0];
        if(next && tmp == 0){
            if(first){
                start = string2Int(ll[1]);
                first = false;
            }
            next = false;
        }else{
            if(tmp > 0 && !next){
                end = string2Int(ll[1]);
                next = true;
                first = true;
                if((end - start) > 150){
                    ouf << ll[0] << "\t" << start-1 << "\t" << end-1 << "\n";
                    end = 1;
                    next = true;
                }
            }else{
                continue;
            }
        }
        
    }
    if(write){
        cout << ll[0] << "\t" << start-1 << "\t" << end-1 << "\n";
    }
    inf.close();
    ouf.close();
    
    return 0;
}

int getMapped(parameter *para){
    igzstream inf ((para->inFile).c_str(),ifstream::in);
    igzstream inf2 ((para->inFile2).c_str(),ifstream::in);
    ofstream ouf ((para->outFile).c_str());
    vector<string> ll;
    string line;
    map<string,int> geno;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        geno.insert(pair<string,int>(ll[0],string2Int(ll[1])));
    }
    int max =0;
    string chrPre = "";
    bool first = true;
    int end = 0;
    cout << "fai file readed!"<<endl;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0] != chrPre) {
            first =true;
            if(chrPre!=""){
                if(end!=max){
                     ouf << chrPre << "\t" << end <<"\t" << max << "\n";
                }
            }
        }
        chrPre = ll[0];
        max = geno[chrPre];
        
        if(first){
            if(string2Int(ll[1])!=0){
                ouf << ll[0] << "\t" << 0 <<"\t" << ll[1] << "\n";
            }
            first = false;
        }else{
            ouf << ll[0] << "\t" << end <<"\t" << ll[1] << "\n";
        }
        
        end = string2Int(ll[2]);
    }
    if(end!=max){
        ouf << chrPre << "\t" << end <<"\t" << max << "\n";
    }
    inf2.close();
    inf.close();
    ouf.close();
    
    return 0;
}

int getOri(parameter *para){
    igzstream inf1 ((para->inFile).c_str(),ifstream::in);
    igzstream inf2 ((para->inFile2).c_str(),ifstream::in);
    ofstream ouf ((para->outFile).c_str());
    set <string> pos;
    vector<string> ll;
    string line;
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        pos.insert(ll[1]);
    }
    while(!inf2.eof()){
        getline(inf2,line);
        if(line[0]=='C') continue;
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        if(pos.count(ll[1])>0){
            ouf << line << "\n";
        }
    }
    ouf.close();
    inf1.close();
    inf2.close();
    return 0;
}
int pi2bed(parameter *para){
//    int binSize = para->size;
    igzstream inF ((para->inFile).c_str(),ifstream::in);
    igzstream inbed ((para->inFile2).c_str(),ifstream::in);
    if(inF.fail()){
        cerr << "Open file error: " << (para->inFile) << endl;
        return 0;
    }
    if(inbed.fail()){
        cerr << "Open file error: " << (para->inFile2) << endl;
        return 0;
    }
    ofstream ouf ((para -> outFile).c_str());
    if(ouf.fail()){
        cerr << "Couldn't open outFile" << endl;
        return 0;
    }
    string chr = (para->chr);
    string line;
    vector < string > ll;
    int** bedPos = imatrix(-1, 500000, -1, 4);
    int bedPos_i = 0;
    while(!inbed.eof()){
        getline(inbed,line);
        if(line.length() < 1) continue;
        if(line[0]=='C') continue;
        ll.clear();
        split(line,ll,"\t");
        if(ll[0] !=chr) continue;
        bedPos[bedPos_i][0] = string2Int(ll[1]); // start pos
        bedPos[bedPos_i][1] = string2Int(ll[2]); // end pos
        bedPos[bedPos_i][2] = string2Int(ll[2]) - string2Int(ll[1]) + 1 ; // length
        bedPos[bedPos_i][3] = string2Int(ll[3]); // number in this region
        bedPos_i++;
    }
    cout << "bed readed! Size is:\t" << bedPos_i << endl;
    inbed.close();
    double pi = 0.0;
    int curent_bed = bedPos[0][0];
    int startPos;
    int endPos;
    int n_bed_pos = 0;
    while(!inF.eof()){
        getline(inF, line);
        if(line.length() < 1) continue;
        if(line[0]=='C') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0]!=chr) continue;
        int current_pos = string2Int(ll[1]);
        if (current_pos < bedPos[0][0]) {
//            cerr << "please check bedFile, the first position is too small!" << endl;
//            return 1;
            continue;
        }
//        if (current_pos > bedPos[bedPos_i-1][1]) continue;
        if(n_bed_pos > bedPos_i){
            break;
        }
        while(bedPos[n_bed_pos][1] < current_pos ){
            startPos = bedPos[n_bed_pos][0];
            endPos = bedPos[n_bed_pos][1];
            ouf << chr << "\t" << startPos << "\t" << endPos << "\t" << pi/bedPos[n_bed_pos][3] << "\n";
            n_bed_pos++;
            if(n_bed_pos > bedPos_i){
                break;
            }
            pi = 0;
        }
        if(ll[2]=="-nan"||ll[2]=="NA"||ll[2]=="inf") ll[2] = "0";
        pi += string2Double(ll[2]);
    }
    while( n_bed_pos < bedPos_i){
        startPos = bedPos[n_bed_pos][0];
        endPos = bedPos[n_bed_pos][1];
        ouf << chr << "\t" << startPos << "\t" << endPos << "\t" << pi/bedPos[n_bed_pos][3] << "\n";
        n_bed_pos++;
        pi = 0;
    }
    inF.close();
    ouf.close();
    return 1;
}

int meanBedpi(parameter *para){
    //    int binSize = para->size;
    igzstream inF ((para->inFile).c_str(),ifstream::in);
    igzstream inbed ((para->inFile2).c_str(),ifstream::in);
    if(inF.fail()){
        cerr << "Open file error: " << (para->inFile) << endl;
        return 0;
    }
    if(inbed.fail()){
        cerr << "Open file error: " << (para->inFile2) << endl;
        return 0;
    }
    ofstream ouf ((para -> outFile).c_str());
    if(ouf.fail()){
        cerr << "Couldn't open outFile" << endl;
        return 0;
    }
    string chr = (para->chr);
    string line;
    vector < string > ll;
    unordered_map<string,double> pi_value;
    while(!inF.eof()){
        getline(inF, line);
        if(line.length() < 1) continue;
        if(line[0]=='C') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0]!=chr) continue;
        string key =ll[0] + "_" + ll[1];
        double value = 0;
        if(ll.size()==2){
            value = 1;
        }else if(ll[2]=="-nan"||ll[2]=="NA"||ll[2]=="inf") {
            value = 0;
        }else{
            value = string2Double(ll[2]);
        }
        pi_value.insert(pair<string,double>(key,value));
    }
    cout << "site value readed! Total sites are:\t" << pi_value.size() <<  endl;
    while(!inbed.eof()){
        double pi = 0;
        int number = 0;
        getline(inbed,line);
        if(line.length()<1) continue;
        if(line[0] == 'C') continue;
        if(line[0] =='S') continue;
        ll.clear();
        split(line,ll,"\t");
        if(ll[0]!=chr) continue;
        int s = string2Int(ll[1]);
        int e = string2Int(ll[2]) + 1 ;
        for(int i = s ; i < e; ++i){
            string key = ll[0]+"_"+Int2String(i);
            if(pi_value.count(key) == 1){
                number++;
                double value = pi_value[key];
                if(value != NAN){
                    pi += value;
                }
            }
        }
        double mean = pi / number;
        ouf << ll[0] << "\t" << ll[1] << "\t" << ll[2] << "\t" << pi << "\t" << number << "\t" << mean << "\n" << flush;
    }
    inbed.close();
    inF.close();
    ouf.close();
    return 1;
}
int SNPs100window(parameter *para){
    cout << "100-SNPs window size.." << endl;
    igzstream inF ((para->inFile).c_str(),ifstream::in);
    if(inF.fail()){
        cerr << "Open file error: " << (para->inFile) << endl;
        return 0;
    }
    ofstream ouf ((para -> outFile).c_str());
    if(ouf.fail()){
        cerr << "Couldn't open outFile" << endl;
        return 0;
    }
    string line;
    vector <string> ll;
    vector<int> pos;
    string chr = (para -> chr);
    int step_size = (para ->step_size);
    while(!inF.eof()){
        getline(inF, line);
        if(line.length() < 1) continue;
        if(line[0]=='#') continue;
        split(line,ll," \t");
        if (ll[0] != chr) continue;
        int p = string2Int(ll[1]);
        pos.push_back(p);

    }
    for (int i = 0; i < pos.size() ; i = i + step_size){
        int b;
        if ((i + 100) > (pos.size() - 1)){
            b = pos.size() -1;
        }else{
            b = i + 100;
        }
        int a = pos[b] - pos[i];
        ouf <<  chr << "\t" << pos[i]-1 << "\t" << pos[b]-1 << "\t" << a << "\n";
    }
    
    ouf.close();
    return 1;
}
int depthEvaluation(parameter *para){
    igzstream inf1 ((para->inFile).c_str(),ifstream::in);
    igzstream inf2 ((para->inFile2).c_str(),ifstream::in);
    if(inf1.fail()){
        cerr << "Open file error: " << (para->inFile) << endl;
        return 0;
    }
    if(inf2.fail()){
        cerr << "Open file error: " << (para->inFile2) << endl;
        return 0;
    }
    ofstream ouf ((para -> outFile).c_str());
    if(ouf.fail()){
        cerr << "Couldn't open outFile" << endl;
        return 0;
    }
    vector<int> hist(41,0);
    int overlapped = 0;
    string line;
    vector<string> ll;
    set<string> pos;
    set<string> pos2;
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length() < 1) continue;
        split(line,ll,"\t");
        pos.insert(ll[0]+"_"+ll[1]);
        int p = string2Int(ll[2]);
        if(p>40) p = 40;
        hist[p] ++;
    }
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        split(line,ll,"\t");
        if(pos.count(ll[0]+"_"+ll[1])==1){
            overlapped++;
        }
        pos2.insert(ll[0]+"_"+ll[1]);
        int p = string2Int(ll[2]);
        if(p>40) p = 40;
        hist[p] ++;
    }
    for(int i = 0; i < hist.size();++i){
        ouf << i << "\t" << hist[i] << "\n";
    }
    cout << "file1 size is:\t" << pos.size() << endl;
    cout << "file2 size is:\t" << pos2.size() << endl;
    cout << "overlapped site is:\t" << overlapped << endl;
    ouf.close();
    return 0;
}
int getGeneBed(parameter *para){
    
    ofstream ouf ((para -> outFile).c_str());
    if(ouf.fail()){
        cerr << "Couldn't open outFile" << endl;
        return 0;
    }
    string chr = (para->chr);
    string line;
    vector < string > ll;
    int binSize = para->size;
    gff3 g3 = gff3((para->inFile),chr);
    cout << "Chromosome "<< chr << " on Gff3 readed!" << endl;
    map<string,gene> g = g3.genes ;
    map<string,gene>::iterator it;
    it = g.begin();
    while(it != g.end()){
        
        gene a = it->second;
        int start = a.start - binSize;
        if ( start < 0 ) start = 0;
        ouf << chr << "\t" << start << "\t" << (a.end + binSize) << "\t";
        ouf << it->first <<"\n";
        it++;
    }
    ouf.close();
    return 1;
}

int pi(parameter *para){
    //site pi
    igzstream inF ((para->inFile).c_str(),ifstream::in);
    igzstream subFile ((para->inFile2).c_str(),ifstream::in);
    if(inF.fail()){
        cerr << "Open file error: " << (para->inFile) << endl;
        return 0;
    }
    if(subFile.fail()){
        cerr << "Open file error: " << (para->inFile2) << endl;
        return 0;
    }
    ofstream ouf ((para -> outFile).c_str());
    if(ouf.fail()){
        cerr << "Couldn't open outFile" << endl;
        return 0;
    }
    string line;
    vector < string > ll;
    set <string> Samples;
    vector<int> samplePos;
    while(!subFile.eof()){
        getline(subFile,line);
        if(line.length()<1) continue;
        Samples.insert(line);
    }
    subFile.close();
//    set<string>::iterator it;
//    for(it = Samples.begin() ; it != Samples.end() ; ++it){
//                    cout<<*it<<endl;
//    }
    while(!inF.eof()){
        double a = 0, b= 0,c=0;
        int sampleSize = 0;
        getline(inF,line);
        if(line[0]=='#' && line[1]=='#') continue;
        if(line[0] == '#' && line[1] == 'C'){
//            set<int>::iterator it;
            ll.clear();
            split(line,ll,"\t");
            for(int i = 9; i < ll.size(); ++i){
                if(Samples.count(ll[i])==1) {
                    samplePos.push_back(i);
//                    cout << ll[i] << endl;
                }
            }
            continue;
        }
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll,"\t");
        for(int i = 0; i< samplePos.size() ;++i){
            if(ll[samplePos[i]][0] == '0' && ll[samplePos[i]][2] == '0'){
                a += 2;
                sampleSize +=2;
            }else if(ll[samplePos[i]][0]== '1' && ll[samplePos[i]][2] == '1'){
                b +=2 ;
                sampleSize +=2;
            }else if(ll[samplePos[i]][0]== '0' && ll[samplePos[i]][2] == '1'){
                a++;
                b++;
                sampleSize +=2;
            }else{
                continue;
            }
        }
        double pi = (2*a*b)/(sampleSize*(sampleSize-1));
        ouf << ll[0] << "\t" << ll[1] << "\t" << pi << endl;
    }
    inF.close();
    ouf.close();
    return 1;
}
int changePos(parameter *para){
    cout << "Change file chromosome position..." << endl;
    string input =(para->inFile);
    string ext;
    ext = input.substr(input.rfind('.') ==string::npos ? input.length() : input.rfind('.') + 1);
    //
    if (ext == "gz"){
        igzstream inFile (input.c_str(),ifstream::in);
        if (inFile.fail()){
            cerr << "open File IN error: " << (para->inFile) << endl;
            return  0;
        }
        ifstream posFile(para->inFile2);
        if((!posFile.good())){
            cerr << "open pos File error: " << para->inFile2 << endl;
            return  0;
        }
        string outFile =(para -> outFile);
//    ofstream OUT ((outFile).c_str());
//    cout << ext << endl;
   
        ogzstream OUT ((outFile).c_str());
        if((!OUT.good())){
            cerr << "open OUT File error: " << outFile << endl;
            return  0;
        }
        map<string, vector<string>> pos ;
        string line;
        vector <string> chr;
        while (getline(posFile,line)){
            chr.clear();
            split(line,chr,"\t");
            pos.insert(map <string, vector<string>> :: value_type(chr[0],chr));
        }
        posFile.close();
        string header = (para->headerC);
        int lh = header.length() - 1;
        bool isBed = para->isBed;
        while (!inFile.eof()){
            chr.clear();
            getline(inFile, line);
            if((line.substr(0,lh) == header) | (line[0] == '#')) {
                OUT << line ;
            }else {
                chr.clear();
                if(line.size()  < 1) {continue ;};
                split(line,chr,"\t");
                int lchr = chr.size();
                vector<string> info = pos[chr[0]];
                set<int> posChange = (para->pos);
                OUT << info[3];
                for (int iil = 1; iil < lchr; iil ++){
                    OUT << "\t";
                    if(posChange.count(iil) == 1){
                        OUT << (atoi(chr[iil].c_str()) + atoi(info[4].c_str()));
                    }else{
                        OUT << chr[iil];
                    }
                }
            }
            OUT << "\n";
        }
        inFile.close();
        OUT.close();
    }else{
        ifstream inFile (input.c_str());
        if (inFile.fail())
        {
            cerr << "open File IN error: " << (para->inFile) << endl;
            return  0;
        }
        ifstream posFile(para->inFile2);
        if((!posFile.good())){
            cerr << "open pos File error: " << para->inFile2 << endl;
            return  0;
        }
        string outFile =(para -> outFile);
        ofstream  OUT((outFile).c_str());
        if((!OUT.good())){
            cerr << "open OUT File error: " << outFile << endl;
            return  0;
        }
        map<string, vector<string>> pos ;
        string line;
        vector <string> chr;
        while (getline(posFile,line)){
            chr.clear();
            split(line,chr,"\t");
            pos.insert(map <string, vector<string>> :: value_type(chr[0],chr));
        }
        posFile.close();
        string header = (para->headerC);
        int lh = header.length();
        bool isBed = para->isBed;
        while (!inFile.eof()){
            chr.clear();
            getline(inFile, line);
//            cout << "testing ..." << endl;
//            cout << line.substr(0,3) << endl;
            if((line.substr(0,lh) == header)) {
                OUT << line ;
            }else {
                chr.clear();
                if(line.size()  < 1) {continue ;};
                split(line,chr,"\t");
                lint lchr = chr.size();
                vector<string> info = pos[chr[0]];
                set<int> posChange = (para->pos);
                OUT << info[3];
                for (int iil = 1; iil < lchr; iil ++){
                    OUT << "\t";
                    if(posChange.count(iil) == 1){
                        OUT << (atoi(chr[iil].c_str()) + stoi(info[4].c_str()));
                    }else{
                        OUT << chr[iil];
                    }
                }
            }
            OUT << "\n";
        }
        inFile.close();
        OUT.close();
    }
    return 1;
}
int changeEigenStratPos(parameter *para){
    cout << "Change file chromosome position..." << endl;
    string input =(para->inFile);
    ifstream inFile (input.c_str());
    if (inFile.fail()){
        cerr << "open File IN error: " << (para->inFile) << endl;
        return  0;
    }
    ifstream posFile(para->inFile2);
    if((!posFile.good())){
        cerr << "open pos File error: " << para->inFile2 << endl;
        return  0;
    }
    string outFile =(para -> outFile);
    ofstream  ouf ((outFile).c_str());
    if((!ouf.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    map<string, vector<string>> pos ;
    string line;
    vector <string> ll;
    while (!posFile.eof()){
        getline(posFile,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll,"\t");
        vector<string> p ;
        p.push_back(ll[3]);
        p.push_back(ll[4]);
        pos.insert(pair<string,vector<string>>(ll[0],p));
    }
    cout << "Position file readed!" << endl;
    posFile.close();
    while (!inFile.eof()){
        getline(inFile, line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll,"\t");
        vector<string> p = pos[ll[1]];
        ll[1] = p[0];
        int po = string2Int(ll[3]) + string2Int(p[1]);
        ll[3] = Int2String(po);
        ouf << ll[0];
        for (int i = 1; i < ll.size(); ++i){
            ouf << "\t" << ll[i];
        }
        ouf << "\n";
    }
    inFile.close();
    ouf.close();
    return 1;
}
int GenomeStatistic(parameter *para){
    cout << "Genome summary..." << endl;
    string input =(para->inFile);
    ifstream inf (input.c_str());
    if (inf.fail()){
        cerr << "open File IN error: " << (para->inFile) << endl;
        return  0;
    }
    string outFile =(para -> outFile);
    ofstream  ouf ((outFile).c_str());
    if((!ouf.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    string line;
    map<string, int> chromosome;
    map<string, string> genome;
    string chr;
    string fasta;
    int len;
    int size;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0]== '>'){
            chr = line;
        }
    }
    return 0;
}
int getRiceGenes(parameter *para){
    string input =(para->inFile);
    string input2 =(para->inFile2);
    ifstream inFile (input.c_str());
    ifstream inFile2 (input2.c_str());
    if (inFile.fail()){
        cerr << "open File IN error: " << (para->inFile) << endl;
        return  0;
    }
    
    if((!inFile2.good())){
        cerr << "open pos File error: " << para->inFile2 << endl;
        return  0;
    }
    string outFile =(para -> outFile);
    ofstream  ouf ((outFile).c_str());
    if((!ouf.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    set<string> genes;
    string line;
    while (!inFile2.eof()){
        getline(inFile2,line);
        if(line.length()<1) continue;
        genes.insert(line);
    }
    vector<string> ll;
    cout << genes.size() << "\tgenes added!" << endl;
    while(!inFile.eof()){
        getline(inFile,line);
        if(line.length() < 1) continue;
        if(line[0] != 'T') continue;
        if (line.rfind("OSY") == string::npos) continue;
        ll.clear();
        split(line,ll," \t");
        string a;
        a = ll[0];
        ll.clear();
        split(a,ll,"|");
        a = ll[1];
        ll.clear();
        split(a,ll,".");
        if(genes.count(ll[0]) == 1){
//            cout << ll[0] << endl;
            ouf << line << "\n";
        }
    }
    ouf.close();
    return 0;
}
int vcf2RleateMap(parameter *para){
    string input =(para->inFile);
    ifstream inf (input.c_str());
    string outFile =(para -> outFile);
    ofstream  ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '#') continue;
        split(line,ll,"\t");
        ouf << ll[2] << " 2.02 " << string2Int(ll[2])/1000000000 << "\n";
    }
    ouf.close();
    return 0;
}

int V11_barley(parameter *para){
    string input =(para->inFile);
    string input2 =(para->inFile2);
    igzstream inf (input.c_str());
    igzstream inf2 (input2.c_str());
    string outFile =(para -> outFile);
    ofstream  ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    map<string,string> barley;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '#') continue;
        split(line,ll,"\t");
        barley.insert(pair<string,string>(ll[1],ll[ll.size()-1]));
    }
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        if(line[0] == '#') {
            ouf << line ;
            if(line[1] == 'C'){
                ouf << "\tBarley";
            }
            ouf << "\n";
            continue;
        };
        split(line,ll,"\t");
        if (barley.count(ll[1]) == 0) continue;
        ouf << line << "\t" << barley[ll[1]]  << "\n";
    }
    ouf.close();
    return 0;
}

int vcf2Major (parameter *para){
    string input =(para->inFile);
    string input2 =(para->inFile2);
    igzstream inf (input.c_str(),ifstream::in);
    igzstream inf2 (input2.c_str(),ifstream::in);
    if (inf.fail()){
        cerr << "open File IN error: " << (para->inFile) << endl;
        return  0;
    }
    
    string outFile =(para -> outFile);
    ofstream ouf ((outFile +".vcf").c_str());
    ofstream ouf2 ((outFile +".rate").c_str());
    if((!ouf.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    map<string,string> sg;
    map<string,int> group;
   
    string line;
    vector <string> ll;
    vector <string> go;
    int order = 0;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        sg.insert(pair<string, string>(ll[0],ll[1]));
    }
    cout << "Total sample in group file is:\t" << sg.size() << endl;
    vector<int> ords;
    int totalSample;
    set<string> ag;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '#'){
            if(line[1] == 'C'){
                split(line,ll,"\t");
                for (int i =0 ; i< 9; i++){
                    ouf << ll[i] << "\t";
                    ouf2 << ll[i] << "\t";
                }
                for(int i = 9; i < ll.size();++i){
                    if(ag.count(sg[ll[i]]) == 0){
                        ag.insert(sg[ll[i]]);
                        go.push_back(sg[ll[i]]);
                        group.insert(pair<string,int>(sg[ll[i]],order));
                        ords.push_back(order);
                        order++;
                    }else{
                        int index = group[sg[ll[i]]];
                        ords.push_back(index);
                    }
//                    cout << "sample is:\t"<<ll[i] << "\n group is:\t" << sg[ll[i]] <<"\ngroup order is:\t" << ords[ords.size()-1] << endl;
                }
                totalSample = ll.size() - 9;
                for (int i = 0; i < go.size()-1; i++){
                    ouf << go[i] << "\t";
                    ouf2 <<go[i] << "\t";
                }
                ouf << go[go.size()-1] << "\n";
                ouf2 << go[go.size()-1] << "\n";
                cout << "Samples in vcf is:\t" << totalSample << endl;
                cout << "Groups in vcf is:\t" << go.size() << endl;
            }else{
               ouf << line << "\n";
            }
            
            continue;
        }
        split(line,ll,"\t");
        for (int i = 0; i< 8; i++){
            ouf << ll[i] << "\t";
            ouf2 << ll[i] << "\t";
        }
        ouf << ll[8];
        ouf2 << ll[8];
        vector<int> posR(go.size(),0);
        vector<int> posA(go.size(),0);
        vector<int> pos(go.size(),0);
//        cout << "length of ords is:\t" << ords.size() << endl;
//        cout << "length of line is:\t" << ll.size() << endl;
        for (int i = 9; i < ll.size(); ++i){
//            cout << ords[i-9] << endl;
            if (ll[i][0] == '0'){
                posR[ords[i-9]] ++;
            }else if (ll[i][0]=='1'){
                posA[ords[i-9]] ++;
            }
            pos[ords[i-9]]++;
        }
//        cout << "testing..." << endl;
        for(int i = 0; i < pos.size(); i++){
            if(posA[i] > posR[i]){
                ouf << "\t" << "1/1;0,10;0,0,10";
                ouf2 << "\t" << setprecision(2) << posA[i]*1.0/(posA[i] + posR[i]);
            }else{
                ouf << "\t" << "0/0;10,0;10,0,0";
                ouf2 << "\t" << setprecision(2) << posR[i]*1.0/(posA[i] + posR[i]);
            }
        }
        ouf << "\n";
        ouf2 << "\n";
    }
    return 0;
}

int chr2num(parameter *para){
    cout << "Change file chromosome position..." << endl;
    string input =(para->inFile);
    string ext;
    igzstream inFile (input.c_str(),ifstream::in);
    if (inFile.fail()){
        cerr << "open File IN error: " << (para->inFile) << endl;
        return  0;
    }
    ifstream posFile(para->inFile2);
    if((!posFile.good())){
        cerr << "open pos File error: " << para->inFile2 << endl;
        return  0;
    }
    string outFile =(para -> outFile);
    ofstream OUT ((outFile).c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    map<string, vector<string>> pos ;
    string line;
    vector <string> ll;
    while (getline(posFile,line)){
        ll.clear();
        split(line,ll,"\t");
        if(pos.count(ll[3]) == 1){
            vector<string> a = pos[ll[3]];
            a.push_back(ll[0]);
            pos[ll[3]] = a;
        }else{
            vector<string> a ;
            a.push_back(ll[0]);
            a.push_back(ll[5]);
            pos.insert(pair<string, vector<string>>(ll[3],a));
        }
    }
    posFile.close();
    string header = (para->headerC);
    int lh = header.length() - 1;
    bool isBed = para->isBed;
    while (!inFile.eof()){
        getline(inFile, line);
        if((line.substr(0,lh) == header) | (line[0] == '#')) {
            OUT << line ;
        }else {
            ll.clear();
            if(line.size()  < 1) continue ;
            split(line,ll,"\t");
            int lchr = ll.size();
            vector<string> info = pos[ll[0]];
            set<int> posChange = (para->pos);
            int p = string2Int(info[1]);
            int po = string2Int(ll[1]);
            string chr;
            if (po > p){
                chr = info[2];
            }else {
                chr = info[0];
            }
            OUT << chr;
            for (int iil = 1; iil < lchr; iil ++){
                OUT << "\t";
                if(posChange.count(iil) == 1){
                    if (po > p){
                        OUT << (atoi(ll[iil].c_str()) - p);
                    }else{
                        OUT << ll[iil];
                    }
                    
                }else{
                    OUT << ll[iil];
                }
            }
        }
        OUT << "\n";
    }
    inFile.close();
    OUT.close();
    
    return 1;
}

int count(parameter *para){
    string input =(para->inFile);
//    string ext;
//    ext = input.substr(input.rfind('.') ==string::npos ? input.length() : input.rfind('.') + 1);
//    //
    igzstream inFile (input.c_str(),ifstream::in);
    if (inFile.fail()){
        cerr << "open File IN error: " << (para->inFile) << endl;
        return  0;
    }
    
    
    int line = 0;
    string l;
    while (!inFile.eof()){
        getline(inFile,l,'\n');
        line++;
//        if( line > 10000) break;
    }
    inFile.close();
    cout << line << endl;
    return 1;
}
int mergeDepth(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
//    string input3 = (para -> bedFile);
    igzstream f1 (input1.c_str(),ifstream::in);
    igzstream f2 (input2.c_str(),ifstream::in);
//    igzstream f3 (input3.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    if(f2.fail()){
        cerr << "open File IN error: " << input2 << endl;
        return 0;
    }
//    if(f2.fail()){
//        cerr << "open File IN error: " << input2 << endl;
//        return 0;
//    }
    
    string outFile =(para -> outFile);
    ogzstream  OUT((outFile).c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    
    string l1, l2;
    vector < string >  ll2;
    
    while(!f1.eof()&&!f2.eof()){
        getline(f1,l1);
        getline(f2,l2);
        OUT << l1;
        OUT << "\t";
        OUT << l2;
//        cout << ll2.size() <<endl;
        for(int i = 2; i < ll2.size(); i++){
            OUT << "\t";
            OUT << ll2[i];
        }
        OUT << "\n";
    }
//    cout << ll2.size()  << endl;
    f1.close();
    f2.close();
    OUT.close();
    return 1;
}
int filterByDepth(parameter *para){
    string input1 = (para->inFile);
    igzstream inf (input1.c_str(),ifstream::in);
    string outFile =(para -> outFile);
    ogzstream  ouf((outFile).c_str());
    string line;
    vector < string >  ll;
    int minDepth = (para -> minDepth) -1 ;
    int maxDepth = (para -> maxDepth) + 1;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        split(line,ll," \t");
        int sum = 0;
        for (int i = 2; i < ll.size(); i++){
            sum += string2Int(ll[i]);
        }
        if(sum > minDepth & sum < maxDepth){
            ouf << ll[0] << "\t" << ll[1] << "\t" << sum << "\n";
        }
    }
    ouf.close();
    return 1;
}
int vcfAddID(parameter *para){
    string input = (para->inFile);
    igzstream inf (input.c_str(),ifstream::in);
    string outFile =(para -> outFile);
    ofstream  ouf((outFile).c_str());
    string line;
    vector < string >  ll;
    int num = 0;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        split(line,ll," \t");
        if(line[0] == '#'){
            ouf << line << "\n";
            continue;
        }
        string ID = ll[0] + "_" + ll[1];
        string IDs = "rs"+ID;
        ll[2] = IDs;
        ouf << ll[0];
//        string geno = ll[ll.size() - 1];
//        string gphased = geno.replace(1,1,"|");
//        ll[ll.size()-1] = geno;
        for (int i = 1 ; i < ll.size(); i++){
            ouf << "\t" << ll[i];
        }
        ouf << "\n";
        num++;
    }
    cout << "Total marker for " << input << ":\t" << num << endl;
    ouf.close();
    return 1;
}
int filterDepth3(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    string input3 = (para -> inFile3);
    igzstream f1 (input1.c_str(),ifstream::in);
    igzstream f2 (input2.c_str(),ifstream::in);
    igzstream f3 (input3.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    if(f2.fail()){
        cerr << "open File IN error: " << input2 << endl;
        return 0;
    }
    if(f3.fail()){
        cerr << "open File IN error: " << input3 << endl;
        return 0;
    }
//    cout << input1 << endl;
//    cout << input2 << endl;
//    cout << input3 << endl;
    string outFile =(para -> outFile);
    ofstream  OUT((outFile).c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    ofstream log((para->outFile+".log").c_str());
    if((!log.good())){
        cerr << "open log File error" << endl;
        return  0;
    }
    string l1, l2,l3;
    vector < string >  ll1,ll2,ll3;
    vector <double> ll;
    int j = 0;
    while(!f1.eof()&&!f2.eof()&&!f3.eof()){
        getline(f1,l1);
        getline(f2,l2);
        getline(f3,l3);
        ll1.clear();
        ll2.clear();
        ll3.clear();
        ll.clear();
        split(l1, ll1,"\t");
        split(l2, ll2,"\t");
        split(l3, ll3,"\t");

        for(int i = 2, len = ll1.size(); i < len ; ++i){
            ll.push_back(string2Double(ll1[i]));
        }
        for(int i = 2, len = ll2.size(); i < len ; ++i){
           ll.push_back(string2Double(ll2[i]));
        }
        for(int i = 2, len = ll3.size(); i < len ; ++i){
           ll.push_back(string2Double(ll3[i]));
        }
        
//        cout << ll.size() << endl;
//        for(int a = 250; a < 272;a++){
//            cout<< ll[a] << "\t";
//        }
//        cout << "\n" << endl;
        bool pass = depthTest(ll,para->a,para->b,para->minDepth,para-> maxDepth,para->depthSD);
        if(pass){
            j++;
            OUT << ll1[0];
            OUT << "\t";
            OUT << ll1[1];
            OUT << "\n";
        }
//        if(lineNum % 100 ==0){
//            cout << lineNum << endl;
//        }
        
    }
    cout << para->logFile << endl;
    log << "passed sites is: " << j ;
    f1.close();
    f2.close();
    f3.close();
    OUT.close();
    log.close();
    return 1;
}

int filterDepth_bySimulation3(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    string input3 = (para -> inFile3);
    double mean = (para -> mean);
    igzstream f1 (input1.c_str(),ifstream::in);
    igzstream f2 (input2.c_str(),ifstream::in);
    igzstream f3 (input3.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    if(f2.fail()){
        cerr << "open File IN error: " << input2 << endl;
        return 0;
    }
    if(f3.fail()){
        cerr << "open File IN error: " << input3 << endl;
        return 0;
    }
    
    string outFile =(para -> outFile);
    ofstream  OUT((outFile).c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    ofstream log((para->outFile+".log").c_str());
    if((!log.good())){
        cerr << "open log File error" << endl;
        return  0;
    }
    string l1, l2,l3;
    vector < string >  ll1,ll2,ll3;
    vector <double> ll;
    int j = 0;
    map <int,vector<double>> dmm ;
    bool first = true;
    while(!f1.eof()&&!f2.eof()&&!f3.eof()){
        getline(f1,l1);
        getline(f2,l2);
        getline(f3,l3);
        ll1.clear();
        ll2.clear();
        ll3.clear();
        ll.clear();
        if(l1.length()<1) continue;
        if(l2.length()<1) continue;
        if(l3.length()<1) continue;
        split(l1, ll1," \t");
        split(l2, ll2," \t");
        split(l3, ll3," \t");
        
        for(int i = 2, len = ll1.size(); i < len ; ++i){
            ll.push_back(string2Double(ll1[i]));
        }
        for(int i = 2, len = ll2.size(); i < len ; ++i){
            ll.push_back(string2Double(ll2[i]));
        }
        for(int i = 2, len = ll3.size(); i < len ; ++i){
            ll.push_back(string2Double(ll3[i]));
        }
        if(first){
            cout << "simulation process: start" <<endl;
            dmm = depth_min_max (ll.size(),mean);
            first = false;
            cout << "simulation process: end" <<endl;
        }
        bool pass = depthFilter(ll,dmm);
//        cout << l1 << endl;
        if(pass){
            j++;
            OUT << ll1[0];
            OUT << "\t";
            OUT << ll1[1];
            OUT << "\n";
            
        }
    }
    cout << para->logFile << endl;
    log << "passed sites is: " << j ;
    f1.close();
    f2.close();
    f3.close();
    OUT.close();
    log.close();
    return 1;
}
int filterDepth_bySimulation(parameter *para){
    string input1 = (para->inFile);
    double mean = (para -> mean);
    igzstream f1 (input1.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    
    string outFile =(para -> outFile);
    ofstream  OUT((outFile).c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    ofstream log((para->outFile+".log").c_str());
    if((!log.good())){
        cerr << "open log File error" << endl;
        return  0;
    }
    string l1;
    vector < string >  ll1;
    vector <double> ll;
    int j = 0;
    map <int,vector<double>> dmm ;
    bool first = true;
    while(!f1.eof()){
        getline(f1,l1);
        
        ll1.clear();
        
        ll.clear();
        split(l1, ll1,"\t");
        
        for(int i = 2, len = ll1.size(); i < len ; ++i){
            ll.push_back(string2Double(ll1[i]));
        }
    
        if(first){
            cout << "simulation process: start" <<endl;
            dmm = depth_min_max (ll.size(),mean);
            first = false;
            cout << "simulation process: end" <<endl;
        }
        bool pass = depthFilter(ll,dmm);
        if(pass){
            j++;
            OUT << ll1[0];
            OUT << "\t";
            OUT << ll1[1];
            OUT << "\n";
        }
    }
    cout << para->logFile << endl;
    log << "passed sites is: " << j ;
    f1.close();
    OUT.close();
    log.close();
    return 1;
}
int filterDepth2(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    igzstream f1 (input1.c_str(),ifstream::in);
    igzstream f2 (input2.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    if(f2.fail()){
        cerr << "open File IN error: " << input2 << endl;
        return 0;
    }
    
    string outFile =(para -> outFile);
    ofstream  OUT((outFile).c_str());
    ofstream log((para->outFile+".log").c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    if((!log.good())){
        cerr << "open log File error" << endl;
        return  0;
    }
    
    string l1, l2;
    vector < string >  ll1,ll2;
    vector <double> ll;
    int j = 0;
    while(!f1.eof()&&!f2.eof()){
        getline(f1,l1);
        getline(f2,l2);
        ll1.clear();
        ll2.clear();
        ll.clear();
        split(l1, ll1,"\t");
        split(l2, ll2,"\t");
        for(int i = 2, len = ll1.size(); i < len ; ++i){
            ll.push_back(string2Double(ll1[i]));
        }
        for(int i = 2, len = ll2.size(); i < len ; ++i){
            ll.push_back(string2Double(ll2[i]));
        }
        bool pass =depthTest(ll,para->a,para->b,para->minDepth,para-> maxDepth,para->depthSD);
        if(pass){
            j++;
            OUT << ll1[0];
            OUT << "\t";
            OUT << ll1[1];
            OUT << "\n";
        }
    }
    
    log << "passed sites is: " << j  ;
    f1.close();
    f2.close();
    OUT.close();
    log.close();
    return 1;
}
int substract(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    igzstream inf1 (input1.c_str(),ifstream::in);
    igzstream inf2 (input2.c_str(),ifstream::in);
    if(inf1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    string outFile =(para -> outFile);
    ofstream  ouf ((outFile).c_str());
    if((!ouf.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    string line;
    vector<string> ll;
    set<string> pos;
    while (!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        if(line[0] == '#') continue;
        if(line[0] == 'C' | line[0] == 'c') continue;
        split(line,ll,"\t");
        pos.insert(ll[1]);
    }
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length() < 1 ) continue;
        if(line[0] == '#') {
            ouf << line << "\n";
            continue;
        }
        ll.clear();
        split(line,ll,"\t");
        if(pos.count(ll[1]) == 1) {
            ouf << line << "\n";
        }
    }
    ouf.close();
    return 0;
    
}
int subtractFQ(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    igzstream inf1 (input1.c_str(),ifstream::in);
    igzstream inf2 (input2.c_str(),ifstream::in);
    if(inf1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    
    string line;
    vector<string> ll;
    set<string> readsID;
    while (!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        if(line[0] == '#') continue;
        readsID.insert(line);
    }
    cout << "ID readed!" << endl;
    int threshold = (para -> threshold);
    if(readsID.size() < threshold){
        cout << "Reads number doesn't meet, exit!" << endl;
        return 0;
    }
    string outFile =(para -> outFile);
    ofstream  ouf ((outFile).c_str());
    if((!ouf.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    bool write=false;
    int cl = 0;
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length() < 1 ) continue;
        cl++;
        if (cl % 400000 == 0){
            cout << "Current reads: " << cl/1000/4 << "K..." << endl;
        }
        if(line[0] == '@' && ( (cl-1) % 4 == 0)) {
            write = false;
            if(readsID.count(line.substr(1,line.length()-1))) write = true;
        }
        if(write){
            ouf << line << "\n";
        }
    }
    ouf.close();
    return 0;
    
}

int subtractFQgroups(parameter *para){
    string input1 = (para->inFile); // fastq文件
    string input2 = (para->inFile2); // contigID file
    igzstream inf1 (input1.c_str(),ifstream::in);
    igzstream inf2 (input2.c_str(),ifstream::in);
    if(inf1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    string outFile =(para -> outFile);
//    ofstream  ouf ((outFile).c_str());
  
    string line;
    vector<string> ll;
    map<string,string> R2C; // reads ID is key, contig ID is value;
    map<string,vector<set<string>>> C2G; // contig ID is key, group info is value;
    map<string,vector<string>> GQ;
    cout << "Reading group info..." << endl;
    while (!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        igzstream inf3 ((line + ".groupIDs.txt").c_str(),ifstream::in);
        string line3;
        vector<set<string>> readsID;
        vector<string> fq;
        while (!inf3.eof()){
            getline(inf3,line3);
            if(line3.length() < 1) continue;
            set<string> g;
            split(line3,ll," \t");
            for (int i = 0; i < ll.size(); i++){
                replaceAll(ll[i],".","/");
                g.insert(ll[i]);
                R2C.insert(pair<string,string>(ll[i],line));
            }
            readsID.push_back(g);
            fq.push_back("");
        }
//        cout << line << " readed!" << endl;
        C2G.insert(pair<string,vector<set<string>>>(line,readsID));
        GQ.insert(pair<string,vector<string>>(line,fq));
        if (fq.size() != readsID.size()) cerr << "fq size is:\t" << fq.size()
            << "; readsID size is:\t" << readsID.size() << endl;
        inf3.close();
    }
   
    // subtract
    cout << "Group info readed!" << endl;
    bool write=false;
    int cl = 0;
    string C;
    int pos;
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length() < 1 ) continue;
        cl++;
        if (cl % 400000 == 0){
            cout << "Current reads: " << cl/1000/4 << "K..." << endl;
        }
        
        if(line[0] == '@' && ( (cl-1) % 4 == 0)) {
            write = false;
            string ID = line.substr(1,line.length()-1);
            if(R2C.count(ID)) {
                write = true;
                C = R2C[ID];
                vector<set<string>> G = C2G[C];
                for (int i = 0; i < G.size(); i++){
                    set<string> gr = G[i];
                    if (gr.count(ID) == 1){
                        pos = i;
                        break;
                    }
                }
            }
        }
        
        if(write){
            vector<string> n = GQ[C];
            string ss = n[pos];
            string sn = ss + line + "\n";
            n[pos] = sn;
            GQ[C] = n;
//            ouf << line << "\n";
        }
    }
    // get summary of the groups;
    ofstream  oufs ((outFile + ".summary.txt").c_str());
    map<string,vector<set<string>>>::iterator it;
    for (it = C2G.begin(); it != C2G.end(); it++){
        string cID = it->first;
        vector<set<string>> cGroup = it->second;
        oufs << cID << "\t" << cGroup.size();
        int sum = 0;
        for (int i = 0; i < cGroup.size(); i++){
            sum += cGroup[i].size();
        }
        oufs << "\t" << sum << "\n";
    }
    oufs.close();
    
    map<string,vector<string>>::iterator gqit;
    for (gqit = GQ.begin(); gqit != GQ.end(); gqit++){
        string gID = gqit->first;
        vector<string> gQ = gqit->second;
        for (int i = 0; i < gQ.size(); i++){
            ofstream  ouf ((outFile + "."+ gID + ".group" + Int2String(i) + ".fastq").c_str());
            ouf << gQ[i];
            ouf.close();
        }
    }
   
    return 0;
    
}

int subtractFQBygroups(parameter *para){
    string input1 = (para->inFile); // fastq文件
    string input2 = (para->inFile2); // group ID file, the first colunme is path; the second colume is ID for output
    igzstream inf1 (input1.c_str(),ifstream::in);
    igzstream inf2 (input2.c_str(),ifstream::in);
    if(inf1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    string outFile =(para -> outFile);
//    ofstream  ouf ((outFile).c_str());
  
    string line;
    vector<string> ll;
    map<string,string> R2C; // reads ID is key, contig ID is value;
    map<string,vector<set<string>>> C2G; // contig ID is key, group info is value;
    map<string,vector<string>> GQ;
    cout << "Reading group info..." << endl;
    while (!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        split(line,ll," \t");
        igzstream inf3 ((ll[0]).c_str(),ifstream::in);
        string outID = ll[1];
        string line3;
        vector<set<string>> readsID;
        vector<string> fq;
        int nfq = 0;
        while (!inf3.eof()){
            getline(inf3,line3);
            if(line3.length() < 1) continue;
            nfq++;
            set<string> g;
            split(line3,ll," \t");
            for (int i = 0; i < ll.size(); i++){
                replaceAll(ll[i],".","/");
                g.insert(ll[i]);
                R2C.insert(pair<string,string>(ll[i],outID));
            }
            readsID.push_back(g);
            fq.push_back("");
        }
        if (nfq < 1000) continue;
//        cout << line << " readed!" << endl;
        C2G.insert(pair<string,vector<set<string>>>(outID,readsID));
        GQ.insert(pair<string,vector<string>>(outID,fq));
        if (fq.size() != readsID.size()) cerr << "fq size is:\t" << fq.size()
            << "; readsID size is:\t" << readsID.size() << endl;
        inf3.close();
    }
   
    // subtract
    cout << "Group info readed! " << GQ.size() << " groups found!" << endl;
    bool write=false;
    int cl = 0;
    string C;
    int pos;
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length() < 1 ) continue;
        cl++;
        if (cl % 400000 == 0){
            cout << "Current reads: " << cl/1000/4 << "K..." << endl;
        }
        
        if(line[0] == '@' && ( (cl-1) % 4 == 0)) {
            write = false;
            string ID = line.substr(1,line.length()-1);
            if(R2C.count(ID)) {
                write = true;
                C = R2C[ID];
                vector<set<string>> G = C2G[C];
                for (int i = 0; i < G.size(); i++){
                    set<string> gr = G[i];
                    if (gr.count(ID) == 1){
                        pos = i;
                        break;
                    }
                }
            }
        }
        
        if(write){
            vector<string> n = GQ[C];
            string ss = n[pos];
            string sn = ss + line + "\n";
            n[pos] = sn;
            GQ[C] = n;
//            ouf << line << "\n";
        }
    }
    // get summary of the groups;
    ofstream  oufs ((outFile + ".summary.txt").c_str());
    map<string,vector<set<string>>>::iterator it;
    for (it = C2G.begin(); it != C2G.end(); it++){
        string cID = it->first;
        vector<set<string>> cGroup = it->second;
        oufs << cID << "\t" << cGroup.size();
        int sum = 0;
        for (int i = 0; i < cGroup.size(); i++){
            sum += cGroup[i].size();
        }
        oufs << "\t" << sum << "\n";
    }
    oufs.close();
    
    map<string,vector<string>>::iterator gqit;
    for (gqit = GQ.begin(); gqit != GQ.end(); gqit++){
        string gID = gqit->first;
        vector<string> gQ = gqit->second;
        for (int i = 0; i < gQ.size(); i++){
            ofstream  ouf ((outFile + "."+ gID + ".fastq").c_str());
            ouf << gQ[i];
            ouf.close();
        }
    }
   
    return 0;
    
}
int filterDepth(parameter *para){
    string input1 = (para->inFile);
    igzstream f1 (input1.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
   
    
    string outFile =(para -> outFile);
    ofstream  OUT((outFile).c_str());
    ofstream log((para->outFile+".log").c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    if((!log.good())){
        cerr << "open log File error" << endl;
        return  0;
    }
    
    string l1, l2;
    vector < string >  ll1,ll2;
    vector <double> ll;
    int j = 0;
    while(!f1.eof()){
        getline(f1,l1);
        if(l1.length() < 1) continue;
        ll1.clear();
        ll.clear();
        split(l1, ll1,"\t");
        for(int i = 2, len = ll1.size(); i < len ; ++i){
            ll.push_back(string2Double(ll1[i]));
        }
        
        bool pass =depthTest(ll,para->a,para->b,para->minDepth,para-> maxDepth,para->depthSD);
        if(pass){
            j++;
            OUT << ll1[0];
            OUT << "\t";
            OUT << ll1[1];
            OUT << "\n";
        }
    }
    log << "passed sites is: " << j  ;
    f1.close();
    OUT.close();
    log.close();
    return 1;
}
int filterDepth_bySimulation2(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    double mean = (para->mean);
    igzstream f1 (input1.c_str(),ifstream::in);
    igzstream f2 (input2.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    if(f2.fail()){
        cerr << "open File IN error: " << input2 << endl;
        return 0;
    }
    string outFile =(para -> outFile);
    ofstream  OUT((outFile).c_str());
    ofstream log((para->outFile+".log").c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    if((!log.good())){
        cerr << "open log File error" << endl;
        return  0;
    }
    
    string l1, l2;
    vector < string >  ll1,ll2;
    vector <double> ll;
    int j = 0;
    map <int,vector<double>> dmm ;
    bool first = true;
    while(!f1.eof()&&!f2.eof()){
        getline(f1,l1);
        getline(f2,l2);
        ll1.clear();
        ll2.clear();
        ll.clear();
        split(l1, ll1," \t");
        split(l2, ll2," \t");
        for(int i = 2, len = ll1.size(); i < len ; ++i){
            ll.push_back(string2Double(ll1[i]));
        }
        for(int i = 2, len = ll2.size(); i < len ; ++i){
            ll.push_back(string2Double(ll2[i]));
        }
        if(first){
            cout << "simulation process: start" << endl;
            dmm = depth_min_max (ll.size(),mean);
            first = false;
//            cout << dmm[400][1] << endl;
//            cout << dmm[400][0]<< endl;
//            cout << "simulation process: end" << endl;
        }
        bool pass = depthFilter(ll,dmm);
        if(pass){
            j++;
            OUT << ll1[0];
            OUT << "\t";
            OUT << ll1[1];
            OUT << "\n";
        }
    }
    log << "passed sites is: " << j  ;
    f1.close();
    f2.close();
    OUT.close();
    log.close();
    return 1;
}
int mergeSynteny(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    igzstream inf1 (input1.c_str(),ifstream::in);
    igzstream inf2 (input2.c_str(),ifstream::in);
    if(inf1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    
    if(inf2.fail()){
        cerr << "open File IN error: " << input2 << endl;
        return 0;
    }
    string outFile =(para -> outFile);
    ofstream  ouf ((outFile).c_str());
    if((!ouf.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    string line;
    vector<string> ll;
    int pos;
    set<int> pos1;
    while (!inf1.eof()){
        getline(inf1,line);
        if(line.length() < 1) continue;
        split(line,ll,"\t");
        pos = string2Int(ll[1]);
        pos1.insert(pos);
    }
    int passed = 0;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        split(line,ll,"\t");
        pos = string2Int(ll[1]);
        if(pos1.count(pos)==1){
            ouf << line << "\n";
            passed++;
        }
    }
    cout << "Passed number is:\t" << passed << endl;
    return 0;
}

int Syn2HapScan(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    string input3 = (para->inFile3);
    igzstream inf1 (input1.c_str(),ifstream::in);
    igzstream inf2 (input2.c_str(),ifstream::in);
    igzstream inf3 (input3.c_str(),ifstream::in);
    if(inf1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    
    if(inf2.fail()){
        cerr << "open File IN error: " << input2 << endl;
        return 0;
    }
    if(inf3.fail()){
        cerr << "open File IN error: " << input3 << endl;
        return 0;
    }
    
    string outFile =(para -> outFile);
    string hapPos = outFile + ".pos.txt";
    string allele = outFile + ".allele.txt";
    ofstream  hapPosf ((hapPos).c_str());
    ofstream  allelef ((allele).c_str());
    if((!hapPosf.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    string line;
    vector<string> ll;
    map<string,string> pos1;
    map<string,string> pos2;
    while (!inf1.eof()){
        getline(inf1,line);
        if(line.length() < 1) continue;
        if(line[0] =='#') continue;
        split(line,ll,"\t");
        pos1.insert((pair<string,string>(ll[1],ll[3] +"\t"+ll[4])));
    }
    cout << "File1 readed!" << endl;
    while (!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        if(line[0] =='#') continue;
        split(line,ll,"\t");
        pos2.insert((pair<string,string>(ll[1],ll[3]+"\t"+ll[4])));
    }
    cout << "File2 readed!" << endl;
    
    allelef << "Chr\tPos\tRef\tAlt\n" ;
    while(!inf3.eof()){
        getline(inf3,line);
        if(line.length() < 1) continue;
        split(line, ll, "\t");
        int a = pos1.count(ll[1]);
        int b = pos2.count(ll[1]);
        if( a == 1 | b == 1){
            if (a == 0 ){
                hapPosf << ll[0] << "\t" << ll[1] << "\n";
                allelef << ll[0] << "\t" << ll[1] << "\t";
                allelef << pos2[ll[1]] << "\n";
            }else if (b == 0){
                hapPosf << ll[0] << "\t" << ll[1] << "\n";
                allelef << ll[0] << "\t" << ll[1] << "\t";
                allelef << pos1[ll[1]] << "\n";
            }else{
                if (pos1[ll[1]] == pos2[ll[1]]){
                    hapPosf << ll[0] << "\t" << ll[1] << "\n";
                    allelef << line << "\t";
                    allelef << pos1[ll[1]] << "\n";
                }
            }
        }
    }
    hapPosf.close();
    allelef.close();
    return 0;
}
int randChoose(parameter *para){
    double r = (para->r);
    string input1 = (para->inFile);
    int head = (para->headLine);
    igzstream f1 (input1.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    
    string outFile =(para -> outFile);
    ofstream  OUT((outFile).c_str());
    if((!OUT.good())){
        cerr << "open OUT File error: " << outFile << endl;
        return  0;
    }
    
    string l;
    double ra = 1 /double(RAND_MAX) ;
    int chosed = 0;
    int pline = 0;
    while(!f1.eof()){
        getline(f1,l);
        if(l.length()<1) continue;
        pline++;
        if(pline < head+1) continue;
        
        if(l[0]=='#') {
            OUT << l ;
            OUT << "\n";
            continue;
        };
        if(rand() * ra < r){
            OUT << l;
            OUT << "\n";
            ++chosed;
        }
    }
    f1.close();
    OUT.close();
    cout << "chosen number is: " << chosed << endl;
    return 1;
}

int intersectFile(parameter *para){
    /* Object: intersect file, if the position in File2 are also contained in File1
     output the content in file2
     */
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    igzstream f1 (input1.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    igzstream f2 (input2.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input2 << endl;
        return 0;
    }
    string outFile =(para -> outFile);
    ofstream  OUT((outFile).c_str());
    
    string logFile =(para -> outFile) + ".log";
    ofstream log ((logFile).c_str());
    set < string > pos;
    string l1;
    vector<string> ll1;
    while(!f1.eof()){
        getline(f1, l1);
        if(l1.length() < 1) continue;
        if(l1[0]=='#') continue;
        ll1.clear();
        split(l1,ll1,"\t");
        pos.insert(ll1[0]+"_"+ll1[1]);
    }
    f1.close();
    int lineNum = 0;
    while(!f2.eof()){
        getline(f2, l1);
        if(l1.length() < 1) continue;
        if(l1[0] == '#'){
            if(para->recode){
                OUT << l1;
                OUT << "\n";
            }
        }else{
            ll1.clear();
            split(l1, ll1,"\t");
            if(pos.count(ll1[0]+"_"+ll1[1])==1){
                ++lineNum;
                if(para->recode){
                    OUT << l1;
                    OUT << "\n";
                }
            }
        }
    }
    log << "SNP number is: " << lineNum << "\n";
    log.close();
    f2.close();
    OUT.close();
    return 1;
}
int diffFile(parameter *para){
    /* Object: different file, if the position in File2 are not contained in File1
     output the content in file2
     */
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    igzstream f1 (input1.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    igzstream f2 (input2.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input2 << endl;
        return 0;
    }
    string outFile =(para -> outFile);
    ofstream  OUT((outFile).c_str());
    set < string > pos;
    string l1;
    vector<string> ll1;
    while(!f1.eof()){
        getline(f1, l1);
        if(l1.length() < 1) continue;
        pos.insert(l1);
    }
    f1.close();
    while(!f2.eof()){
        getline(f2, l1);
        if(l1.length() < 1) continue;
        if(pos.count(l1)==0){
            OUT << l1;
            OUT << "\n";
        }
    }
    f2.close();
    OUT.close();
    return 1;
}
int getPos(parameter *para){
    string input1 = (para->inFile);
    string output2 = (para->inFile2); // pos txt
    string output = (para->outFile); // allele txt
    igzstream f1 (input1.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    ofstream outf (output.c_str());
    if(outf.fail()){
        cerr << "open File IN error: " << output << endl;
        return 0;
    }
    ofstream outf2 (output2.c_str());
    if(outf.fail()){
        cerr << "open File IN error: " << output2 << endl;
        return 0;
    }
    string line;
    vector <string> ll;
    outf << "Chr\t" << "Pos\t" << "Ref\t" << "Alt\n";
    while(!f1.eof()){
        getline(f1,line);
        if(line.length()<1) continue;
        if(line[0]=='#') continue;
        ll.clear();
        split(line,ll,"\t");
        outf << ll[0] << "\t" << ll[1] << "\t" << ll[3] << "\t" << ll[4] << "\n";
        outf2 << ll[0] << "\t" << ll[1] << "\n";
    }
    f1.close();
    outf.close();
    outf2.close();
    return 1;
}
int filterBarley(parameter *para){
    string input1 = (para->inFile);
    igzstream inf (input1.c_str(),ifstream::in);
    if(inf.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    string outfile = (para->outFile);
    ogzstream ouf (outfile.c_str());
    if(ouf.fail()){
        cerr << "Open File out error" << outfile << endl;
        return 0;
    }
    vector <string> ll;
    string line;
    int passed = 0;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1 ) continue;
        if(line[0]== '#') {
            ouf << line << "\n";
        }else{
            ll.clear();
            split(line,ll,"\t");
            if (ll[ll.size()-1][0] != '.'){
                ouf << line << "\n";
                passed++;
            }
        }
    }
    ouf.close();
    cout << "Passed Number is:\t" << passed << "\n";
    return 0;
}
int calibarate(parameter *para){
    string input1 = (para->inFile);
    igzstream f1 (input1.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    vector <string> taxa ;
    vector <string> ll;
    string line;
    string outfile = (para->outFile);
    ogzstream OUT (outfile.c_str());
    if(OUT.fail()){
        cerr << "Open File out error" << outfile << endl;
        return 0;
    }
    int passed = 0;
    while(!f1.eof()){
        getline(f1,line);
        if(line.length()<1) continue;
        if(line[0]=='#') {
            OUT << line ;
            OUT << "\n";
            continue;
        };
        ll.clear();
        split(line,ll,"\t");
        if(ll[ll.size()-1][0] == '.'){
            continue;
        }
        if(ll[ll.size()-1][0] == '0'){
            continue;
        }
        ++passed;
        OUT << line ;
        OUT << "\n";
    }
    cout << "passed number is: " << passed << endl;
    OUT.close();
    f1.close();
    return 1;
}

int calibarate2(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    igzstream f2 (input2.c_str(),ifstream::in);
    igzstream f1 (input1.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    if(f2.fail()){
        cerr << "open File2 IN error: " << input2 << endl;
        return 0;
    }
    vector <string> taxa ;
    vector <string> ll;
    string line;
    string outfile = (para->outFile);
    ogzstream OUT (outfile.c_str());
    if(OUT.fail()){
        cerr << "Open File out error" << outfile << endl;
        return 0;
    }
    set <string> pos;
    while(!f2.eof()){
        getline(f2,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll,"\t");
        pos.insert(ll[0]);
    }
    int passed = 0;
    while(!f1.eof()){
        getline(f1,line);
        if(line.length()<1) continue;
        if(line[0]=='#' ) {
            OUT << line ;
            if(line[1]=='C'){
                OUT << "\t" << "barley";
            }
            OUT << "\n";
            continue;
        };
        ll.clear();
        split(line,ll,"\t");
        if(ll.size()<2) continue;
        if(pos.count(ll[1])!=1) continue;
        ++passed;
        OUT << line ;
        OUT << "\t" << "1/1:0,10:0,0,100";
        OUT << "\n";
    }
    cout << "passed number is: " << passed << endl;
    OUT.close();
    f1.close();
    return 1;
}
int calibarate3(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    igzstream f2 (input2.c_str(),ifstream::in);
    igzstream f1 (input1.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    if(f2.fail()){
        cerr << "open File2 IN error: " << input2 << endl;
        return 0;
    }
    vector <string> taxa ;
    vector <string> ll;
    map <string,string> pos;
    string line;
    string outfile = (para->outFile);
    ofstream OUT (outfile.c_str());
    if(OUT.fail()){
        cerr << "Open File out error" << outfile << endl;
        return 0;
    }
    while(!f2.eof()){
        getline(f2,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        pos.insert(std::pair<string, string>(ll[0],ll[2]));
    }
    int passed = 0;
    while(!f1.eof()){
        getline(f1,line);
        if(line.length()<1) continue;
        if(line[0]=='#' ) {
            OUT << line ;
            if(line[1]=='C'){
                OUT << "\t" << "barley";
            }
            OUT << "\n";
            continue;
        };
        ll.clear();
        split(line,ll,"\t");
        if(ll.size()<2) continue;
        if(pos[ll[1]].c_str() == ll[4]){
            OUT << line ;
            OUT << "\t" << "1/1:0,10:0,0,100";
            OUT << "\n";
            passed++;
        }else if(pos[ll[1]].c_str() == ll[3]){
            OUT << line ;
            OUT << "\t" << "0/0:0,10:0,0,100";
            OUT << "\n";
            passed++;
        }else{
            continue;
        }
    }
    cout << "passed number is: " << passed << endl;
    OUT.close();
    f1.close();
    return 1;
}
int calibarate4(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    igzstream f2 (input2.c_str(),ifstream::in);
    igzstream f1 (input1.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    if(f2.fail()){
        cerr << "open File2 IN error: " << input2 << endl;
        return 0;
    }
    vector <string> taxa ;
    vector <string> ll;
    map <string,string> pos;
    string line;
    string outfile = (para->outFile);
    ofstream OUT (outfile.c_str());
    if(OUT.fail()){
        cerr << "Open File out error" << outfile << endl;
        return 0;
    }
    while(!f2.eof()){
        getline(f2,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        pos.insert(std::pair<string, string>(ll[0],ll[2]));
    }
    int passed = 0;
    while(!f1.eof()){
        getline(f1,line);
        if(line.length()<1) continue;
        if(line[0]=='#' ) {
            OUT << line ;
            if(line[1]=='C'){
                OUT << "\t" << "barley";
            }
            OUT << "\n";
            continue;
        };
        ll.clear();
        split(line,ll,"\t");
        if(ll.size()<2) continue;
        if(pos[ll[1]].c_str() == ll[4]){
            OUT << line ;
            OUT << "\t" << "1/1:0,10:100,0,0";
            OUT << "\n";
            passed++;
        }else if(pos[ll[1]].c_str() == ll[3]){
            OUT << line ;
            OUT << "\t" << "0/0:0,10:0,0,100";
            OUT << "\n";
            passed++;
        }else{
            OUT << line ;
            OUT << "\t" << "./.:0,0:0,0,0";
            OUT << "\n";
            passed++;
        }
    }
    cout << "passed number is: " << passed << endl;
    OUT.close();
    f1.close();
    return 1;
}
int vcf2bed(parameter *para){
    string fas = (para->inFile);
    igzstream inf (fas.c_str(),ifstream::in);
    if(inf.fail()){
        cerr << "open File IN error: " << fas << endl;
        return 0;
    }
    string outfile = (para->outFile);
    ofstream ouf (outfile.c_str());
    if(ouf.fail()){
        cerr << "Open File out error" << outfile << endl;
        return 0;
    }
    string line;
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '#') continue;
        split(line,ll,"\t");
        ouf << ll[0].substr(0,4) << "\t";
        ouf << Int2String(string2Int(ll[1])-1) << "\t" << ll[1] << "\n";
    }
    ouf.close();
    
    return 0;
}
int maf2pos(parameter *para){
    string fas = (para->inFile);
    igzstream inf (fas.c_str(),ifstream::in);
    if(inf.fail()){
        cerr << "open File IN error: " << fas << endl;
        return 0;
    }
    string outfile = (para->outFile);
    ofstream ouf (outfile.c_str());
    if(ouf.fail()){
        cerr << "Open File out error" << outfile << endl;
        return 0;
    }
    string line;
    vector<string> ll;
    string subChr = para->chr;
    bool newS = false;
    bool write = false;
    string snp = "";
    set<string> base;
    base.insert("A"); base.insert("T"); base.insert("G"); base.insert("C");
    base.insert("a"); base.insert("t"); base.insert("g"); base.insert("c");
    cout << "MAF2POS..." << endl;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '#') continue;
        if(line[0] == 'a') {
            newS = true;
            if (write){
                ouf << snp  << "\n";
            }
            write= false;
            snp = "";
            continue;
        }
        if(newS){
            ll.clear();
            split(line,ll," \t");
            if (ll[6].length() > 1) continue;
            string chr = ll[1].substr(7,4) + subChr;
            snp.append(chr);
            snp.append("\t");
            string ref = ll[6];
            std::transform(ref.begin(), ref.end(), ref.begin(), ::toupper);
            snp.append(Int2String(string2Int(ll[2])+1));
            snp.append("\t");
            snp.append(ref);
            newS = false;
            write = true;
        }else{
            ll.clear();
            split(line,ll," \t");
            if (ll[6].length() > 1) continue;
            string chr = ll[1].substr(7,4) + subChr;
            string alt = ll[6];
            if(alt == "-") {
                write = false;
                continue;
            }
            std::transform(alt.begin(), alt.end(), alt.begin(), ::toupper);
            snp.append("\t");
            snp.append(alt);
        }
        
    }
    if (write){
        ouf << snp  << "\n";
    }
    ouf.close();
    return 0;
}
int checkPos(parameter *para){
    string vcffile = (para->inFile);
    string posfile = (para->inFile2);
    igzstream inf (vcffile.c_str(),ifstream::in);
    igzstream inf2 (posfile.c_str(),ifstream::in);
    if(inf.fail()){
        cerr << "open File IN error: " << vcffile << endl;
        return 0;
    }
    string outfile = (para->outFile);
    ofstream ouf (outfile.c_str());
    if(ouf.fail()){
        cerr << "Open File out error" << outfile << endl;
        return 0;
    }
    vector <string> ll ;
    string line;
    map<string,string> pos;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll," \t");
        pos.insert(pair<string,string>(ll[1],ll[3]));
    }
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '#'){
            ouf << line ;
            if(line[1] == 'C'){
                ouf << "\t" <<"Barley";
            }
            ouf << "\n";
            continue;
        }
        ll.clear();
        split(line,ll,"\t");
        if(pos.count(ll[1]) == 0) continue;
        if(pos[ll[1]] == ll[3]){
            ouf << line << "\t" << "0/0:10,0:0,0,10" << "\n";
        }else if (pos[ll[1]] == (ll[4])){
            ouf << line << "\t" << "1/1:0,10:10,0,0" << "\n";
        }
    }
    ouf.close();
    return 0;
}
int GPMm(parameter *para){
    string fas = (para->inFile);
    igzstream inf (fas.c_str(),ifstream::in);
    if(inf.fail()){
        cerr << "open File IN error: " << fas << endl;
        return 0;
    }
    string outfile = (para->outFile);
    ofstream ouf (outfile.c_str());
    if(ouf.fail()){
        cerr << "Open File out error" << outfile << endl;
        return 0;
    }
    vector <string> ll ;
    string line="";
    bool first = true;
    string N = string(80,'N');
    bool un = false;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0]=='>'){
            if(line[4] == 'U'){
                if(first){
                    ouf << ">ChrUn\n";
                    first = false;
                }else{
                    ouf << N << "\n";
                }
                un = true;
            }else{
                split(line,ll," \t");
                ouf << ll[0] << "\n";
            }
        }else{
            if (line.length() < 80){
                ouf << line;
                ouf << string(80 - line.length(),'N');
                ouf << "\n";
            }else{
                ouf << line << "\n";
            }
            
        }
    }
    ouf.close();
    return 1;
}
int GPMm1(parameter *para){
    string fas = (para->inFile);
    igzstream inf (fas.c_str(),ifstream::in);
    if(inf.fail()){
        cerr << "open File IN error: " << fas << endl;
        return 0;
    }
    string outfile = (para->outFile);
    ofstream ouf (outfile.c_str());
    if(ouf.fail()){
        cerr << "Open File out error" << outfile << endl;
        return 0;
    }
    vector <string> ll ;
    string line="";
    bool first = true;
    string N = string(80,'N');
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0]=='>'){
            split(line,ll," \t");
            ouf << ll[0] << "\n";
        }else{
            ouf << line << "\n";
        }
    }
    ouf.close();
    return 1;
}
int calibarate5(parameter *para){
    string input1 = (para->inFile);
    string input2 = (para->inFile2);
    string name = (para->headerC);
    igzstream f2 (input2.c_str(),ifstream::in);
    igzstream f1 (input1.c_str(),ifstream::in);
    if(f1.fail()){
        cerr << "open File IN error: " << input1 << endl;
        return 0;
    }
    if(f2.fail()){
        cerr << "open File2 IN error: " << input2 << endl;
        return 0;
    }
    vector <string> taxa ;
    vector <string> ll;
    map <string,string> pos;
    string line;
    string outfile = (para->outFile);
    ofstream OUT (outfile.c_str());
    if(OUT.fail()){
        cerr << "Open File out error" << outfile << endl;
        return 0;
    }
    while(!f2.eof()){
        getline(f2,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        pos.insert(std::pair<string, string>(ll[0],ll[2]));
    }
    int passed = 0;
    while(!f1.eof()){
        getline(f1,line);
        if(line.length()<1) continue;
        if(line[0]=='#' ) {
            OUT << line ;
            if(line[1]=='C'){
                OUT << "\t" << name;
            }
            OUT << "\n";
            continue;
        };
        ll.clear();
        split(line,ll,"\t");
        if(ll.size()<2) continue;
        if(pos[ll[1]].c_str() == ll[4]){
            OUT << line ;
            OUT << "\t" << "1/1:0,10:100,0,0";
            OUT << "\n";
            passed++;
        }else if(pos[ll[1]].c_str() == ll[3]){
            OUT << line ;
            OUT << "\t" << "0/0:0,10:0,0,100";
            OUT << "\n";
            passed++;
        }else{
            OUT << line ;
            OUT << "\t" << "./.:0,0:0,0,0";
            OUT << "\n";
            passed++;
        }
    }
    cout << "passed number is: " << passed << endl;
    OUT.close();
    f1.close();
    return 1;
}
int toFasta(parameter *para){
    string inFile1 = (para->inFile);
    string outFile = (para->outFile);
    
    return 1;
}

int getV8(parameter *para){
    string inFile1 = (para -> inFile); // file of scanned
    string inFile2 = (para -> inFile2); // file of V6
    igzstream inf1 (inFile1.c_str(),fstream::in);
    igzstream inf2 (inFile2.c_str(),fstream::in);
    if(inf1.fail()){
        cerr << "Couldn't open file: " << inFile1 << endl;
    }
    if(inf2.fail()){
        cerr << "Couldn't open file: " << inFile2 << endl;
        return 0;
    }
    string outFile = (para->outFile);
    ofstream ouf (outFile.c_str());
    if(ouf.fail()){
        cerr << "Couldn't open file: " << outFile << endl;
        return 0;
    }
    string line1;
    string line2;
    vector <string> ll1, ll2;
    map <string,int> name;
    vector<int> replace_pos;
    while(!inf1.eof()){
        getline(inf1, line1);
        if(line1[0]=='#' && line1[1] == 'C') {
            ll1.clear();
            split(line1,ll1,"\t");
            for(int i = 0 ; i < ll1.size(); ++i){
                name.insert(std::pair<string, int>(ll1[i],i));
            }
            ouf << line1 << "\n" ;
            break;
        }else{
            ouf << line1 << "\n";
        }
    }
    while(!inf2.eof()){
        getline(inf2,line2);
        if(line2[0]=='#' && line2[1] == 'C') {
            ll2.clear();
            split(line2,ll2,"\t");
            for (int i = 0; i < ll2.size(); ++i){
                if(name.count(ll2[i]) < 1){
//                    cerr << "Names in file2 are not present in file1:" << ll2[i] << endl;
                    replace_pos.push_back(-1);
//                    return 0;
                }else{
                    replace_pos.push_back(name[ll2[i]]);
                }
            }
            break;
        }
    }
//    for(int i = 0 ; i < replace_pos.size(); ++i){
//        cout << replace_pos[i] << endl;
//    }
    vector <string> geno;
    while(!inf1.eof() && !inf2.eof()){
        getline(inf1,line1);
        getline(inf2, line2);
        if(line1.length()<1) continue;
        if(line2.length()<1) continue;
        ll1.clear();
        ll2.clear();
        split(line1,ll1,"\t");
        split(line2,ll2,"\t");
        if(ll1[1]!=ll2[1]) {
            cout << line1 << endl;
            cout << line2 << endl;
            cerr << "input files are not mactch!" << endl;
            return 0;
        }
        
        for (int i = 9 ; i < ll2.size(); ++i){
            if(replace_pos[i]<0) continue;
            if(ll2[i][0] == '.'){
                ll2[i] = "./.";
            }else{
                geno.clear();
                split(ll2[i],geno,":");
                
                ll2[i] = geno[0]+":"+geno[1]+":"+geno[geno.size()-1];
            }
            
            ll1[replace_pos[i]] = ll2[i];
        }
        for (int i = 0; i < ll1.size() - 1; ++i){
            ouf << ll1[i] << "\t" ;
        }
        ouf << ll1[ll1.size()-1] << "\n";
    }
    inf1.close();
    inf2.close();
    ouf.close();
    return 1;
}

int Q2CLUMPP(parameter *para){
    string inFile = (para ->inFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0;
    }

    string outFile = (para ->outFile);
    ofstream ouf (outFile.c_str());
    string line;
    vector <string> ll;
    int i = 1;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," ");
        ouf << i << "\t" << i << "\t" << "(x)\t1\t:";
        for (int j = 0; j < ll.size(); ++j){
            ouf << "\t" << ll[j];
        }
        ++i;
        ouf << endl;
    }
    inf.close();
    ouf.close();
    return 1;
}
int CLUMPP2R(parameter *para){
    string inFile = (para->inFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0;
    }
    ofstream ouf ((para->outFile).c_str());
    if(ouf.fail()){
        cerr << "Couldn't opne outFile" << endl;
        return 1;
    }
    string line;
    vector <string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll," \t");
        ouf << ll[5];
        for (int i = 6; i < ll.size(); ++i){
            ouf << "\t" << ll[i] ;
        }
        ouf << endl;
    }
    inf.close();
    ouf.close();
    return 1;
}
int getHeader(parameter *para){
    string inFile = (para->inFile);
    igzstream   inf ((inFile.c_str()),fstream::in);
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    ofstream ouf ((para->outFile).c_str());
    string line;
    vector <string> ll;
    int order = 0;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '#' && line[1] == 'C'){
            split(line, ll,"\t");
            for (int i = 9 ; i < ll.size(); ++i){
                ++order;
                ouf << order << "\t";
                ouf << ll[i] << endl;
            }
            break;
        }
       
    }
    inf.close();
    ouf.close();
    return 1;
}
int get2vcf(parameter *para){
    string inFile = (para->inFile);
    string inFile2 = (para->inFile2);
    igzstream   inf ((inFile.c_str()),fstream::in);
    igzstream inf2 ((inFile2.c_str()),fstream::in);
    
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    if(inf2.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    ofstream ouf ((para->outFile).c_str());
    string line;
    vector <string> ll;
    int previous = 0;
    
    return 0;
}
int changePhy (parameter *para){
    string inFile = (para->inFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    ofstream ouf ((para->outFile).c_str());
    string line;
    vector <string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        ll.clear();
        ouf << line <<endl;
    }
    inf.close();
    ouf.close();
    return 1;
}
int fasta2Phylip(parameter *para){
    string inFile = (para->inFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    ofstream ouf ((para->outFile).c_str());
    string line;
    vector <string> ll;
    vector <string> names;
    vector <string> seqs;
    return 1;
}
int readCDS(parameter *para){
    
    return 1;
}
int getMaximum(parameter *para){
    double m = 0;
    string inFile = (para->inFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    ofstream ouf ((para->outFile).c_str());
    string line;
    vector<string> ll;
    set<int> pos = (para->pos);
    int pos1 = *pos.begin();
    vector<double> value;
    bool Noneg = (para->noNeg);
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0] == 'C') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[pos1]=="inf"||ll[pos1]=="Inf"||ll[pos1]=="NA"||ll[pos1]=="NaN"||ll[pos1]=="-nan"||ll[pos1] == "nan") continue;
        if(Noneg){
            value.push_back(string2Doublepos(ll[pos1]));
        }else{
            value.push_back(string2Double(ll[pos1]));
        }        
    }
    sort(value.begin(),value.end());
    double mean = avg(value);
    int c95 = value.size()*0.95;
    int c99 = value.size()*0.99;
    int c999 = value.size()*0.999;
    ouf << mean << "\t" << value[c95] << "\t" << value[c99] << "\t" << value[c999] << "\t" << value[value.size()-1] << "\n";
    inf.close();
    ouf.close();
    return 1;
}
int merge2vcf (parameter *para){
    string inFile = (para->inFile);
    string inFile2 = (para->inFile2);
    string outFile = (para->outFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    igzstream inf2  ((inFile2.c_str()),fstream::in);
    ofstream ouf ((outFile.c_str()));
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    if(inf2.fail()){
        cerr << "Couldn't open inFile2" << endl;
        return 0 ;
    }
    if(ouf.fail()){
        cerr << "Couldn't open outFile" << endl;
        return 0 ;
    }
    string line,line2;
    vector<string> ll,ll2;
    string header;
    set <string> head;
    vector <int> pos;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1] =='#'){
            continue;
        }
        if(line[0]=='#' && line[1] =='C'){
            ll.clear();
            split(line,ll,"\t");
            for(int i = 0; i < ll.size();++i){
                head.insert(ll[i]);
            }
            header = line;
            break;
        }
    }
    
    while(!inf2.eof())
    {
        getline(inf2,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1] =='#')
        {
            ouf << line << "\n" ;
            continue;
        }
        if(line[0]=='#' && line[1] =='C')
        {
            ll2.clear();
            split(line,ll2," \t");
            ouf << header ;
            for (int i = 0 ; i < ll2.size(); ++i)
            {
                if(head.count(ll2[i])!=1)
                {
                    pos.push_back(i);
                    ouf << "\t" << ll2[i];
                }
            }
            ouf << "\n";
            break;
        }
    }
    
    while(!inf.eof() && !inf2.eof())
    {
        getline(inf,line);
        getline(inf2,line2);
        if (line.length()<1) continue;
        if(line2.length()  < 1) continue;
        ll.clear();
        ll2.clear();
        split(line2,ll2," \t");
        split(line,ll," \t");
        if(ll[1]!=ll2[1]) continue;
        ouf << line ;
        for (int i = 0 ; i < pos.size(); ++i){
            ouf << "\t" << ll2[pos[i]];
        }
        ouf << "\n";
    }
    inf.close();
    inf2.close();
    ouf.close();
    return 1;
}
int union3vcf(parameter *para){
    string inFile = (para->inFile);
    string inFile2 = (para->inFile2);
    string inFile3 = (para->inFile3);
    igzstream inf ((inFile.c_str()),fstream::in);
    igzstream inf2  ((inFile2.c_str()),fstream::in);
    igzstream inf3  ((inFile3.c_str()),fstream::in);
    
    string outFile = (para->outFile);
    return 0;
}
int add2vcf (parameter *para){
    string inFile = (para->inFile);
    string inFile2 = (para->inFile2);
    string outFile = (para->outFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    igzstream inf2  ((inFile2.c_str()),fstream::in);
    ofstream ouf ((outFile.c_str()));
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    if(inf2.fail()){
        cerr << "Couldn't open inFile2" << endl;
        return 0 ;
    }
    if(ouf.fail()){
        cerr << "Couldn't open outFile" << endl;
        return 0 ;
    }
    string line,line2;
    vector<string> ll,ll2;
    string header;
    set <string> head;
    vector <int> pos;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1] =='#'){
            continue;
        }
        if(line[0]=='#' && line[1] =='C'){
            ll.clear();
            split(line,ll,"\t");
            for(int i = 0; i < ll.size();++i){
                head.insert(ll[i]);
            }
            header = line;
            break;
        }
    }
    
    while(!inf2.eof())
    {
        getline(inf2,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1] =='#')
        {
            ouf << line << "\n" ;
            continue;
        }
        if(line[0]=='#' && line[1] =='C')
        {
            ll2.clear();
            split(line,ll2," \t");
            ouf << header ;
            for (int i = 0 ; i < ll2.size(); ++i)
            {
                if(head.count(ll2[i])!=1)
                {
                    pos.push_back(i);
                    ouf << "\t" << ll2[i];
                }
            }
            ouf << "\n";
            break;
        }
    }
    int num = 0;
    while(!inf.eof() && !inf2.eof())
    {
        getline(inf,line);
        getline(inf2,line2);
        if (line.length()<1) continue;
        if(line2.length()  < 1) continue;
        ll.clear();
        ll2.clear();
        split(line2,ll2," \t");
        split(line,ll," \t");
        if(ll[1]!=ll2[1]) continue;
        if(ll2[ll2.size()-1][0]=='.' || ll2[ll2.size()-2][0]=='.') continue;
        if(ll2[ll2.size()-1][0]!=ll2[ll2.size()-1][2] || ll2[ll2.size()-2][0]!=ll2[ll2.size()-2][2] ) continue;
        if(ll2[ll2.size()-1][0]!=ll2[ll2.size()-2][0] ) continue;
        ouf << line ;
        num++;
        for (int i = 0 ; i < pos.size(); ++i){
            ouf << "\t" << ll2[pos[i]];
        }
        ouf << "\n";
    }
    cout << num << " SNPs merged!" << endl;
    inf.close();
    inf2.close();
    ouf.close();
    return 1;
}
int pwpd(parameter *para){
    string inFile = (para->inFile);
    string inFile2 = (para->inFile2);
    string outFile = (para->outFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    igzstream inf2  ((inFile2.c_str()),fstream::in);
    ofstream ouf ((outFile.c_str()));
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    if(inf2.fail()){
        cerr << "Couldn't open inFile2" << endl;
        return 0 ;
    }
    if(ouf.fail()){
        cerr << "Couldn't open outFile" << endl;
        return 0 ;
    }
    string line,line2;
    vector<string> ll,ll2;
    string header = (para->headerC);
    int lh = header.length();
   
    while(!inf.eof()&&!inf2.eof()){
        getline(inf,line);
        getline(inf2,line2);
        if(line.length()<1) continue;
        if(line2.length()<1) continue;
        if((line.substr(0,lh) == header)) {
            ouf << line << "\n";
            continue;
        }
        ll.clear();
        ll2.clear();
        split(line,ll," \t");
        split(line2,ll2," \t");
        
        if(ll2[3] == "NA"||ll2[3] == "-nan"||ll2[3] == "nan")
        {
            ouf << ll[0] << "\t" << ll[1] << "\t" << ll[2] << "\t" << "NA" << "\n";
            continue;
        }
        
        if(ll[3] == "NA"||ll[3] == "-nan"||ll[3] == "nan")
        {
            ouf << ll[0] << "\t" << ll[1] << "\t" << ll[2] << "\t" << "NA" << "\n";
            continue;
        }
        if(string2Double(ll2[3]) == 0 ) ll2[3] = "0.001";
        double pwd = string2Double(ll[3])/(string2Double(ll2[3]));
//        if(ll2[3]=="0") pwd = 10;
        ouf << ll[0] << "\t" << ll[1] << "\t" << ll[2] << "\t" << pwd << "\n";
    }
    inf.close();
    inf2.close();
    ouf.close();
    return 1;
}
int splitByChr(parameter *para){
    string inFile = (para->inFile);
    string outFile = (para->outFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    
    vector<string> header;
    vector<string> ll;
    // read header
    while(!inf.eof()){
        string  line ;
        getline(inf,line);
        if (line.length() < 1 )  {
            continue  ;
        }else if ( line[0] == '#' && line[1] == '#' )  {
            header.push_back(line);
            continue  ;
        }else if ( line[0] == '#' && line[1] != '#' ){
            header.push_back(line);
            ll.clear();
            split(line,ll,"\t");
            if  ( ll[0]  != "#CHROM"){
                continue  ;
            }
            break ;
        }else if ( line[0] != '#' && line[1] != '#' ){
            cerr<<"wrong Line : "<<line<<endl;
            cerr<<"VCF Header same thing wrong, can find sample info before site info"<<endl;
            cerr<<"VCF Header sample info Flag : [  #CHROM  ] "<<endl;
            return  0;
            break;
        }
    }
    string chr = "";
    ofstream ouf ;
    bool first = true;
    while(!inf.eof()){
        string  line ;
        getline(inf,line);
        if (line.length() < 1 )  {
            continue  ;
        }
        ll.clear();
        split(line,ll," \t");
        if(ll[0]==chr){
            ouf << line << "\n" ;
        }else{
            if(first){
                first = false;
                chr = ll[0];
                string outname = outFile+chr+".vcf";
                ofstream ouf ((outname.c_str()));
                continue;
            }else{
                ouf.close();
                string outname = outFile+chr;
                ofstream ouf ((outname.c_str()));
            }
            
        }
    }
    inf.close();
    ouf.close();
    
    return 1;
}
int splitByChrNoHeader(parameter *para){
    string inFile = (para->inFile);
    string outFile = (para->outFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    ofstream ouf ((outFile.c_str()));
    vector<string> ll;
    string chr = (para->chr);
    
    string  line ;
    while(!inf.eof()){
        getline(inf,line);
        if (line.length() < 1 )  {
            continue  ;
        }
        ll.clear();
        split(line,ll," \t");
        if(ll[0]==chr){
            ouf << line << "\n" ;
        }
    }
    
    inf.close();
    ouf.close();
    
    return 1;
}

int splitByChrVCF(parameter *para){
    string inFile = (para->inFile);
    string outFile = (para->outFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    ofstream ouf ((outFile.c_str()));
    vector<string> ll;
    string chr = (para->chr);
    
    string  line ;
    while(!inf.eof()){
        getline(inf,line);
        if (line.length() < 1 )  {
            continue  ;
        }
        if(line[0]=='#'){
            ouf << line << "\n";
        }
        ll.clear();
        split(line,ll," \t");
        if(ll[0]==chr){
            ouf << line << "\n" ;
        }
    }
    
    inf.close();
    ouf.close();
    
    return 1;
}

int byChrs(parameter *para){
    string inFile = (para->inFile);
    string outFile = (para->outFile);
    igzstream inf ((inFile.c_str()),fstream::in);
    if(inf.fail()){
        cerr << "Couldn't open inFile" << endl;
        return 0 ;
    }
    ofstream ouf ((outFile.c_str()));
    vector<string> ll;
    string chr = "";
    string  line ;
    while(!inf.eof()){
        getline(inf,line);
        if (line.length() < 1 )  {
            continue  ;
        }
        ll.clear();
        split(line,ll," \t");
        if(ll[0]==chr){
            ouf << line << "\n" ;
        }
    }
    
    inf.close();
    ouf.close();
    
    return 1;
}
int ct3(parameter *para){
    string inFile1 = (para->inFile);
    string inFile2 = (para->inFile2);
    string inFile3 = (para->inFile3);
    string bedFile = (para->bedFile);
    string outFile = (para->outFile);
    igzstream inf1 ((inFile1).c_str(),ifstream::in);
    igzstream inf2 ((inFile2).c_str(),ifstream::in);
    igzstream inf3 ((inFile3).c_str(),ifstream::in);
    igzstream vcf ((bedFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    set <string> g1;
    set <string> g2;
    set <string> g3;
    string line;
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length()<1) continue;
        g1.insert(line);
    }
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        g2.insert(line);
    }
    while(!inf3.eof()){
        getline(inf3,line);
        if(line.length()<1) continue;
        g3.insert(line);
    }
    vector <string> ll;
    set<int> gi1,gi2,gi3;
    int c1 = 0, c2 = 0, c3 =0, c4 = 0,c5 = 0,c6 = 0, c7 = 0,c8=0;
    while(!vcf.eof()){
        getline(vcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1]=='#') continue;
        if(line[0]=='#' && line[1]=='C') {
            ll.clear();
            split(line,ll," \t");
            for(int i = 9; i < ll.size(); ++i){
                if(g1.count(ll[i])==1){
                    gi1.insert(i);
                }else if(g2.count(ll[i])==1){
                    gi2.insert(i);
                }else if(g3.count(ll[i])==1){
                    gi3.insert(i);
                }else{
                    continue;
                }
            }
            cout << "group1 size is: " << gi1.size() << endl;
            cout << "group2 size is: " << gi2.size() << endl;
            cout << "group3 size is: " << gi3.size() << endl;
            continue;
        };
        ll.clear();
        bool s1 = false,s2 = false,s3 = false;
        int n = 0;
        int sum = 0;
        split(line,ll," \t");
        for(set<int>::iterator it=gi1.begin() ;it!=gi1.end();it++){
            if(ll[*it][0]=='.') continue;
            n++;
            if(ll[*it][0]=='1'){
                sum++;
            }
            if(ll[*it][2]=='1'){
                sum++;
            }
        }
        if((2*n-sum)>0 && sum > 0) s1= true;
        
        n = 0;
        sum = 0;
        for(set<int>::iterator it=gi2.begin() ;it!=gi2.end();it++){
            if(ll[*it][0] == '.') continue;
            n++;
            if(ll[*it][0]=='1'){
                sum++;
            }
            if(ll[*it][2]=='1'){
                sum++;
            }
        }
        if((2*n-sum)>0 && sum > 0) s2= true;
        
        n = 0;
        sum = 0;
        for(set<int>::iterator it=gi3.begin() ;it!=gi3.end();it++){
            if(ll[*it][0]=='.') continue;
            n++;
            if(ll[*it][0]=='1'){
                sum++;
            }
            if(ll[*it][2]=='1'){
                sum++;
            }
        }
        if((2*n-sum)>0 && sum > 0) s3= true;
        if(s1 && s2 && s3){
            c1++;
        }else
        if(s1 && s2 && (!s3)){
            c2++;
        }else
        if(s1 && (!s2) && s3){
            c3++;
        }else
        if((!s1) && s2 && s3){
            c4++;
        }else
        if(s1 && (!s2) && (!s3)){
            c5++;
        }else
        if((!s1) && s2 && (!s3)){
            c6++;
        }else
        if((!s1) && (!s2) && s3){
            c7++;
        }else{
            c8++;
        }
    }
    ouf << "c1\t" << c1 << "\n";
    ouf << "c2\t" << c2 << "\n";
    ouf << "c3\t" << c3 << "\n";
    ouf << "c4\t" << c4 << "\n";
    ouf << "c5\t" << c5 << "\n";
    ouf << "c6\t" << c6 << "\n";
    ouf << "c7\t" << c7 << "\n";
    ouf << "c8\t" << c8 << "\n";
    inf1.close();
    inf2.close();
    inf3.close();
    vcf.close();
    ouf.close();
    return 1;
}
int ct2(parameter *para){
    string inFile1 = (para->inFile);//group1
    string inFile2 = (para->inFile2);//group2
    string bedFile = (para->bedFile);//vcf
    string outFile = (para->outFile);//output
    igzstream inf1 ((inFile1).c_str(),ifstream::in);
    igzstream inf2 ((inFile2).c_str(),ifstream::in);
    igzstream vcf ((bedFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    set <string> g1;
    set <string> g2;
    string line;
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length()<1) continue;
        g1.insert(line);
    }
    cout << "group1 readed!" << endl;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        g2.insert(line);
    }
    cout << "group2 readed!" << endl;
    vector <string> ll;
    set<int> gi1,gi2;
    int c1 = 0, c2 = 0, c3 =0, c4 = 0;
    while(!vcf.eof()){
        getline(vcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1]=='#') continue;
        if(line[0]=='#' && line[1]=='C') {
            cout << "headering.." << endl;
            ll.clear();
            split(line,ll," \t");
            for(int i = 9; i < ll.size(); ++i){
                if(g1.count(ll[i])==1){
                    gi1.insert(i);
                }else if(g2.count(ll[i])==1){
                    gi2.insert(i);
                }else{
                    continue;
                }
            }
            cout << "group1 size is: " << gi1.size() << endl;
            cout << "group2 size is: " << gi2.size() << endl;
            continue;
        };
        ll.clear();
        bool s1 = false,s2 = false;
        int n = 0,sum = 0;
        split(line,ll," \t");
        for(set<int>::iterator it=gi1.begin() ;it!=gi1.end();it++){
            if(ll[*it][0]=='.'){
                continue;
            }
            n++;
            if(ll[*it][0]=='1'){
                sum++;
            }
            if(ll[*it][2]=='1'){
                sum++;
            }
        }
        if((2*n-sum)>0 && sum > 0) s1= true;
        
        n = 0, sum = 0;
        for(set<int>::iterator it=gi2.begin() ;it!=gi2.end();it++){
            if(ll[*it][0]=='.'){
                continue;
            }
            n++;
            if(ll[*it][0]=='1'){
                sum++;
            }
            if(ll[*it][2]=='1'){
                sum++;
            }
        }
        if((2*n-sum)>0 && sum > 0) s2= true;
        
        
        if(s1 && s2 ){
            c1++; // shared SNPs
        }else if(s1 && !s2 ){
            c2++; // allelic in group1 but not group2
        }else if(!s1 && s2 ){
            c3++; // allelic in group2 but not group1
        }else{
//            cerr << "No cater found! sum is: " << sum << endl;
            c4++; // not allelic in both
        }
    }
    ouf << "allelic in group1 and group2: \t" << c1 << "\n";
    ouf << "allelic in group1: \t" << c2 << "\n";
    ouf << "allelic in group2: \t" << c3 << "\n";
    ouf << "non-allelic in both: \t" << c4 << "\n";
    inf1.close();
    inf2.close();
    vcf.close();
    ouf.close();
    return 1;
}
int ct1(parameter *para){
    string inFile1 = (para->inFile);//group1
//    string inFile2 = (para->inFile2);//group2
    string bedFile = (para->bedFile);//vcf
    string outFile = (para->outFile);//output
    igzstream inf1 ((inFile1).c_str(),ifstream::in);
//    igzstream inf2 ((inFile2).c_str(),ifstream::in);
    igzstream vcf ((bedFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    set <string> g1;
//    set <string> g2;
    string line;
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length()<1) continue;
        g1.insert(line);
    }
    cout << "group1 readed!" << endl;

    vector <string> ll;
    set<int> gi1;
    int c1 = 0, c2 = 0, c3 =0, c4 = 0;
    while(!vcf.eof()){
        getline(vcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1]=='#') continue;
        if(line[0]=='#' && line[1]=='C') {
            cout << "headering.." << endl;
            ll.clear();
            split(line,ll," \t");
            for(int i = 9; i < ll.size(); ++i){
                if(g1.count(ll[i])==1){
                    gi1.insert(i);
                }else{
                    continue;
                }
            }
            cout << "group1 size is: " << gi1.size() << endl;
            continue;
        };
        ll.clear();
        bool s1 = false;
        int n = 0,sum = 0;
        split(line,ll," \t");
        for(set<int>::iterator it=gi1.begin() ;it!=gi1.end();it++){
            if(ll[*it][0]=='.'){
                continue;
            }
            n++;
            if(ll[*it][0]=='1'){
                sum++;
            }
            if(ll[*it][2]=='1'){
                sum++;
            }
        }
        if((2*n-sum)>0 && sum > 0) s1= true;
        if(s1 ){
            c1++; // shared SNPs
        }else{
//            cerr << "No cater found! sum is: " << sum << endl;
            c2++; // not allelic in both
        }
    }
    ouf << "allelic in group1: \t" << c1 << "\n";
    ouf << "non-allelic: \t" << c2 << "\n";
    inf1.close();
    vcf.close();
    ouf.close();
    return 1;
}
int dotdot(parameter *para){
    string inFile1 = (para->inFile);//group1
    string outFile = (para->outFile);//output
    igzstream vcf ((inFile1).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    vector <string> ll;
    int c1 = 0, c2 = 0;
    string line;
    while(!vcf.eof()){
        getline(vcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' ) continue;
        
        ll.clear();
        bool s1 = false,s2 = false, missing =false;
        int n = 0,sum = 0;
        split(line,ll," \t");
        int pre = -1;
        for(int i = 9; i<ll.size(); ++i){
            if(ll[i][0] == '.'){
                missing = true;
                continue;
            }
            n++;
            if(ll[i][0] == '1'){
                sum++;
            }
            
            if(ll[i][2] == '1'){
                sum++;
            }
        }
        if (missing && sum==0 ) s1=true;
        if (sum == 2*n) s2= true;
        if(s1){
            c1++; // shared SNPs
        }else if (s2){
            c2++;
        }
    }
    ouf << "allelic in 0/0 or ./.: \t" << c1 << "\n";
    ouf << "allelic in 1/1 or ./.: \t" << c2 << "\n";
    ouf.close();
    return 1;
}
int getFasta(parameter *para){
    string inFile = (para->inFile);
    string outFile = (para->outFile);
    igzstream inf ((inFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string chr = (para -> chr);
    map<string,string> genome;
    string line;
    string seq;
    string key;
    bool first = true;
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1 ) continue;
        if(line[0] == '>' ){
            if(!first){
                genome.insert(pair<string,string>(key,seq));
            }
            first = false;
            split(line,ll," \t");
            key = ll[0];
            seq = "";
        }else{
            seq.append(line + "\n");
        }
    }
    genome.insert(pair<string,string>(key,seq));
    cout << "Genome readed!" << endl;
    ouf << ">" + chr + "\n" ;
    ouf << genome[">" + chr] ;
    ouf.close();
    return 0;
}
int getFastas(parameter *para){
    string inFile = (para->inFile);
    string inFile2 = (para->inFile2);
    string outFile = (para->outFile);
    igzstream inf ((inFile).c_str(),ifstream::in);
    igzstream inf2 ((inFile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string chr ;
    map<string,string> genome;
    string line;
    string seq;
    string key;
    bool first = true;
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1 ) continue;
        if(line[0] == '>' ){
            if(!first){
                genome.insert(pair<string,string>(key,seq));
            }
            first = false;
            split(line,ll," \t");
            key = ll[0];
            seq = "";
        }else{
            seq.append(line + "\n");
        }
    }
    genome.insert(pair<string,string>(key,seq));
    cout << "Genome readed!" << endl;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1 ) continue;
        chr = line;
        ouf << ">" << line << "\n";
        ouf << genome[">" + chr] ;
    }
    
    ouf.close();
    return 0;
}
int removeContigs(parameter *para){
    string inFile = (para->inFile);
    string inFile2 = (para->inFile2);
    string outFile = (para->outFile);
    igzstream inf ((inFile).c_str(),ifstream::in);
    igzstream inf2 ((inFile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string chr ;
    map<string,string> genome;
    string line;
    string seq;
    string key;
    bool first = true;
    vector<string> ll;
    set<string> rID;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1 ) continue;
        rID.insert(line);
    }
    bool write=false;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1 ) continue;
        if(line[0] == '>' ){
            split(line,ll," \t");
            key = ll[0];
            if (rID.count(key.substr(1,key.length()-1)) == 0){
                write = true;
            }else{
                write = false;
            }
        }
        if (write) {
            ouf << line << "\n";
        }
    }
    ouf.close();
    return 0;
}
int summaryRate(parameter *para){
    string inFile = (para->inFile);
    string inFile2 = (para->inFile2);
    string outFile = (para->outFile);
    igzstream inf ((inFile).c_str(),ifstream::in);
    igzstream inf2 ((inFile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    unordered_map<string, vector<double>> readsID;
    vector<double> initialVector(400);
    string line;
    string key;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1 ) continue;
        if(line[0] == '>' ){
            readsID.insert(pair<string, vector<double>>(line.substr(1,line.length()-1),initialVector));
        }
    }
    int cl = 0;
    while (!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1 ) continue;
        igzstream inf3 ((line).c_str(),ifstream::in);
        vector<string> ll;
        while(!inf3.eof()){
            getline(inf3,line);
            if(line.length() < 1 ) continue;
            split(line,ll,"\t");
            string key = ll[0];
            vector<double> value = readsID[key];
            value[cl] = string2Double(ll[4]);
            readsID[key] = value;
        }
        cl++;
    }
    unordered_map<string, vector<double>>::iterator iter;
    for(iter = readsID.begin(); iter != readsID.end(); iter++){
        ouf << iter->first;
        vector<double> value = iter->second;
        for(int i = 0; i < value.size(); i++){
            ouf << "\t" << value[i];
        }
        ouf << "\n";
    }
    ouf.close();
    return 0;
}
int getReads(parameter *para){
    string inFile = (para->inFile);
    string outFile = (para->outFile);
    string inFile2 = (para->inFile2);
    igzstream inf ((inFile).c_str(),ifstream::in);
    igzstream inf2 ((inFile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string chr = (para -> chr);
    map<string,string> genome;
    string line;
    string seq;
    string key;
    bool first = true;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1 ) continue;
        if(line[0] == '>' ){
            if(!first){
                genome.insert(pair<string,string>(key,seq));
            }
            first = false;
            key = line;
            seq = "";
        }else{
            seq.append(line + "\n");
        }
    }
    genome.insert(pair<string,string>(key,seq));
    cout << "Genome readed!" << endl;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1 ) continue;
        ouf << ">" + line + "\n" ;
        ouf << genome[">" + line] ;
    }
    ouf.close();
    return 0;
}
int splitByN(parameter *para){
    string inFile = (para->inFile);
    string outFile = (para->outFile);
    igzstream inf ((inFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    string seq="";
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1 ) continue;
        if(line[0] == '>' ) continue;
        seq.append(line + "\n");
    }
    cout << "Genome readed!" << endl;
    split(seq,ll,"N");
    for (int i = 0; i < ll.size(); ++i){
        if(ll[i].length() < 150) continue;
        ouf << ">" << i << "\n";
        ouf << ll[i] <<"\n";
    }
    ouf.close();
    return 0;
}
int splitByNAll(parameter *para){
    string inFile = (para->inFile);
    string outFile = (para->outFile);
    igzstream inf ((inFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    string seq="";
    vector<string> ll;
    int contN = 0;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1 ) continue;
        if(line[0] == '>' ) {
            if(seq=="") continue;
            split(seq,ll,"N");
            for (int i = 0; i < ll.size(); ++i){
                contN++;
                ouf << ">" << contN << "\n";
                ouf << ll[i] <<"\n";
            }
            seq = "";
        };
        seq.append(line + "\n");
    }
    split(seq,ll,"N");
    for (int i = 0; i < ll.size(); ++i){
        contN++;
        ouf << ">" << contN << "\n";
        ouf << ll[i] <<"\n";
    }
    ouf.close();
    return 0;
}
//int ct1(parameter *para){
//    string inFile1 = (para->inFile);
//    string vcfFile = (para->bedFile);
//    string outFile = (para->outFile);
//    igzstream inf1 ((inFile1).c_str(),ifstream::in);
//    igzstream vcf ((vcfFile).c_str(),ifstream::in);
//    ofstream ouf ((outFile).c_str());
//    set <string> g1;
//    string line;
//    while(!inf1.eof()){
//        getline(inf1,line);
//        if(line.length()<1) continue;
//        g1.insert(line);
//    }
//    cout << "group1 readed!" << endl;
//    
//    vector <string> ll;
//    set<int> gi1;
//    while(!vcf.eof()){
//        getline(vcf,line);
//        if(line.length()<1) continue;
//        if(line[0]=='#' && line[1]=='#') continue;
//        if(line[0]=='#' && line[1]=='C') {
//            cout << "headering.." << endl;
//            ll.clear();
//            split(line,ll," \t");
//            for(int i = 9; i < ll.size(); ++i){
//                if(g1.count(ll[i])==1){
//                    gi1.insert(i);
//                }else{
//                    continue;
//                }
//            }
//            cout << "group size is: " << gi1.size() << endl;
//            continue;
//        };
//        ll.clear();
//        bool s1 = false;
//        int n = 0,sum = 0;
//        split(line,ll," \t");
//        for(set<int>::iterator it=gi1.begin() ;it!=gi1.end();it++){
//            if(ll[*it][0]=='.'){
//                continue;
//            }
//            n++;
//            if(ll[*it][0]=='1'){
//                sum++;
//            }
//            if(ll[*it][2]=='1'){
//                sum++;
//            }
//        }
//        if((2*n-sum)>0 && sum > 0) s1= true;
//        ouf << s1 << "\n";
//    }
//    inf1.close();
//    vcf.close();
//    ouf.close();
//    return 1;
//}

int addContig(parameter *para){
    string inFile1 = (para->inFile);
    string inFile2 = (para->inFile2);
    string outFile = (para->outFile);
    igzstream inf1 ((inFile1).c_str(),ifstream::in);
    igzstream inf2 ((inFile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string header;
    string line;
    while(!inf1.eof()){
        line.clear();
        getline(inf1,line);
        if(line.length()<1) continue;
        header.append(line);
        header.append("\n");
    }
    inf1.close();
    while(!inf2.eof()){
        line.clear();
        getline(inf2,line);
        if(line.length() < 1) continue;
        if(line[0]=='#' & line[1] == 'C'){
            ouf << header ;
        }
        ouf << line << "\n";
    }
    inf2.close();
    ouf.close();
    return 0;
}
int subMummer4(parameter *para){
    string inFile1 = (para->inFile);
    string inFile2 = (para->inFile2);
    string outFile = (para->outFile);
    igzstream inf1 ((inFile1).c_str(),ifstream::in);
    igzstream inf2 ((inFile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    set <int> snpPos;
    vector<string> ll;
    while(!inf1.eof()){
        getline(inf1, line);
        if(line.length() < 1) continue;
        if(line[0]=='#') continue;
        ll.clear();
        split(line, ll," \t");
        snpPos.insert(string2Int(ll[1]));
    }
    cout << "vcf readed!" << endl;
    bool newAlignment = true;
    string s1,s2;
    int start = 0 , end = 0;
    int missingLength = 0;
//    std::size_t found ;
    string ss1, ss2;
    while(!inf2.eof()){
        line.clear();
        getline(inf2, line);
        if(line.length() < 1) continue;
        if(line[0]==' ') continue;
        if(line[0]=='\t') continue;
        if(line[0]=='=') continue;
//        found = line.find("^");
//        if (found!=std::string::npos) continue;
        ll.clear();
        split(line, ll," \t");
//        for(int i = 0; i < ll.size(); ++i){
//            cout << ll[i] << endl;
//        }
        if(ll[1]=="BEGIN"){
            s1.clear();
            s2.clear();
            newAlignment = true;
            start = string2Int(ll[5]);
            end = string2Int(ll[7]);
            continue;
        }
        if(ll[1]=="END"){
            ss1.clear();
            ss2.clear();
            for (int i =0; i < s1.length(); ++i){
//                cout << s1.substr(i,1) << endl;
                if(s1.substr(i,1) != "."){
                    ss1 += s1[i];
                    ss2 += s2[i];
                }
            }
            for(int i = start; i < end; ++i){
                if(snpPos.count(i)!=0){
                    if(ss2.substr(i-start,1)!="."){
                        ouf << i << "\t"<< (char)toupper(ss1[i-start]) <<"\t"<< (char)toupper(ss2[i-start])<<"\n";
                    }
                }
            }
        }
        if(newAlignment){
            s1.append(ll[1]);
            newAlignment = false;
            continue;
        }else{
            s2.append(ll[1]);
            newAlignment = true;
            continue;
        }
        
    }
    inf1.close();
    inf2.close();
    ouf.close();
    return 0;
}
int changeAncestralAllele(parameter *para){
    string inFile1 = (para->inFile);
    string outFile = (para->outFile);
    igzstream inf1 ((inFile1).c_str(),ifstream::in);
    ogzstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length()<1) continue;
        if(line[0]=='#'){
            ouf << line << "\n" ;
            continue;
        }
        ll.clear();
        split(line,ll," \t");
        ouf << ll[0];
        for(int i = 1; i < ll.size(); ++i){
            if(ll[i].substr(0,3)=="./."){
                ouf << "\t" << "./.";
            }else if (ll[i].substr(0,3)=="1/1"){
                ouf << "\t" << "0/0";
            }else if (ll[i].substr(0,3)=="0/1"){
                ouf << "\t" << "0/1";
            }else if (ll[i].substr(0,3)=="0/0"){
                ouf << "\t" << "1/1";
            }else{
                ouf << "\t" << ll[i];
            }
        }
        ouf << "\n";
    }
    inf1.close();
    ouf.close();
    return 0;
}
int getMaskRegion(parameter *para)
{
    string inFile = (para->inFile);
    string outFile = (para->outFile);
    igzstream inf ((inFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    int pos = 0,prePos = 0;
    int max = (para->maxLength);
    vector<string> ll;
    bool isFirst = false;
    while(!inf.eof())
    {
        getline(inf, line);
        if(line.length()<1) continue;
        ll.clear();
        split(line, ll," \t");
        pos = string2Int(ll[1]);
        if((pos-prePos)>150){
            ouf << ll[0] << "\t" << prePos+1 << "\t" << pos-1 << "\n";
        }
        prePos = pos;
    }
    if(pos < max){
        ouf << ll[0] << "\t" << pos+1 << "\t" << max << "\n";
    }
    inf.close();
    ouf.close();
    return 0;
}

int genePi(parameter *para){
    string gffFile = (para -> inFile);
    string piFile = (para -> inFile2);
    string outFile = (para -> outFile);
    string chr = (para -> chr);
    igzstream infGff ((gffFile).c_str(),ifstream::in);
    igzstream infPi ((piFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    set<int> utr3;
    set<int> utr5;
    set<int> cds;
    set<int> intron;
    set<int> upstream;
    set<int> downstream;
    string line;
    vector<string> ll;
    set<int> withoutIntron;
    int start = 0, end = 0;
    int ps = 0, pe = 0;
    string strand = "";
    while(!infGff.eof()){
        getline(infGff,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[2] =='#'&& withoutIntron.size() > 0) {
            if ( strand == "+"){
                for (int i = ps-2000; i < ps; ++i){
                    upstream.insert(i);
                }
                for (int i = pe+1; i < pe+2000; ++i){
                    downstream.insert(i);
                }
            }else{
                for (int i = ps-2000; i < ps; ++i){
                    downstream.insert(i);
                }
                for (int i = pe+1; i < pe+2000; ++i){
                    upstream.insert(i);
                }
            }
            for ( int i = start; i < end; ++i){
                if(withoutIntron.count(i) == 0){
                    intron.insert(i);
                }
            }
            start = 0;
            end = 0;
            withoutIntron.clear();
            ps = 0;
            pe = 0;
            continue;
        };
        if(line[0]=='#') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0] != chr) continue;
        if(ll[2] == "gene"){
            start = string2Int(ll[3]);
            end = string2Int(ll[4]);
            strand = ll[6];
        }else if (ll[2] == "five_prime_UTR"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                utr5.insert(i);
                withoutIntron.insert(i);
            }
        }else if (ll[2] == "three_prime_UTR"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                utr3.insert(i);
                withoutIntron.insert(i);
            }
        }else if (ll[2] == "CDS"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                cds.insert(i);
                withoutIntron.insert(i);
            }
        }
    }
    if(withoutIntron.size() > 1) {
        for ( int i = start; i < end; ++i){
            if(withoutIntron.count(i)==0){
                intron.insert(i);
            }
        }
        withoutIntron.clear();
    }
    
    cout << "gff3 readed!" << endl;
    
    double size_upstream = 0, size_utr5 = 0, size_cds = 0, size_intron = 0;
    double size_utr3 = 0, size_downstream = 0, size_intergenic = 0;
    
    while(!infPi.eof()){
        getline(infPi,line);
        if(line.length()<1) continue;
        if(line[0]=='C') continue;
        ll.clear();
        split(line, ll," \t");
        if(ll[0]!=chr) continue;
        int pos = string2Int(ll[1]);
        if(ll.size()==3){
            if (ll[2] == "-nan" || ll[2] == "nan" || ll[2] == "na" || ll[2] == "NA") continue;
            if(upstream.count(pos)==1)
            {
                size_upstream += string2Double(ll[2]);
            }
            else if(utr5.count(pos)==1)
            {
                size_utr5 += string2Double(ll[2]);
            }
            else if(cds.count(pos)==1)
            {
                size_cds += string2Double(ll[2]);
            }
            else if(intron.count(pos)==1)
            {
                size_intron += string2Double(ll[2]);
            }
            else if(utr3.count(pos)==1)
            {
                size_utr3 += string2Double(ll[2]);
            }
            else if(downstream.count(pos)==1)
            {
                size_downstream += string2Double(ll[2]);
            }
            else
            {
                size_intergenic += string2Double(ll[2]);
            }
        }else if (ll.size()==2){
            if(upstream.count(pos)==1)
            {
                size_upstream ++;
            }
            else if(utr5.count(pos)==1)
            {
                size_utr5 ++;
            }
            else if(cds.count(pos)==1)
            {
                size_cds ++;
            }
            else if(intron.count(pos)==1)
            {
                size_intron ++;
            }
            else if(utr3.count(pos)==1)
            {
                size_utr3 ++;
            }
            else if(downstream.count(pos)==1)
            {
                size_downstream ++;
            }
            else
            {
                size_intergenic ++;
            }
        }
        
    }
    ouf << "region\tsum\n";
    ouf << "intergenic\t" << size_intergenic << "\n";
    ouf << "upstream\t" << size_upstream << "\n";
    ouf << "five-UTR\t" << size_utr5 << "\n";
    ouf << "exon\t" << size_cds << "\n";
    ouf << "intron\t" << size_intron << "\n";
    ouf << "three-UTR\t" << size_utr3 << "\n";
    ouf << "downstream\t" << size_downstream << "\n";
    infGff.close();
    infPi.close();
    ouf.close();
    return 0;
}
int vcf2ancestral(parameter *para){
    string inFile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((inFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    cout << "Reading vcf file..." << endl;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '#') {
            if (line.substr(0,2) == "#C"){
                cout << "header.."  << endl;
                ll.clear();
                split(line,ll," \t");
                for (int i = 0; i < ll.size() - 2; ++i){
                    ouf << ll[i] << "\t";
                }
                ouf << ll[ll.size() - 2] << "\n";
            }else{
                ouf << line << "\n";
            }
        }else {
            ll.clear();
            split(line,ll,"\t");
            if (ll[ll.size()-1][0] == '0'){
                ouf << ll[0];
                for ( int i = 1; i < ll.size() -1; ++i){
                    ouf << "\t" << ll[i];
                }
                ouf << "\n";
            } else {
                for ( int i = 0; i < ll.size()-1; i++){
                    if (i == 0){
                        ouf << ll[i];
                    }else if ( i < 9){
                        ouf << "\t" << ll[i];
                    } else {
                        if(ll[i] == "0|0"){
                            ouf << "\t" << "1|1";
                        }else if (ll[i] == "1|1"){
                            ouf << "\t" << "0|0";
                        }else{
                            ouf << "\t" << ll[i];
                        }
                    }
                }
                ouf << "\n";
            }
        }
    }
    ouf.close();
    return 0;
}
int snpID(parameter *para){
    string inFile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((inFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        split(line,ll," ");
        string ID = ll[0]+"_"+ll[2];
        replaceAll(line,".",ID);
        ouf << line << "\n";
    }
    ouf.close();
    return 0;
}
int het2depth(parameter *para){
    string inFile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((inFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        if (line[0] == '#') continue;
        split(line,ll,"\t");
        ouf << ll[0] << "\t" << ll[1] << "\t";
        string g = ll[ll.size()-1];
        ll.clear();
        split(g,ll,":");
        string d = ll[1];
        ll.clear();
        split(d,ll,",");
        if (string2Int(ll[0]) > string2Int(ll[1])){
            ouf << ll[0] << "\t" << ll[1] << "\n";
        }else {
            ouf << ll[1] << "\t" << ll[0] << "\n";
        }
    }
    ouf.close();
    return 0;
}
int DPvsGATK(parameter *para){
    string inFile = (para -> inFile);
    string inFile2 = (para -> inFile2);
    string outFile = (para -> outFile);
    igzstream inf ((inFile).c_str(),ifstream::in);
    igzstream inf2 ((inFile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    set<string> pos;
    while (!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        if (line[0] == '#' ) continue;
        split(line,ll,"\t");
        pos.insert(ll[0]+"_"+ll[1]);
    }
    while (!inf2.eof()){
        getline(inf2,line);
        if (line.length() < 1) continue;
        if (line[0] == '#' ) {
            ouf << line << "\n";
            continue;
        };
        split(line,ll,"\t");
        if(pos.count(ll[0] +"_" + ll[1]) == 0){
            ouf << line << "\n";
        }
    }
    ouf.close();
    return 0;
}
int gene_count(parameter *para){
    string gffFile = (para -> inFile);
    string piFile = (para -> inFile2);
    string outFile = (para -> outFile);
    string chr = (para -> chr);
    double threshold = (para -> threshold);
    igzstream infGff ((gffFile).c_str(),ifstream::in);
    igzstream infPi ((piFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    set<int> withoutIntron;
    int start = 0, end = 0;
    int ps = 0, pe = 0;
    string strand = "";
    vector<int> startP(20000);
    vector<int> endP(20000);
    vector<int> strandP(20000);
    
    vector<int> genefeaturs(500000000);
    int gene_order = 0;
    // upstream50: 1; upstream20: 2;upstream10: 3; upstream5: 4;upstream2: 5;
    // gene: 20, 5utr: 7; cds: 8; intron: 9; 3utr: 10;
    // down50: 11; down20: 12; down10: 13; down5: 14; down2: 15;
    while(!infGff.eof()){
        getline(infGff,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[2] =='#'&& withoutIntron.size() > 0) {
            for ( int i = start; i < end; ++i){
                if(withoutIntron.count(i) == 0){
                    genefeaturs[i] = 9;
//                    intron.insert(i);
                }
            }
            start = 0;
            end = 0;
            withoutIntron.clear();
            ps = 0;
            pe = 0;
            continue;
        };
        if(line[0]=='#') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0] != chr) continue;
        if(ll[2] == "gene"){
            start = string2Int(ll[3]);
            end = string2Int(ll[4]);
            strand = ll[6];
            startP[gene_order] = start;
            endP[gene_order] = end;
            if(strand == "+"){
                strandP[gene_order] = 0;
            }else{
                strandP[gene_order] = 1;
            }
            gene_order++;
        }else if (ll[2] == "five_prime_UTR"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                genefeaturs[i]= 7;
                withoutIntron.insert(i);
            }
        }else if (ll[2] == "three_prime_UTR"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                 genefeaturs[i] = 10;
                withoutIntron.insert(i);
            }
        }else if (ll[2] == "CDS"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                 genefeaturs[i] = 8;
                withoutIntron.insert(i);
            }
        }
    }
    
    if(withoutIntron.size() > 1) {
        for ( int i = start; i < end; ++i){
            if(withoutIntron.count(i)==0){
                genefeaturs[i] = 9;
            }
        }
        withoutIntron.clear();
    }
    
    cout << "gff3 readed!" << endl;
    cout << "gene number is:\t" << gene_order << endl;
//    cout << "UTR number is:\t" << gene_order << endl;
    double size_upstream = 0, size_utr5 = 0, size_cds = 0, size_intron = 0;
    double size_utr3 = 0, size_downstream = 0,size_intergenic = 0;
    double size_up5 = 0, size_up10 = 0, size_up15 = 0, size_up20 = 0, size_up50 = 0;
    double size_down5 = 0, size_down10 = 0, size_down15 = 0, size_down20 = 0, size_down50 = 0;
    int current_order = 0;
    while(!infPi.eof()){
        getline(infPi,line);
        if(line.length()<1) continue;
        if(line[0] == 'C') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0] != chr) continue;
        int pos = string2Int(ll[1]);
//        if (ll.size()<4){
            pos = string2Int(ll[1]);
//        }else{
//            pos = string2Int(ll[2]);
//        }
        int size = ll.size()-1;
        if(size > 1){
            if (ll[size] == "-nan" || ll[size] == "nan" || ll[size] == "na" || ll[size] == "NA"|| ll[size] == "Inf"|| ll[size] == "-Inf") continue;
            double pi = string2Doublepos(ll[size]);
            if( pi > threshold){
                switch(genefeaturs[pos]){
                    case 0:
                        while ((startP[current_order] - pos) < 0){
                            if (current_order > gene_order - 1){
                                size_intergenic++;
                                genefeaturs[pos]= 20;
                                break;
                            }
                            current_order++;
                            if (current_order % 100 == 0 ){
                                cout << "currrent_order is:\t" << current_order << endl;
                            }
                        }
                        if((startP[current_order] - pos) < 2000){
                            if(strandP[current_order] == 0){
                                size_upstream += pi;
                            }else{
                                size_downstream += pi;
                            }
                            genefeaturs[pos]= 20;

                        }else if ((startP[current_order]- pos) < 5000){
                            if(strandP[current_order] == 0){
                                size_up5 += pi;
                            }else{
                                size_down5 += pi;
                            }
                            genefeaturs[pos]= 20;

                        }else if ((startP[current_order]- pos) < 10000){
                            if(strandP[current_order] == 0){
                                size_up10+= pi;
                            }else{
                                size_down10+= pi;
                            }
                            genefeaturs[pos]= 20;

                        }else if ((startP[current_order] - pos) < 20000){
                            if(strandP[current_order]== 0){
                                size_up20 += pi;
                            }else{
                                size_down20 += pi;
                            }
                            genefeaturs[pos]= 20;

                        }else if ((startP[current_order] - pos) < 50000){
                            if(strandP[current_order] == 0){
                                size_up50 += pi;
                            }else{
                                size_down50 += pi;
                            }
                            genefeaturs[pos]= 20;

                        }
                        
                        if( genefeaturs[pos]!=0) break;
                        
                        if((endP[current_order] - pos) < 2000){
                            if(strandP[current_order] == 1){
                                size_upstream += pi;
                            }else{
                                size_downstream += pi;
                            }
                            genefeaturs[pos]= 20;

                        }else if ((endP[current_order]- pos) < 5000){
                            if(strandP[current_order] == 1){
                                size_up5 += pi;
                            }else{
                                size_down5 += pi;
                            }
                            genefeaturs[pos]= 20;

                        }else if ((endP[current_order]- pos) < 10000){
                            if(strandP[current_order] == 1){
                                size_up10+= pi;
                            }else{
                                size_down10+= pi;
                            }
                            genefeaturs[pos]= 20;

                        }else if ((endP[current_order] - pos) < 20000){
                            if(strandP[current_order]== 1){
                                size_up20 += pi;
                            }else{
                                size_down20 += pi;
                            }
                            genefeaturs[pos]= 20;

                        }else if ((endP[current_order] - pos) < 50000){
                            if(strandP[current_order] == 1){
                                size_up50 += pi;
                            }else{
                                size_down50 += pi;
                            }
                            genefeaturs[pos]= 20;

                        }else{
                                size_intergenic+= pi;
                                genefeaturs[pos]= 20;
                        }
                        break;
                    case 7:
                        size_utr5 +=pi ;
                        break;
                    case 8:
                        size_cds +=pi ;
                        break;
                    case 9:
                        size_intron +=pi ;
                        break;
                    case 10:
                        size_utr3 +=pi ;
                        break;
                    default:
                        break;
                }
            }
        }else{
            switch(genefeaturs[pos]){
                case 0:
                    while ((startP[current_order]- pos) < 0){
                        if (current_order % 100 == 0 ){
                            cout << "currrent_order is:\t" << current_order << endl;
                        }
                        if (current_order > gene_order - 1){
                            size_intergenic++;
                            genefeaturs[pos]= 20;
                            break;
                        }
                        current_order++;
                    }
                    if((startP[current_order] - pos) < 2000){
                        if(strandP[current_order] == 0){
                            size_upstream++;
                        }else{
                            size_downstream++;
                        }
                        genefeaturs[pos]= 20;
                    }else if ((startP[current_order]- pos) < 5000){
                        if(strandP[current_order]== 0){
                            size_up5++;
                        }else{
                            size_down5++;
                        }
                        genefeaturs[pos]= 20;
                    }else if ((startP[current_order] - pos) < 10000){
                        if(strandP[current_order] == 0){
                            size_up10++;
                        }else{
                            size_down10++;
                        }
                        genefeaturs[pos]= 20;

                    }else if ((startP[current_order] - pos) < 20000){
                        if(strandP[current_order] == 0){
                            size_up20++;
                        }else{
                            size_down20++;
                        }
                        genefeaturs[pos]= 20;

                    }else if ((startP[current_order] - pos) < 50000){
                        if(strandP[current_order] == 0){
                            size_up50++;
                        }else{
                            size_down50++;
                        }
                        genefeaturs[pos]= 20;
                    }else{
                        
                    }
                    if( genefeaturs[pos] != 0) break;
                    if((endP[current_order] - pos) < 2000){
                        if(strandP[current_order] == 1){
                            size_upstream ++;
                        }else{
                            size_downstream ++;
                        }
                        genefeaturs[pos]= 20;
                        
                    }else if ((endP[current_order]- pos) < 5000){
                        if(strandP[current_order] == 1){
                            size_up5 ++;
                        }else{
                            size_down5 ++;
                        }
                        genefeaturs[pos]= 20;
                        
                    }else if ((endP[current_order]- pos) < 10000){
                        if(strandP[current_order] == 1){
                            size_up10 ++;
                        }else{
                            size_down10 ++;
                        }
                        genefeaturs[pos]= 20;
                        
                    }else if ((endP[current_order] - pos) < 20000){
                        if(strandP[current_order]== 1){
                            size_up20 ++;
                        }else{
                            size_down20 ++;
                        }
                        genefeaturs[pos]= 20;
                        
                    }else if ((endP[current_order] - pos) < 50000){
                        if(strandP[current_order] == 1){
                            size_up50 ++;
                        }else{
                            size_down50 ++;
                        }
                        genefeaturs[pos]= 20;
                        
                    }else{
                        size_intergenic++;
                        genefeaturs[pos]= 20;
                    }
                    break;
                case 7:
                    size_utr5 ++ ;
                    break;
                case 8:
                    size_cds ++ ;
                    break;
                case 9:
                    size_intron ++ ;
                    break;
                case 10:
                    size_utr3 ++ ;
                    break;
                default:
                    break;
            }
        }
    }
    ouf << "region\tsum\n";
    ouf << "intergenic\t" << size_intergenic << "\n";
    ouf << "upstream_20k_50k\t" << size_up50 << "\n";
    ouf << "upstream_10k_20k\t" << size_up20 << "\n";
    ouf << "upstream_5k_10k\t" << size_up10<< "\n";
    ouf << "upstream_2k_5k\t" << size_up5 << "\n";
    
    ouf << "upstream_2k\t" << size_upstream << "\n";
    ouf << "five-UTR\t" << size_utr5 << "\n";
    ouf << "exon\t" << size_cds << "\n";
    ouf << "intron\t" << size_intron << "\n";
    ouf << "three-UTR\t" << size_utr3 << "\n";
    ouf << "downstream_2k\t" << size_downstream << "\n";
    ouf << "downstream_2k_5k\t" << size_down5 << "\n";
    ouf << "downstream_5k_10k\t" << size_down10 << "\n";
    ouf << "downstream_10k_20k\t" << size_down20 << "\n";
    ouf << "downstream_20k_50k\t" << size_down50 << "\n";
  
    infGff.close();
    infPi.close();
    ouf.close();
    return 0;
}
int gene_count_gene(parameter *para){
    string gffFile = (para -> inFile);
    string piFile = (para -> inFile2);
    string outFile = (para -> outFile);
    string outFile1 = outFile + ".genes";
    string chr = (para -> chr);
    double threshold = (para -> threshold);
    igzstream infGff ((gffFile).c_str(),ifstream::in);
    igzstream infPi ((piFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    ofstream ouf1 ((outFile1).c_str());
    string line;
    vector<string> ll;
    set<int> withoutIntron;
    int start = 0, end = 0;
    int ps = 0, pe = 0;
    string strand = "";
    vector<int> startP(20000);
    vector<int> endP(20000);
    vector<int> strandP(20000);
    vector<int> genefeaturs(500000000);
    int gene_order = 0;
    // upstream50: 1; upstream20: 2;upstream10: 3; upstream5: 4;upstream2: 5;
    // gene: 20, 5utr: 7; cds: 8; intron: 9; 3utr: 10;
    // down50: 11; down20: 12; down10: 13; down5: 14; down2: 15;
    while(!infGff.eof()){
        getline(infGff,line);
        if(line.length()<1) continue;
        if(line[0]=='#' &line[2] =='#'){
            
            if(withoutIntron.size() > 0) {
            
                for ( int i = start; i < end; ++i){
                    if(withoutIntron.count(i) == 0){
                        genefeaturs[i] = 9;
                    //                    intron.insert(i);
                    }
                }
            }
            start = 0;
            end = 0;
            withoutIntron.clear();
            ps = 0;
            pe = 0;
            continue;
        };
        if(line[0]=='#') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0] != chr) continue;
        if(ll[2] == "gene"){
            start = string2Int(ll[3]);
            end = string2Int(ll[4]);
            strand = ll[6];
            startP[gene_order] = start;
            endP[gene_order] = end;
            if(strand == "+"){
                strandP[gene_order] = 0;
            }else{
                strandP[gene_order] = 1;
            }
            gene_order++;
        }else if (ll[2] == "five_prime_UTR"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                genefeaturs[i]= 7;
                withoutIntron.insert(i);
            }
        }else if (ll[2] == "three_prime_UTR"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                genefeaturs[i] = 10;
                withoutIntron.insert(i);
            }
        }else if (ll[2] == "CDS"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                genefeaturs[i] = 8;
                withoutIntron.insert(i);
            }
        }
    }
    if(withoutIntron.size() > 1) {
        for ( int i = start; i < end; ++i){
            if(withoutIntron.count(i)==0){
                genefeaturs[i] = 9;
            }
        }
        withoutIntron.clear();
    }
    
    cout << "gff3 readed!" << endl;
    cout << "gene number is:\t" << gene_order << endl;
    double** geneMatrix = dmatrix(-1, gene_order + 1, -1, 16);
    
    //    cout << "UTR number is:\t" << gene_order << endl;
    double size_upstream = 0, size_utr5 = 0, size_cds = 0, size_intron = 0;
    double size_utr3 = 0, size_downstream = 0,size_intergenic = 0;
    double size_up5 = 0, size_up10 = 0, size_up15 = 0, size_up20 = 0, size_up50 = 0;
    double size_down5 = 0, size_down10 = 0, size_down15 = 0, size_down20 = 0, size_down50 = 0;
    int current_order = 0;
    while(!infPi.eof()){
        getline(infPi,line);
        if(line.length()<1) continue;
        if(line[0] == 'C') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0] != chr) continue;
        int pos = string2Int(ll[1]);
        //        if (ll.size()<4){
        pos = string2Int(ll[1]);
        //        }else{
        //            pos = string2Int(ll[2]);
        //        }
        int size = ll.size()-1;
      
        if(size > 1){
            if (ll[size] == "-nan" || ll[size] == "nan" || ll[size] == "na" || ll[size] == "NA"|| ll[size] == "Inf"|| ll[size] == "-Inf") continue;
            double pi = string2Doublepos(ll[size]);
            if( pi > threshold){
                bool next = true;
                switch(genefeaturs[pos]){
                    case 0:
                        while(next){
                            if((pos - startP[current_order])<0){
                                // put into corrent position
                                if((startP[current_order] - pos) < 2000){
                                    if(strandP[current_order] == 0){
                                        size_upstream += pi;
                                        geneMatrix[current_order][5]+=pi;
                                    }else{
                                        size_downstream += pi;
                                        geneMatrix[current_order][10] += pi;
                                    }
                                    genefeaturs[pos]= 20;
                                }else if ((startP[current_order]- pos) < 5000){
                                    if(strandP[current_order]== 0){
                                        size_up5 += pi;
                                        geneMatrix[current_order][4]+=pi;
                                    }else{
                                        size_down5 += pi;
                                        geneMatrix[current_order][11]+=pi;
                                    }
                                    genefeaturs[pos]= 20;
                                }else if ((startP[current_order] - pos) < 10000){
                                    if(strandP[current_order] == 0){
                                        size_up10 += pi;
                                        geneMatrix[current_order][3]+=pi;
                                    }else{
                                        size_down10 += pi;
                                        geneMatrix[current_order][12]+=pi;
                                    }
                                    genefeaturs[pos]= 20;
                                    
                                }else if ((startP[current_order] - pos) < 20000){
                                    if(strandP[current_order] == 0){
                                        size_up20+=pi;
                                        geneMatrix[current_order][2]+=pi;
                                    }else{
                                        size_down20+=pi;
                                        geneMatrix[current_order][13]+=pi;
                                    }
                                    genefeaturs[pos]= 20;
                                    
                                }else if ((startP[current_order] - pos) < 50000){
                                    if(strandP[current_order] == 0){
                                        size_up50 += pi;
                                        geneMatrix[current_order][1]+=pi;
                                    }else{
                                        size_down50 += pi;
                                        geneMatrix[current_order][14]+=pi;
                                    }
                                    genefeaturs[pos]= 20;
                                }else{
                                    size_intergenic += pi;
                                    geneMatrix[current_order][0]+=pi;
                                    genefeaturs[pos]= 20;
                                }
                                next = false;
                            }else{
                                if (current_order > gene_order - 1){
                                    size_intergenic+=pi;
                                    geneMatrix[current_order][0]+=pi;
                                    genefeaturs[pos]= 20;
                                    next = false;
                                }else if ((pos - startP[current_order+1] ) < 0){
                                    // put into corrent position
                                    if((pos - endP[current_order] ) < 2000){
                                        if(strandP[current_order] == 1){
                                            size_upstream +=pi;
                                            geneMatrix[current_order][5]+=pi;
                                        }else{
                                            size_downstream +=pi;
                                            geneMatrix[current_order][10]+=pi;
                                        }
                                        genefeaturs[pos]= 20;
                                        
                                    }else if ((pos - endP[current_order]) < 5000){
                                        if(strandP[current_order] == 1){
                                            size_up5 +=pi;
                                            geneMatrix[current_order][4]+=pi;
                                        }else{
                                            size_down5 +=pi;
                                            geneMatrix[current_order][11]+=pi;
                                        }
                                        genefeaturs[pos]= 20;
                                        
                                    }else if ((pos - endP[current_order]) < 10000){
                                        if(strandP[current_order] == 1){
                                            size_up10 +=pi;
                                            geneMatrix[current_order][3]+=pi;
                                        }else{
                                            size_down10 +=pi;
                                            geneMatrix[current_order][12]+=pi;
                                        }
                                        genefeaturs[pos]= 20;
                                        
                                    }else if ((pos - endP[current_order] ) < 20000){
                                        if(strandP[current_order]== 1){
                                            size_up20 +=pi;
                                            geneMatrix[current_order][2]+=pi;
                                        }else{
                                            size_down20 +=pi;
                                            geneMatrix[current_order][13]+=pi;
                                        }
                                        genefeaturs[pos]= 20;
                                        
                                    }else if ((pos - endP[current_order] ) < 50000){
                                        if(strandP[current_order] == 1){
                                            size_up50 +=pi;
                                            geneMatrix[current_order][1]+=pi;
                                        }else{
                                            size_down50 +=pi;
                                            geneMatrix[current_order][14]+=pi;
                                        }
                                        genefeaturs[pos]= 20;
                                        
                                    }else{
                                        size_intergenic+=pi;
                                        geneMatrix[current_order][0]+=pi;
                                        genefeaturs[pos]= 20;
                                    }
                                    next = false;
                                }else {
                                    current_order++;
                                    next = true;
                                }
                            }
                        }
                        break;
                    case 7:
                        size_utr5 +=pi ;
                        while(pos > endP[current_order]){
                            current_order++;
                        }
                        geneMatrix[current_order][6] +=pi;
                        break;
                    case 8:
                        size_cds +=pi ;
                        while(pos > endP[current_order]){
                            current_order++;
                        }
                        geneMatrix[current_order][7] +=pi;
                        if(current_order==262){
                            cout << line<< endl;
                        }
                        break;
                    case 9:
                        size_intron +=pi ;
                        while(pos > endP[current_order]){
                            current_order++;
                        }
                        geneMatrix[current_order][8] +=pi;
                        break;
                    case 10:
                        size_utr3 +=pi ;
                        while(pos > endP[current_order]){
                            current_order++;
                        }
                        geneMatrix[current_order][9] +=pi;
                        break;
                    default:
                        break;
                }
            }
        }else{
            bool next = true;
            switch(genefeaturs[pos]){
                case 0:
                    // new methods
                    while(next){
                        if((pos - startP[current_order])<0){
                            // put into corrent position
                            if((startP[current_order] - pos) < 2000){
                                if(strandP[current_order] == 0){
                                    size_upstream++;
                                    geneMatrix[current_order][5]++;
                                }else{
                                    size_downstream++;
                                    geneMatrix[current_order][10]++;
                                }
                                genefeaturs[pos]= 20;
                            }else if ((startP[current_order]- pos) < 5000){
                                if(strandP[current_order]== 0){
                                    size_up5++;
                                    geneMatrix[current_order][4]++;
                                }else{
                                    size_down5++;
                                    geneMatrix[current_order][11]++;
                                }
                                genefeaturs[pos]= 20;
                            }else if ((startP[current_order] - pos) < 10000){
                                if(strandP[current_order] == 0){
                                    size_up10++;
                                    geneMatrix[current_order][3]++;
                                }else{
                                    size_down10++;
                                    geneMatrix[current_order][12]++;
                                }
                                genefeaturs[pos]= 20;
                                
                            }else if ((startP[current_order] - pos) < 20000){
                                if(strandP[current_order] == 0){
                                    size_up20++;
                                    geneMatrix[current_order][2]++;
                                }else{
                                    size_down20++;
                                    geneMatrix[current_order][13]++;
                                }
                                genefeaturs[pos]= 20;
                                
                            }else if ((startP[current_order] - pos) < 50000){
                                if(strandP[current_order] == 0){
                                    size_up50++;
                                    geneMatrix[current_order][1]++;
                                }else{
                                    size_down50++;
                                    geneMatrix[current_order][14]++;
                                }
                                genefeaturs[pos]= 20;
                            }else{
                                size_intergenic++;
                                geneMatrix[current_order][0]++;
                                genefeaturs[pos]= 20;
                            }
                            next = false;
                        }else{
                            if (current_order > gene_order - 1){
                                size_intergenic++;
                                geneMatrix[current_order][0]++;
                                genefeaturs[pos]= 20;
                                next = false;
                            }else
                            if ((pos - startP[current_order+1] ) < 0){
                                if((pos - endP[current_order] ) < 2000){
                                    if(strandP[current_order] == 1){
                                        size_upstream ++;
                                        geneMatrix[current_order][5]++;
                                    }else{
                                        size_downstream ++;
                                        geneMatrix[current_order][10]++;
                                    }
                                    genefeaturs[pos]= 20;
                                    
                                }else if ((pos - endP[current_order]) < 5000){
                                    if(strandP[current_order] == 1){
                                        size_up5 ++;
                                        geneMatrix[current_order][4]++;
                                    }else{
                                        size_down5 ++;
                                        geneMatrix[current_order][11]++;
                                    }
                                    genefeaturs[pos]= 20;
                                    
                                }else if ((pos - endP[current_order]) < 10000){
                                    if(strandP[current_order] == 1){
                                        size_up10 ++;
                                        geneMatrix[current_order][3]++;
                                    }else{
                                        size_down10 ++;
                                        geneMatrix[current_order][12]++;
                                    }
                                    genefeaturs[pos]= 20;
                                    
                                }else if ((pos - endP[current_order]) < 20000){
                                    if(strandP[current_order]== 1){
                                        size_up20 ++;
                                        geneMatrix[current_order][2]++;
                                    }else{
                                        size_down20 ++;
                                        geneMatrix[current_order][13]++;
                                    }
                                    genefeaturs[pos]= 20;
                                    
                                }else if ((pos - endP[current_order]) < 50000){
                                    if(strandP[current_order] == 1){
                                        size_up50 ++;
                                        geneMatrix[current_order][1]++;
                                    }else{
                                        size_down50 ++;
                                        geneMatrix[current_order][14]++;
                                    }
                                    genefeaturs[pos]= 20;
                                }else{
                                    size_intergenic++;
                                    geneMatrix[current_order][0]++;
                                    genefeaturs[pos]= 20;
                                }
                                next = false;
                            } else {
                                current_order++;
                                next = true;
                            }
                        }
                    }
                    break;
                case 7:
                    size_utr5 ++ ;
                    while(pos > endP[current_order]){
                        current_order++;
                    }
                    geneMatrix[current_order][6]++;
                    break;
                case 8:
                    size_cds ++ ;
                    while(pos > endP[current_order]){
                        current_order++;
                    }
                    geneMatrix[current_order][7]++;
                    break;
                case 9:
                    size_intron ++ ;
                    while(pos > endP[current_order]){
                        current_order++;
                    }
                    geneMatrix[current_order][8]++;
                    break;
                case 10:
                    size_utr3 ++ ;
                    while(pos > endP[current_order]){
                        current_order++;
                    }
                    geneMatrix[current_order][9]++;
                    break;
                default:
                    break;
            }
        }
    }
    ouf << "region\tsum\n";
    ouf << "intergenic\t" << size_intergenic << "\n";
    ouf << "upstream_20k_50k\t" << size_up50 << "\n";
    ouf << "upstream_10k_20k\t" << size_up20 << "\n";
    ouf << "upstream_5k_10k\t" << size_up10<< "\n";
    ouf << "upstream_2k_5k\t" << size_up5 << "\n";
    
    ouf << "upstream_2k\t" << size_upstream << "\n";
    ouf << "five-UTR\t" << size_utr5 << "\n";
    ouf << "exon\t" << size_cds << "\n";
    ouf << "intron\t" << size_intron << "\n";
    ouf << "three-UTR\t" << size_utr3 << "\n";
    ouf << "downstream_2k\t" << size_downstream << "\n";
    ouf << "downstream_2k_5k\t" << size_down5 << "\n";
    ouf << "downstream_5k_10k\t" << size_down10 << "\n";
    ouf << "downstream_10k_20k\t" << size_down20 << "\n";
    ouf << "downstream_20k_50k\t" << size_down50 << "\n";
   
    for (int i = 0; i < gene_order; i++){
        for (int j = 0; j < 14; j++){
            ouf1 << geneMatrix[i][j] << "\t";
        }
        ouf1 << geneMatrix[i][14] << "\n";
    }
    infGff.close();
    infPi.close();
    ouf.close();
    ouf1.close();
    return 0;
}
int toXPCLR(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para->inFile2);
    string infile3 = (para->bedFile);
    string outfile = (para->outFile);
    string snp = outfile+".snp";
    string geno = outfile+".geno";
    igzstream invcf ((infile.c_str()),ifstream::in);
    ifstream ingroup ((infile2.c_str()),ifstream::in);
    ifstream inrec ((infile3.c_str()),ifstream::in);
    ofstream snpf (snp.c_str());
    ofstream genof (geno.c_str());
    set<string> samples;
    string line;
    vector<string> ll;
    string chr = (para->chr);
    while(!ingroup.eof()){
        getline(ingroup,line);
        if(line.length()<1) continue;
        samples.insert(line);
    }
    cout << "group readed! group size is:\t" << samples.size() << endl;
    double** value = dmatrix(-1,500000000,-1,1);
    double recvalue = 0;
    int previous = 0;
    while(!inrec.eof()){
        getline(inrec,line);
        if(line.length()<1) continue;
        if(line[0]=='c'|| line[0]=='C') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0]!=chr) continue;
        double bin = string2Double(ll[4])/1000000;
        if (bin == 0) bin = 0.001/1000000;
//        cout << "bin is:" << bin << endl;
        int begin = string2Int(ll[1]);
        int end = string2Int(ll[2]);
        for (int cp = begin; cp < end; ++cp ){
            value[cp][0] = recvalue + bin * (cp-previous);
//            if(value[cp][0]==value[cp-1][0]) value[cp][0] = value[cp][0] + 0.000001;
        }
        previous = end;
        recvalue += bin*1000000;
    }
//    cout << "value is: " << value[0][0] << "\t" << value[1400010][0] << endl;
    vector<int> samplePos ;
    while(!invcf.eof()){
        getline(invcf,line);
        if (line.length()<=0 )  {
            continue  ;
        }else if ( line[0] == '#' && line[1] == '#' )  {
            continue  ;
        }else if ( line[0] == '#' && line[1] != '#' ){
            ll.clear();
            split(line,ll,"\t");
            if  ( ll[0]  != "#CHROM"){
                continue  ;
            }else{
                for (int i = 9; i< ll.size();++i){
                    if(samples.count(ll[i])==1){
                        samplePos.push_back(i);
                    }
                }
            }
            break ;
        }else if ( line[0] != '#' && line[1] != '#' ){
            cerr<<"wrong Line : "<<line<<endl;
            cerr<<"VCF Header same thing wrong, can find sample info before site info"<<endl;
            cerr<<"VCF Header sample info Flag : [  #CHROM  ] "<<endl;
            return  0;
            break;
        }
    }
    cout << samplePos.size() << " sample detected!" << endl;
    
    while (!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        for (int i = 0; i < samplePos.size()-1;++i){
            if(ll[samplePos[i]][0]=='0'&&ll[samplePos[i]][2]=='0'){
                genof << "0 0 " ;
            }else if (ll[samplePos[i]][0]=='1'&&ll[samplePos[i]][2]=='1'){
                genof << "1 1 " ;
            }else if(ll[samplePos[i]][0]=='0'&&ll[samplePos[i]][2]=='1'){
                genof << "0 1 " ;
            }else{
                genof << "9 9 " ;
            }
        }
        if(ll[samplePos[samplePos.size()-1]][0]=='0'&&ll[samplePos[samplePos.size()-1]][2]=='0'){
            genof << "0 0\n" ;
        }else if (ll[samplePos[samplePos.size()-1]][0]=='1'&&ll[samplePos[samplePos.size()-1]][2]=='1'){
            genof << "1 1\n" ;
        }else if(ll[samplePos[samplePos.size()-1]][0]=='0'&&ll[samplePos[samplePos.size()-1]][2]=='1'){
            genof << "0 1\n" ;
        }else{
            genof << "9 9\n" ;
        }
        snpf << " rs" << ll[0]<<"_" << ll[1] << "\t" << ll[0]<< "\t" << value[string2Int(ll[1])][0] << "\t" << ll[1] << "\t" << ll[3] << "\t" << ll[4] << "\n";
    }
    invcf.close();
    ingroup.close();
    inrec.close();
    snpf.close();
    genof.close();
    return 1;
}
int toEigenStrat(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para->inFile2);
    string outfile = (para->outFile);
    string snp = outfile+".snp";
    string geno = outfile+".geno";
    string ind = outfile + ".ind";
    
    igzstream invcf ((infile.c_str()),ifstream::in);
    igzstream ingroup ((infile2.c_str()),ifstream::in);
    ofstream snpf (snp.c_str());
    ofstream genof (geno.c_str());
    ofstream indf (ind.c_str());
    string line;
    vector<string> ll;
    map<string,string> group;
    while(!ingroup.eof()){
        getline(ingroup,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll,"\t");
        group.insert(pair<string,string>(ll[0],ll[1]));
    }
    cout << group.size() << " samples added!" << endl;
    set<int> skipSamle;
    while(!invcf.eof()){
        getline(invcf,line);
        if (line.length()<=0 )  {
            continue  ;
        }else if ( line[0] == '#' && line[1] == '#' )  {
            continue  ;
        }else if ( line[0] == '#' && line[1] != '#' ){
            ll.clear();
            split(line,ll,"\t");
            if  ( ll[0]  != "#CHROM"){
                continue  ;
            }else{
                for (int i = 9; i < ll.size();++i){
                    if(group.count(ll[i]) == 0){
                        skipSamle.insert(i);
                    }else{
                        indf << ll[i] << "\t" << "U\t" << group[ll[i]] << "\n";
                    }
                }
                if(skipSamle.size()>0){
                    cout <<  skipSamle.size() << " out of "<< ll.size()-9 << " sample not found!" << endl;
                }
            }
            break;
        }else if ( line[0] != '#' && line[1] != '#' ){
            cerr<<"wrong Line : "<<line<<endl;
            cerr<<"VCF Header same thing wrong, can find sample info before site info"<<endl;
            cerr<<"VCF Header sample info Flag : [  #CHROM  ] "<<endl;
            return  0;
            break;
        }
    }
    
    
    cout << "Reading VCF file..." << endl;
    while (!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        for (int i = 9; i < ll.size(); ++i){
            if(skipSamle.count(i)==1){
                continue;
            }
            if(ll[i][0] == '0' && ll[i][2] == '0'){
                genof << "0" ;
            }else if (ll[i][0]=='1'&&ll[i][2]=='1'){
                genof << "2" ;
            }else if(ll[i][0]=='0'&&ll[i][2]=='1'){
                genof << "1" ;
            }else{
                genof << "9" ;
            }
        }
        
        genof << "\n";
        
        snpf << " rs" << ll[0]<<"_" << ll[1] << "\t" << ll[0]<< "\t0.0\t" << ll[1] << "\t" << ll[3] << "\t" << ll[4] << "\n";
    }
    invcf.close();
    ingroup.close();
    snpf.close();
    genof.close();
    indf.close();
    return 1;
}
int toXPCLRsnp(parameter *para){
    string infile = (para->inFile);
    string infile3 = (para->bedFile);
    string outfile = (para->outFile);
    string snp = outfile+".snp";
    igzstream invcf ((infile.c_str()),ifstream::in);
    ifstream inrec ((infile3.c_str()),ifstream::in);
    ofstream snpf (snp.c_str());
    string line;
    vector<string> ll;
    string chr = (para->chr);
    double** value = dmatrix(-1,500000000,-1,1);
    double recvalue = 0;
    int previous = 0;
    while(!inrec.eof()){
        getline(inrec,line);
        if(line.length()<1) continue;
        if(line[0]=='c'|| line[0]=='C') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0]!=chr) continue;
        double bin = string2Double(ll[4])/1000000;
        if (bin == 0) bin = 0.001/1000000;
//        cout << "bin is:" << bin << endl;
        int begin = string2Int(ll[1]);
        int end = string2Int(ll[2]);
        for (int cp = begin; cp < end; ++cp ){
            value[cp][0] = recvalue + bin * (cp-previous);
            //            if(value[cp][0]==value[cp-1][0]) value[cp][0] = value[cp][0] + 0.000001;
        }
        previous = end;
        recvalue += bin*1000000;
    }
    cout << "recombination readed! Total genetic length is:\t" << recvalue << endl;
//    cout << "value is: " << value[0][0] << "\t" << value[1400010][0] << endl;
    vector<int> samplePos ;
    while(!invcf.eof()){
        getline(invcf,line);
        if (line.length()<=0 )  {
            continue  ;
        }else if ( line[0] == '#' && line[1] == '#' )  {
            continue  ;
        }else if ( line[0] == '#' && line[1] != '#' ){
            ll.clear();
            split(line,ll,"\t");
            if  ( ll[0]  != "#CHROM"){
                continue  ;
            }
            break ;
        }else if ( line[0] != '#' && line[1] != '#' ){
            cerr<<"wrong Line : "<<line<<endl;
            cerr<<"VCF Header same thing wrong, can find sample info before site info"<<endl;
            cerr<<"VCF Header sample info Flag : [  #CHROM  ] "<<endl;
            return  0;
            break;
        }
    }
    while (!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        snpf << " rs" << ll[0]<<"_" << ll[1] << "\t" << ll[0]<< "\t" << value[string2Int(ll[1])][0] << "\t" << ll[1] << "\t" << ll[3] << "\t" << ll[4] << "\n";
    }
    invcf.close();
    inrec.close();
    snpf.close();
    return 1;
}
int toV11(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    vector<string> lll;
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#'){
            ouf << line ;
        }else{
            ll.clear();
            split(line,ll," \t");
            for (int i = 0; i <7; ++i){
                ouf << ll[i] << "\t";
            }
            ouf << "." ;
            ouf << "\t" << "GT:AD:GL";
            for (int i = 9; i< ll.size(); ++i){
                lll.clear();
                split(ll[i],lll,":");
                ouf << "\t" << lll[0] << ":" << lll[1]<<":"<< lll[lll.size()-1];
            }
        }
        ouf << "\n";
    }
    invcf.close();
    ouf.close();
    return 0;
}
int toSFS(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    string c = "ACGT";
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#') continue;
        ll.clear();
        split(line,ll," \t");
        size_t ref = c.find(ll[3]);
        size_t alt = c.find(ll[4]);
        if (ref==std::string::npos||alt==std::string::npos){
            cerr << "vcf file error!" << endl;
            return 1;
        }
        vector<int> N4(4);
        vector<int> O4(4);
        vector<int> D4(4);
        int re = static_cast<int>(ref);
        int al = static_cast<int>(alt);
        for (int i = 9; i < ll.size()-2; ++i){
            if(ll[i][0] == '0' & ll[i][2] == '0'){
                N4[re] ++;
            }else if (ll[i][0]=='1' & ll[i][2] == '1'){
                N4[al] ++;
            }else{
                continue;
            }
        }
        int p = ll.size()-2;
        if(ll[p][0]=='0' && ll[p][2]=='0'){
            O4[re] ++;
        }else if(ll[p][1]=='1' && ll[p][1]=='1') {
            O4[al] ++;
        }
        p = ll.size()-1;
        if(ll[p][0]=='0' && ll[p][2]=='0'){
            D4[re] ++;
        }else if(ll[p][1]=='1' && ll[p][1]=='1') {
            D4[al] ++;
        }
        ouf << N4[0] << "," << N4[1] << ","<< N4[2] << ","<< N4[3] << "\t"<< O4[0] << ","<< O4[1] << ","<< O4[2]  << ","<< O4[3] << "\t"<< D4[0] << ","<< D4[1] << ","<< D4[2]  << ","<< D4[3]<< "\n";
    }
    invcf.close();
    ouf.close();
    return 0;
}

int getAlleleFrequency(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    set<string> names = getSubgroup(para->subPop);
//    vector<int> pos = getSubPos(names,allNames);
    return 0;
}

int LDmean(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    int bin = para->size;
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    double ** rsquare = dmatrix(-1,100001,-1,4);
    int maxBin = 1;
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        int l = string2Int(ll[0]);
        if(l==1){
            rsquare[0][0] += string2Double(ll[1]);
            rsquare[0][1] ++;
        }else{
            int l1 = (int)ceil(string2Double(ll[0])/bin);
            if(l1 >= maxBin) maxBin = l1+1;
            rsquare[l1][0] += string2Double(ll[1]);
            rsquare[l1][1] ++;
        }
    }
    ouf << "Distance(" << bin/1000 <<" kb)\tsum\tnumber\tmean\n";
    for (int i = 0; i < maxBin;++i){
        ouf << i <<"\t" << rsquare[i][0] << "\t"<< rsquare[i][1] << "\t"<< rsquare[i][0]/rsquare[i][1] << "\n";
    }
    invcf.close();
    ouf.close();
    //    vector<int> pos = getSubPos(names,allNames);
    return 0;
}

int pwFrequence(parameter *para){
    string infile = (para->inFile);
    string gf1 = (para -> inFile2 );
    string gf2 = (para -> inFile3);
    string outfile = (para->outFile);
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    set<string> name1 = getSubgroup(gf1);
    set<string> name2 = getSubgroup(gf2);
//    set<string> name = getSubgroup(gf1);
//    name.insert(name2.begin(), name2.end());
    vector<int> na1;
    vector<int> na2;
    vector<int> na;
    vector<string> ll;
    double** maf = dmatrix(-1,51,-1,3);
    double sum = 0;
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1] == '#') continue;
        ll.clear();
        split(line,ll," \t");
        if(line[0]=='#' && line[1] == 'C') {
            na1 = getPos(ll,name1);
            na2 = getPos(ll,name2);
//            na = getPos(ll,name);
            continue;
        }
        double mf1 = MAF(ll,na1);
        double mf2 = MAF(ll,na2);
        double mf = MAF(ll);
        if(mf1 > 0 && mf2 >0){
            maf[(int)ceil(mf/0.01)][0] ++;
            sum++;
        }else if (mf1 > 0 && mf2 ==0){
            maf[(int)ceil(mf/0.01)][1] ++;
            sum++;
        }else if (mf1 == 0 && mf2 > 0){
            maf[(int)ceil(mf/0.01)][2] ++;
            sum++;
        }else{
            continue;
        }
    }
    ouf << "maf\tshared\tgroup1\tgroup2\n";
    for(int i = 0; i < 51; ++i){
        ouf << 0.01*i << "\t" << maf[i][0] << "\t" << maf[i][1] <<"\t" << maf[i][2] << "\n";
    }
    invcf.close();
    ouf.close();
    return 0;
}
int GenerateDiploid(parameter *para){
    string infile = (para->inFile);
    string group = (para -> inFile2 );
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    set<string> name1 ;
    set<string> name2;
    vector<string> n1 ;
    vector<string> n2;
    getName(name1,name2,n1,n2,group);
    vector<int> na1;
    vector<int> na2;
    vector<int> na;
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1] == '#') {
            ouf << line << "\n";
            continue;
        };
        ll.clear();
        split(line,ll," \t");
        if(line[0]=='#' && line[1] == 'C') {
            getPos(ll,n1,n2,na1,na2);
            for (int i = 0 ; i < 8; ++i){
                ouf << ll[i] << "\t";
            }
            ouf << ll[8];
            for (int i = 0; i < na1.size();++i){
                ouf << "\t" << n1[i] << "_" << n2[i] ;
            }
            ouf << "\n";
            continue;
        }
        for (int i = 0; i< 8;++i){
            ouf << ll[i] << "\t";
        }
        ouf << "GT" ;
        for (int i = 0; i< na1.size();++i){
            int p = rand() % 2;
            if (p==1) p++;
            ouf <<"\t" << ll[na1[i]][p] << "|" << ll[na2[i]][p] ;
        }
        ouf << "\n";
    }
    
    ouf.close();
    return 0;
}
int GeneratepsmcDiploid(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para -> inFile2 );
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    igzstream inf2 ((infile2.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    map<string,string> table;
    table.insert(pair<string,string>("AC","M"));
    table.insert(pair<string,string>("AT","W"));
    table.insert(pair<string,string>("AG","R"));
    table.insert(pair<string,string>("CA","M"));
    table.insert(pair<string,string>("CG","S"));
    table.insert(pair<string,string>("CT","Y"));
    table.insert(pair<string,string>("GA","R"));
    table.insert(pair<string,string>("GC","S"));
    table.insert(pair<string,string>("GT","K"));
    table.insert(pair<string,string>("TA","W"));
    table.insert(pair<string,string>("TC","Y"));
    table.insert(pair<string,string>("TG","K"));
    table.insert(pair<string,string>("AN","n"));
    table.insert(pair<string,string>("TN","n"));
    table.insert(pair<string,string>("GN","n"));
    table.insert(pair<string,string>("CN","n"));
    table.insert(pair<string,string>("NA","n"));
    table.insert(pair<string,string>("NT","n"));
    table.insert(pair<string,string>("NG","n"));
    table.insert(pair<string,string>("NC","n"));
    table.insert(pair<string,string>("NN","n"));
    table.insert(pair<string,string>("M","AC"));
    table.insert(pair<string,string>("W","AT"));
    table.insert(pair<string,string>("R","AG"));
    table.insert(pair<string,string>("S","CG"));
    table.insert(pair<string,string>("Y","CT"));
    table.insert(pair<string,string>("K","GT"));
    string line;
    string chr;
    string seq1 = "", qs1 = "", seq2 = "", qs2 = "";
    map<string,string> genome1;
    map<string,string> genome2;
    map<string,string> gq1;
    map<string,string> gq2;
    bool start = true, seqfinished = false;
    vector<string> chrs;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '@' && line.length() < 10){
            chr = line.substr(1,line.length()-1);
            chrs.push_back(chr);
            if(!start) {
                genome1.insert(pair<string, string>(chr,seq1));
                gq1.insert(pair<string,string>(chr,qs1));
                seqfinished = false;
//                cout << "seq length is:\t" << seq1.length() << endl;
//                cout << "quality length is:\t" << qs1.length() << endl;
//                cout << qs1[0] << endl;
            }
            start = false;
            seq1 = "";
            qs1 = "";
        }else{
            if(line[0] == '+' && line.length() < 2){
                seqfinished = true;
                continue;
            }
            if(seqfinished){
                qs1.append(line);
            }else{
                seq1.append(line);
            }
        }
        
    }
    genome1.insert(pair<string, string>(chr,seq1));
    gq1.insert(pair<string,string>(chr,qs1));
    
    cout << genome1.size() << " chromosomes readed for genome1!" << endl;
    
    seq2 = "";
    start = true;
    seqfinished = false;
    
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        if(line[0] == '@' && line.length() < 10){
            chr = line.substr(1,line.length()-1);
            if(!start) {
                genome2.insert(pair<string, string>(chr,seq2));
                gq2.insert(pair<string,string>(chr,qs2));
                seqfinished = false;
            }
            start = false;
            seq2 = "";
            qs2 = "";
        }else{
            if(line[0] == '+' && line.length() < 10){
                seqfinished = true;
            }
            if(seqfinished){
                qs2.append(line);
            }else{
                seq2.append(line);
            }
        }
    }
    genome2.insert(pair<string, string>(chr,seq2));
    gq2.insert(pair<string,string>(chr,qs2));
    cout << genome2.size() << " chromosomes readed for genome2!" << endl;
    string seq ="";
    string sq = "";
    for (int i = 0; i < chrs.size(); i++){
        string c = chrs[i];
        if (string2Int(c) > 42) continue;
        if(genome1.count(c) == 0) continue;
        if(genome2.count(c) == 0) continue;
        string seq1 = genome1[c];
        string seq2 = genome2[c];
        string sq1 = gq1[c];
        string sq2 = gq2[c];
        int a = seq1.length();
        int b = seq2.length();
        int small = a;
        if (a > b) small = b;
        ouf << "@" << c << "\n";
        for (int i = 0; i < small; i++){
            string key ="";
            if(seq1[i] == 'n' || seq2[i] == 'n'){
                ouf << "n";
            }else if ((char)toupper(seq1[i]) == (char)toupper(seq2[i])){
                ouf << seq1[i];
            }else{
                key.push_back((char)toupper(seq1[i]));
                key.push_back((char)toupper(seq2[i]));
                string value = table[key];
                ouf << value;
            }
            if((i+1)%60==0){
                ouf << "\n";
            }
        }
        if (small%60 != 0) ouf << "\n";
        ouf << "+\n";
        for (int i = 0; i < small; i++){
            int av = (int)sq1[i];
            int bv = (int)sq2[i];
            int mv = (av + bv)/2;
            ouf << (char)mv;
            if((i+1)%60==0) ouf << "\n";
        }
        if (small%60 != 0) ouf << "\n";
        
    }
    ouf.close();
    return 0;
}
int concensusGenome(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para -> inFile2 );
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    igzstream inf2 ((infile2.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    string chr = (para->chr);
    bool run = false;
    string seq = "";
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '>'){
            string c = line.substr(1,line.length()-1);
            if(c == chr) {
                run = true;
            }else{
                run = false;
            }
        }else{
            if(run){
                seq.append(line);
            }
        }
    }
    cout << "chromosome readed!" << endl;
    set<int> pos;
    vector<string> ll;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        split(line,ll,"\t");
        pos.insert(string2Int(ll[1])-1);
    }
    ouf << ">" << chr << "\n";
    for(int i = 0; i< seq.length();i++){
        if(pos.count(i) == 0){
            ouf << "N";
        }else{
            ouf << seq[i];
        }
        if((i+1)%80 == 0) {
            ouf << "\n";
        }
    }
    if (seq.length()% 80 != 0){
        ouf << "\n";
    }
    cout << "chr" << chr << " length is: " << seq.length() << ", finished." << endl;
    ouf.close();
    
    return 0;
}
int frq2dxy(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para -> inFile2 );
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    igzstream inf2 ((infile2.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line,line2;
    vector<string> ll,ll2;
    double p1 = 0, p2 = 0;
    while(!inf.eof()){
        getline(inf,line);
        getline(inf2,line2);
        if(line.length() < 1) continue;
        if(line2.length() < 1) continue;
        if(line[0] == 'C') continue;
        split(line,ll,"\t");
        split(line2,ll2,"\t");
        if(ll[1] != ll2[1]) cerr << "Frequency files do not matcht, stoped!" << endl;
        ouf << ll[0] << "\t" << ll[1] << "\t";
        if (ll[3][0] == '0' | ll2[3][0] == '0') {
            ouf << 0 << "\n";
            continue;
        }
        string a1 = ll[4];
        string a2 = ll2[4];
        ll.clear();
        ll2.clear();
        split(a1,ll,":");
        split(a2,ll2,":");
        p1 = string2Double(ll[1]);
        p2 = string2Double(ll2[1]);
        double dxy = p1*(1-p2) + p2*(1-p1);
        ouf << dxy << "\n";
    }
    ouf.close();
    return 0;
}

int writeMAF(parameter *para){
    string infile = (para->inFile);
    string gf1 = (para -> inFile2 );
    string outfile = (para->outFile);
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    set<string> name1 = getSubgroup(gf1);
    //    set<string> name = getSubgroup(gf1);
    //    name.insert(name2.begin(), name2.end());
    vector<int> na1;
    vector<string> ll;
    ouf << "chr\tpos\tmaf\n";
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1] == '#') continue;
        ll.clear();
        split(line,ll," \t");
        if(line[0]=='#' && line[1] == 'C') {
            na1 = getPos(ll,name1);
            continue;
        }
        double mf1 = MAF(ll,na1);
        ouf << ll[0] << "\t" << ll[1] << "\t" << mf1 << "\n";
    }
    
    invcf.close();
    ouf.close();
    return 0;
}

int getDerivedAllele(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#') {
            ouf << line << "\n";
            continue;
        };
        ll.clear();
        split(line,ll," \t");
        int size = ll.size();
        if(ll[size-2][0] != '.' && ll[size-1][0] != '.'){
            if(ll[size-2][0]!=ll[size-1][0]){
                continue;
            }else{
//                if(ll[size-2][0] == '1'){
//                    string tmp = ll[3];
//                    ll[3] = ll[4];
//                    ll[4] = tmp;
//                }
                ouf << ll[0];
                for(int i = 1; i < size; ++i){
                    ouf << "\t" << ll[i];
                }
                ouf << "\n";
            }
        }else{
            continue;
        }
        
    }
    
    invcf.close();
    ouf.close();
    return 0;
}
int cp(parameter *para){
    string infile = (para->inFile);
    string gf1 = (para -> inFile2 );
    string gf2 = (para -> inFile3);
    string outfile = (para->outFile);
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    set<string> name1 = getSubgroup(gf1);
    set<string> name2 = getSubgroup(gf2);
    vector<int> na1;
    vector<int> na2;
    vector<int> na;
    vector<string> ll;
    vector<int> number(9);
    for (int i=0; i <9; ++i){
        number[i] = 0;
    }
    int all = 0, derived = 0;
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1] == '#') {
        };
        ll.clear();
        split(line,ll," \t");
        if(line[0]=='#' && line[1] == 'C') {
            na1 = getPos(ll,name1);
            na2 = getPos(ll,name2);
            if(na1.size() < 1) break;
            if(na2.size() < 1) break;
            continue;
        }
        
        if(na1.size() < 1) continue;
        if(na2.size() < 1) continue;
        
        all++;
        double mf1 = ref(ll,na1);
        double mf2 = ref(ll,na2);
        char ref = ll[ll.size()-1][0];
        if(ref == '1'){
            mf1 = 1 - mf1;
            mf2 = 1 - mf2;
        }
        if (mf1 == 0){
            if(mf2 == 0){
                number[0]++;
            }else if (mf2 == 1){
                number[2]++;
            }else{
                number[1]++;
            }
        }else if (mf1 == 1){
            if(mf2 == 0){
                number[6]++;
            }else if (mf2 == 1){
                number[8]++;
            }else{
                number[7]++;
            }
        }else{
            if(mf2 == 0){
                number[3]++;
            }else if (mf2 == 1){
                number[5]++;
            }else{
                number[4]++;
            }
        }
    }
    ouf << all << "\t" << number[0] ;
    for (int i = 1; i < 9; ++i){
        ouf << "\t" << number[i];
    }
    
    ouf << "\n";
    invcf.close();
    ouf.close();
    
    return 0;
}
double getSum(string & infile){
    double sum = 0;
    igzstream invcf ((infile.c_str()),ifstream::in);
    string line;
    vector<string> ll;
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length() < 1) continue;
        if(line[0] == 'C'||line[0]=='c') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[2]== "-nan" || ll[2]== "nan" || ll[2] == "inf" || ll[2] =="-inf" || ll[2] == "NA") continue;
        sum += string2Double(ll[2]);
    }
    invcf.close();
    return sum;
}

int DiversityReduction(parameter *para){
    string infile = (para->inFile);
    string gf1 = (para -> inFile2 );
    string gf2 = (para -> inFile3);
    string outfile = (para->outFile);
    igzstream invcf ((infile.c_str()),ifstream::in);
    igzstream g1 ((gf1.c_str()),ifstream::in);
    igzstream g2 ((gf2.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    vector<string> file1;
    vector<string> file2;
    vector<string> sub;
    split(gf1,sub,"/");
    string folder = "" ;
    vector<int> chrSize(42);
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length() < 1) continue;
        ll.clear();
        if(line[0]=='C') continue;
        split(line,ll," \t");
        chrSize[string2Int(ll[0])-1] = string2Int(ll[1]);
    }
    invcf.close();
    
    while(!g1.eof()){
        getline(g1,line);
        if(line.length() < 1) continue;
        if(line[0]=='C') continue;
        file1.push_back(line);
    }
    g1.close();
    
    while(!g2.eof()){
        getline(g2,line);
        if(line.length() < 1) continue;
        if(line[0]=='C') continue;
        file2.push_back(line);
    }
    g2.close();
    
    vector<double> gr1(file1.size());
    vector<double> gr2(file2.size());
    long int allC = 0;
    double all1 = 0, all2 = 0;
    for (int i = 0; i < gr1.size(); ++i){
        double tmp = getSum(file1[i]);
        gr1[i] = tmp;
        all1 += tmp;
        long int count = chrSize[getChr(file1[i])-1];
        gr1[i] = gr1[i]/count;
        allC += count;
//        cout << "allC is:\t" << allC << endl;
    }
    
    for (int i = 0; i < gr2.size(); ++i){
        double tmp = getSum(file2[i]);
        gr2[i] = tmp;
        all2 += tmp;
        long int count = chrSize[getChr(file1[i])-1];
        gr2[i] = gr2[i]/count;
//        cout << "all2 is: " << all2 << endl;
    }
    srand((int)time(NULL));
    for (int i = 0; i < 2000; ++i){
        int a = Random(0, gr1.size()-1);
        int b= Random(0, gr2.size()-1);
        if(gr2[b]>gr1[a]) {
            ouf << gr1[a] << "\t" << gr2[b] << "\t" <<  -gr1[a]/gr2[b] << "\n";
        }else{
            ouf << gr1[a] << "\t" << gr2[b] << "\t" << (1-gr2[b]/gr1[a]) << "\n";
        }
    }
//    cout << "all1 is: " << all1 << ";all2 is: " << all2 << endl;
    ouf << all1/allC << "\t" << all2/allC << "\t" << (1 - all2/all1) << "\n";
    ouf.close();
    return 1;
}
int getMean(parameter *para){
    string infile = (para->inFile);
    string gf1 = (para -> inFile2 );
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    igzstream countf ((gf1.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    vector<string> file1;
    vector<string> sub;
    split(gf1,sub,"/");
    string folder = "" ;
    vector<int> chrSize(42);
    int allCount = 0;
    while(!countf.eof()){
        getline(countf,line);
        if(line.length() < 1) continue;
        ll.clear();
        if(line[0]=='C') continue;
        split(line,ll," \t");
        chrSize[string2Int(ll[0])-1] = string2Int(ll[1]);
        allCount += string2Int(ll[1]);
    }
    countf.close();
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        ll.clear();
        if(line[0]=='C') continue;
        cout << "Now calculating file:\t" << line << endl;
        double value = getSum(line);
        ouf << line << "\n";
    }
    inf.close();
    ouf.close();
    return 1;
}
int getSum(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    double value = 0;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        ll.clear();
        if(line[0]=='C') continue;
        split(line,ll,"\t");
        if(isNA(ll[2])) continue;
        value += string2Double(ll[2]);
    }
    ouf << value << "\n";
    inf.close();
    ouf.close();
    return 1;
}
int wc(parameter *para){
    string infile = (para->inFile);
//    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
//    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    lint value = 0;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        value++;
    }
    cout << infile << "\t" << value << endl;
    inf.close();
//    ouf.close();
    return 1;
}
int getBedDensity(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    int windowSize = (para->size );
    igzstream inbed ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector <string> ll;
    map<string,int> chrSize;
    int sum = 0;
    int prePos = 0;
    string chr = "s";
    while(!inbed.eof()){
        getline(inbed,line);
        if(line.length()<0) continue;
        if(line[0] == '#' && line[1] == '#'){
            ll.clear();
            split(line,ll," \t");
            if(ll.size() < 4) continue;
            chrSize.insert(pair<string,int>(ll[1],string2Int(ll[3])));
            continue;
        };
        ll.clear();
        split(line,ll, " \t");
        if(chr != ll[0]){
            if(chr!="s"){
                ouf << chr << "\t" << prePos << "\t" << chrSize[chr] << "\t" << sum << "\n";
            }
            chr = ll[0];
            sum = 0;
            prePos = 0;
        }
        int cp = string2Int(ll[1]);
        if(cp < prePos) {
            cout << "current pos is:\t" << chr<<"\t"<< cp << endl;
            cerr << "please check start position!" << endl;
            return 1;
        }
        while (cp >= (prePos + windowSize)){
            ouf << chr << "\t" << prePos << "\t" << (prePos + windowSize - 1) << "\t" << sum << "\n";
            sum = 0;
            prePos += windowSize;
        }
        sum++;
    }
    ouf << chr << "\t" << prePos << "\t" << chrSize[chr] << "\t" << sum << "\n";
    inbed.close();
    ouf.close();
    return 0;
}
int getGffDensity(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    int windowSize = (para->size );
    igzstream inbed ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector <string> ll;
    map<string,int> chrSize;
    int sum = 0;
    int prePos = 1;
    string chr = "s";
    while(!inbed.eof()){
        getline(inbed,line);
        if(line.length()<0) continue;
        if(line[0] == '#' && line[1] == '#'){
            ll.clear();
            split(line,ll," \t");
            if(ll.size() < 4) continue;
            chrSize.insert(pair<string,int>(ll[1],string2Int(ll[3])));
            continue;
        };
        ll.clear();
        split(line,ll, " \t");
        if(ll[2] != "gene") continue;
        if(chr != ll[0]){
            if(chr!="s"){
                ouf << chr << "\t" << prePos << "\t" << chrSize[chr] << "\t" << sum << "\n";
            }
            chr = ll[0];
            sum = 0;
            prePos = 1;
        }
        int cp = string2Int(ll[3]);
        if(cp < prePos) {
            cerr << "please check start position!" << endl;
            return 1;
        }
        while (cp >= (prePos + windowSize)){
            ouf << chr << "\t" << prePos << "\t" << (prePos + windowSize - 1) << "\t" << sum << "\n";
            sum = 0;
            prePos += windowSize;
        }
        sum++;
    }
    ouf << chr << "\t" << prePos << "\t" << chrSize[chr] << "\t" << sum << "\n";
    inbed.close();
    ouf.close();
    return 0;
}
int SNPdensity(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    int windowSize = (para->size );
    igzstream inbed ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector <string> ll;
    
    return 0;
}
int TEdensity(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    int windowSize = (para->size );
    igzstream inbed ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector <string> ll;
    int sum = 0;
    int prePos = 1;
    string chr = "s";
    int maxPos = 2;
    int length = 0;
    int duo = 0;
    while(!inbed.eof()){
        getline(inbed,line);
        if(line.length()<0) continue;
        ll.clear();
        split(line,ll, " \t");
        maxPos = string2Int(ll[2]);
        if(chr != ll[0]){
            if(chr!="s"){
                ouf << chr << "\t" << prePos << "\t" << maxPos << "\t" << 1.0*sum/windowSize << "\n";
            }
            chr = ll[0];
            sum = 0;
            prePos = 1;
        }
        int cp = string2Int(ll[1]);
        if(cp < prePos) {
            cerr << "please check start position!" << endl;
            return 1;
        }
        while (cp >= (prePos + windowSize)){
            ouf << chr << "\t" << prePos << "\t" << (prePos + windowSize - 1) << "\t" << 1.0*sum/windowSize << "\n";
            sum = duo;
            prePos += windowSize;
        }
        if(maxPos >(prePos + windowSize)){
            sum += prePos + windowSize - string2Int(ll[1]) + 1;
            duo = maxPos -(prePos + windowSize);
        }else{
            sum += string2Int(ll[2]) - string2Int(ll[1]) + 1;
            duo = 0;
        }
        
    }
    ouf << chr << "\t" << prePos << "\t" << maxPos << "\t" << 1.0*sum/windowSize << "\n";
    inbed.close();
    ouf.close();
    return 0;
}
int cleanBed(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inbed ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector <string> ll;
    int pre = 0 ;
    int pos = 0;
    string chr = "";
    while(!inbed.eof()){
        getline(inbed,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll," \t");
        if(chr != ll[0]){
            pre = 0 ;
            pos = 0;
            chr = ll[0];
//            cout << ll[0] << endl;
        }
        int a = string2Int(ll[1]);
        int b = string2Int(ll[2]);
        if(b < pos) continue;
        if(a < pos){
            ll[1] = Int2String(pos+1);
            pre = pos+1;
            pos = b;
            for (int i = 0; i < ll.size()-1; ++i){
                ouf << ll[i] << "\t";
            }
            if(ll.size()<2) cout << line << endl;
            ouf << ll[ll.size()-1] << "\n";
            continue;
        }else{
            pre = a;
            pos = b;
            ouf << line << "\n";
        }
    }
    ouf.close();
    inbed.close();
    return 0;
}
int gff2bed(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inbed ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector <string> ll;
    set<int> pos;
    while(!inbed.eof()){
        getline(inbed,line);
        if(line.length()<1) continue;
        if(line[0] == '#') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[2] != "gene") continue;
        int pre = string2Int(ll[3]) -1;
        if(pos.count(pre)==1){
            continue;
        }else{
            pos.insert(pre);
        }
        ll[3] = Int2String(pre);
        ouf << ll[0] << "\t" << ll[3] << "\t" << ll[4] << "\n";
    }
    inbed.close();
    ouf.close();
    return 0;
}
int gff2exon(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    ofstream ouf (outfile.c_str());
    string line;
    vector <string> ll;
    string chr = (para->chr);
    cout << "reading gff3 file..." << endl;
    gff3 g3 = gff3(infile,chr);
    map<string,transcript> trans = g3.long_transcripts;
    map<string,transcript>::iterator it;
    it = trans.begin();
    cout << "genes number is:\t"<< trans.size() << endl;
    while(it != trans.end()){
        transcript tr = it->second;
        string ID = tr.ID;
        vector<CDS> CDSs = g3.CDSs[ID];
        int csize = CDSs.size();
        if(tr.chr != chr){
            it++;
            continue;
        }
        for (int j = 0; j < csize; j++){
            int cs = CDSs[j].start;
            int ce = CDSs[j].end;
            for(int i = cs; i < ce+1; ++i){
                ouf << chr << "\t" << i << "\n";
            }
        }
        it++;
    }
    return 0;
}
int gff2exon10Kb(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    ofstream ouf (outfile.c_str());
    string line;
    vector <string> ll;
    string chr = (para->chr);
    cout << "reading gff3 file..." << endl;
    gff3 g3 = gff3(infile,chr);
    map<string,transcript> trans = g3.long_transcripts;
    map<string,transcript>::iterator it;
    it = trans.begin();
    cout << "genes number is:\t"<< trans.size() << endl;
    vector<int> exon(500000000,0);
    while(it != trans.end()){
        transcript tr = it->second;
        string ID = tr.ID;
        vector<CDS> CDSs = g3.CDSs[ID];
        int csize = CDSs.size();
        if(tr.chr != chr){
            it++;
            continue;
        }
        for (int j = 0; j < csize; j++){
            int cs = CDSs[j].start-10000;
            if (cs<0) cs = 0;
            int ce = CDSs[j].end+10000;
            for(int i = cs; i < ce+1; ++i){
                exon[i] = 1;
            }
        }
        it++;
    }
    for(int i = 0; i < 500000000;++i){
        if(exon[i]==1){
            ouf << chr << "\t" << i << "\n";
        }
    }
    
    return 0;
}
int gff2exon10Kbexcluded(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    ofstream ouf (outfile.c_str());
    string line;
    vector <string> ll;
    string chr = (para->chr);
    cout << "reading gff3 file..." << endl;
    gff3 g3 = gff3(infile,chr);
    map<string,transcript> trans = g3.long_transcripts;
    map<string,transcript>::iterator it;
    it = trans.begin();
    cout << "genes number is:\t"<< trans.size() << endl;
    vector<int> exon(500000000,0);
    while(it != trans.end()){
        transcript tr = it->second;
        string ID = tr.ID;
        vector<CDS> CDSs = g3.CDSs[ID];
        int csize = CDSs.size();
        if(tr.chr != chr){
            it++;
            continue;
        }
        for (int j = 0; j < csize; j++){
            int cs = CDSs[j].start-10000;
            int ce = CDSs[j].end+10000;
            for(int i = cs; i < ce+1; ++i){
                exon[i] = 1;
            }
        }
        it++;
    }
    for(int i = 0; i < 500000000;++i){
        if(exon[i]==0){
            ouf << chr << "\t" << i << "\n";
        }
    }
    
    return 0;
}
int gff2genicsite(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    string chr = (para->chr);
    vector <string> ll;
    set<int> pos;
    cout << "read gff3 file..." << endl;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0] == '#') continue;
        ll.clear();
        split(line,ll,"\t");
        if(ll[0] != chr) continue;
        if(ll[2] != "gene") continue;
        for(int i = string2Int(ll[3]); i < string2Int(ll[4])+1; ++i){
            ouf << ll[0] << "\t" << i << "\n";
        }
    }
    inf.close();
    ouf.close();
    return 0;
}

int gff2thin(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inbed ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector <string> ll;
    vector <string> ll2;
    set<int> pos;
    while(!inbed.eof()){
        getline(inbed,line);
        if(line.length()<1) continue;
        if(line[0] == '#') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[2] != "gene") continue;
        int pre = string2Int(ll[3]) -1;
        if(pos.count(pre)==1){
            continue;
        }else{
            pos.insert(pre);
        }
        ll[3] = Int2String(pre);
        ll2.clear();
        split(ll[ll.size()-1],ll2,";");
        string ltmp = ll2[0];
        ll2.clear();
        split(ltmp,ll2,"=");
        ouf << ll[0] << "\t" << ll2[1] << ".1" << "\t" << ll[3] << "\t" << ll[4] << "\n";
    }
    inbed.close();
    ouf.close();
    return 0;
}
int BestHit(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para->inFile2);
    string outfile = (para->outFile);
    igzstream inf1 ((infile.c_str()),ifstream::in);
    igzstream inf2 ((infile2.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector <string> ll;
    map<string,string> first;
    set<string> find;
    cout << "read " << infile << endl;
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll," \t");
        
        if(find.count(ll[0])==1){
            continue;
        }else{
            find.insert(ll[0].append("."));
//            ouf << line << endl;
        }
        first.insert(pair<string, string>(ll[0].append("."),ll[1]));
    }
    cout << find.size() << " pairs found!" << endl;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");

        if(first[ll[1]] == ll[0].append(".")){
            ouf << line << endl;
        }
    }
    inf1.close();
    inf2.close();
    ouf.close();
    return 0;
}
int changeName(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para->inFile2);
    string outfile = (para->outFile);
    igzstream inf1 ((infile.c_str()),ifstream::in);
    igzstream inf2 ((infile2.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector <string> ll;
    map<string,string> first;
    set<string> find;
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length()<1) continue;
        
    }
    
    return 0;
}
int getContig(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    string chrSeq = "";
    string chr = "";
    int start = 0;
    int end = 1;
    bool first = true,next = true;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0]=='>'){
            if(!first){
                start = 0;
                end = 0;
                for (int i = 0; i < chrSeq.length(); ++i){
                    if(chrSeq[i]=='N'||chrSeq[i]=='n'){
                        if((i -start)>1 && next){
                            ouf << chr << "\t" << start << "\t" << i << "\t" << i -start << "\n";
                            next = false;
                        }
                        start = i+1;
                    }else{
                        next =true;
                    }
                }
                if ((chrSeq.length()-start)>1) {
                    ouf << chr << "\t" << start << "\t" << chrSeq.length() << "\t" << chrSeq.length() -start << "\n";
                }
            }
            first = false;
            start = 0;
            end = 0;
            chrSeq = "";
            chr = line.substr(1,line.length()-1);
            
        }else{
            chrSeq.append(line);
        }
    }
    start = 0;
    end = 0;
    for (int i = 0; i < chrSeq.length(); ++i){
        if(chrSeq[i]=='N'||chrSeq[i]=='n'){
            if((i -start)>1 && next){
                ouf << chr << "\t" << start << "\t" << i << "\t" << i -start << "\n";
                next = false;
            }
            start = i+1;
        }else{
            next = true;
        }
    }
    if ((chrSeq.length()-start)>1) {
        ouf << chr << "\t" << start << "\t" << chrSeq.length() << "\t" << chrSeq.length() -start << "\n";
    }
    return 0;
}
int writeContig(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    string chrSeq = "";
    string chr = "";
    int contig = 0;
    bool first = true,next = true;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0]=='>'){
            string chrSeq="";
            if(!first){
                vector<string> ll ;
                split(chrSeq,ll,"N");
                for (int i = 0; i < ll.size();++i){
                    contig++;
                    ouf << ">" << contig << "\n";
                    int n =0;
                    while(n < ll[i].length() - 80){
                        ouf << ll[i].substr(n,80) << "\n";
                        n+=80;
                    }
                    ouf << ll[i].substr(ll[i].length()-80,ll[i].length()-n);
                    ouf << "\n";
                }
            }
            first = false;
            
        }else{
            chrSeq.append(line);
        }
    }
    vector<string> ll ;
    split(chrSeq,ll,"N");
    for (int i = 0; i < ll.size();++i){
        contig++;
        ouf << ">" << contig << "\n";
        int n =0;
        while(n < ll[i].length() - 80){
            ouf << ll[i].substr(n,80) << "\n";
            n+=80;
        }
        ouf << ll[i].substr(ll[i].length()-80,ll[i].length()-n);
        ouf << "\n";
    }
    ouf.close();
    inf.close();
    return 0;
}
int getScaffold(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    string chrSeq = "";
    string chr = "";
    int start = 0;
    int end = 1;
    bool first = true,next = true;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0]=='>'){
            if(!first){
                start = 0;
                end = 0;
                for (int i = 0; i < chrSeq.length(); ++i){
                    if((chrSeq[i]=='N'||chrSeq[i]=='n') && (chrSeq[i+99]=='N'||chrSeq[i+99]=='n')){
                        if((i -start)>1 && next){
                            ouf << chr << "\t" << start << "\t" << i << "\t" << i -start << "\n";
                            next = false;
                        }
                        start = i+100;
                        i = i+99;
                    }else{
                        next =true;
                    }
                }
                if ((chrSeq.length()-start)>1) {
                    ouf << chr << "\t" << start << "\t" << chrSeq.length() << "\t" << chrSeq.length() -start << "\n";
                }
            }
            first = false;
            start = 0;
            end = 0;
            chrSeq = "";
            chr = line.substr(1,line.length()-1);
            
        }else{
            chrSeq.append(line);
        }
    }
    start = 0;
    end = 0;
    for (int i = 0; i < chrSeq.length(); ++i){
        if((chrSeq[i]=='N'||chrSeq[i]=='n') && (chrSeq[i+99]=='N'||chrSeq[i+99]=='n')){
            if((i -start)>1 && next){
                ouf << chr << "\t" << start << "\t" << i << "\t" << i -start << "\n";
                next = false;
            }
            start = i+100;
            i = i+99;
        }else{
            next = true;
        }
    }
    if ((chrSeq.length()-start)>1) {
        ouf << chr << "\t" << start << "\t" << chrSeq.length() << "\t" << chrSeq.length() -start << "\n";
    }
    return 0;
}

int getGffMCscan(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    string head = (para->headerC);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    string start, end;
    
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0] == '#') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[2]!="mRNA") continue;
        start = ll[3];
        end = ll[4];
        vector<string> tmp ;
        tmp.clear();
        split(ll[8],tmp, ";");
        ll.clear();
        split(tmp[0],ll,"=");
        ouf << head << "\t" << ll[1] << "\t" << start << "\t" << end << "\n";
    }
    
    inf.close();
    ouf.close();
    return 0;
}
int getGffMCscanChr(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0] == '#') continue;
        ll.clear();
        split(line,ll," \t");
        string chr = ll[1].substr(ll[1].rfind('g')-2,2);
        ouf << ll[0].append(chr) << "\t" << ll[1] << "\t" << ll[2] << "\t" << ll[3] << "\n";
    }
    
    inf.close();
    ouf.close();
    return 0;
}
int FstGenes(parameter *para){
    // write two files, one is gff for selected, the other is gff for unselected
    // input is the gene list of selected and the whole gff3 file
    string infile = (para->inFile);
    string infile2 = (para->inFile2);
    string outs = (para->outFile);
    string outfile = outs.append(".selected.gff3");
    outs = (para->outFile);
    string outfile2 = outs.append(".unselected.gff3");
    igzstream inf1 ((infile.c_str()),ifstream::in);
    igzstream inf2 ((infile2.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    ofstream ouf2 (outfile2.c_str());
    string line;
    vector<string> ll;
    set<string> selectedGenes;
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length() < 1) continue;
        selectedGenes.insert(line);
    }
    int size = (para->size);
    vector<string> tmp;
//    set<int> genePos  = Sample(selectedGenes.size(),0,size,11);
//    sort(order.begin(),order.end(),increase);
//
//    for(int i = 0; i < order.size();++i){
//        genePos.insert(order[i]);
//    }
    int geneC = -1;
    string geneName;
    bool write = false;
    string preGene = "";
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        if(line[0] == '#') continue;
        ll.clear();
        split(line,ll, "\t");
        string type =ll[2];
        if(ll[2] == "gene") {
            tmp.clear();
            split(ll[8],tmp,";");
            ll.clear();
            split(tmp[0],ll,"=");
            tmp.clear();
            split(ll[1],tmp,":");
            if(tmp.size()>1) {
                ll[1] = tmp[1];
            }
            preGene = ll[1];
        }else{
            tmp.clear();
            split(ll[8],tmp,".");
            ll.clear();
            split(tmp[0],ll,"=");
            if(line.find(preGene)!=std::string::npos){
                ll[1] = preGene;
            }
        }
        if(selectedGenes.count(ll[1])==1){
            if(ll[2] == "gene"){
                ouf << "###\n";
            }
            ouf << line << "\n";
        }else{
            if(type == "gene"){
                double ra = 1 /double(RAND_MAX) ;
                if (rand() * ra < selectedGenes.size()/(size*1.0)){
                    write = true;
                }else {
                    write = false;
                }
            }
            if(write){
                if(ll[2] == "gene"){
                    ouf2 << "###\n";
                }
                ouf2 << line << "\n";
            }
        }
    }
    inf1.close();
    inf2.close();
    ouf.close();
    ouf2.close();
    return 0;
}
int vcf2Fasta(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para->inFile2);
    string outfile = (para->outFile);
    igzstream inf1 ((infile.c_str()),ifstream::in);
    igzstream inf2 ((infile2.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    vector <string> region;
    string line;
    vector <string> ll;
    return 0;
}
int slicedGenome(parameter *para){
    string gffFile = (para -> inFile);
    string piFile = (para -> inFile2);
    string outFile = (para -> outFile);
    string outFile1 = outFile + ".genes";
    string chr = (para -> chr);
    double threshold = (para -> threshold);
    igzstream infGff ((gffFile).c_str(),ifstream::in);
    igzstream infPi ((piFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    ofstream ouf1 ((outFile1).c_str());
    string line;
    vector<string> ll;
    set<int> withoutIntron;
    int start = 0, end = 0;
    int ps = 0, pe = 0;
    string strand = "";
    vector<int> startP(20000);
    vector<int> endP(20000);
    vector<int> strandP(20000);
    vector<string> genefeaturs(500000000);
    int gene_order = 0;
    // upstream50: 1; upstream20: 2;upstream10: 3; upstream5: 4;upstream2: 5;
    // gene: 20, 5utr: 7; cds: 8; intron: 9; 3utr: 10;
    // down50: 11; down20: 12; down10: 13; down5: 14; down2: 15;
    while(!infGff.eof()){
        getline(infGff,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[2] =='#'&& withoutIntron.size() > 0) {
            for ( int i = start; i < end; ++i){
                if(withoutIntron.count(i) == 0){
                    genefeaturs[i] = 9;
                    //                    intron.insert(i);
                }
            }
            start = 0;
            end = 0;
            withoutIntron.clear();
            ps = 0;
            pe = 0;
            continue;
        };
        if(line[0]=='#') continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0] != chr) continue;
        if(ll[2] == "gene"){
            start = string2Int(ll[3]);
            end = string2Int(ll[4]);
            strand = ll[6];
            startP[gene_order] = start;
            endP[gene_order] = end;
            if(strand == "+"){
                strandP[gene_order] = 0;
            }else{
                strandP[gene_order] = 1;
            }
            gene_order++;
        }else if (ll[2] == "five_prime_UTR"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                genefeaturs[i]= 7;
                withoutIntron.insert(i);
            }
        }else if (ll[2] == "three_prime_UTR"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                genefeaturs[i] = 10;
                withoutIntron.insert(i);
            }
        }else if (ll[2] == "CDS"){
            ps = string2Int(ll[3]);
            pe = string2Int(ll[4]);
            for (int i = ps; i < pe+1; ++i){
                genefeaturs[i] = 8;
                withoutIntron.insert(i);
            }
        }
    }
    
    if(withoutIntron.size() > 1) {
        for ( int i = start; i < end; ++i){
            if(withoutIntron.count(i)==0){
                genefeaturs[i] = 9;
            }
        }
        withoutIntron.clear();
    }
    
    return 0;
}
int getPairAlleleFrequency(parameter *para){
    string infile = (para->inFile);
    string gf1 = (para -> inFile2 );
    string gf2 = (para -> inFile3);
    string outfile = (para->outFile);
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    set<string> name1 = getSubgroup(gf1);
    set<string> name2 = getSubgroup(gf2);
    vector<int> na1;
    vector<int> na2;
    vector<int> na;
    vector<string> ll;
    vector<int> number(9);
    for (int i=0; i <9; ++i){
        number[i] = 0;
    }
    int all = 0, derived = 0;
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1] == '#') {
        };
        ll.clear();
        split(line,ll," \t");
        if(line[0]=='#' && line[1] == 'C') {
            na1 = getPos(ll,name1);
            na2 = getPos(ll,name2);
            if(na1.size() < 1) break;
            if(na2.size() < 1) break;
            continue;
        }
        
        if(na1.size() < 1) continue;
        if(na2.size() < 1) continue;
        
        all++;
        double mf1 = ref(ll,na1);
        double mf2 = ref(ll,na2);
        char ref = ll[ll.size()-1][0];
        if(ref == '0'){
            mf1 = 1 - mf1;
            mf2 = 1 - mf2;
        }
        if (mf1 == 0 || mf1 == 1 || mf2 ==0 || mf2 == 1) continue;
        ouf << ll[0] << "\t" << ll[1] <<"\t" << mf1 <<"\t" << mf2 << "\n" ;
    }
    invcf.close();
    ouf.close();
    return 0;
}
int getExtream(parameter *para){
    string infile = (para->inFile);
    string gf1 = (para -> inFile2 );
    string gf2 = (para -> inFile3);
    string outfile = (para->outFile);
    string outfile1 = outfile + ".1";
    string outfile2 = outfile +".2";
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    ofstream ouf1 (outfile1.c_str());
    ofstream ouf2 (outfile2.c_str());
    string line;
    set<string> name1 = getSubgroup(gf1);
    set<string> name2 = getSubgroup(gf2);
    vector<int> na1;
    vector<int> na2;
    vector<int> na;
    vector<string> ll;
    vector<int> number(9);
    for (int i=0; i <9; ++i){
        number[i] = 0;
    }
    int all = 0, derived = 0;
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1] == '#') {
            ouf << line << "\n";
        };
        ll.clear();
        split(line,ll," \t");
        if(line[0]=='#' && line[1] == 'C') {
            na1 = getPos(ll,name1);
            na2 = getPos(ll,name2);
            if(na1.size() < 1) break;
            if(na2.size() < 1) break;
            ouf << line << "\n";
            continue;
        }
        
        if(na1.size() < 1) continue;
        if(na2.size() < 1) continue;
        
        all++;
        double mf1 = ref(ll,na1);
        double mf2 = ref(ll,na2);
        char ref = ll[ll.size()-1][0];
        if(ref == '0'){
            mf1 = 1 - mf1;
            mf2 = 1 - mf2;
        }
        if ( (mf1 > 0.9 && mf2 < 0.1) || (mf2 > 0.9 && mf1 < 0.1)) {
            ouf << line << "\n";
        };
        if ( (mf1 > 0.9 && mf2 < 0.1) ) {
            ouf1 << line << "\n";
        };
        if ( (mf2 > 0.9 && mf1 < 0.1)) {
            ouf2 << line << "\n";
        };

        
    }
    invcf.close();
    ouf.close();
    ouf1.close();
    ouf2.close();
    return 0;
}
int mummer2vcf(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    string name = (para->headerC);
    ouf << "##fileformat=VCFv4.2\n";
    ouf << "##FILTER=<ID=LowMQ,Description=\"MQ < 30\"" << "\n";
    ouf << "##FILTER=<ID=HighFS,Description=\"FS > 60\">" << "\n";
    ouf << "##FILTER=<ID=HighFS,Description=\"FS > 60\">"<< "\n";
    ouf << "##FILTER=<ID=HighSOR,Description=\"SOR < 3\">"<< "\n";
    ouf << "##FILTER=<ID=LowDP,Description=\"DP < 2\">"<< "\n";
    ouf << "##FILTER=<ID=LowQD,Description=\"QD < 2.0\">"<< "\n";
    ouf << "##FILTER=<ID=LowBaseQRankSum,Description=\"BaseQRankSum < 0\">"<< "\n";
    ouf << "##FILTER=<ID=LowMQRankSum,Description=\"MQRankSum < -12.5\">"<< "\n";
    ouf << "##FILTER=<ID=LowReadPosRankSum,Description=\"ReadPosRankSum < -8\">"<< "\n";
    ouf << "##FORMAT=<ID=AD,Number=.,Type=Integer,Description=\"Allelic depths for the ref and alt alleles in the order listed\">"<< "\n";
    ouf << "##FORMAT=<ID=DP,Number=1,Type=Integer,Description=\"Read depth\">"<< "\n";
    ouf << "##FORMAT=<ID=GQ,Number=1,Type=Integer,Description=\"Genotype quality\">"<< "\n";
    ouf << "##FORMAT=<ID=GT,Number=1,Type=String,Description=\"Genotype\">"<< "\n";
    ouf << "##FORMAT=<ID=PGT,Number=1,Type=String,Description=\"Physical phasing haplotype information,describing how the alternate alleles are phased in relation to one another\">" << "\n";
    ouf << "##FORMAT=<ID=PID,Number=1,Type=String,Description=\"Physical phasing ID information, where each unique ID within a given sample (but not across samples) connects records within a phasing group\">" << "\n";
    ouf << "##FORMAT=<ID=PL,Number=G,Type=Integer,Description=\"The phred-scaled genotype likelihoods rounded to the closest integer\">" << "\n";
    ouf << "Generated by WGS\n";
    ouf << "#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\tFORMAT\t" << name << "\n";
    string flag = (para->flag);
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        if(flag=="ref"){
            if(ll[1]==".") {
                ll[2] = "CC";
                ll[1] = "C";
            }
            if(ll[2]==".") {
                ll[1] = "CC";
                ll[2] = "C";
            }
            ouf<<ll[10] << "\t" << ll[0] << "\t" << ".\t" << ll[1] << "\t" << ll[2] << "\t.\tPASS\t.\tGT\t1/1\n";
        }else if (flag=="query"){
            if(ll[1]==".") {
                ll[2] = "CC";
                ll[1] = "C";
            }
            if(ll[2]==".") {
                ll[1] = "CC";
                ll[2] = "C";
            }
            ouf<<ll[11] << "\t" << ll[3] << "\t" << ".\t" << ll[2] << "\t" << ll[1] << "\t.\tPASS\t.\tGT\t1/1\n";
        }else{
            cerr << "Unknown type! please check --flag, only ref or query is surported " << endl;
        }
    }
    inf.close();
    ouf.close();
    return 0;
}
int mummerCountInDel(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    int InDel = 0;
    string pre = "";
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        split(line,ll," \t");
        if(ll[1]!="." & ll[2]!=".") {
            pre = "";
            continue;
        }else{
            if (pre == ".") continue;
            InDel ++;
            pre = ".";
        }
    }
    ouf << "InDel:\t" << InDel << "\n";
    inf.close();
    ouf.close();
    return 0;
}
int smoothIndel(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    int pre = 0;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
//        cout << line << endl;
        if(line[0]=='#' ){
            if(line[1] == 'C'){
                ll.clear();
                split(line,ll," \t");
                if(ll[1] == "0") continue;
            }
            ouf << line <<"\n";
            continue;
        }
        ll.clear();
        split(line,ll," \t");
        
        int p = string2Int(ll[1]);
        if ((p-pre)>1) {
            ouf << line <<"\n";
        }
        pre = p;
    }
    inf.close();
    ouf.close();
    return 0;
}
int getUniqueGene(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para->inFile2);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    igzstream inf2 ((infile2.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    map<string,int> gene;
    string tmp = "";
    map<string,int> geneLength;
    set <string> allGene;
    double r = (para->r);
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll,"\t");
        int len = string2Int(ll[2]) - string2Int(ll[1])+1;
        tmp = ll[ll.size()-1];
        ll.clear();
        split(tmp,ll,";");
        tmp = ll[0];
        ll.clear();
        split(tmp,ll,"=");
        tmp = ll[1];
        ll.clear();
        split(tmp,ll,":");
        if(ll.size()>1){
            if(ll[0]!="gene") continue;
            geneLength.insert(pair<string,int>(ll[1],len));
        }else{
            ll.clear();
            split(tmp,ll,".");
            geneLength.insert(pair<string,int>(ll[0],len));
        }
    }
    
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        int len = string2Int(ll[2]) - string2Int(ll[1])+1;
        tmp = ll[ll.size()-1];
        ll.clear();
        split(tmp,ll,";");
        tmp = ll[0];
        ll.clear();
        split(tmp,ll,"=");
        tmp = ll[1];
        ll.clear();
        split(tmp,ll,":");
        if(ll.size()>1){
            if(ll[0]!="gene") continue;
            allGene.insert(ll[1]);
            if(gene.count(ll[1])==1){
                int l = gene[ll[1]] + len;
                gene[ll[1]] = l;
            }else{
                gene[ll[1]] = len;
            }
        }else{
            ll.clear();
            split(tmp,ll,".");
            allGene.insert(ll[0]);
            if(gene.count(ll[0])==1){
                int l = gene[ll[0]] + len;
                gene[ll[0]] = l;
            }else{
                gene[ll[0]] = len;
            }
        }
    }
    for (string ge:allGene){
        int l1 = gene[ge];
        int l2 = geneLength[ge];
        if( l1 > r*l2){
            ouf << ge << "\n";
        }
    }
    
    inf.close();
    inf2.close();
    ouf.close();
    
    return 0;
}
int blast2Gene(parameter *para){
    string infile = (para->inFile);
    double r = (para->r);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    set<string> gene;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1)continue;
        ll.clear();
        split(line,ll,"\t");
        double v = string2Double(ll[2])/100;
        if(v>r){
            gene.insert(ll[0]);
        }
    }
    for(string n:gene){
        ouf << n << "\n";
    }
    return 0;
}
int pepTofasta(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para->inFile2);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    igzstream inf2 ((infile2.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    set <string> allGene;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll,".");
        allGene.insert(ll[0]);
    }
    bool write = false;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        
        if(line[0]=='>'){
            ll.clear();
            split(line,ll,".");
            if(allGene.count(ll[0].substr(1,ll[0].length()-1))==1){
                write =true;
            }else{
                write = false;
            }
        }
        if(write){
            ouf << line << "\n";
        }
    }
    inf2.close();
    inf.close();
    ouf.close();
    return 0;
}
int getSingle(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    set <string> allGene;
    
    return 0;
}
int daf(parameter *para){
    string infile = (para->inFile);
    string gf1 = (para -> inFile2 );
    string outfile = (para->outFile);
    igzstream invcf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    set<string> name1 = getSubgroup(gf1);
    vector<int> na1;
    vector<int> na;
    vector<string> ll;
    vector<int> number(9);
    for (int i=0; i <9; ++i){
        number[i] = 0;
    }
    int all = 0, derived = 0;
    while(!invcf.eof()){
        getline(invcf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1] == '#') {
        };
        ll.clear();
        split(line,ll," \t");
        if(line[0]=='#' && line[1] == 'C') {
            na1 = getPos(ll,name1);
            if(na1.size() < 1) break;
            continue;
        }
        
        if(na1.size() < 1) continue;
        
        all++;
        double mf1 = ref(ll,na1);
        char ref = ll[ll.size()-1][0];
        if(ref == '1'){
            mf1 = 1 - mf1;
        }
        ouf << ll[0] << "\t" << ll[1] << "\t" << mf1 << "\n";
    }
    
    invcf.close();
    ouf.close();
    
    return 0;
}
int getRegulation(parameter *para){
    string infile = (para -> inFile);
    string gffFile = (para -> inFile2);
    string outFile = (para -> outFile);
    igzstream infGff ((gffFile).c_str(),ifstream::in);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    int size = (para->size);
    string line;
    vector<string> ll;
    string strand;
    string chr = (para->chr);
    vector<int> value(500000000);
    while(!infGff.eof()){
        getline(infGff,line);
        if(line.length()<1) continue;
        if(line[0]=='#') continue;
        ll.clear();
        split(line,ll,"\t");
        if(ll[0]!=chr) continue;
        if(ll[2] != "gene") continue;
        int start = string2Int(ll[3]);
        int end = string2Int(ll[4]);
        for (int i = start ; i < end+1; ++i){
            value[i] = 1;
        }
        if(ll[6]=="+"){
            int s =(start-size);
            if (s <0 ) s = 0;
            for (int i = s; i < start; ++i){
                if(value[i]!=1) value[i] = 2;
            }
        }else{
            int s =end+size+1;
            if (s>500000000) s = 500000000;
            for (int i = end+1; i < s; ++i){
                if(value[i]!=1) value[i] = 2;
            }
        }
    }
    while (!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0]=='#') continue;
        ll.clear();
        split(line, ll,"\t");
        if(ll[0]!=chr) continue;
        if(value[string2Int(ll[1])]==1){
            ouf << ll[0] << "\t" << ll[1] << "\t" << "G" << "\n";
        }else if(value[string2Int(ll[1])]==2){
            ouf << ll[0] << "\t" << ll[1] << "\t" << "R" << "\n";
        }else{
            ouf << ll[0] << "\t" << ll[1] << "\t" << "N" << "\n";
        }
    }
    ouf.close();
    inf.close();
    infGff.close();
    return 0;
}
int formatFasta(parameter *para){
    string infile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    string strand;
    string chr = (para->chr);
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1)continue;
        if(line[0]=='>'){
            if(line.substr(1,3)=="VIT"){
                ouf << ">VIN" << "\n";
            }else if(line.substr(1,3)=="Nit"){
                ouf << ">NTA" << "\n";
            }else if(line.substr(1,4)=="Solh"){
                ouf << ">SHA" << "\n";
            }else if(line.substr(1,4)=="Sope"){
                ouf << ">SPE" << "\n";
            }else if(line.substr(1,4)=="Soly"){
                ouf << ">SLY" << "\n";
            }else if(line.substr(1,3)=="Sco"){
                ouf << ">SLO" << "\n";
            }else if(line.substr(1,3)=="PGS"){
                ouf << ">STU" << "\n";
            }else if(line.substr(1,3)=="Sme"){
                ouf << ">SME" << "\n";
            }else if(line.substr(1,3)=="Pea"){
                ouf << ">PAX" << "\n";
            }else if(line.substr(1,2)=="CA"){
                ouf << ">CAN" << "\n";
            }
        }else{
            ouf << line << "\n";
        }
    }
    inf.close();
    ouf.close();
    return 0;
}
int getKaKs(parameter *para){
    string infile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<4) continue;
        if(line.substr(0,2)!= "t=") continue;
        ouf << line.substr(42,7) << "\t" << line.substr(56,7) << "\t" << line.substr(69,7) << "\n";
    }
    inf.close();
    ouf.close();
    return 0;
}
int changeBlast(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    map<string,string> ID;
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line.substr(0,1)!= ">") continue;
        ll.clear();
        split(line,ll," ");
        string value = ll[0].substr(1,ll[0].length()-1);
        ll.clear();
        split(line,ll,"|");
        string key = ll[1];
        ID.insert(pair<string,string>(key,value));
    }
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        split(line, ll," \t");
        ll[1] = ID[ll[1]];
        ouf << ll[0];
        for(int i = 1; i < ll.size(); i ++){
            ouf << "\t" <<  ll[i];
        }
        ouf << "\n";
    }
    inf.close();
    ouf.close();
    return 0;
}
int filterMakerGff(parameter *para){
    string infile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    map<string,string> ID;
    vector<string> ll;
    set<string> keywords;
    keywords.insert("gene");
    keywords.insert("mRNA");
    keywords.insert("CDS");
    keywords.insert("exon");
    keywords.insert("three_prime_UTR");
    keywords.insert("five_prime_UTR");
    bool w = true;
    int n = 0;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line.substr(0,1)== "#") continue;
        ll.clear();
        split(line,ll,"\t");
        if(ll.size()!=9) continue;
        if(keywords.count(ll[2]) == 0) continue;
        if(ll[2]=="gene") n++;
        ouf << line << "\n";
    }
    cout << n << " genes annotated!" << endl;
    inf.close();
    ouf.close();
    return 0;
}
int makerRemap(parameter *para){
    string infile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line.substr(0,1)!= ">") continue;
        ll.clear();
        split(line,ll," ");
        string value = ll[0].substr(1,ll[0].length()-1);
        ll.clear();
        split(line,ll,"|");
        string key = ll[1];
    }
    
    inf.close();
    ouf.close();
    return 0;
}

int getSOG(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para->inFile2);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    set<string> added;
    set<string> species;
    
    map<string,int> pos;
    int p = 0;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        species.insert(line);
        pos.insert(pair<string, int>(line,p));
        p++;
    }
    vector<string> gene(species.size());
    cout << species.size() << " species detected!" << endl;
    inf2.close();
    bool write = true;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line, ll," \t");
        added.clear();
        write = true;
        int c = 0;
        for(int i = 1; i < ll.size(); ++i){
            string sn = ll[i];
            if(species.count(sn.substr(0,3))==1){
                if(added.count(sn.substr(0,3))==1){
                    write = false;
                }else{
                    c++;
                    added.insert(sn.substr(0,3));
                    gene[pos[sn.substr(0,3)]] = ll[i];
                }
            }
        }
        if(write && c == gene.size()){
            for(int i = 0 ; i < gene.size()-1; ++i){
                ouf << gene[i] << "\t";
            }
            ouf << gene[gene.size()-1] << "\n";
        }
    }
    inf.close();
    ouf.close();
    return 0;
}
int getCDS(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para->inFile2);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    string line;
    vector<string> ll;
    map<string,string> gene;
    int col = (para->size);
    string key = "",value = "";
    bool first = true;
    string head = (para->headerC);
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        if(line[0]=='>'){
            if(!first){
                gene.insert(pair<string,string>(key,value));
                key = "";
                value = "";
            }
            first = false;
            ll.clear();
            split(line,ll," \t");
            key = ll[0].substr(1,ll[0].length()-1);
            
        }else{
            value.append(line);
            value.append("\n");
        }
    }
    gene.insert(pair<string,string>(key,value));
//    cout<< gene["Solyc03g095783.1.1"] <<endl;
    cout << gene.size() << " genes added!" << endl;
    key = "";
    value = "";
    int cp = 0;
    while(!inf.eof()){
        getline(inf, line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        line = ll[col];
        ll.clear();
        split(line,ll,"|");
        line = ll[1];
        cp++;
        ofstream ouf ((outFile+"."+Int2String(cp)+".fasta").c_str());
        ouf << ">" << head << "|" << line << "\n";
        ouf << gene[line] ;
        ouf.close();
    }
    inf.close();
    inf2.close();
    
    return 0;
}
int getSeq(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para->inFile2);
    string outFile = (para -> outFile);
    ofstream ouf ((outFile).c_str());
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    string line;
    vector<string> ll;
    set<string> gene;
    int col = 0;
    string key = "",value = "";
    bool write = true;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        col = ll[0].length();
        gene.insert(ll[0]);
    }
    cout << gene.size() << " genes added!" << endl;
    key = "";
    value = "";
    int cp = 0;
    while(!inf.eof()){
        getline(inf, line);
        if(line.length()<1) continue;
        if(line[0]=='>'){
            if(gene.count(line.substr(1,col))==1){
                write = true;
                
            }else{
                write = false;
            }
        }
        if (write){
            ouf << line << "\n";
        }
    }
    ouf.close();
    inf.close();
    inf2.close();
    
    return 0;
}
int formatFasta2(parameter *para){
    string infile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    string strand;
    string chr = (para->chr);
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1)continue;
        if(line[0]=='>'){
            ouf << line.substr(0,4) << "\n";
        }else{
            ouf << line << "\n";
        }
    }
    inf.close();
    ouf.close();
    return 0;
}
int formatFasta3(parameter *para){
    string infile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    string strand;
    string chr = (para->chr);
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1)continue;
        if(line[0]=='>'){
            ll.clear();
            split(line,ll," \t");
            ouf << ll[0] << "\n";
        }else{
            ouf << line << "\n";
        }
    }
    inf.close();
    ouf.close();
    return 0;
}
int toPhy(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    string strand;
    string chr = (para->chr);
    map <string,string> nuc;
    string key="", value="";
    bool first = false;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1)continue;
        if(line[0]=='>'){
            if(!first){
                ll.clear();
                split(value,ll,"-");
                string tmp ="";
                for (int i = 0; i < ll.size(); ++i){
                    tmp.append(ll[i]);
                }
                if(tmp.length()%3!=0){
                    cerr << "length is not 3!, please check sequence: >"<< key << endl;
                }
                nuc.insert(pair<string, string>(key,tmp));
                key = "";
                value = "";
                first = false;
            }
            key = line.substr(1,3);
        }else{
            value.append(line);
        }
    }
    ll.clear();
    split(value,ll,"-");
    string tmp ="";
    for (int i = 0; i < ll.size(); ++i){
        tmp.append(ll[i]);
    }
    if(tmp.length()%3!=0){
        cerr << "length is not 3!, please check sequence: >"<< key << endl;
    }
    nuc.insert(pair<string, string>(key,tmp));
    key = "";
    value = "";
    cout << nuc.size() << " sequences readed!" << endl;
    getline(inf2,line);
    first = true;
    bool write = true;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        if(line[0]=='1') continue;
        if((line.length()>10) && line.substr(4,3) == "   "){
            
            if(!first){
                if(write){
                    ouf << nuc.size()-1 << " " << 3*value.length() << "\n";
                    write = false;
                }
                ouf << key << "        " ;
//                cout << key << endl;
                string seq = nuc[key];
//                cout << key << "length is: " << seq.length()  << endl;
                string nucs = "";
                int j = 0;
                for(int i = 0; i < value.length();++i){
                    if(value[i] == ' ') {
                        continue;
                    }else if(value[i] == '-'){
                        nucs.append("---");
                    }else{
                        nucs.append(seq.substr(j*3,3));
                        j++;
                    }
                }
                j = 2;
                for (int i = 0; i < nucs.length(); i = i + 10){
                    
                    if(j%6!=0){
                        ouf << nucs.substr(i,10) << " ";
                    }else{
                        ouf << nucs.substr(i,10) << "\n";
                    }
                    j++;
                }
                ouf << "\n";
                
            }
            first = false;
//            cout << "line is " << line << endl;
            key = line.substr(0,3);
            ll.clear();
            split(line,ll," \t");
            value = "";
            for (int i = 1; i < ll.size();++i){
                value.append(ll[i]);
            }
        }else{
            ll.clear();
            split(line,ll," \t");
            for (int i = 1; i < ll.size();++i){
                value.append(ll[i]);
            }
        }
    }
    ouf << key << "        " ;
    string seq = nuc[key];
    string nucs = "";
    int j = 0;
    for(int i = 0; i < value.length();++i){
        if(value[i] == ' ') {
            continue;
        }else if(value[i] == '-'){
            nucs.append("---");
        }else{
            nucs.append(seq.substr(j*3,3));
            j++;
        }
    }
    j = 2;
    for (int i = 0; i < nucs.length(); i = i + 10){
        if(j%6!=0){
            ouf << nucs.substr(i,10) << " ";
        }else{
            ouf << nucs.substr(i,10) << "\n";
        }
        j++;
    }
    ouf << "\n";
    inf.close();
    inf2.close();
    ouf.close();
    return 0;
}
int RemoveDot(parameter *para){
    string infile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll,".");
        ouf << ll[0] << "\n";
    }
    inf.close();
    ouf.close();
    return 0;
}
int pairOrtho(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para->inFile2);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    igzstream inf2 ((infile2.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    map <string,string> m1,m2;
    double r = (para->r);
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll, " \t");
        double v = string2Double(ll[2])/100;
        if(r>v) continue;
        m1.insert(pair<string,string>(ll[0],ll[1]));
    }
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll, " \t");
        double v = string2Double(ll[2])/100;
        if(r>v) continue;
        if(ll[0] == m1[ll[1]]){
            vector<string> tmp;
            tmp.clear();
            split(ll[0],tmp,".");
            ouf << tmp[0] << "\t";
            tmp.clear();
            split(ll[1],tmp,".");
            ouf << tmp[0] << "\n";
        }
    }
    inf.close();
    inf2.close();
    ouf.close();
    return 0;
}
int summaryBeast(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    string check = "13579862410";
    while (!inf.eof()){
        getline(inf, line);
        if(line.length()<4) continue;
        ll.clear();
        if(line.substr(0,4)!="tree"){
            continue;
        }else{
            ll.clear();
            split(line, ll," (,):");
            string a = ll[3] + ll[5]+ll[7]+ll[9]+ll[11]+ll[14]+ll[19]+ll[23]+ll[26]+ll[29];
            if(a!=check) continue;
            for (int i = 3 ; i < ll.size()-1; ++i){
                ouf << ll[i] << "\t";
            }
            ouf << ll[ll.size()-1] << "\n";
        }
    }
    inf.close();
    ouf.close();
    return 0;
}
int summary2Beast(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    string check = "13579862410";
    int rep = 0;
    while (!inf.eof()){
        getline(inf, line);
        if(line.length()<4) continue;
        ll.clear();
        split(line, ll," \t");
        ouf << "tree STATE_" << rep;
        rep ++;
        ouf << " = ((((" << ll[0] << ":" << ll[1]; //1
        ouf << ",((" << ll[2] << ":" << ll[3]; //3
        ouf << ",(" << ll[4] << ":" << ll[5]; //5
        ouf << ",((" << ll[6] << ":" << ll[7]; //7
        ouf << "," << ll[8] << ":" << ll[9];//9
        ouf << "):" << ll[10] ; //
        ouf << "," << ll[11] << ":" << ll[12];//8
        ouf << "):" << ll[13] ;
        ouf << "):" << ll[14] ;
        ouf << "):" << ll[15] ;
        ouf << "," << ll[16] << ":" << ll[17] ; //6
        ouf << "):" << ll[18] ;
        ouf << "):" << ll[19] ;
        ouf << "," << ll[20] << ":" << ll[21];//2
        ouf << "):" << ll[22] ;
        ouf << "," << ll[23] << ":" << ll[24];//4
        ouf << "):" << ll[25] ;
        ouf << "," << ll[26] << ":" << ll[27];//10
        ouf << "):0.0" << ";\n" ;
    }
    inf.close();
    ouf.close();
    return 0;
}
int keepLongest(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    map<string,string> cds;
    set<string> keyS;
    string key, value;
    bool first =true;
    while (!inf.eof()){
        getline(inf, line);
        if(line.length() <1 ) continue;
        if(line[0]=='>'){
            ll.clear();
            split(line,ll,".");
            key = ll[0];
            if(!first){
                if(keyS.count(key)==1){
                    if(cds[key].length()>value.length()){
                        cds.insert(pair<string, string>(key,value));
                    }
                }else{
                     cds.insert(pair<string, string>(key,value));
                }
            }
            keyS.insert(key);
            first = false;
            value = "";
        }else{
            value.append(line);
            value.append("\n");
        }
    }
    for (string name:keyS){
        ouf << name << ".1" << "\n";
        ouf << cds[name];
    }
    inf.close();
    ouf.close();
    return 0;
}
int changeGenomePos(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    bool write = false;
    string chr = (para->chr);
    string seq;
    while (!inf.eof()){
        getline(inf, line);
        if(line.length() <1 ) continue;
        if(line[0] == '>'){
            if(line.substr(1,chr.length())== chr){
                write = true;
            }else{
                write = false;
            }
        }else{
            if(write){
                seq.append(line);
            }
        }
    }
    string rcseq = reverse_complementary(seq);
    ouf << ">" << chr << "\n";
    for(int length = 0; length < rcseq.length(); length = length + 80){
        int start = length;
        int end = length + 80;
        if (end > rcseq.length()-1) end = rcseq.length()-1;
        ouf << rcseq.substr(start,80) << "\n";
    }
    inf.close();
    ouf.close();
    return 0;
}
int changeGffPos(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para->inFile2);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    igzstream inf2 ((infile2.c_str()),ifstream::in);
    string chr = (para->chr);
    ofstream ouf (outfile.c_str());
    string line;
    bool write = false;
    string seq;
    int Len;
    vector<string> ll;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0] == chr) Len = string2Int(ll[1]);
    }
    while (!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0]!=chr) continue;
        string tmp = ll[3];
        ll[3] = Int2String(abs(string2Int(ll[4])-Len));
        ll[4] = Int2String(abs(string2Int(tmp)-Len));
        if(ll[6]=="-"){
            ll[6] = "+";
        }else{
            ll[6] == "-";
        }
        for (int i =0; i < 8;i++){
            ouf << ll[i] << "\t";
        }
        for (int i = 8; i < ll.size();++i){
            ouf << ll[i] << ";";
        }
        ouf << "\n";
        
    }
    inf.close();
    inf2.close();
    ouf.close();
    return 0;
}
int changeBedPos(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para->inFile2);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    igzstream inf2 ((infile2.c_str()),ifstream::in);
    string chr = (para->chr);
    ofstream ouf (outfile.c_str());
    string line;
    bool write = false;
    string seq;
    int Len;
    vector<string> ll;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0] == chr) Len = string2Int(ll[1]);
    }
    while (!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0]!=chr) continue;
        string tmp = ll[1];
        ll[1] = Int2String(abs(string2Int(ll[2])-Len));
        ll[2] = Int2String(abs(string2Int(tmp)-Len));
        if(ll[5]=="-"){
            ll[5] = "+";
        }else{
            ll[5] == "-";
        }
        for (int i =0; i < ll.size()-1;i++){
            ouf << ll[i] << "\t";
        }
        ouf << ll[ll.size()-1] << "\n";
    }
    inf.close();
    inf2.close();
    ouf.close();
    return 0;
}
int changeVcfPos(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para->inFile2);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    igzstream inf2 ((infile2.c_str()),ifstream::in);
    string chr = (para->chr);
    ofstream ouf (outfile.c_str());
    string line;
    bool write = false;
    string seq;
    int Len;
    vector<string> ll;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        if(ll[0] == chr) Len = string2Int(ll[1]);
    }
    while (!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0]=='#') {
            ouf << line << "\n";
            continue;
        }
        ll.clear();
        split(line,ll," \t");
        if(ll[0]!=chr) continue;
        ll[1] = Int2String(abs(string2Int(ll[1])-Len));
        for (int i =0; i < ll.size()-1;i++){
            ouf << ll[i] << "\t";
        }
        ouf << ll[ll.size()-1] << "\n";
    }
    inf.close();
    inf2.close();
    ouf.close();
    return 0;
}
int kmerStat(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para->inFile2);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    igzstream inf2 ((infile2.c_str()),ifstream::in);
    string chr = (para->chr);
    ofstream ouf (outfile.c_str());
    string line;
    unordered_map<string, int> umap(10000000000);
    while(!inf.eof()){
        
    }
    return 0;
}
int vcf2Dstat(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' & line[1]=='#') continue;
        split(line,ll," \t");
        if(line[0]=='#' & line[1] == 'C'){
            ouf << ll[0] << "\t" << ll[1] ;
            for (int i = 9; i < ll.size();++i){
                ouf << "\t" << ll[i];
            }
            ouf << "\n";
        }else{
            ouf << ll[0] << "\t" << ll[1] ;
            string ref = ll[3];
            string alt = ll[4];
            for (int i = 9; i < ll.size();++i){
                ouf << "\t" ;
                if(ll[i][0]=='0'||ll[i][2]=='0'){
                    ouf << ref << "/" << ref;
                }else if (ll[i][0]=='0'||ll[i][2]=='1'){
                    ouf << ref << "/" << alt;
                }else if (ll[i][1]=='0'||ll[i][2]=='1'){
                    ouf << alt << "/" << alt;
                }else{
                    ouf << "N" << "/" << "N";
                }
            }
            ouf << "\n";
        }
    }
    inf.close();
    ouf.close();
    
    return 0;
}
int mergeDgeno(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para->inFile2);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    set<string> names = getSubgroup(infile2,0);
    string filename;
    vector<string> ll;
    vector<int> na;
    bool first = true;
    while(!inf.eof()){
        getline(inf,filename);
//        cout << filename << endl;
        if(filename.length()<1) continue;
        igzstream invcf (filename.c_str(),ifstream::in);
        while(!invcf.eof()){
            getline(invcf, line);
            if(line[0]=='#' && line[1] == '#') continue;
            ll.clear();
            split(line,ll," \t");
            if(line[0]=='#' && line[1] == 'C') {
                na = getPos(ll,names,2);
                if(first){
                    ouf << ll[0] << "\t" << ll[1] ;
                    for (int i = 0; i < na.size(); ++i){
                        ouf << "\t" << ll[na[i]] ;
                    }
                    ouf << "\n";
                    first = false;
                }
                continue;
            }
            ouf << ll[0] << "\t" << ll[1] ;
            for (int i = 0; i < na.size(); ++i){
                ouf << "\t" << ll[na[i]] ;
            }
            ouf << "\n";
        }
        invcf.close();
    }
    inf.close();
    ouf.close();
    return 0;
}
int getDFreq(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para->inFile2);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    igzstream inf2 ((infile2.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    map<string,string> pos;
    set<string> group;
    map<string,int> gr;
    string outgroup;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll, " \t");
        pos.insert(pair<string,string>(ll[0],ll[1]));
        group.insert(ll[1]);
    }
    int gi = 0;
    for(string g:group){
        gr.insert(pair<string,int>(g,gi));
        gi++;
    }
    vector<int> po;
   
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        ll.clear();
        split(line,ll," \t");
        if(line[0]=='#'){
            for(int i = 2; i < ll.size(); ++i){
                
            }
        }
    }
    return 0;
}
int statGff(parameter *para){
    string infile = (para->inFile);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    map<string,string> pos;
    set<string> group;
    map<string,int> gr;
    string outgroup;
    while(!inf.eof()){
        
    }
    return 0;
}
double getISvalue(vector<string> ll,vector<int>pos){
    double s = 0;
    int d = 0;
    int sum = 0;
    char derived = ll[ll.size()-1][0];
//    cout << "pos 1 is: " << pos[1] << endl;
//    cout << ll[pos[1]][0]<< endl;
    for(int i = 0; i < pos.size();++i){
        
        if(ll[pos[i]][0]=='.'){
            
            continue;
        }else{
            if(ll[pos[i]][0]==derived){
                d++;
                sum++;
            }else if (ll[pos[i]][2]==derived){
                d++;
                sum++;
            }else {
                sum++;
                sum++;
            }
        }
    }
    s = (double)d*1.0/sum;
    if(sum == 0) s = 0;
//    cout << "d is:\t" << d << endl;
//    cout << "sum is:\t" << sum << endl;
//
    return s;
}
int IScore(parameter *para){
    string infile = (para->inFile);
    string infile2 = (para->inFile2);
    string outfile = (para->outFile);
    igzstream inf ((infile.c_str()),ifstream::in);
    ofstream ouf (outfile.c_str());
    string line;
    vector<string> ll;
    set<string> na = getSubgroup(infile2);
    int binSize = (para->size);
    int binNumber = 500000000/binSize+1;
    vector<int> pos;
    map<string,int> gr;
    string outgroup;
    vector<int> siteNumber(binNumber);
    vector<double> IS(binNumber);
    vector<int> start(binNumber);
    vector<int> end(binNumber);
    vector<string> chrV(binNumber);
    string chr = "";
    int startP = 1;
    int endP = binSize;
    int CP = 1;
    int P = 0;
    double ISvalue = 0;
    int siteValue = 0;
    int Cpos = 0;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0]=='#' && line[1] == '#') continue;
        ll.clear();
        split(line,ll," \t");
        if(line[0] == '#' && line[1] == 'C'){
            pos = getPos(ll, na);
//            cout << "readed!" << endl;
            continue;
        }
        Cpos = string2Int(ll[1]);
        string chrC = ll[0];
        if(chrC!=chr){
            startP = 1;
            endP= startP+binSize-1;
            CP = 1;
            ISvalue = 0;
            siteValue = 0;
        }
        chr= chrC;
        if(Cpos > startP && Cpos < endP){
            siteValue++;
            ISvalue+=getISvalue(ll,pos);
        }
        while( Cpos > (startP + binSize)){
            siteNumber[P] = siteValue;
            IS[P] = ISvalue;
            start[P] =startP;
            end[P] = endP;
            chrV[P] = chrC;
            P++;
            siteValue = 0;
            ISvalue = 0;
            startP += binSize;
            endP = startP+binSize-1;
        }
    }
    if(Cpos > startP && Cpos < endP){
        siteNumber[P] = siteValue;
        IS[P] = ISvalue;
        start[P] =startP;
        end[P] = Cpos;
        chrV[P] = chr;
    }
    
    ouf << "Chr\tPos\tStart\tEnd\tSNP_number\ttotal_IS\tmean_IS\n";
    for(int i = 0; i < P+1; ++i){
        ouf << chrV[i] << "\t" << start[i]<<"\t" << end[i] << "\t" << siteNumber[i] <<"\t" << IS[i] << "\t" << IS[i]/siteNumber[i] <<"\n";
    }
    inf.close();
    ouf.close();
    return 0;
}
int getRegion(parameter *para){
    string file = (para -> inFile);
    string file2 = (para -> inFile2);
    string outFile = (para -> outFile);
    igzstream inf ((file).c_str(),ifstream::in);
    igzstream inf2 ((file2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line,line2;
    double left = (para -> a);
    double right = (para -> b);
    bool keep = true;
    int start = 0;
    int end = 1;
    int cp = 0;
    int start_pre = -1001;
    
    string chr = (para->chr);
    while(!inf.eof() && !inf2.eof()){
        getline(inf,line);
        getline(inf2,line2);
        if(line.length()<1) continue;
        if(line2.length()<1) continue;
        if(line[0]=='C') continue;
        if(line2[0]=='C') continue;
        if (line[0]=='N') line="0";
        if (line2[0]=='N') line2="0";
        double value = string2Double(line);
        double value2 = string2Double(line2);
        if( value >= left && value <= right && value2 >= left && value2 <= right){
            if(!keep) {
                start = cp;
                keep = true;
            }else{
                end = cp;
                if((end-start)==32){
                    ouf << chr << "\t" << start << "\t" << end << "\n";
                    start_pre = cp;
                    keep = false;
                }
                
            }
            
        }else{
            keep = false;
        }
        cp++;
    }
    inf.close();
    ouf.close();
    return 0;
}
int getKmerOrder(parameter *para){
    string file = (para -> inFile); // genome need to re-order
    string file2 = (para -> inFile2); // reference genome
    string file3 = (para -> inFile3); // bed file
    string outFile = (para -> outFile);
    igzstream inf ((file).c_str(),ifstream::in);
    igzstream inf2 ((file2).c_str(),ifstream::in);
    igzstream inf3 ((file3).c_str(),ifstream::in);
    
    ofstream ouf ((outFile).c_str());
    string line;
    
    map<uint64_t, vector<int>> kmer;
    map<int, string> fasta;
    int  key;
    string value;
    uint64_t pkey;
    bool first = true;
    cout << "Read reference genome..." << endl;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        if(line[0]=='>'){
            if(!first){
                fasta.insert(pair<int, string>(key,value));
                value.clear();
            }
            first = false;
            key = string2Int(line.substr(1,line.length()-1))-1;
        }else{
            value.append(line);
        }
    }
    fasta.insert(pair<int, string>(key,value));
    value.clear();
    cout << fasta.size() << " sequences readed..." << endl;
    vector<string> ll;
    cout << "Read reference position..." << endl;
    while(!inf3.eof()){
        getline(inf3,line);
        if(line.length() < 1) continue;
        split(line,ll," \t");
        int chr = string2Int(ll[0]);
        string seq = fasta[chr].substr(string2Int(ll[1]),32);
        uint64_t vseq = encode(seq);
        vector<int> ll1(3);
        for (int i = 0; i < 3;++i){
            ll1[i] = string2Int(ll[i]);
        }
        kmer.insert(pair<uint64_t, vector<int>>(vseq,ll1));
    }
    cout << "Reference position readed..." << endl;
    string chr="";
    string linep = "";
    cout << "Read FINAL assembly scaffold..." << endl;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0]=='>'){
            chr = line.substr(1,line.length()-1);
            linep = "";
            first = true;
            cout << "Processing scaffold:\t" << line << endl;
        }else{
            if(first){
                first = false;
                for(int i = 0; i < line.length()-32;++i){
                    if(i==0){
                        for(int j = 0 ; j < 32;j++){
                            if(line[j]=='N') {
                                i= j+1;
                            }
                        }
                        if(i>0) continue;
                    }
                    if(line[i+31]=='N') {
                        i=i+31;
                        continue;
                    }
                    uint64_t ut = encode(line.substr(i,32));
                    if(kmer.count(ut)==1){
                        vector<int> ll1 = kmer[ut];
                        ouf << chr << "\t" << ll1[0] << "\t" << ll1[1] <<"\t" << ll1[2] << "\n";
                    }
                }
            }else{
                string u1;
                int s = linep.length()-32;
                for(int i = linep.length()-32; i< linep.length();++i){
                    if(linep[i]=='N') {
                        s = i+1;
                    }
                }
                for(int i = 0; i < line.length()-32;++i){
                    if(s<linep.length()){
                        u1 = linep.substr(s,linep.length()-s);
                    }else{
                        u1="";
                    }
                    if(line[31-u1.length()]=='N'){
                        i = i + 31-u1.length();
                        continue;
                    }
                    if(line.length() < (32-u1.length())) continue;
                    uint64_t ut = encode(u1.append(line.substr(i,32-u1.length())));
                    if(kmer.count(ut)==1){
                        vector<int> ll1 = kmer[ut];
                        ouf << chr << "\t" << ll1[0] << "\t" << ll1[1] <<"\t" << ll1[2] << "\n";
                    }
                }
            }
        }
    }
    inf.close();
    inf2.close();
    inf3.close();
    ouf.close();
    return 0;
}
int getKmerOrder2(parameter *para){
    string file = (para -> inFile); // genome need to re-order
    string file2 = (para -> inFile2); // reference genome
    string file3 = (para -> inFile3); // bed file
    string outFile = (para -> outFile);
    igzstream inf ((file).c_str(),ifstream::in);
    igzstream inf2 ((file2).c_str(),ifstream::in);
    igzstream inf3 ((file3).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    map<uint64_t, vector<int>> kmer;
    map<int, string> fasta;
    map<string, string> query;
    int  key;
    int k = (para->size);
    string value,qkey,qvalue;
    bool first = true;
    cout << "Read reference genome..." << endl;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        if(line[0]=='>'){
            if(!first){
                fasta.insert(pair<int, string>(key,value));
                value.clear();
            }
            first = false;
            key = string2Int(line.substr(1,line.length()-1))-1;
        }else{
            value.append(line);
        }
    }
    fasta.insert(pair<int, string>(key,value));
    value.clear();
    cout << fasta.size() << " sequences readed..." << endl;
    vector<string> ll;
    cout << "Read reference position..." << endl;
    while(!inf3.eof()){
        getline(inf3,line);
        if(line.length() < 1) continue;
        split(line,ll," \t");
        int chr = string2Int(ll[0]);
        string seq = fasta[chr].substr(string2Int(ll[1]),k);
        uint64_t vseq = encode(seq);
        vector<int> ll1(3);
        for (int i = 0; i < 3;++i){
            ll1[i] = string2Int(ll[i]);
        }
        kmer.insert(pair<uint64_t, vector<int>>(vseq,ll1));
    }
    cout << "Reference position readed..." << endl;
    cout << "Read FINAL assembly scaffold..." << endl;
    first = true;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0]=='>'){
            if(!first){
                query.insert(pair<string, string>(qkey,qvalue));
                qvalue.clear();
            }
            first = false;
            qkey = line.substr(1,line.length()-1);
        }else{
            qvalue.append(line);
        }
    }
    query.insert(pair<string, string>(qkey,qvalue));
    qvalue.clear();
    cout << query.size() << " query contigs readed!" << endl;
    cout << "writing position..." << endl;
    map <string, string>::iterator qiter = query.begin();
    while(qiter != query.end()){
        string scaf = qiter->first;
        string sseq = qiter->second;
        cout << "coting\t"<< scaf << " length is:\t" << sseq.length() << endl;
        for (int i = 0; i < sseq.length()-k; ++i){
            if(i == 0){
                for(int j = 0 ; j < k;j++){
                    if(sseq[j]=='N') {
                        i= j+1;
                    }
                }
                if(i>0) continue;
            }else if(sseq[i+31]=='N') {
                i=i+31;
                continue;
            }
            string sc = sseq.substr(i,k);
            
            uint64_t ut = encode(sc);
            map<uint64_t, vector<int>>::iterator iter = kmer.find(ut);
            if(iter != kmer.end()){
                vector<int> ll1 = iter->second;
                ouf << scaf << "\t" << i << "\t" << i + k << "\t" << ll1[0] << "\t" << ll1[1] <<"\t" << ll1[2] << "\n";
            }else{
                ut = encode(reverse_complementary(sc));
                iter = kmer.find(ut);
                if(iter != kmer.end()){
                    vector<int> ll1 = iter->second;
                    ouf << scaf << "\t" << i << "\t" << (i + k) << "\t" << ll1[0] << "\t" << ll1[1] <<"\t" << ll1[2] << "\n";
                }
            }
        }
        qiter++;
    }
    inf.close();
    inf2.close();
    inf3.close();
    ouf.close();
    return 0;
}
//void changeGff3(parameter *para){
//    string gffFile = (para->inFile);
//    igzstream infGff ((gffFile).c_str(),ifstream::in);
//    
//}
vector<vector<string>> addFeatures(string gffFile, string chr,int size){
/* Features
 U1, U2, U3, U4, U5
 utr5, e1, I1, em, Io, ee utr3
 D1, D2, D3, D4, D5
*/
     vector<string> feature(size,"non");
     vector<string> name(size,"non");
     cout << "reading gff3 file..." << endl;
     gff3 g3 = gff3(gffFile,chr);
     map<string,transcript> trans = g3.long_transcripts;
     map<string,transcript>::iterator it;
     it = trans.begin();
     cout << "genes number is:\t"<< trans.size() << endl;

     while(it != trans.end()){
         
         transcript tr = it->second;
         string ID = tr.ID;
//         cout << "ID is:\t" << ID << endl;

         int start = tr.start;
         int end = tr.end;
         string strand = tr.strand;
         vector<CDS> CDSs = g3.CDSs[ID];
         int csize = CDSs.size();
//         cout << "exon size is:\t" << csize << endl;
//         cout << "start is:\t" << start << endl;
//         cout << "end is:\t" << end << endl;
         if(tr.chr != chr){
             it++;
             continue;
         }
         if(csize < 3) {
             it++;
             continue;
         }
         if(strand == "+"){
             int cs = CDSs[0].start;
             int ce = CDSs[0].end;
             for(int i = cs; i < ce+1; ++i){
                 feature[i] = "Es";
             }
             
             for(int i = ce+1; i < CDSs[1].start;++i){
                 feature[i] = "intron1";
             }
             
             cs = CDSs[csize-1].start;
             ce = CDSs[csize-1].end;
             for(int i = cs; i < ce+1; ++i){
                 feature[i] = "El";
             }
         }else{
             int cs = CDSs[0].start;
             int ce = CDSs[0].end;
             for(int i = cs; i < ce+1; ++i){
                 feature[i] = "El";
             }
             
             cs = CDSs[csize-1].start;
             ce = CDSs[csize-1].end;
             
             for(int i = cs; i < ce+1; ++i){
                 feature[i] = "Es";
             }
             for(int i = CDSs[csize-2].end+1; i < CDSs[csize-1].start;++i){
                 feature[i] = "intron1";
             }
         }
         for(int i = 1; i < CDSs.size()-1; ++i ){
             int cs = CDSs[i].start;
             int ce = CDSs[i].end;
             for(int j = cs; j < ce+1; ++j){
                 feature[j] = "Em";
             }
         }
//         cout << "started..." << endl;
         vector<utr3> utr3s = g3.utr3s[ID];
         if(utr3s.size()==1){
             int u3s = utr3s[0].start;
             int u3e = utr3s[0].end;
           
             for(int j = u3s; j < u3e + 1; ++j){
                 feature[j] = "utr3";
             }
         }
         
         vector<utr5> utr5s = g3.utr5s[ID];
         if(utr5s.size()==1){
             int u5s = utr5s[0].start;
             int u5e = utr5s[0].end;
             for(int j = u5s; j < u5e + 1; ++j){
                 feature[j] = "utr5";
             }
         }
         for(int i = start;i < end+1;i++){
             name[i] = ID;
             if (feature[i] == "non") feature[i] = "intron2";
        }
//        cout << "ended1..." << endl;
         if(strand == "-"){
             for(int i = end + 1; i < end + 1000; i++){
                 feature[i] = "U1";
                 name[i] = ID;
             }
             for(int i = end + 1000; i < end + 2000; i++){
                 feature[i] = "U2";
                 name[i] = ID;
             }
             for(int i = end + 2000; i < end + 3000; i++){
                 feature[i] = "U3";
                 name[i] = ID;
             }
             for(int i = end + 3000; i < end + 4000; i++){
                 feature[i] = "U4";
                 name[i] = ID;
             }
             for(int i = end + 4000; i < end + 5000; i++){
                 feature[i] = "U5";
                 name[i] = ID;
             }
             
             for(int i = start - 1000; i < start ; i++){
                 feature[i] = "D1";
                 name[i] = ID;
             }
             for(int i = start - 2000; i < start - 1000; i++){
                 feature[i] = "D2";
                 name[i] = ID;
             }
             for(int i = start - 3000; i < start - 2000; i++){
                 feature[i] = "D3";
                 name[i] = ID;
             }
             for(int i = start - 4000; i < start - 3000; i++){
                 feature[i] = "D4";
                 name[i] = ID;
             }
             for(int i = start - 5000; i < start - 4000; i++){
                 if(i < 0) continue;
                 feature[i] = "D5";
                 name[i] = ID;
             }
             
         }else{
             for(int i = end + 1; i < end + 1000; i++){
                 feature[i] = "D1";
                 name[i] = ID;
             }
             for(int i = end + 1000; i < end + 2000; i++){
                 feature[i] = "D2";
                 name[i] = ID;
             }
             for(int i = end + 2000; i < end + 3000; i++){
                 feature[i] = "D3";
                 name[i] = ID;
             }
             for(int i = end + 3000; i < end + 4000; i++){
                 feature[i] = "D4";
                 name[i] = ID;
             }
             for(int i = end + 4000; i < end + 5000; i++){
                 feature[i] = "D5";
                 name[i] = ID;
             }
             
             for(int i = start - 1000; i < start ; i++){
                 feature[i] = "U1";
                 name[i] = ID;
             }
             for(int i = start - 2000; i < start - 1000; i++){
                 feature[i] = "U2";
                 name[i] = ID;
             }
             for(int i = start - 3000; i < start - 2000; i++){
                 feature[i] = "U3";
                 name[i] = ID;
             }
             for(int i = start - 4000; i < start - 3000; i++){
                 feature[i] = "U4";
                 name[i] = ID;
             }
             for(int i = start - 5000; i < start - 4000; i++){
                 if(i < 0) continue;
                 feature[i] = "U5";
                 name[i] = ID;
             }
         }
         //
//         for(int i = start - 100000; i < start - 50000; i++){
//             if(i < 0) continue;
//             if(feature[i] == "non") feature[i] = "intergenic";
//             name[i] = ID;
//         }
         for(int i = start - 100000; i < start -50000;i++){
             if(i < 0) continue;
             if(feature[i] == "non"){
                 feature[i] = "intergenic";
                 name[i] = ID;
             }
         }
         for(int i = end + 50000; i < end + 100000;i++){
             if(i < 0) continue;
             if(feature[i] == "non"){
                 feature[i] = "intergenic";
                 name[i] = ID;
             }
         }
//         cout << "ended2..." << endl;
//         cout << "upstream and downstream added" << endl;
         it++;
     }
//    for (int i = 0; i < feature.size();++i){
//        if(feature[i]=="intron2") cout << "intron2" << endl;
//    }
    vector<vector<string>> re;
    re.push_back(feature);
    re.push_back(name);
    return re;
}

int slicedFunction(parameter *para){
    string gffFile = (para -> inFile);
    string piFile = (para -> inFile2);
    string outFile = (para -> outFile);
    string chr = (para -> chr);
    double threshold = (para -> threshold);
    int size = (para->size);
    cout<<"adding features..."<< endl;
    vector<vector<string>> re = addFeatures(gffFile,chr,size);
    cout << " features added!" << endl;
    
    vector<string> feature = re[0];
    vector<string> name = re[1];

    igzstream infPi ((piFile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    map<string,map<string,double>> values;

    while(!infPi.eof()){
        getline(infPi,line);
        if(line.length()<1) continue;
        if(line[0]=='C' ) continue;
        ll.clear();
        split(line,ll,"\t");
        if(ll[0]!=chr) continue;
        int pos = string2Int(ll[1]);
        int size = ll.size() - 1;
        string ID = name[pos];
        string key = feature[pos];
//        if(ID=="TraesCS6D02G395700.1"){
//            if(key == "U1") cout << "U1 found!" << endl;
//        }
//        if(key=="intron2") cout << "intron2" << endl;
        double value = 0;
        if(size > 1){
            if (ll[size] == "-nan" || ll[size] == "nan" || ll[size] == "na" || ll[size] == "NA"|| ll[size] == "Inf"|| ll[size] == "-Inf") continue;
            double v = string2Double(ll[size]);
            if (v < threshold) continue;
            map<string,double> a;
            if(values.count(ID) == 0){
                values.insert(pair<string,map<string,double>>(ID,a));
            }
            
            if(values[ID].count(key) == 1){
                value = values[ID][key] + v;
                a[key] = value;
            }else{
                value = v;
                a.insert(pair<string,int>(key,value));
            }
            values[ID][key] = value;
        }else{
            map<string,double> a;
            if(values.count(ID) == 0){
                values.insert(pair<string,map<string,double>>(ID,a));
            }
            
            if(values[ID].count(key) == 1){
                value = values[ID][key] + 1;
                a[key] = value;
//                if(ID=="TraesCS6D02G395700.1" ){
//                     if( key == "U1"){
//                        cout << "value U1 is:\t" << value << endl;
//                     }else if (key == "U3"){
//                          cout << "value U3 is:\t" << value << endl;
//                     }
//                 }
            }else{
                value ++;
                a.insert(pair<string,int>(key,value));
            }
            values[ID][key] = value;
        }
    }
    
//    cout << "value U1 is:\t" << values["TraesCS6D02G395700.1"]["U1"] << endl;
//
//    cout << "value U3 is:\t" << values["TraesCS6D02G395700.1"]["U3"]  << endl;
//
    map<string,map<string,double>>::iterator itm;
    itm = values.begin();
    // U1, U2, U3, U4,U5,utr3,Es,intron1,Em,intron2,El,utr5,D1,D2,D3,D4,D5
    ouf << "gene\tU5\tU4\tU3\tU2\tU1\tutr5\texon1\tintron1\texon2\tintron2\texon3\tutr3\tD1\tD2\tD3\tD4\tD5\tintergenic" <<"\n";
    
    while(itm != values.end()){
        map<string,double> a = itm->second;
        string geneID = itm->first;
        if(geneID == "non") {
            itm++;
            continue;
        }
        ouf << geneID <<"\t";
        ouf << a["U5"] << "\t" << a["U4"] << "\t" << a["U3"] <<"\t"<< a["U2"] << "\t"<< a["U1"] << "\t" ;
        ouf << a["utr5"] << "\t" << a["Es"] << "\t"<< a["intron1"] << "\t" << a["Em"] << "\t";
        ouf << a["intron2"] << "\t"<< a["El"] << "\t" << a["utr3"] << "\t";
        ouf << a["D1"] << "\t"<< a["D2"] << "\t" << a["D3"] << "\t" << a["D4"] << "\t" << a["D5"];
        ouf << "\t" << a["intergenic"];
        ouf << "\n";
        itm++;
    }
    ouf.close();
    return 0;
}

int getSubTreemix(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    
    string line;
    map<string,set<string>> f4s;
    cout << "Reading information file..." << endl;
    vector<string> ll;
    vector<string> orders;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        if(line.substr(0,3) == "ord") continue;
        ll.clear();
        split(line,ll," \t");
        set<string> subgroup;
        subgroup.insert(ll[1]);
        subgroup.insert(ll[2]);
        subgroup.insert(ll[3]);
        orders.push_back(ll[0]);
        f4s.insert(pair<string,set<string>>(ll[0],subgroup));
    }
    cout << f4s.size() << " information file readed!" << endl;
    ///
    string *filename;
    filename = new string[f4s.size()];
    map<string,int> pname; // key: order, map: index in filename
    for (int i = 0; i < orders.size();++i){
        filename[i] = outFile + orders[i] +".frq";
        pname.insert(pair<string,int>(orders[i],i));
//        cout << filename[i] << endl;
    }
    ///
    ofstream *ouf;
    ouf = new ofstream[f4s.size()];
    for(int i = 0; i < pname.size(); ++i){
        ouf[i].open(filename[i],ios::out);
    }
    map<int,vector<int>> pos;
    getline(inf,line);
    ll.clear();
    split(line,ll," \t");
    int outgroupP = 0;
    cout << "Reading treeMix frq file..." << endl;
    for(int i = 0; i < ll.size();++i){
        if(ll[i]=="outgroup") outgroupP = i;
        map<string,set<string>>::iterator it;
        for(it=f4s.begin();it!=f4s.end();++it){
            string ord = it->first;
            set<string> f4 = it->second;
            if(f4.count(ll[i])==1){
                int po = pname[ord];
                if(pos.count(i)==0){
                    vector<int> p;
                    p.push_back(po);
                    pos.insert(pair<int,vector<int>>(i,p));
                }else{
                    vector<int> p = pos[i];
                    p.push_back(po);
                    pos[i] = p;
                }
            }
        }
    }
    for (int i = 0; i < ll.size(); ++i){
        if(pos.count(i)==1){
            vector<int> p = pos[i];
            for(int j = 0; j < p.size();j++){
                ouf[p[j]] << ll[i] << "\t";
            }
        }
    }
    for(int i = 0; i < f4s.size(); ++i){
        ouf[i] << "outgroup\n";
    }
    cout << "header added!" << endl;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        vector<string> ll;
        ll.clear();
        split(line,ll," \t");
        for (int i = 0; i < ll.size(); ++i){
            if(pos.count(i)==1){
                vector<int> p = pos[i];
                for(int j = 0; j < p.size();j++){
                    ouf[p[j]] << ll[i] << "\t";
                    
                }
            }
        }
        for(int i = 0;  i<f4s.size();i++){
            ouf[i] << ll[outgroupP];
            ouf[i] << "\n";
        }
        
    }
    for(int i = 0;  i<f4s.size();i++){
        ouf[i].close();
    }
    return 0;
}
int DtoBed(parameter *para){
    string infile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0]=='s') continue;
        ll.clear();
        split(line,ll,",");
        if(ll[8] == "-nan" || ll[8] == "nan" || ll[8] == "na" || ll[8] == "NA"|| ll[8] == "Inf"|| ll[8] == "-Inf") continue;
        if(ll[9] == "-nan" || ll[9] == "nan" || ll[9] == "na" || ll[9] == "NA"|| ll[9] == "Inf"|| ll[9] == "-Inf") continue;
        double Dvalue = string2Double(ll[8]);
        if(Dvalue < 0) continue;
        double fd_value = string2Double(ll[9]);
        if(fd_value > 1) continue;
        ouf << ll[0] << "\t" << ll[1] << "\t" << ll[2] << "\t" << "100" << "\t" << ll[8] << "\t" << ll[9] << "\t" << ll[10] << "\n";
    }
    inf.close();
    ouf.close();
    
    return 0;
}
int DtoBed2(parameter *para){
    string infile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0]=='s') continue;
        ll.clear();
        split(line,ll,",");
        ouf << ll[0] << "\t" << ll[1] << "\t" << ll[2] << "\t" << "500" << "\t" << ll[8] << "\t" << ll[9] << "\t" << ll[10] << "\n";
    }
    inf.close();
    ouf.close();
    
    return 0;
}
int Bed(parameter *para){
    string infile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line[0]=='s') continue;
        ll.clear();
        split(line,ll,",");
        if(ll[8] == "-nan" || ll[8] == "nan" || ll[8] == "na" || ll[8] == "NA"|| ll[8] == "Inf"|| ll[8] == "-Inf") continue;
        if(ll[9] == "-nan" || ll[9] == "nan" || ll[9] == "na" || ll[9] == "NA"|| ll[9] == "Inf"|| ll[9] == "-Inf") continue;
        double Dvalue = string2Double(ll[8]);
        if(Dvalue < 0) continue;
        double fd_value = string2Double(ll[9]);
        if(fd_value > 1) continue;
        ouf << ll[0] << "\t" << ll[1] << "\t" << ll[2] << "\t" << "100" << "\t" << ll[8] << "\t" << ll[9] << "\t" << ll[10] << "\n";
    }
    inf.close();
    ouf.close();
    
    return 0;
}
int getGeoDistance(parameter *para){
/*
 
*/
    string infile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    vector<double> lat;
    vector<double> lng;
    vector<string> ID;
    getline(inf,line);
    split(line,ll,"\t");
    int latp = 0, lngp = 0;
    for(int i = 0; i < ll.size(); ++i){
        if(ll[i] == "Latitude") {
            latp = i;
        }else if (ll[i] == "Longitude"){
            lngp = i;
        }
    }
//    cout <<"latP is:\t" << latp << endl;
//    cout <<"lngP is:\t" << lngp << endl;
    
    double EarthRadius = 6378.1;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        if(ll[latp] == "NA" || ll[lngp] == "NA") continue;
        lat.push_back(string2Double(ll[latp]));
        lng.push_back(string2Double(ll[lngp]));
        ID.push_back(ll[0]);
    }
    
    for(int i = 0; i < ID.size()-1; ++i){
        for (int j = i+1; j < ID.size();++j){
            double a1 = radian(lat[i]);
            double a2 = radian(lat[j]);
            double b1 = radian(lng[i]);
            double b2 = radian(lng[j]);
            double a = a1 - a2;
            double b = b1 - b2;
            double cal = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(a1)
                                                 * cos(a2) * pow(sin(b / 2), 2))) * EarthRadius;
            double result = round(cal * 10000) / 10000;
            ouf << ID[i] << "\t" << ID[j] << "\t" << result << "\n";
        }
    }
    
    inf.close();
    ouf.close();
    
    return 0;
}
int getGeneticDistance(parameter *para){
    string infile = (para -> inFile);
    string outFile = (para -> outFile);
    string sampleFile = (para -> inFile3);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    vector<double> lat;
    vector<double> lng;
    vector<string> ID;
    getline(inf,line);
    set<string> subs = getSubgroup(sampleFile);
    split(line,ll,"\t");
    vector<int> np;
    vector<string> head;
    double** distanceMatrix = dmatrix(-1, subs.size() + 1, -1, subs.size()+1);
    double** markerMatrix = dmatrix(-1, subs.size() + 1, -1, subs.size()+1);
    int cl = 0;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '#' && line[1] == '#') continue;
        cl++;
        if(cl%10000==0){
             cout << "Current line is:\t" << cl << endl;
        }
        ll.clear();
        split(line,ll,"\t");
        if(line[0] == '#' && line[1] == 'C'){
            np = getPos(ll,subs);
            split(line,head,"\t");
            cout << "Reading vcf file..." << endl;
            continue;
        }
        for (int i = 0; i < np.size()-1; ++i){
            string a = ll[np[i]];
            for(int j = i+1; j < np.size(); ++j){
                string b =ll[np[j]];
                if(a[0] =='.' || b[0] == '.') {
                    continue;
                }else{
                    markerMatrix[i][j] ++;
                    if(a[0] != a[2] || b[0] != b[2]){
                        distanceMatrix[i][j] = distanceMatrix[i][j] + 0.5;
                    }else if(a[0]==b[0]){
                        distanceMatrix[i][j] ++;
                    }else{
                        continue;
                    }
                }
            }
        }
    }
    cout << "Distance calculated!" << endl;
    ouf << "ID1\tID2\tsum\tmarker\tmean\n";
    for (int i = 0; i < np.size()-1; ++i){
        for (int j = i+1; j < np.size();++j){
//            cout << "i is:\t" << i <<";j is:\t" << j << endl;
            
            ouf << head[np[i]] << "\t" << head[np[j]] << "\t";
            ouf << markerMatrix[i][j]- distanceMatrix[i][j] << "\t";
            ouf << markerMatrix[i][j] << "\t";
            ouf << 1 - distanceMatrix[i][j]/markerMatrix[i][j] << "\n";
        }
    }
    inf.close();
    ouf.close();
    
    return 0;
}
int getGeneticDistance2(parameter *para){
    cout << "new version!" << endl;
    string infile = (para -> inFile); // vcf文件
    string infile2 = (para -> inFile2); // final文件
    string infile3 = (para -> inFile3); // ID顺序文件，A.list+B.list
    string outFile = (para -> outFile);
    string name = (para-> flag); // 指定ID
    double threshold = (para ->threshold);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    igzstream inf3 ((infile3).c_str(),ifstream::in);
    string chr = (para->chr);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    map<string,string> ID;
// ID file
    while (!inf3.eof()){
        getline(inf3,line);
        if(line.length() < 1) continue;
        split(line,ll,"\t");
        ID.insert(pair<string,string>(ll[0],ll[1].substr(0,4)));
    }
    cout << "ID file readed!" << endl;
// VCF file
    map <string,vector<int>> vcf;
    map<string,int> idp;
    while (!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        if(line[0] == '#'){
            if (line[1] == '#') continue;
            split(line,ll,"\t");
            for(int i = 9; i < ll.size(); i++){
                idp.insert(pair<string,int>(ll[i],i));
//                cout << ll[i] << endl;
//                cout << idp[ll[i]] << endl;
            }
            continue;
        }
        split(line,ll,"\t");
        string key = ll[0] + "_" + ll[1];
        vector<int> genotype;
        for (int i = 9; i < ll.size(); i++){
            if(ll[i][0] == '.'){
                genotype.push_back(-2);
            }else{
                genotype.push_back((int)ll[i][0] + (int)ll[i][2] -97);
//                cout << genotype[i-9] << endl;
            }
        }
        vcf.insert(pair<string,vector<int>>(key,genotype));
    }
    cout << "vcf file readed!" << endl;
    // read final file
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        ll.clear();
        if(line[0] == 's'){
            ouf << line << "\n";
            continue;
        }
        split(line,ll,"\t");
        if(ll[0] != chr) continue;
        if(string2Double(ll[5]) < threshold) continue;
        int start = string2Int(ll[1]);
        int end = string2Int(ll[2]);
        string ids = ll[6];
        vector<string> ll1 = ll;
        ll.clear();
        split(ids,ll,",");
        if (ll.size() == 1) {
            ouf << line << "\n";
        }else{
            vector<double> distance(ll.size(),0);
            int k1 = idp[name];
            for(int i = 0; i < ll.size(); i++){
                // calcualte dxy
                string name2 = ID[ll[i]];
                int k2 = idp[name2];
                int marker = 0;
                for(int p = start; p < end; p++){
                    string c = chr + "_" + Int2String(p);
        
                    if(vcf.count(c)==0) continue;
                    vector<int> genotype = vcf[c];
                    if (genotype[k1] < -1 | genotype[k2] < -1) continue;
                    marker++;
                    double f = genotype[k1] * genotype[k2];
                    if (f < 0 ){
                        f = 0;
                    }else if (f = 0){
                        f = 0.5;
                    }else{
                        f = 1;
                    }
                    distance[i] += f;
                }
                distance[i] = distance[i]/marker;
            }
            double tmp;
            tmp = distance[0];
            int max = 0;
            bool multiple = false;
            for(int i = 1; i < distance.size(); i++){
                if ((distance[i] - tmp) == 0){
//                    cout << distance[i] << "\t" << tmp  << endl;
                    multiple = true;
                }else{
                    if((distance[i] - tmp)>0){
                        max = i;
                        multiple = false;
                        tmp = distance[i];
                    }
                }
//                cout << "multipleC is:\t" << multiple << endl;
            }
//            cout << "max is:\t" << max << endl;
//            cout << "multiple is:\t" << multiple << endl;
            for (int i = 0; i < ll1.size()-1;++i){
                ouf << ll1[i] << "\t";
            }
            if (multiple){
                ouf << "NA" << "\n";
            }else{
                ouf << ll[max] << "\n";
            }
        }
        
    }
    ouf.close();
    
    return 0;
}
int getIBSdistance_site(parameter *para){
    /*
     This was designed to get calculate the IBS distance among one and a population ;
     input: site file indicating passed or not;
     input: vcf files;
     input: sample files;
     output: IBS distance using passed sites only;
     */
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string infile3 = (para -> inFile3);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in); // vcf file
    igzstream inf2 ((infile2).c_str(),ifstream::in); // site file
//    igzstream inf3 ((infile3).c_str(),ifstream::in); // ID file
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    set<string> IDs = getSubgroup(infile3);
    string ID1 = (para -> flag);
    
    return 0;
}
int getIBSdistance_bed(parameter *para){
    /*
     This was designed to get calculate the IBS distance among one and a population and report the most smallest ones;
     input: bed file;
     input: vcf files;
     input: sample files;
     */
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string infile3 = (para -> inFile3);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in); // vcf file
    igzstream inf2 ((infile2).c_str(),ifstream::in); // bed file
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    set<string> IDs = getSubgroup(infile3);
    vector<int> ranges;
    vector<int> orders;
    string ID1 = (para -> flag);
//    map<range*,int> bedpairs;
//    vector <int> range;
    int pos1;
    int order = 0;
   
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
//        if(string2Int(ll[3]) < 3) continue;
        ranges.push_back(string2Int(ll[1]));
        ranges.push_back(string2Int(ll[2]));
//        cout << ll[1] << ": " << string2Int(ll[1]);
//        cout << ll[2] << ": " << string2Int(ll[2]);
        orders.push_back(order);
        order++;
    }
    cout << "File2 size is:\t" << orders.size() << endl;
//    for(int i = 0; i < orders.size(); i++){
//        cout << orders[i] << endl;
//    }
//    bool cal = false;
    map<int,string> ID2p;
    vector<int> pos2;
//    int r = 0;
//    double ibs = 0;
//    vector<double> ibd(orders.size(),0);
//    vector<string> selected(orders.size(),"");
    vector<double> ibd_tmp (IDs.size(),0);
    vector<double> maker_tmp (IDs.size(),0);
    vector<double> IBD_tmp (IDs.size(),0);
    vector<double> MARKER_tmp (IDs.size(),0);
    map<int,vector<double>> ibsv;
    map<int,vector<double>> makerv;
    int passed = 0;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '#' && line[1] == '#') continue;
        if(line[1] == 'C'){
            ll.clear();
            split(line,ll,"\t");
            for(int i = 9; i < ll.size();i++){
                if(ll[i] == ID1) pos1 = i;
                if(IDs.count(ll[i]) == 1){
                    pos2.push_back(i);
                    ID2p.insert(pair<int,string>(i,ll[i]));
                }
            }
            continue;
        }
        ll.clear();
        split(line,ll,"\t");
        int p = string2Int(ll[1]);
        int c = bianrysearch(ranges,orders,ranges.size(),p);
        if (c == -1) continue;
        if (ibsv.count(c) == 0){
            initialize(IBD_tmp);
//            cout << "c is: "<< c <<"; bid_tmp[8] = " << ibd_tmp[8] << endl;
        }else{
            IBD_tmp = ibsv[c];
        }
        if (makerv.count(c) == 0){
            initialize(MARKER_tmp);
        }else{
            MARKER_tmp = makerv[c];
        }
        passed++;
        initialize(maker_tmp);
        initialize(ibd_tmp);
        calibs(pos2,ll,pos1,ibd_tmp,maker_tmp);
//        cout << "C is:\t" << c <<"; marker 8 is:\t" << maker_tmp[8] << endl;
        for(int i = 0; i < ibd_tmp.size();i++){
            MARKER_tmp[i] += maker_tmp[i];
            IBD_tmp[i] += ibd_tmp[i];
        }
//        cout << "C is:\t" << c <<"; ibd_tmp 8 is:\t" << IBD_tmp[8] << endl;
        if (ibsv.count(c) == 0){
            ibsv.insert(pair<int,vector<double>>(c,IBD_tmp));
        }else{
            ibsv[c] = IBD_tmp;
        }
        if (makerv.count(c) == 0){
            makerv.insert(pair<int,vector<double>>(c,MARKER_tmp));
        }else{
            makerv[c] = MARKER_tmp;
        }
        
    }
    cout << "Passed number is:\t" << passed++ << endl;
    for (int i = 0; i < orders.size(); ++i){
        ouf << ll[0] << "\t" << ranges[i*2] << "\t" << ranges[i*2+1] << "\t";
        ibd_tmp = ibsv[i];
//        cout << "ibd size is:\t" << ibd_tmp.size() << endl;
        maker_tmp = makerv[i];
        vector <double> ibs_dis(ibd_tmp.size(),0);
//        cout << "debug1..." << endl;
        for(int i = 0; i < ibd_tmp.size();i++){
//            cout <<"marker number is:\t" << maker_tmp[i] << endl;
//            cout <<"ibd_tmp  is:\t:" << ibd_tmp[i] << endl;
            if(maker_tmp[i] == 0){
                ibs_dis[i] = 1;
            }else{
                ibs_dis[i] = 1 - ibd_tmp[i]/maker_tmp[i];
            }
        }
//        cout << "debug2..." << endl;
//        cout << "ibs_ids length is:\t" << ibs_dis.size() << endl;
//        for(int i = 0; i < ibs_dis.size();i++){
//            cout << "i is:\t" << i <<",value is:\t" << ibs_dis[i] << endl;
//        }
        if(ibs_dis.size() == 0 ) {
            ouf << "NA\tNA\n";
            continue;
        };
        std::vector<double>::iterator smallest = std::min_element(std::begin(ibs_dis), std::end(ibs_dis));
        double s = *smallest;
//        cout << "debug3..." << endl;
        for (int i = 0; i < ibs_dis.size();i++){
            if(ibs_dis[i] == s) {
                ouf << ID2p[pos2[i]] <<";";
            }
//            ibs_dis[i] = 0;
        }
        ouf << "\t";
        ouf << s << "\n";
    }
    ouf.close();
    return 0;
}
int getGeneticDistanceRef(parameter *para){
    string infile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    vector<string> IDs;
    double** distanceMatrix = dmatrix(-1, 500 , -1, 500);
    for(int i = 0; i < 500;++i){
        for(int j = 0; j < 4;j++){
            distanceMatrix[i][j] = 0;
        }
    }
    cout << "Reading file..." << endl;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '#' && line[1] == '#') continue;
        ll.clear();
        split(line,ll,"\t");
        if(line[0] == '#' && line[1] == 'C'){
            split(line,ll,"\t");
            for(int i = 9; i < ll.size(); ++i){
                IDs.push_back(ll[i]);
            }
            continue;
        }
        for (int i = 9; i < ll.size(); ++i){
            if(ll[i][0] == '.') continue;
            if(ll[i][0]=='0'){
                if(ll[i][2] == '0'){
                    distanceMatrix[i-9][0] ++;
                }else{
                    distanceMatrix[i-9][0] += 0.5;
                }
            }
            distanceMatrix[i-9][1] ++;
            
        }
    }
    cout << "Distance calculated!" << endl;
    ouf << "ID\tsum\tmarker\tmean\n";
    for (int i = 0; i < IDs.size(); ++i){
        ouf << IDs[i] << "\t";
        ouf << distanceMatrix[i][0] << "\t";
        ouf << distanceMatrix[i][1] << "\t";
        ouf << 1 - distanceMatrix[i][0]/distanceMatrix[i][1] << "\n";
    }
    inf.close();
    ouf.close();
    return 0;
}
int generateSyntenyGenome(parameter *para){
    string infile = (para -> inFile); // genome
    string infile2 = (para -> inFile2); // synteny sits
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    map<string,string> genome;
    string chr = (para->chr);
    string seq = "";
    string chrkey = "";
    bool getc = false;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '>'){
            int len = line.length() -1;
            if (len >2) len = 2;
            chrkey = line.substr(1,len);
            if (chrkey == chr) {
                getc = true;
            }else{
                getc = false;
            }
            continue;
        }
        if (getc){
            seq.append(line);
        }
    }
    cout << chr <<" length is:\t" << seq.length() << endl;
    genome.insert(pair<string,string>(chr,seq));
    cout << genome.size() << " chromosomes added!" << endl;
    set<int> pos;
    vector<string> ll;
    while(!inf2.eof()){
        getline(inf2,line);
        if (line.length() < 1) continue;
        split(line,ll,"\t");
        if(ll[0] != chr ) continue;
        int p = string2Int(ll[1]) -1 ;
        pos.insert(p);
    }
    cout << pos.size() <<  " pos added!" << endl;
    ouf << ">" << chr << "\n";
    for (int i = 0;i<seq.length();i++){
        if(pos.count(i) == 1){
            ouf << seq[i];
        }else{
            ouf << "N";
        }
        if( (i +1)%60 == 0) {
            ouf << "\n";
        }
    }
    if(seq.length()%60!=0) ouf << "\n";
    ouf.close();
    return 0;
}

int generateAltGenome(parameter *para){
    string infile = (para -> inFile); // genome
    string infile2 = (para -> inFile2); // vcf file
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    map<string,string> genome;
    string chr = (para->chr);
    string seq = "";
    string chrkey = "";
    string ID = (para->flag);
    bool getc = false;
    string line;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '>'){
            int len = line.length() -1;
            if (len >2) len = 2;
            chrkey = line.substr(1,len);
            if (chrkey == chr) {
                getc = true;
            }else{
                getc = false;
            }
            continue;
        }
        if (getc){
            seq.append(line);
        }
    }
    
    cout << chr <<" length is:\t" << seq.length() << endl;
    genome.insert(pair<string,string>(chr,seq));
    cout << genome.size() << " chromosomes added!" << endl;
    set<int> pos;
    vector<string> ll;
    map<int,string> alt;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        if(line[0] == '#') continue;
        split(line,ll,"\t");
        if(ll[9][0] == '0' && ll[9][2] == '0'  ) continue;
        if (ll[9][0] == '.') continue;
        if(ll[0] != chr) continue;
        if (ll[4].length() !=1) continue;
        alt.insert(pair<int,string>(string2Int(ll[1])-1,ll[4]));
    }
    ouf << ">" << ID << "\n";
    for(int i = 0; i < seq.length(); i++ ){
        if(alt.count(i) ==1){
            if(alt[i] == "N") {
                cerr << "N counted" << endl;
            }
            ouf << alt[i] ;
        }else{
            ouf << seq[i];
        }
        if((i+1)%60 ==0){
            ouf << "\n";
        }
    }
    if(seq.length()%60 !=0){
        ouf << "\n";
    }
    ouf.close();
    return 0;
}
int splitGenome(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    
    string line;
    string seq;
    string key = "";
    map<string,string> genome;
//    double start = (para->a) -1;
//    double len = (para->b) - start;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '>'){
//            cout << "length is:\t" << line.length() <<endl;
            if(key != ""){
                genome.insert(pair<string,string>(key,seq));
//                ouf << seq.substr(start,len);
//                ouf << "\n";
            }
            key = line;
//            ouf << line << "\n";
//            seq = "";
        }else{
            seq.append(line);
        }
    }
    genome.insert(pair<string,string>(key,seq));
    cout << genome.size() << " sequences added!" << endl;
    string outFile = (para -> outFile);
    vector<string> ll;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1 ) continue;
        split(line,ll,"\t");
        ofstream ouf ((outFile+"."+ll[1]+".fa").c_str());
        int start = string2Int(ll[1])-1;
        if (start < 1) start = 1;
        int end = string2Int(ll[2]) ;
        
        int len = end-start;
        map<string,string>::iterator it;
        it = genome.begin();
        int s = 0;
        while(it != genome.end()){
            ouf << it->first << "\n";
            cout << "length is:\t" << it->first <<endl;
            seq = (it->second);
//            ouf << seq.substr(start,len);
            if (end > seq.length()) end = seq.length();
            for (int i = start; i < end; i++){
                s++;
                ouf << seq[i] ;
                if(s%60 == 0) {
                    ouf << "\n";
                }
            }
            
            if(s%60 !=0) ouf << "\n";
            it ++;
//            ouf << "\n";
        }
        ouf.close();
    }
//    ouf << seq.substr(start,len);
    
    return 0;
}
int elai_summary(parameter *para){
    string infile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf_sum ((outFile+".sum.txt").c_str()); // total ratio
    double t = (para->threshold);
    string line;
    vector<string> ll;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        split(line,ll," \t");
        double sum = 0;
//        cout << "snps size is:\t" << ll.size()/2 << endl;
        for (int i = 0; i < ll.size(); i+=2){
            double r = string2Double(ll[i]);
            if(r > t) sum ++;
        }
        ouf_sum << sum << "\t" << ll.size()/2 << "\t" << sum/ll.size() << "\n";
    }
    ouf_sum.close();
    return 0;
}

int elai_region(parameter *para){
    string infile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    double t = (para->threshold);
    string line;
    vector<string> ll;
    int cl = 0;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        split(line,ll," \t");
        cl++;
        ofstream ouf_sum ((outFile + "." + Int2String(cl) + ".sites.txt").c_str()); // total ratio
        for (int i = 0; i < ll.size(); i+=2){
            double r = string2Double(ll[i]);
            if(r > t) {
                ouf_sum << "1\n";
            }else{
                ouf_sum << "0\n";
            }
        }
        ouf_sum.close();
    }
    return 0;
}
int elai_regions(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string infile3 = (para -> inFile3);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    igzstream inf3 ((infile3).c_str(),ifstream::in);
    
    double t = (para->threshold);
    string line;
    string line2;
    string line3;
    vector<string> ll;
    vector<string> ll2;
    vector<string> ll3;
    int cl = 0;
    while (!inf.eof()){
        getline(inf,line);
        getline(inf2,line2);
        getline(inf3,line3);
        if(line.length() < 1) continue;
        split(line,ll," \t");
        split(line2,ll2," \t");
        split(line3,ll3," \t");
        cl++;
        ofstream ouf_sum ((outFile + "." + Int2String(cl) + ".sites.txt").c_str()); // total ratio
        for (int i = 0; i < ll.size(); i+=2){
            double r = string2Double(ll[i]);
            double r2 = string2Double(ll2[i]);
            double r3 = string2Double(ll3[i]);
            if((r+r2+r3)/3 > t) {
                ouf_sum << "1\n";
            }else{
                ouf_sum << "0\n";
            }
        }
        ouf_sum.close();
    }
    return 0;
}
int elai2bed(parameter *para){
    string infile = (para -> inFile); // snps file
    string infile2 = (para -> inFile2); // site file
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str()); // total ratio
    string line;
    vector<string> ll;
    vector<int> pos;
    string chr;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0]=='#') continue;
        split(line,ll," \t");
        if(ll[0] == "rs") continue;
        chr=ll[4];
        pos.push_back(string2Int(ll[5]));
    }
    int start = 0, end = 0;
    bool cont = false;
    int cl = 0;
    int counted = 0;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        int v = string2Int(line);
        if (v == 0){
            if (cont & (end > start) ){
                ouf << chr << "\t" << start << "\t" << end << "\t"<< counted<< "\n";
            }
            counted = 0;
            cont = false;
        }else{
            if(!cont){
                start = pos[cl];
                cont = true;
                counted++;
            }else{
                counted++;
                end = pos[cl];
            }
        }
        cl++;
    }
    if (cont &(end > start) ){
        ouf << chr << "\t" << start << "\t" << end << "\t"<< counted << "\n";
    }
    ouf.close();
    return 0;
}


int changeGeneticDistance(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    string seq;
    string key = "";
    map<string,string> snps;
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        snps.insert(pair<string,string>(ll[0],ll[2]));
    }
    cout << "All snps readed!" << endl;
    while (!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        if(snps.count(ll[0])== 0){
            cerr << "SNPs not found!" << endl;
        }
        ll[2] = snps[ll[0]];
        ouf << ll[0];
        for (int i = 1; i < ll.size(); i++ ){
            ouf << "\t" << ll[i];
        }
        ouf << "\n";
    }
    ouf.close();
    return 0;
}
int vcfoverlap(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    set<string> sites;
    vector<string> ll;
    string chr = (para->chr);
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        split(line,ll," \t");
        sites.insert(ll[0]+"_"+ll[1]);
    }
    cout << "sites readed!" << endl;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0]=='#'){
            ouf << line << "\n";
        }else{
            ll.clear();
            split(line,ll," \t");
            if(sites.count(ll[0]+"_"+ll[1])==1){
                ouf << line << "\n";
            }
        }
    }
    ouf.close();
    return 0;
}
int getIntersectVcf(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outFile = (para -> outFile);
    string sampleFile = (para -> inFile3);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    set<string> sites;
    set<string> subs = getSubgroup(sampleFile);
    vector<string> ll;
    vector<int> np;
    
    cout << "Reading sites..." << endl;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        if(line.substr(0,1)=="#") continue;
        ll.clear();
        split(line,ll,"\t");
        sites.insert(ll[0]+"_"+ll[1]);
    }
    cout << "Total sites is:\t" << sites.size() << endl;
    
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line.substr(0,2) == "##") {
            if(para->recode){
                ouf << line << "\n";
            }
            continue;
        };
        ll.clear();
        split(line,ll,"\t");
        if(line[0] == '#' && line[1] == 'C'){
            np = getPos(ll,subs);
            cout << "Reading VCF file..." << endl;
            ouf << ll[0];
            for(int i = 1; i<9;++i){
                ouf << "\t" << ll[i] ;
            }
            for(int i = 0; i < np.size();++i){
                ouf << "\t" << ll[np[i]];
            }
            ouf << "\n";
            continue;
        }
        
        if(sites.count(ll[0]+"_"+ll[1])==1){
            ouf << ll[0];
            for(int i = 1; i<9;++i){
                ouf << "\t" << ll[i] ;
            }
            for(int i = 0; i < np.size();++i){
                ouf << "\t" << ll[np[i]];
            }
            ouf << "\n";
        }
        
    }
    inf.close();
    inf2.close();
    ouf.close();
    
    return 0;
}
int getUnIntersectBed(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2); //bed file
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    set<string> sites;
    vector<string> ll;
    vector<int> np;
    
    cout << "Reading sites..." << endl;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        if(line.substr(0,1)=="#") continue;
        ll.clear();
        split(line,ll,"\t");
        for (int i = string2Int(ll[1]); i < string2Int(ll[2]); ++i){
            sites.insert(ll[0]+"_"+Int2String(i));
        }
    }
    cout << "Total sites is:\t" << sites.size() << endl;
    
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line.substr(0,2) == "##") {
            ouf << line << "\n";
            continue;
        };
        ll.clear();
        split(line,ll,"\t");
        if(line[0] == '#' && line[1] == 'C'){
            cout << "Reading VCF file..." << endl;
            ouf << line;
            ouf << "\n";
            continue;
        }
        if(sites.count(ll[0]+"_"+ll[1]) == 0 ){
            ouf << line << "\n";
        }
    }
    inf.close();
    inf2.close();
    ouf.close();
    
    return 0;
}
int siteOverlap(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    set<string> sites;
    vector<string> ll;
    cout << "Reading sites..." << endl;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        if(line.substr(0,1)=="#") continue;
        ll.clear();
        split(line,ll,"\t");
        sites.insert(ll[0]+"_"+ll[1]);
    }
    cout << "Total sites is:\t" << sites.size() << endl;
    
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line.substr(0,1) == "#") {
            ouf << line << "\n";
            continue;
        };
        ll.clear();
        split(line,ll,"\t");
        if(sites.count(ll[0]+"_"+ll[1])==1){
            ouf << line << "\n";
        }
    }
    
    ouf.close();
    return 0;
}
int getUnIntersectVcf(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    set<string> sites;
    vector<string> ll;
    cout << "Reading sites..." << endl;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        if(line.substr(0,1)=="#") continue;
        ll.clear();
        split(line,ll,"\t");
        sites.insert(ll[0]+"_"+ll[1]);
    }
    cout << "Total sites is:\t" << sites.size() << endl;
    
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line.substr(0,1) == "#") {
            ouf << line << "\n";
            continue;
        };
        ll.clear();
        split(line,ll,"\t");
        if(sites.count(ll[0]+"_"+ll[1])==0){
            ouf << line << "\n";
        }
    }
    inf.close();
    inf2.close();
    ouf.close();
    
    return 0;
}

int concatVCFsite(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    set<string> sites;
    vector<string> ll;
    cout << "Reading sites..." << endl;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length()<1) continue;
        if(line.substr(0,2) == "##"){
            ouf << line << "\n";
            continue;
        }
        ll.clear();
        split(line,ll,"\t");
        if(line.substr(0,2) == "#C"){
            for(int i = 0; i < 9; i++){
                ouf << ll[i] << "\t";
            }
            ouf << ll[9] << "\n";
            continue;
        }
        sites.insert(ll[0]+"_"+ll[1]);
        for(int i = 0; i < 9; i++){
            ouf << ll[i] << "\t";
        }
        ouf << ll[9] << "\n";
    }
    cout << "Total sites is:\t" << sites.size() << endl;
    
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line.substr(0,1) == "#") {
//            ouf << line << "\n";
            continue;
        };
        ll.clear();
        split(line,ll,"\t");
        if(sites.count(ll[0]+"_"+ll[1])==0){
            for(int i = 0; i < 9; i++){
                ouf << ll[i] << "\t";
            }
            ouf << ll[9] << "\n";
        }
    }
    inf.close();
    inf2.close();
    ouf.close();
    
    return 0;
}
int keep(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> subPop);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    vector<string> ll2;
    
    cout << "Reading subfiles..." << endl;
    vector<string> ID;
    vector<int> order;
   
    cout << "ID number is:\t" << ID.size() << endl;
    
    while(!inf.eof()){
        getline(inf,line);
        if(line.length()<1) continue;
        if(line.substr(0,2) == "##") {
            ouf << line << "\n";
            continue;
        };
        ll.clear();
        split(line,ll,"\t");
        if (line.substr(0,2) == "#C"){
            for(int i = 0; i<ll.size();i++){
                ID.push_back(ll[i]);
            }
            while(!inf2.eof()){
                getline(inf2,line);
                if(line.length()<1) continue;
                ll2.clear();
                split(line,ll2," \t");
                for(int i = 0; i < ID.size(); i++){
                    if(ll[i] == ll2[0]) order.push_back(i);
                }
            }
            cout << order.size() << " samples found, the order is:\t";
            for (int i = 0; i<order.size(); i++){
                cout << order[i] << "; ";
            }
            cout << endl;
        }
        ouf << ll[0];
        for(int i = 1; i < 9; i++){
            ouf << "\t" << ll[i];
        }
        for (int i = 0; i < order.size(); i++){
            ouf << "\t" << ll[order[i]];
        }
        ouf << "\n";
    }
    ouf.close();
    
    return 0;
}

int getDistanceAll(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outFile = (para -> outFile);
    
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    map<string,double> geneticDistance;
//    map<string,double> geoDistance;
    vector<string> ll;
    getline(inf,line);
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        geneticDistance.insert(pair<string,double>(ll[0]+"_"+ll[1],string2Double(ll[4])));
    }
    cout << "Genetic distance readed! " << geneticDistance.size() << " pairs found!" << endl;
    ouf << "ID1\tID2\tGeneticDistance\tGeoDistance\n";
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        if(geneticDistance.count(ll[0]+"_"+ll[1])==1){
            ouf << ll[0] << "\t" << ll[1] << "\t" << geneticDistance[ll[0]+"_"+ll[1]] << "\t" << ll[2] << "\n";
        }else if (geneticDistance.count(ll[1]+"_"+ll[0])==1){
            ouf << ll[0] << "\t" << ll[1] << "\t" << geneticDistance[ll[1]+"_"+ll[0]] << "\t" << ll[2] << "\n";
        }
    }
    inf.close();
    inf2.close();
    ouf.close();
    return 0;
}
int checkFile(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outFile = (para -> outFile);
//    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    set<string> samples;
    vector<string> a;
    list_dir(infile, a);
    for(int i = 0; i < a.size(); ++i ){
        line = a[i];
        ll.clear();
        split(line,ll,".");
        samples.insert(ll[0]);
    }
    cout << samples.size() << " samples added" << "n";
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        if(samples.count(line)==0){
            ouf << line << ".sra" << "\n";
        }
    }
    return 0;
}
int getOrtholog(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    set<string> genes;
    bool splitoff = para->recode;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll," \t");
        genes.insert(ll[0]+"|"+ll[1]);
    }
    cout << "gene list readed!" << endl;
    map<string,map<string,string>> orth;
    map<string,double> orthvalue;
    map<string, string> IDP;
    
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        if(ll[2] == ll[3] ) continue;
        string ID1 = ll[0];
        string ID2 = ll[1];
        double iv = string2Double(ll[6]);
        double sv = string2Double(ll[7]);
        double value = sv + iv;
        string taxon1 = ll[2];
        string taxon2 = ll[3];
        ll.clear();
        if(!splitoff){
            split(ID1,ll,"._");
            ID1 = ll[0];
            ll.clear();
            split(ID2,ll,"._");
            ID2 = ll[0];
        }
        if(ID1 == ID2 ) continue;
        if(iv < 50 && sv < 50 ) continue;
        if(value < 120) continue;
        if(genes.count(ID1) == 0 && genes.count(ID2) == 0) continue;
        if(ID1 > ID2){
            string tmp;
            tmp = ID1;
            ID1 = ID2;
            ID2 = tmp;
            tmp = taxon1;
            taxon1 = taxon2;
            taxon2 = tmp;
        }
        string key = ID1+"_"+ taxon2;
        if(orthvalue.count(key) == 1){
            if(orthvalue[key] < value){
                orthvalue[key] = value;
                IDP[key] = ID2;
            }else{
                continue;
            }
        }else{
            orthvalue.insert(pair<string,double>(key,value));
            IDP.insert(pair<string,string>(key,ID2));
        }
//        map<string, string> blast;
//        if(genes.count(ID1) == 1 || genes.count(ID2) == 1){
//            if(orth.count(ID1) == 1){
//                blast = orth[ID1];
//                if(blast.count(taxon2) == 0){
//                    blast.insert(pair<string,string>(taxon2,ID2));
//                    orth[ID1] = blast;
//                }else{
//                    blast[taxon2] = ID2;
//                    orth[ID1] = blast;
//                }
//            }else{
//                blast.insert(pair<string,string>(taxon2,ID2));
//                orth.insert(pair<string,map<string,string>>(ID1,blast));
//            }
//        }
    }
    cout << "similarity file parsed! " << IDP.size() << " pairs found!" << endl;
//    set<string>::iterator it;
    map<string,string>::iterator it;
    map<string,set<string>> orthg;
    for(it = IDP.begin(); it!=IDP.end();it++){
        string key = it->first;
        string value = it-> second;
        ll.clear();
        split(key,ll,"_");
        if(orthg.count(ll[0])==1){
            set<string> g;
            g = orthg[ll[0]];
            g.insert(value);
            orthg[ll[0]] = g;
        }else{
            set<string> g;
            g.insert(value);
            orthg.insert(pair<string,set<string>>(ll[0],g));
        }
    }
    cout << orthg.size() << " ortholog pairs parsed!" << endl;
    map<string,set<string>>::iterator itt;
    for(itt = orthg.begin(); itt != orthg.end(); ++itt){
        string key = itt->first;
        set<string> value = itt->second;
        ouf << key;
        for(string f:value){
            ouf << "\t" << f;
        }
        ouf << "\n";
    }
    
    ouf.close();
//    for(it = genes.begin(); it != genes.end(); it++){
//        if(orth.count(*it) == 1){
//            ouf << *it ;
//            map<string, string> blast = orth[*it];
//            map<string,string>::iterator itm;
//            for(itm = blast.begin(); itm != blast.end(); itm++){
//                ouf << "\t" << itm->second;
//            }
//            ouf << "\n";
//        }
//    }
   
    return 0;
}
int getSummary(parameter *para){
    string infile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    double** Matrix = dmatrix(-1, 500, -1, 10);
    for(int i = 0; i < 500; ++i){
        for (int j = 0; j < 10; ++j){
            Matrix[i][j] = 0;
        }
    }
    ouf << "ID\tsum\thet\tAlt_hom\tmissing\n";
    vector<string> IDs;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0]=='#' && line[1]=='#') continue;
        ll.clear();
        split(line,ll,"\t");
        if(line[0] == '#' && line[1] == 'C'){
            for(int i = 9; i < ll.size(); ++i){
                IDs.push_back(ll[i]);
            }
            continue;
        }
        for(int i = 9; i < ll.size(); ++i){
            if(ll[i][2] == '1'){
                if(ll[i][0]=='0'){ // het = 1
                    Matrix[i-9][1]++;
                }else{
                    Matrix[i-9][2]++; // Alt_hom = 2
                }
            }else if(ll[i][2] == '.'){
                Matrix[i-9][3]++; // missing =3
            }
            Matrix[i-9][0]++; // sum = 0
        }
    }
    for(int i =0; i < IDs.size();++i){
        ouf << IDs[i] << "\t" << Matrix[i][0] << "\t" << Matrix[i][1]
        << "\t" << Matrix[i][2] << "\t" << Matrix[i][3] << "\n";
    }
    ouf.close();
    return 0;
}
int riceHapToVCF(parameter *para){
    string infile = (para -> inFile);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        if(ll[0] == "Chromosome"){
            ouf << "##fileformat=VCFv4.1" << "\n";
            ouf << "#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\tFORMAT";
            for (int i = 8; i < ll.size(); ++i){
                ouf << "\t" << ll[i];
            }
            ouf << "\n";
        }else{
            if(string2Double(ll[4]) < 660) continue;
            if(string2Double(ll[5]) < 0.01) continue;
            ouf << ll[0] << "\t" << ll[1] <<"\t"<< "." << "\t" << ll[2] << "\t" << ll[3];
            ouf << "\t" << "." << "\t"<< "."<< "\t"<< "."<< "\t"<< ".";
            for (int i = 8; i < ll.size(); ++i){
                if(ll[i] == ll[2]){
                    ouf << "\t" << "0/0";
                }else if(ll[i] == ll[3]){
                    ouf << "\t" << "1/1";
                }else if(ll[i] == "-"){
                    ouf << "\t" << "./.";
                }else{
                    ouf << "\t" << "0/1";
                }
            }
            ouf << "\n";
        }
    }
    inf.close();
    ouf.close();
    return 0;
}

int ABBAstat(parameter *para){
    string infile = (para -> inFile);
    string group1 = (para -> inFile2);
    string group2 = (para -> inFile3);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inP1 ((group1).c_str(),ifstream::in);
    igzstream inP2 ((group2).c_str(),ifstream::in);
    
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    set<string> g1;
    set<string> g2;
    while(!inP1.eof()){
        getline(inP1,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        g1.insert(ll[0]);
    }
    cout << "group1 readed! size is:\t" << g1.size() << endl;
    while(!inP2.eof()){
        getline(inP2,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        g2.insert(ll[0]);
    }
    cout << "group2 readed! size is:\t" << g2.size() << endl;
    vector<int> p1;
    vector<int> p2;
    srand((int)time(NULL));
    while(!inf.eof()){
        double A1 = 0, B1 = 0, A2 = 0, B2 = 0;
        getline(inf,line);
        if(line.length() < 1) continue;
        
        ll.clear();
        split(line,ll,"\t");
        if(line[0] == '#'){
            for(int i = 0; i < ll.size(); ++i){
                if(g1.count(ll[i])==1){
                    p1.push_back(i);
                }else if (g2.count(ll[i]) == 1){
                    p2.push_back(i);
                }else{
                    continue;
                }
            }
            cout << p1.size() << "\tsamples in group1 found!" << endl;
            cout << p2.size() << "\tsamples in group2 found!" << endl;
        }else{
            char A = ll[ll.size()-1][0];
            for ( int i = 0; i < p1.size(); ++i){
                if(ll[p1[i]][0] == A ){
                    A1++;
                }else{
                    B1++;
                }
            }
            for ( int i = 0; i < p2.size(); ++i){
                if(ll[p2[i]][0] == A ){
                    A2++;
                }else{
                    B2++;
                }
            }
            double p = (A1 * B2 - B1 * A2)/((A1+B1)*(A2+B2));
            ouf << ll[0] << "\t" << ll[1] << "\t" << p << "\n";
        }
    }
    inf.close();
//    while(!inf.eof()){
//        getline(inf,line);
//        if(line.length() < 1) continue;
//        ll.clear();
//        split(line, ll, "\t");
//        if(line[0] == '#'){
//            for(int i = 0; i < ll.size(); ++i){
//                if(g1.count(ll[0])==1){
//                    p1.push_back(i);
//                }else if (g2.count(ll[0]) == 1){
//                    p2.push_back(i);
//                }else{
//                    continue;
//                }
//            }
//            ouf << ll[0] << "\t" << ll[1];
//            for (int i = 0; i < g1.size(); ++i){
//                ouf << "\t" << ll[p1[i]];
//            }
//            for (int i = 0; i < g2.size(); ++i){
//                ouf << "\t" << ll[p2[i]];
//            }
//
//        }else{
//            char A = ll[ll.size()-1][0];
//            char B = A;
//            for(int i = 2; i < ll.size(); ++i){
//                if(ll[i][0] != A) {
//                    B= ll[i][0];
//                    continue;
//                }
//            }
//            int r = rand()*100;
//            if (r < 50){
//                ouf << "\t" << A << "/" << A ;
//            }else{
//                ouf << "\t" << B << "/" << B;
//            }
//        }
//    }
    
    ouf.close();
    return 0;
}
int ABBAsim(parameter *para){
    string infile = (para -> inFile);
    string group1 = (para -> inFile2);
    string group2 = (para -> inFile3);
    string outFile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inP1 ((group1).c_str(),ifstream::in);
    igzstream inP2 ((group2).c_str(),ifstream::in);
    
    ofstream ouf ((outFile).c_str());
    string line;
    vector<string> ll;
    set<string> g1;
    set<string> g2;
    
    while(!inP1.eof()){
        getline(inP1,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        g1.insert(ll[0]);
    }
    cout << "group1 readed! size is:\t" << g1.size() << endl;
    while(!inP2.eof()){
        getline(inP2,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        g2.insert(ll[0]);
    }
    cout << "group2 readed! size is:\t" << g2.size() << endl;
    vector<int> p1;
    vector<int> p2;
    srand((int)time(NULL));
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line, ll, "\t");
        if(line[0] == '#'){
            for(int i = 0; i < ll.size(); ++i){
                if(g1.count(ll[i]) == 1){
                    p1.push_back(i);
                }else if (g2.count(ll[i]) == 1){
                    p2.push_back(i);
                }else{
                    continue;
                }
            }
            cout << "Header readed!" << endl;
            ouf << ll[0] << "\t" << ll[1];
            for (int i = 0; i < g1.size(); ++i){
//                cout << p1[i] << endl;
                ouf << "\t" << ll[p1[i]];
                
            }
            for (int i = 0; i < g2.size(); ++i){
                ouf << "\t" << ll[p2[i]];
            }
            for (int i = 0;i < 10; ++i){
                ouf << "\t" << "Sim1" << i ;
            }
            ouf << "\t" << ll[ll.size()-2];
            ouf << "\t" << ll[ll.size()-1];
            ouf << "\n";
        }else{
            char A = ll[ll.size()-1][0];
            char B = A;
            for(int i = 2; i < ll.size(); ++i){
                if(ll[i][0] != A & ll[i][0] != 'N') {
                    B= ll[i][0];
                    break;
                }
            }
            ouf << ll[0] << "\t" << ll[1];
            for (int i = 0; i < g1.size(); ++i){
                ouf << "\t" << ll[p1[i]];
                
            }
            for (int i = 0; i < g2.size(); ++i){
                ouf << "\t" << ll[p2[i]];
            }
            for(int i = 0; i < 10; ++i){
                int r = rand()*100;
                if (r < 15){
                    ouf << "\t" << B << "/" << B ;
                }else{
                    ouf << "\t" << B << "/" << B;
                }
            }
            ouf << "\t" << ll[ll.size()-2];
            ouf << "\t" << ll[ll.size()-1];
            ouf << "\n";
        }
    }
    
    ouf.close();
    return 0;
}
int SRA1 (parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    vector<string> ll;
    map<string,string> filePos;
    int num = 0;
    string subgenome = (para -> chr);
    while (!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        split(line,ll," \t");
        if (ll[0] == "Taxa") continue;
        if (!find(ll[3],subgenome)) continue;
        num++;
        filePos.insert(pair<string, string>(ll[0],ll[2]));
        ouf << "intersectBed\t-abam\t" << ll[2] << "\t" << "-b\t" << infile2 << "\t>\t" << ll[0] +"." + subgenome + ".bam & \n";
        if (num % 50 == 0 ){
            ouf << "sleep 1200s\n";
        }
    }
    ouf.close();
    
    return 0;
}
int SRA2 (parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    vector<string> ll;
    map<string,string> filePos;
    int num = 0;
    string subgenome = (para -> chr);
    while (!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        split(line,ll," \t");
        if (ll[0] == "Taxa") continue;
        if (!find(ll[3],subgenome)) continue;
        num++;
        filePos.insert(pair<string, string>(ll[0],ll[2]));
        ouf << "samtools view -f 4 " << ll[2] << " > " << ll[0] +"." + subgenome + ".unmapped.bam & \n";
        if (num % 50 == 0 ){
            ouf << "sleep 1200s\n";
        }
    }
    ouf.close();
    
    return 0;
}
int SRA3 (parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    vector<string> ll;
    map<string,string> filePos;
    int num = 0;
    string subgenome = (para -> chr);
    while (!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        split(line,ll,"/");
        num++;
        filePos.insert(pair<string, string>(ll[0],ll[2]));
        ouf << "bamToFastq -i " << line << " -fq " << ll[2] << ".fq &\n";
        if (num % 50 == 0 ){
            ouf << "sleep 60s\n";
        }
    }
    ouf.close();
    
    return 0;
}

int SRA4 (parameter *para){
    string infile = (para -> inFile); // group file
    string infile2 = (para -> inFile2); // taxa file
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    vector<string> ll;
    map<string,string> filePos;
    string subgenome = (para -> chr);
    map<string,string> ID_group;
    while (!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        ll.clear();
        split(line,ll," \t");
        ID_group.insert(pair<string,string>(ll[0],ll[1]));
    }
    map<string,vector<string>> Group_ID;
    while(!inf2.eof()){
        getline(inf2,line);
        if (line.length() < 1) continue;
        ll.clear();
        split(line,ll," \t");
        if(!find(ll[3],subgenome)) continue;
        string g = ID_group[ll[0]];
        if(Group_ID.count(g) == 0){
            vector<string> a;
            a.push_back(ll[0]);
            Group_ID.insert(pair<string,vector<string>>(g,a));
        }else{
            vector<string> a = Group_ID[g];
            a.push_back(ll[0]);
            Group_ID[g] = a;
        }
    }
    map<string,vector<string>>::iterator it;
    for (it = Group_ID.begin(); it != Group_ID.end(); it++ ){
        vector<string> a = (it -> second);
        
        string g = (it -> first);
        ouf << "cat ";
        for (int i = 0; i < a.size(); ++i ){
            ouf << a[i] << "." << subgenome << ".bam.fq ";
        }
        ouf << "> " << g <<  "." << subgenome << ".fq & \n";
    }
    ouf.close();
    return 0;
}

int SRA5 (parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    vector<string> ll;
    map<string,string> filePos;
    string subgenome = (para -> chr);
    while (!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        ll.clear();
        split(line,ll,"/");
        string l1 = ll[ll.size()-1];
        ll.clear();
        split(l1,ll,".");
        
        ouf << "SRAssembler -t dna -T /dev/shm -1 " << line << " -r pre_" << ll[0] << "_" << subgenome
        <<" -P -o " << ll[0] << "_" << subgenome << " &\n";
        
    }
    ouf.close();
    return 0;
}

int SRA6 (parameter *para){
    string infile = (para -> inFile); // bed file
    string infile2 = (para -> inFile2); // bam file
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    vector<string> ll;
    map<string,string> filePos;
    string subgenome = (para -> chr);
    int num = 0;
    while (!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        ll.clear();
        split(line,ll,"_");
        string t = ll[ll.size()-1];
        ll.clear();
        split(t,ll,".");
        string geneID = ll[0];
        
        igzstream inf2 ((infile2).c_str(),ifstream::in);
        
        string inf2name;
        while(!inf2.eof()){
            getline(inf2, inf2name);
            if(inf2name.length() < 1) continue;
            ll.clear();
            split(inf2name,ll,".");
            t = ll[0];
            ll.clear();
            split(t,ll,"/");
            string ID = ll[ll.size()-1];
            num++;
            if (num % 50 == 0){
                ouf << "intersectBed -abam " << inf2name << " -b " << line << " > " << ID << "_" << geneID << ".bam \n"  ;
                ouf << "sleep 2s" << endl;
            }else{
                ouf << "intersectBed -abam " << inf2name << " -b " << line << " > " << ID << "_" << geneID << ".bam &\n"  ;
            }
        }
    }
    ouf.close();
    return 0;
}
int SRA7 (parameter *para){
    string infile = (para -> inFile); // group file
    string infile2 = (para -> inFile2); // taxa file
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    vector<string> ll;
    map<string,string> filePos;
    string subgenome = (para -> chr);
    map<string,string> ID_group;
    while (!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        ll.clear();
        split(line,ll," \t");
        ID_group.insert(pair<string,string>(ll[0],ll[1]));
    }
    map<string,vector<string>> Group_ID;
    while(!inf2.eof()){
        getline(inf2,line);
        if (line.length() < 1) continue;
        ll.clear();
        split(line,ll," \t");
        if(!find(ll[3],subgenome)) continue;
        string g = ID_group[ll[0]];
        if(Group_ID.count(g) == 0){
            vector<string> a;
            a.push_back(ll[0]);
            Group_ID.insert(pair<string,vector<string>>(g,a));
        }else{
            vector<string> a = Group_ID[g];
            a.push_back(ll[0]);
            Group_ID[g] = a;
        }
    }
    map<string,vector<string>>::iterator it;
    for (it = Group_ID.begin(); it != Group_ID.end(); it++ ){
        vector<string> a = (it -> second);
        string g = (it -> first);
        ouf << "samtools merge ";
        ouf << g <<  "." << subgenome << ".bam ";
        for (int i = 0; i < a.size(); ++i ){
            ouf << a[i] << "." << subgenome << ".bam ";
        }
        ouf << " &\n";
    }
    ouf.close();
    return 0;
}
int SRA8 (parameter *para){
    string infile = (para -> inFile); // group file
    string infile2 = (para -> inFile2); // bed file
    string outfile = (para -> outFile);
    
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    vector<string> ll;
    map<string,string> filePos;
    string subgenome = (para -> chr);
    map<string,string> ID_group;
    int num = 0;
    while (!inf2.eof()){
        getline(inf2,line);
        if (line.length() < 1) continue;
        ll.clear();
        split(line,ll," \t");
        string geneID = ll[3];
        igzstream inf ((infile).c_str(),ifstream::in);
        while(!inf.eof()){
            getline(inf,line);
            if(line.length() < 1 ) continue;
            num++;
            if (num % 50 == 0){
                ouf << "bamToFastq -i " << line << "_" << geneID << ".bam" <<  " -fq " << line << "_" << geneID << ".fq \n";
            }else{
                ouf << "bamToFastq -i " << line << "_" << geneID << ".bam" <<  " -fq " << line << "_" << geneID << ".fq &\n";
            }
        }
        inf.close();
    }
    ouf.close();
    return 0;
}

int SRA9 (parameter *para){
    string infile = (para -> inFile); // fastq folder
    string infile2 = (para -> inFile2); // gene folder
    string infile3 = (para -> inFile3); // group file
    string infile4 = (para -> subPop); // gene ID
    string outfile = (para -> outFile);
    string subfold = (para -> chr);
    igzstream inf2 ((infile4).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string geneID;
    cout << "subfolder is: " << subfold << endl;
    while (!inf2.eof()){
        getline(inf2,geneID);
        if (geneID.length() < 1) continue;
        string group;
        igzstream inf ((infile3).c_str(),ifstream::in);
        while(!inf.eof()){
            getline(inf,group);
            if (group.length() < 1) continue;
            ouf << "SRAssembler -q " << infile2 << "/" << geneID << ".fasta" << " -t dna -p SRAssembler.conf -1 " << infile << "/" << group << "_" << geneID << ".fq"  << "  -r pre_" << group <<"_" << geneID <<  " -o " << "./" << subfold << "/" << group <<"_" << geneID << "\n";
            ouf << "blastn -query " << subfold << "/" <<  group <<"_" << geneID << "/all_contigs.fasta " << "-db " << infile2 << "/" << geneID << " -out " << "./" << subfold << "/" << group <<"_" << geneID << "/" << "blast.out \n";
            ouf << "mkdir -p " << "./" << subfold << "/" <<  geneID << "\n";
            ouf << " WGS --model file --type blast2maf --file " << "./" << subfold << "/"<<  group <<"_" << geneID << "/" << "blast.out --file2 " << infile2 << "/" << geneID << ".fasta" << " --flag " << group << " --out " << "./" << subfold << "/" << geneID << "/" << group << "\n" ;
        }
        inf.close();
    }
    ouf.close();
    return 0;
}

int SRA10 (parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    vector<string> ll;
    int num = 0;
    while (!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        if(line[0] == '>'){
            ll.clear();
            split(line,ll," \t");
            num++;
            if(num % 50 == 0 ){
                ouf << "makeblastdb -in " << ll[ll.size()-1] << ".fasta -title " << ll[ll.size()-1] <<" -out " << ll[ll.size()-1] <<" -dbtype nucl \n";
            }else{
                ouf << "makeblastdb -in " << ll[ll.size()-1] << ".fasta -title " << ll[ll.size()-1] <<" -out " << ll[ll.size()-1] <<" -dbtype nucl &\n";
            }
        }
    }
    ouf.close();
    return 0;
}

int SRA11 (parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    int num = 0;
    while (!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        num++;
        ouf << "echo " << line << "\n";
        ouf << "samtools index " << line << "\n";
        
    }
    ouf.close();
    return 0;
}


int SRA12 (parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    int num = 0;
    set<string> sample;
    while(!inf2.eof()){
        getline(inf2,line);
        sample.insert(line);
    }
    vector<string> ll;
    while (!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        ll.clear();
        split(line,ll," \t");
        if(sample.count(ll[6])!=0){
            ouf << line << "\n";
        }
        
    }
    ouf.close();
    return 0;
}

int SRA13 (parameter *para){
    string infile = (para -> inFile); // group file
    string infile2 = (para -> inFile2); //  bed file
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    string subgenome = (para -> chr);
    ofstream ouf ((outfile + "/" + subgenome + ".sh").c_str());
    string line;
    vector<string> ll;
   
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        split(line,ll,".");
        ouf << "python /data1/home/xuebo/SRAssembler/code/bam_bed.py -a ../" << line << " -e " << infile2 << " -o " << ll[0] << "_"  << " &\n";
    }
    ouf.close();
    return 0;
}

int SRA14 (parameter *para){
    string infile = (para -> inFile); // path for fastq file
    string infile2 = (para -> inFile2); // path for gene
    string subPop = (para -> subPop); // taxa file for group
    string bedFile = (para -> bedFile); // gene file for gene
    string outfile = (para -> outFile);
    igzstream inf ((subPop).c_str(),ifstream::in);
    
    
    string line;
    vector<string> ll;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        string taxa = line;
        ofstream ouf ((outfile + taxa + "_assembly.sh").c_str());
        igzstream inf2 ((bedFile).c_str(),ifstream::in);
        while(!inf2.eof()){
            getline(inf2,line);
            if(line.length() < 1 ) continue;
            string gene = line;
            ouf << "SRAssembler -q " << infile << "/" << gene << ".fasta" << "  -t dna -p parameter.conf -1 " << infile2 << "/" << taxa << "_" << gene << ".fastq -r pre_" << taxa << "_" << gene << " -o " << taxa << "_" << gene << "\n";
            ouf << "blastn -query " << taxa << "_" << gene << "/all_contigs.fasta -db " << infile << "/" << gene << " -out " << taxa << "_" << gene << "/blast.out \n";
            ouf << "mkdir -p " << gene << "\n";
            ouf << "WGS --model file --type blast2maf --file " << taxa << "_" << gene << "/blast.out --file2 " << infile << "/" << gene << ".fasta --flag " << taxa << " --out " << gene << "/" << taxa << "\n";
            ouf << "rm -rf pre_" << taxa << "_" << gene << "\n";
            ouf << "rm -rf " << taxa << "_" << gene << "\n";
        }
        inf2.close();
        ouf.close();
    }
    
    return 0;
}

int bed2single (parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    
    string line;
    vector<string> ll;
    map<string,string> filePos;
    string subgenome = (para -> chr);
    while (!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        ll.clear();
        split(line,ll," \t");
        ofstream ouf ((outfile + ll[3] +".bed").c_str());
        ouf << line << "\n";
        ouf.close();
    }
    return 0;
}
int gene2Single (parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    string line;
    vector<string> ll;
    string seq="";
    bool first = true;
    string ID;
    while (!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        if(line[0] == '>'){
            ll.clear();
            split(line,ll," \t");
            if (!first){
                ofstream ouf ((outfile +"/"+ ID +".fasta").c_str());
                ouf << ">" << ID << "\n";
                ouf << seq ;
                ouf.close();
                seq = "";
            }else{
                first = false;
            }
            ID = ll[ll.size()-1];
        }else{
            seq.append(line+"\n");
        }
    }
    ofstream ouf ((outfile +"/"+ ID +".fasta").c_str());
    ouf << ">" << ID << "\n";
    ouf << seq ;
    ouf.close();
    return 0;
}
int toPEfastq (parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf1 ((outfile +".R1.fq").c_str());
    ofstream ouf2 ((outfile +".R2.fq").c_str());
    string line;
    vector<string> ll;
    string seq = "";
    string line1 = "@EAS139:136:FC706VJ:2:2104:";
    string line3 = "+";
    string line4 = string(150, '|');
    int x = 1, y = 1;
    while (!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        if(line[0] == '>'){
            if(seq == "") continue;
            split(seq, ll,"N");
            for (int i = 0 ; i < ll.size(); ++i){
                if(ll[i].length() < 300) continue;
                string lseq = ll[i];
//                string rseq = reverse_complementary(ll[i]);
                for(int j = 0 ; j < lseq.length() - 150 ; j = j + 15){
                    if((j+150) > lseq.length()) continue;
                    x++;
                    y++;
                    string a = lseq.substr(j+150,150);
                    string b = reverse_complementary(a);
                    if (b.length()!=150) continue;
                    ouf1 << line1 <<  x <<  ":" <<  y <<  " 1:Y:18:ATCACG" << "\n";
                    ouf2 << line1 <<  x <<  ":" <<  y <<  " 1:Y:18:ATCACG" << "\n";
                    ouf1 << lseq.substr(j,150) << "\n";
                    ouf2 <<  b << "\n";
                    ouf1 << line3 << "\n";
                    ouf2 << line3 << "\n";
                    ouf1 << line4 << "\n";
                    ouf2 << line4 << "\n";
                }
            }
            seq = "";
        }else{
            seq.append(line);
        }
    }
    if (seq != ""){
        split(seq, ll,"N");
        for (int i = 0 ; i < ll.size(); ++i){
            if(ll[i].length() < 300) continue;
            string lseq = ll[i];
            for(int j = 0 ; j < lseq.length() - 150 ; j = j + 30){
                if((j+301) > lseq.length()) continue;
                x++;
                y++;
                string a = lseq.substr(j+150,150);
                string b = reverse_complementary(a);
                if (b.length()!=150) continue;
                ouf1 << line1 <<  x <<  ":" <<  y <<  " 1:Y:18:ATCACG" << "\n";
                ouf2 << line1 <<  x <<  ":" <<  y <<  " 1:Y:18:ATCACG" << "\n";
                ouf1 << lseq.substr(j,150) << "\n";
                ouf2 << b << "\n";
                ouf1 << line3 << "\n";
                ouf2 << line3 << "\n";
                ouf1 << line4 << "\n";
                ouf2 << line4 << "\n";
            }
        }
    }
    
    ouf1.close();
    ouf2.close();
    return 0;
}
int D2B(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    vector<string> ll;
    string chr="";
    int start = 0;
    int end = 0;
    bool s = false;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        if(chr != ll[0]){
            if((end - start) > 100){
                ouf << chr <<"\t" << start << "\t" << end << "\n";
            }
            s = false;
            start = 0;
            chr = ll[0];
            end = 0;
        }
        if(string2Int(ll[2]) == 1 ){
            if(!s) {
                start = string2Int(ll[1]);
                s=true;
            }else{
                end = string2Int(ll[1]);
            }
        }else{
            if((end - start) > 100){
                ouf << chr <<"\t" << start << "\t" << end << "\n";
            }
            s = false;
            end = 0;
            start = 0;
        }
    }
    if((end - start) > 2000){
        ouf << chr <<"\t" << start << "\t" << end << "\n";
    }
    ouf.close();
    return 0;
}
int getConcordance(parameter *para){
    string infile = (para -> inFile); // kmer frequency file
    string infile2 = (para -> inFile2); // concordance file
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    vector<string> ll;
    vector<double> cs(1300000000,0.0);
    string prechr = "";
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        string chr = ll[0].substr(3,2);
        if (chr != prechr) {
            cout << "Proceessing chr" << chr << " for concordance file" <<endl;
            prechr = chr;
        }
        int ch;
        if (chr[0] == 'U'){
            ch = 13;
        }else{
            ch = string2Int(chr);
        }
        int pos = string2Int(ll[1]);
        double value = 0.0;
        if(ll.size() == 10){
            value = string2Double(ll[5]);
        }
        cs[(ch-1)*1000000 + pos] = value;
    }
    vector<double> rate(101,0.0);
    
    prechr = "";
    while(!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        if(ll[2] != "1") continue;
        string chr = ll[0].substr(3,2);
        if (chr != prechr) {
            cout << "Proceessing chr" << chr << " for sites file" <<endl;
            prechr = chr;
        }
        int ch;
        if (chr[0] == 'U'){
            ch = 13;
        }else{
            ch = string2Int(chr);
        }
        int pos = string2Int(ll[1]);
        int a = cs[(ch-1)*1000000 + pos]*100;
        rate[a]++;
    }
    rate[0] = 0;
    for (int i = 0; i < rate.size(); ++i){
        ouf << Double2String(0.01*i) << "\t" << rate[i] << "\n";
    }
    ouf.close();
    return 0;
}
int getConcordance_bed(parameter *para){
    string infile = (para -> inFile); // bed file
    string infile2 = (para -> inFile2); // concordance file
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    vector<string> ll;
    vector<double> cs(1300000000,0.0);
    string prechr = "";
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        string chr = ll[0].substr(3,2);
        if (chr != prechr) {
            cout << "Proceessing chr" << chr << " for concordance file" <<endl;
            prechr = chr;
        }
        int ch;
        if (chr[0] == 'U'){
            ch = 13;
        }else{
            ch = string2Int(chr);
        }
        int pos = string2Int(ll[1]);
        double value = 0.0;
        if(ll.size() > 5){
            value = string2Double(ll[5]);
        }
        cs[(ch-1)*100000000 + pos] = value;
    }
    vector<double> rate(101,0.0);
    prechr = "";
    while(!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        string chr = ll[0].substr(3,2);
        if (chr != prechr) {
            cout << "Proceessing chr" << chr << " for bed file" <<endl;
            prechr = chr;
        }
        int ch;
        if (chr[0] == 'U'){
            ch = 13;
        }else{
            ch = string2Int(chr);
        }
        for (int i = string2Int(ll[1]); i < string2Int(ll[2]); ++i){
            int a = cs[(ch-1)*100000000 + i]*100;
            rate[a]++;
        }
    }
//    rate[0] = 0;
    for (int i = 0; i < rate.size(); ++i){
        ouf << Double2String(0.01*i) << "\t" << rate[i] << "\n";
    }
    ouf.close();
    return 0;
}
int KmerFrequence(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    string seq = "";
    string chr = "";
    unordered_map<uint64_t, int> kf;
    int kmer = (para -> size);
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '>') {
           
            if(seq != ""){
                for (int i = 0; i < seq.length(); ++i){
                    uint64_t key = encode(seq.substr(i,kmer));
//                    cout << key << endl;
                    if (kf.count(key) == 1){
                        int v = kf[key];
                        int nv = v + 1;
                        kf[key] = nv;
                    }else{
                        kf.insert(pair<uint64_t,int>(key,1));
                    }
                }
                cout <<  chr << " finished! Length is: " << seq.length() << endl;
            }
            chr = line.substr(1,line.length()-1) ;
            cout << "Processing " << chr << endl;
            seq = "";
            continue;
        }
        seq.append(line);
    }
    if(seq != ""){
        for (int i = 0; i < seq.length(); ++i){
            uint64_t key = encode(seq.substr(i,kmer));
            if (kf.count(key) == 1){
                int v = kf[key];
                int nv = v + 1;
                kf[key] = nv;
            }else{
                kf.insert(pair<uint64_t,int>(key,1));
            }
        }
        cout <<  chr << " finished! Length is: " << seq.length() << endl;
    }
    cout << "Total k-mer is:\t" << kf.size() << endl;
    inf.close();
    igzstream inf1 ((infile).c_str(),ifstream::in);
    
    seq = "";
    uint64_t s = 0;
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length() < 1) continue;
        if (line[0] == '>'){
            cout << "Counting " << line.substr(1,line.length()-1) << endl;
            if(seq != ""){
                for (int i = 0; i < seq.length(); ++i){
                    uint64_t key = encode(seq.substr(i,kmer));
                    if (key == s){
                        ouf << chr << "\t" << i << "\t" << 0 << "\n";
                    }else{
                        ouf << chr << "\t" << i << "\t" << kf[key] << "\n";
                    }
                }
            }
            chr = line.substr(1,line.length()-1);
            seq = "";
            continue;
        }
        seq.append(line);
    }
    if(seq != ""){
        for (int i = 0; i < seq.length(); ++i){
            uint64_t key = encode(seq.substr(i,kmer));
            if (key == s ){
                ouf << chr << "\t" << i << "\t" << 0 << "\n";
            }else{
                ouf << chr << "\t" << i << "\t" << kf[key] << "\n";
            }
        }
    }
    ouf.close();
    return 0;
}
int FastqKmerFrequence(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile+"1.fq.gz").c_str(),ifstream::in);
    igzstream inf2 ((infile+"2.fq.gz").c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    unordered_map<uint64_t, int> kf;
    int freq = (para->freq);
    int kmer = (para -> size);
    bool next = false;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if (line[0]=='@') {
            next = true;
            continue;
        }
        if (next){
            next = false;
        }else{
            continue;
        }
//        cout << line << endl;
        if(line.length() < kmer + 1) continue;
        if(line.length() > kmer){
            for (int i = 0; i < line.length() - kmer - 1; i = i + kmer){
                uint64_t key = encode(line.substr(i,kmer));
                if (kf.count(key) == 1){
                    int v = kf[key];
                    int nv = v + 1;
                    kf[key] = nv;
                }else{
                    kf.insert(pair<uint64_t,int>(key,1));
                }
            }
        }
        string rl = reverse_complementary(line);
        if(rl != ""){
            for (int i = 0; i < rl.length() - kmer - 1; i=i+kmer){
                uint64_t key = encode(rl.substr(i,kmer));
                if (kf.count(key) == 1){
                    int v = kf[key];
                    int nv = v + 1;
                    kf[key] = nv;
                }else{
                    kf.insert(pair<uint64_t,int>(key,1));
                }
            }
        }
    }
    
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        if (line[0]=='@') {
            next = true;
            continue;
        }
        if (next){
            next = false;
        }else{
            continue;
        }
        if(line.length() < kmer + 1) continue;
        if(line.length() > kmer){
            for (int i = 0; i < line.length() - kmer - 1; i = i + kmer){
                uint64_t key = encode(line.substr(i,kmer));
                if (kf.count(key) == 1){
                    int v = kf[key];
                    int nv = v + 1;
                    kf[key] = nv;
                }else{
                    kf.insert(pair<uint64_t,int>(key,1));
                }
            }
        }
        string rl = reverse_complementary(line);
        if(rl != ""){
            for (int i = 0; i < rl.length() - kmer - 1; i=i+kmer){
                uint64_t key = encode(rl.substr(i,kmer));
                if (kf.count(key) == 1){
                    int v = kf[key];
                    int nv = v + 1;
                    kf[key] = nv;
                }else{
                    kf.insert(pair<uint64_t,int>(key,1));
                }
            }
        }
    }
    cout << "Total k-mer is:\t" << kf.size() << endl;
    unordered_map<uint64_t,int>::iterator iter;
    for(iter = kf.begin(); iter != kf.end(); iter++){
        uint64_t key = iter->first;
        char reads[kmer];
        decode(key,reads,false);
        if (iter->second > freq){
            ouf << reads << "\t" << iter->second << "\n";
        }
    }
    ouf.close();
    return 0;
}

int getReadsID(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in); // rate_summary file
    string line;
    double r = (para ->threshold);
    ofstream ouf ((outfile).c_str());
    vector<string> ll;
    long int pb = 0; // Passed bases;
    int pn = 0; // Passed number
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        split(line,ll," \t");
        double v = string2Double(ll[4]);
        if(v > r){
            ouf << ll[0] << "\n";
            pn++;
            pb += string2Int(ll[1]);
        }
    }
    cout << "Number of passed reads is:\t" << pn << endl;
    cout << "Number of passed bases is:\t" << pb << endl;
    return 0;
}
int splitIntoPool(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in); // rate_summary file
    ifstream inf2 (infile2.c_str()); // pool ID order
    string line;
    unordered_map<int, set<string>> readsToPool;
    vector<string> ll;
    
    
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll," \t");
        vector<double> value;
        for(int i = 1; i < ll.size(); i++){
            value.push_back(string2Double(ll[i]));
        }
        int maxElementIndex = std::max_element(value.begin(),value.end()) - value.begin();
        if(readsToPool.count(maxElementIndex)){
            set<string> v = readsToPool[maxElementIndex];
            v.insert(ll[0]);
            readsToPool[maxElementIndex] = v;
        }else{
            set<string> v;
            v.insert(ll[0]);
            readsToPool.insert(pair<int,set<string>>(maxElementIndex,v));
        }
    }
    cout << "summary data readed!" << endl;
    int cl = 0;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        split(line,ll,".");
        string ID = ll[0];
        set<string> reads = readsToPool[cl];
        ofstream ouf ((outfile + ID + ".pool.txt").c_str());
        set<string>::iterator iter;
        for(iter = reads.begin(); iter != reads.end(); iter++){
            ouf << *iter << "\n";
        }
        cl++;
        ouf.close();
    }
    
    return 0;
}

int FastaKmerFrequence(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    unordered_map<uint64_t, int> kf;
    int kmer = (para -> size);
    bool next = false;
    string seq = "";
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if (line[0]=='>') {
            next = true;
            if (seq.length()  > kmer){
                for (int i = 0; i < seq.length(); i++){
                    uint64_t key = encode(seq.substr(i,kmer));
                    if (kf.count(key) == 1){
                        int v = kf[key];
                        int nv = v + 1;
                        kf[key] = nv;
                    }else{
                        kf.insert(pair<uint64_t,int>(key,1));
                    }
                }
                string rl = reverse_complementary(seq);
                for (int i = 0; i < rl.length(); i++){
                    uint64_t key = encode(rl.substr(i,kmer));
                    if (kf.count(key) == 1){
                        int v = kf[key];
                        int nv = v + 1;
                        kf[key] = nv;
                    }else{
                        kf.insert(pair<uint64_t,int>(key,1));
                    }
                }
            }
            continue;
        }
        if (next){
            next = false;
            seq = line;
        }else{
            seq.append(line);
        }
    }
    if (seq.length() > kmer){
        for (int i = 0; i < seq.length(); i++){
            uint64_t key = encode(seq.substr(i,kmer));
            if (kf.count(key) == 1){
                int v = kf[key];
                int nv = v + 1;
                kf[key] = nv;
            }else{
                kf.insert(pair<uint64_t,int>(key,1));
            }
        }
        string rl = reverse_complementary(seq);
        for (int i = 0; i < rl.length(); i++){
            uint64_t key = encode(rl.substr(i,kmer));
            if (kf.count(key) == 1){
                int v = kf[key];
                int nv = v + 1;
                kf[key] = nv;
            }else{
                kf.insert(pair<uint64_t,int>(key,1));
            }
        }
    }
    
    cout << "Total k-mer is:\t" << kf.size() << endl;
    unordered_map<uint64_t,int>::iterator iter;
    for(iter = kf.begin(); iter != kf.end(); iter++){
        uint64_t key = iter->first;
        char reads[kmer];
        decode(key,reads,false);
        ouf << reads << "\t" << iter->second << "\n";
    
    }
    ouf.close();
    return 0;
}

int FastaKmerScore(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in); // fasta file
    ofstream ouf ((outfile).c_str());
    string line;
    unordered_map<uint64_t, int> kmer;
    string seq = "";
    int kmer_len = (para->size);
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '>'){
            if(seq != ""){
                //To do kmer counting;
                long int seqlength = seq.length();
                if(seqlength < kmer_len + 1) continue;
                for(int i = 0; i < seqlength - kmer_len ; i++){
                    uint64_t key = encode(seq.substr(i,kmer_len));
                    if(key == 0) continue;
                    int v ;
                    if(kmer.count(key)){
                        v = kmer[key];
                        v++;
                        kmer[key] = v;
                    }else{
                        kmer.insert(pair<uint64_t,int>(key,1));
                    }
                }
                string rs = reverse_complementary(seq);
                for(int i = 0; i < seqlength - kmer_len ; i++){
                    uint64_t key = encode(rs.substr(i,kmer_len));
                    if(key == 0) continue;
                    int v ;
                    if(kmer.count(key)){
                        v = kmer[key];
                        v++;
                        kmer[key] = v;
                    }else{
                        kmer.insert(pair<uint64_t,int>(key,1));
                    }
                }
            }
            seq = "";
        }else{
            seq.append(line);
        }
    }
    long int seqlength = seq.length();
    if(seqlength > kmer_len + 1){
        for(int i = 0; i < seqlength - kmer_len ; i++){
            uint64_t key = encode(seq.substr(i,kmer_len));
            if(key == 0) continue;
            int v ;
            if(kmer.count(key)){
                v = kmer[key];
                v++;
                kmer[key] = v;
            }else{
                kmer.insert(pair<uint64_t,int>(key,1));
            }
        }
        string rs = reverse_complementary(seq);
        for(int i = 0; i < seqlength - kmer_len ; i++){
            uint64_t key = encode(rs.substr(i,kmer_len));
            if(key == 0) continue;
            int v ;
            if(kmer.count(key)){
                v = kmer[key];
                v++;
                kmer[key] = v;
            }else{
                kmer.insert(pair<uint64_t,int>(key,1));
            }
        }
    }
    cout << "Kmer counted!" << endl;
    
    inf.close();
    igzstream inf1 ((infile).c_str(),ifstream::in);
    string contig;
    vector<string> ll;
    uint64_t key;
    seq="";
    while(!inf1.eof()){
        getline(inf1,line);
        if(line.length() < 1) continue;
        if(line[0] == '>'){
            if(seq != ""){
                //To do kmer counting;
                long int seqlength = seq.length();
                if(seqlength < kmer_len + 1) continue;
                for(int i = 0; i < seqlength - kmer_len ; i++){
                    key = encode(seq.substr(i,kmer_len));
                    ouf << contig << "\t" << i << "\t" << kmer[key] << "\n";
                }
                for(int i = seqlength - kmer_len; i < seqlength; i++ ){
                    ouf << contig << "\t" << i << "\t" << kmer[key] << "\n";
                }
            }
            seq = "";
            split(line,ll," \t");
            contig = ll[0].substr(1,ll[0].length()-1);
        }else{
            seq.append(line);
        }
    }
    cout << "contig is:\t" << contig << endl;
    if(seq != ""){
        //To do kmer counting;
        long int seqlength = seq.length();
        if(seqlength > kmer_len + 1){
            for(int i = 0; i < seqlength - kmer_len ; i++){
                key = encode(seq.substr(i,kmer_len));
                ouf << contig << "\t" << i << "\t" << kmer[key] << "\n";
            }
            for(int i = seqlength - kmer_len; i < seqlength; i++ ){
                ouf << contig << "\t" << i << "\t" << kmer[key] << "\n";
            }
        }
        
    }
    ouf.close();
    return 0;
}
int singleFastaKmerScore(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in); // fasta file
    ofstream ouf ((outfile).c_str());
    string line;
    string seq = "";
    int kmer_len = (para->size);
    string contigID = "";
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '>'){
            if(seq != ""){
                //To do kmer counting;
                unordered_map<uint64_t, int> kmer;
                long int seqlength = seq.length();
                if(seqlength < kmer_len + 1) continue;
                for(int i = 0; i < seqlength - kmer_len ; i++){
                    uint64_t key = encode(seq.substr(i,kmer_len));
                    if(key == 0) continue;
                    int v ;
                    if(kmer.count(key)){
                        v = kmer[key];
                        v++;
                        kmer[key] = v;
                    }else{
                        kmer.insert(pair<uint64_t,int>(key,1));
                    }
                }
                string rs = reverse_complementary(seq);
                for(int i = 0; i < seqlength - kmer_len ; i++){
                    uint64_t key = encode(rs.substr(i,kmer_len));
                    if(key == 0) continue;
                    int v ;
                    if(kmer.count(key)){
                        v = kmer[key];
                        v++;
                        kmer[key] = v;
                    }else{
                        kmer.insert(pair<uint64_t,int>(key,1));
                    }
                }
               
                long int v;
                for(int i = 0; i < seqlength - kmer_len ; i++){
                    uint64_t key = encode(seq.substr(i,kmer_len));
                    v = kmer[key];
                     ouf << contigID << "\t" << i << "\t" << v << "\n" ;
                }
                for(int i = seqlength - kmer_len;i < seqlength ;i++){
                    ouf << contigID << "\t" << i <<"\t" << v << "\n";
                }
               
            }
            ll.clear();
            split(line,ll," \t");
            contigID = ll[0].substr(1,ll[0].length()-1);
            seq = "";
        }else{
            seq.append(line);
        }
    }
    long int seqlength = seq.length();
    if(seqlength > kmer_len + 1){
        unordered_map<uint64_t, int> kmer;
        for(int i = 0; i < seqlength - kmer_len ; i++){
            uint64_t key = encode(seq.substr(i,kmer_len));
            if(key == 0) continue;
            int v ;
            if(kmer.count(key)){
                v = kmer[key];
                v++;
                kmer[key] = v;
            }else{
                kmer.insert(pair<uint64_t,int>(key,1));
            }
        }
        string rs = reverse_complementary(seq);
        for(int i = 0; i < seqlength - kmer_len ; i++){
            uint64_t key = encode(rs.substr(i,kmer_len));
            if(key == 0) continue;
            int v ;
            if(kmer.count(key)){
                v = kmer[key];
                v++;
                kmer[key] = v;
            }else{
                kmer.insert(pair<uint64_t,int>(key,1));
            }
        }
        
        long int v;
        for(int i = 0; i < seqlength - kmer_len ; i++){
            uint64_t key = encode(seq.substr(i,kmer_len));
            v = kmer[key];
            ouf << contigID << "\t" << i << "\t" << v << "\n" ;
        }
        for(int i = seqlength - kmer_len;i < seqlength ;i++){
            ouf << contigID << "\t" << i << "\t" << v << "\n" ;
        }
        ouf << "\n";
    }
    ouf.close();
    return 0;
}
int ClusterBasedOnKmer(parameter *para){
    string infile = (para -> inFile); //fasta file
    string infile2 = (para -> inFile2);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    vector<string> ll;
    unordered_map<uint64_t, set<string>> matched;
    string contigID = "";
    int kmer_len = (para->size);
    double depth = (para->mean);
    map<string,string> genome;
    string seq = "";
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1 ) continue;
        if(line[0] == '>'){
            if(contigID != ""){
                genome.insert(pair<string,string>(contigID,seq));
            }
            ll.clear();
            split(line,ll," \t");
            contigID = ll[0].substr(1,ll[0].length()-1);
            seq = "";
        }else{
            seq.append(line);
        }
    }
    genome.insert(pair<string,string>(contigID,seq));
    cout << "Genome file readed! Contig number is:\t" << genome.size() << endl;
    while (!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll,"\t");
        long int freq = string2Int(ll[2]);
        if( freq < 1.3 * depth && freq > 0.5*depth  ){
            contigID = ll[0];
            seq = genome[contigID];
            int pos = string2Int(ll[1]);
            if (pos > seq.length()- kmer_len - 1) continue;
            uint64_t key = encode(seq.substr(pos,kmer_len));
//            cout << key << endl;
            set<string> value;
            if (matched.count(key) == 1){
                value = matched[key];
                value.insert(contigID);
                matched[key] = value;
            }else{
                value.insert(contigID);
                matched.insert(pair<uint64_t,set<string>>(key,value));
            }
        }
    }
    cout << "Fasta file readed! Unique K-mer number is:\t" << matched.size() << endl;
    return 0 ;
}
int removeBlackFasta(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in); // fasta file
    ofstream ouf ((outfile).c_str());
    string chr = "";
    string seq = "";
    map<string,string> genome;
    string line;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '>'){
            if( chr != "" && seq != ""){
                ouf << chr << "\n";
                ouf << seq ;
            }
            chr = line;
            seq = "";
        }else{
            seq.append(line);
            seq.append("\n");
        }
    }
    
    if( seq != ""){
        ouf << chr << "\n";
        ouf << seq ;
    }
    
    ouf.close();
    return 0;
}
int kmerFreq(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in); // fasta file
    ofstream ouf ((outfile).c_str());
    string line;
    vector<string> ll;
    vector<int> freq(201,0);
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        split(line,ll,"\t");
        int idx = string2Int(ll[2]);
        if(idx > 200) idx = 200;
        freq[idx]++;
    }
    for(int i = 0; i < freq.size(); i++){
        ouf << i << "\t" << freq[i] << "\n";
    }
    ouf.close();
    return 0;
}
int kmerFoldFreq(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in); // fasta file
    ofstream ouf ((outfile).c_str());
    string line;
    vector<string> ll;
    vector<int> freq(1001,0);
    int fold = (para -> size);
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        split(line,ll,"\t");
        int id1 = string2Int(ll[2]);
        int idx = id1/fold;
        if(idx > 1000) idx = 1000;
        freq[idx]++;
    }
    for(int i = 0; i < freq.size(); i++){
        ouf << i << "\t" << freq[i] << "\n";
    }
    ouf.close();
    return 0;
}
int KmerReadScore(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in); // fasta file
    ofstream ouf ((outfile).c_str());
    string line;
    vector<string> ll;
    vector<int> freq(1001,0);
    long int KS_sum = 0, len = 0;
    string readID="";
    
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        split(line,ll,"\t");
        if(ll[0] == readID){
            KS_sum += string2Int(ll[2]);
            len++;
        }else{
            if(readID !=""){
                ouf << readID << "\t" << len << "\t" << KS_sum <<  "\n";
            }
            readID = ll[0];
            len = 1;
            KS_sum = string2Int(ll[2]);
        }
    }
    ouf << readID << "\t" << len << "\t" << KS_sum <<  "\n";
   
    ouf.close();
    return 0;
}
int changeID(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);// fasta file
    ofstream ouf ((outfile).c_str());
    string line;
    int a=0;
    vector<string> ll;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '>'){
            ouf << ">contig" << a << "\n";
            a++;
        }else{
            split(line,ll,"N");
            if(ll.size()>1){
                for(int i = 0; i<ll.size();i++){
                    ouf << ll[i] << "\n";
                }
            }else{
                 ouf << line << "\n";
            }
           
        }
    }
    ouf.close();
    return 0;
}
int reformatID(parameter *para){
    string infile = (para -> inFile); //fasta file
    string infile2 = (para -> inFile2); //ID file
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);// fasta file
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;
    vector<string> ll;
    map<string,string> IDs;

    while (!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        split(line,ll," \t");
        IDs.insert(pair<string,string>(ll[0],ll[1]));
    }
    
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '>'){
            string id1 = line.substr(1,line.length()-1);
            string id2 = IDs[id1];
            ouf << ">" << id2 << "\n";
        }else{
            ouf << line << "\n";
        }
    }
    ouf.close();
    
    return 0;
}

int renameID(parameter *para){
    string infile = (para -> inFile); //fasta file
    string infile2 = (para -> inFile2); //ID file
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);// fasta file
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string line;

    vector<string> ll;
    vector<string> strand;
    map<string,string> genome;
    string contigID = "";
    string chrID;
    string seq;
    string gap(100,'N');
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '>'){
            if(contigID != ""){
//                cout << contigID << "\t" << seq.length() << endl;
                split(contigID,ll," \t");
                genome.insert(pair<string,string>(ll[0],seq));
            }
            contigID = line.substr(1,line.length()-1);
            seq = "";
        }else{
            seq.append(line);
        }
        
    }
//    cout << contigID << "\t" << seq.length() << endl;
    genome.insert(pair<string,string>(contigID,seq));
    cout << genome.size() << " contigs readed!" << endl;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        split(line,ll," \t");
        chrID = ll[0];
        string contigIDs = ll[1];
        ll.clear();
        split(contigIDs,ll,";");
        string seqs = "";
//        cout << contigIDs << endl;
        if(ll.size() > 1){
            for (int i = 0; i < ll.size() - 1;i++){
                split(ll[i],strand,":");
                if (strand[1] == "-"){
                    seqs.append(reverse_complementary(genome[strand[0]]));
                }else{
                    seqs.append(genome[strand[0]]);
                }
                seqs.append(gap);
            }
            split(ll[ll.size()-1],strand,":");
            if (strand[1] == "-"){
                seqs.append(reverse_complementary(genome[strand[0]]));
            }else{
                seqs.append(genome[strand[0]]);
            }
            seqs.append(genome[ll[ll.size()-1]]);
        }else{
            strand.clear();
            split(contigIDs,strand,":");
            if (strand[1] == "-"){
                seqs.append(reverse_complementary(genome[strand[0]]));
            }else{
                seqs.append(genome[strand[0]]);
            }
//            seqs = genome[ll[0]];
        }
        ouf << ">" << chrID << "\n";
        for (int i = 0; i< seqs.length();i++){
            ouf << seqs[i] ;
            if ( (i != seqs.length()-1) && (i+1)%80 == 0){
                ouf << "\n";
            }
        }
        ouf << "\n";
    }
    ouf.close();
    return 0;
}
int countFastaKmer(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in); // fasta file
    ifstream inf2 (infile2.c_str()); // library file
    ofstream ouf ((outfile).c_str());
    string line;
    unordered_map<uint64_t, int> kmer;
    int threshold = (para->threshold);
    vector<string> ll;
    int kmer_len;
    while (!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        ll.clear();
        split(line,ll," \t");
        kmer_len = ll[0].length();
        uint64_t key = encode(ll[0]);
        kmer.insert(pair<uint64_t,int>(key,1));
    }
    cout << "library readed! size is:\t" << kmer.size() << endl;
    bool next = false;
    string seq = "";
    string readID = "";
//    unordered_map<string,int> freq;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '>'){
            if(seq != ""){
                //To do kmer counting;
                int seqlength = seq.length();
                int counted = 0;
                set<uint64_t> maxKmer;
                for(int i = 0; i < seqlength - kmer_len - 8; i+=8){
                    uint64_t key = encode(seq.substr(i,kmer_len));
                    maxKmer.insert(key);
                    if(kmer.count(key)) counted++;
                }
                double f = (double)counted/seqlength;
                if (f > threshold ){
                    ouf << readID << "\t" << seqlength << "\t" << maxKmer.size() << "\t" << counted << "\t" << f << "\n";
                }
               
            }
            readID = line.substr(1,line.length()-1);
            seq = "";
        }else{
            seq.append(line);
        }
    }
    if(seq != ""){
        //To do kmer counting;
        int seqlength = seq.length();
        int counted = 0;
        set<uint64_t> maxKmer;
        for(int i = 0; i < seqlength - kmer_len - 8; i+=8){
            uint64_t key = encode(seq.substr(i,kmer_len));
             maxKmer.insert(key);
            if(kmer.count(key) == 1) counted++;
        }
        double f = (double)counted/seqlength;
        if (f > threshold ) {
             ouf << readID << "\t" << seqlength << "\t" << maxKmer.size() << "\t" << counted << "\t" << f << "\n";
        }
       
    }
    ouf.close();
    return 0;
}
int blast2maf (parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    string group = (para->flag);
    string line;
    vector<string> ll;
    string subseq;
    string geneID;
    while (!inf2.eof()){
        getline(inf2,line);
        if (line.length() < 1) continue;
        if(line[0] == '>'){
            ll.clear();
            split(line,ll," \t");
            string a =ll[ll.size() - 1];
            geneID = a.substr(1,a.length() - 1);
        }else{
            subseq.append(line);
        }
    }
    cout << "Gene " << geneID << "'s length is: " << subseq.length() << endl;
    ofstream ouf ((outfile + "_" + geneID + ".fasta").c_str());
    vector<string> queryseq(subseq.length(),"");
    bool block_s = false;
    bool isPositive = true;
    string temp ;
    int start = 0, end = 0;
    while (!inf.eof()){
        getline(inf,line);
        if (line.length() < 1) continue;
        ll.clear();
        split(line, ll," \t");
        if (!block_s & ll[0] != "Query" ) {
            continue;
        }
//        cout << ll[0] << endl;
        if (ll[0][0] == 'Q' | ll[0][0] == '|' | ll[0][0] == 'S') {
            block_s = true;
        }else {
            block_s = false;
            isPositive = true;
        }
        if (ll[0] == "Query"){
            temp = ll[2];
        }
        
        if (ll[0] == "Sbjct"){
            if (string2Int(ll[1]) > string2Int(ll[3])){
                isPositive = false;
                start = string2Int(ll[3]);
                end = string2Int(ll[1]);
            }else{
                start = string2Int(ll[1]);
                end = string2Int(ll[3]);
            }
            string rq ;
//            cout << line << endl;
            if(!isPositive){
                rq = reverse_complementary(temp);
            }else{
                rq = temp;
            }
            
            if (ll[2].length() != temp.length()){
                cout << "Query is:\t" << temp << endl;
                cout << "Sbjct is:\t" << ll[2] << endl;
                cerr << "length differ, please check" << endl;
            }
            int gap = 0;
            int sumgap = 0;
            for(int i = 0; i < temp.length(); i++ ){
                if(ll[2][i] != '-' & rq[i] != '-'){
                    queryseq[start+i-1-sumgap] = rq.substr(i-gap,1+gap);
                    gap = 0;
                }else if (ll[2][i] == '-'){
                    gap++;
                    sumgap++;
                }
            }
            if (gap != 0 ){
                if(queryseq[end - 1] == ""){
                    queryseq[end - 1] = rq.substr(rq.length() - gap -1,1+gap);
                }else{
                    string pre = queryseq[end - 1];
                    string post = rq.substr(rq.length() - gap ,gap);
                    pre.append(post);
                    queryseq[end - 1] = pre;
                }
            }
        }
    }
    ouf << ">" << group << "\n";
    int b = 0;
    string assembled = "";
    for (int i = 0 ; i <queryseq.size(); ++i ){
        if (queryseq[i] == "" || queryseq[i] == "-") continue;
        assembled.append(queryseq[i]);
    }
    for (int i = 0 ; i <assembled.length(); ++i ){
        if (assembled[i] == '-') continue;
        b++;
        if (b % 100 == 0) ouf << "\n";
        ouf << (char)toupper(assembled[i]);
    }
    ouf << "\n";
    ouf.close();
    return 0;
}

int getKmer(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para-> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    map<uint64_t,vector<int>> kmer_number; // key: kmer; value: vector, even is order; odd is freqency
    map<uint64_t,vector<string>> kmer_strand; // key: kmer; value: vector, even is order; odd is strand
    map<string,int> nameMap; // key: fastq ID, value: numbered order
    map<string,string> dataMap; // key: ID, value:
    int lineNow = 0;
    int fno = 0; // fno: fastq number order
    string line;
    string keyName;
    lint totalSize = 0;
    int kmer_len = 8;
    string seed = "AGC";
    int seed_len = seed.length();
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1 ) continue;
        lineNow++;
        if(lineNow % 4 == 1){
            keyName = line;
            continue;
        }else if (lineNow % 4 == 2){
            fno++;
            totalSize += line.size();
            nameMap.insert(pair<string,int>(keyName,fno));
            dataMap.insert(pair<string,string>(keyName,line)); // fastq file readed
            for(int i = 0; i< line.length() - kmer_len; i += seed_len){
                string subk = line.substr(i,seed_len);
                if(subk == seed){
                    uint64_t kmer32 = encode(line.substr(i + seed_len,kmer_len));
                    if(kmer_number.count(kmer32) == 1){
                        vector<int> count = kmer_number[kmer32];
                        vector<string> strand = kmer_strand[kmer32];
                        int length = count.size()-1;
                        if(count[length-2] == fno){
                            count[length-1] ++;
                        }else{
                            count.push_back(fno);
                            count.push_back(1);
                            strand.push_back(Int2String(fno));
                            strand.push_back("+");
                        }
                        kmer_number[kmer32] = count;
                        kmer_strand[kmer32] = strand;
                    }else{
                        vector<int> count ;
                        vector<string> strand;
                        count.push_back(fno);
                        strand.push_back(Int2String(fno));
                        count.push_back(1);
                        strand.push_back("+");
                        kmer_number.insert(pair<uint64_t,vector<int>>(kmer32,count));
                        kmer_strand.insert(pair<uint64_t,vector<string>>(kmer32,strand));
                    }
                }
            }
            string rl = reverse_complementary(line);
            for(int i = 0; i< rl.length() - kmer_len; i += seed_len){
                string subk = rl.substr(i,seed_len);
                if(subk == seed){
                    uint64_t kmer32 = encode(rl.substr(i + seed_len,kmer_len));
                    if(kmer_number.count(kmer32) == 1){
                        vector<int> count = kmer_number[kmer32];
                        vector<string> strand = kmer_strand[kmer32];
                        int length = count.size()-1;
                        if(count[length-2] == fno){
                            count[length-1] ++;
                        }else{
                            count.push_back(fno);
                            count.push_back(1);
                            strand.push_back(Int2String(fno));
                            
                            strand.push_back("-");
                        }
                        kmer_number[kmer32] = count;
                    }else{
                        vector<int> count ;
                        vector<string> strand;
                        count.push_back(fno);
                        count.push_back(1);
                        strand.push_back(Int2String(fno));
                        strand.push_back("-");
                        kmer_number.insert(pair<uint64_t,vector<int>>(kmer32,count));
                        kmer_strand.insert(pair<uint64_t,vector<string>>(kmer32,strand));
                    }
                }
            }
        }else {
            continue;
        }
    }
    cout << "Kmer size is:\t" << kmer_number.size() << endl;
    cout << "Total reads is:\t" << fno << endl;
    cout << "Total size is:\t" << totalSize << endl;
    map<uint64_t,vector<int>>::iterator kit;
    
    for(kit = kmer_number.begin(); kit !=kmer_number.end(); kit++){
        char *seq ;
        decode(kit->first,seq,false);
        vector<int> number = kit->second;
//        ouf << seq ;
        
        for( int i = 0; i < number.size(); ++i){
            ouf << "\t" << number[i];
        }
        ouf << "\n";
    }
    ouf.close();
    return 0;
}

int getGenomeMasked (parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    string chr = "";
    string line;
    string seq = "";
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if (line[0] == '>'){
            if (seq == "") {
                seq = "";
                chr = line.substr(1,2);
                continue;
            }
            cout << chr <<" length is:\t" << seq.length() << endl;
            for (int i = 0; i < seq.length(); ++i){
                if (seq[i] == 'N') continue;
                ouf << "chr" << chr << "\t" << i+1 << "\n";
            }
            chr = line.substr(1,2);
            seq = "";
        }else{
            seq.append(line);
        }
    }
    cout << chr <<" length is:\t" << seq.length() << endl;
    for (int i = 0; i < seq.length(); ++i){
        if (seq[i] == 'N') continue;
        ouf << chr << "\t" << i+1 << "\n";
    }
    ouf.close();
    return 0;
}
int BSAseq (parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    ouf << "chr\tstart\tend\ttotal_number\tpassed_number\tindex\n";
    ouf <<setiosflags(ios::fixed)<<setprecision(2);
    string line;
//    int window_size = (para -> size) * 1000;
//    int step_size = (para -> step_size) * 1000;
//    int window_num = ceil(window_size/step_size*1.0);
    
    vector<string> ll;
    string cur_line = "", pre_line = "";
//    vector<int> start(window_num,0);
//    vector<int> end(window_num,0);
//    vector<int> sum(window_num,0);
    int s = 0, e = 0, tn = 0, pn = 0;
    double  idx = 0;
    string ch = "";
    cout << "runing..." << endl;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        if(line[0] == '#') continue;
//        cout << line << "\n";
        split(line,ll,"\t");
        string chr = ll[0];
        
        if (chr != ch){
            if( ( e - s) > 0){
                ouf << ch << "\t" << s << "\t" << e << "\t" << tn << "\t" << pn << "\t" << idx << "\n";
            }
            ch = chr;
            s = 0; e = 0; tn = 0; pn = 0; idx = 0;
            continue;
        }
        if (s == 0) s = string2Int(ll[1]);
        e = string2Int(ll[1]);
        if ( (e - s) > 1000000) {
            if (tn > 0 ) {
                idx = pn/tn * 1.0;
            }
            ouf << ch << "\t" << s << "\t" << e << "\t" << tn << "\t"  << pn << "\t" << idx << "\n";
            s = e; tn = 0; pn = 0; idx = 0;
        }else{
            tn++;
            if( ll[9][0] != '.' && ll[10][0] != '.' && ll[11][0] != '.' && ll[12][0] != '.'){
                if (ll[9][0] == ll[9][2] && ll[10][0] == ll[10][2] &&  ll[9][0] != ll[10][0] && ll[11][0] == ll[11][2]){
                    if(ll[9][0] == ll[11][0] && (ll[12][0] != ll[9][0] | ll[12][2] != ll[9][0])){
                        pn++;
                    }
                }
            }
        }
        
    }
    if ( (e - s) > 0) {
        idx = pn/tn * 1.0;
        ouf << ch << "\t" << s << "\t" << e << "\t" << tn << "\t"  << pn  << "\t" << idx << "\n";
        s = e; tn = 0; pn = 0; idx = 0;
    }
    ouf.close();
    return 0;
}
int readCurrentFolder(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    string suffix = (para->suffix);
    ofstream ouf ((outfile).c_str());
    string pattern = (para->pattern);
    vector<string> files = getCurrentFoldfiles(infile,suffix);
    for(int i = 0; i < files.size(); i++){
        smatch result;
        string str = files[i];
        string::const_iterator iterStart = str.begin();
        string::const_iterator iterEnd = str.end();
        regex pattern(pattern);
        regex_search(iterStart, iterEnd, result, pattern);
        ouf <<  str << "\t" << result[0] << "\n";
    }
    ouf.close();
    return 0;
}

int readAllFolder(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);
    string suffix = (para -> suffix);
    ofstream ouf ((outfile).c_str());
    string pattern = (para->pattern);
//    cout << "infile is:\t" << infile << endl;
//    cout << "suffix is:\t" << suffix << endl;
    vector<string> files = getSubFoldfiles(infile,suffix);
    cout << "Number of files matched is:\t" << files.size() << endl;
    for(int i = 0; i < files.size(); i++){
        smatch result;
        string str = files[i];
        vector<string> ll;
        split(str,ll,"/");
        if(ll.size() != 11 & ll.size() != 12) continue;
        string tmp = ll[ll.size()-2];
        ll.clear();
        split(tmp,ll,"_");
//        cout << "string is:\t" << str << endl;
//        string::const_iterator iterStart = str.begin();
//        string::const_iterator iterEnd = str.end();
//        regex pattern(pattern);
//        cout << "testing 1..." << endl;
//        cout << "pattern is:\t" << pattern << endl;
//        regex_search(iterStart, iterEnd, result, regex(pattern));
//        cout << "testing 2..." << endl;
        ouf <<  str << "\t" << ll[ll.size()-1] << "\n";
    }
    ouf.close();
    return 0;
}
int cigarSimilarity(parameter *para){
    string infile = (para -> inFile);
    string infile2 = (para -> inFile2); // bed file
    string outfile = (para -> outFile); // prefix only
    double t = (para -> threshold);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    vector<string> ll;
    map<string,int> contig_length;
    string line;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1 ) continue;
        split(line,ll," \t");
        contig_length.insert(pair<string,int>(ll[0],string2Int(ll[2]) + 15000));
    }
    cout << contig_length.size() << " contigs found!" << endl;
    map<string,vector<int>> ar ;
    vector<string> ri ;
    
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1 ) continue;
        ll.clear();
        split(line,ll," \t");
        vector<int> array=parseCIGAR(ll[3],contig_length[ll[1]],string2Int(ll[2]));
        ar.insert(pair<string,vector<int>>(ll[0],array));
        ri.push_back(ll[0]);
    }
    cout <<  ri.size() << " CIGAR values readed!" << endl;
    vector<set<string>> pa;
//    ofstream ouf1 ((outfile + ".test.txt").c_str());
    for (int i = 0; i < ri.size() - 1; i++){
        string id1 = ri[i];
        vector<int> vi1 = ar[ri[i]];
        for (int j = i+1; j < ri.size(); j++){
            string id2 = ri[j];
            vector<int> vi2 = ar[ri[j]];
            int sum = 0;
            int diff = 0;
            for (int idx = 0; idx < vi1.size(); idx++){
                if (vi2[idx] == -1 || vi1[idx] == -1 ) continue;
                int a1 = abs(vi2[idx] - vi1[idx]);
                if (a1 > 2) {
                    int a2  , a3 ;
                    a2 = abs(vi2[idx] - vi1[idx+1]);
                    a3 = abs(vi2[idx+1] - vi1[idx]);
                    int a = smallest(a1,a2,a3);
                    diff += a;
                }else{
                    diff += a1;
                }
                sum++;
            }

            if (((double)diff/sum*1.0) < t && sum > 1000) {
                if (pa.size() > 0){
                    bool inserted = false;
                    for (int p = 0; p < pa.size(); p++){
                        set<string> value = pa[p];
                        if(value.count(id1) == 1 ){
                            value.insert(id2);
                            pa[p] = value;
                            inserted = true;
                        }else if ( value.count(id2) == 1){
                            value.insert(id1);
                            pa[p] = value;
                            inserted = true;
                        }
                    }
                    if (!inserted){
                        set<string> nv;
                        nv.insert(id1);
                        nv.insert(id2);
                        pa.push_back(nv);
                    }
                }else{
                    set<string> value;
                    value.insert(id1);
                    value.insert(id2);
                    pa.push_back(value);
                }
//                if(id1=="m64054_191222_151922/128386659/ccs" || id2 == "m64054_191222_151922/128386659/ccs"){
//                    cout << "id1 = " << id1 << "; id2 = " << id2 << endl;
//                    cout << "diff is:\t" << diff << "; sum is:\t" << sum << endl;
//                }
            }
//            ouf1 << id1 << "\t" << id2 << "\t" << diff << "\t" <<  sum << endl;
        }
    }
    if ( pa.size() == 0){
        cout << "None group found!" << endl;
        return 0;
    }
    cout << pa.size() << " groups found!" << endl;
    int g = 0;
    for (int i = 0; i < pa.size(); i++){
        set<string> value = pa[i];
        set<string>::iterator it = value.begin();
        ofstream ouf ((outfile + ".group" + Int2String(g) + ".txt").c_str());
        while (it != value.end()){
            ouf << *it << "\n";
            it++;
        }
        g++;
        ouf.close();
    }
    
    
    
    return 0;
}
int concensus(parameter *para){
    string infile = (para -> inFile);
    string outfile = (para -> outFile);

    igzstream inf ((infile).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    int misMatchPenalty = 10;
    int gapPenalty = 2;
    string line;
    string seq = "";
    while(!inf.eof()){
        
    }
    string gene1 = "AAGGCTAG";
    string gene2 = "AGGCTA";
    
    getMinimumPenalty(gene1, gene2,misMatchPenalty, gapPenalty);
        
    return 0;
}

int paf(parameter *para){
    string infile = (para -> inFile); // paf file
    string infile2 = (para -> inFile2); //mapped file
    string infile3 = (para -> inFile3); //fai file
    string outfile = (para -> outFile);
    double t = (para -> threshold); // threshold
    string chr = (para -> chr);
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    igzstream inf3 ((infile3).c_str(),ifstream::in);
    string line;
    vector<string> ll;
    vector<set<string>> pa;
    map<string,string> idc;
    map<string,vector<int>> ar ;
    map<string,int> contigs;
    
    while (!inf3.eof()){
        getline(inf3,line);
        if(line.length() < 1) continue;
        split(line,ll," \t");
        contigs.insert(pair<string,int>(ll[0],string2Int(ll[1])));
    }
    cout << "contig length readed!" << endl;
    
    while (!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        split(line,ll," \t");
        string readID = ll[0];
        string contigID = ll[1];
        string cigar = ll[3];
        idc.insert(pair<string,string>(readID,contigID));
//        idcigar.insert(pair<string,string>(key,cigar));
        int contig_length  = contigs[contigID];
        if(contigID != chr) continue;
        vector<int> arrays = parseCIGAR(cigar,contig_length,string2Int(ll[2]));
//        cout << "parsed CIGAR:" << readID << endl;
        ar.insert(pair<string,vector<int>>(readID,arrays));
    }
    cout << "CIGAR values readed!" << endl;
    map<string,double> pairsValue;
    double *ss =  new double[10000*10000];
    double (*sim)[10000] = (double(*)[10000])ss;

    for (int col = 0; col < 10000; col++){
        for (int row = 0; row < 10000; row++){
            sim[row][col] = -1;
        }
    }
    vector<string> IDo;
    map<string,int> idp;
    int cpos = 0;
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1 ) continue;
        split(line,ll," \t");
        // 1. div should smaller than 0.01
        // 2. two sequences should overlapped (overlapped region should not located in the two sequences)
        // 3. overlap length longer than 1kb
        string id1 = ll[0];
        string id2 = ll[5];
        if (idc[id1] != idc[id2]) continue;
        if (idc[id1] != chr) continue;
        int start1 = string2Int(ll[2]);
        int start2 = string2Int(ll[7]);
        int end1 = string2Int(ll[3]);
        int end2 = string2Int(ll[8]);
        int len1 = string2Int(ll[1]);
        int len2 = string2Int(ll[6]);
        string div = ll[15];
        ll.clear();
        split(div,ll,":");
        double d = string2Double(ll[2]);
        if(d > 0.0099) continue;
        if (start1 > 50 & (len1 - end1) > 50 & start2 > 50 & (len2 - end2) > 50) continue;
        if ( (end1 - start1) < 1000 || (end2 - start2) < 1000) continue;
        if ((start1 > 50) && (start2 > 50) && (ll[4] == "+")) continue;
        if (((len1 - end1) > 50) && ((len2 - end2) > 50) && (ll[4] == "+")) continue;
//        cout << "id1 + id2 is:\t" << id2 << endl;
        double rate = (double)(end1 - start1)/(end2-start2);
        if ( abs(1-rate) > t) continue;
        
        
        vector<int> vi1 = ar[id1];
        vector<int> vi2 = ar[id2];
        
        int sum = 0;
        int diff = 0;
        int l1 = 0;
        int l2 = 0;
        string ids = id1+"_"+id2;
        for (int idx = 0; idx < vi1.size(); idx++){
            if (vi2[idx] == -1 || vi1[idx] == -1 )
                continue;
            l1 += vi1[idx];
            l2 += vi2[idx];
            int a1 = abs(vi2[idx] - vi1[idx]);
            if (a1 > 2) {
                int a2  , a3 ;
                a2 = abs(vi2[idx] - vi1[idx+1]);
                a3 = abs(vi2[idx+1] - vi1[idx]);
                int a = smallest(a1,a2,a3);
                diff += a;
            }else{
                diff += a1;
            }
            sum++;
        }
        double piv = (double)diff/sum*1.0;
        
        
        pairsValue.insert(pair<string,double>(ids,piv));
        
        if ( piv < t && sum > 1000 && (abs(l1 - l2)/sum) < t){
            if (idp.count(id1) == 0){
                idp.insert(pair<string,int>(id1,cpos));
                cpos++;
                IDo.push_back(id1);
            }
            if (idp.count(id2) == 0){
                idp.insert(pair<string,int>(id2,cpos));
                cpos++;
                IDo.push_back(id2);
            }
            int p1 = idp[id1];
            int p2 = idp[id2];
            sim[p1][p2] = piv;
            sim[p2][p1] = piv;
        }
        
        
//        if ( piv < t && sum > 1000 && (abs(l1 - l2)/sum) < t) {
//            if (pa.size() > 0){
//                bool inserted = false;
//                for (int p = 0; p < pa.size(); p++){
//                    set<string> value = pa[p];
//                    if(value.count(id1) == 1 ){
//                        value.insert(id2);
//                        pa[p] = value;
//                        inserted = true;
//                    }else if ( value.count(id2) == 1){
//                        value.insert(id1);
//                        pa[p] = value;
//                        inserted = true;
//                    }
//                }
//                if (!inserted){
//                    set<string> nv;
//                    nv.insert(id1);
//                    nv.insert(id2);
//                    pa.push_back(nv);
//                }
//            }else{
//                set<string> value;
//                value.insert(id1);
//                value.insert(id2);
//                pa.push_back(value);
//            }
//        }
    }
    
//    if ( pa.size() == 0){
//        cout << "None group found!" << endl;
//        return 0;
//    }
//    cout << pa.size() << " groups found!" << endl;
//    int g = 0;
//    for (int i = 0; i < pa.size(); i++){
//        set<string> value = pa[i];
//        if (value.size() < 5) continue;
//        set<string>::iterator it = value.begin();
//        ofstream ouf ((outfile + ".group" + Int2String(g) + ".txt").c_str());
//        vector<string> idid;
//        while (it != value.end()){
//            idid.push_back(*it);
//            ouf << *it << "\n";
//            it++;
//        }
//        g++;
//        ouf.close();
//    }
    ofstream ouf (outfile.c_str());
    if  (cpos > 5){
        for (int p = 0 ; p < IDo.size() - 1; p++){
            ouf << IDo[p] << "\t";
        }
        ouf << IDo[IDo.size() - 1] << "\n";
        for (int p = 0; p < IDo.size() ; p++){
            for (int p2 = 0; p2 < IDo.size() -1; p2++ ){
                ouf << sim[p][p2] << "\t";
            }
            ouf << sim[p][IDo.size() - 1] << "\n";
        }
    }
    ouf.close();
    return 0;
}
int removeHS (parameter *para){
    string infile = (para -> inFile); // paf file
//    string infile2 = (para -> inFile2); // fai file
    string outfile = (para -> outFile); //
    igzstream inf ((infile).c_str(),ifstream::in);
//    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    vector<string> ll;
    map<string,int> contigLen;
    map<string,whole_section> sec;
    string line;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        split(line,ll," \t"); // paf line
        int len1 = string2Int(ll[1]);
        int len2 = string2Int(ll[6]);
//        if (len1 > len2) continue;
        int start = string2Int(ll[2]);
        int end = string2Int(ll[3]);
        
        string c1 = ll[0];
        string c2 = ll[5];
//        if (c1 == c2) continue;
        contigLen.insert(pair<string,int>(c1,len1));
        contigLen.insert(pair<string,int>(c2,len2));
        string key = c1 + "_" + c2;
        if (len1 > len2){
            key = c2 + "_" + c1;
            start = string2Int(ll[7]);
            end = string2Int(ll[8]);
        }
        whole_section* ws;
        ws=(whole_section*)malloc(sizeof(whole_section));
        init(ws);
        if (sec.count(key) == 0){
            insert(ws,start,end);
            sec.insert(pair<string,whole_section>(key,*ws));
        }else{
            ws = & sec[key];
            insert(ws,start,end);
            sec[key] = *ws;
        }
    }
    cout << "Found " << sec.size() << " pairs!" << endl;
    map<string,int>::iterator it;
    it = contigLen.begin();
    vector<string> c;
    vector<int> len;
    while (it != contigLen.end()){
        c.push_back(it->first);
        len.push_back(it->second);
        it++;
    }
    vector<size_t> idx;
    cout << "contigs found:\t" << contigLen.size() << endl;
    idx = sort_indexes_e(len);
//    cout << c[idx[idx.size()-1]] << endl;
    for (int i = 0; i < idx.size()-1; i++){
        bool kept = true;
        for (int j = i+1; j < idx.size(); j++){
            string k = c[idx[i]] + "_" + c[idx[j]];
            int l = len[idx[i]]; // contig length
            int sum = calculate(&sec[k]); // matched length
//            if (k == "contig2080_contig1996"){
//                cout << "l is:\t" << l << endl;
//                cout << "sum is:\t" << sum << endl;
//            }
            if (sum*1.0/l > 0.8){
                kept = false;
                break;
            }
        }
        if (kept){
            ouf << c[idx[i]] << "\n";
        }
    }
    ouf << c[idx[idx.size()-1]] << "\n";
    ouf.close();
//
//    map<string,whole_section>::iterator iter;
//    iter = sec.begin();
//    while(iter != sec.end()) {
//        cout << iter->first << " : " << calculate(&(iter->second)) << endl;
//        iter++;
//    }
   
    
    return 0;
}
int removeVsRef (parameter *para){
    string infile = (para -> inFile); // paf file
    string infile2 = (para -> inFile2); // orinal ID
    string outfile = (para -> outFile); //
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    ofstream ouf ((outfile).c_str());
    vector<string> ll;
    map<string,int> contigLen;
    map<string,whole_section> sec;
    string line;
    set<string> cfound;
    while(!inf.eof()){
        getline(inf,line);
        if(line.length() < 1) continue;
        split(line,ll," \t"); // paf line
        int len1 = string2Int(ll[1]);
        int len2 = string2Int(ll[6]);
//        if (len1 > len2) continue;
        int start = string2Int(ll[2]);
        int end = string2Int(ll[3]);
        
        string c1 = ll[0];
        string c2 = ll[5];
//        if (c1 == c2) continue;
        cfound.insert(c1);
        contigLen.insert(pair<string,int>(c1,len1));
        contigLen.insert(pair<string,int>(c2,len2));
        string key = c1 + "_" + c2;
        if (len1 > len2){
            key = c2 + "_" + c1;
            start = string2Int(ll[7]);
            end = string2Int(ll[8]);
        }
        whole_section* ws;
        ws=(whole_section*)malloc(sizeof(whole_section));
        init(ws);
        if (sec.count(key) == 0){
            insert(ws,start,end);
            sec.insert(pair<string,whole_section>(key,*ws));
        }else{
            ws = & sec[key];
            insert(ws,start,end);
            sec[key] = *ws;
        }
    }
    cout << "Found " << sec.size() << " pairs!" << endl;
    map<string,int>::iterator it;
    it = contigLen.begin();
    vector<string> c;
    vector<int> len;
    while (it != contigLen.end()){
        c.push_back(it->first);
        len.push_back(it->second);
        it++;
    }
    vector<size_t> idx;
    cout << "contigs found:\t" << contigLen.size() << endl;
    idx = sort_indexes_e(len);
//    cout << c[idx[idx.size()-1]] << endl;
    for (int i = 0; i < idx.size()-1; i++){
        bool kept = true;
        for (int j = i+1; j < idx.size(); j++){
            string k = c[idx[i]] + "_" + c[idx[j]];
            int l = len[idx[i]]; // contig length
            int sum = calculate(&sec[k]); // matched length
//            if (k == "contig2080_contig1996"){
//                cout << "l is:\t" << l << endl;
//                cout << "sum is:\t" << sum << endl;
//            }
            if (sum*1.0/l > 0.8){
                kept = false;
//                if (c[idx[i]] == "ptg001039l_1_awad"){
//                    print(&sec[k]);
//                    cout << "sum is:\t" << sum << endl;
//                }
                break;
            }
            
        }
        if (kept){
            ouf << c[idx[i]] << "\n";
        }
    }
    ouf << c[idx[idx.size()-1]] << "\n";
    
    while (!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1) continue;
        split(line,ll," \t");
        if (cfound.count(ll[0]) == 0){
            ouf << ll[0] << "\n";
        }
    }
    ouf.close();
//
//    map<string,whole_section>::iterator iter;
//    iter = sec.begin();
//    while(iter != sec.end()) {
//        cout << iter->first << " : " << calculate(&(iter->second)) << endl;
//        iter++;
//    }
   
    
    return 0;
}
int cleanCIGAR(parameter *para){
    string infile = (para -> inFile); // map file
    string infile2 = (para -> inFile2); // fai file
    string outfile = (para -> outFile); // prefix only
    igzstream inf ((infile).c_str(),ifstream::in);
    igzstream inf2 ((infile2).c_str(),ifstream::in);
    vector<string> ll;
    map<string,int> contig_length;
    string line;
    while(!inf2.eof()){
        getline(inf2,line);
        if(line.length() < 1 ) continue;
        split(line,ll," \t");
        contig_length.insert(pair<string,int>(ll[0],string2Int(ll[2]) + 15000));
    }
    map<string,vector<int>> ar ;
    vector<string> ri ;
    
    while (!inf.eof()){
        getline(inf,line);
        if(line.length() < 1 ) continue;
        ll.clear();
        split(line,ll," \t");
        vector<int> array=parseCIGAR(ll[3],contig_length[ll[1]],string2Int(ll[2]));
        ar.insert(pair<string,vector<int>>(ll[0],array));
        ri.push_back(ll[0]);
    }
    cout <<  ri.size() << " CIGAR values readed!" << endl;
    vector<set<string>> pa;

    
    
    
    return 0;
}
#endif /* FileFunctions_h */
