// HexByte.cpp
/*=================
  16�� ���ڿ��� �ٷ�� �Լ���
=================*/
#include "HexByte.h"

// �־��� ���ڰ� 16���� ���ڷ� ��ȿ�Ѱ�?
// 0,1,2, ... , 9, A~F, a~f
bool isHex(char ch) {
	return ((ch >= '0') && (ch <= '9')) ||  // 48~57 �����ΰ�? (��������)
		((ch >= 'A') && (ch <= 'F')) || // 65~70 �����ΰ�? (��������)
		((ch >= 'a') && (ch <= 'f'));  // 97~102 �����ΰ�? (��������)
}

// ���ڷ� ���� 1���� 16���� ---> 10������ 
// (char) ---> (byte) 0~15 (�ƴϸ� ����)
// 'a' ---> 10,  '0' ---> 0,  'f' ---> 15
byte Hex2Digit(char ch) {
	if (!isHex(ch)) {
		cout << ch << " is not a hex value." << endl;
		return -1; //�ǹ̾��� ���
	}
	if ((ch >= '0') && (ch <= '9')) {
		return  ch - '0'; // ��: '4'-'0' = 52 - 48 = 4
	}
	else if ((ch >= 'A') && (ch <= 'F')) {
		return ch - 'A' + 10;  // ��: 'B' - 'A' + 10 = 66 - 65 + 10 = 11
	}
	else if ((ch >= 'a') && (ch <= 'f')) {
		return ch - 'a' + 10;
	}
	// �������� �ʴ� �ڵ� (Ȥ�ó�...)
	cout << "Unknown error." << endl;
	return -1;
}

// 2�ڸ� 16���� ---> 1����Ʈ
// h[] = { h[0], h[1] } = { 'a', '1' } ---> 1010 0001 = A1 = 161
byte Hex2Byte(const char h[2]) {
	byte upper, lower;
	upper = h[0]; // ���� 4��Ʈ(nibble)�� ��Ÿ�� 1����
	lower = h[1]; // ���� 4��Ʈ(nibble)�� ��Ÿ�� 1����
	if ((!isHex(upper)) || (!isHex(lower))) {
		cout << "Hex Error" << endl;
		return -1;
	}
	return Hex2Digit(upper) * 16 + Hex2Digit(lower);
	// h[] = { 'a', '1' } --> 10*16 + 01 = 161 = A1
}

// 16�� ���ڿ� ---> ����Ʈ �迭
// 16�� ���ڿ� hex_str[] = "8d2e60365f17c7df1040d7501b4a7b5a"  (32�� 16����)
// ���ڿ� ���� hex_len = 32 (��� ����Ʈ �迭�� ���� * 2)
// ��� ����Ʈ �迭 barr[] = { '8d', '2e', ... , '5a' }
void Hex2Array(const char hex_str[], int hex_len, byte barr[]) {
	char h[2]; // h[] = { h[0], h[1] } ---> 1����Ʈ b_value
	byte b_value;
	for (int i = 0; i < hex_len / 2; i++) { // barr[] ũ�� = hex_len/2
		h[0] = hex_str[2 * i]; // ���� nibble
		h[1] = hex_str[2 * i + 1]; // ���� nibble
		// h[] = { hex_str[0], hex_str[1] },
		// h[] = { hex_str[2], hex_str[3] }, ...
		b_value = Hex2Byte(h); // 2�ڸ� 16���� ---> 1����Ʈ
		barr[i] = b_value;
	}
}

// ����Լ�
// const char* pStr = nullptr (default: nullptr)
// void print_b_array(byte b_arr[], int len, const char* pStr = nullptr);
void print_b_array(byte b_arr[], int len, const char* pStr) {
	if (pStr != nullptr) {
		printf("%s = ", pStr);
	}
	for (int i = 0; i < len; i++) {
		printf("%02x ", b_arr[i]);
	}
	printf("\n");
}

// ����Ʈ �迭 �����ϱ�
void copy_b_array(byte src[], int len, byte dest[]) {
	for (int i = 0; i < len; i++) {
		dest[i] = src[i];
	}
}

// data[] ---> data[] ^ xor_arr[] 
// ����! data[] �迭�� ������Ʈ  ( X xor Y ---> X ������Ʈ)
void xor_b_array(byte data[], int len, byte xor_arr[]) {
	for (int i = 0; i < len; i++) {
		data[i] ^= xor_arr[i];
	}
}

void hex_test() {
	cout << "isHex('a') = " << isHex('a') << endl;
	cout << "isHex('x') = " << isHex('x') << endl;
	cout << "Hex2Digit('a') = " << (int)Hex2Digit('a') << endl;

	char H[2] = { 'f', 'f' }; // 0xff
	cout << "Hex2Byte(H) = " << (int)Hex2Byte(H) << endl;
	const char* HexString = "8d2e60365f17c7df1040d7501b4a7b5a";
	byte HexArray[16];
	Hex2Array(HexString, 32, HexArray);
	cout << HexString << " = ";
	print_b_array(HexArray, 16);
	print_b_array(HexArray, 16, "Hex2Array");
}