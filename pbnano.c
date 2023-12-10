#include "pbnano.h"

#define RETURN_ERROR(err) do { if ((err) < 0) return (err); } while (0)

PbError pb_read_int32(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, int32_t* out) {
	uint64_t varint;
	PbError varint_error = _pb_find_and_read_varint(data, length, field_number, find_type, &varint);
	RETURN_ERROR(varint_error);
	if (out) {
		*out = (int32_t) (varint & 0xFFFFFFFFLLU);
	}
	return PB_OK;
}

PbError pb_read_int64(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, int64_t* out) {
	uint64_t varint;
	PbError varint_error = _pb_find_and_read_varint(data, length, field_number, find_type, &varint);
	RETURN_ERROR(varint_error);
	if (out) {
		*out = (int64_t) (varint);
	}
	return PB_OK;
}

PbError pb_read_uint32(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, uint32_t* out) {
	uint64_t varint;
	PbError varint_error = _pb_find_and_read_varint(data, length, field_number, find_type, &varint);
	RETURN_ERROR(varint_error);
	if (out) {
		*out = (int32_t) (varint & 0xFFFFFFFFLLU);
	}
	return PB_OK;
}

PbError pb_read_uint64(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, uint64_t* out) {
	return _pb_find_and_read_varint(data, length, field_number, find_type, out);
}

PbError pb_read_sint32(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, int32_t* out) {
	uint64_t varint;
	PbError varint_error = _pb_find_and_read_varint(data, length, field_number, find_type, &varint);
	RETURN_ERROR(varint_error);
	if (out) {
		if (varint % 2) {
			// Negative
			*out = -((int32_t) ((varint + 1) >> 1));
		} else {
			// Positive
			*out = (int32_t) (varint >> 1);
		}
	}
	return PB_OK;
}

PbError pb_read_sint64(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, int64_t* out) {
	uint64_t varint;
	PbError varint_error = _pb_find_and_read_varint(data, length, field_number, find_type, &varint);
	RETURN_ERROR(varint_error);
	if (out) {
		if (varint % 2) {
			// Negative
			*out = -((int64_t) ((varint + 1) >> 1));
		} else {
			// Positive
			*out = (int64_t) (varint >> 1);
		}
	}
	return PB_OK;
}

PbError pb_read_bool(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, bool* out) {
	uint64_t varint;
	PbError varint_error = _pb_find_and_read_varint(data, length, field_number, find_type, &varint);
	RETURN_ERROR(varint_error);
	if (out) {
		*out = (bool) (varint & 0xFFFFFFFFLLU);
	}
	return PB_OK;
}

PbError pb_read_enum(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, int32_t* out) {
	return pb_read_int32(data, length, field_number, find_type, out);
}

PbError pb_read_fixed32(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, uint32_t* out) {
	int32_t i32;
	PbError varint_error = _pb_find_and_read_i32(data, length, field_number, find_type, &i32);
	RETURN_ERROR(varint_error);
	if (out) {
		*out = (uint32_t) i32;
	}
	return PB_OK;
}

PbError pb_read_fixed64(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, uint64_t* out) {
	int64_t i64;
	PbError varint_error = _pb_find_and_read_i64(data, length, field_number, find_type, &i64);
	RETURN_ERROR(varint_error);
	if (out) {
		*out = (uint64_t) i64;
	}
	return PB_OK;
}

PbError pb_read_sfixed32(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, int32_t* out) {
	return _pb_find_and_read_i32(data, length, field_number, find_type, out);
}

PbError pb_read_sfixed64(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, int64_t* out) {
	return _pb_find_and_read_i64(data, length, field_number, find_type, out);
}

PbError pb_read_float(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, float* out) {
	int32_t i32;
	PbError varint_error = _pb_find_and_read_i32(data, length, field_number, find_type, &i32);
	RETURN_ERROR(varint_error);
	if (out) {
		*out = *((float*) (&i32));
	}
	return PB_OK;
}

PbError pb_read_double(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, double* out) {
	int64_t i64;
	PbError varint_error = _pb_find_and_read_i64(data, length, field_number, find_type, &i64);
	RETURN_ERROR(varint_error);
	if (out) {
		*out = *((double*) (&i64));
	}
	return PB_OK;
}

PbError pb_find_string(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, const char** out_string, uint64_t* out_length) {
	const uint8_t* len_data;
	uint64_t len_length;
	PbError len_error = _pb_find_and_read_len(data, length, field_number, find_type, &len_data, &len_length);
	RETURN_ERROR(len_error);
	if (out_string) {
		*out_string = (const char*) len_data;
	}
	if (out_length) {
		*out_length = len_length;
	}
	return PB_OK;
}

PbError pb_find_bytes(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, const uint8_t** out_bytes, uint64_t* out_length) {
	return _pb_find_and_read_len(data, length, field_number, find_type, out_bytes, out_length);
}

PbError pb_find_submessage(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, const uint8_t** out_data, uint64_t* out_length) {
	return _pb_find_and_read_len(data, length, field_number, find_type, out_data, out_length);
}

PbError pb_find_field(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, const uint8_t** out_field) {
	return _pb_find_field(data, length, field_number, find_type, out_field, NULL, NULL);
}

PbError pb_find_packed(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, const uint8_t** out_data, uint64_t* out_length) {
	return _pb_find_and_read_len(data, length, field_number, find_type, out_data, out_length);
}

PbError pb_read_packed_int32(const uint8_t* data, size_t length, int32_t* out, const uint8_t** out_next_data) {
	uint64_t varint;
	PbError varint_error = _pb_fetch_varint(data, length, &varint);
	RETURN_ERROR(varint_error);

	if (out) {
		*out = (int32_t) (varint & 0xFFFFFFFFLLU);
	}
	if (out_next_data) {
		*out_next_data = data + varint_error;
	}
	return PB_OK;
}

