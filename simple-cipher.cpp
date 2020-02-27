#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<stdio.h>
#include<string.h>

int main(int argc, char* argv[])
{

if(argc < 4 || strcmp(argv[1] , "h") == 0)
{
std::cout << "First argument: e/d e: encryption , d: decryption" << "\nSecond argument: file name" << "\nThird argument: password" << '\n';

return 0;
}

std::string fileExtension;

if(argv[1][0]=='e'&&argv[1][1]=='\0')
fileExtension=".enc";

else if(argv[1][0]=='d'&&argv[1][1]=='\0')
fileExtension=".dec";

else
{std::cout<<"ERROR invalid argument 1; can be 'e' : encryption, 'd' : decryption)"<<'\n';
return 0;}

std::fstream inFile;
inFile.open(argv[2],std::ios::in);

if(EOF==inFile.peek())
{std::cout<<"ERROR invalid argument 2; empty file"<<'\n';
return 0;}

char *password;
password = argv[3];

std::istringstream is;
is.str(argv[2]);

std::string outFileNameS;
outFileNameS=is.str()+fileExtension;

char * outFileName;
outFileName=new char[outFileNameS.length()];

for(int i=0;i<outFileNameS.length();i++)
{outFileName[i]=outFileNameS[i];}

std::fstream outFile;
outFile.open(outFileName,std::ios::out);

int bufferSize = strlen(argv[3]);

char * buffer = new char[bufferSize+1];

if(argv[1][0]=='e')
{
char * defaultBuffer = new char[bufferSize+1];

for(int i=0;i<bufferSize;i++)
{defaultBuffer[i]='0';}

int addedChars;

while(inFile.peek()!=EOF)
{
inFile.read((char*)&buffer[0],bufferSize);
buffer[bufferSize]='\0';

for(int i=0;i<bufferSize;i++)
{/*character addition*/
addedChars=buffer[i]+password[i];
addedChars%=256;
buffer[i]=addedChars;
/*XOR*/
buffer[i]=buffer[i]^password[i];
}

outFile<<buffer;

strcpy(buffer,defaultBuffer);
}
}

else
{
int subtractedChars;

while(inFile.peek()!=EOF)
{
inFile.read((char*)&buffer[0],bufferSize);
buffer[bufferSize]='\0';

for(int i=0;i<bufferSize;i++)
{
/*reversing XOR*/
buffer[i]=buffer[i]^password[i];
/*reversing addition*/
subtractedChars=buffer[i]-password[i];

if(subtractedChars<0)
subtractedChars+=256;

buffer[i]=subtractedChars;
}

outFile<<buffer;
}
}

std::cout<<"Done; saved to: "<<outFileName<<'\n';

return 1;
}

