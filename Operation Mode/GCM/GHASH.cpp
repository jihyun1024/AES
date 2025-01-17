﻿// GHASH.cpp
#include "HexByte.h"

//----------------------------------------------------
// 상수 R0[], R1[]: Make_GHASH_const_R0R1() 에서 생성한 코드임
byte R0[256] = {
0x00, 0x01, 0x03, 0x02, 0x07, 0x06, 0x04, 0x05, 0x0e, 0x0f, 0x0d, 0x0c, 0x09, 0x08, 0x0a, 0x0b,
0x1c, 0x1d, 0x1f, 0x1e, 0x1b, 0x1a, 0x18, 0x19, 0x12, 0x13, 0x11, 0x10, 0x15, 0x14, 0x16, 0x17,
0x38, 0x39, 0x3b, 0x3a, 0x3f, 0x3e, 0x3c, 0x3d, 0x36, 0x37, 0x35, 0x34, 0x31, 0x30, 0x32, 0x33,
0x24, 0x25, 0x27, 0x26, 0x23, 0x22, 0x20, 0x21, 0x2a, 0x2b, 0x29, 0x28, 0x2d, 0x2c, 0x2e, 0x2f,
0x70, 0x71, 0x73, 0x72, 0x77, 0x76, 0x74, 0x75, 0x7e, 0x7f, 0x7d, 0x7c, 0x79, 0x78, 0x7a, 0x7b,
0x6c, 0x6d, 0x6f, 0x6e, 0x6b, 0x6a, 0x68, 0x69, 0x62, 0x63, 0x61, 0x60, 0x65, 0x64, 0x66, 0x67,
0x48, 0x49, 0x4b, 0x4a, 0x4f, 0x4e, 0x4c, 0x4d, 0x46, 0x47, 0x45, 0x44, 0x41, 0x40, 0x42, 0x43,
0x54, 0x55, 0x57, 0x56, 0x53, 0x52, 0x50, 0x51, 0x5a, 0x5b, 0x59, 0x58, 0x5d, 0x5c, 0x5e, 0x5f,
0xe1, 0xe0, 0xe2, 0xe3, 0xe6, 0xe7, 0xe5, 0xe4, 0xef, 0xee, 0xec, 0xed, 0xe8, 0xe9, 0xeb, 0xea,
0xfd, 0xfc, 0xfe, 0xff, 0xfa, 0xfb, 0xf9, 0xf8, 0xf3, 0xf2, 0xf0, 0xf1, 0xf4, 0xf5, 0xf7, 0xf6,
0xd9, 0xd8, 0xda, 0xdb, 0xde, 0xdf, 0xdd, 0xdc, 0xd7, 0xd6, 0xd4, 0xd5, 0xd0, 0xd1, 0xd3, 0xd2,
0xc5, 0xc4, 0xc6, 0xc7, 0xc2, 0xc3, 0xc1, 0xc0, 0xcb, 0xca, 0xc8, 0xc9, 0xcc, 0xcd, 0xcf, 0xce,
0x91, 0x90, 0x92, 0x93, 0x96, 0x97, 0x95, 0x94, 0x9f, 0x9e, 0x9c, 0x9d, 0x98, 0x99, 0x9b, 0x9a,
0x8d, 0x8c, 0x8e, 0x8f, 0x8a, 0x8b, 0x89, 0x88, 0x83, 0x82, 0x80, 0x81, 0x84, 0x85, 0x87, 0x86,
0xa9, 0xa8, 0xaa, 0xab, 0xae, 0xaf, 0xad, 0xac, 0xa7, 0xa6, 0xa4, 0xa5, 0xa0, 0xa1, 0xa3, 0xa2,
0xb5, 0xb4, 0xb6, 0xb7, 0xb2, 0xb3, 0xb1, 0xb0, 0xbb, 0xba, 0xb8, 0xb9, 0xbc, 0xbd, 0xbf, 0xbe };
byte R1[256] = {
0x00, 0xc2, 0x84, 0x46, 0x08, 0xca, 0x8c, 0x4e, 0x10, 0xd2, 0x94, 0x56, 0x18, 0xda, 0x9c, 0x5e,
0x20, 0xe2, 0xa4, 0x66, 0x28, 0xea, 0xac, 0x6e, 0x30, 0xf2, 0xb4, 0x76, 0x38, 0xfa, 0xbc, 0x7e,
0x40, 0x82, 0xc4, 0x06, 0x48, 0x8a, 0xcc, 0x0e, 0x50, 0x92, 0xd4, 0x16, 0x58, 0x9a, 0xdc, 0x1e,
0x60, 0xa2, 0xe4, 0x26, 0x68, 0xaa, 0xec, 0x2e, 0x70, 0xb2, 0xf4, 0x36, 0x78, 0xba, 0xfc, 0x3e,
0x80, 0x42, 0x04, 0xc6, 0x88, 0x4a, 0x0c, 0xce, 0x90, 0x52, 0x14, 0xd6, 0x98, 0x5a, 0x1c, 0xde,
0xa0, 0x62, 0x24, 0xe6, 0xa8, 0x6a, 0x2c, 0xee, 0xb0, 0x72, 0x34, 0xf6, 0xb8, 0x7a, 0x3c, 0xfe,
0xc0, 0x02, 0x44, 0x86, 0xc8, 0x0a, 0x4c, 0x8e, 0xd0, 0x12, 0x54, 0x96, 0xd8, 0x1a, 0x5c, 0x9e,
0xe0, 0x22, 0x64, 0xa6, 0xe8, 0x2a, 0x6c, 0xae, 0xf0, 0x32, 0x74, 0xb6, 0xf8, 0x3a, 0x7c, 0xbe,
0x00, 0xc2, 0x84, 0x46, 0x08, 0xca, 0x8c, 0x4e, 0x10, 0xd2, 0x94, 0x56, 0x18, 0xda, 0x9c, 0x5e,
0x20, 0xe2, 0xa4, 0x66, 0x28, 0xea, 0xac, 0x6e, 0x30, 0xf2, 0xb4, 0x76, 0x38, 0xfa, 0xbc, 0x7e,
0x40, 0x82, 0xc4, 0x06, 0x48, 0x8a, 0xcc, 0x0e, 0x50, 0x92, 0xd4, 0x16, 0x58, 0x9a, 0xdc, 0x1e,
0x60, 0xa2, 0xe4, 0x26, 0x68, 0xaa, 0xec, 0x2e, 0x70, 0xb2, 0xf4, 0x36, 0x78, 0xba, 0xfc, 0x3e,
0x80, 0x42, 0x04, 0xc6, 0x88, 0x4a, 0x0c, 0xce, 0x90, 0x52, 0x14, 0xd6, 0x98, 0x5a, 0x1c, 0xde,
0xa0, 0x62, 0x24, 0xe6, 0xa8, 0x6a, 0x2c, 0xee, 0xb0, 0x72, 0x34, 0xf6, 0xb8, 0x7a, 0x3c, 0xfe,
0xc0, 0x02, 0x44, 0x86, 0xc8, 0x0a, 0x4c, 0x8e, 0xd0, 0x12, 0x54, 0x96, 0xd8, 0x1a, 0x5c, 0x9e,
0xe0, 0x22, 0x64, 0xa6, 0xe8, 0x2a, 0x6c, 0xae, 0xf0, 0x32, 0x74, 0xb6, 0xf8, 0x3a, 0x7c, 0xbe };
//----------------------------------------------------

