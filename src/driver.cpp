/*
 * driver.cpp
 *
 * Driver for the math parser program
 *
 * Lab3: You do not have to modify this file, but you may choose to do so
 *
 * If you do, note that your output is expected to match ours
 */

#include <iostream>
#include "expression.h"
#include "parser.h"

using std::cout;
using std::endl;

int main( )
{
    std::string input;
    input = "quick brown fox";
    //while(std::getline( std::cin, input )) {
    while(1) {
        Parser parser( input );
        cout << "parsed";
        Isr *expr = parser.Parse( );
        if ( expr  && parser.fullParsed())
        {
            expr->ResetToStart();
            cout << "hello";
            std::cout << expr->NextInstance( ) << "\n";
            cout << "hello";
            std::cout << expr->NextInstance( ) << "\n";
            cout << "hello";
            //for(int i = 0; i < expr->queries.size(); i++) {
              //  for(int j = 0; j < expr->queries[i]->queries.size(); j++) {
                //    std::cout << expr->queries[i]->queries[j] << "\n";
                //}
                std::cout << "\n";
            //}
            
            delete expr;
        }
        else
        {
            help_message();
        }
        
        cout << expr->NextInstance();
        cout << expr->NextInstance();
        
    }
}
