#include <vector>
#include <algorithm>
#include <cppunit/extensions/HelperMacros.h>
#include "my_stdio.h"

class MyStdioTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(MyStdioTest);
	CPPUNIT_TEST(fputc_test);
	CPPUNIT_TEST(putc_test);
	CPPUNIT_TEST(ungetc_test);
	CPPUNIT_TEST_SUITE_END();

	my_FILE testFile;
	std::vector<unsigned char> fileToReadBuffer;
	std::vector<unsigned char> fileToWrittenBuffer;
	int charsToError;

	static my_size_t fileRead(void* status, unsigned char* data, my_size_t max_size) {
		MyStdioTest& obj = *(MyStdioTest*)status;
		my_size_t readSize = obj.fileToReadBuffer.size();
		if (max_size < readSize) readSize = max_size;
		if (obj.charsToError >=0 && (my_size_t)obj.charsToError < readSize) readSize = obj.charsToError;
		std::copy(obj.fileToReadBuffer.begin(), obj.fileToReadBuffer.begin() + readSize, data);
		obj.fileToReadBuffer.erase(obj.fileToReadBuffer.begin(), obj.fileToReadBuffer.begin() + readSize);
		if (obj.charsToError >= 0) obj.charsToError -= readSize;
		return readSize;
	}

	static my_size_t fileWrite(void* status, const unsigned char* data, my_size_t length) {
		MyStdioTest& obj = *(MyStdioTest*)status;
		my_size_t writeSize = length;
		if (obj.charsToError >= 0 && (my_size_t)obj.charsToError < writeSize) writeSize = obj.charsToError;
		for (my_size_t i = 0; i < writeSize; i++) {
			obj.fileToWrittenBuffer.push_back(data[i]);
		}
		if (obj.charsToError > 0) obj.charsToError -= writeSize;
		return writeSize;
	}

	static int fileIsEof(void* status) {
		return ((MyStdioTest*)status)->fileToReadBuffer.empty() ? 1 : 0;
	}

	static int fileIsError(void* status) {
		return ((MyStdioTest*)status)->charsToError == 0 ? 1 : 0;
	}

public:
	MyStdioTest() : charsToError(-1) {}

	void setUp() {
		testFile.status = this;
		testFile.read = fileRead;
		testFile.write = fileWrite;
		testFile.is_eof = fileIsEof;
		testFile.is_error = fileIsError;
		testFile.ungetc_num = 0;
	}

	void tearDown() {
	}

	void fputc_test() {
		// initialize file
		fileToReadBuffer.clear();
		fileToWrittenBuffer.clear();
		charsToError = -1;

		// test normal operation
		CPPUNIT_ASSERT_EQUAL((int)'a', my_fputc('a', &testFile));
		CPPUNIT_ASSERT_EQUAL((std::vector<unsigned char>::size_type)1, fileToWrittenBuffer.size());
		CPPUNIT_ASSERT_EQUAL((unsigned char)'a', fileToWrittenBuffer.back());

		CPPUNIT_ASSERT_EQUAL((int)'b', my_fputc('b', &testFile));
		CPPUNIT_ASSERT_EQUAL((std::vector<unsigned char>::size_type)2, fileToWrittenBuffer.size());
		CPPUNIT_ASSERT_EQUAL((unsigned char)'b', fileToWrittenBuffer.back());

		// test big number input
		CPPUNIT_ASSERT_EQUAL((int)(unsigned char)0x1234, my_fputc(0x1234, &testFile));
		CPPUNIT_ASSERT_EQUAL((std::vector<unsigned char>::size_type)3, fileToWrittenBuffer.size());
		CPPUNIT_ASSERT_EQUAL((unsigned char)0x1234, fileToWrittenBuffer.back());

		CPPUNIT_ASSERT_EQUAL((int)(unsigned char)0x5678, my_fputc(0x5678, &testFile));
		CPPUNIT_ASSERT_EQUAL((std::vector<unsigned char>::size_type)4, fileToWrittenBuffer.size());
		CPPUNIT_ASSERT_EQUAL((unsigned char)0x5678, fileToWrittenBuffer.back());

		// test write error
		charsToError = 0;
		CPPUNIT_ASSERT_EQUAL(my_EOF, my_fputc('c', &testFile));
	}

	void putc_test() {
		// initialize file
		fileToReadBuffer.clear();
		fileToWrittenBuffer.clear();
		charsToError = -1;

		// test normal operation
		CPPUNIT_ASSERT_EQUAL((int)'a', my_putc('a', &testFile));
		CPPUNIT_ASSERT_EQUAL((std::vector<unsigned char>::size_type)1, fileToWrittenBuffer.size());
		CPPUNIT_ASSERT_EQUAL((unsigned char)'a', fileToWrittenBuffer.back());

		CPPUNIT_ASSERT_EQUAL((int)'b', my_putc('b', &testFile));
		CPPUNIT_ASSERT_EQUAL((std::vector<unsigned char>::size_type)2, fileToWrittenBuffer.size());
		CPPUNIT_ASSERT_EQUAL((unsigned char)'b', fileToWrittenBuffer.back());

		// test big number input
		CPPUNIT_ASSERT_EQUAL((int)(unsigned char)0x1234, my_putc(0x1234, &testFile));
		CPPUNIT_ASSERT_EQUAL((std::vector<unsigned char>::size_type)3, fileToWrittenBuffer.size());
		CPPUNIT_ASSERT_EQUAL((unsigned char)0x1234, fileToWrittenBuffer.back());

		CPPUNIT_ASSERT_EQUAL((int)(unsigned char)0x5678, my_putc(0x5678, &testFile));
		CPPUNIT_ASSERT_EQUAL((std::vector<unsigned char>::size_type)4, fileToWrittenBuffer.size());
		CPPUNIT_ASSERT_EQUAL((unsigned char)0x5678, fileToWrittenBuffer.back());

		// test write error
		charsToError = 0;
		CPPUNIT_ASSERT_EQUAL(my_EOF, my_putc('c', &testFile));
	}

	void ungetc_test() {
		// test normal operation
		testFile.ungetc_num = 0;
		for (int i = 0; i < MY_C_LIBRARY_UNGETC_MAX; i++) {
			CPPUNIT_ASSERT_EQUAL((int)(' ' + i), my_ungetc(' ' + i, &testFile));
		}
		CPPUNIT_ASSERT_EQUAL(my_EOF, my_ungetc('a', &testFile));

		// test EOF and conversion
		testFile.ungetc_num = 0;
		CPPUNIT_ASSERT_EQUAL(my_EOF, my_ungetc(my_EOF, &testFile));
		CPPUNIT_ASSERT_EQUAL((int)(unsigned char)(my_EOF - 1), my_ungetc(my_EOF - 1, &testFile));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(MyStdioTest);