// GF(2^128) 데이터 = p[16] = p0 p1 ... p127 = [p0...p7] [p8... p15] ...
// p(x) = p0 + p1*x + p2*x^2 + ... + p127*x^127
// m(x) = 1 + x + x^2 + x^7 + x^127 --- 원시다항식 
// x*p(x) = p0*x + p1*x^2 + ... + p126*x^127 + p127*x^128
//        = p0*x + p1*x^2 + ... + p126*x^127 + p127*(1+x+x^2+x^7)
// = [0p0...p6] [p7...p14] ... [p119...p126] xor p127*[1110 0001][0]...[0]
// [1110 0001] = 0xe1
// p(x) ---> p(x)*x 로 업데이트 
void GF128_xtime(byte p[16]) {
	byte msb; // b127 최고차항의 계수
	msb = (byte)(p[15] & 0x01); // p127
	for (int i = 15; i > 0; i--) { // p[15] p[14]... p[0]
		//[.... a] [bcde fghi] [...] ==> [...] [abcd efgh] [...]
		p[i] = (p[i] >> 1) | (p[i - 1] & 0x01) << 7;
	}
	p[0] = p[0] >> 1; // p[0] >>= 1;
	if (msb != 0) { // p127=1인 경우
		p[0] ^= 0xe1; // 0xe1 = 1+x+x^2+x^7 = x^128
	}
}

