/*
Write a program which will perform the job of moving the file from one location to another.
The source and destination path will be entered by the user.
Perform the required error checking and handle the exceptions accordingly.
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main (void)
{
    const int path = 40;//defined length of the path
    char inputFile[path];
    char outputFile[path];
    char buffer[BUFSIZ] = { '\0' } ;

    cout<<"This program moves a file and renames it. Original version is deleted. "<<endl<<
    "Both input (source) and output (destination) paths have to be given"<<endl<<
    "with filename and extension. Example: \"c:/a/a.bmp\""<<endl;
    cout<<"Input path:"<<endl;
    cin>>inputFile;
    cout<<"Output path:"<<endl;
    cin>>outputFile;

    FILE* in = fopen( inputFile, "rb" ) ;
    FILE* out = fopen( outputFile, "wb" ) ;

    if( in == NULL || out == NULL )
    {
        perror( "An error occured while opening files" ) ;
        in = out = 0 ;
        return 0;
    }
    cout<<"Input: "<<in<<", output: "<<out<<endl; //showing file handles


    while( !feof(in) )
    {
        //clearing buffer
        for( int i = 0; i < BUFSIZ; i++ )
            buffer[i] = { '\0' } ;

        fread( buffer, BUFSIZ, 1, in);

        cout<<buffer<<endl; //in case of showing file data to the console

        fwrite( buffer, BUFSIZ, 1, out ) ;

        //error checking
        if(ferror(in)){
            perror("An error occured while reading the file");
            return 0;
        }
        if(ferror(out)){
            perror("An error occured while writing to the file");
            return 0;
        }
    }

    fclose(in) ;
    fclose(out) ;

    //removing original file
    if(  remove(inputFile) )
    {
        perror( "An error occured while removing the file" );
        return 0;
    }

    cout << "\nFile successfully moved.\n" << endl;
    return 0 ;
}
