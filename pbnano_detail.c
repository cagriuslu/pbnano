#include "pbnano_detail.h"
#include <stdio.h>
#include <stdbool.h>

#define RETURN_ERROR(err) do { if ((err) < 0) return (err); } while (0)

uint64_t _pb_field_from_varint(uint64_t varint) {
	return varint >> 3;
}
PbWireType _pb_wire_type_from_varint(uint64_t varint) {
	return varint & 0x07;
}

/// Returns number of bytes read
PbError _pb_fetch_varint(const uint8_t *data, size_t length, uint64_t *out_varint) {
	uint64_t varint = 0;

	for (size_t i = 0; i < length && i < 10; ++i) {
		uint8_t byte = data[i];

		if (i == 9) {
			// Last byte
			if (byte & 0x80) {
				return PB_VARINT_INVALID;
			} else {
				varint |= ((uint64_t) (byte & 0x01)) << 63;

				if (out_varint) {
					*out_varint = varint;
				}
				return PB_OK + 10;
			}
		} else {
			// Any other byte
			varint |= ((uint64_t) (byte & 0x7F)) << (i * 7);

			if (!(byte & 0x80)) {
				if (out_varint) {
					*out_varint = varint;
				}
				return PB_OK + i + 1;
			}
		}
	}

	return PB_VARINT_TOO_SHORT;
}
PbError _pb_fetch_i64(const uint8_t* data, size_t length, int64_t* out_i64) {
	uint64_t u64 = 0; // It's safer to deal with unsigned integer until the end

	for (size_t i = 0; i < length && i < 8; ++i) {
		uint8_t byte = data[i];
		u64 |= ((uint64_t) byte) << (i * 8);

		if (i == 7) {
			// Last byte
			if (out_i64) {
				*out_i64 = (int64_t) u64;
			}
			return PB_OK + 8;
		}
	}

	return PB_I64_TOO_SHORT;
}
PbError _pb_fetch_len(const uint8_t* data, size_t length, const uint8_t** out_data, uint64_t* out_length) {
	uint64_t len_length;
	PbError length_error = _pb_fetch_varint(data, length, &len_length);
	RETURN_ERROR(length_error);

	if (len_length <= length - length_error) {
		if (out_data) {
			*out_data = data + length_error;
		}
		if (out_length) {
			*out_length = len_length;
		}
		return PB_OK + length_error + len_length;
	} else {
		return PB_LEN_TOO_SHORT;
	}
}
PbError _pb_fetch_i32(const uint8_t* data, size_t length, int32_t* out_i32) {
	uint32_t u32 = 0; // It's safer to deal with unsigned integer until the end

	for (size_t i = 0; i < length && i < 4; ++i) {
		uint8_t byte = data[i];
		u32 |= ((uint32_t) byte) << (i * 8);

		if (i == 3) {
			// Last byte
			if (out_i32) {
				*out_i32 = (int32_t) u32;
			}
			return PB_OK + 4;
		}
	}

	return PB_I32_TOO_SHORT;
}

