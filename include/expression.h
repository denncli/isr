//
//  constraint_solver.hpp
//
//
//  Created by Bradley on 4/3/19.
//
//

#ifndef constraint_solver_hpp
#define constraint_solver_hpp
#include <stdio.h>
#include "String.h"
#include "vector.h"
#include "IndexInterface.h"

typedef unsigned long long Location;
typedef size_t FileOffset;// Created by Jason Setting
// Graham Eger added additional string concatenation functions on 4/2

#pragma once
#ifndef STRING_H_398
#define STRING_H_398

class String
{
public:
   String( );
   String( const char single_char );
   String( const char* toCopy );
   String( char*&& toMove );
   String( const String& toCopy );
   String( String&& toMove );
   String& operator=( const String& toCopy );
   String& operator=( String&& toMove );
   ~String();
   void RemoveWhitespace( );
   void Swap( String& toSwap );
   bool Empty( ) const;
   int Size( ) const;
   const char* CString( ) const;
   bool Compare( const String& other ) const;
   const char operator[ ] ( int index ) const;
   char& operator[ ] ( int index );

   String& operator+= ( const String& rhs );
   friend String operator+ ( String lhs, const String& rhs );
   friend String operator+ ( String lhs, const char * toCat );

   operator bool( ) const;

private:
    const static char* nullString;
    char* cstring;
    int size;
};

#endif

namespace IsrGlobals
{
   const Location IsrSentinel = 0;
   //TODO: CHange to 1
   const Location IndexStart = 1;
}

struct DocumentLocation {
    Location docStart;
    Location docEnd;
};

class Isr{
public:
   Isr();

   ~Isr();
   //Isr pointer to the end of the current doc
   Isr* docEnd;
   
   //Find next instance of a term
   virtual Location NextInstance() = 0;
   
   //Similar to nextDocument, finds the first occurrence of a term just at 'target' or later
   virtual Location SeekToLocation(Location target);
   
   //First number in the posting list of a term
   virtual Location GetCurrentLocation();

   virtual Location ResetToStart() = 0;

   virtual Location MoveAllTermsOffCurrentDocument();

   virtual void addTerm(Isr*);
   
   //Returns whatever document you're looking at
   Isr* getDocIsr();
   
   protected:
   Vector<Isr*> terms;
   Location currentLocation;
};

class IsrWord : public Isr {
public:
    IsrWord() {}
    IsrWord( String &word_in );
   void SetLocations( Vector<Location>& matchesIn );
   //    ~IsrWord( );
   
   Location NextInstance( ) override;
   Location SeekToLocation( Location seekDestination = 0 ) override;
   Location GetCurrentLocation() override;
   Location ResetToStart() override;
   //Location CurInstance() const override;
   void AddWord(String &wordIn);
   DocumentAttributes GetDocInfo();
   void SetImportance(unsigned importanceIn);
   
   
   operator bool( ) const;
   friend class IsrEndDoc;
   
private:
   bool validIsr;
   Vector<Location> matches;
   Location currentLocation;
   String word;
   unsigned nextPtr;
   unsigned importance;
   unsigned curInd;
   bool hasNextInstance();
};


class IsrOr : public Isr {
public:
   //Variable to keep track of how many terms are in 'terms' (because resize/reserve isn't implemented)
//   unsigned numOfTerms = 0;
   
   //Constructor for IsrOr, MUST be in a vector<Isr> format, otherwise it wont compile
   IsrOr(Vector<Isr*>& phrasesToInsert);
   IsrOr() {}
   virtual Location ResetToStart() override;
   Location moveTermsToSameDocument(DocumentLocation& docLocation);
   
   //Find the next instance of ANY of the words in 'terms'
   Location NextInstance() override;
   Location NextInstanceWithoutSeekToNewPage();
};

class IsrAnd : public Isr{
public:
   //Constructor for IsrAnd
   IsrAnd(Vector<Isr*>& phrasesToInsert);
   IsrAnd() {}
   virtual Location ResetToStart() override;

   //Destructor
   ~IsrAnd(){};
   
   Location NextInstance() override;
   Location NextInstanceWithoutSeekToNewPage();
   
private:
   Location moveTermsToSameDocument(DocumentLocation& docLocation);
};

class IsrPhrase : public Isr {
public:
    IsrPhrase(Vector<Isr*>& phrasesToInsert);
    IsrPhrase() {}
    virtual Location ResetToStart() override;

    ~IsrPhrase(){};
    Location NextInstance() override;
    Location NextInstanceWithoutSeekToNewPage();
};

class IsrEndDoc : public IsrWord
{
public:
   IsrEndDoc(); 
   ~IsrEndDoc();
   DocumentAttributes* GetDocInfo();
   void AddMatches(Vector<Location>& matchesIn);
   Location GetDocLength();
private:
   DocumentAttributes* docInfo;
   void saveDocInfo();
   Location currentLocation;
};

bool IsOnDoc(DocumentLocation& docLocation, Isr* isr);
void MoveDocEndToCurrentDocument(IsrEndDoc* docIsr, Isr* curIsr);
#endif /* constraint_solver_hpp */