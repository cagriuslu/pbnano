#pragma once
#include "stdint.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum PbError {
	PB_OK = 0,        // Operation successful
	PB_INVALID_WIRE_TYPE = -1,
	PB_UNSUPPORTED_WIRE_TYPE = -2,
	PB_VARINT_INVALID = -3,
	PB_VARINT_TOO_SHORT = -4,
	PB_I64_TOO_SHORT = -5,
	PB_LEN_TOO_SHORT = -6,
	PB_I32_TOO_SHORT = -7,
	PB_NOT_FOUND = -8,
	PB_TYPE_MISMATCH = -9,
} PbError;

typedef enum PbWireType {
	PB_VARINT = 0,
	PB_I64 = 1,
	PB_LEN = 2,
	PB_SGROUP = 3,
	PB_EGROUP = 4,
	PB_I32 = 5
} PbWireType;

typedef enum PbFindType {
	PB_FIRST,
	PB_NEXT,
	PB_LAST
} PbFindType;

uint64_t _pb_field_from_varint(uint64_t varint);
PbWireType _pb_wire_type_from_varint(uint64_t varint);

/// These functions return an error, or the number of bytes fetched
PbError _pb_fetch_varint(const uint8_t* data, size_t length, uint64_t* out_varint);
PbError _pb_fetch_i64(const uint8_t* data, size_t length, int64_t* out_i64);
PbError _pb_fetch_len(const uint8_t* data, size_t length, const uint8_t** out_data, uint64_t* out_length);
PbError _pb_fetch_i32(const uint8_t* data, size_t length, int32_t* out_i32);

PbError _pb_find_field(const uint8_t *data, size_t length, uint64_t field_number, PbFindType find_type, const uint8_t** out_field, PbWireType* out_wire_type, const uint8_t** out_field_data);
PbError _pb_find_and_read_varint(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, uint64_t* out_variant);
PbError _pb_find_and_read_i64(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, int64_t* out_i64);
PbError _pb_find_and_read_len(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, const uint8_t** out_data, uint64_t* out_length);
PbError _pb_find_and_read_i32(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, int32_t* out_i32);

#ifdef __cplusplus
}
#endif
