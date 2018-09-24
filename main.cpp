//
// Created by atif on 2018/09/24.
//

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const double PI  = 3.141592653589793238463;
const double PI2 = 2.*PI;

double complimentary(double angle){

    double compliment = PI2-angle;
    return compliment < PI2 ? compliment:compliment-PI2;
}

void convertIso(unsigned char *tmpl, string outFile){

    ofstream file;
    file.open (outFile);

    int16_t width=0, height=0, xPixelsPerCM=0, yPixelsPerCM=0;
    int16_t numFingerprints=0, fingerPosition=0, quality=0, numMinutiae=0;
    int16_t packedX,packedY,x,y,angleBit,type,minuQuality;

    double angle;

    width+=(tmpl[14]<<8) + tmpl[15];
    height+=(tmpl[16]<<8) + tmpl[17];
    xPixelsPerCM+=(tmpl[18]<<8) + tmpl[19];
    yPixelsPerCM+=(tmpl[20]<<8) + tmpl[21];

    numFingerprints+=(tmpl[22]);
    fingerPosition+=tmpl[24];
    quality+=tmpl[26];
    numMinutiae+=tmpl[27];


    file <<width<<"\n";
    file <<height<<"\n";
    file <<numMinutiae<<"\n";

//    cout <<width<<endl;
//    cout <<height<<endl;
//    cout <<xPixelsPerCM<<" "<<yPixelsPerCM<<endl;
//    cout <<numFingerprints<<" "<<fingerPosition<<" "<<quality<<endl;
//    cout <<numMinutiae<<endl;

    for (int i = 28; i <28+(6*numMinutiae) ; i+=6) {

        packedX=0+(tmpl[i]<<8)+tmpl[i+1];
        packedY=0+(tmpl[i+2]<<8)+tmpl[i+3];
        angleBit=0+tmpl[i+4];
        minuQuality=0+(tmpl[i+5]);
        type = (packedX>>14) & 0x3;
        x = packedX & 0x3fff;
        y = packedY & 0x3fff;

        angle = angleBit*PI2/256.;
        angle = complimentary(angle);
        file <<x<<" "<<y<<" "<<angle<<"\n";

//        cout <<type<<" "<<x <<" "<<y<<" "<<minuQuality<<" "<<angle*(180./PI)<<endl;
//        cout <<x<<" "<<y<<" "<<angle*(180./PI)<<endl; //converts angle to degrees from radians
//        cout <<x<<" "<<y<<" "<<angle<<endl;
    }

    file.close();
}

int main(int argc, char ** argv) {

    ifstream inFile;

    size_t minSizeAllowed=34;

    if(argc != 3 || argv[1] == NULL || argv[2] == NULL) {
        printf("ISO 19794-2 2005 converter\n"
                       "Usage: %s <fmd.ist> <fmd.txt>\n"
                       "where <fmd.ist> is the file source file where fingerprint minutia data is in ISO/IEC 19794-2 2005 format\n"
                       "      <fmd.txt> is the file where to write fingerprint minutia data in text format\n", argv[0]);
        return -1;
    }


    inFile.open( argv[1], ios::in|ios::binary|ios::ate );
    size_t size = inFile.tellg();
    inFile.seekg(0, ios::beg);
    unsigned char* oData = new  unsigned char[ size ];
    inFile.read((char *) oData, size );

    if (size<minSizeAllowed){
        printf("ISO file %s is too short\n", argv[1]);
        return 11;
    }

    convertIso(oData,argv[2]);


    return 0;
}