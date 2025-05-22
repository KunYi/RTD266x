#include <stdbool.h>
#include <stdint.h>

// --- C Implementation ---
typedef struct {
    uint8_t mask;
    uint8_t* data_ptr;
    uint32_t data_len;
} BitStream;

void BitStream_Init(BitStream* bs, uint8_t* data_ptr, uint32_t data_len) {
    bs->mask = 0x80;
    bs->data_ptr = data_ptr;
    bs->data_len = data_len;
}

bool BitStream_HasData(const BitStream* bs) {
    return bs->mask != 0 || bs->data_len != 0;
}

uint32_t BitStream_DataSize(const BitStream* bs) {
    return bs->data_len;
}

bool BitStream_ReadBit(BitStream* bs) {
    if (!bs->mask) {
        if (bs->data_len) {
            bs->mask = 0x80;
            bs->data_ptr++;
            bs->data_len--;
        }
    }
    bool result = (bs->data_ptr[0] & bs->mask) != 0;
    bs->mask >>= 1;
    return result;
}

static uint8_t gff_decode_nibble(BitStream* bit_stream) {
    uint8_t zero_cnt = 0;
    bool bit;

    do {
        if (!BitStream_HasData(bit_stream)) return 0xF0;
        bit = BitStream_ReadBit(bit_stream);
        if (bit) break;
        zero_cnt++;
    } while (zero_cnt < 6);

    if (zero_cnt > 5) {
        if (BitStream_DataSize(bit_stream) == 1) {
            return 0xF0;
        }
        return 0xFF;
    }

    switch (zero_cnt) {
        case 0: return 0;
        case 1:
            bit = BitStream_ReadBit(bit_stream);
            return bit ? 0xF : 1;
        case 2:
            bit = BitStream_ReadBit(bit_stream);
            return bit ? 8 : 2;
        case 3:
            bit = BitStream_ReadBit(bit_stream);
            return bit ? 7 : 0xC;
        case 4:
            bit = BitStream_ReadBit(bit_stream);
            if (bit) {
                bit = BitStream_ReadBit(bit_stream);
                return bit ? 9 : 4;
            } else {
                bit = BitStream_ReadBit(bit_stream);
                if (bit) {
                    bit = BitStream_ReadBit(bit_stream);
                    return bit ? 5 : 0xA;
                } else {
                    bit = BitStream_ReadBit(bit_stream);
                    return bit ? 0xB : 3;
                }
            }
            break;
        case 5:
            bit = BitStream_ReadBit(bit_stream);
            if (bit) {
                bit = BitStream_ReadBit(bit_stream);
                return bit ? 0xD : 0xE;
            } else {
                bit = BitStream_ReadBit(bit_stream);
                return bit ? 6 : 0xFF;
            }
            break;
    }
    return 0xFF;
}

uint32_t ComputeGffDecodedSize(uint8_t* data_ptr, uint32_t data_len) {
    BitStream bs;
    BitStream_Init(&bs, data_ptr, data_len);
    uint32_t cnt = 0;
    while (BitStream_HasData(&bs)) {
        uint8_t b = gff_decode_nibble(&bs);
        if (b == 0xFF) return 0;
        if (b == 0xF0) return cnt;

        b = gff_decode_nibble(&bs);
        if (b > 0xF) return 0;
        cnt++;
    }
    return cnt;
}

bool DecodeGff(uint8_t* data_ptr, uint32_t data_len, uint8_t* dest) {
    BitStream bs;
    BitStream_Init(&bs, data_ptr, data_len);
    while (BitStream_HasData(&bs)) {
        uint8_t n1 = gff_decode_nibble(&bs);
        if (n1 == 0xF0) return true;
        if (n1 == 0xFF) return false;

        uint8_t n2 = gff_decode_nibble(&bs);
        if (n2 > 0xF) return false;

        uint8_t byte = (n1 << 4) | n2;
        *dest++ = byte;
    }
    return true;
}
