// Solution to the Annual Return Problem
//
// File:	annual.cc
// Authors:	Bob Walton (walton@seas.harvard.edu)
// Date:	Mon Jul 13 04:10:15 EDT 2020
//
// The authors have placed this program in the public
// domain; they make no warranty and accept no liability
// for this program.

#include <iostream>
using namespace std;
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>

// !!** lines are for debugging.
//
// Asserts are judge's checks that data is valid, and
// are not part of the solution.

int debug = false;
#define dout    if ( debug ) cout
#define dprintf if ( debug ) printf

#define FOR1(i,n) for ( int i = 1; i <= (n); ++ i )

const int MAX_LINE = 80;
const int MAX_N = 30;
const int MAX_Y = 9999;
const double MAX_V = 1e6;

char title[MAX_LINE+2];
int y[MAX_N+2];
double v[MAX_N+2];
int n = 1;

// Compute C(r,k) = r^k.  For debugging.
//
double C ( double r, int k )
{
    double c = 1;
    FOR1 ( i, k ) c *= r;
    return c;
}

// Compute B(r,k) such that B^k = r.
// Therefore log ( B ) * k = log ( r ).
//
double B ( double r, int k )
{
    double logr = log ( r );
    double logB = logr / k;
    return exp ( logB );
}
    
double A ( int i, int j )
{
    double b = B ( v[j]/v[i], y[j] - y[i] );
    return 100 * ( b - 1 );
}

// The best way to debug this is to run the computation
// in reverse as a check.  So this is for debugging.
//
void check ( int i, int j )
{
    double r = v[j]/v[i];
    int k = y[j] - y[i];
    double a = A ( i, j );
    double error = r - C ( 1 + a/100, k );
    assert ( fabs ( error ) < 1e-9 );
}

int main ( int argc, char * argv[] )
{
    debug = ( argc > 1 );

    cin.getline ( title, sizeof ( title ) );
    assert ( cin.good() );
    assert ( strlen ( title ) <= MAX_LINE );

    cout << "!!** " << title << endl;
        // Just for debugging convenience.

    while ( cin >> y[n] >> v[n] )
    {
        assert ( cin.get() == '\n' );
	assert ( n <= MAX_N );
	assert ( 0 < y[n] && y[n] <= MAX_Y );
	assert ( 0 < v[n] && v[n] <= MAX_V );

	cout << "!!** " << y[n]
	     << " " << v[n] << endl;
	    // Just for debugging convenience.

	++ n;
    }
    -- n;

    cout << title << endl;

    printf ( "      " );
    FOR1 ( i, n-1 ) printf ( "%6d", y[i] );
    printf ( "\n" );
    FOR1 ( j, n-1 )
    {
        printf ( "%6d", y[j+1] );
	FOR1 ( i, j ) printf ( "%6.2f", A(i,j+1) );
	printf ( "\n" );
    }

    FOR1 ( j, n-1 ) FOR1 ( i, j ) check ( i, j+1 );

    return 0;
}