PbError pb_read_packed_int64(const uint8_t* data, size_t length, int64_t* out, const uint8_t** out_next_data) {
	uint64_t varint;
	PbError varint_error = _pb_fetch_varint(data, length, &varint);
	RETURN_ERROR(varint_error);

	if (out) {
		*out = (int64_t) (varint);
	}
	if (out_next_data) {
		*out_next_data = data + varint_error;
	}
	return PB_OK;
}

PbError pb_read_packed_uint32(const uint8_t* data, size_t length, uint32_t* out, const uint8_t** out_next_data) {
	uint64_t varint;
	PbError varint_error = _pb_fetch_varint(data, length, &varint);
	RETURN_ERROR(varint_error);

	if (out) {
		*out = (int32_t) (varint & 0xFFFFFFFFLLU);
	}
	if (out_next_data) {
		*out_next_data = data + varint_error;
	}
	return PB_OK;
}

PbError pb_read_packed_uint64(const uint8_t* data, size_t length, uint64_t* out, const uint8_t** out_next_data) {
	uint64_t varint;
	PbError varint_error = _pb_fetch_varint(data, length, &varint);
	RETURN_ERROR(varint_error);

	if (out) {
		*out = varint;
	}
	if (out_next_data) {
		*out_next_data = data + varint_error;
	}
	return PB_OK;
}

PbError pb_read_packed_sint32(const uint8_t* data, size_t length, int32_t* out, const uint8_t** out_next_data) {
	uint64_t varint;
	PbError varint_error = _pb_fetch_varint(data, length, &varint);
	RETURN_ERROR(varint_error);

	if (out) {
		if (varint % 2) {
			// Negative
			*out = -((int32_t) ((varint + 1) >> 1));
		} else {
			// Positive
			*out = (int32_t) (varint >> 1);
		}
	}
	if (out_next_data) {
		*out_next_data = data + varint_error;
	}
	return PB_OK;
}

PbError pb_read_packed_sint64(const uint8_t* data, size_t length, int64_t* out, const uint8_t** out_next_data) {
	uint64_t varint;
	PbError varint_error = _pb_fetch_varint(data, length, &varint);
	RETURN_ERROR(varint_error);

	if (out) {
		if (varint % 2) {
			// Negative
			*out = -((int64_t) ((varint + 1) >> 1));
		} else {
			// Positive
			*out = (int64_t) (varint >> 1);
		}
	}
	if (out_next_data) {
		*out_next_data = data + varint_error;
	}
	return PB_OK;
}

PbError pb_read_packed_bool(const uint8_t* data, size_t length, bool* out, const uint8_t** out_next_data) {
	uint64_t varint;
	PbError varint_error = _pb_fetch_varint(data, length, &varint);
	RETURN_ERROR(varint_error);

	if (out) {
		*out = (bool) (varint & 0xFFFFFFFFLLU);
	}
	if (out_next_data) {
		*out_next_data = data + varint_error;
	}
	return PB_OK;
}

PbError pb_read_packed_enum(const uint8_t* data, size_t length, int32_t* out, const uint8_t** out_next_data) {
	return pb_read_packed_int32(data, length, out, out_next_data);
}

PbError pb_read_packed_fixed32(const uint8_t* data, size_t length, uint32_t* out, const uint8_t** out_next_data) {
	int32_t i32;
	PbError i32_error = _pb_fetch_i32(data, length, &i32);
	RETURN_ERROR(i32_error);

	if (out) {
		*out = (uint32_t) i32;
	}
	if (out_next_data) {
		*out_next_data = data + i32_error;
	}
	return PB_OK;
}

PbError pb_read_packed_fixed64(const uint8_t* data, size_t length, uint64_t* out, const uint8_t** out_next_data) {
	int64_t i64;
	PbError i64_error = _pb_fetch_i64(data, length, &i64);
	RETURN_ERROR(i64_error);

	if (out) {
		*out = (uint64_t) i64;
	}
	if (out_next_data) {
		*out_next_data = data + i64_error;
	}
	return PB_OK;
}

PbError pb_read_packed_sfixed32(const uint8_t* data, size_t length, int32_t* out, const uint8_t** out_next_data) {
	int32_t i32;
	PbError i32_error = _pb_fetch_i32(data, length, &i32);
	RETURN_ERROR(i32_error);

	if (out) {
		*out = i32;
	}
	if (out_next_data) {
		*out_next_data = data + i32_error;
	}
	return PB_OK;
}

PbError pb_read_packed_sfixed64(const uint8_t* data, size_t length, int64_t* out, const uint8_t** out_next_data) {
	int64_t i64;
	PbError i64_error = _pb_fetch_i64(data, length, &i64);
	RETURN_ERROR(i64_error);

	if (out) {
		*out = i64;
	}
	if (out_next_data) {
		*out_next_data = data + i64_error;
	}
	return PB_OK;
}

PbError pb_read_packed_float(const uint8_t* data, size_t length, float* out, const uint8_t** out_next_data) {
	int32_t i32;
	PbError i32_error = _pb_fetch_i32(data, length, &i32);
	RETURN_ERROR(i32_error);

	if (out) {
		*out = *((float*) (&i32));
	}
	if (out_next_data) {
		*out_next_data = data + i32_error;
	}
	return PB_OK;
}

PbError pb_read_packed_double(const uint8_t* data, size_t length, double* out, const uint8_t** out_next_data) {
	int64_t i64;
	PbError i64_error = _pb_fetch_i64(data, length, &i64);
	RETURN_ERROR(i64_error);

	if (out) {
		*out = *((double*) (&i64));
	}
	if (out_next_data) {
		*out_next_data = data + i64_error;
	}
	return PB_OK;
}