PbError _pb_find_field(const uint8_t *data, size_t length, uint64_t field_number, PbFindType find_type, const uint8_t** out_field, PbWireType* out_wire_type, const uint8_t** out_field_data) {
	const uint8_t* found_field = NULL, *prev_found_field = NULL;
	PbWireType found_field_wire_type;
	const uint8_t* found_field_data = NULL;

	for (const uint8_t* finger = data; (size_t)(finger - data) < length; ) {
		uint64_t tag;
		PbError tag_error = _pb_fetch_varint(finger, length - (finger - data), &tag); // Fetch tag
		RETURN_ERROR(tag_error);

		PbWireType wire_type = _pb_wire_type_from_varint(tag);
		if (field_number == _pb_field_from_varint(tag)) {
			prev_found_field = found_field;

			found_field = finger;
			found_field_wire_type = wire_type;
			found_field_data = finger + tag_error;

			if (find_type == PB_FIRST || (find_type == PB_NEXT && prev_found_field)) {
				break; // Bail out on first or second occurrence
			}
		}

		finger += tag_error; // Advance the finger by the length of the tag

		// Advance the finger by the length of the data
		switch (wire_type) {
			case PB_VARINT: {
				PbError varint_error = _pb_fetch_varint(finger, length - (finger - data), NULL);
				RETURN_ERROR(varint_error);
				finger += varint_error; // Advance the finger by the length of the varint
				break;
			}
			case PB_I64: {
				PbError i64_error = _pb_fetch_i64(finger, length - (finger - data), NULL);
				RETURN_ERROR(i64_error);
				finger += i64_error; // Advance the finger by the length of the i64
				break;
			}
			case PB_LEN: {
				PbError len_error = _pb_fetch_len(finger, length - (finger - data), NULL, NULL);
				RETURN_ERROR(len_error);
				finger += len_error; // Advance the finger by the length of the LEN
				break;
			}
			case PB_SGROUP:
			case PB_EGROUP:
				return PB_UNSUPPORTED_WIRE_TYPE;
			case PB_I32: {
				PbError i32_error = _pb_fetch_i32(finger, length - (finger - data), NULL);
				RETURN_ERROR(i32_error);
				finger += i32_error; // Advance the finger by the length of the i32
				break;
			}
			default:
				return PB_INVALID_WIRE_TYPE;
		}
	}

	bool is_found = false;
	if (find_type == PB_NEXT) {
		is_found = found_field && prev_found_field; // While searching for the next field, a prev field must exist
	} else {
		is_found = found_field;
	}

	if (is_found) {
		if (out_field) {
			*out_field = found_field;
		}
		if (out_wire_type) {
			*out_wire_type = found_field_wire_type;
		}
		if (out_field_data) {
			*out_field_data = found_field_data;
		}
		return PB_OK;
	} else {
		return PB_NOT_FOUND;
	}
}
PbError _pb_find_and_read_varint(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, uint64_t* out_variant) {
	const uint8_t* field, *field_data;
	PbWireType field_wire_type;
	PbError last_field_error = _pb_find_field(data, length, field_number, find_type, &field, &field_wire_type, &field_data);
	RETURN_ERROR(last_field_error);

	if (field_wire_type == PB_VARINT) {
		uint64_t varint;
		PbError varint_error = _pb_fetch_varint(field_data, length - (field_data - field), &varint);
		RETURN_ERROR(varint_error);

		if (out_variant) {
			*out_variant = varint;
		}
		return PB_OK;
	} else {
		return PB_TYPE_MISMATCH;
	}
}
PbError _pb_find_and_read_i64(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, int64_t* out_i64) {
	const uint8_t* field, *field_data;
	PbWireType field_wire_type;
	PbError last_field_error = _pb_find_field(data, length, field_number, find_type, &field, &field_wire_type, &field_data);
	RETURN_ERROR(last_field_error);

	if (field_wire_type == PB_I64) {
		int64_t i64;
		PbError i64_error = _pb_fetch_i64(field_data, length - (field_data - field), &i64);
		RETURN_ERROR(i64_error);

		if (out_i64) {
			*out_i64 = i64;
		}
		return PB_OK;
	} else {
		return PB_TYPE_MISMATCH;
	}
}
PbError _pb_find_and_read_len(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, const uint8_t** out_data, uint64_t* out_length) {
	const uint8_t* field, *field_data;
	PbWireType field_wire_type;
	PbError last_field_error = _pb_find_field(data, length, field_number, find_type, &field, &field_wire_type, &field_data);
	RETURN_ERROR(last_field_error);

	if (field_wire_type == PB_LEN) {
		const uint8_t* len_data;
		uint64_t len_length;
		PbError len_error = _pb_fetch_len(field_data, length - (field_data - field), &len_data, &len_length);
		RETURN_ERROR(len_error);

		if (out_data) {
			*out_data = len_data;
		}
		if (out_length) {
			*out_length = len_length;
		}
		return PB_OK;
	} else {
		return PB_TYPE_MISMATCH;
	}
}
PbError _pb_find_and_read_i32(const uint8_t* data, size_t length, uint64_t field_number, PbFindType find_type, int32_t* out_i32) {
	const uint8_t* field, *field_data;
	PbWireType field_wire_type;
	PbError last_field_error = _pb_find_field(data, length, field_number, find_type, &field, &field_wire_type, &field_data);
	RETURN_ERROR(last_field_error);

	if (field_wire_type == PB_I32) {
		int32_t i32;
		PbError i32_error = _pb_fetch_i32(field_data, length - (field_data - field), &i32);
		RETURN_ERROR(i32_error);

		if (out_i32) {
			*out_i32 = i32;
		}
		return PB_OK;
	} else {
		return PB_TYPE_MISMATCH;
	}
}
