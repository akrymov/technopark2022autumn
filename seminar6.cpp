#include <iostream>
#include <vector>

typedef unsigned char byte;

struct IInputStream {
    // Возвращает false, если поток закончился
    virtual bool Read(byte& value) = 0;
};

struct IOutputStream {
    virtual void Write(byte value) = 0;
};

class VectorInput : public IInputStream {
public:
    VectorInput(std::vector<byte>* input_buffer ) : buf(input_buffer), pos(0) {
    }
    
    virtual bool Read(byte& value) {
        if (pos >= buf->size())
            return false;
        value = (*buf)[pos++];
        return true;
    }
private:
    std::vector<byte>* buf;
    size_t pos;
};

class VectorOutput : public IOutputStream {
public:
    VectorOutput(std::vector<byte>* output_buffer): buf(output_buffer) {
        
    }
    
    virtual void Write(byte value) {
        buf->push_back(value);
    }

    
private:
    std::vector<byte>* buf;
};

class BitWriter {
public:
    BitWriter(IOutputStream& out_stream) : out(out_stream), pos(0) {
    }
    
    void write_bit(byte value) {
        if (pos == 8) {
            flush();
        }
        buf = buf | ((value & 1) << (pos++));
    }
    
    void write_byte(byte value) {
        
    }
    
    void flush() {
        out.Write(buf);
        buf = 0;
        pos = 0;
    }
private:
    IOutputStream& out;
    byte buf;
    byte pos;
};

class BitReader {
public:
    BitReader(IInputStream& in_stream) : in(in_stream), pos(0) {
    }
    
    bool read_bit(byte& value) {
        if (pos == 0) {
            if (!in.Read(buf)) {
                return false;
            }
            
        }
        value = (buf >> (pos++)) & 1;
        if (pos == 8) {
            pos = 0;
        }
        return true;
    }
    

private:
    IInputStream& in;
    byte buf;
    byte pos;
};



int main(int argc, const char * argv[]) {
    std::vector<byte> out_buf;
    VectorOutput vec_out(&out_buf);
    BitWriter writer(vec_out);
    writer.write_bit(0);
    writer.write_bit(1);
    writer.write_bit(0);
    writer.write_bit(1);
    writer.write_bit(0);
    writer.write_bit(1);
    writer.write_bit(0);
    writer.write_bit(1);
    writer.write_bit(0);
    writer.write_bit(1);
    writer.flush();
    // aa = 1010 1010
    // 2 = 00000010
    for (byte c : out_buf) {
        std::cout << std::hex << (int)c << std::endl;
    }
    
    VectorInput vec_in(&out_buf);
    BitReader reader(vec_in);
    byte val = 0;
    while(reader.read_bit(val)) {
        std::cout << (int)val << std::endl;
    }
    return 0;
}