// p(x) --> p(x)*q(x)로 업데이트 하기
// p(x)*q(x) = p(x)*(q0 + q1*x + q2*x^2 + ... + q127*x^127)
//      = q0*p(x) + q1*p(x)*x + q2*p(x)*x^2 + ... + q127*p(x)*x^127
// p(x) --> p(x)*x --> p(x)*x^2 --> p(x)*x^127
void GF128_mul(byte p[16], byte q[16]) {
	byte z[16] = { 0, }; // z[16] = {0,0,...,0}
	byte qi; // q0, q1, ... , q127
	for (int i = 0; i < 16; i++) { // 바이트 단위
		for (int j = 0; j < 8; j++) { // 바이트 내 비트 위치
			qi = q[i] & (1 << (7 - j)); // 0 또는 0이 아닌(1로 간주)
			if (qi != 0) { // if(qi)와 동등함 
				for (int k = 0; k < 16; k++) z[k] ^= p[k];
			}
			GF128_xtime(p); // p(x), p(x)*x, ... , p(x)*x^127
		}
	}
	for (int k = 0; k < 16; k++) p[k] = z[k];
}

// msg_blocks: 메시지 블록의 개수 
// H[16]: GF(2^128) 다항식
void GHASH_ver0(byte msg[], int msg_blocks, byte H[16], byte tag[16]) {
	byte x[16];
	byte out[16] = { 0, };
	for (int i = 0; i < msg_blocks; i++) { // 메시지 블록 수 만큼
		for (int j = 0; j < 16; j++) x[j] = msg[i * 16 + j];
		xor_b_array(out, 16, x); // out = x xor out
		GF128_mul(out, H); // out = out*H
	}
	for (int j = 0; j < 16; j++) tag[j] = out[j];
}

// H(x)*q(x) = H(x)*(q0+q1*x+....+q7*x^7) --> HT[q(x)][]
// = q0*H(x) + q1*H(x)*x + ... + q7*H(x)*x^7 
// 더 빠르게 구현하기 위해 Table로 저장하는 코드
void Make_GHASH_H_table(byte H[16], byte HT[256][16]) {
	byte Z[16]; // 중간 계산 저장
	byte H_mul[16]; // H(x), H(x)*x, H(x)*x^2, ... , H(x)*x^7
	byte qj; // q_j: q0, q1, ... , q7

	for (int i = 0; i < 256; i++) { // i = 7차 이하 다항식 [0000 0000] ~ [1111 1111]
		// H(x)*[i 다항식] ==> HT[i][0]...HT[i][16]
		for (int j = 0; j < 16; j++) { // 버퍼 초기화
			Z[j] = 0x00;  // 계산 결과 저장할 장소
			H_mul[j] = H[j];  // H(x)로 초기화
		}
		for (int j = 0; j < 8; j++) { // q_j: q0, q1, ... , q7
			// [i 다항식] =  [q0 q1 q2 ... q7] (8비트)
			qj = (byte)((i >> (7 - j)) & 0x01);
			if (qj == 1) {
				xor_b_array(Z, 16, H_mul); // Z <- Z + qj*H(x)*x^j
			}
			GF128_xtime(H_mul); // Hmul <-- H_mul * x 
		}
		copy_b_array(Z, 16, HT[i]); // Z[] --> HT[i][]
	}
}

// HT[], R0[], R1[]을 이용한 GF(2^128)의 곱셈
// state[] --> state[] * H(x) (state[]: 현재 상태)
// p(x) = p0 + p1*x + p2*x^2 + ... + p127*x^127
//      = P[0] + P[1]*x^8 + ... + P[15]*x^128 (P[i]는 7차 이하 다항식)
// H(x)*p(x) = H(x)*P[0] + H(x)*P[1]*x^8 + ... + H(x)*P[15]*x^120
//           = HT[P[0]][] + HT[P[1]][]*x^8 + ... + HT[P[15]][]*x^120
// H(x)*P[15]*x^8
// (H(x)*P[14] + H(x)*P[15]*x^8)*x^8
// (H(x)*P[13] + (H(x)*P[14] + H(x)*P[15]*x^8)*x^8)^8
// H(x)*P[0] + (  ...  )*x^8
void GF128_Hmul(byte state[16], byte HT[256][16], byte R0[256], byte R1[256]) {
	byte W[16] = { 0, }; // 결과 저장용
	byte temp; // 7차 이하 다항식

	for (int i = 0; i < 15; i++) { // 0, 1, 2, ... , 14
		temp = state[15 - i]; // P[15], P[14], ... P[1]
		xor_b_array(W, 16, HT[temp]);  // H(x)*temp 
		//W --> W*x^8
		// W = W[0] ... W[15] 
		// ==> ( 0 W[0] ... W[14] ) xor (W[15] * x^128) = ( 0 W[0] ... W[14] ) xor (R0[W[15]] R1[W[15]] 0..)
		temp = W[15];
		for (int j = 15; j > 0; j--) {
			W[j] = W[j - 1];
		}
		W[0] = R0[temp]; // 주의! W[0] = R0[]
		W[1] ^= R1[temp]; //  W[1] = W[1] xor R1[]
	}
	// H(x)*P[0]를 더하기
	// W[] + H(x)*P[0] --> state[]
	temp = state[0]; // P[0]
	for (int j = 0; j < 16; j++) state[j] = W[j] ^ HT[temp][j];
}

