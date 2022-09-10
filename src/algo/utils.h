#ifndef UTILS_H
#define UTILS_H

#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC

typedef signed char        s8;
typedef unsigned char      u8;
typedef short              s16;
typedef unsigned short     u16;
typedef int                s32;
typedef unsigned int       u32;
typedef long long          s64;
typedef unsigned long long u64;

typedef float			   r32;
typedef double			   r64;

#include <vector>
#include <array>

#define vec_s32 std::vector<int>
#define vec_s64 std::vector<long long>;
#define vec_u32 std::vector<unsigned int>;
#define vec_u64 std::vector<unsigned long long>;
#define vec_r32 std::vector<float>;
#define vec_r64 std::vector<double>;

#define arr_s32(N) std::array<int, N>
#define arr_s64(N) std::array<long long, N>
#define arr_u32(N) std::array<unsigned int, N>
#define arr_u64(N) std::array<unsigned long long, N>
#define arr_r32(N) std::array<float, N>
#define arr_r64(N) std::array<double, N>

#include <iostream>

template<typename T>
__forceinline void Print(const T& x) {
	std::cout << x << std::endl;
}

template<typename T>
__forceinline void PartialPrint(const T& x) {
	std::cout << x << " ";
}

__forceinline void Endl(void) {
	Print("");
}

template<typename T>
__forceinline void Print1DArray(const T& arr) {
	for (const auto& e : arr)
		PartialPrint(e);
	Endl();
}

template<typename T>
constexpr __forceinline T Max(const T a, const T b) {
	return( a < b ? b : a );
}
template<typename T>
constexpr __forceinline T Min(const T a, const T b) {
	return( a < b ? a : b );
}

#endif // !UTILS_H

