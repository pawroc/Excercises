#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

string isPrimeGood(int n);
string isPrimeBest(int n);
void printResult(string fcnName, string msg, int count);

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    cout << "Give a number:     ";
    int number;
    cin >> number;

    cout << "isPrimeGood\n";
    cout << isPrimeGood(number) << endl;
    cout << "isPrimeBest\n";
    cout << '\n' << isPrimeBest(number) << endl;

    return 0;
}

string isPrimeGood(int n){
    int counter = 0;
    // check lower boundaries on primality
    if( n == 2 ){
        printResult(__func__, "Prime", ++counter);
        return "Prime";
    } // 1 is not prime, even numbers > 2 are not prime
    else if( n == 1 || (n & 1) == 0){
        printResult(__func__, "Not prime", ++counter);
        return "Not Prime";
    }

    // Check for primality using odd numbers from 3 to sqrt(n)
    for(int i = 3; i <= sqrt(n); i += 2){
        counter++;
        // n is not prime if it is evenly divisible by some 'i' in this range
        if( n % i == 0 ){
            printResult(__func__, "Not prime", ++counter);
            return "Not Prime";
        }
    }
    // n is prime
    printResult(__func__, "Prime", ++counter);
    return "Prime";
}

string isPrimeBest(int n) {
    int counter = 0;
    //check if n is <= 1
    if(n <= 1) {
        printResult(__func__, "Not prime", ++counter);
        return "Not prime";
    }

    //check if n is 2 or 3
    if(n <= 3) {
        printResult(__func__, "Prime", ++counter);
        return "Prime";
    }

    //check if n is divisible by 2 or 3 (and is not itself neither 2 nor 3)
    if(n % 2 == 0 || n % 3 == 0) {
        printResult(__func__, "Not prime", ++counter);
        return "Not prime";
    }

    //According to the facts that all primes can be representad as (6k +- 1)
    //and for all numbers n its divisors are looped after sqrt(n), it is
    //not necessery to check greater divisors than sqrt(n). Finally, it is
    //enough to check whether n is divisible by (6k +- 1), if so, n is not prime.
    int divisor = 5; //6*1 - 1 -> the least prime except of 2...
    while(divisor <= sqrt(n)) {
        counter++;
        if(n % divisor == 0 || n % (divisor + 2) == 0) { // divisor -> 6*k - 1; divisor + 2 -> 6*k + 1
            printResult(__func__, "Not prime", ++counter);
            return "Not prime";
        }
        divisor += 6;
    }
    printResult(__func__, "Prime", ++counter);
    return "Prime";
}

void printResult(string fcnName, string msg, int count) {
    cout << "==FUNCTION " << fcnName << "==\n\n" << msg << '\n';
    cout << "Result is got in " << count << " steps\n\n";
}
