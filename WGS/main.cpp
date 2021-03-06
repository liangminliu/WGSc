//
//  main.cpp
//  WGS
//
//  Created by Yao Zhou on 2018/12/4.
//  Copyright © 2018 Yao Zhou. All rights reserved.
//

#include "HeaderIns.h"
#include "baseFunctions.h"
#include "DataClass.h"
#include "help.h"
#include "initialization.h"
#include "checkers.h"
#include "FileFunctions.h"
#include "scripts.h"
#include "vcf.h"
#include "dataConvert.h"
int main(int argc, char * argv[]) {
    clock_t start;
    double duration;
    start = clock();
    
    //Testing

//     gene1 = "GGGGGGGGGGGGGGGGGGGGGAAAGAAAAAAA";
//     gene2 = "AAGAAAAAAATTTTTTTTTTTTTTTTTTTT";
//    int misMatchPenalty = -1;
//    int gapPenalty =  -1;
    
//    SmithWaterman(gene1, gene2,misMatchPenalty, gapPenalty);
//    getMinimumPenalty(gene1, gene2,misMatchPenalty, gapPenalty);
//    regex dv("(dv:f:)(.*)(\\s)");
//    smatch m;
//    string l ="s1:i:9541\tdv:f:0.0083\trl:i:5540";
//    cout << regex_search(l.cbegin(),l.cend(), m,dv) << endl;
//    cout << m.str() << endl;
//    cout << m.str(1) << endl;
//    cout << m.str(2) << endl;
//    whole_section* ws;
//    ws=(whole_section*)malloc(sizeof(whole_section));
//    init(ws);
//    insert(ws,0,1);
//    print(ws);
//    insert(ws,0,3);
//    print(ws);
//    insert(ws,-5,-2);
//    print(ws);
//    insert(ws,7,9);
//    print(ws);
    parameter *para = new parameter;
    if ( (WGS_initialization(argc, argv, para) == 0) )
    {
        delete para;
        return 1 ;
    }
    
    vcf *inVCF = new vcf;
    depth *inDepth = new depth;
    
    if (!(para->inFile).empty())
    {
        if ((para -> model).empty()){
            cerr << "model should be specified! Please check" << endl;
        }else if((para -> model) == "vcf"){
            if((para->type)==""){
                Read_VCF_IN(para, inVCF);
            }else if((para->type)=="GenerateDiploid"){
                GenerateDiploid(para);
            }else if((para->type)=="toFastaRef"){
                toFastaRef(para);
            }else if((para->type)=="filterBarley"){
                filterBarley(para);
            }else if((para->type) == "calibrate"){
                calibarate(para);
            }else if((para->type) == "calibrate2"){
                calibarate2(para);
            }else if((para->type) == "calibarate3"){
                calibarate3(para);
            }else if((para->type) == "calibarate4"){
                calibarate4(para);
            }else if((para->type) == "calibarate5"){
                calibarate5(para);
            }else if((para->type)=="toV8"){
                cout << "toV8..." << endl;
                getV8(para);
            }else if ((para->type)=="site-pi"){
                pi(para);
            }else if((para->type) == "vcf2sNMF"){
                vcf2sNMF(para);
            }else if ((para->type) == "getHeader"){
                getHeader(para);
            }else if ((para->type) == "get2vcf"){
                get2vcf(para);
            }else if((para->type) == "depthFilter"){
                DepthFilter(para);
            }else if((para->type) == "depthFilterDP"){
                DepthFilterDP(para);
            }else if((para->type) == "calTotalDP"){
                calTotalDP(para);
            }else if((para->type) == "inDel_len"){
                inDel_len(para);
            }else if((para->type) == "ct3"){
                ct3(para); // snps shared among three groups
            }else if((para->type) == "ct2"){
                ct2(para); // snps shared in two groups
            }else if((para->type) == "ct1"){
                ct1(para); // allelic or not
            }else if((para->type) == "dot"){
                dotdot(para); // allelic or not
            }else if((para->type) == "addContig"){
                addContig(para);
            }else if((para -> type) == "ANC"){
                changeAncestralAllele(para);
            }else if ((para->type) == "merge2vcf"){
                merge2vcf(para);
            }else if ((para->type) == "addOutgroup"){
                add2vcf(para);
            }else if ((para->type) == "toXPCLR"){
                toXPCLR(para);
            }else if((para->type) =="toXPCLRsnp") {
                toXPCLRsnp(para);
            }else if ((para->type)=="toV11"){
                toV11(para);
            }else if ((para->type) == "toSFS"){
                toSFS(para);
            }else if ((para->type) == "pwMAF"){
                pwFrequence(para);
            }else if((para->type) =="maf"){
                writeMAF(para);
            }else if ((para->type) =="Derived"){
                getDerivedAllele(para);
            }else if ((para->type) == "incp"){
                cp(para);
            }else if ((para->type) == "getExtream"){
                getExtream(para);
            }else if((para->type) =="DAF"){
                daf(para);
            }else if ((para->type)=="getReg"){
                getRegulation(para);
            }else if ((para->type) =="changePos"){
                changeVcfPos(para);
            }else if ((para->type) =="smoothIndel"){
                smoothIndel(para);
            }else if ((para->type) == "toDstatistic"){
                vcf2Dstat(para);
            }else if ((para->type)=="IS"){
                IScore(para);
            }else if ((para->type) == "GeneticDistance"){
                getGeneticDistance(para);
            }else if ((para->type) == "GeneticDistanceRef"){
                getGeneticDistanceRef(para);
            }else if ((para ->type) == "getMinDxy"){
                getGeneticDistance2(para);
            }else if((para->type) =="intersect"){
                getIntersectVcf(para);
            }else if ((para->type) == "getUnIntersectBed"){
                getUnIntersectBed(para);
            }else if((para->type) =="unintersect"){
                getUnIntersectVcf(para);
            }else if ((para->type) == "toEigenStrat"){
                toEigenStrat(para);
            }else if((para->type) == "getSummary"){
                getSummary(para);
            }else if ((para->type) == "overlap"){
                vcfoverlap(para);
            }else if ((para->type) =="toAncestral"){
                vcf2ancestral(para);
            }else if ((para->type) == "DPvsGATK"){
                DPvsGATK(para);
            }else if ((para->type) == "het2depth"){
                het2depth(para);
            }else if ((para->type) == "vcf2RleateMap"){
                vcf2RleateMap(para);
            }else if ((para->type) == "vcf2bed"){
                vcf2bed(para);
            }else if ((para->type) == "addBarley"){
                V11_barley(para);
            }else if ((para->type) == "substract"){
                substract(para);
            }else if ((para->type) == "vcf2Major"){
                vcf2Major(para);
            }else if ((para->type) == "vcfAddID"){
                vcfAddID(para);
            }else if ((para->type) == "SNPs100window"){
                SNPs100window(para);
            }else if ((para->type) == "siteOverlap"){
                siteOverlap(para);
            }else if ((para->type) == "concatVCFsite"){
                concatVCFsite(para);
            }else if ((para->type) == "keep"){
                keep(para);
            }else if ((para->type) == "splitByChr"){
                splitByChrVCF(para);
            }else if ((para->type) == "SVfilter_reads"){
                SVfilter_reads(para);
            }else if ((para->type) == "SVfilter_long"){
                SVfilter_long(para);
            }else if ((para->type) == "bed2vcf"){
                bed2vcf(para);
            }else if ((para->type) == "mergeSVs"){
                mergeSVs(para);
            }
        }else if((para -> model) == "depth"){
            if((para->type)=="site"){
                Read_depth_IN(para);
            }else if((para->type) == "toBed"){
                Depth2Bed(para);
            }else if ((para->type) == "merge"){
                mergeDepth(para);
            }else if((para->type) == "mask"){
                getMaskRegion(para);
            }else if ((para->type) == "UnMapped"){
                getUnMapped(para);
            }else if ((para->type) == "Mapped"){
                getMapped(para);
            }else if ((para->type) == "siteDepth"){
                siteDepth(para);
            }else if ((para->type) == "getsynteny"){
                getsynteny(para);
            }else if ((para->type) == "divided2synteny"){
                divided2synteny(para);
            }else if ((para->type) == "filterByDepth"){
                filterByDepth(para);
            }else if ((para->type) == "C2VCF"){
                C2VCF(para);
            }else if ((para->type) == "D2B"){
                D2B(para);
            }else if ((para->type) == "Pos2Bed"){
                Pos2Bed(para);
            }
//            outDepthFile(para,inDepth);
        }else if ((para->model) == "pos"){
            if ((para->type) == "changePos"){
                changePos(para);
            }else if((para->type) =="change2num"){
                chr2num(para);
            }else if ((para->type) == "toEigenStrat"){
                changeEigenStratPos(para);
            }
        }else if((para->model) == "wc"){
            count(para);
        }else if((para->model) == "folder"){
           if ((para->type) == "current"){
               readCurrentFolder(para);
           }else if ((para->type) == "all"){
               readAllFolder(para);
           }
            
        }else if((para->model) == "file"){
            if ((para->type) == "merge"){
                mergeDepth(para);
            }else if((para -> type)=="random"){
                randChoose(para);
            }else if((para -> type)=="merge3"){
                filterDepth3(para);
            }else if((para -> type)=="synteny"){
                filterDepth(para);
            }else if((para -> type)=="mergeSynteny"){
                mergeSynteny(para);
            }else if((para -> type)=="Syn2HapScan"){
                Syn2HapScan(para);
            }else if((para -> type)=="merge2"){
                filterDepth2(para);
            }else if((para -> type)=="filterBySim3"){
                filterDepth_bySimulation3(para);
            }else if((para -> type)=="filterBySim"){
                filterDepth_bySimulation(para);
            }else if((para -> type)=="filterBySim2"){
//                cout <<"testing..."<<endl;
                filterDepth_bySimulation2(para);
            }else if((para->type) == "intersect"){
                intersectFile(para);
            }else if((para->type) == "diff"){
                diffFile(para);
            }else if ((para->type) == "getPos"){
                getPos(para);
            }else if((para->type) =="getMax"){
                getMaximum(para);
            }else if((para->type) =="pwpd"){
                pwpd(para);
            }else if((para->type) == "mumer4"){
                subMummer4(para);
            }else if((para->type) == "LDmean"){
                LDmean(para);
            }else if ((para->type) =="TEdensity"){
                TEdensity(para);
            }else if ((para->type) == "cleanBed"){
                cleanBed(para);
            }else if ((para->type) =="BestHit"){
                BestHit(para);
            }else if((para->type) == "geneToGff3"){
                FstGenes(para);
            }else if((para->type) =="pairedMAF"){
                getPairAlleleFrequency(para);
            }else if((para->type)=="ByChr"){
                splitByChrNoHeader(para);
            }else if((para->type) =="mummer2vcf"){
                mummer2vcf(para);
            }else if ((para->type) =="mummerCountInDel"){
                mummerCountInDel(para);
            }else if((para->type)=="blast2Gene"){
                blast2Gene(para);
            }else if((para->type)=="changeBlast"){
                changeBlast(para);
            }else if ((para->type) == "sog"){
                getSOG(para);
            }else if ((para->type)=="getKaKs"){
                getKaKs(para);
            }else if ((para->type) == "RemoveDot"){
                RemoveDot(para);
            }else if((para->type) =="pairOrtho"){
                pairOrtho(para);
            }else if ((para->type) =="summaryBeast"){
                summaryBeast(para);
            }else if ((para->type) =="summary2Beast"){
                summary2Beast(para);
            }else if ((para->type)=="mergeDgeno"){
                mergeDgeno(para);
            }else if ((para->type) == "DtoBed"){
                DtoBed(para);
            }else if ((para->type) == "DtoBed2"){
                DtoBed2(para);
            }else if ((para->type) == "meanBed"){
                meanBedpi(para);
            }else if ((para->type) == "GeoDistance"){
                getGeoDistance(para);
            }else if ((para->type)== "DistanceAll"){
                getDistanceAll(para);
            }else if ((para->type) == "tof4"){
                getSubTreemix(para);
            }else if ((para->type) =="checkFile"){
                checkFile(para);
            }else if ((para->type) == "getOrtholog"){
                getOrtholog(para);
            }else if ((para->type) == "HapToVCF"){
                riceHapToVCF(para);
            }else if ((para->type) == "getMean"){
                getMean(para);
            }else if ((para->type) == "getSum"){
                getSum(para);
            }else if ((para->type) == "wc"){
                wc(para);
            }else if ((para->type) =="ABBAstat"){
                ABBAstat(para);
            }else if ((para->type) == "ABBAsim"){
                ABBAsim(para);
            }else if ((para->type) == "depthEvaluation"){
                depthEvaluation(para);
            }else if ((para->type) == "rice"){
                getRiceGenes(para);
            }else if ((para->type)=="test"){
//                readtest(para);
            }else if ((para->type) == "snpID"){
                snpID(para);
            }else if ((para->type) == "maf2pos"){
                maf2pos(para);
            }else if ((para->type) =="checkPos"){
                checkPos(para);
            }else if ((para->type) == "blast2maf"){
                blast2maf(para);
            }else if ((para -> type) == "bed2single"){
                bed2single(para);
            }else if ((para -> type) == "BSAseq") {
                BSAseq(para);
            }else if ((para -> type) =="checkNumber"){
                checkNumber(para);
            }else if ((para -> type) == "modifyPAF" ){
                modifyPAF(para);
            }else if ((para -> type) == "getConcordance"){
                getConcordance(para);
            }else if ((para -> type) == "getConcordanceBed"){
                getConcordance_bed(para);
            }else if ((para -> type) == "frq2dxy"){
                frq2dxy(para);
            }else if ((para ->type) == "changeGeneticDistance"){
                changeGeneticDistance(para);
            }else if ((para->type) == "elai_summary"){
                elai_summary(para);
            }else if ((para->type) == "elai_region"){
                elai_region(para);
            }else if ((para->type) == "elai_regions"){
                elai_regions(para);
            }else if ((para->type) == "elai2bed"){
                elai2bed(para);
            }else if ((para ->type) == "getIBSdistance_bed"){
                getIBSdistance_bed(para);
            }else if ((para ->type) == "svmu"){
                svmu(para);
            }
        }else if((para->model) == "gff3"){
            if ((para->type) == "density"){
                getGffDensity(para);
            }else if ((para->type) == "gff2bed"){
                gff2bed(para);
            }else if ((para->type) == "gff3thin"){
                gff2thin(para);
            }else if ((para->type) =="ToGene"){
                getUniqueGene(para);
            }else if ((para->type) == "changePos"){
                changeGffPos(para);
            }else if((para->type) == "stat"){
                statGff(para);
            }else if((para -> type) == "gff2genic"){
                gff2genicsite(para);
            }else if ((para->type) == "gff2exon"){
                gff2exon(para);
            }else if ((para->type) == "gff2exon10Kb"){
                gff2exon10Kb(para);
            }else if ((para->type) == "gff2exon10Kbexcluded"){
                gff2exon10Kbexcluded(para);
            }else if ((para->type) == "gff2geneBed"){
                getGeneBed(para);
            }else if ((para->type) == "filterMakerGff"){
                filterMakerGff(para);
            }
        }else if((para->model) == "bed"){
            if ((para->type) == "changePos"){
                changeBedPos(para);
            }else if ((para->type) == "density"){
                getBedDensity(para);
            }
        
        }else if((para->model) == "diversity"){
            if((para->type)=="bedPi"){
                pi2bed(para);
            }else if((para->type) == "syn"){
                getOri(para);
            }else if ((para -> type) =="genePi"){
                genePi(para);
            }else if ((para->type) == "overCount"){
                gene_count(para);
            }else if((para->type) == "CountByGene"){
                gene_count_gene(para);
            }else if ((para->type)== "slicedByGene"){
                slicedFunction(para);
            }else if((para->type) == "reduction"){
                DiversityReduction(para);
            }
        }else if((para -> model) == "structure"){
            if((para -> type) == "Q2CLUMPP"){
                Q2CLUMPP(para);
            }else if((para->type) == "CLUMPP2R"){
                CLUMPP2R(para);
            }
        }else if((para->model) == "tree"){
            if((para->type) == "phy"){
                changePhy(para);
            }
        }else if ((para->model) == "fasta"){
            if((para->type) == "toMCscanGff"){
                getGffMCscan(para);
            }else if((para->type) =="changeGff"){
                getGffMCscanChr(para);
            }else if((para->type)=="pepTofasta"){
                pepTofasta(para);
            }else if((para->type)=="getContig"){
                getContig(para);
            }else if((para->type)=="writeContig"){
                writeContig(para);
            }else if((para->type)=="getScaffold"){
                getScaffold(para);
            }else if ((para->type) =="formatFasta"){
                formatFasta(para);
            }else if((para->type) =="formatFasta2"){
                formatFasta2(para);
            }else if((para->type) =="formatFasta3"){
                formatFasta3(para);
            }else if ((para->type) == "toPhy"){
                toPhy(para);
            }else if((para->type)=="getCDS"){
                getCDS(para);
            }else if((para->type)=="getSeq"){
                getSeq(para);
            }else if((para->type)=="keepLongest"){
                keepLongest(para);
            }else if ((para->type) =="RC"){
                changeGenomePos(para);
            }else if ((para->type) == "getRegion"){
                getRegion(para);
            }else if ((para->type) == "getKmerOrder"){
                getKmerOrder(para);
            }else if ((para->type) =="getKmerOrder2"){
                getKmerOrder2(para);
            }else if ((para->type) == "GenomeStatistic"){
                GenomeStatistic(para);
            }else if ((para -> type) == "getChr"){
                getFasta(para);
            }else if ((para -> type) == "summaryRate"){
                summaryRate(para);
            }else if ((para -> type) == "getReads"){
                getReads(para);
            }else if ((para-> type) =="splitByN"){
                splitByN(para);
            }else if ((para-> type) =="splitByNAll"){
                splitByNAll(para);
            }else if ((para-> type) =="GPM"){
                GPMm(para);
            }else if ((para-> type) =="GPM1"){
                GPMm1(para);
            }else if ((para->type) == "gene2Single"){
                gene2Single(para);
            }else if ((para->type) == "toPEfastq"){
                toPEfastq(para);
            }else if ((para->type) == "modifyGenome"){
                modifyGenome(para);
            }else if ((para->type) == "KmerFrequence"){
                KmerFrequence(para);
            }else if ((para -> type) == "getGenomeMasked"){
                getGenomeMasked(para);
            }else if ((para -> type) == "GeneratepsmcDiploid"){
                GeneratepsmcDiploid(para);
            } else if ((para ->type) == "concensusGenome"){
                concensusGenome(para);
            }else if ((para->type) =="generateSyntenyGenome"){
                generateSyntenyGenome(para);
            }else if ((para->type) == "generateAltGenome"){
                generateAltGenome(para);
            }else if ((para ->type) =="splitGenome"){
                splitGenome(para);
            }else if ((para -> type) == "getChrs"){
                getFastas(para);
            }else if ((para -> type) == "removeChrs"){
                removeContigs(para);
            }else if ((para -> type) == "concensus"){
                concensus(para);
            }
        }else if ((para->model) == "assembly"){
            if((para->type) == "fastq"){
                getKmer(para);
            }else if((para->type) == "faLib"){
                FastaKmerFrequence(para);
            }else if((para->type) == "fqLib"){
                FastqKmerFrequence(para);
            }else if((para->type) == "countFasta"){
                countFastaKmer(para);
            }else if((para->type) == "splitIntoPool"){
                splitIntoPool(para);
            }else if((para->type) == "getReadID"){
                getReadsID(para);
            }else if ((para->type) == "KS"){
                FastaKmerScore(para);
            }else if ((para->type) == "singleKS"){
                singleFastaKmerScore(para);
            }else if ((para->type) == "ClusterBasedOnKmer"){
                ClusterBasedOnKmer(para);
            }else if ((para->type) == "removeBlankFasta"){
                removeBlackFasta(para);
            }else if ((para->type) == "kmerFreq"){
                kmerFreq(para);
            }else if ((para->type) == "kmerFoldFreq"){
                kmerFoldFreq(para);
            }else if ((para->type) == "KmerReadScore"){
                KmerReadScore(para);
            }else if ((para->type) == "changeContigID"){
                changeID(para);
            }else if ((para->type) == "rename"){
                renameID(para);
            }else if ((para->type) == "reformatID"){
                reformatID(para);
            }else if ((para->type) == "removeContigs"){
                removeContigs(para);
            }
        }else if ((para->model) == "fastq"){
            if((para->type) == "subtract"){
                subtractFQ(para);
            }else if ((para -> type) == "subtractFQgroups"){
                subtractFQgroups(para);
            }else if ((para -> type) == "subtractFQBygroups"){
                subtractFQBygroups(para);
            }
            
        }else if ((para->model) == "scripts"){
            if ((para -> type) == "SRA1"){
                SRA1(para);
            }else if ((para -> type) == "SRA2"){
                SRA2(para);
            }else if ((para -> type) == "SRA3"){
                SRA3(para);
            }else if ((para -> type) == "SRA4"){
                SRA4(para);
            }else if ((para -> type) == "SRA5"){
                SRA5(para);
            }else if ((para -> type) == "SRA6"){
                SRA6(para);
            }else if ((para -> type) == "SRA7"){
                SRA7(para);
            }else if ((para -> type) == "SRA8"){
                SRA8(para);
            }else if ((para -> type) == "SRA9"){
                SRA9(para);
            }else if ((para -> type) == "SRA10"){
                SRA10(para);
            }else if ((para -> type) == "SRA11"){
                SRA11(para);
            }else if ((para -> type) == "SRA12"){
                SRA12(para);
            }else if ((para -> type) == "SRA13"){
                SRA13(para);
            }else if ((para -> type) == "SRA14"){
                SRA14(para);
            }else if ((para -> type) == "fastp"){
                getFastp(para);
            }else if ((para -> type) == "cp"){
                cpFolder(para);
            }
        }else if((para->model) == "bam"){
            if ((para -> type) == "test"){
               
            }else if ((para ->type) == "cigarSimilarity"){
                cigarSimilarity(para);
            }
        }else if((para->model) == "paf"){
            if ((para -> type) == "test"){
               
            }else if ((para ->type) == "div"){
                paf(para);
            }else if ((para ->type) == "removeHS"){
                removeHS(para);
            }else if ((para ->type) == "removeVsRef"){
                removeVsRef(para);
            }
        }
    }
    
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cout<<"Finished in "<< duration <<" sec " << '\n';
    return 0;
}
