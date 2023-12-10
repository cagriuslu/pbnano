#include <Test.pb.h>

int test() {
	pb::Test test;
	test.set_a(0);
	test.set_b(-1);
	test.set_c(12345678);
	test.set_d(18446744073709551615LLU);
	test.set_e(-12345678);
	test.set_f(1);
	test.set_g(true);
	test.set_h(m2::pb::TestEnum::TEST_ENUM_C);
	test.set_i(4294967295);
	test.set_j(281474976710655LLU);
	test.set_k(1);
	test.set_l(-1152921504606846975LL);
	test.set_m(1234.56F);
	test.set_n(-123456.789);
	test.set_o("Hello, world!");
	test.set_p("\x30\x31\x32\x33");
	test.mutable_q()->set_a("Submessage");
	test.add_r("ABC");
	test.add_r("DEF");
	test.add_r("GHI");
	test.add_s()->set_a("JKL");
	test.add_s()->set_a("MNO");
	test.add_s()->set_a("PQR");
	test.add_t(-2147483648);
	test.add_t(-1);
	test.add_t(0);
	test.add_t(1);
	test.add_t(2147483647);
	test.add_u(-1.0F);
	test.add_u(0.0F);
	test.add_u(1.0F);

	auto size = test.ByteSizeLong();
	std::vector<uint8_t> buffer(size, 0);
	test.SerializeToArray(buffer.data(), size);

	for (uint8_t i : buffer) {
		fprintf(stderr, "%02X", i);
	}
	fprintf(stderr, "\n");
}
