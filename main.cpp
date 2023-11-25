#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

uint32_t leftRotate(uint32_t value, int bits)
{
	return (value << bits) | (value >> (32 - bits));
}

std::string sha1(const std::string& message)
{
	std::vector<uint8_t> bytes(message.begin(), message.end());
	uint64_t totalBits = bytes.size() * 8;//count of bits in out message

	bytes.push_back(0x80);//padding our message
	while ((bytes.size() * 8) % 512 != 448)
		bytes.push_back(0x00);

	for (int i = 7; i >= 0; --i)//padding our block(56 bytes) to 64 bytes
		bytes.push_back((totalBits >> (i * 8)) & 0xFF);

	uint32_t h[5] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };


	for (size_t i = 0; i < bytes.size(); i += 64)//from block 64 bytes to 80 block 4 bytes
	{
		const uint8_t* block = bytes.data() + i;

		uint32_t w[80];

		for (int j = 0; j < 16; ++j)
		{
			w[j] = (block[j * 4] << 24) | (block[j * 4 + 1] << 16) | (block[j * 4 + 2] << 8) | (block[j * 4 + 3]);
 		}

		for (int j = 16; j < 80; ++j)
		{
			w[j] = leftRotate(w[j - 3] ^ w[j - 8] ^ w[j - 14] ^ w[j - 16], 1);
		}

		uint32_t a = h[0];
		uint32_t b = h[1];
		uint32_t c = h[2];
		uint32_t d = h[3];
		uint32_t e = h[4];


		for (int t = 0; t < 80; ++t)
		{
			uint32_t f, k;
			if (t < 20)
			{
				f = (b & c) | ((~b) & d);
				k = 0x5A827999;
			}
			else if (t < 40)
			{
				f = b ^ c ^ d;
				k = 0x6ED9EBA1;
			}
			else if (t < 60)
			{
				f = (b & c) | (b & d) | (c & d);
				k = 0x8F1BBCDC;
			}
			else 
			{
				f = b ^ c ^ d;
				k = 0xCA62C1D6;
			}

			uint32_t temp = leftRotate(a, 5) + f + e + k + w[t];
			e = d;
			d = c;
			c = leftRotate(b, 30);
			b = a;
			a = temp;
		}

		h[0] += a;
		h[1] += b;
		h[2] += c;
		h[3] += d;
		h[4] += e;
	}

	std::stringstream result;
	for (int i = 0; i < 5; ++i)
		result << std::hex << std::setfill('0') << std::setw(8) << h[i];

	return result.str();
}

int main()
{
	std::string message = "Hello, SHA-1!";
	std::string sha1Hash = sha1(message);

	std::cout << "Message: " << message << std::endl;
	std::cout << "SHA-1 Hash: " << sha1Hash << std::endl;

	return 0;
}