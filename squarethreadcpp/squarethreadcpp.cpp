//#define VERBOSE
//#define SQUARE
#define REPORT

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#ifdef VERBOSE
#include <cmath>
#include <string>
#endif
using namespace std::chrono;
using namespace std;
std::mutex mlock;
static const uint_fast32_t target = 24;
static const uint_fast32_t gnumthreads = 12;
static uint_fast32_t matches = 0;
static uint_fast32_t tosolve;
static long long cycles = 0;
static uint_fast32_t ps[100] = {0};
#ifdef VERBOSE
class comma_numpunct : public std::numpunct<char>
{protected:
	virtual char do_thousands_sep() const{return ',';}
	virtual std::string do_grouping() const{return "\03";}};
std::locale comma_locale(std::locale(), new comma_numpunct());
#endif 
bool isPerfectSquare(uint_fast32_t x)
{
	if (x >= 0) {
		long long sr = sqrt(x);
		return (sr * sr == x);
	}
	return false;
}
static void CountUp(uint_fast32_t iTarget, uint_fast32_t nStep, uint_fast32_t iStart, uint_fast32_t iOffset)
{
#ifdef VERBOSE
	long long tcps = 0;
	int percentComplete = 0;
	double minsleft = 0;
	double secondsleft = 0;
	auto minselapsed = high_resolution_clock::now();
	std::chrono::duration<double> diff;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
#endif 
	long long tcycles = 0;
	long tmatches = 0;
	uint_fast32_t iStep = gnumthreads;
	uint_fast32_t a = iStart + iOffset;
	uint_fast32_t b = iStart;
	uint_fast32_t c = iStart;
	uint_fast32_t d = iStart;
	uint_fast32_t e = iStart;
	uint_fast32_t f = iStart;
	uint_fast32_t g = iStart;
	uint_fast32_t h = iStart;
	uint_fast32_t i = iStart;
	uint_fast32_t bestsquares[10] = { 0 };
	uint_fast32_t squares = 0;
loophead:
	if (a == b) { goto notequal; }
#ifndef SQUARE
	if (a + b + c != d + e + f) { goto notequal; }
	if (a + b + c != g + h + i) { goto notequal; }
	if (a + b + c != a + d + g) { goto notequal; }
	if (a + b + c != b + e + h) { goto notequal; }
	if (a + b + c != c + f + i) { goto notequal; }
	if (a + b + c != a + e + i) { goto notequal; }
	if (a + b + c != c + e + g) { goto notequal; }
#endif
#ifdef SQUARE
	if (ps[b] + ps[e] + ps[g] != ps[d] + ps[e] + ps[f]) { goto notequal; }
	//if (ps[a] + ps[b] + ps[c] != ps[g] + ps[h] + ps[i]) { goto notequal; }
	//if (ps[a] + ps[b] + ps[c] != ps[a] + ps[d] + ps[g]) { goto notequal; }
	//if (ps[a] + ps[b] + ps[c] != ps[b] + ps[e] + ps[h]) { goto notequal; }
	//if (ps[a] + ps[b] + ps[c] != ps[c] + ps[f] + ps[i]) { goto notequal; }
	// diagonals
	if (ps[b] + ps[e] + ps[g] != ps[a] + ps[e] + ps[i]) { goto notequal; }
	if (ps[b] + ps[e] + ps[g] != ps[c] + ps[e] + ps[g]) { goto notequal; }
	//matches++;
#endif
	// compare (a) with cells
	if (a == b) { goto notequal; }
	if (a == c) { goto notequal; }
	if (a == d) { goto notequal; }
	if (a == e) { goto notequal; }
	if (a == f) { goto notequal; }
	if (a == g) { goto notequal; }
	if (a == h) { goto notequal; }
	if (a == i) { goto notequal; }
	// compare (b) with cells
	if (b == c) { goto notequal; }
	if (b == d) { goto notequal; }
	if (b == e) { goto notequal; }
	if (b == f) { goto notequal; }
	if (b == g) { goto notequal; }
	if (b == h) { goto notequal; }
	if (b == i) { goto notequal; }
	// compare (c) with cells
	if (c == d) { goto notequal; }
	if (c == e) { goto notequal; }
	if (c == f) { goto notequal; }
	if (c == g) { goto notequal; }
	if (c == h) { goto notequal; }
	if (c == i) { goto notequal; }
	// compare (d) with cells
	if (d == e) { goto notequal; }
	if (d == f) { goto notequal; }
	if (d == g) { goto notequal; }
	if (d == h) { goto notequal; }
	if (d == i) { goto notequal; }
	// compare (e) with cells
	if (e == f) { goto notequal; }
	if (e == g) { goto notequal; }
	if (e == h) { goto notequal; }
	if (e == i) { goto notequal; }
	// compare (f) with cells
	if (f == g) { goto notequal; }
	if (f == h) { goto notequal; }
	if (f == i) { goto notequal; }
	// compare (g) with cells
	if (g == h) { goto notequal; }
	if (g == i) { goto notequal; }
	// compare (h) with cells
	if (h == i) { goto notequal; }	
#ifdef REPORT
	mlock.lock();
	uint_fast32_t n = 0;
	uint_fast32_t m = 0;
	std::cout << a << "." << b << "." << c << "\n";
	std::cout << d << "." << e << "." << f << "\n";
	std::cout << g << "." << h << "." << i << "\n";
	if (c > e) { m = c - e; }
	else { m = e - c; }
	if (a > e) { n = a - e; }
	else { n = e - a; }
	std::cout << "n: " << n << " m: " << m << " s: " << e*3 << "\n";
	if (isPerfectSquare(a)) { std::cout << "a:" << sqrt(a) << "^2"; squares++; }
	if (isPerfectSquare(b)) { std::cout << "b:" << sqrt(b) << "^2"; squares++; }
	if (isPerfectSquare(c)) { std::cout << "c:" << sqrt(c) << "^2"; squares++; }
	if (isPerfectSquare(d)) { std::cout << "d:" << sqrt(d) << "^2"; squares++; }
	if (isPerfectSquare(e)) { std::cout << "e:" << sqrt(e) << "^2"; squares++; }
	if (isPerfectSquare(f)) { std::cout << "f:" << sqrt(f) << "^2"; squares++; }
	if (isPerfectSquare(g)) { std::cout << "g:" << sqrt(g) << "^2"; squares++; }
	if (isPerfectSquare(h)) { std::cout << "h:" << sqrt(h) << "^2"; squares++; }
	if (isPerfectSquare(i)) { std::cout << "i:" << sqrt(i) << "^2"; squares++; }
	if (squares > bestsquares[0]) {
		bestsquares[0] = squares;
		bestsquares[1] = a;
		bestsquares[2] = b;
		bestsquares[3] = c;
		bestsquares[4] = d;
		bestsquares[5] = e;
		bestsquares[6] = f;
		bestsquares[7] = g;
		bestsquares[8] = h;
		bestsquares[9] = i;
	}
	squares = 0;
	std::cout << "\n\n";
	mlock.unlock();
#endif
	tmatches++;
	mlock.lock();
	matches += 1;
#ifdef VERBOSE
	try {
		percentComplete = ((double)matches / (double)tosolve) * 100;
		std::cout << "Solved " << matches << " of " << tosolve << " | n=" << (a + b + c) << " | tar=" << iTarget << " | thr=" << gnumthreads << "\n";
		if (percentComplete > 1 && percentComplete < 101) {
			string pleft(percentComplete / 2, '=');
			string pright(50 - (percentComplete / 2), '-');
			std::cout << "[" << pleft << pright << "] " << percentComplete << "% \n"; }
		minselapsed = high_resolution_clock::now();
		diff = minselapsed - t1;
		tcps = (tcycles / diff.count());
		secondsleft = ((pow(target, 9) / gnumthreads) - tcycles) / tcps;
		tcps = tcps * gnumthreads;
		minsleft = secondsleft / 60;
		std::cout << "Cycles p/s     : " << tcps << "\n";
		std::cout << "Time elapsed   : " << diff.count() << "s (" << diff.count() / 60 << "m )\n";
		std::cout << "Time remaining : " << secondsleft << " s (" << minsleft << "m )\n\n";	}
	catch (...) { std::cout << "Something got all fucked up and shit.\n"; }
#endif

	mlock.unlock();
notequal:
	tcycles += 1;
	a += iStep;
	if (a <= iTarget) { goto loophead; }
	a = (a % iStep) + 1;
	b += 1;
	if (b <= iTarget) { goto loophead; }
	b = iStart;
	c += 1;
	if (c <= iTarget) { goto loophead; }
	c = iStart;
	d += 1;
	if (d <= iTarget) { goto loophead; }
	d = iStart;
	e += 1;
	if (e <= iTarget) { goto loophead; }
	e = iStart;
	f += 1;
	if (f <= iTarget) { goto loophead; }
	f = iStart;
	g += 1;
	if (g <= iTarget) { goto loophead; }
	g = iStart;
	h += 1;
	if (h <= iTarget) { goto loophead; }
	h = iStart;
	i += 1;
	if (i <= iTarget) { goto loophead; }
	mlock.lock();
	cycles += tcycles;
	mlock.unlock();
	std::cout << "Thread [" << iOffset << "] " << cycles << " cycles\n";
#ifdef REPORT
	mlock.lock();
	std::cout << "--------\n";
	std::cout << "BEST: "<< bestsquares[0] <<"\n";
	std::cout << bestsquares[1] << "." << bestsquares[2] << "." << bestsquares[3] << "\n";
	std::cout << bestsquares[4] << "." << bestsquares[5] << "." << bestsquares[6] << "\n";
	std::cout << bestsquares[7] << "." << bestsquares[8] << "." << bestsquares[9] << "\n";
	std::cout << "--------\n";
	mlock.unlock();
#endif
	return;	}

