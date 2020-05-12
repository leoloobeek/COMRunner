#pragma once
#include <Windows.h>
#include <string>

//
// All this code taken directly from Dark Side Ops by Silent Break Security
// Follow @monoxgas, @moo_hax, and take the course!
//

static inline void a3_to_a4(unsigned char* a4, unsigned char* a3) {
	a4[0] = (a3[0] & 0xfc) >> 2;
	a4[1] = ((a3[0] & 0x03) << 4) + ((a3[1] & 0xf0) >> 4);
	a4[2] = ((a3[1] & 0x0f) << 2) + ((a3[2] & 0xc0) >> 6);
	a4[3] = (a3[2] & 0x3f);
}

static inline void a4_to_a3(unsigned char* a3, unsigned char* a4) {
	a3[0] = (a4[0] << 2) + ((a4[1] & 0x30) >> 4);
	a3[1] = ((a4[1] & 0xf) << 4) + ((a4[2] & 0x3c) >> 2);
	a3[2] = ((a4[2] & 0x3) << 6) + a4[3];
}

static inline unsigned char b64_lookup(unsigned char c) {
	if (c >= 'A' && c <= 'Z') return c - 'A';
	if (c >= 'a' && c <= 'z') return c - 71;
	if (c >= '0' && c <= '9') return c + 4;
	if (c == '+') return 62;
	if (c == '/') return 63;
	return 255;
}

static int DecodedLength(const std::string& in) {
	int numEq = 0;
	int n = (int)in.size();

	for (std::string::const_reverse_iterator it = in.rbegin(); *it == '='; ++it) {
		++numEq;
	}

	return ((6 * n) / 8) - numEq;
}

static bool Base64Decode(const std::string& in, std::string* out) {
	int i = 0, j = 0;
	size_t dec_len = 0;
	unsigned char a3[3];
	unsigned char a4[4];

	int input_len = (int)in.size();
	std::string::const_iterator input = in.begin();

	out->resize(DecodedLength(in));

	while (input_len--) {
		if (*input == '=') {
			break;
		}

		a4[i++] = *(input++);
		if (i == 4) {
			for (i = 0; i < 4; i++) {
				a4[i] = b64_lookup(a4[i]);
			}

			a4_to_a3(a3, a4);

			for (i = 0; i < 3; i++) {
				(*out)[dec_len++] = a3[i];
			}

			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 4; j++) {
			a4[j] = '\0';
		}

		for (j = 0; j < 4; j++) {
			a4[j] = b64_lookup(a4[j]);
		}

		a4_to_a3(a3, a4);

		for (j = 0; j < i - 1; j++) {
			(*out)[dec_len++] = a3[j];
		}
	}

	return (dec_len == out->size());
}

const char kBase64Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

static std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), slength, 0, 0);
	std::wstring r(len, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, s.c_str(), slength, &r[0], len);
	return r;
}

static std::string ws2s(const std::wstring& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = WideCharToMultiByte(CP_UTF8, 0, s.c_str(), slength, 0, 0, 0, 0);
	std::string r(len, '\0');
	WideCharToMultiByte(CP_UTF8, 0, s.c_str(), slength, &r[0], len, 0, 0);
	return r;
}