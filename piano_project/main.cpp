#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <array>

using namespace std;

bool isNoteLetter(char c)  //Function tests if a note is a note letter from 'A' through 'G'
{
    if(c=='A' || c=='B' || c=='C' || c=='D' || c=='E' || c=='F' || c=='G')
    {
        return true;
    }
    return false;
}

bool isAccidentalSign(char c)  //Function tests if a note is an accidental sign, '#' or 'b'
{
    if(c=='#' || c=='b')
    {
        return true;
    }
    return false;
}

bool isAcceptableCharacter(char c) //Function tests if a character is acceptable
{
    if(isNoteLetter(c)==false && isAccidentalSign(c)==false && c!='/' && isdigit(c)==false)
    {
        return false;
    }
    return true;
}

bool isNote(string tune) //Function tests entire string to see if each character and note are OK, without checking slashes
{
    if(tune=="") //If the tune is empty, return true
    {
        return true;
    }
    for(int k=0; k!=tune.size(); k++) //If there is ever an unacceptable character, return false
    {
        if(isAcceptableCharacter(tune[k])==false)
        {
            return false;
        }
    }

    if((isdigit(tune[0]) || isAccidentalSign(tune[0]) || isNoteLetter(tune[0])==false) && tune[0]!='/')
    {
        return false;
    }
    for(int k=0; k!=tune.size(); k++)
    {
        if(isalpha(tune[k]) && isNoteLetter(tune[k])==false && tune[k]!='b')
        {
            return false;
        }
        if((k+1)!=tune.size())
        {
            if(isalpha(tune[k]) && (tune[k+1]=='#' || tune[k+1]=='b'))
            {
                
            }
            if(isalpha(tune[k]) && isdigit(tune[k+1]))
            {
                
            }
        }
        if((k+2)!=tune.size())
        {
            if(isalpha(tune[k]) && isdigit(tune[k+1]) && isAccidentalSign(tune[k+2]))
            {
                return false;
            }
        }
        if(isalpha(tune[k]) && isNoteLetter(tune[k]) && isAccidentalSign(tune[k+1]) && isAccidentalSign(tune[k+2]))
        {
            return false;
        }
        if(isalpha(tune[k]) && isNoteLetter(tune[k]) && isdigit(tune[k+1]) && isdigit(tune[k+2]))
        {
            return false;
        }
    }
    return true;
}

bool isWellFormedTune(string tune)
{
    if(isNote(tune)==false)
    {
        return false;
    }
    if(tune=="")
    {
        return true;
    }
    if(tune[tune.size()-1]!='/')
    {
        return false;
    }
    char secondToLast=tune[tune.size()-2];
    if(isAcceptableCharacter(secondToLast) && tune[tune.size()-1]!='/')
    {
        return false;
    }
    
    return true;
}

bool isPlayableNote(string tune)
{
    if(tune=="")
    {
        return true;
    }
    if(isWellFormedTune(tune)==false)
    {
        return false;
    }
    
    for(int k=0; k!=tune.size(); k++)
    {
        //Test if octaves are in the right range
        if(isdigit(tune[k]))
           {
               //Test for Cb2
               if(tune.find("Cb2")!=std::string::npos)
               {
                   return false;
               }
               if(k-2>=0)
               {
                   if(tune[k]<'2' && tune.substr(k-2, 3)!="B#1")
                   {
                       return false;
                   }
               }
               if(tune.find("C#6")!=std::string::npos || tune.find("Db6")!=std::string::npos || tune.find("D6")!=std::string::npos || tune.find("D#6")!=std::string::npos || tune.find("Eb6")!=std::string::npos || tune.find("E6")!=std::string::npos || tune.find("F6")!=std::string::npos || tune.find("F#6")!=std::string::npos || tune.find("Gb6")!=std::string::npos || tune.find("G6")!=std::string::npos || tune.find("G#6")!=std::string::npos || tune.find("Ab6")!=std::string::npos || tune.find("A6")!=std::string::npos || tune.find("A#6")!= std::string::npos || tune.find("Bb6")!=std::string::npos || tune.find("B6")!=std::string::npos || tune.find("B#6")!=std::string::npos)
               {
                   return false;
               }

               if(tune[k]>'6')
               {
                   return false;
               }
           }
    }
    return true;
}

int playableNoteBadLocation(string tune)
{
    int beatCounter=1;
    
    for(int k=0; k!=tune.size(); k++)
    {
        if(tune[k]=='C' && tune[k+1]=='b' && tune[k+2]=='2')
        {
            return beatCounter;
        }
        
        if(isdigit(tune[k]) && tune[k]<'2' && tune.substr(k-2, 3)!="B#1")
        {
            return beatCounter;
        }
        
        if(isalpha(tune[k]) && isdigit(tune[k+1]))
        {
            if(tune[k+1]<'2' || tune[k+1]>'6')
            {
                return beatCounter;
            }
        }
        if(isalpha(tune[k]) && isAccidentalSign(tune[k+1]) && isdigit(tune[k+2]))
        {
            if(tune[k+2]<'2' || tune[k+2]>'6')
            {
                return beatCounter;
            }
            
        }
        if(isalpha(tune[k]) && tune[k+1]==6 && tune[k]!='C')
        {
            return beatCounter;
        }
        if(isalpha(tune[k]) && isAccidentalSign(tune[k+1]) && tune[k+2]=='6')
        {
            return beatCounter;
        }
        if(tune[k]=='/')
        {
            beatCounter++;
        }

    }
    return beatCounter;
}

