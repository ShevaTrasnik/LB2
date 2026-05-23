#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

using namespace std;
uint32_t CalculateChecksum(const vector<char>& data)
{
    uint32_t sum = 0;
    for (char byte : data)
    {
        sum += static_cast<unsigned char>(byte);
    }
    return sum;
}
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Usage: ChecksumWriter <dll_path>" << endl;
        return 1;
    }
    string fileName = argv[1];
    ifstream input(fileName, ios::binary);
    if (!input.is_open())
    {
        cout << "Error: cannot open DLL file" << endl;
        return 1;
    }
    vector<char> data(
        (istreambuf_iterator<char>(input)),
        istreambuf_iterator<char>()
    );
    input.close();
    uint32_t checksum = CalculateChecksum(data);
    ofstream output(fileName, ios::binary | ios::app);
    if (!output.is_open())
    {
        cout << "Error: cannot write to DLL file" << endl;
        return 1;
    }
    output.write(reinterpret_cast<char*>(&checksum), sizeof(checksum));
    output.close();
    cout << "Checksum was written successfully" << endl;
    cout << "Checksum = " << checksum << endl;
    return 0;
}