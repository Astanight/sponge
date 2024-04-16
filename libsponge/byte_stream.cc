#include "byte_stream.hh"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <regex>
#include <string>

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) : buffer(""),buffer_max_size(capacity),write_count(0),read_count(0){}

size_t ByteStream::write(const string &data) {
    size_t write_in_count = min(remaining_capacity(),data.length());        // need to consider the case of overwritting
    size_t origin_pos = 0;
    buffer += data.substr(origin_pos,write_in_count);
    origin_pos = write_in_count;
    write_count += write_in_count;
    return write_in_count;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    std::string to_copied = buffer.substr(0,len);
    return to_copied;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    buffer = buffer.substr(len);
    read_count += len;          // pop equs output
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    std::string read_content = peek_output(len);
    pop_output(len);
    return read_content;
}

void ByteStream::end_input() {end_sign = true;}

bool ByteStream::input_ended() const {
    return end_sign;
}

size_t ByteStream::buffer_size() const { return buffer.size(); }

bool ByteStream::buffer_empty() const { 
    if(buffer_size() == 0){
        return true;
    }
    return false; 
}

bool ByteStream::eof() const {
    if(end_sign and read_count == write_count and buffer_empty()){
        return true;
    }
    return false;
}

size_t ByteStream::bytes_written() const { return write_count; }

size_t ByteStream::bytes_read() const { return read_count; }

size_t ByteStream::remaining_capacity() const { return buffer_max_size - buffer_size(); }