bool isTuneWellFormed(string tune)
{
    return isWellFormedTune(tune);
}

//*************************************
//  translateNote
//*************************************

// Given an octave number, a note letter, and an accidental sign, return
// the character that the indicated note translates to if it is playable.
// Return a space character if it is not playable.
//
// First parameter:   the octave number (the integer 4 is the number of the
//                    octave that starts with middle C, for example).
// Second parameter:  an upper case note letter, 'A' through 'G'
// Third parameter:   '#', 'b', or ' ' (meaning no accidental sign)
//
// Examples:  translateNote(4, 'A', ' ') returns 'Q'
//            translateNote(4, 'A', '#') returns '%'
//            translateNote(4, 'H', ' ') returns ' '

char translateNote(int octave, char noteLetter, char accidentalSign)
{
    // This check is here solely to report a common CS 31 student error.
    if (octave > 9)
    {
        cerr << "********** translateNote was called with first argument = "
        << octave << endl;
    }
    
    // Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
    //      to -1, 0,   1,   2,   3, ...,  11, 12
    
    int note;
    switch (noteLetter)
    {
        case 'C':  note =  0; break;
        case 'D':  note =  2; break;
        case 'E':  note =  4; break;
        case 'F':  note =  5; break;
        case 'G':  note =  7; break;
        case 'A':  note =  9; break;
        case 'B':  note = 11; break;
        default:   return ' ';
    }
    switch (accidentalSign)
    {
        case '#':  note++; break;
        case 'b':  note--; break;
        case ' ':  break;
        default:   return ' ';
    }
    
    // Convert ..., A#1, B1, C2, C#2, D2, ... to
    //         ..., -2,  -1, 0,   1,  2, ...
    
    int sequenceNumber = 12 * (octave - 2) + note;
    
    string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
    if (sequenceNumber < 0  ||  sequenceNumber >= keymap.size())
        return ' ';
    return keymap[sequenceNumber];
}

int translateTune(string tune, string& instructions, int& badBeat)
{
    if(isWellFormedTune(tune)==false)
    {
        return 1;
    }
    else if(isWellFormedTune(tune)==true && isPlayableNote(tune)==false)
    {
        badBeat=playableNoteBadLocation(tune);
        return 2;
    }
    
    //If isWellFormedTune is true and isPlayableNote is true
    instructions="";
    if(tune[0]=='/')
    {
        instructions+=" ";
    }
    
    string beatSubstring="";
    int lettersPerBeatForChordPosition=0;
    
    for(int k=0; k!=tune.size(); k++)
    {
        if(isalpha(tune[k]) && isAccidentalSign(tune[k+1]) && isdigit(tune[k+2]))
        {
            beatSubstring+=translateNote(tune[k+2] - '0', tune[k], tune[k+1]);
            lettersPerBeatForChordPosition++;
        }
        else if(isalpha(tune[k]) && isAccidentalSign(tune[k+1]))
        {
            beatSubstring+=translateNote(4, tune[k], tune[k+1]);
            lettersPerBeatForChordPosition++;
        }
        else if(isalpha(tune[k]) && isdigit(tune[k+1]))
        {
            beatSubstring+=translateNote(tune[k+1] - '0', tune[k], ' ');
            lettersPerBeatForChordPosition++;
        }
        else if(isalpha(tune[k]))
        {
            beatSubstring+=translateNote(4, tune[k], ' ');
            lettersPerBeatForChordPosition++;
        }
        if(tune[k]=='/' && tune[k-1]=='/')
        {
            beatSubstring+=" ";
            instructions+=beatSubstring;
            beatSubstring="";
        }
        else if(tune[k]=='/' && lettersPerBeatForChordPosition>1)
        {
            beatSubstring.insert(0, "[");
            beatSubstring+="]";
            instructions+=beatSubstring;
            beatSubstring="";
            lettersPerBeatForChordPosition=0;
        }
        else if(tune[k]=='/' && lettersPerBeatForChordPosition<=1)
        {
            instructions+=beatSubstring;
            beatSubstring="";
            lettersPerBeatForChordPosition=0;
        }
    }
    
    return 0;
}


int main(int argc, const char * argv[]) {
    string input="";
    do
    {
        cout << "Please enter a tune to be tested: ";
        getline(cin, input);
        string noteSequence=input;
        cout << "Testing bool isTuneWellFormed(string tune): " << isTuneWellFormed(input) << endl;
        cout << "Testing isPlayableNote: " << isPlayableNote(noteSequence) << endl;
        string instructions;
        int badBeat;
        if(isWellFormedTune(noteSequence)==true && isPlayableNote(noteSequence)==false)
        {
            cout << "badBeat location: " << playableNoteBadLocation("noteSequence") << endl;
        }
        cout << "Testing translateTune: " << translateTune(noteSequence, instructions, badBeat) << endl;
        cout << instructions << endl;
        if(instructions=="[,SL] G @KL G @KL G @KL G @K[L,S] G JKL G JKL G JKL G JK[,SGL] G @KL G @K[B.H] S 0GH S 0GH S 0GH S 0G[5A0K] 0 @HK 0 [,@]HG 90G A 90G A 90G A 90[,SGLEU] [GLE] [7@][AK][SL] [,SGK] [@&][KY][B.SHR] [SL] [0%][GE][HR] [SL] [0%][GE][HR] [SL] [0%][GE][HR] [SL] [0%][GE][5A0K%Y] ")
        {
            cout << "It worked!" << endl;
        }
    } while(input!="n");
    return 0;
}