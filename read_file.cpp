#include <cstdio>
#include <cstring>
#include <string>
#include <stdexcept>

std::string read_file_contents(const char *fname)
{
  FILE *fp = fopen(fname, "rb");
  if (!fp) {
    std::string err = "Failed to open ";
    err += fname;
    err += " with error: ";
    err += strerror(errno);
    throw std::runtime_error(err);
  }
  std::string contents;

  fseek(fp, 0, SEEK_END);
  contents.resize(ftell(fp));
  rewind(fp);
  fread(&contents[0], 1, contents.size(), fp);
  fclose(fp);
  return contents;
}


int main(int argc, char *argv[])
{
  auto c = read_file_contents("read_file.cpp");

  printf("%s\n", c.c_str());
  return 0;
}