// msg_blocks: 메시지 블록의 개수 
// H[16]: GF(2^128) 다항식
// HT, R0, R1 테이블을 이용한 GHASH 구현
void GHASH(byte msg[], int msg_blocks,
	byte HT[256][16], byte R0[256], byte R1[256],
	byte tag[16]) {
	byte x[16];
	byte out[16] = { 0, };
	for (int i = 0; i < msg_blocks; i++) { // 메시지 블록 수 만큼
		for (int j = 0; j < 16; j++) x[j] = msg[i * 16 + j];
		xor_b_array(out, 16, x); // out = x xor out
		//GF128_mul(out, H); // out = out*H
		GF128_Hmul(out, HT, R0, R1);
	}
	for (int j = 0; j < 16; j++) tag[j] = out[j];
}

void GHASH_test() {
	byte H[16];
	byte Msg[16] = { 0, };
	byte tag1[16];

	for (int j = 0; j < 16; j++) H[j] = j; // 테스트용 H(x)
	for (int j = 0; j < 16; j++) Msg[j] = 0;
	Msg[1] = 0x01;

	GHASH_ver0(Msg, 1, H, tag1);

	//예상 출력: GHASH Tag1 = 152ebc020406080a0c0e10121416181a
	print_b_array(tag1, 16, "Tag1");

	byte HT[256][16];
	byte tag2[16];

	Make_GHASH_H_table(H, HT);
	GHASH(Msg, 1, HT, R0, R1, tag2);
	print_b_array(tag2, 16, "Tag2");
}

// 7차 이하 다항식(1바이트)와 x^127 곱하기
// x^127 = 1+x+x^2+x^7
// (a0+a1*x+...+a7*x^7) * (1+x+x^2+x^7) --> R0[] R1[] (2바이트)
void Make_GHASH_const_R0R1(byte R0[256], byte R1[256]) {
	byte a[8]; // [a0a1...a7] -> 다항식을 저장
	for (int i = 0; i < 256; i++) {
		R0[i] = 0;
		R1[i] = 0;
	}

	for (int i = 0; i < 256; i++) { // 7차 이하 다항식 i = [a0a1...a7]
		for (int j = 0; j < 8; j++) {
			a[j] = (i >> (7 - j)) & 0x01; // a0, a1, ... , a7 -> 각각의 계수를 저장
		}
		// 계수들을 xor로 각각 더하여 결과물의 계수에 저장
		R0[i] = a[0] << 7;
		R0[i] ^= (a[0] ^ a[1]) << 6;
		R0[i] ^= (a[0] ^ a[1] ^ a[2]) << 5;
		R0[i] ^= (a[1] ^ a[2] ^ a[3]) << 4;
		R0[i] ^= (a[2] ^ a[3] ^ a[4]) << 3;
		R0[i] ^= (a[3] ^ a[4] ^ a[5]) << 2;
		R0[i] ^= (a[4] ^ a[5] ^ a[6]) << 1;
		R0[i] ^= a[5] ^ a[6] ^ a[7] ^ a[0];

		R1[i] = (a[7] ^ a[6] ^ a[1]) << 7;
		R1[i] ^= (a[7] ^ a[2]) << 6;
		R1[i] ^= a[3] << 5;
		R1[i] ^= a[4] << 4;
		R1[i] ^= a[5] << 3;
		R1[i] ^= a[6] << 2;
		R1[i] ^= a[7] << 1;
	}

	printf("byte R0[256] = { \n");
	for (int i = 0; i < 256; i++) {
		if (i != 255) { 
			printf("0x%02x, ", R0[i]);
		}
		else { // 마지막의 경우 comma가 안 찍히게 하기 위해
			printf("0x%02x ", R0[i]);

		}
		if ((i % 16) == 15) printf("\n");
	}
	printf("};\n");

	printf("byte R1[256] = { \n");
	for (int i = 0; i < 256; i++) {
		if (i != 255) {
			printf("0x%02x, ", R1[i]);
		}
		else { // 마지막의 경우 comma가 안 찍히게 하기 위해
			printf("0x%02x ", R1[i]);

		}
		if ((i % 16) == 15) printf("\n");
	}
	printf("};\n");
}