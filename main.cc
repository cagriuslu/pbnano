#include "pbnano.h"
#include <string>
#include <cstdio>

std::vector<uint8_t> hex_to_bytes(const std::string& hex) {
	std::vector<uint8_t> bytes;
	for (unsigned int i = 0; i < hex.length(); i += 2) {
		bytes.push_back(static_cast<uint8_t>(strtol(hex.substr(i, 2).c_str(), nullptr, 16)));
	}
	return bytes;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: pbnano-util HEXDATA\n");
		return -1;
	}

	std::string hexdata{argv[1]};
	auto data = hex_to_bytes(hexdata);

	int32_t a = 0;
	PbError a_error = pb_read_int32(data.data(), data.size(), 1, PB_LAST, &a);
	if (a_error == PB_NOT_FOUND) {
		// a is not expected to exist
		fprintf(stderr, "a: %d\n", a);
	} else {
		fprintf(stderr, "pb_read_int32 error: %d\n", a_error);
		return -1;
	}

	int64_t b = 0;
	PbError b_error = pb_read_int64(data.data(), data.size(), 2, PB_LAST, &b);
	if (b_error < 0) {
		fprintf(stderr, "pb_read_int64 error: %d\n", b_error);
		return -1;
	}
	fprintf(stderr, "b: %lld\n", b);

	uint32_t c = 0;
	PbError c_error = pb_read_uint32(data.data(), data.size(), 3, PB_LAST, &c);
	if (c_error < 0) {
		fprintf(stderr, "pb_read_uint32 error: %d\n", c_error);
		return -1;
	}
	fprintf(stderr, "c: %u\n", c);

	uint64_t d = 0;
	PbError d_error = pb_read_uint64(data.data(), data.size(), 4, PB_LAST, &d);
	if (d_error < 0) {
		fprintf(stderr, "pb_read_uint64 error: %d\n", d_error);
		return -1;
	}
	fprintf(stderr, "d: %llu\n", d);

	int32_t e = 0;
	PbError e_error = pb_read_sint32(data.data(), data.size(), 5, PB_LAST, &e);
	if (e_error < 0) {
		fprintf(stderr, "pb_read_sint32 error: %d\n", e_error);
		return -1;
	}
	fprintf(stderr, "e: %d\n", e);

	int64_t f = 0;
	PbError f_error = pb_read_sint64(data.data(), data.size(), 6, PB_LAST, &f);
	if (f_error < 0) {
		fprintf(stderr, "pb_read_sint64 error: %d\n", f_error);
		return -1;
	}
	fprintf(stderr, "f: %lld\n", f);

	bool g = false;
	PbError g_error = pb_read_bool(data.data(), data.size(), 7, PB_LAST, &g);
	if (g_error < 0) {
		fprintf(stderr, "pb_read_bool error: %d\n", g_error);
		return -1;
	}
	fprintf(stderr, "g: %d\n", g);

	int32_t h = false;
	PbError h_error = pb_read_enum(data.data(), data.size(), 8, PB_LAST, &h);
	if (h_error < 0) {
		fprintf(stderr, "pb_read_enum error: %d\n", h_error);
		return -1;
	}
	fprintf(stderr, "h: %d\n", h);

	uint32_t i = 0;
	PbError i_error = pb_read_fixed32(data.data(), data.size(), 9, PB_LAST, &i);
	if (i_error < 0) {
		fprintf(stderr, "pb_read_fixed32 error: %d\n", i_error);
		return -1;
	}
	fprintf(stderr, "i: %u\n", i);

	uint64_t j = 0;
	PbError j_error = pb_read_fixed64(data.data(), data.size(), 10, PB_LAST, &j);
	if (j_error < 0) {
		fprintf(stderr, "pb_read_fixed64 error: %d\n", j_error);
		return -1;
	}
	fprintf(stderr, "j: %llu\n", j);

	int32_t k = 0;
	PbError k_error = pb_read_sfixed32(data.data(), data.size(), 11, PB_LAST, &k);
	if (k_error < 0) {
		fprintf(stderr, "pb_read_sfixed32 error: %d\n", k_error);
		return -1;
	}
	fprintf(stderr, "k: %d\n", k);

	int64_t l = 0;
	PbError l_error = pb_read_sfixed64(data.data(), data.size(), 12, PB_LAST, &l);
	if (l_error < 0) {
		fprintf(stderr, "pb_read_sfixed64 error: %d\n", l_error);
		return -1;
	}
	fprintf(stderr, "l: %lld\n", l);

	float m = 0.0f;
	PbError m_error = pb_read_float(data.data(), data.size(), 13, PB_LAST, &m);
	if (m_error < 0) {
		fprintf(stderr, "pb_read_float error: %d\n", m_error);
		return -1;
	}
	fprintf(stderr, "m: %f\n", m);

	double n = 0.0;
	PbError n_error = pb_read_double(data.data(), data.size(), 14, PB_LAST, &n);
	if (n_error < 0) {
		fprintf(stderr, "pb_read_double error: %d\n", n_error);
		return -1;
	}
	fprintf(stderr, "n: %f\n", n);

	const char* o;
	uint64_t o_length;
	PbError o_error = pb_find_string(data.data(), data.size(), 15, PB_LAST, &o, &o_length);
	if (o_error < 0) {
		fprintf(stderr, "pb_find_string error: %d\n", o_error);
		return -1;
	}
	fprintf(stderr, "o: %s\n", std::string{o, o_length}.c_str());

	const uint8_t* p;
	uint64_t p_length;
	PbError p_error = pb_find_bytes(data.data(), data.size(), 16, PB_LAST, &p, &p_length);
	if (p_error < 0) {
		fprintf(stderr, "pb_find_bytes error: %d\n", p_error);
		return -1;
	}
	fprintf(stderr, "p: %s\n", std::string{reinterpret_cast<const char*>(p), p_length}.c_str());

	const uint8_t* q;
	uint64_t q_length;
	PbError q_error = pb_find_submessage(data.data(), data.size(), 17, PB_LAST, &q, &q_length);
	if (q_error < 0) {
		fprintf(stderr, "pb_find_submessage error: %d\n", q_error);
		return -1;
	}
	const char* q_a;
	uint64_t q_a_length;
	PbError q_a_error = pb_find_string(q, q_length, 1, PB_LAST, &q_a, &q_a_length);
	if (q_a_error < 0) {
		fprintf(stderr, "pb_find_string error: %d\n", q_a_error);
		return -1;
	}
	fprintf(stderr, "q_a: %s\n", std::string{q_a, q_a_length}.c_str());

	const uint8_t* r;
	PbError r_error = pb_find_field(data.data(), data.size(), 18, PB_FIRST, &r);
	if (r_error < 0) {
		fprintf(stderr, "pb_find_field error: %d\n", r_error);
		return -1;
	}
	while (r_error == PB_OK) {
		const char* r_item;
		uint64_t r_item_length;
		PbError r_item_error = pb_find_string(r, data.size() - (r - data.data()), 18, PB_FIRST, &r_item, &r_item_length);
		if (r_item_error < 0) {
			fprintf(stderr, "pb_find_string error: %d\n", r_item_error);
			return -1;
		}
		fprintf(stderr, "r: %s\n", std::string{r_item, r_item_length}.c_str());

		r_error = pb_find_field(r, data.size() - (r - data.data()), 18, PB_NEXT, &r);
		if (r_error < 0 && r_error != PB_NOT_FOUND) {
			fprintf(stderr, "pb_find_field error: %d\n", r_error);
			return -1;
		}
	}

	const uint8_t* s;
	PbError s_error = pb_find_field(data.data(), data.size(), 19, PB_FIRST, &s);
	if (s_error < 0) {
		fprintf(stderr, "pb_find_field error: %d\n", s_error);
		return -1;
	}
	while (s_error == PB_OK) {
		const uint8_t* s_item;
		uint64_t s_item_length;
		PbError s_item_error = pb_find_submessage(s, data.size() - (s - data.data()), 19, PB_FIRST, &s_item, &s_item_length);
		if (s_item_error < 0) {
			fprintf(stderr, "pb_find_string error: %d\n", s_item_error);
			return -1;
		}
		const char* s_a;
		uint64_t s_a_length;
		PbError s_a_error = pb_find_string(s_item, s_item_length, 1, PB_LAST, &s_a, &s_a_length);
		if (s_a_error < 0) {
			fprintf(stderr, "pb_find_string error: %d\n", s_a_error);
			return -1;
		}
		fprintf(stderr, "s_a: %s\n", std::string{s_a, s_a_length}.c_str());

		s_error = pb_find_field(s, data.size() - (s - data.data()), 19, PB_NEXT, &s);
		if (s_error < 0 && s_error != PB_NOT_FOUND) {
			fprintf(stderr, "pb_find_field error: %d\n", s_error);
			return -1;
		}
	}

	const uint8_t* first_t;
	uint64_t t_length;
	PbError t_error = pb_find_packed(data.data(), data.size(), 20, PB_FIRST, &first_t, &t_length);
	if (t_error < 0) {
		fprintf(stderr, "pb_find_packed error: %d\n", t_error);
		return -1;
	}
	const uint8_t* t = first_t;
	while (0 < (t_length - (t - first_t))) {
		int32_t t_value;
		PbError packed_t_error = pb_read_packed_int32(t, t_length - (t - first_t), &t_value, &t);
		if (packed_t_error < 0) {
			fprintf(stderr, "pb_read_packed_int32 error: %d\n", packed_t_error);
			return -1;
		}
		fprintf(stderr, "t: %d\n", t_value);
	}

	const uint8_t* first_u;
	uint64_t u_length;
	PbError u_error = pb_find_packed(data.data(), data.size(), 21, PB_FIRST, &first_u, &u_length);
	if (u_error < 0) {
		fprintf(stderr, "pb_find_packed error: %d\n", u_error);
		return -1;
	}
	const uint8_t* u = first_u;
	while (0 < (u_length - (u - first_u))) {
		float u_value;
		PbError packed_u_error = pb_read_packed_float(u, u_length - (u - first_u), &u_value, &u);
		if (packed_u_error < 0) {
			fprintf(stderr, "pb_read_packed_float error: %d\n", packed_u_error);
			return -1;
		}
		fprintf(stderr, "u: %f\n", u_value);
	}

	return 0;
}
