# WGSc
## 1. Installation:
    git clone https://github.com/YaoZhou89/WGSc.git
#### For mac users:
    open the project directly, and add the libz.tbz in the linked Frameworks and libraries
#### For linux users:
    sh compile.sh
## 2. Functions   
### 2.1 count lines for a .gz file (gzip compressed)
    WGS --model wc --file depth.1.txt.gz
### 2.2 random choose from a file
    WGS --model file --type random --file all.depth.txt.gz --out test.txt.gz --r 0.001
### 2.3 select barley  as calibrate
    WGS --model vcf --type calibrate --file chr1.vcf.gz --out chr1.cal.vcf.gz
### 2.4 change the position from numeric to chr1
    WGS --model pos --type changePos --file chr1.vcf.gz --file2 pos.txt --out changed.vcf.gz --pos 2,3
### 2.5 Change the bam site depth to bed file;
    WGS --model depth --type toBed --file chr1.txt --out chr1.bed
### 2.6 estimate diversity 
    WGS --model diversity --type window-pi --file chr1.site.pi --windowSize 1000000 --out chr1.window.pi
### 
### 
### 
### 
### 