int main() {
#ifdef VERBOSE
	std::cout.imbue(comma_locale);
#endif
	uint_fast32_t t = (target + 1);
	switch (t % 12) {
	case 0: case 2: case 6: case 8: tosolve = ((t * t * t) - 16 * t * t + 76 * t - 96) / 6;	break;
	case 1: tosolve = ((t * t * t) - 16 * t * t + 73 * t - 58) / 6;	break;
	case 3: case 11: tosolve = ((t * t * t) - 16 * t * t + 73 * t - 102) / 6; break;
	case 4: case 10: tosolve = ((t * t * t) - 16 * t * t + 76 * t - 112) / 6; break;
	case 5: case 9: tosolve = ((t * t * t) - 16 * t * t + 73 * t - 90) / 6;	break;
	case 7: tosolve = ((t * t * t) - 16 * t * t + 73 * t - 70) / 6;	}

	for (uint_fast32_t i = 0; i < 100; i++) { ps[i] = i * i; }

	std::cout << "Threads: " << gnumthreads << "\n";
	std::cout << "Target : " << target << "\n";
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	std::thread thr[gnumthreads];
	for (uint_fast32_t i = 0; i < gnumthreads; i++) { thr[i] = std::thread(CountUp, target, 1, 1, i); }
	for (uint_fast32_t i = 0; i < gnumthreads; i++) { thr[i].join(); }

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> total_time = duration_cast<duration<double>>(t2 - t1);

	std::cout << "\nCycles     : " << cycles << "\n";
	std::cout << "Matches    : " << matches << "\n";
	std::cout << "Total time : " << total_time.count() << " s\n";
	std::cout << "Speed      : " << pow(target, 9) / total_time.count() << "\n";
	return 0;
}