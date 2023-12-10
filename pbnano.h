#pragma once
#include "pbnano_detail.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Read scalar types
PbError pb_read_int32(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, int32_t* out);
PbError pb_read_int64(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, int64_t* out);
PbError pb_read_uint32(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, uint32_t* out);
PbError pb_read_uint64(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, uint64_t* out);
PbError pb_read_sint32(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, int32_t* out);
PbError pb_read_sint64(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, int64_t* out);
PbError pb_read_bool(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, bool* out);
PbError pb_read_enum(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, int32_t* out);
PbError pb_read_fixed32(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, uint32_t* out);
PbError pb_read_fixed64(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, uint64_t* out);
PbError pb_read_sfixed32(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, int32_t* out);
PbError pb_read_sfixed64(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, int64_t* out);
PbError pb_read_float(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, float* out);
PbError pb_read_double(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, double* out);

/// Find variable length types
PbError pb_find_string(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, const char** out_string, uint64_t* out_length);
PbError pb_find_bytes(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, const uint8_t** out_bytes, uint64_t* out_length);
PbError pb_find_submessage(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, const uint8_t** out_data, uint64_t* out_length);

/// Find/iterate repeated and map types
PbError pb_find_field(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, const uint8_t** out_field);

/// Read packed repeated types
PbError pb_find_packed(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, const uint8_t** out_data, uint64_t* out_length);
PbError pb_read_packed_int32(const uint8_t* data, size_t length, int32_t* out, const uint8_t** out_next_data);
PbError pb_read_packed_int64(const uint8_t* data, size_t length, int64_t* out, const uint8_t** out_next_data);
PbError pb_read_packed_uint32(const uint8_t* data, size_t length, uint32_t* out, const uint8_t** out_next_data);
PbError pb_read_packed_uint64(const uint8_t* data, size_t length, uint64_t* out, const uint8_t** out_next_data);
PbError pb_read_packed_sint32(const uint8_t* data, size_t length, int32_t* out, const uint8_t** out_next_data);
PbError pb_read_packed_sint64(const uint8_t* data, size_t length, int64_t* out, const uint8_t** out_next_data);
PbError pb_read_packed_bool(const uint8_t* data, size_t length, bool* out, const uint8_t** out_next_data);
PbError pb_read_packed_enum(const uint8_t* data, size_t length, int32_t* out, const uint8_t** out_next_data);
PbError pb_read_packed_fixed32(const uint8_t* data, size_t length, uint32_t* out, const uint8_t** out_next_data);
PbError pb_read_packed_fixed64(const uint8_t* data, size_t length, uint64_t* out, const uint8_t** out_next_data);
PbError pb_read_packed_sfixed32(const uint8_t* data, size_t length, int32_t* out, const uint8_t** out_next_data);
PbError pb_read_packed_sfixed64(const uint8_t* data, size_t length, int64_t* out, const uint8_t** out_next_data);
PbError pb_read_packed_float(const uint8_t* data, size_t length, float* out, const uint8_t** out_next_data);
PbError pb_read_packed_double(const uint8_t* data, size_t length, double* out, const uint8_t** out_next_data);

#ifdef __cplusplus
}
#endif
